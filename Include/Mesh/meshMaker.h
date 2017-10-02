#ifndef MESH_MAKER_H_
#define MESH_MAKER_H_

#include <vector>
#include <UI/geometryShapes.h>
#include <common/plfcolony.h>


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
	//! Vector containing a list of all closed contours within the geometry. Which each closed contour is a vector of edge line shapes.
	std::vector<std::vector<edgeLineShape>> p_closedContours;
	
	//! Pointer to the global nodal list
	plf::colony<node> *p_nodeList;
	
	//! Pointer to the global block label list
	plf::colony<blockLabel> *p_blockLabelList;
	
	//! Pointer to the global line list
	plf::colony<edgeLineShape> *p_lineList;
	
	//! Pointer to the global arc list
	plf::colony<arcShape> *p_arcList;
	
	//! This is the total number of lines within the geometry. This is the number of lines and arcs
	unsigned long p_numberofLines = 0;
	
	//! This data type is incremented when the program visists a new line
	unsigned long p_numberVisited = 0;
	
	/**
	 * @brief 	This function is called in order to find all of the closed contours connected to 
	 * 			a common edge. The function will then determine what the geometry pieces are within
	 * 			the closed contour. This function is modeled off of the depth-first search algorthim
	 */
	std::vector<std::vector<edgeLineShape>> findContours();
	
	/**
	 * @brief 
	 */
	void contourRecombination(std::vector<std::vector<edgeLineShape>> contourPaths);
	
	/**
	 * @brief Function that will determine if the inpuit contour is a closed contour
	 * @param contour The vector of the contour that will be tested for closed contour
	 * @return Returns true if the contour is closed contour. Return false if it is open contour
	 */
	bool isClosedContour(std::vector<edgeLineShape> contour);
	
	/**
	 * @brief 	Function that is called in order to remove any dangling lines from the path
	 * 			Dangling lines are defined as lines that are not connected to form a closed contour.
	 * 			This occurs when the contour loops on itself and ends at a position other then the
	 * 			starting position. This occurs if the end line semgent is connected between 2
	 * 			line segments within the contour. When this occurs, the program
	 * 			needs to erase the line segments from the beginning to 1 - the current iterator
	 * 			position.
	 * @param contour Reference to the contour list that will need to be modified
	 */
	void removeDanglingLines(std::vector<edgeLineShape> &contour);
	
	/**
	 * @brief This function is called in order to create the mesh for hte geometry model.
	 * 			This function needs to be called after the program sorts through and determines
	 * 			the geometry pieces within the model
	 */
	void createMesh();
	
	/**
	 * @brief This function will take a edge segment and find all of the banches that are connected to that edge and return as a vector
	 * @param segment The line segment that the program will find the connected branches to
	 * @return Returns a vector containing all of the connected branches to the segment
	 */
	std::vector<edgeLineShape> getConnectedPaths(std::vector<edgeLineShape>::reference segment, std::vector<edgeLineShape> &pathVector);
	
	/**
	 * @brief 	This function will test if two paths share a common edge. It does not determine which edge is common. But
	 * 			it tests if there is a common edge. The function does not determine how many common edges. Just that if
	 * 			a common edge exists.
	 * @param path1 The first path
	 * @param path2 The second path
	 * @return Returns true if a common edge exists. Otherwise, returns false
	 */
	bool shareCommonEdge(std::vector<edgeLineShape> path1, std::vector<edgeLineShape> path2);
public:
	meshMaker(plf::colony<node> *nodeList, plf::colony<blockLabel> *blockLabelList, plf::colony<edgeLineShape> *lineList, plf::colony<arcShape> *arcList)
	{
		p_nodeList = nodeList;
		p_blockLabelList = blockLabelList;
		p_lineList = lineList;
		p_arcList = arcList;
		p_numberofLines = p_lineList->size() + p_arcList->size();
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
	
	/**
	 * @brief This function is called when the program is ready to create the mesh for the model.
	 */
	void findGeometry();
	
	~meshMaker()
	{
		//free(p_nodeList);
		//delete p_blockLabelList;
		//delete p_lineList;
		//delete p_arcList;
	}
	
	
};


#endif