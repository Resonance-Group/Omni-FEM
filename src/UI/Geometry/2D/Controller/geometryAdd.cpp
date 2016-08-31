#include <UI/openGLGeometry.h>


void geometryEditorCanvas::addNode(double xPoint, double yPoint, double distance)
{
	edgeLineShape *edgeLine;
	edgeLine = new edgeLineShape();
	arcShape *arcSegment;
	arcSegment = new arcShape();
	
	Vector firstNode, secondNode, thirdNode, c;
	int nodeListSize = nodeList.size();
	node newNode;
    
	/* This section will make sure that two nodes are not drawn on top of each other */
	for(int i = 0; i < nodeListSize; i++)
	{
		if(nodeList[i].getDistance(xPoint, yPoint) < 0.0)// This will compare against 1/mag where mag is the scaling function for zooming. However, it is currently being hardcoded to 0.01
			return;
	}
	
	/* This section will make sure that a node is not drawn ontop of a block label */
	for(int i = 0; i < blockLabelList.size(); i++)
	{
		if(blockLabelList[i].getDistance(xPoint, yPoint) < 0.01)
			return;
	}
	
    newNode.setCenter(xPoint, yPoint);
    
	nodeList.push_back(newNode);
    int testSize = nodeList.size();
	nodeList[testSize - 1].setNodeIndex(testSize - 1);
	
	/* If the node is in between a line, then break the line into 2 lines */
	for(int i = 0; i < lineList.size(); i++)
	{
		if(geoController.calculateShortestDistance(xPoint, yPoint, i, nodeList, lineList) < distance)
		{
			edgeLine = &(lineList[i]);
			lineList[i].setSecondNodeIndex((int)(nodeList.size() - 1)); // This will set the recently created node to be the second node of the shortend line
			edgeLine->setFirstNodeIndex((int)(nodeList.size() - 1)); // This will set the recently created node to be the first node of the new line
			lineList.push_back(*(edgeLine));// Add the new line to the array
		}
	} 
	
	/* If the node is in between an arc, then break the arc into 2 */
	for(int i = 0; i < arcList.size(); i++)
	{
		if(fabs(-5) < distance)
		{
			firstNode.Set(nodeList[arcList[i].getFirstNodeIndex()].getCenterXCoordinate(), nodeList[arcList[i].getFirstNodeIndex()].getCenterYCoordinate());
			secondNode.Set(nodeList[arcList[i].getSecondNodeIndex()].getCenterXCoordinate(), nodeList[arcList[i].getSecondNodeIndex()].getCenterYCoordinate());
			thirdNode.Set(xPoint, yPoint);
			
			//getCircle{arcList[i], c, R);// No idea what this is.... yet
			
			arcSegment = &arcList[i];
			
			arcList[i].setSecondNodeIndex((int)nodeList.size() - 1);
			arcList[i].setArcAngle((((firstNode - c) / (secondNode - c)) * 180.0 / PI).Arg());
			
			arcSegment->setFirstNodeIndex((int)nodeList.size() - 1);
			arcSegment->setArcAngle((((firstNode - c) / (secondNode - c)) * 180.0 / PI).Arg());
			
			arcList.push_back(*arcSegment);
		}
	}
}



void geometryEditorCanvas::getCircle(arcShape &arc, Vector &center, double &radius)
{
	Vector firstNode, secondNode, temp, tempNode;
	double distance;
	
	firstNode.Set(nodeList[arc.getFirstNodeIndex()].getCenterXCoordinate(), nodeList[arc.getFirstNodeIndex()].getCenterYCoordinate());
	secondNode.Set(nodeList[arc.getSecondNodeIndex()].getCenterXCoordinate(), nodeList[arc.getSecondNodeIndex()].getCenterYCoordinate());
	
	
	tempNode = firstNode - secondNode;
	distance = Vabs(tempNode);
	
	temp = (firstNode - secondNode) / distance;
	
	radius = distance / (2.0 * sin(arc.getArcAngle() * PI / 360.0));
	
	center = firstNode + (distance / 2.0 + J * sqrt(pow(radius, 2) - pow(distance, 2) / 4.0)) * temp;
}


void geometryEditorCanvas::addLineSegment(int node0, int node1, edgeLineShape *parseSegment)
{
    double nodePointX, nodePointY;
    edgeLineShape *tempLine = new edgeLineShape;
    
	if(node0 == node1)
		return;
	
/* Check to see if the line has already been created */	
	for(int i = 0; i < lineList.size(); i++)
	{
		if((lineList[i].getFirstNodeIndex() == node0 && lineList[i].getSecondNodeIndex() == node1) || (lineList[i].getFirstNodeIndex() == node0 && lineList[i].getSecondNodeIndex() == node0))
			return;
	}
    
    if(parseSegment != NULL)
        tempLine = parseSegment;
    
    tempLine->setFirstNodeIndex(node0);
    tempLine->setSecondNodeIndex(node1);
    
    /* This section will check to see if there are any intersections with other segments. If so, create a node at the intersection */
    for(int i = 0; i < lineList.size(); i++)
    {
   //     if(true)
   //         addNode(nodePointX, nodePointY, 0);
    }
    
    /* This section will check to see if there are any intersections with arcs. If so, create a node at the intersection */
    for(int i = 0; i < arcList.size(); i++)
    {
        
    }
    
    lineList.push_back(*tempLine);// Add the line to the list
    
}




