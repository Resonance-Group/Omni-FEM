#include <Solver/ElectrostaticSolver2.h>

void ElectroStaticSolver::run()
{
	
}



void ElectroStaticSolver::setupGrid()
{
	for(auto cellIterator = triangulation.getTriangulation()->begin_active(); cellIterator != triangulation.getTriangulation()->end(); celIterator++)
	{
		closedPath closedContour;
		
		for(auto contourIterator = p_closedPath->begin(); contourIterator != p_closedPath->end(); contourIterator++)
		{
			wxRealPoint cellCenter = wxRealPoint(cellIterator->center()(0), cellIterator->center()(1));
			
			if(contourIterator->pointInBoundingBox(cellCenter))
			{
				// If the center of the triagulation is inside of the bounding box, we need to check if the 
				// center is inside of the actual contour
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
						cellIterator->set_material_ID(contourIterator->getProperty()->getElectricalMaterial()->getMaterialID());
						
						// Now, we need to check if a face of the triagulation cell is on a boundary of the contour
						// If so, we need to set the boundary ID accordingly
						for(unsigned int f = 0; f < GeometryInfo<2>::faces_per_cell; f++)
						{
							for(auto edgeIterator = contourIterator->getClosedPath()->begin(); edgeIterator != contourIterator->getClosedPath()->end(); edgeIterator++)
							{
								if(CommonSolverFunctions::faceLiesOnBoundary(cellIterator->face(f), *edgeIterator))
								{
									edgeLineShape *edge = *edgeIterator;
									cellIterator->face(f)->set_boundary_id(edge->getSegmentProperty()->getElectricalBoundary()->getBoundaryID());
								}
							}
						}
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