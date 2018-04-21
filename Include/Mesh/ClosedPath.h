#ifndef CLOSED_PATH_H_
#define CLOSED_PATH_H_

#include <vector>
#include <algorithm>
#include <map>
#include <iterator>

#include <wx/wx.h>
#include <wx/dir.h>

#include <common/OmniFEMMessage.h>
#include <common/GeometryProperties/BlockProperty.h>

#include <Mesh/BoundingBox.h>

#include <UI/geometryShapes.h>


/**
 * @class closedPath
 * @author Phillip
 * @date 04/04/18
 * @file ClosedPath.h
 * @brief This is the main class for a polygon. The terms, closed contour, closed path, and polygon are used interchangability
 * 			This class contains all of the necessary functions to describe a polygon. The class contains the bounding box, the parameter
 * 			of the polygon, the list of edges forming the polygon, the block label property describing the mesh settings, and the 
 * 			list of vertices that make up the polygon.
 */
class closedPath
{
private:

	//! The bounding box of the polygon
	boundingBox p_boundingBox;

	//! The perimeter of the polygon
	double p_distance = 0;
	
	//! The list of edges that make up the polygon
	std::vector<edgeLineShape*> p_closedPath;
	
	//! Vector of simplified edges representing the polygon. This is used in the winding number algorithm 
	std::vector<simplifiedEdge> p_simplifiedPath;
	
	//! If the polygon has any arcs, then this vector will contain all of the boxes that encase each arc. This is used in the PIP algorithm
	std::vector<arcPolygon> p_arcPolygons;
	
	//! This is the center of the polygon computing by taking the average of all of the centers of the edges
	wxRealPoint p_centerPoint = wxPoint(0, 0);
	
	//! The block label propert that is associated with the polygon	
	blockProperty *p_property = nullptr;
	
	//! The list of holes within the polygon
	std::vector<closedPath> p_holes;
	
	//! A temporary list to describe all of the block labels within the polygon
	std::vector<blockLabel*> p_blockLabelList;
	
	//! The vertex list of all of the vertices that make up the polygon
	std::map<node*, char> p_vertexList;
	
	bool p_holesFound = false;
	
	//! Boolean that is used to indicate if the orientation of the polygon is CCW (false) or CW (true). Used in the PIP algorithm
	bool p_reverseWindingResult = false;
	
	/**
	 * @brief This function is used to determine if any holes share a common edge. In GMSH, holes are not allowed to share a common edge
	 * 			when meshing. Therefor, an algorithm was created that will combine the two holes removing the commone edge.
	 * 			The order of firstPath and secondPath does not matter in this algorithm
	 * @param firstPath The first hole for comparing
	 * @param secondPath The second hole for comparing
	 * @param commonEdges The list of commone edges for the two holes. If no common edges exist
	 * 						this list will be empty
	 * @return Returns True if common edges found, otherwise returns false
	 */
	bool shareCommonEdge(closedPath firstPath, closedPath secondPath, std::vector<edgeLineShape*> &commonEdges)
	{
		commonEdges.clear();// Make sure this vector is empty before proceding
		
		for(auto firstPathIterator = firstPath.getClosedPath()->begin(); firstPathIterator != firstPath.getClosedPath()->end(); firstPathIterator++)
		{
			for(auto secondPathIterator = secondPath.getClosedPath()->begin(); secondPathIterator != secondPath.getClosedPath()->end(); secondPathIterator++)
			{
				if(*(*firstPathIterator) == *(*secondPathIterator))
					commonEdges.push_back(*firstPathIterator);
			}
		}
		
		if(commonEdges.size() > 0)
			return true;
		else
			return false;
	}
	
	/**
	 * @brief This function will recreate a new closed contour (polygon) from a list of provided edges in either CW or CCW order
	 * @param edgeList The list of edges to create a new polygon from
	 * @return Returns a new polygon from the edgeList that is either in the CCW or CW orientation
	 */
	closedPath getClosedContour(std::vector<edgeLineShape*> edgeList);

public:

	bool operator () (const simplifiedEdge &sedge)
	{
		return sedge.getDeleteState();
	}

