#include <UI/GeometryEditor2D.h>
#include <string>

void geometryEditor2D::addNode(double xPoint, double yPoint)// Could distance be the 1/mag which is the zoom factor
{
    /* This function was ported from the BOOL CFemmeDoc::AddNode(double x, double y, double d) located in FemmeDoc.cpp */
	node newNode;
    
    /* This section will make sure that two nodes are not drawn on top of each other */
	for(unsigned int i = 0; i < _nodeList.size(); i++)
	{
        // The program FEMM would start the zoom factor at 100. We are starting at 1. The process by which FEMM creates the nodes is very good. Therefor, we multiply our results by 100
		if(_nodeList.at(i).getDistance(xPoint, yPoint) < 1 / (*_zoomFactorPointer * 50))// This will compare against 1/mag where mag is the scaling function for zooming. However, it is currently being hardcoded to 0.01
			return;
	}
    
    /* This section will make sure that a node is not drawn on top of a block label */
	for(unsigned int i = 0; i < _blockLabelList.size(); i++)
	{
		if(_blockLabelList[i].getDistance(xPoint, yPoint) < 1 / (*_zoomFactorPointer * 50))
			return;
	}
    
    newNode.setCenter(xPoint, yPoint);
	_nodeList.push_back(newNode);
    
    /* If the node is in between a line, then break the line into 2 lines */
	for(unsigned int i = 0; i < _lineList.size(); i++)
	{
        edgeLineShape testLine = _lineList.at(i);
        node testFirstNode = testLine.getFirstNode();
		if(fabs(calculateShortestDistance(xPoint, yPoint, testLine)) < 1 / (*_zoomFactorPointer * 50))
		{
            /* Ok so if the node is on the line (determined by the calculateShortestDistance function) a new line will be created (This will be called line 1)
             * Line1 will be set equal to the original line (line0).
             * For the sake of explanation, the left most node will be considered as node 1 and the right most node will be considered node 2.
             * So, node 2 of line1 will then be switched to the newly created node and the first node of line0 will be set to the new node 
             * also. This effectively breaks the line into 2 shorter lines
             */ 
            edgeLineShape edgeLine = _lineList.at(i);
            _lineList.at(i).setSecondNode(newNode);// This will set the recently created node to be the second node of the shortend line
			
            edgeLine.setFirstNode(newNode);// This will set the recently created node to be the first node of the new line
			_lineList.push_back(edgeLine);// Add the new line to the array
		}
	} 
    
    /* If the node is in between an arc, then break the arc into 2 */
	for(unsigned int i = 0; i < _arcList.size(); i++)
	{
        /* Pretty much, this portion of the code is doing the exact same thing as the code above but instead of straight lines, we are working with arcs */
		if(fabs(-5) < 1 / (*_zoomFactorPointer * 100)) // this needs t be looked into more
		{
            Vector firstNode, secondNode, thirdNode, center;
            arcShape arcSegment = _arcList.at(i);
            double radius;
            
            firstNode.Set(_arcList.at(i).getFirstNode().getCenterXCoordinate(), _arcList.at(i).getFirstNode().getCenterYCoordinate());
			secondNode.Set(_arcList.at(i).getSecondNode().getCenterXCoordinate(), _arcList.at(i).getSecondNode().getCenterYCoordinate());
			thirdNode.Set(xPoint, yPoint);
			
			//getCircle{arcList[i], center, R);// No idea what this is.... yet
            center.Set(_arcList.at(i).getCenterXCoordinate(), _arcList.at(i).getCenterYCoordinate());
            radius = _arcList.at(i).getRadius();
			
            _arcList.at(i).setSecondNode(newNode);
			_arcList.at(i).setArcAngle((((firstNode - center) / (secondNode - center)) * 180.0 / PI).Arg());
			
            arcSegment.setFirstNode(newNode);
			arcSegment.setArcAngle((((firstNode - center) / (secondNode - center)) * 180.0 / PI).Arg());
			
			_arcList.push_back(arcSegment);
		}
	}
}



