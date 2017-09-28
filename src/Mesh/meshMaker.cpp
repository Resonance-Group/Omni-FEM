#include <Mesh/meshMaker.h>

std::vector<std::vector<edgeLineShape>> meshMaker::findContours()
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
			break;
		}
	}
	
	if(!lineIsFound)
	{
		for(plf::colony<arcShape>::iterator arcIterator = p_arcList->begin(); arcIterator != p_arcList->end(); arcIterator++)
		{
			if(!arcIterator->getVisitedStatus())
			{
				lineFound = *arcIterator;
				lineIsFound = true;
				arcIterator->setVisitedStatus(true);
				p_numberVisited++;
				break;
			}
		}
	}
	
	if(lineIsFound)
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
				if(*listIterator == *pathIterator)
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
			bool lineSet = false;
			pathContour.push_back(branches.at(0));// For now, we are going to assume that the first branch found is the next segment that creates the contour.
			
			/* This section will loop through both lists to make sure that the line segment that was added to the 
			 * contour path is updated to be visited
			 */ 
			for(plf::colony<edgeLineShape>::iterator lineIterator = p_lineList->begin(); lineIterator != p_lineList->end(); lineIterator++)
			{
				if(*lineIterator == pathContour.back())
				{
					lineSet = true;
					lineIterator->setVisitedStatus(true);
					break;
				}
			}
			
			if(!lineSet)
			{
				for(plf::colony<arcShape>::iterator lineIterator = p_arcList->begin(); lineIterator != p_arcList->end(); lineIterator++)
				{
					if(*lineIterator == pathContour.back())
					{
						lineSet = true;
						lineIterator->setVisitedStatus(true);
						break;
					}
				}
			}
			
			// First we will seach through the stack to see if the added branch was already in the stack
			// If so, remove it from the stack
			for(std::vector<edgeLineShape>::iterator stackIterator = branchStack.begin(); stackIterator != branchStack.end();)
			{
				if(branches.at(0) == *stackIterator)
				{
					if(*stackIterator == branchStack.back())
					{
						branchStack.clear();
						break;
					}
					else
						branchStack.erase(stackIterator++);
				}
				else
					stackIterator++;
			}
			
			branches.erase(branches.begin());// Now that the first element in the branches has been added to the path, we can remove it from the branches
			
			// Now we are going to check if any of the branches are already in the stack
			// If so, then we do not need to add the branches to the stack later
			if(branches.size() > 0)
			{
				for(std::vector<edgeLineShape>::iterator stackIterator = branchStack.begin(); stackIterator != branchStack.end(); stackIterator++)
				{
					for(std::vector<edgeLineShape>::iterator branchIterator = branches.begin(); branchIterator != branches.end();)
					{
						if(*branchIterator == *stackIterator)
						{
							if(*branchIterator == branches.back())
							{
								branches.clear();
								break;
							}
							else
								branches.erase(branchIterator++);
						}
						else
							branchIterator++;
					}
					
					// If all of the branches are already in the stack, then we can stop checking the stack
					if(branches.size() == 0)
						break;
				}
			}
			
			// If there are any branches left, then go ahead and add them to the stack
			if(branches.size() > 0)
			{
				branchStack.reserve(branchStack.size() + branches.size());// Increase the size of the stack by the number of branches.
				branchStack.insert(branchStack.end(), branches.begin(), branches.end());
			}
		}
	} while(!closedContourFormed);
	
	removeDanglingLines(pathContour);
	
	returnPaths.push_back(pathContour);
	
	while(branchStack.size() > 0)
	{
		closedContourFormed = false;
		
		pathContour.clear();
		
		// Now we have to find the back path of the branch in order to add it to the new path vector
		for(int i = 0; i < returnPaths.size(); i++)
		{
			bool backPathFound = false;
			/*
			 * Starting from the previous path, we are going to loop through all of the lines 
			 * to see if the branch is connected to one of the lines of the previous contour. 
			 * If there is a common node, then this will save time. If not, then it will take a minute to 
			 * complete
			 */ 
			std::vector<edgeLineShape> tempPath = returnPaths[returnPaths.size() - i];
			for(std::vector<edgeLineShape>::iterator pathIterator = tempPath.begin(); pathIterator != tempPath.end(); pathIterator++)
			{
				if(	pathIterator->getFirstNode() == branchStack.begin()->getFirstNode() || 
					pathIterator->getSecondNode() == branchStack.begin()->getFirstNode() || 
					pathIterator->getFirstNode() == branchStack.begin()->getSecondNode() || 
					pathIterator->getSecondNode() == branchStack.begin()->getSecondNode() )
				{
					// If the branch is connected to one of the nodes on the path, then we have found the back path!
					// Next, we add in the back path to the paht contour
					// and from there add in the branch.
					pathContour.assign(tempPath.begin(), pathIterator);
					// Now we pop the first branch from the branch stack 
					pathContour.push_back(*branchStack.begin());
					
					branchStack.erase(branchStack.begin());
					
					backPathFound = true;
					
					break;
				}
			}
			
			if(backPathFound)
				break;
		}
		
		// Now that the back path has been found, we can procced to find the next connected edge
		// To do this, the search will be similiar to above
		do
		{
			std::vector<edgeLineShape> branches = getConnectedPaths(pathContour.back());
			
			// This part will check if any of the branches are already in the path contour vector.
			// If so, then this means a closed contour has been formed
			for(std::vector<edgeLineShape>::iterator listIterator = branches.begin(); listIterator != branches.end(); listIterator++)
			{
				for(std::vector<edgeLineShape>::iterator pathIterator = pathContour.begin(); pathIterator != pathContour.end(); pathIterator++)
				{
					if(*listIterator == *pathIterator)
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
				bool lineUpdated = false;
				pathContour.push_back(branches.at(0));// For now, we are going to assume that the first branch found is the next segment that creates the contour.
				
				/* This section will loop through both lists to make sure that the line segment that was added to the 
				 * contour path is updated to be visited
				 */ 
				for(plf::colony<edgeLineShape>::iterator lineIterator = p_lineList->begin(); lineIterator != p_lineList->end(); lineIterator++)
				{
					if(*lineIterator == *(pathContour.end()--))
					{
						lineUpdated = true;
						lineIterator->setVisitedStatus(true);
						p_numberVisited++;
						break;
					}
				}
				
				if(!lineUpdated)
				{
					for(plf::colony<arcShape>::iterator arcIterator = p_arcList->begin(); arcIterator != p_arcList->end(); arcIterator++)
					{
						if((edgeLineShape)*arcIterator == *(pathContour.end()--))
						{
							lineUpdated = true;
							arcIterator->setVisitedStatus(true);
							p_numberVisited++;
							break;
						}
					}
				}
				
				// First we will seach through the stack to see if the added branch was already in the stack
				// If so, remove it from the stack
				for(std::vector<edgeLineShape>::iterator stackIterator = branchStack.begin(); stackIterator != branchStack.end(); stackIterator++)
				{
					if(branches.at(0) == *stackIterator)
					{
						if(*stackIterator == branchStack.back())
						{
							branchStack.clear();
							break;
						}
						else
							branchStack.erase(stackIterator++);
					}
					else
						stackIterator++;
				}
				
				branches.erase(branches.begin());// Now that the first element in the branches has been added to the path, we can remove it from the branches
				
				// Now we are going to check if any of the branches are already in the stack
				// If so, then we do not need to add the branches to the stack later
				if(branches.size() > 0)
				{
					for(std::vector<edgeLineShape>::iterator stackIterator = branchStack.begin(); stackIterator != branchStack.end(); stackIterator++)
					{
						for(std::vector<edgeLineShape>::iterator branchIterator = branches.begin(); branchIterator != branches.end();)
						{
							if(*branchIterator == *stackIterator)
							{
								if(*branchIterator == branches.back())
								{
									branches.clear();
									break;
								}
								else
									branches.erase(branchIterator++);
							}
							else
								branchIterator++;
						}
						
						// If all of the branches are already in the stack, then we can stop checking the stack
						if(branches.size() == 0)
							break;
					}
				}
				
				// If there are any branches left, then go ahead and add them to the stack
				if(branches.size() > 0)
				{
					branchStack.reserve(branchStack.size() + branches.size());// Increase the size of the stack by the number of branches.
					branchStack.insert(branchStack.end(), branches.begin(), branches.end());
				}
			}
		}while(!closedContourFormed);
		
		// Once a closed path has been found, we then need to make sure that the path is actually a closed contour
		// by removing any dangling lines which are lines that are in the path but do not make up the closed contour
		// Then, we add the path to the return vector.
		removeDanglingLines(pathContour);
		returnPaths.push_back(pathContour);
	}
	
	return returnPaths;
}