bool geometryEditorCanvas::getIntersection(int node0, int node1, int lineSegmentIndex, double &intercetionXPoint, double &intercestionYPoint)
{
	Vector p0, p1, q0, q1;
	double error, x, z;
	double test1, test2;
	
	// If the end point already exists, do not create it
	if(node0 == lineList[lineSegmentIndex].getFirstNodeIndex() || node0 == lineList[lineSegmentIndex].getSecondNodeIndex() || node1 == lineList[lineSegmentIndex].getFirstNodeIndex() || node1 == lineList[lineSegmentIndex].getSecondNodeIndex())
	{
		return false;
	}
	
	p0.Set(nodeList[lineList[lineSegmentIndex].getFirstNodeIndex()].getCenterXCoordinate(), nodeList[lineList[lineSegmentIndex].getFirstNodeIndex()].getCenterYCoordinate());
	
	p1.Set(nodeList[lineList[lineSegmentIndex].getSecondNodeIndex()].getCenterXCoordinate(), nodeList[lineList[lineSegmentIndex].getSecondNodeIndex()].getCenterYCoordinate());
	
	q0.Set(nodeList[node0].getCenterXCoordinate(), nodeList[node0].getCenterYCoordinate());
	
	q1.Set(nodeList[node1].getCenterXCoordinate(), nodeList[node1].getCenterYCoordinate());
	
	error = std::min((p1 - p0).Abs(), (q1 - q0).Abs()) * 1.0e-8;
	
	q0 = (q0 - p0) / (p1 - p0);
	q1 = (q1 - p0) / (p1 - p0);
	
	if((q0.getXComponent() <= 0 && q1.getXComponent() <= 0) || (q0.getXComponent() >= 1 && q1.getXComponent() >= 1) || (q0.getYComponent() <= 0 && q1.getYComponent() <= 0) || (q0.getYComponent() >= 0 && q1.getYComponent() >= 0))
		return false;
		
	z = q0.getYComponent() / (q0 - q1).getYComponent();
	
	x = ((1.0 - z) * q0 + z * q1).getXComponent();
	
	if(x < error || (x > (1.0 - error)))
		return false;
	
	test1 = (1.0 - z) * nodeList[node0].getCenterXCoordinate() + z * nodeList[node1].getCenterXCoordinate();
	test2 = (1.0 - z) * nodeList[node0].getCenterYCoordinate() + z * nodeList[node1].getCenterYCoordinate();
	
	p0.Set(test1, test2);
//	p0.Set(5.0, 5.0);
	intercetionXPoint = p0.getXComponent();
	intercestionYPoint = p0.getYComponent();
	
//	intercetionXPoint = 5;
//	intercestionYPoint = 5;
	
	return true;
}



double geometryEditorCanvas::shortestDistanceFromArc(Vector pointVec, arcShape &arcSegment)
{
	double radius, distance, length, z;
	Vector vec1, vec2, centerVec, tempVec;
	
	vec1.Set(nodeList[arcSegment.getFirstNodeIndex()].getCenterXCoordinate(), nodeList[arcSegment.getFirstNodeIndex()].getCenterYCoordinate());
	vec2.Set(nodeList[arcSegment.getSecondNodeIndex()].getCenterXCoordinate(), nodeList[arcSegment.getSecondNodeIndex()].getCenterYCoordinate());
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
}



