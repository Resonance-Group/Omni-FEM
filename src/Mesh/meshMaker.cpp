#include <Mesh/meshMaker.h>

#include <common/OmniFEMMessage.h>

#include <iterator>

#include <wx/dir.h>


closedPath meshMaker::findContour(edgeLineShape *startingEdge, rectangleShape *point)
{
	closedPath foundPath;
	std::vector<closedPath> pathsVector;
	
	// Find the first line segment that is not visited
	if(startingEdge == nullptr)
	{
		bool lineIsFound = false; // Boolean used to indicate if a line or arc was found.
		for(plf::colony<edgeLineShape>::iterator lineIterator = p_lineList->begin(); lineIterator != p_lineList->end(); lineIterator++)
		{
			if(!lineIterator->getVisitedStatus() && !lineIterator->getSegmentProperty()->getHiddenState())
			{
				pathsVector.push_back(closedPath(*lineIterator));
				lineIsFound = true;
				break;
			}
		}
		
		if(!lineIsFound)
		{
			for(plf::colony<arcShape>::iterator arcIterator = p_arcList->begin(); arcIterator != p_arcList->end(); arcIterator++)
			{
				if(!arcIterator->getVisitedStatus() && !arcIterator->getSegmentProperty()->getHiddenState())
				{
					pathsVector.push_back(closedPath(*arcIterator));
					lineIsFound = true;
					break;
				}
			}
		}
	}
	else
		pathsVector.push_back(closedPath(startingEdge));
	
	while(pathsVector.size() != 0)
	{
		for(std::vector<closedPath>::iterator pathIterator = pathsVector.begin(); pathIterator != pathsVector.end();)
		{
			if(foundPath.getDistance() == 0 || pathIterator->getDistance() < foundPath.getDistance())
			{
				bool closedContourFound = false;
				bool branchInPaths = false;
				
				std::vector<edgeLineShape*> branches = getConnectedPaths(pathIterator->getClosedPath()->back(), pathIterator->getClosedPath());
				
				if(branches.size() == 0)
				{
					// This means that we have an error in the path
					// usually caused by a path not forming a closed loop
					// This occurs if the path has no branches attached to it
					if(pathsVector.size() > 1)
					{
						pathsVector.erase(pathIterator);
						break;
					}
					else
					{
						return pathsVector.at(0);
					}
				}
				
				// Test to see if a closed contour is found
				// A closed contour occurs when one of the branches 
				// is the beginning edge of the closed path
				for(auto branchIterator = branches.begin(); branchIterator != branches.end(); branchIterator++)
				{
					if(**branchIterator == **(pathIterator->getClosedPath()->begin()))
					{
						closedContourFound = true;
						break;
					}
					else if(**branchIterator == *(pathIterator->getClosedPath()->back()))
					{
						branches.erase(branchIterator);
						branchIterator = branches.begin();
					}
				}
				
				/* This will test if any branch loops back to the path where the loop is connected to a segment after the 
				 * begining segment of the path.
				 * On the start, this for loop will skip the first edge in the closed path becuase that is the 
				 * trivial solution
				 */ 
				for(auto pathEdgeIterator = ++(pathIterator->getClosedPath()->begin()); pathEdgeIterator != pathIterator->getClosedPath()->end(); pathEdgeIterator++)
				{
					for(auto branchIterator = branches.begin(); branchIterator != branches.end();branchIterator++)
					{
						if(**pathEdgeIterator == **branchIterator)
						{
							// This means that the path has looped back on itself
							branchInPaths = true;
							break;
						}
					}
					
					if(branchInPaths)
						break;
				}
				
				if(branchInPaths)
				{
					pathsVector.erase(pathIterator);
					break;
				}
				else if(closedContourFound || branches.size() == 0)
				{
					// If found, we are going to test if the 
					// found contour's distance is less then the current found path
					// distance
					if(point == nullptr && (pathIterator->getDistance() < foundPath.getDistance() || foundPath.getDistance() == 0))
					{
						foundPath = *pathIterator;
					}
					else if(checkPointInContour(*point, *pathIterator) && (pathIterator->getDistance() < foundPath.getDistance() || foundPath.getDistance() == 0))
					{
						foundPath = *pathIterator;
					}

					pathsVector.erase(pathIterator);
					break;
				}
				else
				{

					// If the size of the branches is greater then 1, then we found some additional possible paths
					// Create another closed path object and add them to the paths vector as possible
					// solutions to finding the shortest path.
					if(branches.size() > 1)
					{
						closedPath masterPath = *pathIterator;
						
						pathIterator->addEdgeToPath(*branches.begin());
						branches.erase(branches.begin());
						
						while(branches.size() != 0)
						{
							closedPath addedPath = masterPath;
							
							addedPath.addEdgeToPath(*branches.begin());
							pathsVector.push_back(addedPath);
							branches.erase(branches.begin());
						}
						break;
					}
					else if(branches.size() == 1)
					{
						// Otherwise, add the one branch to the current path
						pathIterator->addEdgeToPath(*branches.begin());
						branches.clear();
					}
					
					pathIterator++;
					continue;
				}
			}
			else
			{
				// Since the path is no the shortest path,
				// remove the path from the vector
				pathsVector.erase(pathIterator);
				break;
			}
		}
	}
	
	return foundPath;
}


