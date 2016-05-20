#include "UI/geometryShapes.h"

edgeLineShape::edgeLineShape() : geometry2D()
{
	nodeIndex1 = 0;
	nodeIndex2 = 0;
	
	numberOfVertices = 2;
    
    boundaryMarker = "<None>";
	
}



void edgeLineShape::setFirstNodeIndex(int index)
{
	nodeIndex1 = index;
}



void edgeLineShape::setSecondNodeIndex(int index)
{
	nodeIndex2 = index;
}



int edgeLineShape::getFirstNodeIndex() const
{
	return nodeIndex1;
}



int edgeLineShape::getSecondNodeIndex() const
{
	return nodeIndex2;
}



void edgeLineShape::setHiddenStatus(bool status)
{
    isHidden = status;
}



bool edgeLineShape::getHiddenStatus()
{
    return isHidden;
}



void edgeLineShape::setBoundaryMarker(std::string boundary)
{
    boundaryMarker = boundary;
}



std::string edgeLineShape::getBoundaryMarker()
{
    return boundaryMarker;
}



void edgeLineShape::setConductor(std::string conductor)
{
    inConductor = conductor;
}



std::string edgeLineShape::getConductor()
{
    return inConductor;
}



void edgeLineShape::draw(int node1X, int node1Y, int node2X, int node2Y)
{
    glBegin(GL_LINES);
        if(isSelected)
            glColor3f(1.0f, 0.0f, 0.0f);
        else
            glColor3f(0.0f, 0.0f, 0.0f);
        glVertex2i(node1X, node1Y);
        glVertex2i(node2X, node2Y);
    glEnd();
        
}