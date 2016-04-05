#include <UI/openGLGeometry.h>

geometryEditorCanvas::geometryEditorCanvas(wxWindow *par, const wxPoint &position, const wxSize &size) : wxGLCanvas(par, wxID_ANY, NULL, position, size, wxBORDER_DOUBLE | wxBORDER_RAISED)
{
	geometryContext = new wxGLContext(this);
	wxGLCanvas::SetCurrent(*geometryContext);
	
//	glViewport(0, 0, this->GetSize().x, this->GetSize().y);// Set the viewport to see the rendering
	
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);// This will control the color of the background for the drawing canvas

	glMatrixMode(GL_MODELVIEW);// The matrix mode specifies which matrix stack is the target for matrix operations
	glLoadIdentity();// Initial value
	glTranslated((float)this->GetSize().x / 2.0f, (float)this->GetSize().y / 2.0f, 0.0f);
    
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	/*	
		This will setup the screen such that the x value will extend from the left (x = 0) to the right (x = canvas->GetSize().x)
		As for the y value, it will extend from the top (y = 0) to the bottom (y = canvas->GetSize().y)
		By default, the screen is the the unit square. This command changes that 
	*/
	glOrtho(0.0, (float)this->GetSize().x, (float)this->GetSize().y, 0.0, 1.0, -1.0);
	
	/* Ensure that there are no errors */
	GLenum error = glGetError();
	if(error != GL_NO_ERROR)
	{
	//	wxMessageBox("Error - " + gluErrorString(error));
		return;
	}	
}