std::vector<edgeLineShape*> meshMaker::getConnectedPaths(std::vector<edgeLineShape*>::reference currentSegment, std::vector<edgeLineShape*> *pathVector)
{
	std::vector<edgeLineShape*> returnList;
	node *branchNode;
	std::vector<edgeLineShape*>::iterator previousAddedSegment;
	
	edgeLineShape *previouseSegmentPointer;
	edgeLineShape *currentSegmentPointer = currentSegment; // This part may not be necessary but it helps with the thinking
	
	int pathSize = pathVector->size();
	
	if(pathVector->size() >= 2)
		previousAddedSegment = pathVector->end() - 2;
	else
		previousAddedSegment = pathVector->begin();
		
	previouseSegmentPointer = *previousAddedSegment;
	
	// Determines what node we should be looking at
	if(pathVector->size() >= 2)
	{
		// FInd out which node is connected to the back
		if((*(currentSegmentPointer->getFirstNode()) == *(previouseSegmentPointer->getFirstNode())) || (*(currentSegmentPointer->getFirstNode()) == *(previouseSegmentPointer->getSecondNode())))
			branchNode = currentSegmentPointer->getSecondNode();
		else
			branchNode = currentSegmentPointer->getFirstNode();
	}
	else
		branchNode = currentSegmentPointer->getFirstNode();// This is the case for the very first segment added
	
	//Find all of the lines that are connected to the segment
	for(plf::colony<edgeLineShape>::iterator lineIterator = p_lineList->begin(); lineIterator != p_lineList->end(); lineIterator++)
	{
		// Perform check to make sure that the segment and the previously added segment are not included
		// Perform check to make sure that the segment is not hidden
		if(*lineIterator == *currentSegmentPointer || (pathVector->size() > 1 && (*lineIterator == *previouseSegmentPointer)) && !lineIterator->getSegmentProperty()->getHiddenState())
			continue;
		
		// Checks to see if the first node on the line has already been scanned through for branches.
		// If so, then we need to move on to the second node.
		// If both of the nodes for the segment have already been visited then we can go ahead and
		// skip that segment
		if(((*branchNode == *lineIterator->getFirstNode()) || (*branchNode == *lineIterator->getSecondNode())) && lineIterator->getSegmentProperty()->getHiddenState())
		{
			returnList.push_back(&(*lineIterator));
		}
	}
	
	// Find all of the arcs connected to the segment
	for(plf::colony<arcShape>::iterator arcIterator = p_arcList->begin(); arcIterator != p_arcList->end(); arcIterator++)
	{
		if((arcIterator->getArcID() == currentSegmentPointer->getArcID()) || (pathVector->size() > 1 && arcIterator->getSegmentProperty()->getHiddenState()))
			continue;
			
		if((*branchNode == *arcIterator->getFirstNode()) || (*branchNode == *arcIterator->getSecondNode()))
		{
			returnList.push_back(&(*arcIterator));
		}
	}
	
	return returnList;
}



