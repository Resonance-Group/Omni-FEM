#ifndef CLOSED_PATH_H_
#define CLOSED_PATH_H_

#include <vector>
#include <algorithm>

#include <wx/wx.h>

#include <common/BoundingBox.h>

#include <UI/geometryShapes.h>

class closedPath
{
private:
	boundingBox p_boundingBox;

	double p_distance = 0;
	
	std::vector<edgeLineShape*> p_closedPath;
	
	wxRealPoint p_centerPoint = wxPoint(0, 0);
	

public:

	closedPath(edgeLineShape &firstEdge)
	{
		p_closedPath.push_back(&firstEdge);
		p_boundingBox = boundingBox(wxRealPoint(firstEdge.getFirstNode()->getCenterXCoordinate(), firstEdge.getFirstNode()->getCenterYCoordinate()));
		p_boundingBox.addPoint(wxRealPoint(firstEdge.getSecondNode()->getCenterXCoordinate(), firstEdge.getSecondNode()->getCenterYCoordinate()));
		p_centerPoint = firstEdge.getCenter();
	}
	
	closedPath(edgeLineShape *firstEdge)
	{
		p_closedPath.push_back(firstEdge);
		p_boundingBox = boundingBox(wxRealPoint(firstEdge->getFirstNode()->getCenterXCoordinate(), firstEdge->getFirstNode()->getCenterYCoordinate()));
		p_boundingBox.addPoint(wxRealPoint(firstEdge->getSecondNode()->getCenterXCoordinate(), firstEdge->getSecondNode()->getCenterYCoordinate()));
		p_centerPoint = firstEdge->getCenter();
	}
	
	closedPath()
	{
		
	}

	unsigned long getDistance()
	{
		return p_distance;
	}
	
	void addDistance(unsigned long value)
	{
		p_distance += value;
	}
	
	std::vector<edgeLineShape*> *getClosedPath()
	{
		return &p_closedPath;
	}
	
	void addEdgeToPath(edgeLineShape &addEdge)
	{
		p_distance += addEdge.getDistance();
		p_centerPoint.x = (addEdge.getCenter().x + p_closedPath.size() * p_centerPoint.x) / (p_closedPath.size() + 1);
		p_centerPoint.y = (addEdge.getCenter().y + p_closedPath.size() * p_centerPoint.y) / (p_closedPath.size() + 1);
		p_closedPath.push_back(&addEdge);
		p_boundingBox.addPoint(wxRealPoint(addEdge.getFirstNode()->getCenterXCoordinate(), addEdge.getFirstNode()->getCenterYCoordinate()));
		p_boundingBox.addPoint(wxRealPoint(addEdge.getSecondNode()->getCenterXCoordinate(), addEdge.getSecondNode()->getCenterYCoordinate()));
	}
	
	void addEdgeToPath(edgeLineShape *addEdge)
	{
		p_distance += addEdge->getDistance();
		p_centerPoint.x = (addEdge->getCenter().x + p_closedPath.size() * p_centerPoint.x) / (p_closedPath.size() + 1);
		p_centerPoint.y = (addEdge->getCenter().y + p_closedPath.size() * p_centerPoint.y) / (p_closedPath.size() + 1);
		p_closedPath.push_back(addEdge);
		p_boundingBox.addPoint(wxRealPoint(addEdge->getFirstNode()->getCenterXCoordinate(), addEdge->getFirstNode()->getCenterYCoordinate()));
		p_boundingBox.addPoint(wxRealPoint(addEdge->getSecondNode()->getCenterXCoordinate(), addEdge->getSecondNode()->getCenterYCoordinate()));
	}
	
	wxRealPoint getMaxSize()
	{
		return p_boundingBox.getMaxBounds();
	}
	
	/**
	 * @brief 	This function will re-orient all of the nodes connecting the lines such that the 
	 * 			geometry will flow counter-clockwise
	 */
	void orient()
	{
		for(auto lineIterator = p_closedPath.begin(); lineIterator != p_closedPath.end(); lineIterator++)
		{
			if((*lineIterator)->isLeft(p_centerPoint) < 0)
				(*lineIterator)->swap();
		}
	}
	
	wxRealPoint getCenter()
	{
		return p_centerPoint;
	}
};

#endif