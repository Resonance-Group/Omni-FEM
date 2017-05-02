#ifndef GEOMETRYEDITOR2D_H_
#define GEOMETRYEDITOR2D_H_

#include <vector>
#include <list>
#include <deque>
#include <math.h>

#include <glew.h>
#include <freeglut.h>
/*
#include <gl.h>
#include <glu.h>
*/
#include <common/Vector.h>
#include <common/plfcolony.h>
#include <common/wxGLString.h>

#include <UI/geometryShapes.h>

class geometryEditor2D
{
private:
    
    /*! /brief
     *  So you might be thinking, why use a colony instead of a vector or a list or a deque?
     *  It is simple, for a vector, when something is added or removed, the vector
     *  copies all of of the contents from one memory location to another. This can cause significant speed issues
     *  with a large amount of data. Also, in some datatypes, we are storing the address of the node.
     *  If the address changes everytime we add or remove soemthing from
     *  the vector, this can create a number of issues.
     *  For a list, everything was already coded using vectors when the vector issue was discover which results
     *  in a preference for using a deque since it contains many functions similiar to that of the vector and so the deque datatype was
     *  the prefered choice. The list is also much slower then a deque. However, it was discovered that when an element 
     *  was added or removed for the deque, the addresses became invalidated.A hybrid was needed between the 
     *  list's ability to keep all of the addresses validated when changing the list but have the speed of a deque.
     *  Further research found the plf::colony class. It functions similiar to a list
     *  and you have many of the benefits of using a list but with the added speed bonus of a deque
     */ 
    plf::colony<node> _nodeList;
    
	plf::colony<blockLabel> _blockLabelList;
    
	plf::colony<edgeLineShape> _lineList;
    
	plf::colony<arcShape> _arcList;
    
    /*! The reason that these two variables are initilized to nullptr on first go around is this,
     *  There have been cases where the gcc compiler did not initilize these two variables as null
     *  and they were pointing to something. Which is an issue which occurs when you first select
     *  a node to be used for arc or line creation. The program will skip the first nodeIterator
     *  and move on to the second (or skip the second and never set it). Then, when you
     *  go to add the line or arc, one of these two pointers are pointing to something other 
     *  then the selected node. Thus causing the program to crash
     */ 
    node *_nodeInterator1 = nullptr;// This is the index of the first selected node
    
    node *_nodeInterator2 = nullptr;// This is the index of the second selected node
    
    plf::colony<node>::iterator _lastNodeAdded;
    
    plf::colony<edgeLineShape>::iterator _lastLineAdded;
    
    plf::colony<arcShape>::iterator _lastArcAdded;
    
    plf::colony<blockLabel>::iterator _lastBlockLabelAdded;
    
    int _tolerance = 2;
    
    double _zoomFactorPointer = 1.0;
    
    /*! This function will check to see if there is an intersection between two lines. If so, get the node of intersection and return true
     * node0 is the first node that the user selects
     * node1 is the second node that the user selects
     * lineSegment is the line segment index that will be checked for an intersection
     * intersectionXPoint and YPoint are the (X, Y) intercetion points of the two lines
     */
	bool getIntersection(edgeLineShape prospectiveLine, edgeLineShape intersectionLine, double &intersectionXPoint, double &intersectionYPoint);
    
    /*! This function will calculate the shortest distance from a point to an arc */
	double shortestDistanceFromArc(Vector vectorPoint, arcShape &arcSegment);
	
	/*! This function will get the number of instersection points where a line and an arc intersect */
	int getLineToArcIntersection(edgeLineShape &lineSegment, arcShape &arcSegment, Vector *pointVec);
	
	/*! This function will calculate the number of intersection points where two arcs intersect */
	int getArcToArcIntersection(arcShape& arcSegment1, arcShape &arcSegment2, Vector *point);
    
    

public:
    
    /*! This function is used to calcualte if the shortest distance between a line a node */
	double calculateShortestDistance(node selectedNode, edgeLineShape segment);
    
    /*! This function is used to calcualte if the distance between a line a node */
	double calculateShortestDistance(blockLabel selectedNode, edgeLineShape segment);
    
