#include <UI/GeometryEditor2D.h>
#include <string>

double geometryEditor2D::getAngle(wxRealPoint aboutPoint, node toPoint)
{
    if(fabs(aboutPoint.y - toPoint.getCenterYCoordinate()) <= 1e-9)
    {
        if(toPoint.getCenterXCoordinate() > aboutPoint.x)
            return 0.0;
        else
            return 180.0;
    }
    else if(fabs(aboutPoint.x - toPoint.getCenterXCoordinate()) <= 1e-9)
    {
        if(toPoint.getCenterYCoordinate() > aboutPoint.y)
            return 90.0;
        else
            return 270.0;
    }
    
    if(toPoint.getCenterXCoordinate() > aboutPoint.x && toPoint.getCenterYCoordinate() > aboutPoint.y)
    {
        return (atan((toPoint.getCenterYCoordinate() - aboutPoint.y) / (toPoint.getCenterXCoordinate() - aboutPoint.x)) * 180.0 / PI);
    }
    else if(toPoint.getCenterXCoordinate() < aboutPoint.x && toPoint.getCenterYCoordinate() > aboutPoint.y)
    {
        return 90.0 + (atan((toPoint.getCenterYCoordinate() - aboutPoint.y) / (aboutPoint.x - toPoint.getCenterXCoordinate())) * 180.0 / PI);
    }
    else if(toPoint.getCenterXCoordinate() < aboutPoint.x && toPoint.getCenterYCoordinate() < aboutPoint.y)
    {
        return 180.0 + (atan((aboutPoint.y - toPoint.getCenterYCoordinate()) / (aboutPoint.x - toPoint.getCenterXCoordinate())) * 180.0 / PI);
    }
    else if(toPoint.getCenterXCoordinate() > aboutPoint.x && toPoint.getCenterYCoordinate() < aboutPoint.y)
    {
        return 270.0 + (atan((aboutPoint.y - toPoint.getCenterYCoordinate()) / (toPoint.getCenterXCoordinate() - aboutPoint.x)) * 180.0 / PI);
    }
    
    return 0.0;
}



double geometryEditor2D::getAngle(wxRealPoint aboutPoint, blockLabel label)
{
    if(fabs(aboutPoint.y - label.getCenterYCoordinate()) <= 1e-9)
    {
        if(label.getCenterXCoordinate() > aboutPoint.x)
            return 0.0;
        else
            return 180.0;
    }
    else if(fabs(aboutPoint.x - label.getCenterXCoordinate()) <= 1e-9)
    {
        if(label.getCenterYCoordinate() > aboutPoint.y)
            return 90.0;
        else
            return 270.0;
    }
    
    if(label.getCenterXCoordinate() > aboutPoint.x && label.getCenterYCoordinate() > aboutPoint.y)
    {
        return (atan((label.getCenterYCoordinate() - aboutPoint.y) / (label.getCenterXCoordinate() - aboutPoint.x)) * 180.0 / PI);
    }
    else if(label.getCenterXCoordinate() < aboutPoint.x && label.getCenterYCoordinate() > aboutPoint.y)
    {
        return 90.0 + (atan((label.getCenterYCoordinate() - aboutPoint.y) / (aboutPoint.x - label.getCenterXCoordinate())) * 180.0 / PI);
    }
    else if(label.getCenterXCoordinate() < aboutPoint.x && label.getCenterYCoordinate() < aboutPoint.y)
    {
        return 180.0 + (atan((aboutPoint.y - label.getCenterYCoordinate()) / (aboutPoint.x - label.getCenterXCoordinate())) * 180.0 / PI);
    }
    else if(label.getCenterXCoordinate() > aboutPoint.x && label.getCenterYCoordinate() < aboutPoint.y)
    {
        return 270.0 + (atan((aboutPoint.y - label.getCenterYCoordinate()) / (label.getCenterXCoordinate() - aboutPoint.x)) * 180.0 / PI);
    }
    
    return 0.0;
}



