#include <UI/openGLGeometry.h>


geometryEditorContext::geometryEditorContext(wxGLCanvas *canvas) : wxGLContext(canvas)
{
	SetCurrent(*canvas);// Set the current context to the drawing canvas
	
	/* This section is simply setting up setting for the canvas in a sense */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	/* This section is for initial setting */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, (float)canvas->GetSize().x, (float)canvas->GetSize().y, 0.0, 1.0, -1.0);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);// This will control the color of the background for the drawing canvas
	
	/* Ensure that there are no errors */
	GLenum error = glGetError();
	if(error != GL_NO_ERROR)
	{
	//	wxMessageBox("Error - " + gluErrorString(error));
		return;
	}
}



