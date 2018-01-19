#ifndef CLOSED_PATH_H_
#define CLOSED_PATH_H_

#include <vector>
#include <algorithm>

#include <wx/wx.h>

#include <common/BoundingBox.h>
#include <common/GeometryProperties/BlockProperty.h>

#include <UI/geometryShapes.h>

class closedPath
{
private:
	boundingBox p_boundingBox;

	double p_distance = 0;
	
	std::vector<edgeLineShape*> p_closedPath;
	
	wxRealPoint p_centerPoint = wxPoint(0, 0);
	
	blockProperty *p_property = nullptr;
	
	std::vector<closedPath> p_holes;
	
	std::vector<blockLabel*> p_blockLabelList;
	
	bool shareCommonEdge(closedPath firstPath, closedPath secondPath, std::vector<edgeLineShape*> &commonEdges)
	{
		commonEdges.clear();// Make sure this vector is empty before proceding
		
		for(auto firstPathIterator = firstPath.getClosedPath()->begin(); firstPathIterator != firstPath.getClosedPath()->end(); firstPathIterator++)
		{
			for(auto secondPathIterator = secondPath.getClosedPath()->begin(); secondPathIterator != secondPath.getClosedPath()->end(); secondPathIterator++)
			{
				if(*(*firstPathIterator) == *(*secondPathIterator))
					commonEdges.push_back(*firstPathIterator)
			}
		}
		
		if(commonEdges.size() > 0)
			return true;
		else
			return false;
	}

public:

	closedPath(edgeLineShape &firstEdge)
	{
		p_closedPath.push_back(&firstEdge);
		
		p_boundingBox = boundingBox(wxRealPoint(firstEdge.getFirstNode()->getCenterXCoordinate(), firstEdge.getFirstNode()->getCenterYCoordinate()));
		p_boundingBox.addPoint(wxRealPoint(firstEdge.getSecondNode()->getCenterXCoordinate(), firstEdge.getSecondNode()->getCenterYCoordinate()));
		
		if(firstEdge.isArc())
			p_boundingBox.addPoint(firstEdge.getMidPoint());
			
		p_centerPoint = firstEdge.getMidPoint();
	}
	
	closedPath(edgeLineShape *firstEdge)
	{
		p_closedPath.push_back(firstEdge);
		
		p_boundingBox = boundingBox(wxRealPoint(firstEdge->getFirstNode()->getCenterXCoordinate(), firstEdge->getFirstNode()->getCenterYCoordinate()));
		p_boundingBox.addPoint(wxRealPoint(firstEdge->getSecondNode()->getCenterXCoordinate(), firstEdge->getSecondNode()->getCenterYCoordinate()));
		
		if(firstEdge->isArc())
			p_boundingBox.addPoint(firstEdge->getMidPoint());
		
		p_centerPoint = firstEdge->getMidPoint();
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
			p_boundingBox.addPoint(addEdge.getMidPoint());
		}
	}
	
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
			p_boundingBox.addPoint(addEdge->getMidPoint());
		}
		
	}
	
	wxRealPoint getMaxSize()
	{
		return p_boundingBox.getMaxBounds();
	}
	
	wxRealPoint getCenter() const
	{
		return p_centerPoint;
	}
	
	void setProperty(blockProperty &property)
	{
		p_property = &property;
	}
	
	void setProperty(blockProperty *property)
	{
		p_property = property;
	}
	
	blockProperty *getProperty()
	{
		return p_property;
	}
	
	void addHole(closedPath *hole)
	{
		p_holes.push_back(*hole);
	}
	
	void addHole(closedPath &hole)
	{
		p_holes.push_back(hole);
	}
	
	std::vector<closedPath> *getHoles()
	{
		return &p_holes;
	}
	
	void addBlockLabel(blockLabel &label)
	{
		p_blockLabelList.push_back(&label);
	}
	
	std::vector<blockLabel*> *getBlockLabelList()
	{
		return &p_blockLabelList;
	}
	
	void clearBlockLabelList()
	{
		p_blockLabelList.clear();
	}
	
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
	
	boundingBox getBoundingBox()
	{
		return p_boundingBox;
	}
	
	void combineHoles()
	{
		bool isFinished = false;
		
		while(!isFinished)
		{
			for(auto firstHoleIterator = p_holes.begin(); firstHoleIterator != --(p_holes.end()); firstHoleIterator++)
			{
				std::vector<edgeLineShape*> commonEdgeList;
				
				for(auto secondHoleIterator = ++firstHoleIterator; secondHoleIterator != p_holes.end(); secondHoleIterator++)
				{
					if(shareCommonEdge(*firstHoleIterator, *secondHoleIterator, commonEdgeList))
					{
						
					}
				}
			}
		}
	}
};

#endif