bool geometryEditor2D::addNode(double xPoint, double yPoint, double distanceNode)// Could distance be the 1/mag which is the zoom factor
{
    /* This function was ported from the BOOL CFemmeDoc::AddNode(double x, double y, double d) located in FemmeDoc.cpp */
	node newNode;
    
    /* This section will make sure that two nodes are not drawn on top of each other */
	for(plf::colony<node>::iterator nodeIterator = _nodeList.begin(); nodeIterator != _nodeList.end(); ++nodeIterator)
	{
		if(nodeIterator->getDistance(xPoint, yPoint) < distanceNode)// This will compare against 1/mag where mag is the scaling function for zooming. However, it is currently being hardcoded to 0.01
        {
            /*
             * Bug Fix:
             * There is a case where if the user tries to select a node after a node failed to be placed, the program would crash
             * That is because the function, addDragNode, would insert a node into the colony for dragging. The iterator of the added node would then be saved
             * to the last node added variable.
             * However, on the up button release, the program would try to earse this node at the iterator.
             * But, if the node failed to be created, then the iterator is now pointing to nothing.
             * SO, when the program first checks to see if the node is in dragging mode (since it is pointing to a 
             * random block of data, it is anyone's guess as to what the value is. Most of the time, the boolean is true)
             * The program then attempts to erase the node but this crashs the program since the iterator is pointing to some random data.
             * The fix is that when the node fails to be created, set the last node added variable equal to the beginning list
             */
            _lastNodeAdded = _nodeList.begin();
            return false;
        }
	
	}
    
    /* This section will make sure that a node is not drawn on top of a block label */
	for(plf::colony<blockLabel>::iterator blockIterator = _blockLabelList.begin(); blockIterator != _blockLabelList.end(); ++blockIterator)
	{
		if(blockIterator->getDistance(xPoint, yPoint) < distanceNode)
		{
            _lastNodeAdded = _nodeList.begin();
            return false;
        }
	}
    
    newNode.setCenter(xPoint, yPoint);
	_lastNodeAdded = _nodeList.insert(newNode);
    
    /* If the node is in between a line, then break the line into 2 lines */
	for(plf::colony<edgeLineShape>::iterator lineIterator = _lineList.begin(); lineIterator != _lineList.end(); ++lineIterator)
	{
        edgeLineShape testLine = *lineIterator;
        node testFirstNode = *(testLine.getFirstNode());
		if(fabs(calculateShortestDistance(newNode, testLine)) < distanceNode)
		{
            /* Ok so if the node is on the line (determined by the calculateShortestDistance function) a new line will be created (This will be called line 1)
             * Line1 will be set equal to the original line (line0).
             * For the sake of explanation, the left most node will be considered as node 1 and the right most node will be considered node 2.
             * So, node 2 of line1 will then be switched to the newly created node and the first node of line0 will be set to the new node 
             * also. This effectively breaks the line into 2 shorter lines
             */ 
            edgeLineShape edgeLine = *lineIterator;
            lineIterator->setSecondNode(*_lastNodeAdded);// This will set the recently created node to be the second node of the shortend line
			
            edgeLine.setFirstNode(*_lastNodeAdded);// This will set the recently created node to be the first node of the new line
			_lastLineAdded = _lineList.insert(edgeLine);// Add the new line to the array
            break;
		}
	} 
    
    /* If the node is in between an arc, then break the arc into 2 */
	for(plf::colony<arcShape>::iterator arcIterator = _arcList.begin(); arcIterator != _arcList.end(); ++arcIterator)
	{
        Vector nodeVector;
        nodeVector.Set(xPoint, yPoint);
        /* Pretty much, this portion of the code is doing the exact same thing as the code above but instead of straight lines, we are working with arcs */
        double dis = fabs(shortestDistanceFromArc(nodeVector, *arcIterator));
		if(dis < distanceNode) // this needs t be looked into more
		{
            Vector firstNode, secondNode, thirdNode, center;
            arcShape arcSegment = *arcIterator;
            double radius;
            
            firstNode.Set(arcIterator->getFirstNode()->getCenterXCoordinate(), arcIterator->getFirstNode()->getCenterYCoordinate());
			secondNode.Set(arcIterator->getSecondNode()->getCenterXCoordinate(), arcIterator->getSecondNode()->getCenterYCoordinate());
			thirdNode.Set(xPoint, yPoint);
			
            center.Set(arcIterator->getCenterXCoordinate(), arcIterator->getCenterYCoordinate());
            radius = arcIterator->getRadius();
			
            arcIterator->setSecondNode(*_lastNodeAdded);
            
            double angle = Varg((thirdNode - center) / (firstNode - center)) * (180.0 / PI);
			arcIterator->setArcAngle(angle);
            arcIterator->calculate();
			
            arcSegment.setFirstNode(*_lastNodeAdded);
            angle = Varg((secondNode - center) / (thirdNode - center)) * (180.0 / PI);
			arcSegment.setArcAngle(angle);
            arcSegment.setNumSegments(20);
			arcSegment.calculate();
            
            _lastArcAdded = _arcList.insert(arcSegment);
            break;
		}
	}
    
    return true;
}