    double calculateShortestDistance(wxRealPoint selectedPoint, edgeLineShape segment);
    
    double calculateShortestDistanceFromArc(wxRealPoint selectedPoint, arcShape arcSegment)
    {
        return shortestDistanceFromArc(Vector(selectedPoint.x, selectedPoint.y), arcSegment);
    }
    
    bool setNodeIndex(node &iterator)
    {
        if(_nodeInterator1 == nullptr)
        {
            _nodeInterator1 = &iterator;
            return false;
        }
        else if(_nodeInterator2 == nullptr)
        {
            _nodeInterator2 = &iterator;
            return true;
        }
        
        return false;
    }

    plf::colony<node> *getNodeList()
    {
        return &_nodeList;
    }
    
    void setNodeList(plf::colony<node> list)
    {
        _nodeList = list;
    }
    
    plf::colony<blockLabel> *getBlockLabelList()
    {
        return &_blockLabelList;
    }
    
    void setBlockLabelList(plf::colony<blockLabel> list)
    {
        _blockLabelList = list;
    }
    
    plf::colony<edgeLineShape> *getLineList()
    {
        return &_lineList;
    }
    
    void setLineList(plf::colony<edgeLineShape> list)
    {
        _lineList = list;
    }
    
    plf::colony<arcShape> *getArcList()
    {
        return &_arcList;
    }
    
    void setArcList(plf::colony<arcShape> list)
    {
        _arcList = list;
    }

    bool addNode(double xPoint, double yPoint, double distanceNode);
    
    void addDragNode(double xPoint, double yPoint)
    {
        node newNode;
        newNode.setCenter(xPoint, yPoint);
        newNode.setDraggingState(true);
        _lastNodeAdded = _nodeList.insert(newNode);
    }
    
    bool addBlockLabel(double xPoint, double yPoint, double tolerance);
    
    void addDragBlockLabel(double xPoint, double yPoint)
    {
        blockLabel newLabel;
        newLabel.setCenter(xPoint, yPoint);
        newLabel.setDraggingState(true);
        _lastBlockLabelAdded = _blockLabelList.insert(newLabel);
    }
    
    bool addLine(node &firstNode, node &secondNode, double tolerance)
    {
        return addLine(&firstNode, &secondNode, tolerance);
    }
    
    bool addLine(node *firstNode, node *secondNode, double tolerance = 0);
    
    bool addLine(node &firstNode, node *secondNode, double tolerance)
    {
        return addLine(&firstNode, secondNode, tolerance);
    }
    
    bool addLine(node *firstNode, node &secondNode, double tolerance)
    {
        return addLine(firstNode, &secondNode, tolerance);
    }
    
    bool addLine()
    {
        return addLine(nullptr, nullptr);
    }
    
    bool addLine(double tolerance)
    {
        return addLine(nullptr, nullptr, tolerance);
    }
    
    bool addArc(arcShape &arcSeg, double tolerance, bool nodesAreSelected);
    
    void resetIndexs()
    {
        _nodeInterator1 = nullptr;
        _nodeInterator2 = nullptr;
    }
    
    void switchIndex()
    {
        node *temp = _nodeInterator1;
        _nodeInterator1 = _nodeInterator2;
        _nodeInterator2 = temp;
    }
    
    plf::colony<node>::iterator getLastNodeAdd()
    {
        return _lastNodeAdded;
    }
    
    plf::colony<edgeLineShape>::iterator getLastLineAdded()
    {
        return _lastLineAdded;
    }
    
    plf::colony<arcShape>::iterator getLastArcAdded()
    {
        return _lastArcAdded;
    }
    
    plf::colony<blockLabel>::iterator getLastBlockLabelAdded()
    {
        return _lastBlockLabelAdded;
    }
    
    //! If nodes/lines/arcs are moved, then this function needs to be called in order to check if the displaced geometry intercets with other geometries
    bool checkIntersections(EditGeometry editedGeometry, double tolerance);
    
    bool createFillet(double radius);
};

#endif