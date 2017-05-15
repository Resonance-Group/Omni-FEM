#include <UI/GeometryEditor2D.h>
#include <string>


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
		if((fabs(calculateShortestDistance(newNode, *lineIterator)) < distanceNode) && (newNode != *lineIterator->getFirstNode() && newNode != *lineIterator->getSecondNode()))
		{
            /* If the node is on the line (determined by the calculateShortestDistance function) a new line will be created (This will be called line 1)
             * Line1 will be set equal to the original line (line0).
             * For the sake of explanation, the left most node will be considered as node 1 and the right most node will be considered node 2.
             * So, node 2 of line1 will then be switched to the newly created node and the first node of line0 will be set to the new node 
             * also. This effectively breaks the line into 2 shorter lines
             */ 
            edgeLineShape edgeLine = *lineIterator;
            lineIterator->setSecondNode(*_lastNodeAdded);// This will set the recently created node to be the second node of the shortend line
			
            edgeLine.setFirstNode(*_lastNodeAdded);// This will set the recently created node to be the first node of the new line
			_lastLineAdded = _lineList.insert(edgeLine);// Add the new line to the array
            continue;
		}
	} 
    
    /* If the node is in between an arc, then break the arc into 2 */
	for(plf::colony<arcShape>::iterator arcIterator = _arcList.begin(); arcIterator != _arcList.end(); ++arcIterator)
	{
        Vector nodeVector;
        nodeVector.Set(xPoint, yPoint);
        /* Pretty much, this portion of the code is doing the exact same thing as the code above but instead of straight lines, we are working with arcs */
		if((fabs(shortestDistanceFromArc(nodeVector, *arcIterator)) < distanceNode) && (newNode != *arcIterator->getFirstNode() && newNode != *arcIterator->getSecondNode())) // this needs t be looked into more
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
    Vector blockVector = Vector(xPoint, yPoint);
    
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
    
    // Make sure that the label is not placed ontop of an arc. If it is, don't bother creating the label
    for(plf::colony<arcShape>::iterator arcIterator = _arcList.begin(); arcIterator != _arcList.end(); ++arcIterator)
    {
        if(fabs(shortestDistanceFromArc(blockVector, *arcIterator)) < tolerance)
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
        if(getIntersection(newLine, *lineIterator, tempX, tempY) && !lineIterator->getSegmentProperty()->getHiddenState())
            addNode(tempX, tempY, tempTolerance);
    }
    
    /* This section will check to see if there are any intersections with arcs. If so, create a node at the intersection */
    for(plf::colony<arcShape>::iterator arcIterator = _arcList.begin(); arcIterator != _arcList.end(); ++arcIterator)
    {
        Vector newNodesPoints[2];
        int j = getLineToArcIntersection(newLine, *arcIterator, newNodesPoints);
        if(j > 0 && !arcIterator->getSegmentProperty()->getHiddenState())
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
                addLine(tempNodeOne, &(*nodeIterator), dmin);
                addLine(&(*nodeIterator), tempNodeTwo, dmin);
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
	arcShape newArc;
	Vector intersectingNodes[2];
	Vector centerPoint;
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
		
		if(j > 0 && !lineIterator->getSegmentProperty()->getHiddenState())
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
		
		if(j > 0 && !arcIterator->getSegmentProperty()->getHiddenState())
		{
			for(int k = 0; k < j; k++)
			{
				addNode(intersectingNodes[k].getXComponent(), intersectingNodes[k].getYComponent(), distanceTolerance);
			}
		}
	}
	
	_lastArcAdded = _arcList.insert(arcSeg);
	
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



bool geometryEditor2D::checkIntersections(EditGeometry editedGeometry, double tolerance)
{
    bool labelsViolated = false;
    
    if(editedGeometry == EditGeometry::EDIT_NODES || editedGeometry == EditGeometry::EDIT_ALL)
    {
        for(plf::colony<node>::iterator nodeIterator1 = _nodeList.begin(); nodeIterator1 != _nodeList.end(); ++nodeIterator1)
        {
            bool nodeIsConfigured = false;
            plf::colony<node>::iterator tempNodeIterator = nodeIterator1;
            /* Iterate through all of the nodes to see if a node is on top of another node and if so, move all of the lines/arcs to one of the nodes 8*/
            for(plf::colony<node>::iterator nodeIterator2 = ++tempNodeIterator; nodeIterator2 != _nodeList.end(); ++nodeIterator2)
            {
                if(nodeIterator2 == _nodeList.end())
                    break;
                   
                /*  TODO: During mesh testing, determine if this if statment should be the distance between the two nodes.
                    THis will determine if there is a min. distance required before we get convergence issues
                     */ 
                if(*nodeIterator1 == *nodeIterator2)
                {
                    for(plf::colony<edgeLineShape>::iterator lineIterator = _lineList.begin(); lineIterator != _lineList.end(); ++lineIterator)
                    {
                        if(*lineIterator->getFirstNode() == *nodeIterator2)
                            lineIterator->setFirstNode(*nodeIterator1);
                        else if(*lineIterator->getSecondNode() == *nodeIterator2)
                            lineIterator->setSecondNode(*nodeIterator1);
                    }
                    
                    for(plf::colony<arcShape>::iterator arcIterator = _arcList.begin(); arcIterator != _arcList.end(); ++arcIterator)
                    {
                        if(*arcIterator->getFirstNode() == *nodeIterator2)
                            arcIterator->setFirstNode(*nodeIterator1);
                        else if(*arcIterator->getSecondNode() == *nodeIterator2)
                            arcIterator->setSecondNode(*nodeIterator1);
                    }
                    
                    if(*_lastNodeAdded == *nodeIterator2)
                        _lastNodeAdded = _nodeList.begin();
                        
                    _nodeList.erase(nodeIterator2);
                    nodeIsConfigured = true;// A node being ontop of another node will only happen once and it will not be ontop of a line or an arc
                    break;
                }
            }
            
            // If the node is not ontop of another node, then check to see if the node is on top of a line or arc. If so, break the line/arc into 2
            if(!nodeIsConfigured)
            {
                for(plf::colony<edgeLineShape>::iterator lineIterator = _lineList.begin(); lineIterator != _lineList.end(); ++lineIterator)
                {
                    if((fabs(calculateShortestDistance(*nodeIterator1, *lineIterator)) < tolerance) && (*nodeIterator1 != *lineIterator->getFirstNode() && *nodeIterator1 != *lineIterator->getSecondNode()) && !lineIterator->getSegmentProperty()->getHiddenState())
                    {
                        /* If the node is on the line (determined by the calculateShortestDistance function) a new line will be created (This will be called line 1)
                         * Line1 will be set equal to the original line (line0).
                         * For the sake of explanation, the left most node will be considered as node 1 and the right most node will be considered node 2.
                         * So, node 2 of line1 will then be switched to the newly created node and the first node of line0 will be set to the new node 
                         * also. This effectively breaks the line into 2 shorter lines
                         */ 
                        edgeLineShape edgeLine = *lineIterator;
                        lineIterator->setSecondNode(*nodeIterator1);
                        
                        edgeLine.setFirstNode(*nodeIterator1);
                        _lastLineAdded = _lineList.insert(edgeLine);// Add the new line to the array
                        nodeIsConfigured = true;
                        break;
                    }
                }
                
                for(plf::colony<arcShape>::iterator arcIterator = _arcList.begin(); arcIterator != _arcList.end(); ++arcIterator)
                {
                    Vector nodeVector;
                    nodeVector.Set(nodeIterator1->getCenterXCoordinate(), nodeIterator1->getCenterYCoordinate());
                    /* Pretty much, this portion of the code is doing the exact same thing as the code above but instead of straight lines, we are working with arcs */
                    double dis = fabs(shortestDistanceFromArc(nodeVector, *arcIterator));
                    
                    if(dis < tolerance && !arcIterator->getSegmentProperty()->getHiddenState() && (*nodeIterator1 != *arcIterator->getFirstNode() && *nodeIterator1 != *arcIterator->getSecondNode())) // this needs t be looked into more
                    {
                        Vector firstNode, secondNode, thirdNode, center;
                        arcShape arcSegment = *arcIterator;
                        double radius;
                        
                        firstNode.Set(arcIterator->getFirstNode()->getCenterXCoordinate(), arcIterator->getFirstNode()->getCenterYCoordinate());
                        secondNode.Set(arcIterator->getSecondNode()->getCenterXCoordinate(), arcIterator->getSecondNode()->getCenterYCoordinate());
                        thirdNode.Set(nodeIterator1->getCenterXCoordinate(), nodeIterator1->getCenterYCoordinate());
                        
                        center.Set(arcIterator->getCenterXCoordinate(), arcIterator->getCenterYCoordinate());
                        radius = arcIterator->getRadius();
                        
                        arcIterator->setSecondNode(*nodeIterator1);
                        
                        double angle = Varg((thirdNode - center) / (firstNode - center)) * (180.0 / PI);
                        arcIterator->setArcAngle(angle);
                        arcIterator->calculate();
                        
                        arcSegment.setFirstNode(*nodeIterator1);
                        angle = Varg((secondNode - center) / (thirdNode - center)) * (180.0 / PI);
                        arcSegment.setArcAngle(angle);
                        arcSegment.setNumSegments(20);
                        arcSegment.calculate();
                        
                        _lastArcAdded = _arcList.insert(arcSegment);
                        break;
                    }
                }
            }
        }
    }
    
    if(editedGeometry == EditGeometry::EDIT_LINES || editedGeometry == EditGeometry::EDIT_ALL)
    {
        for(plf::colony<edgeLineShape>::iterator lineIterator = _lineList.begin(); lineIterator != _lineList.end(); ++lineIterator)
        {
            // If the line is to be ignored by the postprocessor, go ahead and ignore it in any intercetion calculation
            if(lineIterator->getSegmentProperty()->getHiddenState())
                continue;
                
            plf::colony<edgeLineShape>::iterator tempLineIterator = lineIterator;
            
            //TODO: Check if there is ever a case where one line iterator can intesect a node/line/arc
            if(editedGeometry == EditGeometry::EDIT_LINES)
            {
                /* First we check if there is any intercetion with just nodes */
                for(plf::colony<node>::iterator nodeIterator = _nodeList.begin(); nodeIterator != _nodeList.end(); ++nodeIterator)
                {
                    if(fabs(calculateShortestDistance(*nodeIterator, *lineIterator)) < tolerance && (*nodeIterator != *lineIterator->getFirstNode() && *nodeIterator != *lineIterator->getSecondNode()))
                    {
                        /* If the node is on the line (determined by the calculateShortestDistance function) a new line will be created (This will be called line 1)
                         * Line1 will be set equal to the original line (line0).
                         * For the sake of explanation, the left most node will be considered as node 1 and the right most node will be considered node 2.
                         * So, node 2 of line1 will then be switched to the newly created node and the first node of line0 will be set to the new node 
                         * also. This effectively breaks the line into 2 shorter lines
                         */ 
                        edgeLineShape edgeLine = *lineIterator;
                        lineIterator->setSecondNode(*nodeIterator);
                        
                        edgeLine.setFirstNode(*nodeIterator);
                        _lastLineAdded = _lineList.insert(edgeLine);// Add the new line to the array
                    }
                }
            }
            
            // Next, we need to check if there are any intercetions with the lines. That is, if a line is placed on top of a line or if a line crosses another line
            for(plf::colony<edgeLineShape>::iterator lineIterator2 = ++tempLineIterator; lineIterator2 != _lineList.end();)
            {
                double tempX, tempY;
                
                if(lineIterator2 == _lineList.end())
                    break;
                    
                // If a line is placed on top of another line, then we will have to transfer any lines/arcs connecting to the nodes of the line to the other line 
                if(((*lineIterator->getFirstNode() == *lineIterator2->getFirstNode() && *lineIterator->getSecondNode() == *lineIterator2->getSecondNode()) || (*lineIterator->getFirstNode() == *lineIterator2->getSecondNode() && *lineIterator->getSecondNode() == *lineIterator2->getFirstNode())) && (lineIterator != lineIterator2))
                {
                    for(plf::colony<edgeLineShape>::iterator lineIterator3 = _lineList.begin(); lineIterator3 != _lineList.end(); ++lineIterator3)
                    {
                        if(*lineIterator3->getFirstNode() == *lineIterator->getFirstNode())
                            lineIterator3->setFirstNode(*lineIterator->getFirstNode());
                        else if(*lineIterator3->getFirstNode() == *lineIterator->getSecondNode())
                            lineIterator3->setSecondNode(*lineIterator->getSecondNode());
                    }
                    
                    for(plf::colony<arcShape>::iterator arcIterator = _arcList.begin(); arcIterator != _arcList.end(); ++arcIterator)
                    {
                        if(*arcIterator->getFirstNode() == *lineIterator->getFirstNode())
                            arcIterator->setFirstNode(*lineIterator->getFirstNode());
                        else if(*arcIterator->getFirstNode() == *lineIterator->getSecondNode())
                            arcIterator->setSecondNode(*lineIterator->getSecondNode());
                    }
                    
                    // As the last item, we need to delete the two nodes and the line from the list
                    for(plf::colony<node>::iterator nodeIterator = _nodeList.begin(); nodeIterator != _nodeList.end();)
                    {
                        if(*nodeIterator == *lineIterator2->getFirstNode() || *nodeIterator == *lineIterator2->getSecondNode())
                            _nodeList.erase(nodeIterator++);
                        else
                             nodeIterator++;   
                    }
                    
                    _lineList.erase(lineIterator2++);
                }    
                else if(getIntersection(*lineIterator2, *lineIterator, tempX, tempY) && !lineIterator2->getSegmentProperty()->getHiddenState())
                {
                    // If the line intersectes with another line, then go ahead and place a node at the intercetion point
                    addNode(tempX, tempY, tolerance);
                    lineIterator2++;
                }
                else
                    lineIterator2++;
            }
            
            for(plf::colony<arcShape>::iterator arcIterator = _arcList.begin(); arcIterator != _arcList.end(); ++arcIterator)
            {
                Vector newNodesPoints[2];
                int j = getLineToArcIntersection(*lineIterator, *arcIterator, newNodesPoints);
                if(j > 0 && !arcIterator->getSegmentProperty()->getHiddenState())
                {
                    for(int k = 0; k < j; k++)
                    {
                        addNode(newNodesPoints[k].getXComponent(), newNodesPoints[k].getYComponent(), tolerance);
                    }
                }
            }
        }
    }
    
    if(editedGeometry == EditGeometry::EDIT_ARCS || editedGeometry == EditGeometry::EDIT_ALL)
    {
        for(plf::colony<arcShape>::iterator arcIterator = _arcList.begin(); arcIterator != _arcList.end(); ++arcIterator)
        {
            if(editedGeometry == EditGeometry::EDIT_ARCS)
            {
                for(plf::colony<node>::iterator nodeIterator = _nodeList.begin(); nodeIterator != _nodeList.end(); ++nodeIterator)
                {
                    Vector nodeVector;
                    nodeVector.Set(nodeIterator->getCenterXCoordinate(), nodeIterator->getCenterYCoordinate());
                    /* Pretty much, this portion of the code is doing the exact same thing as the code above but instead of straight lines, we are working with arcs */
                    double dis = fabs(shortestDistanceFromArc(nodeVector, *arcIterator));
                    
                    if(dis < tolerance && !arcIterator->getSegmentProperty()->getHiddenState() && (*nodeIterator != *arcIterator->getFirstNode() && *nodeIterator != *arcIterator->getSecondNode())) // this needs t be looked into more
                    {
                        Vector firstNode, secondNode, thirdNode, center;
                        arcShape arcSegment = *arcIterator;
                        double radius;
                        
                        firstNode.Set(arcIterator->getFirstNode()->getCenterXCoordinate(), arcIterator->getFirstNode()->getCenterYCoordinate());
                        secondNode.Set(arcIterator->getSecondNode()->getCenterXCoordinate(), arcIterator->getSecondNode()->getCenterYCoordinate());
                        thirdNode.Set(nodeIterator->getCenterXCoordinate(), nodeIterator->getCenterYCoordinate());
                        
                        center.Set(arcIterator->getCenterXCoordinate(), arcIterator->getCenterYCoordinate());
                        radius = arcIterator->getRadius();
                        
                        arcIterator->setSecondNode(*nodeIterator);
                        
                        double angle = Varg((thirdNode - center) / (firstNode - center)) * (180.0 / PI);
                        arcIterator->setArcAngle(angle);
                        arcIterator->calculate();
                        
                        arcSegment.setFirstNode(*nodeIterator);
                        angle = Varg((secondNode - center) / (thirdNode - center)) * (180.0 / PI);
                        arcSegment.setArcAngle(angle);
                        arcSegment.setNumSegments(20);
                        arcSegment.calculate();
                        
                        _lastArcAdded = _arcList.insert(arcSegment);
                        break;
                    }
                }
                
                for(plf::colony<edgeLineShape>::iterator lineIterator = _lineList.begin(); lineIterator != _lineList.end(); ++lineIterator)
                {
                    Vector newNodesPoints[2];
                    int j = getLineToArcIntersection(*lineIterator, *arcIterator, newNodesPoints);
                    if(j > 0 && !lineIterator->getSegmentProperty()->getHiddenState())
                    {
                        for(int k = 0; k < j; k++)
                        {
                            addNode(newNodesPoints[k].getXComponent(), newNodesPoints[k].getYComponent(), tolerance);
                        }
                    }
                }
            }
            plf::colony<arcShape>::iterator tempArcIterator = arcIterator;
            for(plf::colony<arcShape>::iterator arcIterator2 = ++tempArcIterator; arcIterator2 != _arcList.end(); ++arcIterator2)
            {
                Vector intersectingNodes[2];
                int j = getArcToArcIntersection(*arcIterator, *arcIterator2,  intersectingNodes); // This will be for an arc intersecting an arc
		
                if(j > 0 && !arcIterator2->getSegmentProperty()->getHiddenState())
                {
                    for(int k = 0; k < j; k++)
                    {
                        addNode(intersectingNodes[k].getXComponent(), intersectingNodes[k].getYComponent(), tolerance);
                    }
                }
            }
        }
    }
    
    // Here we will not delete the block labels but rather we willl flag them so that the user can deal with them apprioately
    if(editedGeometry == EditGeometry::EDIT_LABELS || editedGeometry == EditGeometry::EDIT_ALL)
    {
        
        for(plf::colony<blockLabel>::iterator blockIterator = _blockLabelList.begin(); blockIterator != _blockLabelList.end(); ++blockIterator)
        {
            for(plf::colony<arcShape>::iterator arcIterator = _arcList.begin(); arcIterator != _arcList.end(); ++arcIterator)
            {
                Vector blockLabelVector = Vector(blockIterator->getCenterXCoordinate(), blockIterator->getCenterYCoordinate());
                if(shortestDistanceFromArc(blockLabelVector, *arcIterator) < tolerance)
                {
                    labelsViolated = true;
                    blockIterator->setSelectState(true);// Flag the block label if it violates tolerances so that the user can deal with it.
                }
                    
            }
            
            for(plf::colony<edgeLineShape>::iterator lineIterator = _lineList.begin(); lineIterator != _lineList.end(); ++lineIterator)
            {
                if(calculateShortestDistance(*blockIterator, *lineIterator) < tolerance)
                {
                    labelsViolated = true;
                    blockIterator->setSelectState(true);
                }
                    
            }
            
            for(plf::colony<node>::iterator nodeIterator = _nodeList.begin(); nodeIterator != _nodeList.end(); ++nodeIterator)
            {
                if(nodeIterator->getDistance(blockIterator->getCenterXCoordinate(), blockIterator->getCenterYCoordinate()) < tolerance)
                {
                    labelsViolated = true;
                    blockIterator->setSelectState(true);
                }
                    
            }
            
            plf::colony<blockLabel>::iterator tempIterator = blockIterator;
            for(plf::colony<blockLabel>::iterator blockIterator2 = ++tempIterator; blockIterator2 != _blockLabelList.end(); ++blockIterator2)
            {
                if(blockIterator2->getDistance(blockIterator->getCenterXCoordinate(), blockIterator->getCenterYCoordinate()) < tolerance)
                {
                    labelsViolated = true;
                    blockIterator->setSelectState(true);
                }
                    
            }
        }
    }
    
    return labelsViolated;
}




bool geometryEditor2D::createFillet(double radius)
{
    bool willReturn = false;
    // This code is being adapted from CcdrawDoc::CreateRadius located in femm/CDRAWDOC.CPP
    if(radius <= 0)
        return false;
        
    for(plf::colony<node>::iterator nodeIterator = _nodeList.begin(); nodeIterator != _nodeList.end();)
    {
        if(nodeIterator->getIsSelectedState())
        {
            nodeIterator->setSelectState(false);
            unsigned int numberOfLines = 0;
            unsigned int numberOfArcs = 0;
            
            // Tally up the number of lines connected to the node
            for(plf::colony<edgeLineShape>::iterator lineIterator = _lineList.begin(); lineIterator != _lineList.end(); ++lineIterator)
            {
                if((*lineIterator->getFirstNode() == *nodeIterator || *lineIterator->getSecondNode() == *nodeIterator) && !lineIterator->getSegmentProperty()->getHiddenState())
                    numberOfLines++;
            }
            
            // Tally up the number of arcs connected to the node
            for(plf::colony<arcShape>::iterator arcIterator = _arcList.begin(); arcIterator != _arcList.end(); ++arcIterator)
            {
                if((*arcIterator->getFirstNode() == *nodeIterator || *arcIterator->getSecondNode() == *nodeIterator) && !arcIterator->getSegmentProperty()->getHiddenState())
                    numberOfArcs++;
            }
            
            if((numberOfLines + numberOfArcs > 2) || (numberOfLines == 1 && numberOfArcs == 0) || (numberOfLines == 0 && numberOfArcs == 1) || (numberOfLines + numberOfArcs) == 0)
            {
                ++nodeIterator;
                continue;// Move to the next node if there are too many lines/arcs connecting to the node (Or not enough of either type)
            } 
                
            switch(numberOfLines - numberOfArcs)
            {
                case 0:// This is the case for if we have one arc and one line at the node
                {
                    plf::colony<arcShape>::iterator connectedArc;
                    plf::colony<edgeLineShape>::iterator connectedLine;
                    arcShape addedArc;
                    Vector centerPoint, lineEndpointOne, lineEndpointTwo, unitVectorAlongLine, q, p[4], v[8], I1[8], I2[8];
                    double arcRadius, R[4], angle;
                    int j = 0;
                    int m = 0;
                    int k = 0;
                    
                    // First we need to grab some information about the arc that the node is connected to
                    for(plf::colony<arcShape>::iterator arcIterator = _arcList.begin(); arcIterator != _arcList.end(); ++arcIterator)
                    {
                        if((*arcIterator->getFirstNode() == *nodeIterator || *arcIterator->getSecondNode() == *nodeIterator) && !arcIterator->getSegmentProperty()->getHiddenState())
                        {
                            addedArc.setSegmentProperty(*arcIterator->getSegmentProperty());
                            addedArc.setNumSegments(arcIterator->getnumSegments());
                            centerPoint.Set(arcIterator->getCenterXCoordinate(), arcIterator->getCenterYCoordinate());
                            arcRadius = arcIterator->getRadius();
                            connectedArc = arcIterator;
                        }
                    }
                    
                    // Next, we need to grab some information about the line that the node is connected to
                    for(plf::colony<edgeLineShape>::iterator lineIterator = _lineList.begin(); lineIterator != _lineList.end(); ++lineIterator)
                    {
                        if((*lineIterator->getFirstNode() == *nodeIterator || *lineIterator->getSecondNode() == *nodeIterator) && !lineIterator->getSegmentProperty()->getHiddenState())
                        {
                            lineEndpointOne.Set(lineIterator->getFirstNode()->getCenterXCoordinate(), lineIterator->getFirstNode()->getCenterYCoordinate());
                            lineEndpointTwo.Set(lineIterator->getSecondNode()->getCenterXCoordinate(), lineIterator->getSecondNode()->getCenterYCoordinate());
                            connectedLine = lineIterator;
                        }
                    }
                    
                    unitVectorAlongLine = (lineEndpointTwo - lineEndpointOne) / Vabs(lineEndpointTwo - lineEndpointOne); // Determine the unit vector along the line
                    
                    q = lineEndpointOne + unitVectorAlongLine * ((centerPoint - lineEndpointOne) / unitVectorAlongLine).getXComponent();// q is the closest point on the line to the center of the circle
                    
                    unitVectorAlongLine = J * unitVectorAlongLine;
                    
                    p[0] = q + radius * unitVectorAlongLine;
                    p[1] = q - radius * unitVectorAlongLine;
                    p[2] = q + radius * unitVectorAlongLine;
                    p[3] = q - radius * unitVectorAlongLine;
                    
                    R[0] = arcRadius + radius;
                    R[1] = arcRadius + radius;
                    R[2] = arcRadius - radius;
                    R[3] = arcRadius - radius;
                    
                    for(j = 0, k = 0; k < 4; k++)
                    {
                        double b = pow(R[k], 2) - pow(Vabs(p[k] - centerPoint), 2);
                        if(b >= 0)
                        {
                            b = sqrt(b);
                            v[j++] = p[k] + J * b * (p[k] - centerPoint) / Vabs(p[k] - centerPoint);
                            v[j++] = p[k] - J * b * (p[k] - centerPoint) / Vabs(p[k] - centerPoint);
                        }
                    }
                    
                    unitVectorAlongLine = (lineEndpointTwo - lineEndpointOne) / Vabs(lineEndpointTwo - lineEndpointOne);
                    
                    for(m = 0, k = 0; k < j; k++)
                    {
                        I1[m] = lineEndpointOne + unitVectorAlongLine * ((v[k] - lineEndpointOne) / unitVectorAlongLine).getXComponent();
                        I2[m] = centerPoint + arcRadius * (v[k] - centerPoint) / Vabs(v[k] - centerPoint);
                        v[m] = v[k];
     
                        if(shortestDistanceFromArc(I2[m], *connectedArc) < (radius / 10000.0) && calculateShortestDistance(wxRealPoint(I1[m].getXComponent(), I1[m].getYComponent()), *connectedLine) < (radius / 10000.0) && Vabs(I1[m] - I2[m]) > (radius / 10000.0))
                        {
                            m++;
                            if(m == 2)
                                break; 
                        }
                    }
                    
                    if(m == 0)
                    {
                        ++nodeIterator;
                        continue;
                    }
                    else if(m > 1)
                    {
                        if(Vabs(v[0] - lineEndpointOne) < Vabs(v[1] - lineEndpointOne))
                            j = 0;
                        else
                            j = 1;
                    }
                    else
                        j =0;
                    
                    if(addNode(I1[j].getXComponent(), I1[j].getYComponent(), radius / 10000.0))
                    {
                        _nodeInterator1 = &(*_lastNodeAdded);
                    }  
                    else
                    {
                        ++nodeIterator;
                        continue;// This means there is something interfering with the node and this should be dealt with properly
                    }
                        
                    
                    if(addNode(I2[j].getXComponent(), I2[j].getYComponent(), radius / 10000.0))
                    {
                        _nodeInterator2 = &(*_lastNodeAdded);
                        
                    }
                    else
                    {
                        ++nodeIterator;
                        continue;
                    }
                    
                    bool isConnectedToHiddenSegment = false;
                    
                    for(plf::colony<edgeLineShape>::iterator lineIterator = _lineList.begin(); lineIterator != _lineList.end(); ++lineIterator)
                    {
                        if((*lineIterator->getFirstNode() == *nodeIterator || *lineIterator->getSecondNode() == *nodeIterator) && !lineIterator->getSegmentProperty()->getHiddenState())
                        {
                            _lineList.erase(lineIterator);
                            break;
                        }
                        else if(lineIterator->getSegmentProperty()->getHiddenState())
                            isConnectedToHiddenSegment = true;
                    }
                    
                    for(plf::colony<arcShape>::iterator arcIterator = _arcList.begin(); arcIterator != _arcList.end(); ++arcIterator)
                    {
                        if((*arcIterator->getFirstNode() == *nodeIterator || *arcIterator->getSecondNode() == *nodeIterator) && !arcIterator->getSegmentProperty()->getHiddenState())
                        {
                            _arcList.erase(arcIterator);
                            break;
                        }
                        else if(arcIterator->getSegmentProperty()->getHiddenState())
                            isConnectedToHiddenSegment = true;
                    }
                        
                    angle = Varg((I2[j] - v[j])/(I1[j] - v[j]));
                    
                    if(angle < 0)
                    {
                        switchIndex();
                        angle = fabs(angle);
                    }
                    
                    addedArc.setArcAngle(angle * (180.0 / PI));
                    
                    if(addArc(addedArc, 0, true));
                        willReturn = true;
                        
                    if(!isConnectedToHiddenSegment)
                        _nodeList.erase(nodeIterator++);
                    else
                        nodeIterator++;
                }
                    continue;
                case 2:// This is the case for if we have two lines
                {
                    Vector commonNode, endPointLine1, endPointLine2;
                    bool firstLineFound = false;
                    bool secondLineFound = false;
                    double angle, length;
                    arcShape lineAddedArc;
                    
                    lineAddedArc.setNumSegments(20);
                    
                    commonNode.Set(nodeIterator->getCenterXCoordinate(), nodeIterator->getCenterYCoordinate());
                    
                    for(plf::colony<edgeLineShape>::iterator lineIterator = _lineList.begin(); lineIterator != _lineList.end(); ++lineIterator)
                    {
                        if(!firstLineFound && (*lineIterator->getFirstNode() == *nodeIterator || *lineIterator->getSecondNode() == *nodeIterator) && !lineIterator->getSegmentProperty()->getHiddenState())
                        {
                            if(*lineIterator->getFirstNode() == *nodeIterator)
                                endPointLine1.Set(lineIterator->getSecondNode()->getCenterXCoordinate(), lineIterator->getSecondNode()->getCenterYCoordinate());
                            else
                                endPointLine1.Set(lineIterator->getFirstNode()->getCenterXCoordinate(), lineIterator->getFirstNode()->getCenterYCoordinate());
                            
                            lineAddedArc.setSegmentProperty(*lineIterator->getSegmentProperty());
                            
                            firstLineFound = true;
                        }
                        else if(!secondLineFound && (*lineIterator->getFirstNode() == *nodeIterator || *lineIterator->getSecondNode() == *nodeIterator) && !lineIterator->getSegmentProperty()->getHiddenState())
                        {
                            if(*lineIterator->getFirstNode() == *nodeIterator)
                                endPointLine2.Set(lineIterator->getSecondNode()->getCenterXCoordinate(), lineIterator->getSecondNode()->getCenterYCoordinate());
                            else
                                endPointLine2.Set(lineIterator->getFirstNode()->getCenterXCoordinate(), lineIterator->getFirstNode()->getCenterYCoordinate());
                                
                            secondLineFound = true;
                        }
                    }
                    
                    angle = Varg((endPointLine2 - commonNode) / (endPointLine1 - commonNode));// Angle here is currently in radians
                    
                    if(fabs(angle) > PI)
                    {
                        ++nodeIterator;
                        continue;
                    }
                        
                    
                    if(angle < 0)
                    {
                        commonNode = endPointLine1;
                        endPointLine1 = endPointLine2;
                        endPointLine2 = commonNode;
                        commonNode.Set(nodeIterator->getCenterXCoordinate(), nodeIterator->getCenterYCoordinate());
                        angle = fabs(angle);
                    }
                    
                    length = radius / tan(angle / 2.0);
                    
                    // If the radius is too big to fit
                    if((Vabs(endPointLine1 - commonNode) < length) || Vabs(endPointLine2 - commonNode) < length)
                    {
                        ++nodeIterator;
                        continue;
                    }
                        
                    
                    // Compute the locations of the tangent points
                    endPointLine1 = length * (endPointLine1 - commonNode) / Vabs(endPointLine1 - commonNode) + commonNode;
                    endPointLine2 = length * (endPointLine2 - commonNode) / Vabs(endPointLine2 - commonNode) + commonNode;
                    
                    if(addNode(endPointLine1.getXComponent(), endPointLine1.getYComponent(), length / 10000.0))
                    {
                        _nodeInterator2 = &(*_lastNodeAdded);
                    }
                    else
                    {
                        ++nodeIterator;
                        continue;
                    }
                        
                        
                    if(addNode(endPointLine2.getXComponent(), endPointLine2.getYComponent(), length / 10000.0))
                    {
                        _nodeInterator1 = &(*_lastNodeAdded);
                    }
                    else
                    {
                        ++nodeIterator;
                        continue;
                    }
                    
                    bool isConnectedToHiddenLine = false;
                    
                    for(plf::colony<edgeLineShape>::iterator lineIterator = _lineList.begin(); lineIterator != _lineList.end();)
                    {
                        if((*nodeIterator == *lineIterator->getFirstNode() || *nodeIterator == *lineIterator->getSecondNode()) && !lineIterator->getSegmentProperty()->getHiddenState())
                        {
                            if(lineIterator == _lineList.back())
                            {
                                _lineList.erase(lineIterator);
                                break;
                            }
                            else
                                _lineList.erase(lineIterator++);
                        }
                        else if(lineIterator->getSegmentProperty()->getHiddenState())
                        {
                            isConnectedToHiddenLine = true;
                            lineIterator++;
                        }
                        else
                            lineIterator++;
                    }
                    
                    if(!isConnectedToHiddenLine)
                    {
                        for(plf::colony<arcShape>::iterator arcIterator = _arcList.begin(); arcIterator != _arcList.end(); ++arcIterator)
                        {
                            if((*nodeIterator == *arcIterator->getFirstNode() || *nodeIterator == *arcIterator->getSecondNode()) && arcIterator->getSegmentProperty()->getHiddenState())
                            {
                                // Even if there is one arc/line connnected to the node and labeled as hidden, we must keep that node
                                // Although if there are multiple lines/arcs, connected to the node, then they all must be hidden save for
                                // one line, one arc or two arcs or two lines in order to execute these functions
                                isConnectedToHiddenLine = true;
                                break;
                            }
                        }
                    }
                    
                    _lastLineAdded = _lineList.begin();// Used to make sure that the variable is still set to a valid iterator
                    
                    lineAddedArc.setArcAngle(180.0 - angle * (180.0 / PI));
                    
                    if(addArc(lineAddedArc, 0, true))
                        willReturn = true;
                        
                    if(!isConnectedToHiddenLine)
                        _nodeList.erase(nodeIterator++); /// TODO: Check here for issues with iterators
                    else
                        nodeIterator++;
                }
                    continue;
                case -2:// This is the case for if we have two arcs
                {
                    int arcj = 0;
                    Vector arcCenter1, arcCenter2, commonNode, p[8], arcI1[8], arcI2[8];
                    double angle, radius1, radius2, centerDistance, a[8], b[8], d[8], x[8];
                    bool firstArcFound = false;
                    bool secondArcFound = false;
                    plf::colony<arcShape>::iterator firstArc;
                    plf::colony<arcShape>::iterator secondArc;
                    arcShape arcAddArc;
                    
                    commonNode = Vector(nodeIterator->getCenterXCoordinate(), nodeIterator->getCenterYCoordinate());
                    
                    for(plf::colony<arcShape>::iterator arcIterator = _arcList.begin(); arcIterator != _arcList.end(); ++arcIterator)
                    {
                        if(!firstArcFound && (*arcIterator->getFirstNode() == *nodeIterator || *arcIterator->getSecondNode() == *nodeIterator) && !arcIterator->getSegmentProperty()->getHiddenState())
                        {
                            arcCenter1 = Vector(arcIterator->getCenterXCoordinate(), arcIterator->getCenterYCoordinate());
                            radius1 = arcIterator->getRadius(); 
                            arcAddArc.setSegmentProperty(*arcIterator->getSegmentProperty());
                            arcAddArc.setNumSegments(arcIterator->getnumSegments());
                            firstArc = arcIterator;
                            firstArcFound = true;
                        }
                        else if(!secondArcFound && (*arcIterator->getFirstNode() == *nodeIterator || *arcIterator->getSecondNode() == *nodeIterator) && !arcIterator->getSegmentProperty()->getHiddenState())
                        {
                            arcCenter2 = Vector(arcIterator->getCenterXCoordinate(), arcIterator->getCenterYCoordinate());
                            radius2 = arcIterator->getRadius();
                            secondArc = arcIterator; 
                            secondArcFound = true;
                        }
                    }
                    
                    centerDistance = Vabs(arcCenter2 - arcCenter1);
                    
                    a[0] = radius1 + radius; 
                    b[0] = radius2 + radius;
                    
                    a[1] = radius1 + radius; 
                    b[1] = radius2 + radius;
                    
                    a[2] = radius1 - radius; 
                    b[2] = radius2 - radius;
                    
                    a[3] = radius1 - radius; 
                    b[3] = radius2 - radius;
                    
                    a[4] = radius1 - radius; 
                    b[4] = radius2 + radius;
                    
                    a[5] = radius1 - radius; 
                    b[5] = radius2 + radius;
                    
                    a[6] = radius1 + radius; 
                    b[6] = radius2 - radius;
                    
                    a[7] = radius1 + radius; 
                    b[7] = radius2 - radius;
                    
                    for(int k = 0; k < 8; k++)
                    {
                        x[k] = (pow(b[k], 2) + pow(centerDistance, 2) - pow(a[k], 2)) / (2.0 * pow(centerDistance, 2));
                        d[k] = sqrt(pow(b[k], 2) - pow(x[k], 2) * pow(centerDistance, 2));
                    }
                    
                    for(int k = 0; k < 8; k += 2)
                    {
                        // solve for the center point of the radius for each solution.
                        p[k] = ((1 - x[k]) * centerDistance + J * d[k]) * (arcCenter2 - arcCenter1) / Vabs(arcCenter2 - arcCenter1) + arcCenter1;
                        p[k + 1] = ((1 - x[k]) * centerDistance - J * d[k]) * (arcCenter2 - arcCenter1) / Vabs(arcCenter2 - arcCenter1) + arcCenter1;
                    }
                    
                    
                    for(int k = 0; k < 8; k++)
                    {
                        arcI1[arcj] = arcCenter1 + radius1 * (p[k] - arcCenter1) / Vabs(p[k] - arcCenter1);
                        arcI2[arcj] = arcCenter2 + radius2 * (p[k] - arcCenter2) / Vabs(p[k] - arcCenter2);
                        p[arcj] = p[k];
                        
                        if(shortestDistanceFromArc(arcI1[arcj], *firstArc) < (radius / 10000.0) && shortestDistanceFromArc(arcI2[arcj], *secondArc) < (radius / 10000.0) && Vabs(arcI1[arcj] - arcI2[arcj]) > (radius / 10000.0))
                        {
                            arcj++;
                            if(arcj == 2)
                            {
                                break;
                            }
                        }
                    }
                    
                    if(arcj == 0)
                    {
                        ++nodeIterator;
                        continue;
                    }
                    else if(arcj > 1)
                    {
                        if(Vabs(p[0] - commonNode) < Vabs(p[1] - commonNode))
                            arcj = 0;
                        else
                            arcj = 1;
                    }
                    else 
                        arcj = 0;
                        
                    if(addNode(arcI1[arcj].getXComponent(), arcI1[arcj].getYComponent(), centerDistance / 10000.0))
                    {
                            _nodeInterator1 = &(*_lastNodeAdded);
                    }
                    else
                    {
                        ++nodeIterator;
                        continue;
                    }
                        
                        
                    if(addNode(arcI2[arcj].getXComponent(), arcI2[arcj].getYComponent(), centerDistance / 10000.0))
                    {
                            _nodeInterator2 = &(*_lastNodeAdded);
                    }  
                    else
                    {
                        ++nodeIterator;
                        continue;
                    }
                    
                    bool isConnectedToHiddenSegment = false;
                    
                    for(plf::colony<arcShape>::iterator arcIterator = _arcList.begin(); arcIterator != _arcList.end();)
                    {
                        if((*arcIterator->getFirstNode() == *nodeIterator || *arcIterator->getSecondNode() == *nodeIterator) && !arcIterator->getSegmentProperty()->getHiddenState())
                        {
                            if(arcIterator == _arcList.back())
                            {
                                _arcList.erase(arcIterator);
                                break;
                            }
                            else
                                _arcList.erase(arcIterator++);
                        }
                        else if(arcIterator->getSegmentProperty()->getHiddenState())
                        {
                            isConnectedToHiddenSegment = true;
                            arcIterator++;
                        }
                        else
                            arcIterator++;
                    }
                    
                    if(!isConnectedToHiddenSegment)
                    {
                        for(plf::colony<edgeLineShape>::iterator lineIterator = _lineList.begin(); lineIterator != _lineList.end(); ++lineIterator)
                        {
                            if((*nodeIterator == *lineIterator->getFirstNode() || *nodeIterator == *lineIterator->getSecondNode()) && lineIterator->getSegmentProperty()->getHiddenState())
                            {
                                // Even if there is one arc/line connnected to the node and labeled as hidden, we must keep that node
                                // Although if there are multiple lines/arcs, connected to the node, then they all must be hidden save for
                                // one line, one arc or two arcs or two lines in order to execute these functions
                                isConnectedToHiddenSegment = true;
                                break;
                            }
                        }
                    }
    
                    angle = Varg((arcI2[arcj] - p[arcj]) / (arcI1[arcj] - p[arcj]));
                    if(angle < 0)
                    {
                        switchIndex();
                        angle = fabs(angle);
                    }
                    
                    arcAddArc.setArcAngle(angle * 180.0 / PI);
                    
                    if(addArc(arcAddArc, 0, true))
                        willReturn = true;
                        
                    if(!isConnectedToHiddenSegment)
                        _nodeList.erase(nodeIterator++);
                    else
                        nodeIterator++;
                }
                    continue;
                default:// For everything else
                    ++nodeIterator;
                    continue;
                    
            }
        }
        else
            ++nodeIterator;
    }
    
    return willReturn;
}


// Talk to Palm about some of these functions
bool geometryEditor2D::getIntersection(edgeLineShape existingLine, edgeLineShape prospectiveLine, double &intersectionXPoint, double &intersectionYPoint)
{
    /* This code was adapted from FEMM from FEmmeDoc.cpp line 728 BOOL CFemmeDoc::GetIntersection*/
    Vector pNode0, pNode1, iNode0, iNode1;// These are the nodes on the prospective line (pNode) and the intersectionLine (iNode
    Vector tempNode0, tempNode1;
    // First check to see if there are any commmon end points. If so, there is no intersection
    if(existingLine.getFirstNode() == prospectiveLine.getFirstNode() || existingLine.getFirstNode() == prospectiveLine.getSecondNode() || existingLine.getSecondNode() == prospectiveLine.getFirstNode() || existingLine.getSecondNode() == prospectiveLine.getSecondNode())
        return false;
        
    pNode0.Set(existingLine.getFirstNode()->getCenterXCoordinate(), existingLine.getFirstNode()->getCenterYCoordinate());
    pNode1.Set(existingLine.getSecondNode()->getCenterXCoordinate(), existingLine.getSecondNode()->getCenterYCoordinate());
    iNode0.Set(prospectiveLine.getFirstNode()->getCenterXCoordinate(), prospectiveLine.getFirstNode()->getCenterYCoordinate());
    iNode1.Set(prospectiveLine.getSecondNode()->getCenterXCoordinate(), prospectiveLine.getSecondNode()->getCenterYCoordinate());
    
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



double geometryEditor2D::calculateShortestDistance(blockLabel selectedLabel, edgeLineShape segment)
{
    double t, x[3], y[3];

    x[0] = segment.getFirstNode()->getCenterXCoordinate();
    y[0] = segment.getFirstNode()->getCenterYCoordinate();
	
    x[1] = segment.getSecondNode()->getCenterXCoordinate();
    y[1] = segment.getSecondNode()->getCenterYCoordinate();
	
	t = ((selectedLabel.getCenterXCoordinate() - x[0]) * (x[1] - x[0]) + (selectedLabel.getCenterYCoordinate() - y[0]) * (y[1] - y[0])) / ((x[1] - x[0]) * (x[1] - x[0]) + (y[1] - y[0]) * (y[1] - y[0]));
      
	if(t > 1)
		t = 1.0;
	else if(t < 0.0)
		t = 0.0;
		
	x[2] = x[0] + t * (x[1] - x[0]);
	y[2] = y[0] + t * (y[1] - y[0]);
    
	return sqrt((selectedLabel.getCenterXCoordinate() - x[2]) * (selectedLabel.getCenterXCoordinate() - x[2]) + (selectedLabel.getCenterYCoordinate() - y[2]) * (selectedLabel.getCenterYCoordinate() - y[2]));   
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