bool geometryEditor2D::addBlockLabel(double xPoint, double yPoint, double tolerance)
{
    /* This code was adapted from the FEMM project. THe code came from FemmeDoc.cpp line 576 */
    blockLabel newLabel;
    
    // Make sure that teh block labe is not placed ontop of an existing block label
    for(plf::colony<blockLabel>::iterator blockIterator = _blockLabelList.begin(); blockIterator != _blockLabelList.end(); ++blockIterator)
    {
        if(blockIterator->getDistance(xPoint, yPoint) < tolerance)
        {
            _lastBlockLabelAdded = _blockLabelList.begin();
            return false;
        } 
    }
    
    // MAke sure that the block label is not placed on top of an existing node
    for(plf::colony<node>::iterator nodeIterator = _nodeList.begin(); nodeIterator != _nodeList.end(); ++nodeIterator)
	{
        // The program FEMM would start the zoom factor at 100. We are starting at 1. The process by which FEMM creates the nodes is very good. Therefor, we multiply our results by 100
		if(nodeIterator->getDistance(xPoint, yPoint) < tolerance)// This will compare against 1/mag where mag is the scaling function for zooming. However, it is currently being hardcoded to 0.01
		{
            _lastBlockLabelAdded = _blockLabelList.begin();
            return false;
        } 
	}
    
    // Make sure that the block label is not placed ontop of a line
    for(plf::colony<edgeLineShape>::iterator lineIterator = _lineList.begin(); lineIterator != _lineList.end(); ++lineIterator)
	{
		if(fabs(calculateShortestDistance(newLabel, *lineIterator)) < tolerance)
        {
            _lastBlockLabelAdded = _blockLabelList.begin();
            return false;
        } 
    }
            
    /* Later, add in check to make sure that a block node will not be placed on top of a arc */
    newLabel.setCenterXCoordinate(xPoint);
    newLabel.setCenterYCoordiante(yPoint);
   
    _lastBlockLabelAdded = _blockLabelList.insert(newLabel);

  //  _blockLabelNameArray.addString(newLabel.getProperty()->getMaterialName());
 //   _blockLabelNameArray.addString(wxT("Test"));
    return true;
}



