#ifndef MESH_MAKER_H_
#define MESH_MAKER_H_

#include <vector>
#include <algorithm>
#include <map>
#include <utility>

#include <UI/geometryShapes.h>
#include <UI/ModelDefinition/ModelDefinition.h>

#include <common/plfcolony.h>
#include <common/Vector.h>
#include <common/enums.h>

#include <common/MeshSettings.h>
#include <common/ClosedPath.h>
#include <common/ProblemDefinition.h>

#include <common/GeometryProperties/BlockProperty.h>

#include <Mesh/Gmsh.h>
#include <Mesh/Context.h>
#include <Mesh/GVertex.h>
#include <Mesh/GEdge.h>
#include <Mesh/GFace.h>
#include <Mesh/GModel.h>

#include <Mesh/SBoundingBox3d.h>


/**
 * @class meshMaker
 * @author phillip
 * @date 21/09/17
 * @file meshMaker.h
 * @brief 	The purpose of this class is to handle the creation of the 2D Mesh from the geometry
 * 			that the user has created. This class contains the function needed in order to
 * 			determine the closed contours within the geometry. This class will interface with
 * 			the GMSH source in order to create the mesh.
 */
class meshMaker
{
private:
	//! The master list of all of te closed contours found in the geometry
	std::vector<closedPath> p_closedContourPaths;
	
	//! Pointer to the global nodal list
	plf::colony<node> *p_nodeList;
	
	//! Pointer to the global block label list
	plf::colony<blockLabel> *p_blockLabelList;
	
	//! Pointer to the global line list
	plf::colony<edgeLineShape> *p_lineList;
	
	//! Pointer to the global arc list
	plf::colony<arcShape> *p_arcList;
	
	//! Pointer to the mesh settigns that are settable by the user
	meshSettings *p_settings;
	
	//! The name of the simulation as set by the user. This is used in order to create the different mesh file formats
	wxString p_simulationName;
	
	//! This setting is set by the user and specifies where to save the mesh file format(s)
	wxString p_folderPath;
	
	//! A pointer to the GMSH model
	GModel *p_meshModel;
	
	//! This is the total number of lines within the geometry. This is the number of lines and arcs
	unsigned long p_numberofLines = 0;
	
	//! A counter to keep track of the number of visited edges during the findContour algorithm.
	unsigned long p_numberVisited = 0;
	
	//! A number to specify the number of block labels that the program used. Used to check if there are any forgotten labels
	unsigned int p_blockLabelsUsed = 0;
	
	/**
	 * @brief 	This algorithm is called in order to find 1 closed contour. If the first parameter is null, then the algorithm
	 * 			will start at the first avaiable edge in the lineList as the starting edge. If none exists, then the algorithm will look in the 
	 * 			arc list for the starting edge. The algorithm will then run a modified version of the Dijkstra's algorithm where the 
	 * 			program will look for the shortest path to loop back on itself. If the second parameter is not null, then the 
	 * 			algorithm will look for the shortest path that encompasses a point.
	 * @param startingEdge Parameter that specifies which edge to start with. If null, the algorithm will look in the lineList for the starting edge
	 * @param point Parameter that specifies a point that the closed contour will need to encompass around. If null, then find the shortest path.
	 * @return Returns a closed contour path of the shortest distance to loop back on itself. Will return a path of 0 distance if no path could be found.
	 */
	closedPath findContour(edgeLineShape *startingEdge = nullptr, rectangleShape *point = nullptr);
	
	/**
	 * @brief This function will take a edge segment and find all of the banches that are connected to that edge and return as a vector
	 * @param currentSegment The line segment that the program will find the connected branches to
	 * @param pathVector The path list that contains the currentSegment
	 * @return Returns a vector containing all of the connected branches to the segment
	 */
	std::vector<edgeLineShape*> getConnectedPaths(std::vector<edgeLineShape*>::reference currentSegment, std::vector<edgeLineShape*> *pathVector);
	
	/**
	 * @brief This algorithm will take a vector of closed paths and convert the closed path into the GMSH geometry face.
	 * If the parameter is null, then the function will operate on the master list of the closed paths. This function will always
	 * operate on the mesh model in order to add faces to GMSH. This function will add in the closed path, the holes, and set the mesh 
	 * settings of the face. For an edge that is shared by 2 or more faces, this algorithm will create duplicates of the edge
	 * in order to ensure that the edge has the correct mesh size setting for the corresponding face. If the closed path does
	 * not have an assigned mesh size to it, then the closed path will not be converted into the GMSH geometry.
	 * @param pathContour A pointer to the list that the algorithm will operate on. If null, the algorithm will default to the master list.
	 */
	void createGMSHGeometry(std::vector<closedPath> *pathContour = nullptr);
	
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
	bool checkPointInContour(wxRealPoint point, closedPath path);
	
