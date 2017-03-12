#include "UI/geometryShapes.h"

node::node(double xCenter, double yCenter) : rectangleShape(xCenter, yCenter)
{

}



node::node()
{
    
}



void node::setCenter(double xCoor, double yCoor)
{
    xCenterCoordinate = xCoor;
    yCenterCoordinate = yCoor;
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
    glPointSize(5.0);
    
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