#include <UI/openGLGeometry.h>

geometryEditorCanvas::geometryEditorCanvas(wxWindow *par, const wxPoint &position, const wxSize &size) : wxGLCanvas(par, wxID_ANY, NULL, position, size, wxBORDER_DOUBLE | wxBORDER_RAISED)
{
	geometryContext = new wxGLContext(this);
	wxGLCanvas::SetCurrent(*geometryContext);
	
	glViewport(0, 0, this->GetSize().x, this->GetSize().y);// Set the viewport to see the rendering
	
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);// This will control the color of the background for the drawing canvas

	glMatrixMode(GL_MODELVIEW);// The matrix mode specifies which matrix stack is the target for matrix operations
	glLoadIdentity();// Initial value
	
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
	glTranslated((float)this->GetSize().x / 2.0f, (float)this->GetSize().y / 2.0f, 0.0f);
	
    int tempWidth = this->GetSize().x;
    int tempHeight = this->GetSize().y;
    
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
wxEND_EVENT_TABLE()