void geometryEditor2D::addBlockLabel(double xPoint, double yPoint)
{
    /* This code was adapted from the FEMM project. THe code came from FemmeDoc.cpp line 576 */
    blockLabel newLabel;
    
    // Make sure that teh block labe is not placed ontop of an existing block label
    for(unsigned int i = 0; i < _blockLabelList.size(); i++)
    {
        if(_blockLabelList.at(i).getDistance(xPoint, yPoint) < 1 / (*_zoomFactorPointer * 25))
            return;
    }
    
    // MAke sure that the block label is not placed on top of an existing node
    for(unsigned int i = 0; i < _nodeList.size(); i++)
	{
        // The program FEMM would start the zoom factor at 100. We are starting at 1. The process by which FEMM creates the nodes is very good. Therefor, we multiply our results by 100
		if(_nodeList.at(i).getDistance(xPoint, yPoint) < 1 / (*_zoomFactorPointer * 10))// This will compare against 1/mag where mag is the scaling function for zooming. However, it is currently being hardcoded to 0.01
			return;
	}
    
    // Make sure that the block label is not placed ontop of a line
    for(unsigned int i = 0; i < _lineList.size(); i++)
	{
		if(fabs(calculateShortestDistance(xPoint, yPoint, _lineList.at(i))) < 1 / (*_zoomFactorPointer * 100))
            return;
    }
            
    /* Later, add in check to make sure that a block node will not be placed on top of a arc */
    newLabel.setCenterXCoordinate(xPoint);
    newLabel.setCenterYCoordiante(yPoint);
   
    _blockLabelList.push_back(newLabel);

  //  _blockLabelNameArray.addString(wxT(newLabel.getProperty()->getMaterialName()));
 //   _blockLabelNameArray.addString(wxT("Test"));
}



void geometryEditor2D::addLine(int node0, int node1)
{
    /* This code was adapted from the FEMM project. See line 263 in FemmeDoc.cpp */
    edgeLineShape newLine;
    
    int tempNodeIndex1, tempNodeIndex2;
    
    if(node0 == -1 && node1 == -1)
    {
        tempNodeIndex1 = _nodeIndex1;
        tempNodeIndex2 = _nodeIndex2;
    }
    else
    {
        tempNodeIndex1 = node0;
        tempNodeIndex2 = node1;
    }
    
	if(tempNodeIndex1 == tempNodeIndex2)
		return;
	
/* Check to see if the line has already been created */	
	for(unsigned int i = 0; i < _lineList.size(); i++)
	{
		if((_lineList.at(i).getFirstNode() == _nodeList.at(tempNodeIndex1) && _lineList.at(i).getSecondNode() == _nodeList.at(tempNodeIndex2)) || (_lineList.at(i).getFirstNode() == _nodeList.at(tempNodeIndex2) && _lineList.at(i).getSecondNode() == _nodeList.at(tempNodeIndex1)))
			return;
	}
    
    newLine.setFirstNode(_nodeList.at(tempNodeIndex1));
    newLine.setSecondNode(_nodeList.at(tempNodeIndex2));
    
    /* This section will check to see if there are any intersections with other segments. If so, create a node at the intersection */
    for(int i = 0; i < _lineList.size(); i++)
    {
        double tempX, tempY;
        if(getIntersection(newLine, _lineList.at(i), tempX, tempY))
            addNode(tempX, tempY);
    }
    
    /* This section will check to see if there are any intersections with arcs. If so, create a node at the intersection */
    for(unsigned int i = 0; i < _arcList.size(); i++)
    {
        Vector newNodesPoints[2];
        int j = getLineToArcIntersection(newLine, _arcList.at(i), newNodesPoints);
        if(j > 0)
        {
            for(int k = 0; k < j; k++)
            {
                addNode(newNodesPoints[k].getXComponent(), newNodesPoints[k].getYComponent());
            }
        }
    }
    
    /* If things do not work out correctly with adding nodes to the intersection,
     * we can create a list of nodes that need to be added within the function. 
     * Then calculate what the distance tolerance should be and call addNode function
     * with the tolerance value as the tolerance between points. That can be done here.
     */ 

    _lineList.push_back(newLine);// Add the line to the list
    
    double shortDistance, dmin;
    Vector node0Vec, node1Vec, nodeiVec;
    
    node0Vec.Set(_nodeList.at(tempNodeIndex1).getCenterXCoordinate(), _nodeList.at(tempNodeIndex1).getCenterYCoordinate());
    node1Vec.Set(_nodeList.at(tempNodeIndex2).getCenterXCoordinate(), _nodeList.at(tempNodeIndex2).getCenterYCoordinate());
    
    dmin = Vabs(node1Vec - node0Vec) * 1.0e-05;

    for(int i = 0; i < _nodeList.size(); i++)
    {
        if((i != tempNodeIndex1) && (i != tempNodeIndex2))
        {
            nodeiVec.Set(_nodeList.at(i).getCenterXCoordinate(), _nodeList.at(i).getCenterYCoordinate());
            shortDistance = calculateShortestDistance(_nodeList.at(i).getCenterXCoordinate(), _nodeList.at(i).getCenterYCoordinate(), newLine);
            if((Vabs(nodeiVec - node0Vec) < dmin) || (Vabs(nodeiVec - node1Vec) < dmin))
                shortDistance = 2.0 * dmin;
            if(shortDistance < dmin)
            {
                _lineList.pop_back();
                addLine(tempNodeIndex1, i);
                addLine(i, tempNodeIndex2);
            }
            i = _nodeList.size();
        }
    }
    resetIndexs();
}


