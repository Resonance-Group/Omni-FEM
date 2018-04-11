#include "common/ClosedPath.h"


bool closedPath::pointInContourNew(wxRealPoint point)
{
	std::vector<simplifiedEdge> convertedPath;
	std::vector<arcPolygon> arcShapes;
	
	double additionTerms = 0;
	double subtractionTerms = 0;
	bool isFirstRun = true;
	bool returnValue = false;
	int windingNumber = 0;
	
	if(p_simplifiedPath.size() == 0)
	{
		/*
		 * This section of the code is doing two things at once. The code is convertering the lines and 
		 * arcs into their simplified geometry models and orienting them on a particular direction.
		 * At the same time, we are computing the shoelace algorithm in order to determine the entire direction of the 
		 * the new polygon. 
		 * Once done, the algorithm will then add in any arc-boxes depending on the direction of the polygon
		 */
		 if(p_closedPath.size() > 2)
		 {
			for(auto edgeIterator = p_closedPath.begin(); edgeIterator != p_closedPath.end(); edgeIterator++)
			{
				auto nextIterator = edgeIterator + 1;
				
				if(nextIterator == p_closedPath.end())
					nextIterator = p_closedPath.begin();
				
				if(isFirstRun)
				{
					simplifiedEdge firstEdge;
					simplifiedEdge secondEdge;
					
					if((*edgeIterator)->isArc())
					{
						arcShape *tempArc = static_cast<arcShape*>(*edgeIterator);
						std::vector<simplifiedEdge> returnEdges = tempArc->getBoundingEdges();
						arcShapes.push_back(arcPolygon(returnEdges, *tempArc));
						firstEdge = returnEdges.at(0);
					}
					else
					{
						firstEdge = (*edgeIterator)->getBoundingEdges().at(0);
					}
					
					if((*nextIterator)->isArc())
					{
						arcShape *tempArc = static_cast<arcShape*>(*nextIterator);
						std::vector<simplifiedEdge> returnEdges = tempArc->getBoundingEdges();
						arcShapes.push_back(arcPolygon(returnEdges, *tempArc));
						secondEdge = returnEdges.at(0);
					}
					else
					{
						secondEdge = (*nextIterator)->getBoundingEdges().at(0);
					}
					
					if(firstEdge.getEndPoint() != secondEdge.getStartPoint())
					{
						if(firstEdge.getStartPoint() == secondEdge.getStartPoint())
						{
							firstEdge.swap();
							
							for(auto arcIterator = arcShapes.begin(); arcIterator != arcShapes.end(); arcIterator++)
							{
								if(arcIterator->getArc().getArcID() == firstEdge.getArcID())
								{
									arcIterator->setSwapped();
									break;
								}
							}
						}
						else if(firstEdge.getStartPoint() == secondEdge.getEndPoint())
						{
							firstEdge.swap();
							secondEdge.swap();
							
							for(auto arcIterator = arcShapes.begin(); arcIterator != arcShapes.end(); arcIterator++)
							{
								if(arcIterator->getArc().getArcID() == firstEdge.getArcID())
								{
									arcIterator->setSwapped();
								}
								
								if(arcIterator->getArc().getArcID() == secondEdge.getArcID())
								{
									arcIterator->setSwapped();
								}
							}
							
						}
						else if(firstEdge.getEndPoint() == secondEdge.getEndPoint())
						{
							secondEdge.swap();
							
							for(auto arcIterator = arcShapes.begin(); arcIterator != arcShapes.end(); arcIterator++)
							{
								if(arcIterator->getArc().getArcID() == secondEdge.getArcID())
								{
									arcIterator->setSwapped();
									break;
								}
							}
						}
					}
					
					isFirstRun = false;
					
					convertedPath.push_back(firstEdge);
					convertedPath.push_back(secondEdge);
					
					additionTerms += (firstEdge.getStartPoint().x) * (firstEdge.getEndPoint().y);
					subtractionTerms += (firstEdge.getEndPoint().x) * (firstEdge.getStartPoint().y);
					
					additionTerms += (secondEdge.getStartPoint().x) * (secondEdge.getEndPoint().y);
					subtractionTerms += (secondEdge.getEndPoint().x) * (secondEdge.getStartPoint().y);
				}
				else
				{
					simplifiedEdge aEdge;
					
					if(nextIterator != p_closedPath.begin())
					{
						if((*nextIterator)->isArc())
						{
							arcShape *tempArc = static_cast<arcShape*>(*nextIterator);
							std::vector<simplifiedEdge> returnEdges = tempArc->getBoundingEdges();
							arcShapes.push_back(arcPolygon(returnEdges, *tempArc));
							aEdge = returnEdges.at(0);
						}
						else
							aEdge = (*nextIterator)->getBoundingEdges().at(0);
					}
					else
						aEdge = convertedPath.at(0);
						
					if(convertedPath.back().getEndPoint() == aEdge.getEndPoint() && nextIterator != p_closedPath.begin())
					{
						aEdge.swap();
						
						if(aEdge.getArcID() != 0)
							arcShapes.back().setSwapped();
					}
					
					if(nextIterator != p_closedPath.begin())
					{
						convertedPath.push_back(aEdge);
						additionTerms += (aEdge.getStartPoint().x) * (aEdge.getEndPoint().y);
						subtractionTerms += (aEdge.getEndPoint().x) * (aEdge.getStartPoint().y);
					}
				}
			}
				
			if(subtractionTerms > additionTerms)
				p_reverseWindingResult = true;
		 }
		 else if(p_closedPath.size() == 2 && p_closedPath.at(0)->isArc() && p_closedPath.at(1)->isArc())
		 {
			 // This is the case where we have 2 semi circles
			 std::vector<simplifiedEdge> returnEdges;
			 
			 arcShape *tempArc = static_cast<arcShape*>(p_closedPath.at(0));
			 returnEdges = tempArc->getBoundingEdges();
			 arcShapes.push_back(arcPolygon(returnEdges, *tempArc));
			 
			 returnEdges.erase(returnEdges.begin());
			 
			 convertedPath = returnEdges;
			 
			 tempArc = static_cast<arcShape*>(p_closedPath.at(1));
			 returnEdges = tempArc->getBoundingEdges();
			 arcShapes.push_back(arcPolygon(returnEdges, *tempArc));
			 
			 returnEdges.erase(returnEdges.begin());
			 
			 convertedPath.insert(convertedPath.end(), returnEdges.begin(), returnEdges.end());
		 }
		 else
			 return false;// This is an invalid condition
			 
		if(!(p_closedPath.size() == 2 && p_closedPath.at(0)->isArc() && p_closedPath.at(1)->isArc()))
		{
			for(auto arcShapeIterator = arcShapes.begin(); arcShapeIterator != arcShapes.end(); arcShapeIterator++)
			{
				for(auto edgeIterator = convertedPath.begin(); edgeIterator != convertedPath.end(); edgeIterator++)
				{
					if(edgeIterator->getArcID() == arcShapeIterator->getArc().getArcID())
					{
						// If we have a match, we need to check if the algorithm should replace the simplified edge with
						// the approiate "arc box"
						if(!p_reverseWindingResult)
						{
							// IF we do not have a swapped edge, then this means that geometry was "added" to the polygon
							if(!edgeIterator->getSwappedState())
							{
								std::vector<simplifiedEdge> returnEdges = arcShapeIterator->getEdges();
								returnEdges.erase(returnEdges.begin());
								edgeIterator->setDeleteStatus();// This edge will not longer be need since it is being replaced
								convertedPath.insert(edgeIterator, returnEdges.begin(), returnEdges.end());
							}
						}
						else
						{
							// For CW orientations, if we have a swapped state, then this means that geometry was "added" to the polygon
							if(edgeIterator->getSwappedState())
							{
								simplifiedEdge lastEdge;
								
								std::vector<simplifiedEdge> returnEdges = arcShapeIterator->getEdges();
								returnEdges.erase(returnEdges.begin());
								/*
								 * For CW orientations, we need to maintain the orietation of the lines
								 * These section will ensure that the arc box lines match up with the 
								 * previouse and next lines
								 */ 
								lastEdge = returnEdges.at(0);
								returnEdges.at(0) = returnEdges.back();
								returnEdges.pop_back();
								returnEdges.push_back(lastEdge);
								
								for(auto returnEdgeIterator = returnEdges.begin(); returnEdgeIterator != returnEdges.end(); returnEdgeIterator++)
								{
									returnEdgeIterator->swap();
								}
								
								edgeIterator->setDeleteStatus();
								convertedPath.insert(edgeIterator, returnEdges.begin(), returnEdges.end());
							}
						}
						
						break;
					}
				}
			}
		}
		
		convertedPath.erase(std::remove_if(convertedPath.begin(), convertedPath.end(), *this), convertedPath.end());
		
		if(p_simplifiedPath.size() == 0)
		{
			p_simplifiedPath = convertedPath;
			p_arcPolygons = arcShapes;
		}
		
	}
		
/*		if((*edgeIterator)->isArc())
		{
			arcShape *tempArc = static_cast<arcShape*>(*edgeIterator);
			returnEdges = tempArc->getBoundingEdges();
			arcShapes.push_back(arcPolygon(returnEdges, tempArc->getArcID()));
			
			for(auto arcEdgeIterator = returnEdges.begin(); arcEdgeIterator != returnEdges.end();)
			{
				
			}
			
			
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
		 
		additionTerms += (lineIterator->getStartPoint().x) * (lineIterator->getEndPoint().y);
		subtractionTerms += (lineIterator->getEndPoint().x) * (lineIterator->getStartPoint().y);
	}
	
	if(subtractionTerms > additionTerms)
		reverseWindingResult = true;*/
		
	// Now we run the actual winding number algorithm
	for(auto lineIterator = p_simplifiedPath.begin(); lineIterator != p_simplifiedPath.end(); lineIterator++)
	{
		double isLeftResult = lineIterator->isLeft(point);
		
		if(p_reverseWindingResult)
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
		
		for(auto arcSegmentIterator = p_arcPolygons.begin(); arcSegmentIterator != p_arcPolygons.end(); arcSegmentIterator++)
		{
			// Check if the point lies within the arc segment on the correct side
			// If the point is on the incorrect side of the arc (where the point is actually outside of the
			// geometry, then we need to set the pointIsInside to false and break out of the loop.
			// if the point is actually in one of the boxes and is inside the geometry, then simply break out
			// of this loop
			if(arcSegmentIterator->isInside(point))
			{
				double distance = sqrt(pow((point.x - arcSegmentIterator->getArc().getCenter().x), 2) + pow((point.y - arcSegmentIterator->getArc().getCenter().y), 2));
				
				if(p_reverseWindingResult)
				{
					// The case for CW direction
					if(arcSegmentIterator->getSwappedState())
					{
						if(distance > arcSegmentIterator->getArc().getRadius())
							pointIsInside = false;
					}
					else
					{
						if(distance < arcSegmentIterator->getArc().getRadius())
							pointIsInside = false;
					}
				}
				else
				{
					// The case for CCW direction
					if(arcSegmentIterator->getSwappedState())
					{
						if(distance < arcSegmentIterator->getArc().getRadius())
							pointIsInside = false;
					}
					else
					{
						if(distance > arcSegmentIterator->getArc().getRadius())
							pointIsInside = false;
					}
				}
				
				break;
			}
		}
		
		returnValue = pointIsInside;
	}
	else
		returnValue = false;
	
	return returnValue;
}