#include <Mesh/meshMaker.h>

void meshMaker::findContours()
{
	edgeLineShape lineFound;// This line segment is the first one that is found in order to start a new contour path
	bool lineIsFound = false; // Boolean used to indicate if a line or arc was found.
	for(plf::colony<edgeLineShape>::iterator lineIterator = p_lineList->begin(); lineIterator != p_lineList->end(); lineIterator++)
	{
		if(!lineIterator->getVisitedStatus())
		{
			lineFound = *lineIterator;
			lineIsFound = true;
			lineIterator->setVisitedStatus(true);
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
			}
		}
	}
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