// Left off but this function still needs updated
void geometryEditor2D::addArc(arcShape &arcSeg, double tolerance, bool nodesAreSelected)
{
        // This function was obtained from CbeladrawDoc::AddArcSegment
	edgeLineShape segment;
	arcShape newArc;
	Vector intersectingNodes[2];
	Vector centerPoint;
	double dist, radius, minDistance, shortDistanceFromArc;
    
    if(nodesAreSelected && (_nodeList.at(_nodeIndex1) == _nodeList.at(_nodeIndex2)))
        return;
    else if(!nodesAreSelected && (arcSeg.getFirstNode() == arcSeg.getSecondNode()))
        return;
        
    if(nodesAreSelected)
    {
        arcSeg.setFirstNode(_nodeList.at(_nodeIndex1));
        arcSeg.setSecondNode(_nodeList.at(_nodeIndex2));
        arcSeg.calculate();
    }
		
	for(int i = 0; i < _arcList.size(); i++)
	{
		if((_arcList.at(i).getFirstNode() == arcSeg.getFirstNode()) && (_arcList.at(i).getSecondNode() == arcSeg.getSecondNode()) && (fabs(_arcList.at(i).getArcAngle() - arcSeg.getArcAngle()) < 1.0e-02))
			return;
	}
	
	if(tolerance == 0)
	{
		if(_nodeList.size() < 2)
			dist = 1.0e-08;
		else
		{
			Vector vec1, vec2;
			vec1.Set(_nodeList.at(0).getCenterXCoordinate(), _nodeList.at(0).getCenterYCoordinate());
			vec2 = vec1;
			for(int i = 0; i < _nodeList.size(); i++)
			{
				if(_nodeList.at(i).getCenterXCoordinate() < vec1.getXComponent())
					vec1.Set(_nodeList.at(i).getCenterXCoordinate(), vec1.getYComponent());
				
				if(_nodeList[i].getCenterXCoordinate() > vec2.getXComponent())
					vec2.Set(_nodeList.at(i).getCenterXCoordinate(), vec2.getYComponent());
				
				if(_nodeList.at(i).getCenterYCoordinate() < vec1.getYComponent())
					vec1.Set(vec1.getXComponent(), _nodeList.at(i).getCenterYCoordinate());
					
				if(_nodeList.at(i).getCenterYCoordinate() > vec2.getYComponent())
					vec2.Set(vec2.getXComponent(), _nodeList.at(i).getCenterYCoordinate());
			}
			
			dist = Vabs(vec1 - vec2) * 1.0e-06;
		}
	}
	else
		dist = tolerance;
	
	/* This section will check for any intesections with lines and arcs and if so, place a node there */
	for(int i = 0; i < _lineList.size(); i++)// This will check how many times the existing arc intercests the proposed arc.
	{
		int j = getLineToArcIntersection(_lineList.at(i), arcSeg, intersectingNodes); // Place the function for intersecting here This will be for an arc intersecting a line
		
		if(j > 0)
		{
			for(int k = 0; k < j; k++)
			{
				addNode(intersectingNodes[k].getXComponent(), intersectingNodes[k].getYComponent());
			}
		}
	}
	
	/* This section is for the proposed arc intersecting another arc */
	for(int i = 0; i < _arcList.size(); i++)
	{
		int j = 0; // This will be for an arc intersecting an arc
		
		if(j > 0)
		{
			for(int k = 0; k < j; k++)
			{
				addNode(intersectingNodes[k].getXComponent(), intersectingNodes[k].getYComponent());
			}
		}
	}
	
	_arcList.push_back(arcSeg);
	
//	getCircle(arcSeg, centerPoint, radius);
    centerPoint.Set(arcSeg.getCenterXCoordinate(), arcSeg.getCenterYCoordinate());
    radius = arcSeg.getRadius();
	
	if(tolerance == 0)
		minDistance = fabs(radius * PI * arcSeg.getArcAngle() / 180.0) * 1.0e-05;
	else
		minDistance = tolerance;
	
	for(int loopCounter = 0; loopCounter < _nodeList.size(); loopCounter++)
	{
		if((_nodeList.at(loopCounter) != arcSeg.getFirstNode()) && (_nodeList.at(loopCounter) != arcSeg.getSecondNode()))
		{
			shortDistanceFromArc = shortestDistanceFromArc(Vector(_nodeList.at(loopCounter).getCenterXCoordinate(), _nodeList.at(loopCounter).getCenterYCoordinate()), _arcList.at(_arcList.size() - 1));
			if(shortDistanceFromArc < minDistance)
			{
				Vector vec1, vec2, vec3;
				vec1.Set(arcSeg.getFirstNode().getCenterXCoordinate(), arcSeg.getFirstNode().getCenterYCoordinate());
				vec2.Set(arcSeg.getSecondNode().getCenterXCoordinate(), arcSeg.getSecondNode().getCenterYCoordinate());
				vec3.Set(_nodeList.at(loopCounter).getCenterXCoordinate(), _nodeList.at(loopCounter).getCenterYCoordinate());
				
				_arcList.pop_back();
				
				newArc = arcSeg;
				
                newArc.setSecondNode(_nodeList.at(loopCounter));
				newArc.setArcAngle(Varg((vec3 - centerPoint) / (vec1 - centerPoint)) * 180.0 / PI);
				addArc(newArc, minDistance, false);
				
				newArc = arcSeg;
                newArc.setFirstNode(_nodeList.at(loopCounter));
				newArc.setArcAngle(Varg((vec2 - centerPoint) / (vec3 - centerPoint)) * 180.0 / PI);
				addArc(newArc, minDistance, false);
				
				loopCounter = _nodeList.size();
			}
		}
	}
    resetIndexs();
}