bool geometryEditor2D::addLine(node *firstNode, node *secondNode, double tolerance)
{
    /* This code was adapted from the FEMM project. See line 263 in FemmeDoc.cpp */
    edgeLineShape newLine;
    double tempTolerance;
    node *tempNodeOne;
    node *tempNodeTwo;

    
    if(firstNode != nullptr && secondNode != nullptr)
    {
        tempNodeOne = firstNode;
        tempNodeTwo = secondNode;
    }
    else if(_nodeInterator1 != nullptr && _nodeInterator2 != nullptr)
    {
        tempNodeOne = _nodeInterator1;
        tempNodeTwo = _nodeInterator2;
    }
    else
    {
        resetIndexs();
        return false;
    }
    
	if(*tempNodeOne == *tempNodeTwo)
    {
        resetIndexs();
		return false;
    }
        
	
/* Check to see if the line has already been created */	

	for(plf::colony<edgeLineShape>::iterator lineIterator = _lineList.begin(); lineIterator != _lineList.end(); ++lineIterator)
	{
		if((*lineIterator->getFirstNode() == *tempNodeOne && *lineIterator->getSecondNode() == *tempNodeTwo) || (*lineIterator->getFirstNode() == *tempNodeTwo && *lineIterator->getSecondNode() == *tempNodeOne))
        {
            resetIndexs();
            return false;
        }
	}
    
    newLine.setFirstNode(*tempNodeOne);
    newLine.setSecondNode(*tempNodeTwo);
    
    if(tolerance == 0)
    {
        if(_nodeList.size() < 2)
            tempTolerance = 1.0e-08;
        else
        {
            Vector tempVecOne, tempVecTwo;
            tempVecOne.Set(_nodeList.begin()->getCenterXCoordinate(), _nodeList.begin()->getCenterYCoordinate());
            tempVecTwo = tempVecOne;
            for(plf::colony<node>::iterator nodeIterator = _nodeList.begin(); nodeIterator != _nodeList.end(); ++nodeIterator)
            {
                if(nodeIterator->getCenterXCoordinate() < tempVecOne.getXComponent())
                    tempVecOne.Set(nodeIterator->getCenterXCoordinate(), tempVecOne.getYComponent());
                    
                if(nodeIterator->getCenterXCoordinate() > tempVecTwo.getXComponent())
                    tempVecTwo.Set(nodeIterator->getCenterXCoordinate(), tempVecTwo.getYComponent());
                
                if(nodeIterator->getCenterYCoordinate() < tempVecOne.getYComponent())
                    tempVecOne.Set(tempVecOne.getXComponent(), nodeIterator->getCenterYCoordinate());
                    
                if(nodeIterator->getCenterYCoordinate() > tempVecTwo.getYComponent())
                    tempVecTwo.Set(tempVecTwo.getXComponent(), nodeIterator->getCenterYCoordinate());
            }
            
            tempTolerance = Vabs(tempVecTwo - tempVecOne) * 1.0e-06;
        }
    }
    else
        tempTolerance = tolerance;
    
    /* This section will check to see if there are any intersections with other segments. If so, create a node at the intersection */
    for(plf::colony<edgeLineShape>::iterator lineIterator = _lineList.begin(); lineIterator != _lineList.end(); ++lineIterator)
    {
        double tempX, tempY;
        if(getIntersection(newLine, *lineIterator, tempX, tempY))
            addNode(tempX, tempY, tempTolerance);
    }
    
    /* This section will check to see if there are any intersections with arcs. If so, create a node at the intersection */
    for(plf::colony<arcShape>::iterator arcIterator = _arcList.begin(); arcIterator != _arcList.end(); ++arcIterator)
    {
        Vector newNodesPoints[2];
        int j = getLineToArcIntersection(newLine, *arcIterator, newNodesPoints);
        if(j > 0)
        {
            for(int k = 0; k < j; k++)
            {
                addNode(newNodesPoints[k].getXComponent(), newNodesPoints[k].getYComponent(), tempTolerance);
            }
        }
    }
    
    /* If things do not work out correctly with adding nodes to the intersection,
     * we can create a list of nodes that need to be added within the function. 
     * Then calculate what the distance tolerance should be and call addNode function
     * with the tolerance value as the tolerance between points. That can be done here.
     */ 

    _lastLineAdded = _lineList.insert(newLine);// Add the line to the list
    
    double shortDistance, dmin;
    Vector node0Vec, node1Vec, nodeiVec;
    
    if(tolerance == 0)
    {
        node0Vec.Set(tempNodeOne->getCenterXCoordinate(), tempNodeOne->getCenterYCoordinate());
        node1Vec.Set(tempNodeTwo->getCenterXCoordinate(), tempNodeTwo->getCenterYCoordinate());
        
        dmin = Vabs(node1Vec - node0Vec) * 1.0e-05;
    }
    else
        dmin = tolerance;
    
    for(plf::colony<node>::iterator nodeIterator = _nodeList.begin(); nodeIterator != _nodeList.end(); ++nodeIterator)
    {
        if((*nodeIterator != *tempNodeOne) && (*nodeIterator != *tempNodeTwo))
        {
            nodeiVec.Set(nodeIterator->getCenterXCoordinate(), nodeIterator->getCenterYCoordinate());
            shortDistance = calculateShortestDistance(*nodeIterator, newLine);
            if((Vabs(nodeiVec - node0Vec) < dmin) || (Vabs(nodeiVec - node1Vec) < dmin))
                shortDistance = 2.0 * dmin;
            if(shortDistance < dmin)
            {
                _lineList.erase(_lastLineAdded);
                addLine(tempNodeOne, *nodeIterator, dmin);
                addLine(*nodeIterator, tempNodeTwo, dmin);
                nodeIterator = _nodeList.back();
            }
        }
    }
    resetIndexs();
    return true;
}


