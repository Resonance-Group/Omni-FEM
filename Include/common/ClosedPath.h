#ifndef CLOSED_PATH_H_
#define CLOSED_PATH_H_

#include <vector>
#include <algorithm>

#include <wx/wx.h>

#include <UI/geometryShapes.h>

class closedPath
{
private:
	double p_distance = 0;
	
	std::vector<edgeLineShape*> p_closedPath;
	
	wxRealPoint p_maxSize;

public:

	closedPath(edgeLineShape &firstEdge)
	{
		p_closedPath.push_back(&firstEdge);
		p_maxSize.x = std::max(firstEdge.getFirstNode()->getCenterXCoordinate(), firstEdge.getSecondNode()->getCenterXCoordinate());
		p_maxSize.y = std::max(firstEdge.getFirstNode()->getCenterYCoordinate(), firstEdge.getSecondNode()->getCenterYCoordinate());
	}
	
	closedPath(edgeLineShape *firstEdge)
	{
		p_closedPath.push_back(firstEdge);
		p_maxSize.x = std::max(firstEdge->getFirstNode()->getCenterXCoordinate(), firstEdge->getSecondNode()->getCenterXCoordinate());
		p_maxSize.y = std::max(firstEdge->getFirstNode()->getCenterYCoordinate(), firstEdge->getSecondNode()->getCenterYCoordinate());
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
		p_closedPath.push_back(&addEdge);
		p_maxSize.x = std::max(std::max(addEdge.getFirstNode()->getCenterXCoordinate(), addEdge.getSecondNode()->getCenterXCoordinate()), p_maxSize.x);
		p_maxSize.y = std::max(std::max(addEdge.getFirstNode()->getCenterYCoordinate(), addEdge.getSecondNode()->getCenterYCoordinate()), p_maxSize.y);
	}
	
	void addEdgeToPath(edgeLineShape *addEdge)
	{
		p_distance += addEdge->getDistance();
		p_closedPath.push_back(addEdge);
		p_maxSize.x = std::max(std::max(addEdge->getFirstNode()->getCenterXCoordinate(), addEdge->getSecondNode()->getCenterXCoordinate()), p_maxSize.x);
		p_maxSize.y = std::max(std::max(addEdge->getFirstNode()->getCenterYCoordinate(), addEdge->getSecondNode()->getCenterYCoordinate()), p_maxSize.y);
	}
	
	wxRealPoint getMaxSize()
	{
		return p_maxSize;
	}
};

#endif