std::vector<edgeLineShape> meshMaker::getConnectedPaths(std::vector<edgeLineShape>::reference segment)
{
	
	std::vector<edgeLineShape> returnList;
	
	//Find all of the lines that are connected to the segment
	for(plf::colony<edgeLineShape>::iterator lineIterator = p_lineList->begin(); lineIterator != p_lineList->end(); lineIterator++)
	{
		if(*lineIterator == segment)
		{
			if(!lineIterator->getFirstNode()->getVisitedState())
				lineIterator->getFirstNode()->setVisitedState(true);
			else
				lineIterator->getSecondNode()->setVisitedState(true);
				
			continue;
		}
		
		// Checks to see if the first node on the line has already been scanned through for branches.
		// If so, then we need to move on to the second node.
		// If both of the nodes for the segment have already been visited then we can go ahead and
		// skip that segment
		if(!segment.getFirstNode()->getVisitedState())
		{
			if(*segment.getFirstNode() == *lineIterator->getFirstNode() || *segment.getFirstNode() == *lineIterator->getSecondNode())
			{
				returnList.push_back(*lineIterator);
			}
		}
		else if(!segment.getSecondNode()->getVisitedState())
		{
			if(*segment.getSecondNode() == *lineIterator->getFirstNode() || *segment.getSecondNode() == *lineIterator->getSecondNode())
			{
				returnList.push_back(*lineIterator);
			}
		}
	}
	
	// Find all of the arcs connected to the segment
	for(plf::colony<arcShape>::iterator arcIterator = p_arcList->begin(); arcIterator != p_arcList->end(); arcIterator++)
	{
		if(arcIterator->getArcID() == segment.getArcID())
		{
			if(!arcIterator->getFirstNode()->getVisitedState())
				arcIterator->getFirstNode()->setVisitedState(true);
			else
				arcIterator->getSecondNode()->setVisitedState(true);
				
			continue;
		}
		
		if(!segment.getFirstNode()->getVisitedState())
		{
			if(*segment.getFirstNode() == *arcIterator->getFirstNode() || *segment.getFirstNode() == *arcIterator->getSecondNode())
			{
				returnList.push_back(*arcIterator);
			}
		}
		else
		{
			if(*segment.getSecondNode() == *arcIterator->getFirstNode() || *segment.getSecondNode() == *arcIterator->getSecondNode())
			{
				returnList.push_back(*arcIterator);
			}
		}
	}
	
	
	
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
		std::vector<edgeLineShape>::iterator temp = contour.end() - 2;
		if(*contourIterator == *(contour.end()--) || (*contourIterator == *(temp)))
			continue;
		else
		{
			if(	*contourIterator->getFirstNode() == *contour.back().getFirstNode() || 
				*contourIterator->getSecondNode() == *contour.back().getFirstNode() || 
				*contourIterator->getFirstNode() == *contour.back().getSecondNode() || 
				*contourIterator->getSecondNode() == *contour.back().getSecondNode() )
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
	while(p_numberofLines >= p_numberVisited)
	{
		std::vector<std::vector<edgeLineShape>> temp = findContours();
		p_closedContours.reserve(p_closedContours.size() + temp.size());
		p_closedContours.insert(p_closedContours.end(), temp.begin(), temp.end());
		// TODO: Add in the code to find all of the closed contours.
		// TODO: Add in the code in order to add the contor(s) to the global list
	}
	
	// TODO: Check for an errors?
	// TODO: Add in the interface to the GMSH API
	// TODO: Mesh the model
	// TODO: Return the mesh. The function return is void for now
}