// Talk to Palm about some of these functions
bool geometryEditor2D::getIntersection(edgeLineShape prospectiveLine, edgeLineShape intersectionLine, double &intersectionXPoint, double &intersectionYPoint)
{
    /* This code was adapted from FEMM from FEmmeDoc.cpp line 728 */
    Vector pNode0, pNode1, iNode0, iNode1;// These are the nodes on the prospective line (pNode) and the intersectionLine (iNode
    Vector tempNode0, tempNode1;
    // First check to see if there are any commmon end points. If so, there is no intersection
    if(prospectiveLine.getFirstNode() == intersectionLine.getFirstNode() || prospectiveLine.getFirstNode() == intersectionLine.getSecondNode() || prospectiveLine.getSecondNode() == intersectionLine.getFirstNode() || prospectiveLine.getSecondNode() == intersectionLine.getSecondNode())
        return false;
        
    pNode0.Set(prospectiveLine.getFirstNode().getCenterXCoordinate(), prospectiveLine.getFirstNode().getCenterYCoordinate());
    pNode1.Set(prospectiveLine.getSecondNode().getCenterXCoordinate(), prospectiveLine.getSecondNode().getCenterYCoordinate());
    iNode0.Set(intersectionLine.getFirstNode().getCenterXCoordinate(), intersectionLine.getFirstNode().getCenterYCoordinate());
    iNode1.Set(intersectionLine.getSecondNode().getCenterXCoordinate(), intersectionLine.getSecondNode().getCenterYCoordinate());
    
    tempNode0 = iNode0;
    tempNode1 = iNode1;
    
    double ee = min(Vabs(pNode1 - pNode0), Vabs(iNode1 - iNode0)) * 1.0e-8;
    
    iNode0 = (iNode0 - pNode0) / (pNode1 - pNode0);
    iNode1 = (iNode1 - pNode0) / (pNode1 - pNode0);
    
    if(iNode0.getXComponent() <= 0 && iNode1.getXComponent() <= 0)
        return false;
    else if(iNode0.getXComponent() >= 1.0 && iNode1.getXComponent() >= 1.0)
        return false;
    else if(iNode0.getYComponent() <= 0 && iNode1.getYComponent() <= 0)
        return false;
    else if(iNode0.getYComponent() >= 0 && iNode1.getYComponent() >= 0)
        return false;
        
    double z = iNode0.getYComponent() / (iNode0 - iNode1).getYComponent();
    
    double x = ((1.0 - z) * iNode0 + z * iNode1).getXComponent();
    if((x < ee) || (x > (1.0 - ee)))
        return false;
        
    pNode0 = (1.0 - z) * tempNode0 + z * tempNode1;
    
    intersectionXPoint = pNode0.getXComponent();
    intersectionYPoint = pNode0.getYComponent();
    
    return true;
}


