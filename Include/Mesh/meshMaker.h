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
public:
	meshMaker(plf::colony<node> *nodeList, plf::colony<blockLabel> *blockLabelList, plf::colony<edgeLineShape> *lineList, plf::colony<arcShape> *arcList)
	{
		p_nodeList = nodeList;
		p_blockLabelList = blockLabelList;
		p_lineList = lineList;
		p_arcList = arcList;
	}
};


#endif