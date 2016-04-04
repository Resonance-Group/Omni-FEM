#include <UI/openGLGeometry.h>

geometryEditorCanvas::geometryEditorCanvas(wxWindow *par, const wxPoint &position, const wxSize &size) : wxGLCanvas(par, wxID_ANY, NULL, position, size, wxBORDER_DOUBLE | wxBORDER_RAISED)
{

}


void geometryEditorCanvas::render()
{
	// Clears the color buffer
	glClear(GL_COLOR_BUFFER_BIT);
	
	//Reset to modelview matrix
	glMatrixMode(GL_MODELVIEW);// The matrix mode specifies which matrix stack is the target for matrix operations
	glLoadIdentity();
	
	glTranslated((float)this->GetSize().x / 2.0f, (float)this->GetSize().y / 2.0f, 0.0f);
	
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
	}
}


/* This function gets called over and over */
void geometryEditorCanvas::onGeometryPaint(wxPaintEvent &event)
{
	wxPaintDC dc(this);
	
	const wxSize canvasSize = GetSize();// This will get the current size of the drawing canvas
	canvasContext = new geometryEditorContext(this);// initilize the context
	
	glViewport(0, 0, canvasSize.x, canvasSize.y);// Set the viewport to see the rendering
	
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