/* The purpose of this function and neccessicity is being evaluated
void geometryEditor2D::getCircle(arcShape &arc, Vector &center, double &radius)
{
    Vector firstNode, secondNode, unitVector;
	double distance;
	
	firstNode.Set(arc.getFirstNode().getCenterXCoordinate(), arc.getFirstNode().getCenterYCoordinate());
	secondNode.Set(arc.getSecondNode().getCenterXCoordinate(), arc.getSecondNode().getCenterYCoordinate());
	
	distance = Vabs(firstNode - secondNode);
	
	unitVector = (firstNode - secondNode) / distance;
	
	radius = distance / (2.0 * sin(arc.getArcAngle() * PI / 360.0));
	
	center = firstNode + (distance / 2.0 + J * sqrt(pow(radius, 2) - pow(distance, 2) / 4.0)) * unitVector;
}
 * */



double geometryEditor2D::shortestDistanceFromArc(Vector point, arcShape &arcSegment)
{
    double radius, distance, length, z;
    Vector arcStartNode, arcEndNode, centerVec, tempVec;
    
    arcStartNode.Set(arcSegment.getFirstNode().getCenterXCoordinate(), arcSegment.getFirstNode().getCenterYCoordinate());
    arcEndNode.Set(arcSegment.getSecondNode().getCenterXCoordinate(), arcSegment.getSecondNode().getCenterYCoordinate());
    
    radius = arcSegment.getRadius();
    centerVec.Set(arcSegment.getCenterXCoordinate(), arcSegment.getCenterYCoordinate());
    
    distance = Vabs(point - centerVec);
    
    if(distance == 0)
        return radius;
        
    tempVec = (point - centerVec) / distance;
    length = Vabs(point - centerVec - radius * tempVec);
    z = Varg(tempVec / (arcStartNode - centerVec)) * 180.0 / PI;
    
    if((z > 0.0) && (z < arcSegment.getArcLength()))
        return length;
        
    z = Vabs(point - arcStartNode);
    length = Vabs(point - arcEndNode);
    
    if(z < length)
        return z;
    
    return length;
}



