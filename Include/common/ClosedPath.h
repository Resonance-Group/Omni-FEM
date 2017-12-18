#ifndef CLOSED_PATH_H_
#define CLOSED_PATH_H_

#include <vector>

#include <UI/geometryShapes.h>

class closedPath
{
private:
	unsigned long p_distance = 0;
	
	std::vector<edgeLineShape*> p_closedPath;
	
public:

	closedPath(edgeLineShape &firstEdge)
	{
		p_closedPath.push_back(&firstEdge);
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
		p_closedPath.push_back(&addEdge);
	}
}