#ifndef CLOSED_PATH_H_
#define CLOSED_PATH_H_

#include <vector>
#include <algorithm>
#include <map>
#include <iterator>

#include <wx/wx.h>

#include <common/BoundingBox.h>
#include <common/GeometryProperties/BlockProperty.h>

#include <UI/geometryShapes.h>

class closedPath
{
private:
	boundingBox p_boundingBox;

	double p_distance = 0;
	
	std::vector<edgeLineShape*> p_closedPath;
	
	wxRealPoint p_centerPoint = wxPoint(0, 0);
	
	blockProperty *p_property = nullptr;
	
	std::vector<closedPath> p_holes;
	
	std::vector<blockLabel*> p_blockLabelList;
	
	std::map<node*, char> p_vertexList;
	
	bool p_holesFound = false;
	
	bool shareCommonEdge(closedPath firstPath, closedPath secondPath, std::vector<edgeLineShape*> &commonEdges)
	{
		commonEdges.clear();// Make sure this vector is empty before proceding
		
		for(auto firstPathIterator = firstPath.getClosedPath()->begin(); firstPathIterator != firstPath.getClosedPath()->end(); firstPathIterator++)
		{
			for(auto secondPathIterator = secondPath.getClosedPath()->begin(); secondPathIterator != secondPath.getClosedPath()->end(); secondPathIterator++)
			{
				if(*(*firstPathIterator) == *(*secondPathIterator))
					commonEdges.push_back(*firstPathIterator);
			}
		}
		
		if(commonEdges.size() > 0)
			return true;
		else
			return false;
	}
	
	closedPath getClosedContour(std::vector<edgeLineShape*> edgeList)
	{
		closedPath newPath;
		bool isFinished = false;
		
		// Find the first edge that is not yet used
		for(auto edgeIterator = edgeList.begin(); edgeIterator != edgeList.end(); edgeIterator++)
		{
			if(!(*edgeIterator)->getVisitedStatus())
			{
				newPath = closedPath(*edgeIterator);
				break;
			}
		}
		
		
		while(!isFinished)
		{
			if(newPath.getClosedPath()->size() > 1)
			{
				for(auto edgeIterator = edgeList.begin(); edgeIterator != edgeList.end(); edgeIterator++)
				{
					edgeLineShape *previouseAddedSegment = *(++newPath.getClosedPath()->rbegin());
					node *nodeToTest = nullptr;
					
					if(*(*edgeIterator) == *newPath.getClosedPath()->back() || *(*edgeIterator) == *previouseAddedSegment)
					{
						auto backValue = *edgeList.back();
						bool result = *(*edgeIterator) == *edgeList.back();
						if(result)
							isFinished = true;
							
						continue;
					}
					
					// If the first node of the recently added line is connected to the previousely added segment, then we need to test
					// on the second node.
					// Otherwise, go ahead and test on the first node
					if(*newPath.getClosedPath()->back()->getFirstNode() == *previouseAddedSegment->getFirstNode() || *newPath.getClosedPath()->back()->getFirstNode() == *previouseAddedSegment->getSecondNode())
						nodeToTest = newPath.getClosedPath()->back()->getSecondNode();
					else
						nodeToTest = newPath.getClosedPath()->back()->getFirstNode();
					
					if(*nodeToTest == *(*newPath.getClosedPath()->begin())->getFirstNode() || *nodeToTest == *(*newPath.getClosedPath()->begin())->getSecondNode())
					{
						isFinished = true;
						break;
					}
					else if(*nodeToTest == *(*edgeIterator)->getFirstNode() || *nodeToTest == *(*edgeIterator)->getSecondNode())
					{
						newPath.addEdgeToPath(*edgeIterator);
						break;
					}
				}
			}
			else if(newPath.getClosedPath()->size() == 1)
			{
				for(auto edgeIterator = edgeList.begin(); edgeIterator != edgeList.end(); edgeIterator++)
				{
					if(*(*edgeIterator) == *newPath.getClosedPath()->at(0) || (*edgeIterator)->getVisitedStatus())
						continue;
					
					if(*newPath.getClosedPath()->at(0)->getFirstNode() == *(*edgeIterator)->getFirstNode() || *newPath.getClosedPath()->at(0)->getFirstNode() == *(*edgeIterator)->getSecondNode())
					{
						newPath.addEdgeToPath(*edgeIterator);
						break;
					}
				}
			}
			else
			{
				// THis means there was an error and we need to avoid an infinite loop
				isFinished = true;
				break;
			}
		}
		
		return newPath;
	}

public:

