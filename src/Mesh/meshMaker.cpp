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
				
				// Test to see if a closed contour is found
				// A closed contour occurs when one of the branches 
				// is the beginning edge of the closed path
				for(std::vector<edgeLineShape*>::iterator branchIterator = branches.begin(); branchIterator != branches.end(); branchIterator++)
				{
					if(**branchIterator == **(pathIterator->getClosedPath()->begin()))
					{
						closedContourFound = true;
						break;
					}
				}
				
				for(std::vector<edgeLineShape*>::iterator pathEdgeIterator = ++(pathIterator->getClosedPath()->begin()); pathEdgeIterator != pathIterator->getClosedPath()->end(); pathEdgeIterator++)
				{
					for(std::vector<edgeLineShape*>::iterator branchIterator = branches.begin(); branchIterator != branches.end();branchIterator++)
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
	
//	foundPath.orient();
	
	return foundPath;
}


std::vector<edgeLineShape*> meshMaker::getConnectedPaths(std::vector<edgeLineShape*>::reference currentSegment, std::vector<edgeLineShape*> *pathVector)
{
	std::vector<edgeLineShape*> returnList;
	node *branchNode;
	std::vector<edgeLineShape*>::iterator previousAddedSegment;
	
	edgeLineShape *previouseSegmentPointer;
	edgeLineShape *currentSegmentPointer = currentSegment; // This part may not be necessary but it helps with the thinking
	
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
		if((*branchNode == *lineIterator->getFirstNode()) || (*branchNode == *lineIterator->getSecondNode()))
		{
			returnList.push_back(&(*lineIterator));
		}
	}
	
	// Find all of the arcs connected to the segment
	for(plf::colony<arcShape>::iterator arcIterator = p_arcList->begin(); arcIterator != p_arcList->end(); arcIterator++)
	{
		if((arcIterator->getArcID() == currentSegmentPointer->getArcID()) || (pathVector->size() > 1 && (arcIterator->getArcID() == previouseSegmentPointer->getArcID())) && !arcIterator->getSegmentProperty()->getHiddenState())
			continue;
			
		if((*branchNode == *arcIterator->getFirstNode()) || (*branchNode == *arcIterator->getSecondNode()))
		{
			returnList.push_back(&(*arcIterator));
		}
	}
	
	return returnList;
}



double meshMaker::calculateShortestDistance(blockLabel selectedLabel, edgeLineShape segment)
{
    double t, x[3], y[3];

    x[0] = segment.getFirstNode()->getCenterXCoordinate();
    y[0] = segment.getFirstNode()->getCenterYCoordinate();
	
    x[1] = segment.getSecondNode()->getCenterXCoordinate();
    y[1] = segment.getSecondNode()->getCenterYCoordinate();
	
	t = ((selectedLabel.getCenterXCoordinate() - x[0]) * (x[1] - x[0]) + (selectedLabel.getCenterYCoordinate() - y[0]) * (y[1] - y[0])) / ((x[1] - x[0]) * (x[1] - x[0]) + (y[1] - y[0]) * (y[1] - y[0]));
      
	if(t > 1)
		t = 1.0;
	else if(t < 0.0)
		t = 0.0;
		
	x[2] = x[0] + t * (x[1] - x[0]);
	y[2] = y[0] + t * (y[1] - y[0]);
    
	return sqrt((selectedLabel.getCenterXCoordinate() - x[2]) * (selectedLabel.getCenterXCoordinate() - x[2]) + (selectedLabel.getCenterYCoordinate() - y[2]) * (selectedLabel.getCenterYCoordinate() - y[2]));   
}



