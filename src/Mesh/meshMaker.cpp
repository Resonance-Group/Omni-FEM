#include <Mesh/meshMaker.h>

void meshMaker::findContours()
{
	std::vector<std::vector<edgeLineShape>> returnPaths; // This is what is filled up with the paths
	std::vector<edgeLineShape> pathContour; // This list contains the initial path
	std::vector<edgeLineShape> branchStack; // the stack of branches
	
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
	
	bool closedContourFormed = false;
	
	do
	{
		std::vector<edgeLineShape> branches = getConnectedPaths(pathContour.back());
		
		// This part will check if any of the branches are already in the path contour vector.
		// If so, then this means a closed contour has been formed
		for(std::vector<edgeLineShape>::iterator listIterator = branches.begin(); listIterator != branches.end(); listIterator++)
		{
			for(std::vector<edgeLineShape>::iterator pathIterator = pathContour.begin(); pathIterator != pathContour.end(); pathIterator++)
			{
				if(*listIterator == *pathContour)
				{
					closedContourFormed = true;
					break;
				}
			}
			
			if(closedContourFormed)
				break;
		}
		
		if(!closedContourFormed)
		{
			pathContour.push_back(branches.at(0));// For now, we are going to assume that the first branch found is the next segment that creates the contour.
			
			// First we will seach through the stack to see if the added branch was already in the stack
			// If so, remove it from the stack
			for(std::vector<edgeLineShape>::iterator stackIterator = branchStack.begin(); stackIterator != branchStack.end(); stackIterator++)
			{
				if(branches.at(0) == *stackIterator)
				{
					branchStack.erase(stackIterator);
					break;
				}
			}
			
			branches.erase(branches.begin());
			
			// Now we are going to check if any of the branches are already in the stack
			// If so, then we do not need to add the branches to the stack later
			if(branches.size() > 0)
			{
				for(std::vector<edgeLineShape>::iterator stackIterator = branchStack.begin(); pathIterator != branchStack.end(); stackIterator++)
				{
					for(std::vector<edgeLineShape>::iterator branchIterator = branches.begin(); branchIterator != branches.end(); branchIterator++)
					{
						if(*branchIterator == *stackIterator)
						{
							branches.erase(branchIterator);
							break;
						}
					}
					
					// If all of the branches are already in the stack, then we can stop checking the stack
					if(branches.size() == 0)
						break;
				}
			}
			
			// If there are any branches left, then go ahead and add them to the stack
			if(branches.size() > 0)
			{
				branchStack.reserve(branchStack.size() + branches.size());// Increase to size of the stack by the number of branches.
				branchStack.insert(branchStack.end(), branches.begin(), branches.end());
			}
		}
	} while(!closedContourFormed)
	
	removeDanglingLines(pathContour);
	
	returnPaths.push_back(pathContour);
	
	while(branchStack.size() > 0)
	{
		pathContour.clear();
		pathContour.insert(*branchStack.begin());
		branchStack.erase(branchStack.begin());
	}
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
	unsigned int numberConnections = 0;
	for(std::vector<edgeLineShape>::iterator contourIterator = contour.begin(); contourIterator != contour.end(); contourIterator++)
	{
		/*
		 * Basically, the line itself and the line segment that the back is attached to
		 * Doesn't count since the previouse line segment in the list will always be
		 * attached to the one in back
		 */ 
		if(*contourIterator == *contour.back() || (*contourIterator == *(--contour.back())))
			continue;
		else
		{
			if(contourIterator->getFirstNode() == contour.back()->getFirstNode() || contourIterator->getSecondNode() == contour.back()->getFirstNode() || contourIterator->getFirstNode() == contour.back()->getSecondNode() || contourIterator->getSecondNode() == contour.back()->getSecondNode())
			{
				numberConnections++;
			}
			
			if(numberConnections == 2)// Dangling lines found!
			{
				contour.erase(contour.begin(), --contourIterator);
				break;
			}
		}
	}
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