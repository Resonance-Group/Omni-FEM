#ifndef GEOMETRYEDITOR2D_H_
#define GEOMETRYEDITOR2D_H_

#include <vector>
#include <math.h>

#include <common/Vector.h>

#include <UI/geometryShapes.h>

class geometryEditor2D
{
private:
    std::vector<node> _nodeList;
    
	std::vector<blockLabel> _blockLabelList;
    
	std::vector<edgeLineShape> _lineList;
    
	std::vector<arcShape> _arcList;
    
    int _tolerance = 2;
    
    long _firstSelectedNodeIndex = -1;
    
    // Add in functions that are used to calculate intersection points here
    
    /*! This function will check to see if there is an intersection between two lines. If so, get the node of intersection and return true
     * node0 is the first node that the user selects
     * node1 is the second node that the user selects
     * lineSegment is the line segment index that will be checked for an intersection
     * intersectionXPoint and YPoint are the (X, Y) intercetion points of the two lines
     */
	bool getIntersection(int node0, int node1, int lineSegment, double &intercetionXPoint, double &intercestionYPoint);
    
    //! This function will determine the center and the radius of the given arc.
	void getCircle(arcShape &arc, Vector &center, double &radius);
    
    /*! This function will calculate the shortest distance from a point to an arc */
	double shortestDistanceFromArc(Vector point, arcShape &arcSegment);
	
	/*! This function will get the number of instersection points where a line and an arc intersect */
	int getLineToArcIntersection(edgeLineShape &lineSegment, arcShape &arcSegment, Vector *pointVec);
	
	/*! This function will calculate the number of intersection points where two arcs intersect */
	int getArcToArcIntersection(arcShape& arcSegment1, arcShape &arcSegment2, Vector *point);
    
    /*! This function is used to calcualte if the shortest distance between a line a node */
	double calculateShortestDistance(double p, double q, int segmentIndex, std::vector<node> const &refNodeList, std::vector<edgeLineShape> const &refLineList);

public:
    std::vector<node> *getNodeList()
    {
        return &_nodeList;
    }
    
    std::vector<blockLabel> *getBlockLabelList()
    {
        return &_blockLabelList;
    }
    
    std::vector<edgeLineShape> *getLineList()
    {
        return &_lineList;
    }
    
    std::vector<arcShape> *getArcList()
    {
        return &_arcList;
    }
    
    void setFirstSelectedNodeIndex(long index)
    {
        _firstSelectedNodeIndex = index;
    }
    
    long getFirstSelectedNodeIndex()
    {
        return _firstSelectedNodeIndex;
    }
    
    void addNode(double xPoint, double yPoint, double distance);
    
    void addBlockLabel();
    
    void addLine(int node0, int node1, edgeLineShape *parseSegment);
    
    void addArc(arcShape &arcSeg, double tolerance);
	
};

#endif