	/**
	 * @brief Constructor that is called in order to add the first edge to the closedPath
	 * @param firstEdge Reference to the first edge to add in
	 */
	closedPath(edgeLineShape &firstEdge)
	{
		p_closedPath.push_back(&firstEdge);
		
		p_boundingBox = boundingBox(wxRealPoint(firstEdge.getFirstNode()->getCenterXCoordinate(), firstEdge.getFirstNode()->getCenterYCoordinate()));
		p_boundingBox.addPoint(wxRealPoint(firstEdge.getSecondNode()->getCenterXCoordinate(), firstEdge.getSecondNode()->getCenterYCoordinate()));
		
		
		if(firstEdge.isArc())
		{
			if(firstEdge.getMidPoint() == wxRealPoint(0, 0))
			{
				arcShape *temp = static_cast<arcShape*>(&firstEdge);
				temp->calculateMidPoint();
				p_boundingBox.addPoint(temp->getMidPoint());
			}
			else
				p_boundingBox.addPoint(firstEdge.getMidPoint());
		}
			
		p_centerPoint = firstEdge.getMidPoint();

		p_vertexList.insert(std::pair<node*, int>(firstEdge.getFirstNode(), 1));
		p_vertexList.insert(std::pair<node*, int>(firstEdge.getSecondNode(), 1));
	}
	
	/**
	 * @brief Constructor that is called in order to add the first edge to the closedPath
	 * @param firstEdge Pointer to the first edge to add in
	 */
	closedPath(edgeLineShape *firstEdge)
	{
		p_closedPath.push_back(firstEdge);
		
		p_boundingBox = boundingBox(wxRealPoint(firstEdge->getFirstNode()->getCenterXCoordinate(), firstEdge->getFirstNode()->getCenterYCoordinate()));
		p_boundingBox.addPoint(wxRealPoint(firstEdge->getSecondNode()->getCenterXCoordinate(), firstEdge->getSecondNode()->getCenterYCoordinate()));
		
		if(firstEdge->isArc())
		{
			if(firstEdge->getMidPoint() == wxRealPoint(0, 0))
			{
				arcShape *temp = static_cast<arcShape*>(firstEdge);
				temp->calculateMidPoint();
				p_boundingBox.addPoint(temp->getMidPoint());
			}
			else
				p_boundingBox.addPoint(firstEdge->getMidPoint());
		}
		
		p_centerPoint = firstEdge->getMidPoint();
		
		p_vertexList.insert(std::pair<node*, int>(firstEdge->getFirstNode(), 1));
		p_vertexList.insert(std::pair<node*, int>(firstEdge->getSecondNode(), 1));
	}
	
	/**
	 * @brief An empty construtor for convience
	 */
	closedPath()
	{
		
	}

	/**
	 * @brief Retreieves the perimeter of the polygon
	 * @return Returns a number representing the perimeter of a polygon
	 */
	double getDistance()
	{
		return p_distance;
	}
	
	/**
	 * @brief Increments the perimeter by the number in value
	 * @param value A value to increase the perimeter by
	 */
	void addDistance(double value)
	{
		p_distance += value;
	}
	
	/**
	 * @brief This function is used to retrieve a pointer of the list of edges that form the polygon
	 * @return Returns a pointer to the list of edges forming the polygon
	 */
	std::vector<edgeLineShape*> *getClosedPath()
	{
		return &p_closedPath;
	}
	
