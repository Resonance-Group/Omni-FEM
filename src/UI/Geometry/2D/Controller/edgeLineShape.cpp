#include "UI/geometryShapes.h"

edgeLineShape::edgeLineShape() : geometry2D()
{
	nodeIndex1 = 0;
	nodeIndex2 = 0;
	
	numberOfVertices = 2;
	
}



void edgeLineShape::setFirstNodeIndex(int index)
{
	nodeIndex1 = index;
}



void edgeLineShape::setSecondNodeIndex(int index)
{
	nodeIndex2 = index;
}



int edgeLineShape::getFirstNodeIndex()
{
	return nodeIndex1;
}



int edgeLineShape::getSecondNodeIndex()
{
	return nodeIndex2;
}