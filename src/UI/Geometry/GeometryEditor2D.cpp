#include <UI/GeometryEditor2D.h>

void geometryEditor2D::addNode(double xPoint, double yPoint)// Could distance be the 1/mag which is the zoom factor
{
    /* This function was ported from the BOOL CFemmeDoc::AddNode(double x, double y, double d) located in FemmeDoc.cpp */
	node newNode;
    
    /* This section will make sure that two nodes are not drawn on top of each other */
	for(int i = 0; i < _nodeList.size(); i++)
	{
        // The program FEMM would start the zoom factor at 100. We are starting at 1. The process by which FEMM creates the nodes is very good. Therefor, we multiply our results by 100
		if(_nodeList.at(i).getDistance(xPoint, yPoint) < 1 / (*_zoomFactorPointer * 100))// This will compare against 1/mag where mag is the scaling function for zooming. However, it is currently being hardcoded to 0.01
			return;
	}
    
    /* This section will make sure that a node is not drawn ontop of a block label */
	for(int i = 0; i < _blockLabelList.size(); i++)
	{
		if(_blockLabelList[i].getDistance(xPoint, yPoint) < 1 / (*_zoomFactorPointer * 100))
			return;
	}
    
    newNode.setCenter(xPoint, yPoint);
	_nodeList.push_back(newNode);
    
    /* If the node is in between a line, then break the line into 2 lines */
	for(int i = 0; i < _lineList.size(); i++)
	{
		if(fabs(calculateShortestDistance(xPoint, yPoint, i)) < 1 / (*_zoomFactorPointer * 100))
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
	for(int i = 0; i < _arcList.size(); i++)
	{
        /* Pretty much, this portion of the code is doing the exact same thing as the code above but instead of straight lines, we are working with arcs */
		if(fabs(-5) < 1 / (*_zoomFactorPointer * 100)) // this needs t be looked into more
		{
            Vector firstNode, secondNode, thirdNode, center;
            arcShape arcSegment = _arcList.at(i);
            
            firstNode.Set(_arcList.at(i).getFirstNode().getCenterXCoordinate(), _arcList.at(i).getFirstNode().getCenterYCoordinate());
			secondNode.Set(_arcList.at(i).getSecondNode().getCenterXCoordinate(), _arcList.at(i).getSecondNode().getCenterYCoordinate());
			thirdNode.Set(xPoint, yPoint);
			
			//getCircle{arcList[i], center, R);// No idea what this is.... yet
			
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
    for(int i = 0; _blockLabelList.size(); i++)
    {
        if(_blockLabelList.at(i).getDistance(xPoint, yPoint) < 1 / (*_zoomFactorPointer * 100))
            return;
    }
    
    // MAke sure that the block label is not placed on top of an existing node
    for(int i = 0; i < _nodeList.size(); i++)
	{
        // The program FEMM would start the zoom factor at 100. We are starting at 1. The process by which FEMM creates the nodes is very good. Therefor, we multiply our results by 100
		if(_nodeList.at(i).getDistance(xPoint, yPoint) < 1 / (*_zoomFactorPointer * 100))// This will compare against 1/mag where mag is the scaling function for zooming. However, it is currently being hardcoded to 0.01
			return;
	}
    
    // Make sure that the block label is not placed ontop of a line
    for(int i = 0; i < _lineList.size(); i++)
	{
		if(fabs(calculateShortestDistance(xPoint, yPoint, i)) < 1 / (*_zoomFactorPointer * 100))
            return;
    }
            
    /* Later, add in check to make sure that a block node will not be placed on top of a arc */
    newLabel.setCenterXCoordinate(xPoint);
    newLabel.setCenterYCoordiante(yPoint);
    _blockLabelList.push_back(newLabel);
}



void geometryEditor2D::addLine(int node0, int node1)
{
    /* This code was adapted from the FEMM project. See line 263 in FemmeDoc.cpp */
    edgeLineShape newLine;
    
	if(node0 == node1)
		return;
	
/* Check to see if the line has already been created */	
	for(int i = 0; i < _lineList.size(); i++)
	{
		if((_lineList.at(i).getFirstNode() == _nodeList.at(node0) && _lineList.at(i).getSecondNode() == _nodeList.at(node1)) || (_lineList.at(i).getFirstNode() == _nodeList.at(node1) && _lineList.at(i).getSecondNode() == _nodeList.at(node0)))
			return;
	}
    
    newLine.setFirstNode(_nodeList.at(node0));
    newLine.setSecondNode(_nodeList.at(node1));
    
    /* This section will check to see if there are any intersections with other segments. If so, create a node at the intersection */
    for(int i = 0; i < _lineList.size(); i++)
    {
        /* Left off here */
   //     if(true)
   //         addNode(nodePointX, nodePointY, 0);
    }
    
    /* This section will check to see if there are any intersections with arcs. If so, create a node at the intersection */
    for(int i = 0; i < _arcList.size(); i++)
    {
        
    }
    
    _lineList.push_back(newLine);// Add the line to the list
}



void geometryEditor2D::addArc(arcShape &arcSeg, double tolerance)
{
    
    // Hey this is where we add in that dialog
    
        // This function was obtained from CbeladrawDoc::AddArcSegment
	edgeLineShape segment;
	arcShape newArc;
	Vector intersectingNodes[2];
	Vector centerPoint;
	double dist, radius, minDistance, shortDistanceFromArc;
	
	if(arcSeg.getFirstNodeIndex() == arcSeg.getSecondNodeIndex())
		return;
		
	for(int i = 0; i < _arcList.size(); i++)
	{
		if((_arcList[i].getFirstNodeIndex() == arcSeg.getFirstNodeIndex()) && (_arcList[i].getSecondNodeIndex() == arcSeg.getSecondNodeIndex()) && (fabs(_arcList[i].getArcAngle() - arcSeg.getArcAngle()) < 1.0e-02))
			return;
	}
	
	if(tolerance == 0)
	{
		if(_nodeList.size() < 2)
			dist = 1.0e-08;
		else
		{
			Vector vec1, vec2;
			vec1.Set(_nodeList[0].getCenterXCoordinate(), _nodeList[0].getCenterYCoordinate());
			vec2 = vec1;
			for(int i = 0; i < _nodeList.size(); i++)
			{
				if(_nodeList[i].getCenterXCoordinate() < vec1.getXComponent())
					vec1.Set(_nodeList[i].getCenterXCoordinate(), vec1.getYComponent());
				
				if(_nodeList[i].getCenterXCoordinate() > vec2.getXComponent())
					vec2.Set(_nodeList[i].getCenterXCoordinate(), vec2.getYComponent());
				
				if(_nodeList[i].getCenterYCoordinate() < vec1.getYComponent())
					vec1.Set(vec1.getXComponent(), _nodeList[i].getCenterYCoordinate());
					
				if(_nodeList[i].getCenterYCoordinate() > vec2.getYComponent())
					vec2.Set(vec2.getXComponent(), _nodeList[i].getCenterYCoordinate());
			}
			
			dist = Vabs(vec1 - vec2) * 1.0e-06;
		}
	}
	else
		dist = tolerance;
	
	/* This section will check for any intesections with lines and arcs and if so, place a node there */
	for(int i = 0; i < _lineList.size(); i++)// This will check how many times the existing arc intercests the proposed arc.
	{
		int j = getLineToArcIntersection(_lineList[i], arcSeg, intersectingNodes); // Place the function for intersecting here This will be for an arc intersecting a line
		
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
	
	getCircle(arcSeg, centerPoint, radius);
	
	if(tolerance == 0)
		minDistance = fabs(radius * PI * arcSeg.getArcAngle() / 180.0) * 1.0e-05;
	else
		minDistance = tolerance;
	
	int loopCounter = 0;
	
	for(int loopCounter = 0; loopCounter < _nodeList.size(); loopCounter++)
	{
		if((loopCounter != arcSeg.getFirstNodeIndex()) && (loopCounter != arcSeg.getSecondNodeIndex()))
		{
			shortDistanceFromArc = shortestDistanceFromArc(Vector(_nodeList[loopCounter].getCenterXCoordinate(), _nodeList[loopCounter].getCenterYCoordinate()), _arcList[_arcList.size() - 1]);
			if(shortDistanceFromArc < minDistance)
			{
				Vector vec1, vec2, vec3;
				vec1.Set(_nodeList[arcSeg.getFirstNodeIndex()].getCenterXCoordinate(), _nodeList[arcSeg.getFirstNodeIndex()].getCenterYCoordinate());
				vec2.Set(_nodeList[arcSeg.getSecondNodeIndex()].getCenterXCoordinate(), _nodeList[arcSeg.getSecondNodeIndex()].getCenterYCoordinate());
				vec3.Set(_nodeList[loopCounter].getCenterXCoordinate(), _nodeList[loopCounter].getCenterYCoordinate());
				
				_arcList.pop_back();
				
				newArc = arcSeg;
				
				newArc.setSecondNodeIndex(loopCounter);
				newArc.setArcAngle(Varg((vec3 - centerPoint) / (vec1 - centerPoint)) * 180.0 / PI);
				addArc(newArc, minDistance);
				
				newArc = arcSeg;
				newArc.setFirstNodeIndex(loopCounter);
				newArc.setArcAngle(Varg((vec2 - centerPoint) / (vec3 - centerPoint)) * 180.0 / PI);
				addArc(newArc, minDistance);
				
				loopCounter = _nodeList.size();
			}
		}
	}
}



bool geometryEditor2D::getIntersection(edgeLineShape prospectiveLine, edgeLineShape intersectionLine, double &intersectionXPoint, double &intersectionYPoint)
{
    
}



void geometryEditor2D::getCircle(arcShape &arc, Vector &center, double &radius)
{
    Vector firstNode, secondNode, unitVector;
	double distance;
	
	firstNode.Set(_nodeList[arc.getFirstNodeIndex()].getCenterXCoordinate(), _nodeList[arc.getFirstNodeIndex()].getCenterYCoordinate());
	secondNode.Set(_nodeList[arc.getSecondNodeIndex()].getCenterXCoordinate(), _nodeList[arc.getSecondNodeIndex()].getCenterYCoordinate());
	
	distance = Vabs(firstNode - secondNode);
	
	unitVector = (firstNode - secondNode) / distance;
	
	radius = distance / (2.0 * sin(arc.getArcAngle() * PI / 360.0));
	
	center = firstNode + (distance / 2.0 + J * sqrt(pow(radius, 2) - pow(distance, 2) / 4.0)) * unitVector;
}



double geometryEditor2D::shortestDistanceFromArc(Vector point, arcShape &arcSegment)
{
    /*
    double radius, distance, length, z;
	Vector vec1, vec2, centerVec, tempVec;
	
	vec1.Set(nodeList[arcSegment.getFirstNodeIndex()].getCenterXCoordinate(), _nodeList[arcSegment.getFirstNodeIndex()].getCenterYCoordinate());
	vec2.Set(nodeList[arcSegment.getSecondNodeIndex()].getCenterXCoordinate(), _nodeList[arcSegment.getSecondNodeIndex()].getCenterYCoordinate());
	getCircle(arcSegment, centerVec, radius);
	
	distance = Vabs(pointVec - centerVec);
	
	if(distance == 0)
		return radius;
	
	tempVec = (pointVec - centerVec) / distance;
	
	length = Vabs(pointVec - centerVec - radius * tempVec);
	
	z = Varg(tempVec / (vec1 - centerVec)) * 180 / PI;
	
	if((z > 0) && (z < arcSegment.getArcAngle()))
		return length;
		
	z = Vabs(pointVec - vec1);
	length = Vabs(pointVec - vec1);
	
	if(z < 1)
		return z;
	else
		return length;
         * */
}



int geometryEditor2D::getLineToArcIntersection(edgeLineShape &lineSegment, arcShape &arcSegment, Vector *pointVec)
{
    /* Note: this function has not yet been verified to be working. Logical bugs could still exist */
    // This function was ported from Cbeladraw::GetLineArcIntersection
	Vector lineSegVec1, lineSegVec2, arcSegVec1, arcSegVec2, tempVec1, tempVec2, tempVec3;
	double distance, length, radius, z;
	int intersectionCounter = 0;

	lineSegVec1.Set(_nodeList[lineSegment.getFirstNodeIndex()].getCenterXCoordinate(), _nodeList[lineSegment.getFirstNodeIndex()].getCenterYCoordinate());
	lineSegVec2.Set(_nodeList[lineSegment.getSecondNodeIndex()].getCenterXCoordinate(), _nodeList[lineSegment.getSecondNodeIndex()].getCenterYCoordinate());
	
	arcSegVec1.Set(_nodeList[arcSegment.getFirstNodeIndex()].getCenterXCoordinate(), _nodeList[arcSegment.getFirstNodeIndex()].getCenterYCoordinate());
	arcSegVec2.Set(_nodeList[arcSegment.getSecondNodeIndex()].getCenterXCoordinate(), _nodeList[arcSegment.getSecondNodeIndex()].getCenterYCoordinate());
	
	distance = Vabs(arcSegVec2 - arcSegVec1);
	
	tempVec1 = (arcSegVec2 - arcSegVec1) / distance;
	radius = distance / (2.0 * sin(arcSegment.getArcAngle() * PI / 360.));
	
	tempVec3 = arcSegVec1 + (distance / 2.0 + J * sqrt(pow(radius, 2) - pow(distance, 2) / 4.0)) * tempVec1;
	
	distance = Vabs(lineSegVec2 - lineSegVec2);
	tempVec1 = (lineSegVec2 - lineSegVec2) / distance;
	tempVec2 = (tempVec3 - lineSegVec1) / distance;
	tempVec2 = (tempVec3 - lineSegVec1) / tempVec1;
	
	if(fabs(tempVec2.getYComponent()) > radius)
		return 0;
		
	length = sqrt(pow(radius, 2) - pow(tempVec2.getYComponent(), 2));
	
	if((length / radius) < 1.0e-05)
	{
		pointVec[intersectionCounter] = lineSegVec1 + tempVec2.getXComponent() * tempVec1;
		radius = ((pointVec[intersectionCounter] - lineSegVec1) / tempVec1).getXComponent();
		z = Varg((pointVec[intersectionCounter] - tempVec3) / (arcSegVec1 - tempVec3));
		if((radius > 0) && (radius < distance) && (z > 0.0) && (z < arcSegment.getArcAngle() * PI / 180))
			intersectionCounter++;
		return intersectionCounter;
	}
	
	pointVec[intersectionCounter] = lineSegVec1 + (tempVec2.getXComponent() + length) * tempVec1;
	radius = ((pointVec[intersectionCounter] - lineSegVec1) / tempVec1).getXComponent();
	z = Varg((pointVec[intersectionCounter] - tempVec3) / (arcSegVec1 - tempVec3));
	if((radius > 0) && (radius < distance) && (z > 0.0) && (z < arcSegment.getArcAngle() * PI / 180))
		intersectionCounter++;
		
	pointVec[intersectionCounter] = lineSegVec1 + (tempVec2.getXComponent() + length) * tempVec1;
	radius = ((pointVec[intersectionCounter] - lineSegVec1) / tempVec1).getXComponent();
	z = Varg((pointVec[intersectionCounter] - tempVec3) / (arcSegVec1 - tempVec3));
	if((radius > 0) && (radius < distance) && (z > 0.0) && (z < arcSegment.getArcAngle() * PI / 180))
		intersectionCounter++;
		
	return intersectionCounter;
}



int geometryEditor2D::getArcToArcIntersection(arcShape& arcSegment1, arcShape &arcSegment2, Vector *point)
{
    // This function was ported from CbeladrawDoc::GetArcArcIntersection (Please note that the variable names may not be accurate to what they actually are. This is because there is a lack of documentation in FEMM)
    Vector arcCenter1, arcCenter2, arc1StartNode, arc2StartNode, tempVec;
    double distance, arcRadius1, arcRadius2, length, center, arc1Length, arc2Length, z0, z1;
    int counter;
    
    arc1StartNode.Set(_nodeList[arcSegment1.getFirstNodeIndex()].getCenterXCoordinate(), _arcList[arcSegment1.getFirstNodeIndex()].getCenterYCoordinate());
    arc2StartNode.Set(_nodeList[arcSegment2.getFirstNodeIndex()].getCenterXCoordinate(), _arcList[arcSegment2.getFirstNodeIndex()].getCenterYCoordinate());
    
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
double geometryEditor2D::calculateShortestDistance(double p, double q, int segmentIndex)
{
    // I have no idea what this function does
    double t, xNew[3], wereNew[3];
	
    xNew[0] = _nodeList[_lineList[segmentIndex].getFirstNodeIndex()].getCenterXCoordinate();
	wereNew[0] = _nodeList[_lineList[segmentIndex].getFirstNodeIndex()].getCenterYCoordinate();
	
	xNew[1] = _nodeList[_lineList[segmentIndex].getSecondNodeIndex()].getCenterXCoordinate();
	wereNew[1] = _nodeList[_lineList[segmentIndex].getSecondNodeIndex()].getCenterYCoordinate();
	
	t = ((p - xNew[0]) * (xNew[1] - xNew[0]) + (q - wereNew[0]) * (wereNew[1] - wereNew[0])) / ((xNew[1] - xNew[0]) * (xNew[1] - xNew[0]) + (wereNew[1] - wereNew[0]) * (wereNew[1] - wereNew[0]));

	if(t > 1)
		t = 1.0;
	else
		t = 0.0;
		
	xNew[2] = xNew[0] + t * (xNew[1] - xNew[0]);
	wereNew[2] = wereNew[0] + t * (wereNew[1] - wereNew[0]);
	
	return sqrt((p - xNew[2]) * (p - xNew[2]) + (q - wereNew[2]) * (q - wereNew[2]));  
}