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
    double cornerMinX = convertToXCoordinate(0);
    double cornerMinY = convertToYCoordinate(0);

    double cornerMaxX = convertToXCoordinate(this->GetSize().GetWidth());
    double cornerMaxY = convertToYCoordinate(this->GetSize().GetHeight());
    
    if(_preferences.getShowGridState())
    {
        /* The code for drawing the grid was adapted from the Agros2D project */
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
            if(((cornerMaxX - cornerMinX) / _preferences.getGridStep() + (cornerMinY - cornerMaxY) / _preferences.getGridStep() < 200) && ((cornerMaxX - cornerMinX) / _preferences.getGridStep() > 0) && ((cornerMinY - cornerMaxY) / _preferences.getGridStep() > 0))
            {
                /* Create the grid for the vertical lines first */
                for(int i = cornerMinX / _preferences.getGridStep() - 1; i < cornerMaxX / _preferences.getGridStep() + 1; i++)
                {
                    if(i % 4 == 0)
                    {
                        glLineWidth(0.7);
                        glColor3d(0.0, 0.0, 0.0);
                    }
                    else
                    {
                        glLineWidth(0.5);
                        glColor3d(0.7, 0.7, 0.7);
                    }
                    
                    glVertex2d(i * _preferences.getGridStep(), cornerMinY);
                
                    glVertex2d(i * _preferences.getGridStep(), cornerMaxY);
                }
            
                /* Create the grid for the horizontal lines */
                for(int i = cornerMaxY / _preferences.getGridStep() - 1; i < cornerMinY / _preferences.getGridStep() + 1; i++)
                {
                    if(i % 4 == 0)
                    {
                        glLineWidth(0.7);
                        glColor3d(0.0, 0.0, 0.0);
                    }
                    else
                    {
                        glLineWidth(0.5);
                        glColor3d(0.5, 0.7, 0.7);
                    }
                    
                    glVertex2d(cornerMinX, i * _preferences.getGridStep());
                    glVertex2d(cornerMaxX, i * _preferences.getGridStep());
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
    
    /* This will create a crosshairs to indicate the location of the origin */
    if(_preferences.getShowOriginState())
    {
        glColor3b(0.0, 0.0, 0.0);
        glLineWidth(2.5);
        
        glBegin(GL_LINES);
            glVertex2d(0, -0.25);
            glVertex2d(0, 0.25);
            
            glVertex2d(-0.25, 0);
            glVertex2d(0.25, 0);
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


/* This function gets called everytime a draw routine is needed */
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



void modelDefinition::onMouseWheel(wxMouseEvent &event)
{
    if(event.GetWheelRotation() != 0)
    {
        /* This section of the code was adapted from Agro2D */
        
        _cameraX += (((2.0 / this->GetSize().GetWidth()) * (event.GetX() - this->GetSize().GetWidth() / 2.0)) / _zoomFactor) * (this->GetSize().GetWidth() / this->GetSize().GetHeight());
        _cameraY += (-(2.0 / this->GetSize().GetHeight()) * (event.GetY() - this->GetSize().GetHeight() / 2.0)) / _zoomFactor;
        
        if(!_preferences.getMouseZoomReverseState())
        {
            if(event.GetWheelRotation() > 0)
                _zoomFactor *= pow(1.2, -(event.GetWheelDelta()) / 150.0);
            else
                _zoomFactor *= pow(1.2, (event.GetWheelDelta()) / 150.0);
        }
        else
        {
            if(event.GetWheelRotation() < 0)
                _zoomFactor *= pow(1.2, -(event.GetWheelDelta()) / 150.0);
            else
                _zoomFactor *= pow(1.2, (event.GetWheelDelta()) / 150.0);
        }
        
        /* This will recalculate the new position of the mouse. Assuming that the mouse does not move at all during the process
         * This also enables the feature where the zoom will zoom in/out at the position of the mouse */
        
        _cameraX -= (((2.0 / this->GetSize().GetWidth()) * (event.GetX() - this->GetSize().GetWidth() / 2.0)) / _zoomFactor) * (this->GetSize().GetWidth() / this->GetSize().GetHeight());
        _cameraY -= (-(2.0 / this->GetSize().GetHeight()) * (event.GetY() - this->GetSize().GetHeight() / 2.0)) / _zoomFactor;
    }
	
    this->Refresh();// This will force the canvas to experience a redraw event
}



void modelDefinition::onMouseMove(wxMouseEvent &event)
{
    int dx = event.GetX() - _mouseXCoordinate;
    int dy = event.GetY() - _mouseYCoordinate;
    
	_mouseXCoordinate = event.GetX();
	_mouseYCoordinate = event.GetY();
    
    if(event.ButtonIsDown(wxMOUSE_BTN_MIDDLE))
    {
        _cameraX -= (2.0 / this->GetSize().GetWidth()) * ((double)dx / _zoomFactor) * (this->GetSize().GetWidth() / this->GetSize().GetHeight());
        _cameraY += (2.0 / this->GetSize().GetHeight()) * ((double)dy / _zoomFactor);
    }
    
    this->Refresh();
}



void modelDefinition::onMouseLeftDown(wxMouseEvent &event)
{
    
}



void modelDefinition::onMouseRightDown(wxMouseEvent &event)
{
    std::string combineStringPixel;
    std::string combineStringCoord = "(";
    
    combineStringPixel = "(";
    combineStringPixel.append(std::to_string(_mouseXCoordinate));
    combineStringPixel.append(", ");
    combineStringPixel.append(std::to_string(_mouseYCoordinate));
    combineStringPixel.append(")");
    
    combineStringCoord.append(std::to_string(convertToXCoordinate(_mouseXCoordinate)));
    combineStringCoord.append(", ");
    combineStringCoord.append(std::to_string(convertToYCoordinate(_mouseYCoordinate)));
    combineStringCoord.append(")");
    
    wxMessageBox(combineStringCoord);
}



wxBEGIN_EVENT_TABLE(modelDefinition, wxGLCanvas)
    EVT_PAINT(modelDefinition::onPaintCanvas)
    EVT_SIZE(modelDefinition::onResize)
    EVT_ENTER_WINDOW(modelDefinition::onEnterWindow)
    /* This section is the event procedure for the mouse controls */
    EVT_MOUSEWHEEL(modelDefinition::onMouseWheel)
    EVT_MOTION(modelDefinition::onMouseMove)
    EVT_LEFT_DOWN(modelDefinition::onMouseLeftDown)
    EVT_RIGHT_DOWN(modelDefinition::onMouseRightDown)
wxEND_EVENT_TABLE()