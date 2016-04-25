#include <UI/geometryShapes.h>

rectangleShape::rectangleShape(double xCenterPoint, double yCenterPoint)
{
	xCenterCoordinate = xCenterPoint;
	
	yCenterCoordinate = yCenterPoint;
	
	isSelected = false;
	
	numberOfVertices = 4;
}



double rectangleShape::getDistance(double xp, double yp)
{
	return sqrt(pow((xCenterCoordinate - xp), 2) + pow((yCenterCoordinate - yp), 2));
}



void rectangleShape::draw()
{
	
}