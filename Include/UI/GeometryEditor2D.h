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
    
    long _nodeIndex1 = -1;// This is the index of the first selected node
    
    long _nodeIndex2 = -1;// This is the index of the second selected node
    
    int _tolerance = 2;
    
    double *_zoomFactorPointer;
    
    // Add in functions that are used to calculate intersection points here
    
    /*! This function will check to see if there is an intersection between two lines. If so, get the node of intersection and return true
     * node0 is the first node that the user selects
     * node1 is the second node that the user selects
     * lineSegment is the line segment index that will be checked for an intersection
     * intersectionXPoint and YPoint are the (X, Y) intercetion points of the two lines
     */
	bool getIntersection(edgeLineShape prospectiveLine, edgeLineShape intersectionLine, double &intersectionXPoint, double &intersectionYPoint);
    
    //! This function will determine the center and the radius of the given arc.
	void getCircle(arcShape &arc, Vector &center, double &radius);
    
    /*! This function will calculate the shortest distance from a point to an arc */
	double shortestDistanceFromArc(Vector point, arcShape &arcSegment);
	
	/*! This function will get the number of instersection points where a line and an arc intersect */
	int getLineToArcIntersection(edgeLineShape &lineSegment, arcShape &arcSegment, Vector *pointVec);
	
	/*! This function will calculate the number of intersection points where two arcs intersect */
	int getArcToArcIntersection(arcShape& arcSegment1, arcShape &arcSegment2, Vector *point);
    
    /*! This function is used to calcualte if the shortest distance between a line a node */
	double calculateShortestDistance(double p, double q, edgeLineShape segment);

public:
    bool setNodeIndex(unsigned long index)
    {
        if(_nodeIndex1 == -1)
        {
            _nodeIndex1 = index;
            return false;
        }
        else if(_nodeIndex1 != -1)
        {
            _nodeIndex2 = index;
            return true;
        }
        
        return false;
    }

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

    void addNode(double xPoint, double yPoint);
    
    void addDragNode(double xPoint, double yPoint)
    {
        node newNode;
        newNode.setCenter(xPoint, yPoint);
        _nodeList.push_back(newNode);
    }
    
    void addBlockLabel(double xPoint, double yPoint);
    
    void addLine(int node0, int node1);
    
    void addLine()
    {
        addLine(-1, -1);
    }
    
    void addArc(arcShape &arcSeg, double tolerance);
    
    void setZoomFactorAddress(double &address)
    {
        _zoomFactorPointer = &address;
    }
    
    void resetIndexs()
    {
        _nodeIndex1 = -1;
        _nodeIndex2 = -1;
    }
	
};

#endif