bool geometryEditor2D::addArc(arcShape &arcSeg, double tolerance, bool nodesAreSelected)
{
        // This function was obtained from CbeladrawDoc::AddArcSegment
	edgeLineShape segment;
	arcShape newArc;
	Vector intersectingNodes[2];
	Vector centerPoint;
//    node *tempNodeOne;
//    node *tempNodeTwo;
	double distanceTolerance, radius, minDistance, shortDistanceFromArc;
    
    if((_nodeInterator1 == nullptr || _nodeInterator2 == nullptr) && nodesAreSelected)
    {
        resetIndexs();
        return false;
    }

    if(nodesAreSelected && (*_nodeInterator1 == *_nodeInterator2))
    {
        resetIndexs();
        return false;
    }
    else if(!nodesAreSelected && (arcSeg.getFirstNode() == arcSeg.getSecondNode()))
    {
        resetIndexs();
        return false;
    }
    
    if(arcSeg.getArcAngle() < 1.0)
    {
        // I mean, you might as well add in a line
       return addLine(nullptr, nullptr, tolerance); 
    }
        
    if(nodesAreSelected)
    {
        arcSeg.setFirstNode(*_nodeInterator1);
        arcSeg.setSecondNode(*_nodeInterator2);
        arcSeg.calculate();
    }
		
	for(plf::colony<arcShape>::iterator arcIterator = _arcList.begin(); arcIterator != _arcList.end(); ++arcIterator)
	{
		if((arcIterator->getFirstNode() == arcSeg.getFirstNode()) && (arcIterator->getSecondNode() == arcSeg.getSecondNode()) && (fabs(arcIterator->getArcAngle() - arcSeg.getArcAngle()) < 1.0e-02))
        {
            resetIndexs();
            return false;
        }
	}
	
	if(tolerance == 0)
	{
		if(_nodeList.size() < 2)
			distanceTolerance = 1.0e-08;
		else
		{
			Vector vec1, vec2;
			vec1.Set(_nodeList.begin()->getCenterXCoordinate(), _nodeList.begin()->getCenterYCoordinate());
			vec2 = vec1;
			for(plf::colony<node>::iterator nodeIterator = _nodeList.begin(); nodeIterator != _nodeList.end(); ++nodeIterator)
			{
				if(nodeIterator->getCenterXCoordinate() < vec1.getXComponent())
					vec1.Set(nodeIterator->getCenterXCoordinate(), vec1.getYComponent());
				
				if(nodeIterator->getCenterXCoordinate() > vec2.getXComponent())
					vec2.Set(nodeIterator->getCenterXCoordinate(), vec2.getYComponent());
				
				if(nodeIterator->getCenterYCoordinate() < vec1.getYComponent())
					vec1.Set(vec1.getXComponent(), nodeIterator->getCenterYCoordinate());
					
				if(nodeIterator->getCenterYCoordinate() > vec2.getYComponent())
					vec2.Set(vec2.getXComponent(), nodeIterator->getCenterYCoordinate());
			}
			
			distanceTolerance = Vabs(vec1 - vec2) * 1.0e-06;
		}
	}
	else
		distanceTolerance = tolerance;
	
	/* This section will check for any intesections with lines and arcs and if so, place a node there */
	for(plf::colony<edgeLineShape>::iterator lineIterator = _lineList.begin(); lineIterator != _lineList.end(); ++lineIterator)// This will check how many times the existing arc intercests the proposed arc.
	{
		int j = getLineToArcIntersection(*lineIterator, arcSeg, intersectingNodes); // Place the function for intersecting here This will be for an arc intersecting a line
		
		if(j > 0)
		{
			for(int k = 0; k < j; k++)
			{
				addNode(intersectingNodes[k].getXComponent(), intersectingNodes[k].getYComponent(), distanceTolerance);
			}
		}
	}
	
	/* This section is for the proposed arc intersecting another arc */
	for(plf::colony<arcShape>::iterator arcIterator = _arcList.begin(); arcIterator != _arcList.end(); ++arcIterator)
	{
        // THis finds the number of points where intercetion occurs.
        // The point values are stored in the variable intersectiongNodes.
		int j = getArcToArcIntersection(*arcIterator, arcSeg,  intersectingNodes); // This will be for an arc intersecting an arc
		
		if(j > 0)
		{
			for(int k = 0; k < j; k++)
			{
				addNode(intersectingNodes[k].getXComponent(), intersectingNodes[k].getYComponent(), distanceTolerance);
			}
		}
	}
	
	_lastArcAdded = _arcList.insert(arcSeg);
	
//	getCircle(arcSeg, centerPoint, radius);
    centerPoint.Set(arcSeg.getCenterXCoordinate(), arcSeg.getCenterYCoordinate());
    radius = arcSeg.getRadius();
	
	if(tolerance == 0)
		minDistance = fabs(radius * PI * arcSeg.getArcAngle() / 180.0) * 1.0e-05;
	else
		minDistance = tolerance;
	
	for(plf::colony<node>::iterator nodeIterator = _nodeList.begin(); nodeIterator != _nodeList.end(); ++nodeIterator)
	{
		if((*nodeIterator != *arcSeg.getFirstNode()) && (*nodeIterator != *arcSeg.getSecondNode()))
		{
			shortDistanceFromArc = shortestDistanceFromArc(Vector(nodeIterator->getCenterXCoordinate(), nodeIterator->getCenterYCoordinate()), *_lastArcAdded);
			if(shortDistanceFromArc < minDistance)
			{
				Vector vec1, vec2, vec3;
				vec1.Set(arcSeg.getFirstNode()->getCenterXCoordinate(), arcSeg.getFirstNode()->getCenterYCoordinate());
				vec2.Set(arcSeg.getSecondNode()->getCenterXCoordinate(), arcSeg.getSecondNode()->getCenterYCoordinate());
				vec3.Set(nodeIterator->getCenterXCoordinate(), nodeIterator->getCenterYCoordinate());
				
				_arcList.erase(_lastArcAdded);
				
				newArc = arcSeg;
				
                newArc.setSecondNode(*nodeIterator);
				newArc.setArcAngle(Varg((vec3 - centerPoint) / (vec1 - centerPoint)) * 180.0 / PI);
				addArc(newArc, minDistance, false);
				
				newArc = arcSeg;
                newArc.setFirstNode(*nodeIterator);
				newArc.setArcAngle(Varg((vec2 - centerPoint) / (vec3 - centerPoint)) * 180.0 / PI);
				addArc(newArc, minDistance, false);
				
                break;
			}
		}
	}
    resetIndexs();
    return true;
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
        
    pNode0.Set(prospectiveLine.getFirstNode()->getCenterXCoordinate(), prospectiveLine.getFirstNode()->getCenterYCoordinate());
    pNode1.Set(prospectiveLine.getSecondNode()->getCenterXCoordinate(), prospectiveLine.getSecondNode()->getCenterYCoordinate());
    iNode0.Set(intersectionLine.getFirstNode()->getCenterXCoordinate(), intersectionLine.getFirstNode()->getCenterYCoordinate());
    iNode1.Set(intersectionLine.getSecondNode()->getCenterXCoordinate(), intersectionLine.getSecondNode()->getCenterYCoordinate());
    
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



double geometryEditor2D::shortestDistanceFromArc(Vector vectorPoint, arcShape &arcSegment)
{
    // This function was adapted from CbeladrawDoc::ShortestDistanceFromArc
    double radius, distance, length, z;
    Vector arcStartNode, arcEndNode, centerVec, tempVec;
    
    arcStartNode.Set(arcSegment.getFirstNode()->getCenterXCoordinate(), arcSegment.getFirstNode()->getCenterYCoordinate());
    arcEndNode.Set(arcSegment.getSecondNode()->getCenterXCoordinate(), arcSegment.getSecondNode()->getCenterYCoordinate());
    
    radius = arcSegment.getRadius();
    centerVec.Set(arcSegment.getCenterXCoordinate(), arcSegment.getCenterYCoordinate());
    
    distance = Vabs(vectorPoint - centerVec);
    
    if(distance == 0)
        return radius;
        
    tempVec = (vectorPoint - centerVec) / distance;
    length = Vabs(vectorPoint - centerVec - radius * tempVec);
    z = Varg(tempVec / (arcStartNode - centerVec)) * 180.0 / PI;
    if((z > 0.0) && (z < arcSegment.getArcAngle()))
        return length;
     
    z = Vabs(vectorPoint - arcStartNode);
    length = Vabs(vectorPoint - arcEndNode);
    
    if(z < length)
        return z;
    
    return length;
}



int geometryEditor2D::getLineToArcIntersection(edgeLineShape &lineSegment, arcShape &arcSegment, Vector *pointVec)
{
    /* Note: this function has not yet been verified to be working. Logical bugs could still exist */
    // This function was ported from CbeladrawDoc::GetLineArcIntersection
    
	Vector lineSegVec1, lineSegVec2, arcSegVec1, arcSegVec2, unitVec1, tempVec2, arcCenterPoint;
	double distance, length, radius, z;
	int intersectionCounter = 0;

    lineSegVec1.Set(lineSegment.getFirstNode()->getCenterXCoordinate(), lineSegment.getFirstNode()->getCenterYCoordinate());
	lineSegVec2.Set(lineSegment.getSecondNode()->getCenterXCoordinate(), lineSegment.getSecondNode()->getCenterYCoordinate());
	
	arcSegVec1.Set(arcSegment.getFirstNode()->getCenterXCoordinate(), arcSegment.getFirstNode()->getCenterYCoordinate());
	arcSegVec2.Set(arcSegment.getSecondNode()->getCenterXCoordinate(), arcSegment.getSecondNode()->getCenterYCoordinate());
	
	distance = Vabs(arcSegVec2 - arcSegVec1);
	
    radius = arcSegment.getRadius();
    
    arcCenterPoint.Set(arcSegment.getCenterXCoordinate(), arcSegment.getCenterYCoordinate());
    
    // Determining the distance between the line and the circle's center
	distance = Vabs(lineSegVec2 - lineSegVec1);
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
		if((radius > 0) && (radius < distance) && (z > 0.0) && (z < (arcSegment.getArcAngle() * PI / 180.0)))
			intersectionCounter++;
		return intersectionCounter;
	}
	
    // First intersection
	pointVec[intersectionCounter] = lineSegVec1 + (tempVec2.getXComponent() + length) * unitVec1;
	radius = ((pointVec[intersectionCounter] - lineSegVec1) / unitVec1).getXComponent();
	z = Varg((pointVec[intersectionCounter] - arcCenterPoint) / (arcSegVec1 - arcCenterPoint));
	if((radius > 0) && (radius < distance) && (z > 0.0) && (z < (arcSegment.getArcAngle() * PI / 180.0)))
    {
		intersectionCounter++;
    }
    
    // Second intersection
	pointVec[intersectionCounter] = lineSegVec1 + (tempVec2.getXComponent() - length) * unitVec1;
	radius = ((pointVec[intersectionCounter] - lineSegVec1) / unitVec1).getXComponent();
	z = Varg((pointVec[intersectionCounter] - arcCenterPoint) / (arcSegVec1 - arcCenterPoint));
	if((radius > 0) && (radius < distance) && (z > 0.0) && (z < (arcSegment.getArcAngle() * PI / 180.0)))
    {
		intersectionCounter++;
    }
		
	return intersectionCounter;
}



