#include <Mesh/meshMaker.h>

void meshMaker::findContours()
{
	std::vector<edgeLineShape> pathContour;
	std::vector<std::vector<edgeLineShape>> branchStack;
	
	// Find the first line segment that is not visited
	edgeLineShape lineFound;// This line segment is the first one that is found in order to start a new contour path
	bool lineIsFound = false; // Boolean used to indicate if a line or arc was found.
	for(plf::colony<edgeLineShape>::iterator lineIterator = p_lineList->begin(); lineIterator != p_lineList->end(); lineIterator++)
	{
		if(!lineIterator->getVisitedStatus())
		{
			lineFound = *lineIterator;
			lineIsFound = true;
			lineIterator->setVisitedStatus(true);
			p_numberVisited++;
		}
	}
	
	if(!lineFound)
	{
		for(plf::colony<arcShape>::iterator arcIterator = p_arcList->begin(); arcIterator != p_arcList->end(); arcIterator++)
		{
			if(!arcIterator->getVisitedStatus())
			{
				lineFound = *arcIterator;
				lineIsFound = true;
				arcIterator->setVisitedStatus(true);
				p_numberVisited++;
			}
		}
	}
	
	if(lineFound)
		pathContour.push_back(lineFound);
	else
	{
		// Do something if it fails
	}
	
	while(!pathContour.back()->getVisitedStatus())
	{
		std::vector<edgeLineShape> branches = getConnectedPaths(pathContour.back());
		
		// Now we have to scan through all of the branches to ensure that there is not one that has already been visited
		// If there is, then this means that we have come to the end of our path and a closed contour has formed
		for(std::vector<edgeLineShape>::iterator listIterator = branches.begin(); listIterator != branches.end(); listIterator++)
		{
			if(listIterator->getVisitedStatus())
			{
				pathContour.push_back(*listIterator);
				break;
			}
		}
		
		if(!pathContour.back()->getVisitedStatus())
		{
			pathContour.push_back(branches.at(0));
			
			if(branches.size() == 1)
				branches.clear();
			else
			{
				// Now we have to scan through the stack to make sure we don't add duplicates of the branches
				branches.erase(branches.begin());
				branchStack.push_back(branches);
			}
			
			// Now we have to scan through the stack in order to determine if any of the branch
		}
	}
	
	pathContour.erase(pathContour.back());
	
	// Now, we have to loop through both lists again in order to find the next edge and the branches
	
	
	
	
}



std::vector<edgeLineShape> getConnectedPaths(std::vector<edgeLineShape>::iterator &segment)
{
	std::vector<edgeLineShape> returnList;
	
	//Find all of the lines that are connected to the segment
	for(plf::colony<edgeLineShape>::iterator lineIterator = p_lineList->begin(); lineIterator != p_lineList->end(); lineIterator++)
	{
		if(*lineIterator == *segment)
			continue;
		
		// Checks to see if the first node on the line has already been scanned through for branches.
		// If so, then we need to move on to the second node.
		if(!segment->getFirstNode()->getVisitedState())
		{
			if(*segment->getFirstNode() == *lineIterator->getFirstNode() || *segment->getFirstNode() == *lineIterator->getSecondNode())
			{
				returnList.push_back(*lineIterator);
			}
		}
		else
		{
			if(*segment->getSecondNode() == *lineIterator->getFirstNode() || *segment->getSecondNode() == *lineIterator->getSecondNode())
			{
				returnList.push_back(*lineIterator);
			}
		}
	}
	
	// Find all of the arcs connected to the segment
	for(plf::colony<arcShape>::iterator arcIterator = p_arcList->begin(); arcIterator != p_arcList->end(); arcIterator++)
	{
		if(*arcIterator == *segment)
			continue;
		
		if(!segment->getFirstNode()->getVisitedState())
		{
			if(*segment->getFirstNode() == *arcIterator->getFirstNode() || *segment->getFirstNode() == *arcIterator->getSecondNode())
			{
				returnList.push_back(*arcIterator);
			}
		}
		else
		{
			if(*segment->getSecondNode() == *arcIterator->getFirstNode() || *segment->getSecondNode() == *arcIterator->getSecondNode())
			{
				returnList.push_back(*arcIterator);
			}
		}
	}
	
	if(!segment->getFirstNode()->getVisitedState())
		segment->getFirstNode()->setVisitedState(true);
	else
		segment->getSecondNode()->setVisitedState(true);
	
	return returnList;
}



void meshMaker::contourRecombination()
{
	
}



bool meshMaker::isClosedContour(std::vector<edgeLineShape> contour)
{
	
}



void meshMaker::removeDanglingLines(std::vector<edgeLineShape> &contour)
{
	
}



void meshMaker::findGeometry()
{
	while(p_numberofLines <= p_numberVisisted)
	{
		// TODO: Add in the code to find all of the closed contours.
		// TODO: Add in the code in order to add the contor(s) to the global list
	}
	
	// TODO: Check for an errors?
	// TODO: Add in the interface to the GMSH API
	// TODO: Mesh the model
	// TODO: Return the mesh. The function return is void for now
}