	/**
	 * @brief Adds an edge to the closedPath. This function will also increase the perimeter, change the bounding box,
	 * 			change the center of the polygon, and add to the list of vertices
	 * @param addEdge The edge to be added. This is by reference only
	 */
	void addEdgeToPath(edgeLineShape &addEdge)
	{
		p_distance += addEdge.getDistance();
		
		if(!addEdge.isArc())
		{
			p_centerPoint.x = (addEdge.getCenter().x + p_closedPath.size() * p_centerPoint.x) / (p_closedPath.size() + 1);
			p_centerPoint.y = (addEdge.getCenter().y + p_closedPath.size() * p_centerPoint.y) / (p_closedPath.size() + 1);
		}
		else
		{
			p_centerPoint.x = (addEdge.getMidPoint().x + p_closedPath.size() * p_centerPoint.x ) / (p_closedPath.size() + 1);
			p_centerPoint.y = (addEdge.getMidPoint().y + p_closedPath.size() * p_centerPoint.y) / (p_closedPath.size() + 1);
		}
		
		p_closedPath.push_back(&addEdge);
		
		p_boundingBox.addPoint(wxRealPoint(addEdge.getFirstNode()->getCenterXCoordinate(), addEdge.getFirstNode()->getCenterYCoordinate()));
		p_boundingBox.addPoint(wxRealPoint(addEdge.getSecondNode()->getCenterXCoordinate(), addEdge.getSecondNode()->getCenterYCoordinate()));
		
		if(addEdge.isArc())
		{
	//		p_boundingBox.addPoint(addEdge.getMidPoint());
			
			if(addEdge.getMidPoint() == wxRealPoint(0, 0))
			{
				arcShape *temp = static_cast<arcShape*>(&addEdge);
				temp->calculateMidPoint();
				p_boundingBox.addPoint(temp->getMidPoint());
			}
			else
				p_boundingBox.addPoint(addEdge.getMidPoint());
		}
		
		auto mapIterator = p_vertexList.find(addEdge.getFirstNode());
		
		if(mapIterator == p_vertexList.end())
			p_vertexList.insert(std::pair<node*, int>(addEdge.getFirstNode(), 1));
			
		mapIterator = p_vertexList.find(addEdge.getSecondNode());
		
		if(mapIterator == p_vertexList.end())
			p_vertexList.insert(std::pair<node*, int>(addEdge.getSecondNode(), 1));
	}
	
	/**
	 * @brief Adds an edge to the closedPath. This function will also increase the perimeter, change the bounding box,
	 * 			change the center of the polygon, and add to the list of vertices
	 * @param addEdge The edge to be added. This is by pointer only
	 */
	void addEdgeToPath(edgeLineShape *addEdge)
	{
		double temp = addEdge->getDistance();
		p_distance += addEdge->getDistance();
		
		if(!addEdge->isArc())
		{
			p_centerPoint.x = (addEdge->getCenter().x + p_closedPath.size() * p_centerPoint.x) / (p_closedPath.size() + 1);
			p_centerPoint.y = (addEdge->getCenter().y + p_closedPath.size() * p_centerPoint.y) / (p_closedPath.size() + 1);
		}
		else
		{
			p_centerPoint.x = (addEdge->getMidPoint().x + p_closedPath.size() * p_centerPoint.x) / (p_closedPath.size() + 1);
			p_centerPoint.y = (addEdge->getMidPoint().y + p_closedPath.size() * p_centerPoint.y) / (p_closedPath.size() + 1);
		}
		
		p_closedPath.push_back(addEdge);
		
		p_boundingBox.addPoint(wxRealPoint(addEdge->getFirstNode()->getCenterXCoordinate(), addEdge->getFirstNode()->getCenterYCoordinate()));
		p_boundingBox.addPoint(wxRealPoint(addEdge->getSecondNode()->getCenterXCoordinate(), addEdge->getSecondNode()->getCenterYCoordinate()));
			
		if(addEdge->isArc())
		{
		//	p_boundingBox.addPoint(addEdge->getMidPoint());
			
			if(addEdge->getMidPoint() == wxRealPoint(0, 0))
			{
				arcShape *temp = static_cast<arcShape*>(addEdge);
				temp->calculateMidPoint();
				p_boundingBox.addPoint(temp->getMidPoint());
			}
			else
				p_boundingBox.addPoint(addEdge->getMidPoint());
		}
		
		auto mapIterator = p_vertexList.find(addEdge->getFirstNode());
		
		if(mapIterator == p_vertexList.end())
			p_vertexList.insert(std::pair<node*, int>(addEdge->getFirstNode(), 1));
			
		mapIterator = p_vertexList.find(addEdge->getSecondNode());
		
		if(mapIterator == p_vertexList.end())
			p_vertexList.insert(std::pair<node*, int>(addEdge->getSecondNode(), 1));
		
	}
	
