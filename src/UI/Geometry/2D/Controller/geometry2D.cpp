#include <UI/geometryShapes.h>

geometry2D::geometry2D()
{
	
}



void geometry2D::setVertexNumber(int number)
{
	numberOfVertices = number;
}



int geometry2D::getVertexNumber()
{
	return numberOfVertices;
}



void geometry2D::toggleSelect()
{
	if(isSelected == true)
		isSelected = false;
	else
		isSelected = true;
}


void geometry2D::setCenterXCoordinate(double xCenter)
{
	xCenterCoordinate = xCenter;
}


void geometry2D::setCenterYCoordiante(double yCenter)
{
	yCenterCoordinate = yCenter;
}



double geometry2D::getCenterXCoordinate()
{
	return xCenterCoordinate;
}



double geometry2D::getCenterYCoordinate()
{
	return yCenterCoordinate;
}



void geometry2D::setGroup(int group)
{
	inGroup = group;
}



int geometry2D::getGroup()
{
	return inGroup;
}



bool geometry2D::getIsSelected()
{
	return isSelected;
}