	/**
	 * @brief This function performs exactly the same as checkPointInContour excpet that the parameters are different
	 * @param point Rectanglur point to check if it exists within the closed path
	 * @param path The closed path to check if point exists inside of
	 * @return Returns true if the rectangle shape lies within the closed path. Otherwise, returns false.
	 */
	bool checkPointInContour(rectangleShape point, closedPath path)
	{
		return checkPointInContour(point.getCenter(), path);
	}
	
	/**
	 * @brief This function performs exactly the same as checkPointInContour excpet that the parameters are different
	 * @param point Pointer to the point to check if it exists within the closed path
	 * @param path Pointer to the closed path to check if point exists inside of
	 * @return Returns true if the rectangle shape lies within the closed path. Otherwise, returns false.
	 */
	bool checkPointInContour(rectangleShape *point, closedPath *path)
	{
		return checkPointInContour(point->getCenter(), *path);
	}
	
	/**
	 * @brief Algorithm that is ran in order to locate the holes of a closed contour. This alogorithm will first 
	 * locate all of the holes and then find the top level holes belonging to the closed contour. This is a requirement
	 * imposed by GMSH. Additionally, there holes are unable to share a common edge. If a common edge exists, then the
	 * algorithm will create a new hole with the common edge removed. This algorithm will operate on the pathContour
	 * pointer.
	 * @param pathContour Pointer pointing to the closed path to operate on. If null, algorithm will operate on the master list.
	 */
	void holeDetection(std::vector<closedPath> *pathContour = nullptr);
	
	/**
	 * @brief This algorithm will run in order to detect the block label that belongs to the closed path. 
	 * If more then one block label is inside of the closed path, the algorithm will determine which block labels are 
	 * in the holes and locate the first block label outside of the holes. Once detected, it will assign the 
	 * mesh settings of the block label to the closed path. THe algorithm will operate on the pathContour pointer.
	 * @param pathContour Pointer pointing to the closed path to operate on. If null, algorithm will operate on the master list.
	 */
	void assignBlockLabel(std::vector<closedPath> *pathContour = nullptr);
	
	/**
	 * @brief Function that is used in order to check if a closed path is actually a closed path
	 * @param pathEdges Vector of the edge list that will be checked
	 * @return Returns true if the last element in the vector is connected to the first element forming a closed path. Otherwise, returns false
	 */
	bool isClosedPath(std::vector<edgeLineShape*> pathEdges)
	{
		edgeLineShape beginEdge = *(*pathEdges.begin());
		edgeLineShape lastEdge = *(*pathEdges.rbegin());
		
		if(pathEdges.size() > 1)
		{
			if(beginEdge.getFirstNodeID() == lastEdge.getFirstNodeID() || beginEdge.getFirstNodeID() == lastEdge.getSecondNodeID() ||
				beginEdge.getSecondNodeID() == lastEdge.getFirstNodeID() || beginEdge.getSecondNodeID() == lastEdge.getSecondNodeID())
				return true;
			else
				return false;
		}
		else
			return false;
	}
	
public:
	
	meshMaker(problemDefinition &definition, modelDefinition *model)
	{
		p_meshModel = model->getMeshModel();
		
		p_nodeList = model->getModelNodeList();
		p_blockLabelList = model->getModelBlockList();
		p_lineList = model->getModelLineList();
		p_arcList = model->getModelArcList();
		
		p_numberofLines = p_lineList->size() + p_arcList->size();
		
		p_settings = definition.getMeshSettingsPointer();
		p_simulationName = definition.getName();
		p_folderPath = definition.getSaveFilePath();
	}
	
	/**
	 * @brief Function that is used to check if the system has found all geometry pieces 
	 * @return Returns true when the class has finished the procedure. Otherwise returns false
	 */
	bool geometryIsFound()
	{
		if(p_numberVisited == p_numberofLines)
			return true;
		else
			return false;
	}
	
	void mesh();
	
	~meshMaker()
	{
		//free(p_nodeList);
		//delete p_blockLabelList;
		//delete p_lineList;
		//delete p_arcList;
	}
	
	
};


#endif