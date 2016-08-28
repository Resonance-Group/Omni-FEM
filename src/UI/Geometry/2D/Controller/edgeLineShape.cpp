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



void edgeLineShape::setBoundaryMarker(wxString boundary)
{
    boundaryMarker = boundary;
}



wxString edgeLineShape::getBoundaryMarker()
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



void edgeLineShape::draw(double node1X, double node1Y, double node2X, double node2Y)
{
    glLineWidth(2.0);
    glBegin(GL_LINES);
        if(isSelected)
            glColor3f(1.0f, 0.0f, 0.0f);
        else
            glColor3f(0.0f, 0.0f, 0.0f);
        glVertex2d(node1X, node1Y);
        glVertex2d(node2X, node2Y);
    glEnd();
    glLineWidth(0.5);
}