int geometryEditor2D::getArcToArcIntersection(arcShape& arcSegment1, arcShape &arcSegment2, Vector *point)
{
    // This function was ported from CbeladrawDoc::GetArcArcIntersection (Please note that the variable names may not be accurate to what they actually are. This is because there is a lack of documentation in FEMM)
    Vector arcCenter1, arcCenter2, arc1StartNode, arc2StartNode, tempVec;
    double distance, arcRadius1, arcRadius2, length, center, arc1Length, arc2Length, z0, z1;
    int counter = 0;
    
    arc1StartNode.Set(arcSegment1.getFirstNode()->getCenterXCoordinate(), arcSegment1.getFirstNode()->getCenterYCoordinate());
    arc2StartNode.Set(arcSegment2.getFirstNode()->getCenterXCoordinate(), arcSegment2.getFirstNode()->getCenterYCoordinate());
    
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
    
    arc1Length = arcSegment1.getArcAngle() * PI / 180.0;
    arc2Length = arcSegment2.getArcAngle() * PI / 180.0;
    
    point[counter] = arcCenter1 + (center * distance / 2.0 + J * length) * tempVec;
    
    z0 = Varg((point[counter] - arcCenter1) / (arc1StartNode - arcCenter1));
    z1 = Varg((point[counter] - arcCenter2) / (arc2StartNode - arcCenter2));
    
    if((z0 > 0.0) && (z0 < arc1Length) && (z1 > 0.0) && (z1 < arc2Length))
        counter++;
        
    if(fabs(distance - arcRadius1 + arcRadius2) / (arcRadius1 + arcRadius2) < 1.0e-05)
    {
        point[counter] = arcCenter1 + center * distance * (tempVec / 2.0);
        counter++;
        return counter;
    }
    
    point[counter] = arcCenter1 + (center * distance / 2.0 - J * length) * tempVec;
    z0 = Varg((point[counter] - arcCenter1) / (arc1StartNode - arcCenter1));
    z1 = Varg((point[counter] - arcCenter2) / (arc2StartNode - arcCenter2));
    
    if((z0 > 0.0) && (z0 < arc1Length) && (z1 > 0.0) && (z1 < arc2Length))
        counter++;
        
    return counter;    
}