int geometryEditor2D::getLineToArcIntersection(edgeLineShape &lineSegment, arcShape &arcSegment, Vector *pointVec)
{
    /* Note: this function has not yet been verified to be working. Logical bugs could still exist */
    // This function was ported from Cbeladraw::GetLineArcIntersection
    
	Vector lineSegVec1, lineSegVec2, arcSegVec1, arcSegVec2, unitVec1, tempVec2, arcCenterPoint;
	double distance, length, radius, z;
	int intersectionCounter = 0;

    lineSegVec1.Set(lineSegment.getFirstNode().getCenterXCoordinate(), lineSegment.getFirstNode().getCenterYCoordinate());
	lineSegVec2.Set(lineSegment.getSecondNode().getCenterXCoordinate(), lineSegment.getSecondNode().getCenterYCoordinate());
	
	arcSegVec1.Set(arcSegment.getFirstNode().getCenterXCoordinate(), arcSegment.getFirstNode().getCenterYCoordinate());
	arcSegVec2.Set(arcSegment.getSecondNode().getCenterXCoordinate(), arcSegment.getSecondNode().getCenterYCoordinate());
	
	distance = Vabs(arcSegVec2 - arcSegVec1);
	
    radius = arcSegment.getRadius();
    
    arcCenterPoint.Set(arcSegment.getCenterXCoordinate(), arcSegment.getCenterYCoordinate());
    
    // Determining the distance between the line and the circle's center
	distance = Vabs(lineSegVec2 - lineSegVec2);
	unitVec1 = (lineSegVec2 - lineSegVec1) / distance;
	tempVec2 = (arcCenterPoint - lineSegVec1) / unitVec1;
	
	if(fabs(tempVec2.getYComponent()) > radius)
		return 0;
		
	length = sqrt(pow(radius, 2) - pow(tempVec2.getYComponent(), 2));
	// If the line is a tangent, make it a tangent
	if((length / radius) < 1.0e-05)
	{
		pointVec[intersectionCounter] = lineSegVec1 + tempVec2.getXComponent() * unitVec1;
		radius = ((pointVec[intersectionCounter] - lineSegVec1) / unitVec1).getXComponent();
		z = Varg((pointVec[intersectionCounter] - arcCenterPoint) / (arcSegVec1 - arcCenterPoint));
		if((radius > 0) && (radius < distance) && (z > 0.0) && (z < (arcSegment.getArcAngle() * PI / 180)))
			intersectionCounter++;
		return intersectionCounter;
	}
	
    // First intersection
	pointVec[intersectionCounter] = lineSegVec1 + (tempVec2.getXComponent() + length) * unitVec1;
	radius = ((pointVec[intersectionCounter] - lineSegVec1) / unitVec1).getXComponent();
	z = Varg((pointVec[intersectionCounter] - arcCenterPoint) / (arcSegVec1 - arcCenterPoint));
	if((radius > 0) && (radius < distance) && (z > 0.0) && (z < (arcSegment.getArcAngle() * PI / 180)))
		intersectionCounter++;
    
    // Second intersection
	pointVec[intersectionCounter] = lineSegVec1 + (tempVec2.getXComponent() + length) * unitVec1;
	radius = ((pointVec[intersectionCounter] - lineSegVec1) / unitVec1).getXComponent();
	z = Varg((pointVec[intersectionCounter] - arcCenterPoint) / (arcSegVec1 - arcCenterPoint));
	if((radius > 0) && (radius < distance) && (z > 0.0) && (z < (arcSegment.getArcAngle() * PI / 180)))
		intersectionCounter++;
		
	return intersectionCounter;
}