void meshMaker::createGMSHGeometry(std::vector<closedPath> *pathContour)
{
	std::vector<closedPath> *pathToOperate;
	
	if(pathContour == nullptr)
		pathToOperate = &p_closedContourPaths;
	else
		pathToOperate = pathContour;
		
	for(auto contourIterator = pathToOperate->begin(); contourIterator != pathToOperate->end(); contourIterator++)
	{
		/* This section here will transfer the found closed contours into a vector 
		 * of GEdges
		 */ 
		std::vector<GEdge*> contourLoop;
		
		closedPath contour = *contourIterator;
		
		for(std::vector<edgeLineShape*>::iterator lineIterator = contour.getClosedPath()->begin(); lineIterator != contour.getClosedPath()->end(); lineIterator++)
		{
			GVertex *firstNode = nullptr;
			GVertex *secondNode = nullptr;
			//numberOfIntersections = 0;
	
			for(auto vertexIterator : p_vertexModelList)
			{
				double xValueVertex = vertexIterator->x();
				double yValueVertex = vertexIterator->y();
				double firstNodeCenterX = (*lineIterator)->getFirstNode()->getCenterXCoordinate();
				double firstNodeCenterY = (*lineIterator)->getFirstNode()->getCenterYCoordinate();
				double secondNodeCenterX = (*lineIterator)->getSecondNode()->getCenterXCoordinate();
				double secondNodeCenterY = (*lineIterator)->getSecondNode()->getCenterYCoordinate();
				if(((xValueVertex == firstNodeCenterX) && (yValueVertex == firstNodeCenterY)) ||
					((xValueVertex == secondNodeCenterX) && (yValueVertex == secondNodeCenterY)))
					{
						if(xValueVertex == firstNodeCenterX && yValueVertex == firstNodeCenterY)
							firstNode = vertexIterator;
						else if (xValueVertex == secondNodeCenterX && yValueVertex == secondNodeCenterY)
							secondNode = vertexIterator;
						
						if(firstNode && secondNode)
							break;
					}
			}
			
			GEdge *temp = nullptr;
			
			if((*lineIterator)->isArc())
			{
				// Throw in the code here in order to create a Bspline within the mesh model
				// look at the code: bool GEO_Internals::addBezier(int &tag, const std::vector<int> &vertexTags)
				// located in GMODELIO_GEO.cpp file on added in a Bezier curve to the model
				p_vertexModelList.push_back(p_meshModel->addVertex((*lineIterator)->getCenterXCoordinate(), (*lineIterator)->getCenterYCoordinate(), 0.0, 1.0));
				temp = p_meshModel->addCircleArcCenter(firstNode, p_vertexModelList.back(), secondNode);
				
			}
			else
			{
				temp = p_meshModel->addLine(firstNode, secondNode);
			}
			
			// All lines start off with the mesh method as none. If there is a corresponding block label,
			// or a specific mesh size on within the face, then the line will be set to me transfinite or
			// unstructured depending on the meshSettings set by the user
				
			temp->meshAttributes.method = MESH_NONE;
				
			if(!(*lineIterator)->getSegmentProperty()->getMeshAutoState())
			{
				temp->meshAttributes.meshSize = (*lineIterator)->getSegmentProperty()->getElementSizeAlongLine();
			}
			
			contourLoop.push_back(temp);
		}
		
		std::vector<std::vector<GEdge*>> test;
		
		// Now, we need to test if the contour is a hole to another contour
		// Or, if the contour lies outside of a set of contours
		// Or if the contour is not related to any of the already added contours
		// And add it in the correct place of the complete line loop
		// For now, we will just add it to the model directly
		test.push_back(contourLoop);
		
		// Add the contour to the face selection
		GFace *testFace = p_meshModel->addPlanarFace(test);
		
		testFace->meshAttributes.method = MESH_NONE; // Assume that the user does not want to mesh the face
		
		if(p_settings->getStructuredState())
		{
			testFace->meshAttributes.method = 1;// Sets the face to be transfinite
			
			switch(p_settings->getMeshArrangment())
			{
				case StructuredArrangement::ARRANGMENT_LEFT:
					testFace->meshAttributes.transfiniteArrangement = -1;
					break;
				case StructuredArrangement::ARRANGMENT_RIGHT:
					testFace->meshAttributes.transfiniteArrangement = 1;
					break;
				case StructuredArrangement::ARRANGMENT_ALTERNATED:
					testFace->meshAttributes.transfiniteArrangement = 2;
					break;
				default:
					testFace->meshAttributes.transfiniteArrangement = -1;
					break;
			}
			
			
			testFace->meshAttributes.meshSize = 0.05;
		}
		else
		{
			testFace->meshAttributes.method = 2;
			testFace->meshAttributes.transfiniteArrangement = 0;
		}

		
		for(auto blockIterator = p_blockLabelList->begin(); blockIterator != p_blockLabelList->end(); blockIterator++)
		{
			if(checkPointInContour(*blockIterator, *contourIterator))
			{
				meshSize testEnum = blockIterator->getProperty()->getMeshsizeType();
				contourIterator->setProperty(blockIterator->getProperty());
				if(blockIterator->getProperty()->getMeshsizeType() != meshSize::MESH_NONE_)
				{
					double checkMesh = blockIterator->getProperty()->getMeshSize();
					for(int i = 0; i < contourLoop.size(); i++)
					{
						if(contourLoop[i]->meshAttributes.meshSize == MAX_LC)
						{
							contourLoop[i]->meshAttributes.meshSize = blockIterator->getProperty()->getMeshSize();
						}
						
						if(p_settings->getStructuredState())
							contourLoop[i]->meshAttributes.method = MESH_TRANSFINITE;
						else
							contourLoop[i]->meshAttributes.method = MESH_UNSTRUCTURED;
							
					}
				//	testFace->meshAttributes.meshSize = blockIterator.getProperty()->getMeshSize();	
					testFace->meshAttributes.meshSize = 1.0;	
				}
					
				blockIterator->setUsedState(true);
				p_blockLabelsUsed++;
				
				break;
			}
		}
	}
}



