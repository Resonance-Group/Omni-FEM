#include <Solver/ElectrostaticSolver.h>

void ElectroStaticSolver::run()
{
	
}



void ElectroStaticSolver::setupGrid()
{
	for(auto cellIterator = triangulation.getTriangulation().begin_active(); cellIterator != triangulation.getTriangulation().end(); celIterator++)
	{
		closedPath closedContour;
		
		for(auto contourIterator = p_closedPath->begin(); contourIterator != p_closedPath->end(); contourIterator++)
		{
			// Call function that will check if the mesh center is inside of the contour
			wxRealPoint cellCenter = wxRealPoint(cellIterator->center()(0), cellIterator->center()(1));
			
			if(contourIterator->pointInBoundingBox(cellCenter))
			{
				if(contourIterator->pointInContour(cellCenter))
				{
					bool cellLiesInHole = false;
					
					for(auto holeIterator = contourIterator->getHoles()->begin(); holeIterator != contourIterator->getHoles()->end(); holeIterator++)
					{
						if(holeIterator->pointInContour(cellCenter))
						{
							cellLiesInHole = tue;
							break;
						}
					}
					
					if(!cellLiesInHole)
					{
						cellIterator->set_material_ID(contourIterator->get)
					}
					
				}
			}
		}
	}
}



void ElectroStaticSolver::setupSystem()
{
	
}



void ElectroStaticSolver::assembleSystem()
{
	
}



void ElectroStaticSolver::solveSystem()
{
	
}



void ElectroStaticSolver::resultsProcessing()
{
	
}