	/**
	 * @brief Returns the max bounds (which is a 2-D point) of the polygon
	 * @return Returns the max bounds of the polygon
	 */
	wxRealPoint getMaxSize()
	{
		return p_boundingBox.getMaxBounds();
	}
	
	/**
	 * @brief Retrieves the center of the polygon
	 * @return Returns a point representing the center of the polygon
	 */
	wxRealPoint getCenter() const
	{
		return p_centerPoint;
	}
	
	/**
	 * @brief Function that is used to set the block label property of the polygon
	 * @param property The property that is to be associated with the polygon. This contains
	 * 					details such as the mesh size of the geometry. This is by reference
	 */
	void setProperty(blockProperty &property)
	{
		p_property = &property;
	}
	
	/**
	 * @brief Function that is used to set the block label property of the polygon
	 * @param property The property that is to be associated with the polygon. This contains
	 * 					details such as the mesh size of the geometry. This is by pointer
	 */
	void setProperty(blockProperty *property)
	{
		p_property = property;
	}
	
	/**
	 * @brief Retrieves the property that is associated with the polygon
	 * @return Returns a pointer to the property
	 */
	blockProperty *getProperty()
	{
		return p_property;
	}
	
	/**
	 * @brief Function that is used to add a hole to the polygon
	 * @param hole THe hole that is to be added. This assumes that the hole is currently a pointer
	 */
	void addHole(closedPath *hole)
	{
		p_holes.push_back(*hole);
	}
	
	/**
	 * @brief Function that is used to add a hole to the polygon
	 * @param hole THe hole that is to be added. Adds by reference
	 */
	void addHole(closedPath &hole)
	{
		p_holes.push_back(hole);
	}
	
	/**
	 * @brief Function that is used in order to get the list of holes belonging to the polygon
	 * @return Returns a pointer pointing to the list of holes
	 */
	std::vector<closedPath> *getHoles()
	{
		return &p_holes;
	}
	
	/**
	 * @brief Adds a blocklabel to the list of block labels. This list will contain all of the labels that are inside of the polygon.
	 * 			Later, the top level property will be extracted from this list.
	 * @param label The label that is to be added to the list by reference.
	 */
	void addBlockLabel(blockLabel &label)
	{
		p_blockLabelList.push_back(&label);
	}
	
	 /**
	  * @brief Retrieves the block label list associated with the polygon
	  * @return Returns a pointer pointing to the block label list
	  */
	std::vector<blockLabel*> *getBlockLabelList()
	{
		return &p_blockLabelList;
	}
	
	/**
	 * @brief This function will set the block label list. This is mainly used if the original polygon needs to be 
	 * 			destoryed and recreated and the block label list needs to be transferred to the new
	 * @param blockList The list that the polygon should be associated with
	 */
	void setBlockLabelList(std::vector<blockLabel*> blockList)
	{
		p_blockLabelList = blockList;
	}
	
	/**
	 * @brief Clears the contents of the block label list
	 */
	void clearBlockLabelList()
	{
		p_blockLabelList.clear();
	}
	
	/**
	 * @brief Checks if the point is inside of the bounding box for the polygon
	 * @param point The point to check
	 * @return Returns True if the point is inside, otherwise returns false
	 */
	bool pointInBoundingBox(wxRealPoint point)
	{
		if(	point.x < p_boundingBox.getMaxBounds().x &&
			point.x > p_boundingBox.getMinBounds().x &&
			point.y < p_boundingBox.getMaxBounds().y &&
			point.y > p_boundingBox.getMinBounds().y)
			return true;
		else
			return false;
	}
	
	/**
	 * @brief Returns the vertex list of the polygon
	 * @return Returns a pointer pointing to the vertex list of the polygon
	 */
	std::map<node*, char> *getVertexList()
	{
		return &p_vertexList;
	}
	
	/**
	 * @brief Returns the bounding bounding box
	 * @return Returns the bounding box
	 */
	boundingBox getBoundingBox()
	{
		return p_boundingBox;
	}
	
