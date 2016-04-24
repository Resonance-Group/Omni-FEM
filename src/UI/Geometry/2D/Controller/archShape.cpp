#include <UI/geometryShapes.h>

arcShape::arcShape()
{
	nodeIndex1 = 0;
	nodeIndex2 = 0;
	
	isSelected = false;
	isHidden = false;
	
	arcLength = 90.0d;
	maxSideLength = 10.0d;
	
	boundaryMarker = "<None>";
	inConductor = "<None>";
	
	inGroup = 0;
	
	isNormalDirection = true;
}


void arcShape::setFirstNodeIndex(int index)
{
	nodeIndex1 = index;
}



void arcShape::setSecondNodeIndex(int index)
{
	nodeIndex2 = index;
}


int arcShape::getFirstNodeIndex()
{
	return nodeIndex1;
}



int arcShape::getSecondNodeIndex()
{
	return nodeIndex2;
}