// Consider removing the last two arguments
// Maybe the last parameter can be an edgeLineShape
double geometryEditor2D::calculateShortestDistance(node selectedNode, edgeLineShape segment)
{
    // This function was adapted from the CbeladrawDoc::ShortestDistance function
    double t, x[3], y[3];

    x[0] = segment.getFirstNode()->getCenterXCoordinate();
    y[0] = segment.getFirstNode()->getCenterYCoordinate();
	
    x[1] = segment.getSecondNode()->getCenterXCoordinate();
    y[1] = segment.getSecondNode()->getCenterYCoordinate();
	
	t = ((selectedNode.getCenterXCoordinate() - x[0]) * (x[1] - x[0]) + (selectedNode.getCenterYCoordinate() - y[0]) * (y[1] - y[0])) / ((x[1] - x[0]) * (x[1] - x[0]) + (y[1] - y[0]) * (y[1] - y[0]));
      
	if(t > 1)
		t = 1.0;
	else if(t < 0.0)
		t = 0.0;
		
	x[2] = x[0] + t * (x[1] - x[0]);
	y[2] = y[0] + t * (y[1] - y[0]);
    
	return sqrt((selectedNode.getCenterXCoordinate() - x[2]) * (selectedNode.getCenterXCoordinate() - x[2]) + (selectedNode.getCenterYCoordinate() - y[2]) * (selectedNode.getCenterYCoordinate() - y[2]));  
}