	closedPath(edgeLineShape &firstEdge)
	{
		p_closedPath.push_back(&firstEdge);
		
		p_boundingBox = boundingBox(wxRealPoint(firstEdge.getFirstNode()->getCenterXCoordinate(), firstEdge.getFirstNode()->getCenterYCoordinate()));
		p_boundingBox.addPoint(wxRealPoint(firstEdge.getSecondNode()->getCenterXCoordinate(), firstEdge.getSecondNode()->getCenterYCoordinate()));
		
		if(firstEdge.isArc())
			p_boundingBox.addPoint(firstEdge.getMidPoint());
			
		p_centerPoint = firstEdge.getMidPoint();

		p_vertexList.insert(std::pair<node*, int>(firstEdge.getFirstNode(), 1));
		p_vertexList.insert(std::pair<node*, int>(firstEdge.getSecondNode(), 1));
	}
	
	closedPath(edgeLineShape *firstEdge)
	{
		p_closedPath.push_back(firstEdge);
		
		p_boundingBox = boundingBox(wxRealPoint(firstEdge->getFirstNode()->getCenterXCoordinate(), firstEdge->getFirstNode()->getCenterYCoordinate()));
		p_boundingBox.addPoint(wxRealPoint(firstEdge->getSecondNode()->getCenterXCoordinate(), firstEdge->getSecondNode()->getCenterYCoordinate()));
		
		if(firstEdge->isArc())
			p_boundingBox.addPoint(firstEdge->getMidPoint());
		
		p_centerPoint = firstEdge->getMidPoint();
		
		p_vertexList.insert(std::pair<node*, int>(firstEdge->getFirstNode(), 1));
		p_vertexList.insert(std::pair<node*, int>(firstEdge->getSecondNode(), 1));
	}
	
	closedPath()
	{
		
	}

	double getDistance()
	{
		return p_distance;
	}
	
	void addDistance(double value)
	{
		p_distance += value;
	}
	
	std::vector<edgeLineShape*> *getClosedPath()
	{
		return &p_closedPath;
	}
	
	void addEdgeToPath(edgeLineShape &addEdge)
	{
		p_distance += addEdge.getDistance();
		
		if(!addEdge.isArc())
		{
			p_centerPoint.x = (addEdge.getCenter().x + p_closedPath.size() * p_centerPoint.x) / (p_closedPath.size() + 1);
			p_centerPoint.y = (addEdge.getCenter().y + p_closedPath.size() * p_centerPoint.y) / (p_closedPath.size() + 1);
		}
		else
		{
			p_centerPoint.x = (addEdge.getMidPoint().x + p_closedPath.size() * p_centerPoint.x ) / (p_closedPath.size() + 1);
			p_centerPoint.y = (addEdge.getMidPoint().y + p_closedPath.size() * p_centerPoint.y) / (p_closedPath.size() + 1);
		}
		
		p_closedPath.push_back(&addEdge);
		
		p_boundingBox.addPoint(wxRealPoint(addEdge.getFirstNode()->getCenterXCoordinate(), addEdge.getFirstNode()->getCenterYCoordinate()));
		p_boundingBox.addPoint(wxRealPoint(addEdge.getSecondNode()->getCenterXCoordinate(), addEdge.getSecondNode()->getCenterYCoordinate()));
		
		if(addEdge.isArc())
		{
			p_boundingBox.addPoint(addEdge.getMidPoint());
		}
		
		auto mapIterator = p_vertexList.find(addEdge.getFirstNode());
		
		if(mapIterator == p_vertexList.end())
			p_vertexList.insert(std::pair<node*, int>(addEdge.getFirstNode(), 1));
			
		mapIterator = p_vertexList.find(addEdge.getSecondNode());
		
		if(mapIterator == p_vertexList.end())
			p_vertexList.insert(std::pair<node*, int>(addEdge.getSecondNode(), 1));
	}
	
