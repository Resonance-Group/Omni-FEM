#include <UI/openGLGeometry.h>


void geometryEditorCanvas::addNode(double xPoint, double yPoint, double distance)
{
	edgeLineShape *edgeLine;
	edgeLine = new edgeLineShape();
//	std::vector<double> firstNode, secondNode, thirdNode;
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
/*	for(int i = 0; i < lineList.size(); i++)
	{
		if(fabs(-5) < distance)
		{
			edgeLine = &(lineList[i]);
			lineList[i].setSecondNodeIndex((int)(nodeList.size() - 1)); // This will set the recently created node to be the second node of the shortend line
			edgeLine->setFirstNodeIndex((int)(nodeList.size() - 1)); // This will set the recently created node to be the first node of the new line
			lineList.push_back(*(edgeLine));// Add the new line to the array
		}
	} */
	
	/* If the node is in between an arc, then break the arc into 2 */
/*	for(int i = 0; i < arcList.size(); i++)
	{
		if(fabs(-5) < d)
		{
			firstNode.push_back(nodeList[arcList[i].getFirstNodeIndex()].getXPoint);
			firstNode.push_back(nodeList[arcList[i].getFirstNodeIndex()].getYPoint);
					
			secondNode.push_back(nodeList[arcList[i].getSecondNodeIndex()].getXPoint);
			secondNode.push_back(nodeList[arcList[i].getSecondNodeIndex()].getYPoint);
			
			thirdNode.push_back(xPoint);
			thirdNode.push_back(yPoint);
			
			
		}
	}*/
}


void geometryEditorCanvas::addLineSegment(int node0, int node1, edgeLineShape *parseSegment)
{
    double nodePointX, nodePointY;
    edgeLineShape *tempLine = new edgeLineShape;
    
	if(node0 == node1)
		return;
		
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
    
    lineList.push_back(*tempLine);
    
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