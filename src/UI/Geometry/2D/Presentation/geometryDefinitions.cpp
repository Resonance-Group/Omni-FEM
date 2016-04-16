#include <UI/geometryShapes.h>


nodePoint::nodePoint(GLdouble xcoordinate, GLdouble ycoordinate, wxGLCanvas *parent)
{
	xPoint = xcoordinate;
	yPoint = ycoordinate;
	
	glMatrixMode(GL_MODELVIEW);
	
	glBegin(GL_QUADS);
		glColor3f( 0.f, 0.f, 0.f );
		glVertex2f(-4.0f, -4.0f);
		glVertex2f(4.0f, -4.0f);
		glVertex2f(4.0f, 4.0f);
		glVertex2f(-4.0f, 4.0f);
	glEnd();
}