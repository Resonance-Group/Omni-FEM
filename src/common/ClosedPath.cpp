#include "common/ClosedPath.h"


bool closedPath::pointInContourNew(wxRealPoint point)
{
	std::vector<simplifiedEdge> convertedPath;
	std::vector<std::vector<simplifiedEdge>> arcShapes;
	
	double additionTerms = 0;
	double subtractionTerms = 0;
	bool reverseWindingResult = false;
	bool isFirstRun = true;
	bool returnValue = false;
	int windingNumber = 0;
	
	// First, we need to convert the entire path into a list of edges
	// Also we need to ensure that the lines are in a order be it CW or CCW
	for(auto edgeIterator = p_closedPath.begin(); edgeIterator != p_closedPath.end(); edgeIterator++)
	{
		std::vector<simplifiedEdge> returnEdges;
		
		if((*edgeIterator)->isArc())
		{
			
		}
		else
		{
			returnEdges = (*edgeIterator)->getBoundingEdges();
		}
		
		convertedPath.insert(convertedPath.end(), returnEdges.begin(), returnEdges.end());
	}
	
	// Next we need to run the shoelace algorithm in order to to determine the orientation of the lines
	// And to ensure that all of the lines are oriented the same way for their orientation
	for(auto lineIterator = convertedPath.begin(); lineIterator != convertedPath.end(); lineIterator++)
	{
		auto nextLineIterator = lineIterator + 1;
		
		if(nextLineIterator == convertedPath.end())
			nextLineIterator = convertedPath.begin();
		
		if(isFirstRun)
		{
			if(lineIterator->getEndPoint() != nextLineIterator->getStartPoint())
			{
				if(lineIterator->getStartPoint() == nextLineIterator->getStartPoint())
					lineIterator->swap();
				else if(lineIterator->getStartPoint() == nextLineIterator->getEndPoint())
				{
					lineIterator->swap();
					nextLineIterator->swap();
				}
				else if(lineIterator->getEndPoint() == nextLineIterator->getEndPoint())
					nextLineIterator->swap();
			}
			
			isFirstRun = false;
		}
		else
		{
			if(lineIterator->getEndPoint() == nextLineIterator->getEndPoint())
				nextLineIterator->swap();
		}
		
		/* 
		 * This is the actual shoelace algorithm that is implemented. In short, we have two terms, addition terms
		 * and subtraction terms. THe addition terms are the summation of the Xpoint of the first node multiplied by
		 * the Ypoint of the second node for all edges (arcs are a special case)
		 * 
		 * The subtraction term is the summation of the Xpoint of the second node multiplied by the
		 * Ypoint of the first node (arcs are a special case)
		 * 
		 */ 
		 
		additionTerms += (lineIterator->getStartPoint().x) * (lineIterator->getEndPoint().y);
		subtractionTerms += (lineIterator->getEndPoint().x) * (lineIterator->getStartPoint().y);
	}
	
	if(subtractionTerms > additionTerms)
		reverseWindingResult = true;
		
	// Now we run the actual winding number algorithm
	for(auto lineIterator = convertedPath.begin(); lineIterator != convertedPath.end(); lineIterator++)
	{
		double isLeftResult = lineIterator->isLeft(point);
		
		if(reverseWindingResult)
			isLeftResult *= -1;
		
		if(lineIterator->getStartPoint().y <= point.y)
		{
			if(lineIterator->getEndPoint().y > point.y)
			{
				if(isLeftResult > 0)
					windingNumber++;
				else if(isLeftResult < 0)
					windingNumber--;
			}
		}
		else if(lineIterator->getEndPoint().y <= point.y)
		{
			if(isLeftResult < 0)
				windingNumber--;
			else if(isLeftResult > 0)
				windingNumber++;
		}
	}
	
	if(windingNumber > 0)
	{
		bool pointIsInside = true;
		
		for(auto arcSegmentIterator = arcShapes.begin(); arcSegmentIterator != arcShapes.end(); arcSegmentIterator++)
		{
			// Check if the point lies within the arc segment on the correct side
			// If the point is on the incorrect side of the arc (where the point is actually outside of the
			// geometry, then we need to set the pointIsInside to false and break out of the loop.
			// if the point is actually in one of the boxes and is inside the geometry, then simply break out
			// of this loop
		}
		
		returnValue = pointIsInside;
	}
	else
		returnValue = false;
	
	
	return returnValue;
}