double geometryEditor2D::calculateShortestDistance(blockLabel selectedNode, edgeLineShape segment)
{
    double t, x[3], y[3];

    x[0] = segment.getFirstNode()->getCenterXCoordinate();
    y[0] = segment.getFirstNode()->getCenterYCoordinate();
	
    x[1] = segment.getSecondNode()->getCenterXCoordinate();
    y[1] = segment.getSecondNode()->getCenterYCoordinate();
	
	t = ((selectedNode.getCenterXCoordinate() - x[0]) * (x[1] - x[0]) + (selectedNode.getCenterYCoordinate() - y[0]) * (y[1] - y[0])) / ((x[1] - x[0]) * (x[1] - x[0]) + (y[1] - y[0]) * (y[1] - y[0]));
      
	if(t > 1)
		t = 1.0;
	else if(t < 0.0)
		t = 0.0;
		
	x[2] = x[0] + t * (x[1] - x[0]);
	y[2] = y[0] + t * (y[1] - y[0]);
    
	return sqrt((selectedNode.getCenterXCoordinate() - x[2]) * (selectedNode.getCenterXCoordinate() - x[2]) + (selectedNode.getCenterYCoordinate() - y[2]) * (selectedNode.getCenterYCoordinate() - y[2]));   
}



double geometryEditor2D::calculateShortestDistance(wxRealPoint selectedPoint, edgeLineShape segment)
{
    double t, x[3], y[3];

    x[0] = segment.getFirstNode()->getCenterXCoordinate();
    y[0] = segment.getFirstNode()->getCenterYCoordinate();
	
    x[1] = segment.getSecondNode()->getCenterXCoordinate();
    y[1] = segment.getSecondNode()->getCenterYCoordinate();
	
	t = ((selectedPoint.x - x[0]) * (x[1] - x[0]) + (selectedPoint.y - y[0]) * (y[1] - y[0])) / ((x[1] - x[0]) * (x[1] - x[0]) + (y[1] - y[0]) * (y[1] - y[0]));
      
	if(t > 1)
		t = 1.0;
	else if(t < 0.0)
		t = 0.0;
		
	x[2] = x[0] + t * (x[1] - x[0]);
	y[2] = y[0] + t * (y[1] - y[0]);
    
	return sqrt((selectedPoint.x - x[2]) * (selectedPoint.x - x[2]) + (selectedPoint.y - y[2]) * (selectedPoint.y - y[2]));    
}