	void addEdgeToPath(edgeLineShape *addEdge)
	{
		double temp = addEdge->getDistance();
		p_distance += addEdge->getDistance();
		
		if(!addEdge->isArc())
		{
			p_centerPoint.x = (addEdge->getCenter().x + p_closedPath.size() * p_centerPoint.x) / (p_closedPath.size() + 1);
			p_centerPoint.y = (addEdge->getCenter().y + p_closedPath.size() * p_centerPoint.y) / (p_closedPath.size() + 1);
		}
		else
		{
			p_centerPoint.x = (addEdge->getMidPoint().x + p_closedPath.size() * p_centerPoint.x) / (p_closedPath.size() + 1);
			p_centerPoint.y = (addEdge->getMidPoint().y + p_closedPath.size() * p_centerPoint.y) / (p_closedPath.size() + 1);
		}
		
		p_closedPath.push_back(addEdge);
		
		p_boundingBox.addPoint(wxRealPoint(addEdge->getFirstNode()->getCenterXCoordinate(), addEdge->getFirstNode()->getCenterYCoordinate()));
		p_boundingBox.addPoint(wxRealPoint(addEdge->getSecondNode()->getCenterXCoordinate(), addEdge->getSecondNode()->getCenterYCoordinate()));
			
		if(addEdge->isArc())
		{
			p_boundingBox.addPoint(addEdge->getMidPoint());
		}
		
		auto mapIterator = p_vertexList.find(addEdge->getFirstNode());
		
		if(mapIterator == p_vertexList.end())
			p_vertexList.insert(std::pair<node*, int>(addEdge->getFirstNode(), 1));
			
		mapIterator = p_vertexList.find(addEdge->getSecondNode());
		
		if(mapIterator == p_vertexList.end())
			p_vertexList.insert(std::pair<node*, int>(addEdge->getSecondNode(), 1));
		
	}
	
	wxRealPoint getMaxSize()
	{
		return p_boundingBox.getMaxBounds();
	}
	
	wxRealPoint getCenter() const
	{
		return p_centerPoint;
	}
	
	void setProperty(blockProperty &property)
	{
		p_property = &property;
	}
	
	void setProperty(blockProperty *property)
	{
		p_property = property;
	}
	
	blockProperty *getProperty()
	{
		return p_property;
	}
	
	void addHole(closedPath *hole)
	{
		p_holes.push_back(*hole);
	}
	
	void addHole(closedPath &hole)
	{
		p_holes.push_back(hole);
	}
	
	std::vector<closedPath> *getHoles()
	{
		return &p_holes;
	}
	
	void addBlockLabel(blockLabel &label)
	{
		p_blockLabelList.push_back(&label);
	}
	
	std::vector<blockLabel*> *getBlockLabelList()
	{
		return &p_blockLabelList;
	}
	
	void setBlockLabelList(std::vector<blockLabel*> blockList)
	{
		p_blockLabelList = blockList;
	}
	
	void clearBlockLabelList()
	{
		p_blockLabelList.clear();
	}
	
	bool pointInBoundingBox(wxRealPoint point)
	{
		if(	point.x < p_boundingBox.getMaxBounds().x &&
			point.x > p_boundingBox.getMinBounds().x &&
			point.y < p_boundingBox.getMaxBounds().y &&
			point.y > p_boundingBox.getMinBounds().y)
			return true;
		else
			return false;
	}
	
	std::map<node*, char> *getVertexList()
	{
		return &p_vertexList;
	}
	
	boundingBox getBoundingBox()
	{
		return p_boundingBox;
	}
	