void geometryEditorCanvas::render()
{
	// Clears the color buffer
	glClear(GL_COLOR_BUFFER_BIT);
	
	//Reset to modelview matrix
	glMatrixMode(GL_MODELVIEW);
	
    // Translate to the center of the screen (0,0)
	
	
    float tempWidth = (float)this->GetSize().x;
    float tempHeight = (float)this->GetSize().y;
    
    if(viewPortMode == ViewPortMode::VIEWPORT_MODE_FULL)
    {
        glViewport(0, 0, tempWidth, tempHeight);
        
        glBegin(GL_QUADS);
            glColor3f(1.0f, 0.0f, 0.0f);
            glVertex2f(-tempWidth / 2.0f, -tempHeight / 2.0f);
            glVertex2f(tempWidth / 2.0f, -tempHeight / 2.0f);
            glVertex2f(tempWidth / 2.0f, tempHeight / 2.0f);
            glVertex2f(-tempWidth / 2.0f, tempHeight / 2.0f);
        glEnd();
    }
    else if(viewPortMode == ViewPortMode::VIEWPORT_MODE_HALF_CENTER)
    {
        glViewport(tempWidth / 4.f, tempHeight / 4.0f, tempWidth / 2.0f, tempHeight / 2.0f);
        
        glBegin(GL_QUADS);
            glColor3f(0, 1.0f, 0);
            glVertex2f(-tempWidth / 2.0f, -tempHeight / 2.0f);
            glVertex2f(tempWidth / 2.0f, -tempHeight / 2.0f);
            glVertex2f(tempWidth / 2.0f, tempHeight / 2.0f);
            glVertex2f(-tempWidth / 2.0f, tempHeight / 2.0f);
        glEnd();
    }
    else if(viewPortMode == ViewPortMode::VIEWPORT_MODE_HALF_TOP)
    {
        glViewport(tempWidth / 4.f, tempHeight / 2.0f, tempWidth / 2.0f, tempHeight / 2.0f);
        
        glBegin(GL_QUADS);
            glColor3f(0, 0, 1.0f);
            glVertex2f(-tempWidth / 2.0f, -tempHeight / 2.0f);
            glVertex2f(tempWidth / 2.0f, -tempHeight / 2.0f);
            glVertex2f(tempWidth / 2.0f, tempHeight / 2.0f);
            glVertex2f(-tempWidth / 2.0f, tempHeight / 2.0f);
        glEnd();
    }
    else if(viewPortMode == ViewPortMode::VIEWPORT_MODE_QUAD)
    {
        //Bottom left red quad
        glViewport( 0.f, 0.f, tempWidth / 2.f, tempHeight / 2.f );
        glBegin( GL_QUADS );
            glColor3f( 1.f, 0.f, 0.f );
            glVertex2f( -tempWidth / 4.f, -tempHeight / 4.f );
            glVertex2f(  tempWidth / 4.f, -tempHeight / 4.f );
            glVertex2f(  tempWidth / 4.f,  tempHeight / 4.f );
            glVertex2f( -tempWidth / 4.f,  tempHeight / 4.f );
        glEnd();

        //Bottom right green quad
        glViewport( tempWidth / 2.f, 0.f, tempWidth / 2.f, tempHeight / 2.f );
        glBegin( GL_QUADS );
            glColor3f( 0.f, 1.f, 0.f );
            glVertex2f( -tempWidth / 4.f, -tempHeight / 4.f );
            glVertex2f(  tempWidth / 4.f, -tempHeight / 4.f );
            glVertex2f(  tempWidth / 4.f,  tempHeight / 4.f );
            glVertex2f( -tempWidth / 4.f,  tempHeight / 4.f );
        glEnd();

        //Top left blue quad
        glViewport( 0.f, tempHeight / 2.f, tempWidth / 2.f, tempHeight / 2.f );
        glBegin( GL_QUADS );
            glColor3f( 0.f, 0.f, 1.f );
            glVertex2f( -tempWidth / 4.f, -tempHeight / 4.f );
            glVertex2f(  tempWidth / 4.f, -tempHeight / 4.f );
            glVertex2f(  tempWidth / 4.f,  tempHeight / 4.f );
            glVertex2f( -tempWidth / 4.f,  tempHeight / 4.f );
        glEnd();

        //Top right yellow quad
        glViewport( tempWidth / 2.f, tempHeight / 2.f, tempWidth / 2.f, tempHeight / 2.f );
        glBegin( GL_QUADS );
            glColor3f( 1.f, 1.f, 0.f );
            glVertex2f( -tempWidth / 4.f, -tempHeight / 4.f );
            glVertex2f(  tempWidth / 4.f, -tempHeight / 4.f );
            glVertex2f(  tempWidth / 4.f,  tempHeight / 4.f );
            glVertex2f( -tempWidth / 4.f,  tempHeight / 4.f );
        glEnd();
    }
    else if(viewPortMode == ViewPortMode::VIEWPORT_MODE_RADAR)
    {
        //Full size quad
        glViewport( 0.f, 0.f, tempWidth, tempHeight );
        glBegin( GL_QUADS );
            glColor3f( 1.f, 1.f, 1.f );
            glVertex2f( -tempWidth / 8.f, -tempHeight / 8.f );
            glVertex2f(  tempWidth / 8.f, -tempHeight / 8.f );
            glVertex2f(  tempWidth / 8.f,  tempHeight / 8.f );
            glVertex2f( -tempWidth / 8.f,  tempHeight / 8.f );
            glColor3f( 0.f, 0.f, 0.f );
            glVertex2f( -tempWidth / 16.f, -tempHeight / 16.f );
            glVertex2f(  tempWidth / 16.f, -tempHeight / 16.f );
            glVertex2f(  tempWidth / 16.f,  tempHeight / 16.f );
            glVertex2f( -tempWidth / 16.f,  tempHeight / 16.f );
        glEnd();

        //Radar quad
        glViewport( tempWidth / 2.f, tempHeight / 2.f, tempWidth / 2.f, tempHeight / 2.f );
        glBegin( GL_QUADS );
            glColor3f( 1.f, 1.f, 1.f );
            glVertex2f( -tempWidth / 8.f, -tempHeight / 8.f );
            glVertex2f(  tempWidth / 8.f, -tempHeight / 8.f );
            glVertex2f(  tempWidth / 8.f,  tempHeight / 8.f );
            glVertex2f( -tempWidth / 8.f,  tempHeight / 8.f );
            glColor3f( 0.f, 0.f, 0.f );
            glVertex2f( -tempWidth / 16.f, -tempHeight / 16.f );
            glVertex2f(  tempWidth / 16.f, -tempHeight / 16.f );
            glVertex2f(  tempWidth / 16.f,  tempHeight / 16.f );
            glVertex2f( -tempWidth / 16.f,  tempHeight / 16.f );
        glEnd();       
    }

/*
	if(colormode == COLOR_MODE_CYAN)
	{
		glBegin(GL_QUADS);
			glColor3f(0.0f, 1.0f, 1.0f);
			glVertex2f(-50.f, -50.f);
			glVertex2f(50.f, -50.f);
			glVertex2f(50.f, 50.f);
			glVertex2f(-50.f, 50.f);
		glEnd();
	}
	else
	{
		glBegin(GL_QUADS);
			glColor3f(1.0f, 0.0f, 0.0f);
			glVertex2f(-50.f, -50.f);
			
			glColor3f(1.0f, 1.0f, 0.0f);
			glVertex2f(50.0f, -50.0f);
			
			glColor3f(0.0f, 1.0f, 0.0f);
			glVertex2f(50.0f, 50.f);
			
			glColor3f(0.f, 0.f, 1.f);
			glVertex2f(-50.f, 50.f);
		glEnd();
	}*/
}


void geometryEditorCanvas::onKeyDown(wxKeyEvent &event)
{
    if(event.GetKeyCode() == LETTER_E || event.GetKeyCode() == LETTER_e)
    {
        viewPortMode++;
        if(viewPortMode > ViewPortMode::VIEWPORT_MODE_RADAR)
            viewPortMode = ViewPortMode::VIEWPORT_MODE_FULL;
    }
    
    this->Refresh();// This will force the canvas to experience a redraw event
}


/* This function gets called over and over */
void geometryEditorCanvas::onGeometryPaint(wxPaintEvent &event)
{
	wxGLCanvas::SetCurrent(*geometryContext);// This will make sure the the openGL commands are routed to the wxGLCanvas object
	wxPaintDC dc(this);// This is required for drawing
	
	render();
	
	SwapBuffers();// Display the output
}


void geometryEditorCanvas::onResize(wxSizeEvent &event)
{
//	wxMessageBox("hello");
}



wxBEGIN_EVENT_TABLE(geometryEditorCanvas, wxGLCanvas)
	EVT_PAINT(geometryEditorCanvas::onGeometryPaint)
	EVT_SIZE(geometryEditorCanvas::onResize)
    EVT_KEY_DOWN(geometryEditorCanvas::onKeyDown)
wxEND_EVENT_TABLE()