int geometryEditor2D::getArcToArcIntersection(arcShape& arcSegment1, arcShape &arcSegment2, Vector *point)
{
    // This function was ported from CbeladrawDoc::GetArcArcIntersection (Please note that the variable names may not be accurate to what they actually are. This is because there is a lack of documentation in FEMM)
    Vector arcCenter1, arcCenter2, arc1StartNode, arc2StartNode, tempVec;
    double distance, arcRadius1, arcRadius2, length, center, arc1Length, arc2Length, z0, z1;
    int counter = 0;
    
    arc1StartNode.Set(arcSegment1.getFirstNode().getCenterXCoordinate(), arcSegment1.getFirstNode().getCenterYCoordinate());
    arc2StartNode.Set(arcSegment2.getFirstNode().getCenterXCoordinate(), arcSegment2.getFirstNode().getCenterYCoordinate());
    
    arcRadius1 = arcSegment1.getRadius();
    arcRadius2 = arcSegment2.getRadius();
    
    arcCenter1.Set(arcSegment1.getCenterXCoordinate(), arcSegment1.getCenterYCoordinate());
    arcCenter2.Set(arcSegment2.getCenterXCoordinate(), arcSegment2.getCenterYCoordinate());
    
    distance = Vabs(arcCenter1 - arcCenter2);
    
    if((distance > (arcRadius1 + arcRadius2) || (distance < 1.0e-08)))
        return 0;
    
    length = sqrt((arcRadius1 + arcRadius2 - distance) * (distance + arcRadius1 - arcRadius2) * (distance - arcRadius1 + arcRadius2) * (distance + arcRadius1 + arcRadius2)) / (2.0 * distance);
    
    center = 1.0 + pow((arcRadius1 / distance), 2) - pow(arcRadius2 / distance, 2);
    
    tempVec = (arcCenter2 - arcCenter1) / distance;
    
    arc1Length = arcSegment1.getArcLength();
    arc2Length = arcSegment2.getArcLength();
    
    point[counter] = arcCenter1 + (center * distance / 2.0 + J * length) * tempVec;
    
    z0 = Varg((point[counter] - arcCenter1) / (arc1StartNode - arcCenter1));
    z1 = Varg((point[counter] - arcCenter2) / (arc2StartNode - arcCenter2));
    
    if((z0 > 0.0) && (z0 < arc1Length) && (z1 > 0.0) && (z1 < arc2Length))
        counter++;
        
    if(fabs(distance - arcRadius1 + arcRadius2) / (arcRadius1 + arcRadius2) < 1.0e-05)
    {
        point[counter] = arcCenter1 + center * distance * (tempVec / 2.0);
        return counter;
    }
    
    point[counter] = arcCenter1 + (center * distance / 2.0 - J * length) * tempVec;
    z0 = Varg((point[counter] - arc1StartNode) / (arc1StartNode - arcCenter1));
    z1 = Varg((point[counter] - arc2StartNode) / (arc2StartNode - arcCenter2));
    
    if((z0 > 0.0) && (z0 < arc1Length) && (z1 > 0.0) && (z1 < arc2Length))
        counter++;
        
    return counter;    
}


// Consider removing the last two arguments
// Maybe the last parameter can be an edgeLineShape
//double geometryEditor2D::calculateShortestDistance(double p, double q, int segmentIndex)
double geometryEditor2D::calculateShortestDistance(double p, double q, edgeLineShape segment)
{
    // I have no idea what this function does
    double t, xNew[3], wereNew[3];
	node test = segment.getFirstNode();
    //xNew[0] = _nodeList[_lineList[segmentIndex].getFirstNodeIndex()].getCenterXCoordinate();
    xNew[0] = segment.getFirstNode().getCenterXCoordinate();
    wereNew[0] = segment.getFirstNode().getCenterYCoordinate();
	//wereNew[0] = _nodeList[_lineList[segmentIndex].getFirstNodeIndex()].getCenterYCoordinate();
	
    xNew[1] = segment.getSecondNode().getCenterXCoordinate();
    wereNew[1] = segment.getSecondNode().getCenterYCoordinate();
	
	t = ((p - xNew[0]) * (xNew[1] - xNew[0]) + (q - wereNew[0]) * (wereNew[1] - wereNew[0])) / ((xNew[1] - xNew[0]) * (xNew[1] - xNew[0]) + (wereNew[1] - wereNew[0]) * (wereNew[1] - wereNew[0]));

	if(t > 1)
		t = 1.0;
	else
		t = 0.0;
		
	xNew[2] = xNew[0] + t * (xNew[1] - xNew[0]);
	wereNew[2] = wereNew[0] + t * (wereNew[1] - wereNew[0]);
	
	return sqrt((p - xNew[2]) * (p - xNew[2]) + (q - wereNew[2]) * (q - wereNew[2]));  
}