	void combineHoles()
	{
		bool isFinished = false;
		
		while(!isFinished)
		{
			bool newHoleCreated = false;
			for(auto firstHoleIterator = p_holes.begin(); firstHoleIterator != --(p_holes.end()); firstHoleIterator++)
			{
				std::vector<edgeLineShape*> commonEdgeList;// This list here is used to indicate which edges are common to the two holes
				
				for(auto secondHoleIterator = firstHoleIterator + 1; secondHoleIterator != p_holes.end(); secondHoleIterator++)
				{
					if(shareCommonEdge(*firstHoleIterator, *secondHoleIterator, commonEdgeList))
					{
						// First we must generate a list of all of the edges that are not the common edge
						std::vector<edgeLineShape*> newHoleEdgeList;
						closedPath newHole;
						
						// First, store all edges that are not the common edge from the first hole
						for(auto edgeIterator = firstHoleIterator->getClosedPath()->begin(); edgeIterator != firstHoleIterator->getClosedPath()->end(); edgeIterator++)
						{
							bool isCommonEdge = false;
							
							for(auto holeEdgeIterator = commonEdgeList.begin(); holeEdgeIterator != commonEdgeList.end(); holeEdgeIterator++)
							{
								if(*(*edgeIterator) == *(*holeEdgeIterator))
								{
									isCommonEdge = true;
									break;
								}
							}
							
							if(!isCommonEdge)
								newHoleEdgeList.push_back(*edgeIterator);
						}
						
						// Then store all edges that are not the common edge from the second hole
						for(auto edgeIterator = secondHoleIterator->getClosedPath()->begin(); edgeIterator != secondHoleIterator->getClosedPath()->end(); edgeIterator++)
						{
							bool isCommonEdge = false;
							
							for(auto holeEdgeIterator = commonEdgeList.begin(); holeEdgeIterator != commonEdgeList.end(); holeEdgeIterator++)
							{
								if(*(*edgeIterator) == *(*holeEdgeIterator))
								{
									isCommonEdge = true;
									break;
								}
							}
							
							if(!isCommonEdge)
								newHoleEdgeList.push_back(*edgeIterator);
						}
						
						for(auto newHoleEdgeIterator = newHoleEdgeList.begin(); newHoleEdgeIterator != newHoleEdgeList.end(); newHoleEdgeIterator++)
						{
							/* We must set the visited state to false for this portion of the code 
							 * Later, it will be set back to true once the algorithm is done
							 */ 
							(*newHoleEdgeIterator)->setVisitedStatus(false);
						}
						
						if(commonEdgeList.size() > 1)
						{
							/* This is the case that would pertain to if two holes form a circular pattern
							 * then we are left with 2 paths. One of the two paths will have a greater distance then the other.
							 * THe path with the greatest distance would be the outside path and thus the outer hole.
							 * In this case, the algorithm would need to choose the outer path as the hole.
							 * In the case where two holes contain 2 or more common edges, this path will still work
							 * since at the end of the loop, numberOfCompletedEdges == size of the new hole edge list
							 */ 
							unsigned int numberOfCompletedEdges = 0;
							
							while(numberOfCompletedEdges < newHoleEdgeList.size())
							{
								closedPath tempHole = getClosedContour(newHoleEdgeList);
								
								for(auto edgeIterator = tempHole.getClosedPath()->begin(); edgeIterator != tempHole.getClosedPath()->end(); edgeIterator++)
								{
									if(!(*edgeIterator)->getVisitedStatus())
									{
										(*edgeIterator)->setVisitedStatus(true);
										numberOfCompletedEdges++;
									}
								}
								
								if(newHole.getClosedPath()->size() == 0 || tempHole.getDistance() > newHole.getDistance())
									newHole = tempHole;
							}
						}
						else if(commonEdgeList.size() == 1)
						{
							newHole = getClosedContour(newHoleEdgeList);
							
							for(auto edgeIterator = newHole.getClosedPath()->begin(); edgeIterator !=  newHole.getClosedPath()->end(); edgeIterator++)
							{
								(*edgeIterator)->setVisitedStatus(true);
							}
						}
						
						unsigned int firstHoleDistance = std::distance(p_holes.begin(), firstHoleIterator);
						unsigned int secondHoleDistance = std::distance(p_holes.begin(), secondHoleIterator);
						auto lastIterator = --(p_holes.end());
						
						if(secondHoleIterator == lastIterator)
						{
							p_holes.erase(lastIterator);
							
							p_holes.at(firstHoleDistance) = p_holes.back();
							p_holes.pop_back();
						}
						else
						{
							p_holes.at(firstHoleDistance) = p_holes.back();
							p_holes.pop_back();
						
							p_holes.at(secondHoleDistance) = p_holes.back();
							p_holes.pop_back();
						}
						
						p_holes.push_back(newHole);
						
						newHoleCreated = true;
					}
					
					if(newHoleCreated)
						break;
				}
				
				if(newHoleCreated)
					break;
			}
			
			if(!newHoleCreated)
				isFinished = true;
		}
	}
	
