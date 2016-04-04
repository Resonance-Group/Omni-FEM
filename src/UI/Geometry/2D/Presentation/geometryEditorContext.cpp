#include <UI/geometryEditor2D.h>


geometryEditorContext::geometryEditorContext(wxGLCanvas *canvas) : wxGLContext(canvas)
{
	SetCurrent(*canvas);
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glClearColor(0.f, 0.f, 0.f, 1.f);
	
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