	/**
	 * @brief An algorithm that is ran that checks all of the holes to ensure that no hole shares a common edge
	 * 			If two holes share a common edge, then a new hole will be created that removes the common edge and
	 * 			combines the two holes. This algorithm will loop through until no two holes share a common edge.
	 */
	void combineHoles();
	
	/**
	 * @brief Retrieves teh found holes state
	 * @return Returns true if all holes have been found otherwise, returns false
	 */
	bool getHolesFoundState()
	{
		return p_holesFound;
	}
	
	/**
	 * @brief Sets the found holes state to true
	 */
	void setHolesFound()
	{
		p_holesFound = true;
	}
	
	/**
	 * @brief Sets the holes of the polygon to be a list specified. This is typically used in the event holes from
	 * 			one polygon needs to be transferred over to a new polygon
	 * @param holes The holes that are to be associated with the polygon
	 */
	void setHoles(std::vector<closedPath> holes)
	{
		p_holes = holes;
	}
	
	/**
	 * @brief Transfers the holes from this polygon to a new polygon
	 * @param transfer The polygon to which to holes will be transferred to
	 */
	void transferHoles(closedPath &transfer)
	{
		transfer.setHoles(p_holes);
	}
	
	/**
	 * @brief 	The purpose of this function to to check if a specfied point lies within the path/closed contour.
	 * 			The function accomplishes this through the use of a modified version of the winding number method.
	 * 			In this method, the algorithm calculates the number of times that the point wraps around the 
	 * 			closed path. The current version of this algorithm does not use arc sin or cos. But instead checks to see
	 * 			if the point is to the left or right of an edge within the closed path. If teh number of times that the point
	 * 			is to the left of the edges is greater then the number of rights, then this means that the point lies withing the
	 * 			closed path. Note that in this algorithm arcs are represented by a box that encases the arc. If the point is found
	 * 			to exist in this box, then a test will be performed to see which side the point lies on the arc which will determine
	 * 			if the the arc is inside or outside of the polygon.
	 * @param point The point that will be tested to see if it exists inside of the polygon
	 * @return Returns true if the point lies within the closed path. Otherwise, returns false. If the point lies on an edge
	 * 			of the polygon, then this function will return true.
	 */
	bool pointInContour(wxRealPoint point);
	
	/**
	 * @brief Function that is called that will determine if this polygon is inside of another polygon
	 * @param compare The top level polygon. This polygon will be checked to see if it is contained inside of the 
	 * 					the compare polygon
	 * @return Returns true if this is contained in compare. Otherwise, returns false
	 */
	bool isInside(closedPath &compare)
	{
		bool pointFound = false;
		wxRealPoint comparePoint;
		std::map<node*, char> *compareVertexList = compare.getVertexList();
		
		for(auto lineIterator = p_closedPath.begin(); lineIterator != p_closedPath.end(); lineIterator++)
		{
			auto nodeExists = compareVertexList->find((*lineIterator)->getFirstNode());
			
			if(nodeExists == compareVertexList->end())
			{
				comparePoint = (*lineIterator)->getFirstNode()->getCenter();
				pointFound = true;
				break;
			}
			
			nodeExists = compareVertexList->find((*lineIterator)->getSecondNode());
			
			if(nodeExists == compareVertexList->end())
			{
				comparePoint = (*lineIterator)->getSecondNode()->getCenter();
				pointFound = true;
				break;
			}
			
			if((*lineIterator)->isArc())
			{
				bool lineInCompare = false;
				
				for(auto secondLineIterator = compare.getClosedPath()->begin(); secondLineIterator != compare.getClosedPath()->end(); secondLineIterator++)
				{
					if(**secondLineIterator == **lineIterator)
					{
						lineInCompare = true;
						break;
					}
						
				}
				
				if(!lineInCompare)
				{
					comparePoint = (*lineIterator)->getMidPoint();
					pointFound = true;
					break;
				}
				
			}
		}
		
		if(compare.pointInBoundingBox(comparePoint))
		{
			if(pointFound)
				return compare.pointInContour(comparePoint);
			else
				return false;
		}
		else
			return false;
	}
};

#endif