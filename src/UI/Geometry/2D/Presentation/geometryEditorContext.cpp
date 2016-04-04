#include <UI/geometryEditor2D.h>


geometryEditorContext::geometryEditorContext(wxGLCanvas *canvas) : wxGLContext(canvas)
{
	SetCurrent(*canvas);// Set the current context to the drawing canvas
	
	/* This section is simply setting up setting for the canvas in a sense */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	/* This section is for initial setting */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glClearColor(0.556f, 1.f, 1.f, 0.f);// This will control the color of the background for the drawing canvas
	
	/* Ensure that there are no errors */
	GLenum error = glGetError();
	if(error != GL_NO_ERROR)
	{
	//	wxMessageBox("Error - " + gluErrorString(error));
		return;
	}
}



void geometryEditorContext::renderGeometry()
{
	glClear(GL_COLOR_BUFFER_BIT);
	
	glBegin(GL_QUADS);
		glVertex2f(-0.5f, -0.5f);
		glVertex2f(0.5f, -0.5f);
		glVertex2f(0.5f, 0.5f);
		glVertex2f(-0.5f, 0.5f);
	glEnd();
}