	bool getHolesFoundState()
	{
		return p_holesFound;
	}
	
	void setHolesFound()
	{
		p_holesFound = true;
	}
	
	void setHoles(std::vector<closedPath> holes)
	{
		p_holes = holes;
	}
	
	void transferHoles(closedPath &transfer)
	{
		transfer.setHoles(p_holes);
	}
	
	/**
	 * @brief 	The purpose of this function to to check if a specfied point lies within the path/closed contour.
	 * 			The function accomplishes this through the use of a modified version of the winding number method.
	 * 			In this method, the algorithm calculates the number of times that the point wraps around the 
	 * 			closed path. The current version of this algorithm does not use arc sin or cos. But instead checks to see
	 * 			if the point is to the left or right of an edge within the closed path. If teh number of times that the point
	 * 			is to the left of the edges is greater then the number of rights, then this means that the point lies withing the
	 * 			closed path.
	 * @param label The rectangle shape that the algorithm will be checking to see if it lies within the closed path
	 * @param path The closed path to check if point exists inside of
	 * @return Returns true if the point lies within the closed path. Otherwise, returns false.
	 */
	bool pointInContour(wxRealPoint point)
	{
		int windingNumber = 0;
		bool isFirstRun = true;
		bool reverseWindingResult = false;
		
		double additionTerms = 0;
		double subtractionTerms = 0;
		
		// First, the algorithm will need to ensure that all of the lines are oriented in either CCW or CW.
		// Each contour, the order of the lines is CCW or CW but the order of the nodes is different.
		// For example, the start node of the 1st line could be "connected" to the end node of the next line.
		// In which case, we need to swap the nodes of the 1st line.
		
		for(auto lineIterator = p_closedPath.begin(); lineIterator != p_closedPath.end(); lineIterator++)
		{
			auto nextLineIterator = lineIterator + 1;
			
			if(nextLineIterator == p_closedPath.end())
				nextLineIterator = p_closedPath.begin();
			
			if(isFirstRun)
			{
				if(*(*lineIterator)->getSecondNode() != *(*nextLineIterator)->getFirstNode())
				{
					if(*(*lineIterator)->getFirstNode() == *(*nextLineIterator)->getFirstNode())
						(*lineIterator)->swap();
					else if(*(*lineIterator)->getFirstNode() == *(*nextLineIterator)->getSecondNode())
					{
						(*lineIterator)->swap();
						(*nextLineIterator)->swap();
					}
					else if(*(*lineIterator)->getSecondNode() == *(*nextLineIterator)->getSecondNode())
						(*nextLineIterator)->swap();
				}
				
				isFirstRun = false;
			}
			else
			{
				if(*(*lineIterator)->getSecondNode() == *(*nextLineIterator)->getSecondNode())
					(*nextLineIterator)->swap();
			}
			
			/* 
			 * This is the actual shoelace algorithm that is implemented. In short, we have two terms, addition terms
			 * and subtraction terms. THe addition terms are the summation of the Xpoint of the first node multiplied by
			 * the Ypoint of the second node for all edges (arcs are a special case)
			 * 
			 * The subtraction term is the summation of the Xpoint of the second node multiplied by the
			 * Ypoint of the first node (arcs are a special case)
			 */ 
			if((*lineIterator)->isArc())
			{
				/* This algorithm is not being used to accurately determine the arc within a closed contour
				 * with that said, we only need to approximately determine the area. For arcs, we shall draw
				 * a line from the first node to the mid point and then from the mid point to the second node.
				 * We will use these two lines as the calculation for the shoelace algorithm.
				 */ 
				additionTerms += ((*lineIterator)->getFirstNode()->getCenter().x) * ((*lineIterator)->getMidPoint().y);
				subtractionTerms += ((*lineIterator)->getMidPoint().x) * ((*lineIterator)->getFirstNode()->getCenter().y);
				
				additionTerms += ((*lineIterator)->getMidPoint().x) * ((*lineIterator)->getSecondNode()->getCenter().y);
				subtractionTerms += ((*lineIterator)->getSecondNode()->getCenter().x) * ((*lineIterator)->getMidPoint().y);
			}
			else
			{
				additionTerms += ((*lineIterator)->getFirstNode()->getCenter().x) * ((*lineIterator)->getSecondNode()->getCenter().y);
				subtractionTerms += ((*lineIterator)->getSecondNode()->getCenter().x) * ((*lineIterator)->getFirstNode()->getCenter().y);
			}
		}
		
		// Next, we need to run the shoe-lace algorithm to determine if the ordering is CCW or CW. If CW, then we will need to swap
		// the start node and end node of all of the edges in order to ensure the polygon edge is in CCW
		double shoelaceResult = additionTerms - subtractionTerms;
		
		if(shoelaceResult < 0)
			reverseWindingResult = true;
		
		// Now we can perform the winding number algorithm
		for(auto lineIterator = p_closedPath.begin(); lineIterator != p_closedPath.end(); lineIterator++)
		{
		
			if((*lineIterator)->isArc() && (*lineIterator)->getSwappedState())
				(*lineIterator)->swap();
				
			double isLeftResult = (*lineIterator)->isLeft(point);
				
			if(!(*lineIterator)->isArc())
			{
				if(reverseWindingResult)
					isLeftResult *= -1;
				
				if((*lineIterator)->getFirstNode()->getCenterYCoordinate() <= point.y)
				{
					if((*lineIterator)->getSecondNode()->getCenterYCoordinate() > point.y)
					{
						if(isLeftResult > 0)
							windingNumber++;
						else if(isLeftResult < 0)
							windingNumber--;
					}
				}
				else if((*lineIterator)->getSecondNode()->getCenterYCoordinate() <= point.y)
				{
					if(isLeftResult < 0)
						windingNumber--;
					else if(isLeftResult > 0)
						windingNumber++;
				}
				
			}
			else
			{
				if((*lineIterator)->getSwappedState())
				{
					isLeftResult *= -1;
					// For arcs, we need to preserve the orientation of the first and second
					// node for drawing purposes. Lines do not matter as much for drawing but arcs,
					// it matters
					(*lineIterator)->swap();
				}
				
				if(isLeftResult > 0)
					windingNumber++;
				else
					windingNumber--;
			}
		}
		
		if(windingNumber > 0)
			return true;
		else
			return false;
	}
	
	bool isInside(closedPath &compare)
	{
		bool pointFound = false;
		wxRealPoint comparePoint;
		std::map<node*, char> *compareVertexList = compare.getVertexList();
		
		for(auto lineIterator = p_closedPath.begin(); lineIterator != p_closedPath.end(); lineIterator++)
		{
			auto nodeExists = compareVertexList->find((*lineIterator)->getFirstNode());
			
			if(nodeExists == compareVertexList->end())
			{
				comparePoint = (*lineIterator)->getFirstNode()->getCenter();
				pointFound = true;
				break;
			}
			
			nodeExists = compareVertexList->find((*lineIterator)->getSecondNode());
			
			if(nodeExists == compareVertexList->end())
			{
				comparePoint = (*lineIterator)->getSecondNode()->getCenter();
				pointFound = true;
				break;
			}
		}
		
		if(pointFound)
			return compare.pointInContour(comparePoint);
		else
			return false;
	}
};

#endif