bool meshMaker::checkPointInContour(wxRealPoint point, closedPath &path)
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
		
		if(contourPath.getDistance() == 0)
		{
			//TODO: Add in error handling
		}
		else
			p_closedContourPaths.push_back(contourPath);
		
		for(std::vector<edgeLineShape*>::iterator edgeIterator = contourPath.getClosedPath()->begin(); edgeIterator != contourPath.getClosedPath()->end(); edgeIterator++)
		{
			if(!(*edgeIterator)->getVisitedStatus())
			{
				(*edgeIterator)->setVisitedStatus(true);
				p_numberVisited++;
			}
		}
	}
	
	
	
	OmniFEMMsg::instance()->MsgStatus("Contours found");

	contextMeshOptions testMesh = CTX::instance()->mesh;
	
	/* Now we go to conver Omni-FEM's geometry data structure into the data structure for GMSH */
	// lcFactor->0.29999999999 lcExtendFromBoundary->1 algo3D-> 1
	OmniFEMMsg::instance()->MsgStatus("Verfied Mesh");
	std::vector<GVertex*> vertexModelList;
	
	p_vertexModelList.reserve(p_nodeList->size());

	p_meshModel->setFactory("Gmsh");
	
	OmniFEMMsg::instance()->MsgStatus("Adding in GMSH Vertices");
	for(auto nodeIterator : *p_nodeList)
	{
		double test1 = nodeIterator.getCenterXCoordinate();
		double test2 = nodeIterator.getCenterYCoordinate();
		GVertex *temp = p_meshModel->addVertex(test1, test2, 0.0, 1.0);
		p_vertexModelList.push_back(temp);
	}
	
	/* Now we create the faces */
	OmniFEMMsg::instance()->MsgStatus("Adding in GMSH faces");
	
	createGMSHGeometry();
	
	/*if(p_blockLabelsUsed < p_blockLabelList->size())
	{
		std::vector<closedPath> additionalPaths;
		for(auto blockIterator : *p_blockLabelList)
		{
			
			if(!blockIterator.getUsedState())
			{
				double shortestDistance = 0;
				edgeLineShape *shortestEdge;
				for(plf::colony<edgeLineShape>::iterator lineIterator = p_lineList->begin(); lineIterator != p_lineList->end(); lineIterator++)
				{
					double distance = calculateShortestDistance(blockIterator, *lineIterator);
					if(distance < shortestDistance || shortestDistance == 0)
					{
						shortestDistance = distance;
						shortestEdge = &(*lineIterator);
					}
				}
				// This function would only be called if a block label has been forgotten
				// An additional parameter should be added here that will inform the program of anoher condition
				// for the closed path where the closed path must encompass the blocklabel
				closedPath path = findContour(shortestEdge, &blockIterator);
				additionalPaths.push_back(path);
			}
		}
		
		createGMSHGeometry(&additionalPaths);
	}
	 */ 
	 
	
	/* As a side note,this current method for constructing the GMSH geometry will not work.
	 * The order needs to be this:
	 * 1) Create the list of vertices. Convert all Omni-FEM nodes to GMSH vertices
	 * 2) Convert all Omni-FEM lines/arcs into GMSH edges. Save in a list which groups them based on the face that they are in
	 * At the end of step 2, we should have a vector will all of the closed contours containing the GMSH edges
	 * 3) Construct the faces of the model by indentifying if the contour lies within the another contour and construct the face vector
	 * 4) Add face to the GMSH geometry
	 */ 
	
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
	
	// THis is the file that the solver uses for meshing
//	p_meshModel->writeMSH(p_folderPath.ToStdString() + "/" + p_simulationName.ToStdString() + ".msh", 2.2, false, false, false, 1.0, 0, 0, false);
	
	// TODO: Check for an errors?
	// TODO: Add in the interface to the GMSH API
	// TODO: Mesh the model
	// TODO: Return the mesh. The function return is void for now
	
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
		p_meshModel->indexMeshVertices(true, 0, true);
	
	OmniFEMMsg::instance()->MsgStatus("Meshing Finished");
}


bool meshMaker::shareCommonEdge(std::vector<edgeLineShape> path1, std::vector<edgeLineShape> path2)
{
	bool commonFound = false;
	
	for(auto pathIterator1 : path1)
	{
		for(auto pathIterator2 : path2)
		{
			if(pathIterator2 == pathIterator1)
			{
				commonFound = true;
				break;
			}
		}
		
		if(commonFound)
			break;
	}
	
	return commonFound;
}