bool meshMaker::checkPointInContour(wxRealPoint point, closedPath path)
{
	int windingNumber = 0;
	for(auto lineIterator = path.getClosedPath()->begin(); lineIterator != path.getClosedPath()->end(); lineIterator++)
	{
		bool reverseDirection = false;
		
		if((*lineIterator)->isLeft(path.getCenter()) < 0)
			reverseDirection = true; // THis indicates that the direction of the path is clockwise
			
		double isLeftResult = (*lineIterator)->isLeft(point);
		
		if(reverseDirection)
			isLeftResult *= -1;
			
		if(!(*lineIterator)->isArc())
		{
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


void meshMaker::mesh()
{
	bool meshCreated = false;
	unsigned int blockLabelsUsed = 0;

	GmshInitialize();
	
	/* These are settings that will remain constant */
	
	CTX::instance()->mesh.recombinationTestNewStrat = 0;
	CTX::instance()->mesh.nProc = 0;
	CTX::instance()->mesh.nbProc = 0;
	CTX::instance()->lc = 2.5;
	
	CTX::instance()->mesh.algoSubdivide = 1; // The 1 here is to specify that we are only concerned with quads
	CTX::instance()->mesh.secondOrderIncomplete = 0; // Always use complete meshes
	CTX::instance()->mesh.lcExtendFromBoundary = 1; // By setting to 1 the mesh size will extend from the boundary. This needs more research. This maybe an option that the user speficies
	CTX::instance()->mesh.recombineAll = 1; // Make sure to recombine all triangles into quads
	
	CTX::instance()->mesh.algo3d = 1; // Not really necessary?
	CTX::instance()->mesh.lcFromPoints = 0;// Obtain the characteristic length from the nodes (This doesn't work too well)
	CTX::instance()->mesh.lcFromCurvature = 1;// Obtain the characteristic length (mesh size) from the edges of the face (This works better)
	
	/* These are the settings that are set by the user */
	
	CTX::instance()->mesh.optimizeLloyd = p_settings->getLlyodSmoothingSteps();
	CTX::instance()->mesh.multiplePasses = p_settings->getMultiplePasses();
	
	switch(p_settings->getRemeshParameter())
	{
		case MeshParametrization::MESH_PARAM_HARMONIC:
			CTX::instance()->mesh.remeshParam = 0;
			break;
		case MeshParametrization::MESH_PARAM_CONFORMAL:
			CTX::instance()->mesh.remeshParam = 1;
			break;
		case MeshParametrization::MESH_PARAM_RBFHARMONIC:
			CTX::instance()->mesh.remeshParam = 2;
			break;
	}
	
	if(p_settings->getAutoRemeshingState())
		CTX::instance()->mesh.remeshAlgo = 1;
	else
		CTX::instance()->mesh.remeshAlgo = 0;
		
	switch(p_settings->getMeshAlgorithm())
	{
		case MeshAlgorthim::MESH_ALGO_AUTOMATIC:
			CTX::instance()->mesh.algo2d = ALGO_2D_AUTO;
			break;
		case MeshAlgorthim::MESH_ALGO_MESHADAPT:
			CTX::instance()->mesh.algo2d = ALGO_2D_MESHADAPT;
			break;
		case MeshAlgorthim::MESH_ALGO_DELAUNAY:
			CTX::instance()->mesh.algo2d = ALGO_2D_DELAUNAY;
			break;
		case MeshAlgorthim::MESH_ALGO_FRONTAL:
			CTX::instance()->mesh.algo2d = ALGO_2D_FRONTAL;
			break;
	}
	
	if(p_settings->getBlossomRecombinationState())
		CTX::instance()->mesh.algoRecombine = 1; // Setting to one will cause the program to perform the blossom algorthim for recombination
	else
		CTX::instance()->mesh.algoRecombine = 0;
		
	CTX::instance()->mesh.nbSmoothing = (int)p_settings->getSmoothingSteps();
	
	CTX::instance()->mesh.lcFactor = p_settings->getElementSizeFactor();
	CTX::instance()->mesh.lcMin = p_settings->getMinElementSize();
	CTX::instance()->mesh.lcMax = p_settings->getMaxElementSize();
	
	CTX::instance()->mesh.order = p_settings->getElementOrder();
	
	OmniFEMMsg::instance()->MsgStatus("Creating GMSH Geometry from Omni-FEM geometry");
	OmniFEMMsg::instance()->MsgStatus("Finding contours");
	
	while(p_numberVisited < p_numberofLines)
	{
		closedPath contourPath = findContour();
		
		for(std::vector<edgeLineShape*>::iterator edgeIterator = contourPath.getClosedPath()->begin(); edgeIterator != contourPath.getClosedPath()->end(); edgeIterator++)
		{
			if(!(*edgeIterator)->getVisitedStatus())
			{
				(*edgeIterator)->setVisitedStatus(true);
				p_numberVisited++;
			}
		}
		
		/* All empty paths indicate that there was an error. This error usually results from
		 * the path not being a closed path.
		 * In this case, we skip the path and move on to the next one
		 */ 
		if(isClosedPath(*contourPath.getClosedPath()))
		{
			for(auto blockIterator = p_blockLabelList->begin(); blockIterator != p_blockLabelList->end(); blockIterator++)
			{
				if(contourPath.pointInBoundingBox(blockIterator->getCenter()))
				{
					if(checkPointInContour(blockIterator->getCenter(), contourPath))
					{
						contourPath.addBlockLabel(*blockIterator);
					}
				}
			}
			
			p_closedContourPaths.push_back(contourPath);// The path will only be pushed to the master list if it is a closed path
		}
		else
		{
			OmniFEMMsg::instance()->MsgError("Open Path Found. Skipping and moving to the next path");
		}
	}
	
	if(p_closedContourPaths.size() > 0)
	{
		OmniFEMMsg::instance()->MsgStatus("Contours found");

		contextMeshOptions testMesh = CTX::instance()->mesh;
		
		/* Now we go to conver Omni-FEM's geometry data structure into the data structure for GMSH */
		// lcFactor->0.29999999999 lcExtendFromBoundary->1 algo3D-> 1
		OmniFEMMsg::instance()->MsgStatus("Verfied Mesh");

		p_meshModel->setFactory("Gmsh");
		
		OmniFEMMsg::instance()->MsgStatus("Adding in GMSH Vertices");
		
		for(auto nodeIterator = p_nodeList->begin(); nodeIterator != p_nodeList->end(); nodeIterator++)
		{
			GVertex *temp = p_meshModel->addVertex(nodeIterator->getCenterXCoordinate(), nodeIterator->getCenterYCoordinate(), 0.0, 1.0);
			nodeIterator->setGModalTagNumber(temp->tag());
		}
		
		/* Now we create the faces */
		OmniFEMMsg::instance()->MsgStatus("Adding in GMSH faces");
		
		holeDetection();
		
		assignBlockLabel();
		
		createGMSHGeometry();
		
		if(p_blockLabelsUsed < p_blockLabelList->size())
		{
			std::vector<closedPath> additionalPaths;
			
			for(auto blockIterator = p_blockLabelList->begin(); blockIterator != p_blockLabelList->end(); blockIterator++)
			{
				if(!blockIterator->getUsedState())
				{
					// Speed here could be improved upon?
					closedPath foundPath;
					edgeLineShape *startEdge = nullptr;
					bool existsInGeometry = false;
					std::multimap<double, edgeLineShape*> sortedEdges;
					
					for(auto closedPathIterator = p_closedContourPaths.begin(); closedPathIterator != p_closedContourPaths.end(); closedPathIterator++)
					{
						closedPath temp = *closedPathIterator;
						if(checkPointInContour(blockIterator->getCenter(), temp))
						{
							existsInGeometry = true;
							break;
						}
					}
					
					if(existsInGeometry)
					{
						/* This next section will organize all of the edges of the geometry in asending order based on the 
						 * distance of the block label to the midpoint of the edge
						 */ 
						for(auto lineIterator = p_lineList->begin(); lineIterator != p_lineList->end(); lineIterator++)
						{
							double distance = blockIterator->getDistance(lineIterator->getMidPoint());
							
							sortedEdges.insert(std::pair<double, edgeLineShape*>(distance, &(*lineIterator)));
						}
						
						for(auto arcIterator = p_arcList->begin(); arcIterator != p_arcList->end(); arcIterator++)
						{
							double distance = blockIterator->getDistance(arcIterator->getMidPoint());
							
							sortedEdges.insert(std::pair<double, edgeLineShape*>(distance, &(*arcIterator)));
						}
					
						for(auto mapIterator = sortedEdges.begin(); mapIterator != sortedEdges.end(); mapIterator++)
						{
							closedPath possiblePath = findContour((*mapIterator).second, &(*blockIterator));
							
							if(possiblePath.getDistance() > 0)
							{
								// THe first valid path found will be the path that encompasses the label
								foundPath = possiblePath;
								break;
							}
						}
						
						// Since we found a path that encompasses the label, set the property of that path to the label
						if(foundPath.getDistance() > 0)
						{
							foundPath.setProperty(blockIterator->getProperty());
							additionalPaths.push_back(foundPath);
						}
					}
					else
					{
						OmniFEMMsg::instance()->MsgWarning("Block Label outside of geoemtry found");
					}
					
					p_blockLabelsUsed++;
					blockIterator->setUsedState(true);
				}
			}
			
			if(additionalPaths.size() > 0)
			{
				holeDetection(&additionalPaths);
				
				createGMSHGeometry(&additionalPaths);
				
				p_closedContourPaths.reserve(p_closedContourPaths.size() + additionalPaths.size());
				
				p_closedContourPaths.insert(p_closedContourPaths.end(), additionalPaths.begin(), additionalPaths.end());
			}
		}
		
		OmniFEMMsg::instance()->MsgStatus("Meshing GMSH geometry");
		
		for(int i = 0; i < CTX::instance()->mesh.multiplePasses; i++)
		{
			OmniFEMMsg::instance()->MsgStatus("Performing pass " + std::to_string(i + 1) + " of " + std::to_string(CTX::instance()->mesh.multiplePasses));
			p_meshModel->mesh(2);
		}
		
		// Next set any output mesh options
		// such as different files to output the mesh. Be it VTK or some other format
		OmniFEMMsg::instance()->MsgStatus("Saving Mesh file");
		
		wxDir validDir;
		
		if(p_settings->getDirString() != wxString("") && validDir.Open(p_settings->getDirString()))
		{
			validDir.Close();
			
			if(p_settings->getSaveVTKState())
				p_meshModel->writeVTK(p_settings->getDirString().ToStdString() + "/" + p_simulationName.ToStdString() + ".vtk");
			
			if(p_settings->getSaveBDFState())
				p_meshModel->writeBDF(p_settings->getDirString().ToStdString() + "/" + p_simulationName.ToStdString() + ".bdf"); // double check this one
			
			if(p_settings->getSaveCELUMState())
				p_meshModel->writeCELUM(p_settings->getDirString().ToStdString() + "/" + p_simulationName.ToStdString() + ".celum", false, 1.0);
				
			if(p_settings->getSaveDIFFPACKSate())
				p_meshModel->writeDIFF(p_settings->getDirString().ToStdString() + "/" + p_simulationName.ToStdString() + ".diff", false, false, 1.0);
				
			if(p_settings->getSaveGEOState())
				p_meshModel->writeGEO(p_settings->getDirString().ToStdString() + "/" + p_simulationName.ToStdString() + ".geo", true, false);
				
			if(p_settings->getSaveINPState())
				p_meshModel->writeINP(p_settings->getDirString().ToStdString() + "/" + p_simulationName.ToStdString() + ".inp", false, false, 1.0);
			
			if(p_settings->getSaveIR3State())
				p_meshModel->writeIR3(p_settings->getDirString().ToStdString() + "/" + p_simulationName.ToStdString() + ".ir3", 0, true, 1.0);
				
			if(p_settings->getSaveMAILState())
				p_meshModel->writeMAIL(p_settings->getDirString().ToStdString() + "/" + p_simulationName.ToStdString() + ".mail", true, 1.0);
				
			if(p_settings->getSaveMESHState())
				p_meshModel->writeMESH(p_settings->getDirString().ToStdString() + "/" + p_simulationName.ToStdString() + ".mesh", 1, false, 1.0);
		
			if(p_settings->getSaveP3DState())
				p_meshModel->writeP3D(p_settings->getDirString().ToStdString() + "/" + p_simulationName.ToStdString() + ".p3d", false, 1.0);

			if(p_settings->getSavePartitionedMeshState())
				p_meshModel->writePartitionedMSH(p_settings->getDirString().ToStdString() + "/" + p_simulationName.ToStdString() + ".mesh", 2.2, false, false, false, 1.0);
				
			if(p_settings->getSavePLY2State())
				p_meshModel->writePLY2(p_settings->getDirString().ToStdString() + "/" + p_simulationName.ToStdString() + ".ply2");
				
			if(p_settings->getSaveSTLState())
				p_meshModel->writeSTL(p_settings->getDirString().ToStdString() + "/" + p_simulationName.ToStdString() + ".stl", false, false, 1.0);
				
			if(p_settings->getSaveTochnogState())
				p_meshModel->writeTOCHNOG(p_settings->getDirString().ToStdString() + "/" + p_simulationName.ToStdString() + ".toc", false, false, 1.0);
				
			if(p_settings->getSaveSU2State())
				p_meshModel->writeSU2(p_settings->getDirString().ToStdString() + "/" + p_simulationName.ToStdString() + ".su2", true, 1.0);
				
			if(p_settings->getSaveUNVState())
				p_meshModel->writeUNV(p_settings->getDirString().ToStdString() + "/" + p_simulationName.ToStdString() + ".unv", false, false, 1.0);
				
			if(p_settings->getSaveVRMLState())
				p_meshModel->writeVRML(p_settings->getDirString().ToStdString() + "/" + p_simulationName.ToStdString() + ".vrml", true, 1.0);
		}
	}
	else
	{
		OmniFEMMsg::instance()->MsgError("No closed paths were found");
	}
	
	// THis is the file that the solver uses for meshing
//	p_meshModel->writeMSH(p_folderPath.ToStdString() + "/" + p_simulationName.ToStdString() + ".msh", 2.2, false, false, false, 1.0, 0, 0, false);
	
	// No matter what happens, we need to reset the visited state for arcs and lines 
	// lines visited state back to false!
	for(plf::colony<edgeLineShape>::iterator lineIterator = p_lineList->begin(); lineIterator != p_lineList->end(); lineIterator++)
	{
		lineIterator->setVisitedStatus(false);
	}
	
	for(plf::colony<arcShape>::iterator arcIterator = p_arcList->begin(); arcIterator != p_arcList->end(); arcIterator++)
	{
		arcIterator->setVisitedStatus(false);
	}
	
	for(auto blockIterator = p_blockLabelList->begin(); blockIterator != p_blockLabelList->end(); blockIterator++)
	{
		blockIterator->setUsedState(false);
	}

	if(p_meshModel->getNumMeshVertices() > 0)
		p_meshModel->indexMeshVertices(true);
	
	OmniFEMMsg::instance()->MsgStatus("Meshing Finished");
}



void meshMaker::createGMSHGeometry(std::vector<closedPath> *pathContour)
{
	// At this point, the pathContour is all set up ready to go
	// PLease note that this function assumes that the lines for each closed contour in 
	// pathContour has not already been created
	std::vector<closedPath> *pathToOperate = nullptr;
	
	if(pathContour == nullptr)
		pathToOperate = &p_closedContourPaths;
	else
		pathToOperate = pathContour;

	for(auto pathIterator = pathToOperate->begin(); pathIterator != pathToOperate->end(); pathIterator++)
	{
		std::vector<std::vector<GEdge*>> lineLoop;
		std::vector<GEdge*> addLineVector;
		
		/* Creating the face will be ignored if the closed contour does not 
		 * have a block label assigned to it (perhaps the user forgot to place a label within the contour)
		 * Or if the user specified that the face is suppose to have no mesh
		 */ 
		if(pathIterator->getProperty() && pathIterator->getProperty()->getMeshsizeType() != meshSize::MESH_NONE_)
		{
		// We first must add in the actual path of the contour to the line loop
			for(auto lineIterator = pathIterator->getClosedPath()->begin(); lineIterator != pathIterator->getClosedPath()->end(); lineIterator++)
			{
				GEdge *addedEdge = nullptr;
				
				GVertex *firstNode = p_meshModel->getVertexByTag((*lineIterator)->getFirstNode()->getGModalTagNumber());
				GVertex *secondNode = p_meshModel->getVertexByTag((*lineIterator)->getSecondNode()->getGModalTagNumber());
				
				if((*lineIterator)->isArc())
				{
					GVertex *temp = p_meshModel->addVertex((*lineIterator)->getCenterXCoordinate(), (*lineIterator)->getCenterYCoordinate(), 0.0, 1.0);
					addedEdge = p_meshModel->addCircleArcCenter(firstNode, temp, secondNode);
				}
				else
				{
					addedEdge = p_meshModel->addLine(firstNode, secondNode);
				}
					
				if(pathIterator->getProperty()->getMeshsizeType() != meshSize::MESH_NONE_)
				{
					if((*lineIterator)->getSegmentProperty()->getMeshAutoState())
					{
						// If the mesh spacing is set to auto for the line, then the mesh size of the GEdge will inherit the
						// mesh size specified by the user in the block label
						if(!pathIterator->getProperty()->getAutoMeshState())
						{
							addedEdge->meshAttributes.meshSize = pathIterator->getProperty()->getMeshSize();
						}
						else
						{
							std::string temp = pathIterator->getProperty()->getMaterialName();
							std::transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
							
							if(temp == "air")
								addedEdge->meshAttributes.meshSize = 0.25;
							else
								addedEdge->meshAttributes.meshSize = 0.1;
						}
					}
					else if(!(*lineIterator)->getSegmentProperty()->getMeshAutoState())
					{
						// In this case, the user has specificially specified that they need the line's mesh size set to a specific value
						addedEdge->meshAttributes.meshSize = (*lineIterator)->getSegmentProperty()->getElementSizeAlongLine();
					}
				}
				
				addLineVector.push_back(addedEdge);
			}
			
			// Next we need to set the mesh size of the GEdges here
			
			lineLoop.push_back(addLineVector);
			
			// IF there are any holes, add them to the lineloop vector here
			if(pathIterator->getHoles()->size() > 0)
			{
				for(auto holeIterator = pathIterator->getHoles()->begin(); holeIterator != pathIterator->getHoles()->end(); holeIterator++)
				{
					addLineVector.clear();
					for(auto lineIterator = holeIterator->getClosedPath()->begin(); lineIterator != holeIterator->getClosedPath()->end(); lineIterator++)
					{
						GVertex *firstNode = p_meshModel->getVertexByTag((*lineIterator)->getFirstNode()->getGModalTagNumber());
						GVertex *secondNode = p_meshModel->getVertexByTag((*lineIterator)->getSecondNode()->getGModalTagNumber());
						
						GEdge *addedEdge = nullptr;
						
						if((*lineIterator)->isArc())
						{
							GVertex *temp = p_meshModel->addVertex((*lineIterator)->getCenterXCoordinate(), (*lineIterator)->getCenterYCoordinate(), 0.0, 1.0);
							addedEdge = p_meshModel->addCircleArcCenter(firstNode, temp, secondNode);
						}
						else
						{
							addedEdge = p_meshModel->addLine(firstNode, secondNode);
						}
						
						if(pathIterator->getProperty()->getMeshsizeType() != meshSize::MESH_NONE_)
						{
							if((*lineIterator)->getSegmentProperty()->getMeshAutoState())
							{
								// If the mesh spacing is set to auto for the line, then the mesh size of the GEdge will inherit the
								// mesh size specified by the user in the block label
								if(!pathIterator->getProperty()->getAutoMeshState())
								{
									addedEdge->meshAttributes.meshSize = pathIterator->getProperty()->getMeshSize();
								}
								else
								{
									std::string temp = pathIterator->getProperty()->getMaterialName();
									std::transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
									
									if(temp == "air")
										addedEdge->meshAttributes.meshSize = 0.25;
									else
										addedEdge->meshAttributes.meshSize = 0.1;
								}
							}
							else if(!(*lineIterator)->getSegmentProperty()->getMeshAutoState())
							{
								// In this case, the user has specificially specified that they need the line's mesh size set to a specific value
								addedEdge->meshAttributes.meshSize = (*lineIterator)->getSegmentProperty()->getElementSizeAlongLine();
							}
						}
				
						addLineVector.push_back(addedEdge);
					}
					lineLoop.push_back(addLineVector);
				}
			}
			
			GFace *addedFace = p_meshModel->addPlanarFace(lineLoop);
			
			if(p_settings->getStructuredState())
			{
				addedFace->meshAttributes.method = 1;// Sets the face to be transfinite
				
				switch(p_settings->getMeshArrangment())
				{
					case StructuredArrangement::ARRANGMENT_LEFT:
						addedFace->meshAttributes.transfiniteArrangement = -1;
						break;
					case StructuredArrangement::ARRANGMENT_RIGHT:
						addedFace->meshAttributes.transfiniteArrangement = 1;
						break;
					case StructuredArrangement::ARRANGMENT_ALTERNATED:
						addedFace->meshAttributes.transfiniteArrangement = 2;
						break;
					default:
						addedFace->meshAttributes.transfiniteArrangement = -1;
						break;
				}
			}
			else
			{
				addedFace->meshAttributes.method = 2;
				addedFace->meshAttributes.transfiniteArrangement = 0;
			}
			
			addedFace->meshAttributes.meshSize = 1.0;
		}
	}
}



void meshMaker::holeDetection(std::vector<closedPath> *pathContour)
{
	std::vector<closedPath> *pathToOperate = nullptr;
	
	if(pathContour == nullptr)
		pathToOperate = &p_closedContourPaths;
	else
		pathToOperate = pathContour;
	
	
	// First, we need to loop through every single closed path and check the bounding box
	// against all the other closed paths to see if it is a possible hole
	for(auto pathIterator = pathToOperate->begin(); pathIterator != pathToOperate->end(); pathIterator++)
	{
		for(auto holeIterator = p_closedContourPaths.begin(); holeIterator != p_closedContourPaths.end(); holeIterator++)
		{
			if(holeIterator->getBoundingBox().isInside(pathIterator->getBoundingBox()))
				pathIterator->addHole(*holeIterator);
		}
	}
	
	// Now, we need to find the top level holes
	for(auto pathIterator = pathToOperate->begin(); pathIterator != pathToOperate->end(); pathIterator++)
	{
		if(pathIterator->getHoles()->size() > 1)
		{
			bool isFinished = false;
			
			while(!isFinished)
			{
				for(auto topLevelIterator = pathIterator->getHoles()->begin(); topLevelIterator != pathIterator->getHoles()->end();)
				{
					bool resetIterator = false;
					
					for(auto holeIterator = pathIterator->getHoles()->begin(); holeIterator != pathIterator->getHoles()->end();)
					{
						// If the hole is inside of the top level contour, delete the hole and restart the process
						if(holeIterator->getBoundingBox().isInside(topLevelIterator->getBoundingBox()))
						{
							pathIterator->getHoles()->erase(holeIterator);
							resetIterator = true;
							break;
						}
						else if(topLevelIterator->getBoundingBox().isInside(holeIterator->getBoundingBox()))
						{
							// If the top level is actually inside of the hole,
							// then we need to delete the top level and restart the process
							pathIterator->getHoles()->erase(topLevelIterator);
							resetIterator = true;
							break;
						}
						else// If the hole is not even inside of the top level but inside of the closed contour, skip and continue on
							holeIterator++;
					}
					
					if(resetIterator)
						break;
					else
						topLevelIterator++;
					
					if(topLevelIterator == pathIterator->getHoles()->end())
						isFinished = true;
				}
			}
		}
		
		// Need to combine any closed paths holes with a common edge here
		if(pathIterator->getHoles()->size() > 0)
			pathIterator->combineHoles();
	}
}



void meshMaker::assignBlockLabel(std::vector<closedPath> *pathContour)
{
	std::vector<closedPath> *pathToOperate = nullptr;
	
	if(pathContour == nullptr)
		pathToOperate = &p_closedContourPaths;
	else
		pathToOperate = pathContour;
		
	for(auto pathIterator = pathToOperate->begin(); pathIterator != pathToOperate->end(); pathIterator++)
	{
		blockLabel *setLabel = nullptr;
		
		if(pathIterator->getBlockLabelList()->size() > 1)
		{
			for(auto propertyIterator = pathIterator->getBlockLabelList()->begin(); propertyIterator != pathIterator->getBlockLabelList()->end(); propertyIterator++)
			{
				bool isInHole = false;
				
				if(!(*propertyIterator)->getUsedState())
				{
					for(auto holeIterator = pathIterator->getHoles()->begin(); holeIterator != pathIterator->getHoles()->end(); holeIterator++)
					{
						if(checkPointInContour(*propertyIterator, &(*holeIterator)))
						{
							isInHole = true;
							break;
						}
					}
				}
				
				if(!isInHole && !(*propertyIterator)->getUsedState())
				{
					setLabel = *propertyIterator;
					break;
				}
			}
		}
		else if(pathIterator->getBlockLabelList()->size() == 1)
		{
			setLabel = pathIterator->getBlockLabelList()->at(0);
		}
		else
		{
			continue;
		}
		
		setLabel->setUsedState(true);
		p_blockLabelsUsed++;
		pathIterator->setProperty(setLabel->getProperty());
		pathIterator->clearBlockLabelList();
	}
}