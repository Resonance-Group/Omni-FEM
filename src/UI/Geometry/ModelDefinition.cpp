#include <UI/ModelDefinition/ModelDefinition.h>


modelDefinition::modelDefinition(wxWindow *par, const wxPoint &point, const wxSize &size) : wxGLCanvas(par, wxID_ANY, NULL, point, size, wxBORDER_DOUBLE | wxBORDER_RAISED)
{
    _geometryContext = new wxGLContext(this);
	wxGLCanvas::SetCurrent(*_geometryContext);
    
    glViewport(0, 0, (double)this->GetSize().GetWidth(), (double)this->GetSize().GetHeight());
    
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glMatrixMode(GL_MODELVIEW);// The matrix mode specifies which matrix stack is the target for matrix operations
	glLoadIdentity();// Initial value
	glTranslated((float)this->GetSize().GetWidth() / 2.0f, (float)this->GetSize().GetHeight() / 2.0f, 0.0f);// This will move the camera to the center of the screen
    
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
    
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
    GLenum error = glGetError();
	if(error != GL_NO_ERROR)
	{
	//	wxMessageBox("Error - " + gluErrorString(error));
		return;
	}
    
    glMatrixMode(GL_MODELVIEW);
}


void modelDefinition::updateProjection()
{
    // First, load the projection matrix and reset the view to a default view
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    //Reset to modelview matrix
	glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    /* This section will handle the translation (panning) and scaled (zooming). 
     * Needs to be called each time a draw occurs in order to update the placement of all the components */
    if(_zoomFactor < 1e-9)
        _zoomFactor = 1e-9;
    
    if(_zoomFactor > 1e6)
        _zoomFactor = 1e6;
        
    glScaled(_zoomFactor / (this->GetSize().GetWidth() / this->GetSize().GetHeight()), _zoomFactor, 1.0);
//    glTranslated((float)this->GetSize().GetWidth() / 2.0f, (float)this->GetSize().GetHeight() / 2.0f, 0.0f);
    glTranslated(-_cameraX, -_cameraY, 0.0);
}

void modelDefinition::drawGrid()
{
    updateProjection();
    
    double cornerMinX = convertToXCoordinate(0);
    double cornerMinY = convertToYCoordinate(0);

    double cornerMaxX = convertToXCoordinate(this->GetSize().GetWidth());
    double cornerMaxY = convertToYCoordinate(this->GetSize().GetHeight());
    
    if(_preferences.getShowGridState())
    {
        glLineWidth(1.0);
        glEnable(GL_LINE_STIPPLE);
        /* 
        * The binary form is able to display the concept of glLineStipple for 
        * new users better then the Hex form. Although, the function is able to accept Hex
        * For an idea of how glLineStipple work, refer to the following link
        * http://images.slideplayer.com/16/4964597/slides/slide_9.jpg
        * 
        */ 
        glLineStipple(1, 0b0000100001000010);
    
        glBegin(GL_LINES);
            if(((cornerMaxX - cornerMinX) / _gridStep + (cornerMinY - cornerMaxY) / _gridStep < 200) && ((cornerMaxX - cornerMinX) / _gridStep > 0) && ((cornerMinY - cornerMaxY) / _gridStep > 0))
            {
                /* Create the grid for the vertical lines first */
                for(int i = cornerMinX / _gridStep - 1; i < cornerMaxX / _gridStep + 1; i++)
                {
                    if(i % 5 == 0)
                        glColor3d(0.0, 0.0, 0.0);
                    else
                        glColor3d(0.6, 0.6, 0.6);
                    
                    glVertex2d(i * _gridStep, cornerMinY);
                
                    glVertex2d(i * _gridStep, cornerMaxY);
                }
            
                /* Create the grid for the horizontal lines */
                for(int i = cornerMaxY / _gridStep - 1; i < cornerMinY / _gridStep + 1; i++)
                {
                    if(i % 5 == 0)
                        glColor3d(0.0, 0.0, 0.0);
                    else
                        glColor3d(0.6, 0.6, 0.6);
                    
                    glVertex2d(cornerMinX, i * _gridStep);
                    glVertex2d(cornerMaxX, i * _gridStep);
                }
            }
        
        glEnd();
        glDisable(GL_LINE_STIPPLE);
    }

    if(_preferences.getShowAxisState())
    {
        /* Create the center axis */    
        glColor3d(0.0, 0.0, 0.0);
        glLineWidth(1.5);
    
        glBegin(GL_LINES);
            glVertex2d(0, cornerMinY);
            glVertex2d(0, cornerMaxY);
        
            glVertex2d(cornerMinX, 0);
            glVertex2d(cornerMaxX, 0);
        glEnd();
    }
    
    if(_preferences.getShowOriginState())
    {
        glColor3b(0.0, 0.0, 0.0);
        glLineWidth(2.5);
        
        glBegin(GL_LINES);
            glVertex2d(0, -0.125);
            glVertex2d(0, 0.125);
            
            glVertex2d(-0.125, 0);
            glVertex2d(0.125, 0);
        glEnd();
    }
    
    glLineWidth(0.5);// Resets the line width back to the default
}



double modelDefinition::convertToXCoordinate(int xPixel)
{
    return (((2.0 / this->GetSize().GetWidth()) * ((double)xPixel - this->GetSize().GetWidth() / 2.0)) / _zoomFactor) * (this->GetSize().GetWidth() / this->GetSize().GetHeight()) + _cameraX;
}



double modelDefinition::convertToYCoordinate(int yPixel)
{
    return (-(2.0 / this->GetSize().GetHeight()) * ((double)yPixel - this->GetSize().GetHeight() / 2.0)) / _zoomFactor + _cameraY;
}



void modelDefinition::onPaintCanvas(wxPaintEvent &event)
{
    wxGLCanvas::SetCurrent(*_geometryContext);// This will make sure the the openGL commands are routed to the wxGLCanvas object
	wxPaintDC dc(this);// This is required for drawing
	
    glMatrixMode(GL_MODELVIEW);
    glClear(GL_COLOR_BUFFER_BIT);
    
    updateProjection();
    drawGrid();
    glMatrixMode(GL_MODELVIEW);
    
    // Add in the code to draw the different points here
    
    SwapBuffers();
}



void modelDefinition::onResize(wxSizeEvent &event)
{
    wxGLCanvas::SetCurrent(*_geometryContext);
    /* This section of the code will resize the viewport when a resize event occurs and then move the view back to the center of the grid
     * This is considered the initial starting position. The glLoadIdentity() function returns the matrix back to the the 
     * default condition
     */ 
    glViewport(0, 0, (double)this->GetSize().GetWidth(), (double)this->GetSize().GetHeight());
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslated((float)this->GetSize().GetWidth() / 2.0f, (float)this->GetSize().GetHeight() / 2.0f, 0.0f);
   
 // The code below is not needed at this time. But the class needs to be created a little more in order to accurately determine that the code is in fact not needed
/*  glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
    */
    
    this->Refresh();
}



wxBEGIN_EVENT_TABLE(modelDefinition, wxGLCanvas)
    EVT_PAINT(modelDefinition::onPaintCanvas)
    EVT_SIZE(modelDefinition::onResize)
wxEND_EVENT_TABLE()