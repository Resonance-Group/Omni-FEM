#include "UI/geometryShapes.h"

node::node(double xCenter, double yCenter) : rectangleShape(xCenter, yCenter)
{
	xPixel = 0;
	yPixel = 0;
}

void node::setCenterYPixel(int yPix)
{
	yPixel = yPix;
}



void node::setCenterXPixel(int xPix)
{
	xPixel = xPix;
}



void node::draw()
{
	glBegin(GL_QUADS);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex2i(xPixel - 2, yPixel + 2);
		glVertex2i(xPixel + 2, yPixel + 2);
		glVertex2i(xPixel + 2, yPixel - 2);
		glVertex2i(xPixel - 2, yPixel - 2);
	glEnd();
}