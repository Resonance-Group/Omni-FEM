#include <UI/geometryShapes.h>

arcShape::arcShape() : edgeLineShape()
{
	nodeIndex1 = 0;
	nodeIndex2 = 0;
	
	isHidden = false;
	
	arcLength = 90.0d;
	maxSideLength = 10.0d;
	
	boundaryMarker = "<None>";
	inConductor = "<None>";
	
	isNormalDirection = true;
}



void arcShape::setArcLength(double lengthOfArc)
{
	arcLength = lengthOfArc;
}