int geometryEditorCanvas::getLineToArcIntersection(edgeLineShape &lineSegment, arcShape &arcSegment, Vector *pointVec)
{
	/* Note: this function has not yet been verified to be working. Logical bugs could still exist */
	Vector lineSegVec1, lineSegVec2, arcSegVec1, arcSegVec2, tempVec1, tempVec2, tempVec3;
	double distance, length, radius, z;
	int intersectionCounter = 0;

	lineSegVec1.Set(nodeList[lineSegment.getFirstNodeIndex()].getCenterXCoordinate(), nodeList[lineSegment.getFirstNodeIndex()].getCenterYCoordinate());
	lineSegVec2.Set(nodeList[lineSegment.getSecondNodeIndex()].getCenterXCoordinate(), nodeList[lineSegment.getSecondNodeIndex()].getCenterYCoordinate());
	
	arcSegVec1.Set(nodeList[arcSegment.getFirstNodeIndex()].getCenterXCoordinate(), nodeList[arcSegment.getFirstNodeIndex()].getCenterYCoordinate());
	arcSegVec2.Set(nodeList[arcSegment.getSecondNodeIndex()].getCenterXCoordinate(), nodeList[arcSegment.getSecondNodeIndex()].getCenterYCoordinate());
	
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


void geometryEditorCanvas::addArcSegment(arcShape &arcSeg, double tolerance)
{
	edgeLineShape segment;
	arcShape newArc;
	Vector intersectingNodes[2];
	Vector centerPoint;
	double dist, radius, minDistance, shortDistanceFromArc;
	
	if(arcSeg.getFirstNodeIndex() == arcSeg.getSecondNodeIndex())
		return;
		
	for(int i = 0; i < arcList.size(); i++)
	{
		if((arcList[i].getFirstNodeIndex() == arcSeg.getFirstNodeIndex()) && (arcList[i].getSecondNodeIndex() == arcSeg.getSecondNodeIndex()) && (fabs(arcList[i].getArcAngle() - arcSeg.getArcAngle()) < 1.0e-02))
			return;
	}
	
	if(tolerance == 0)
	{
		if(nodeList.size() < 2)
			dist = 1.0e-08;
		else
		{
			Vector vec1, vec2;
			vec1.Set(nodeList[0].getCenterXCoordinate(), nodeList[0].getCenterYCoordinate());
			vec2 = vec1;
			for(int i = 0; i < nodeList.size(); i++)
			{
				if(nodeList[i].getCenterXCoordinate() < vec1.getXComponent())
					vec1.Set(nodeList[i].getCenterXCoordinate(), vec1.getYComponent());
				
				if(nodeList[i].getCenterXCoordinate() > vec2.getXComponent())
					vec2.Set(nodeList[i].getCenterXCoordinate(), vec2.getYComponent());
				
				if(nodeList[i].getCenterYCoordinate() < vec1.getYComponent())
					vec1.Set(vec1.getXComponent(), nodeList[i].getCenterYCoordinate());
					
				if(nodeList[i].getCenterYCoordinate() > vec2.getYComponent())
					vec2.Set(vec2.getXComponent(), nodeList[i].getCenterYCoordinate());
			}
			
			dist = Vabs(vec1 - vec2) * 1.0e-06;
		}
	}
	else
		dist = tolerance;
	
	/* This section will check for any intesections with lines and arcs and if so, place a node there */
	for(int i = 0; i < lineList.size(); i++)// This will check how many times the existing arc intercests the proposed arc.
	{
		int j = 0; // Place the function for intersecting here This will be for an arc intersecting a line
		
		if(j > 0)
		{
			for(int k = 0; k < j; k++)
			{
				addNode(intersectingNodes[k].getXComponent(), intersectingNodes[k].getYComponent(), dist);
			}
		}
	}
	
	/* This section is for the proposed arc intersecting another arc */
	for(int i = 0; i < arcList.size(); i++)
	{
		int j = 0; // This will be for an arc intersecting an arc
		
		if(j > 0)
		{
			for(int k = 0; k < j; k++)
			{
				addNode(intersectingNodes[k].getXComponent(), intersectingNodes[k].getYComponent(), dist);
			}
		}
	}
	
	arcList.push_back(arcSeg);
	
	getCircle(arcSeg, centerPoint, radius);
	
	if(tolerance == 0)
		minDistance = fabs(radius * PI * arcSeg.getArcAngle() / 180.0) * 1.0e-05;
	else
		minDistance = tolerance;
	
	int loopCounter = 0;
	
	for(int loopCounter = 0; loopCounter < nodeList.size(); loopCounter++)
	{
		if((loopCounter != arcSeg.getFirstNodeIndex()) && (loopCounter != arcSeg.getSecondNodeIndex()))
		{
			shortDistanceFromArc = shortestDistanceFromArc(Vector(nodeList[loopCounter].getCenterXCoordinate(), nodeList[loopCounter].getCenterYCoordinate()), arcList[arcList.size() - 1]);
			if(shortDistanceFromArc < minDistance)
			{
				Vector vec1, vec2, vec3;
				vec1.Set(nodeList[arcSeg.getFirstNodeIndex()].getCenterXCoordinate(), nodeList[arcSeg.getFirstNodeIndex()].getCenterYCoordinate());
				vec2.Set(nodeList[arcSeg.getSecondNodeIndex()].getCenterXCoordinate(), nodeList[arcSeg.getSecondNodeIndex()].getCenterYCoordinate());
				vec3.Set(nodeList[loopCounter].getCenterXCoordinate(), nodeList[loopCounter].getCenterYCoordinate());
				
				arcList.pop_back();
				
				newArc = arcSeg;
				
				newArc.setSecondNodeIndex(loopCounter);
				newArc.setArcAngle(Varg((vec3 - centerPoint) / (vec1 - centerPoint)) * 180.0 / PI);
				addArcSegment(newArc, minDistance);
				
				newArc = arcSeg;
				newArc.setFirstNodeIndex(loopCounter);
				newArc.setArcAngle(Varg((vec2 - centerPoint) / (vec3 - centerPoint)) * 180.0 / PI);
				addArcSegment(newArc, minDistance);
				
				loopCounter = nodeList.size();
			}
		}
	}
}