#include <UI/openGLGeometry.h>


void geometryEditorCanvas::addNode(double xPoint, double yPoint, double distance)
{
	edgeLineShape *edgeLine;
	edgeLine = new edgeLineShape();
//	std::vector<double> firstNode, secondNode, thirdNode;
	
	
	/* This section will make sure that two nodes are not drawn on top of each other */
	for(int i = 0; i < nodeList.size(); i++)
	{
		if(nodeList[i].getDistance(xPoint, yPoint) < 0.01)// This will compare against 1/mag where mag is the scaling function for zooming. However, it is currently being hardcoded to 0.01
			return;
	}
	
	/* This section will make sure that a node is not drawn ontop of a block label */
	for(int i = 0; i < blockLabelList.size(); i++)
	{
		if(blockLabelList[i].getDistance(xPoint, yPoint) < 0.01)
			return;
	}
	
	nodeList.push_back(*(new node(xPoint, yPoint)));
    int testSize = nodeList.size();
	nodeList[testSize - 1].setNodeIndex(testSize - 1);
	
	/* If the node is in between a line, then break the line into 2 lines */
	for(int i = 0; i < lineList.size(); i++)
	{
		if(fabs(-5) < distance)
		{
			edgeLine = &(lineList[i]);
			lineList[i].setSecondNodeIndex((int)(nodeList.size() - 1)); // This will set the recently created node to be the second node of the shortend line
			edgeLine->setFirstNodeIndex((int)(nodeList.size() - 1)); // This will set the recently created node to be the first node of the new line
			lineList.push_back(*(edgeLine));// Add the new line to the array
		}
	} 
	
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
