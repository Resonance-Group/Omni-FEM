#include "UI/geometryShapes.h"

node::node(double xCenter, double yCenter) : rectangleShape(xCenter, yCenter)
{
	xPixel = 0;
	yPixel = 0;
}

node::node()
{
    
}

void node::setCenterYPixel(int yPix)
{
	yPixel = yPix;
}

void node::setCenter(double xCoor, double yCoor)
{
    xCenterCoordinate = xCoor;
    yCenterCoordinate = yCoor;
}

void node::setCenterXPixel(int xPix)
{
	xPixel = xPix;
}


int node::getCenterXPixel()
{
	return xPixel;
}


int node::getCenterYPixel()
{
	return yPixel;
}

void node::draw()
{
    if(isSelected)
        glColor3d(1.0, 0.0, 0.0);
    else
        glColor3d(0.0, 0.0, 0.0);
    
    glPointSize(6.0);
    
    glBegin(GL_POINTS);
        glVertex2d(xCenterCoordinate, yCenterCoordinate);
    glEnd();
    
    glColor3d(1.0, 1.0, 1.0);
    glPointSize(4.0);
    
    glBegin(GL_POINTS);
        glVertex2d(xCenterCoordinate, yCenterCoordinate);
    glEnd();
}


void node::setNodeIndex(int index)
{
	nodeIndex = index;
}



int node::getNodeIndex()
{
	return nodeIndex;
}