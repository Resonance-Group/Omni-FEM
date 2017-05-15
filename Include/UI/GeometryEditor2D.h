#ifndef GEOMETRYEDITOR2D_H_
#define GEOMETRYEDITOR2D_H_

#include <math.h>

#include <common/Vector.h>
#include <common/plfcolony.h>

#include <UI/geometryShapes.h>

//! This class is responsible for any math related functions that operate on the geometry shapes. This includes adding the geomerty.
/*!
    This class contains any math related function that operates directly on the geometry objects (nodes/labels/arcs/lines)
    The functions that this class contains relate to determining how many line-line/line-arc/arc-arc intersections occur and
    where the intersection point is located at. The class is responsible for calculating the distance between a point and a line
    and the distance between a point and an arc.
    The class is also responsible for any functions that add nodes/labels/arcs/lines to their respective lists
*/ 
class geometryEditor2D
{
private:
    
    /*
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
     
    //! This is the list that contains all of the nodes that the user adds to the model
    /*!
        This is the master node list and contains all of the nodes that are added. 
        A colony data type was used becuase in many cases, it has a faster access time
        then many of the stl containers. A colony also allows the use of pointers and
        only invaldates a pointer when the object that the pointer is pointing is
        deleted. For additional documentation on the colony datatype, visit the website:
        http://plflib.org/colony.htm
    */ 
    plf::colony<node> _nodeList;
    
    //! This is the list that contains all of the labels that the user adds to the model
    /*!
        This is the master block label list. For additional documentation on the colony,
        visit the website:
        http://plflib.org/colony.htm
        \sa _nodeList
    */ 
	plf::colony<blockLabel> _blockLabelList;
    
    //! This is the list that contains all of the lines that the user adds to the model
    /*!
        This is the master line list. For additional documentation on the colony,
        visit the website:
        http://plflib.org/colony.htm
        \sa _nodeList
    */ 
	plf::colony<edgeLineShape> _lineList;
    
    //! This is the list that contains all of the arcs that the user adds to the model
    /*!
        This is the master arc list. For additional documentation on the colony,
        visit the website:
        http://plflib.org/colony.htm
        \sa _nodeList
    */ 
	plf::colony<arcShape> _arcList;
    
    //! For nodes that are selected for arc/line creation, the first node is saved here
    /*! 
        This variable is the address of the first selected node when a user would like to 
        create an arc or line. This will also apply to the program if the program is manually
        creating the lines or arcs.
      
        This variable is initilized to nullptr becuase there have been cases where the gcc compiler
        did not initilize these two variables as null and they were pointing to something. 
        Which is an issue which occurs when you first select a node to be used for arc or line creation.
        The program will skip the first nodeIterator and move on to the second (or skip the second 
        and never set it). Then, when the user goes to add the line or arc, one of these two pointers are
        pointing to something other then the selected node. Thus causing the program to crash
    */ 
    node *_nodeInterator1 = nullptr;
    
    //! For nodes that are selected for arc/line creation, the second selected node is saved here
    /*!
        This variable is the address of the second selected node when a user would like to create
        an arc or a line. This is also used when the program manually creates an arc or line.
        For further documentation, see the _nodeIterator1 variable.
        \sa _nodeInterator1
    */ 
    node *_nodeInterator2 = nullptr;
    
    //! The iterator that is pointing to the location to the last node added in the colony
    /*!
        This is the iterator that contains the address of the last node added in the colony. The colony
        is an unsorted structure. This means that when objects are added to the colony,
        they may not necessarily  be added to the end of the colony. They could be added in middle or 
        closer to the beginning. This iterator saves the location of where the node was added for quick access.
    */ 
    plf::colony<node>::iterator _lastNodeAdded;
    
    //! The iterator that is pointing to the location of the last line added in the colony
    /*!
        This does the same thing as _lastNodeAdded except this is for lines
        \sa _lastNodeAdded
    */
    plf::colony<edgeLineShape>::iterator _lastLineAdded;
    
    //! THe iterator that is pointing to the location of the last arc added in the respective colony
    /*!
        This has the same purpose and function as _lastNodeAdded except this is for line
        \sa _lastNodeAdded
    */ 
    plf::colony<arcShape>::iterator _lastArcAdded;
    
    //! The iterator that is pointing to the location of the last block label added in the respective colony
    /*!
        THis has the same purpose and function as _lastNodeAdded except this is for the block labels.
        \sa _lastNodeAdded
    */ 
    plf::colony<blockLabel>::iterator _lastBlockLabelAdded;
    
    //! Function that will get the intersection X, Y point of two lines crossing each other
    /*!
        The idea behind this function is that it will transform the endpoints of the two lines to lie within the range between 0 and 1.
        If the y parts of the translated existingLine line are both greater then 0, then the existingLine line is above the x-axis
        and there can be no intersection. This also applies if the y parts are both < 0 except this would mean that the line is below the x-axis
        If the x part of the endpoints for the existingLine line are < 0, then this means that the prosepective line is to the left of the 
        prospectiveLine line which would mean that there is no intersection. if the x part ofs are > 1, then this means that the existingLine line
        is only to the right of the prospectiveLine line and there is no intersection.
        \param existingLine This is a line that already exists within the line list.
        \param prospectiveLine This is the line that is to be drawn.
        \param intersectionXPoint The returned x-point if there is an intersection.
        \param intersectionYPoint The returned y-point if there is an intersection.
        \return The function returns True if an intersection is found. Otherwise, the function returns False.
    */ 
	bool getIntersection(edgeLineShape existingLine, edgeLineShape prospectiveLine, double &intersectionXPoint, double &intersectionYPoint);
    
    //! This function will calculate the shortest distance from a vector point to an arc
    /*!
        \param vectorPoint The vector of point where the distance needs to be calculated from
        \param arcSegment The arc that is used to calculate the distance to
        \return Returns a number representing the shortest distance from the vector point to the arc
    */ 
	double shortestDistanceFromArc(Vector vectorPoint, arcShape &arcSegment);
	
	//! This function will get the number of intersection points where a line and an arc intersect
    /*!
        When a line and an arc intersect, there is at most 2 possible points of intersection.
        The first would be if the line is a tangent to the arc. In this case, there is only 1 point of 
        intersection.
        The second would be if the line is a chord to the arc. In this case, there are 2 points of
        intersections.
        This fnction will be able to determine if the line is a chord or a tangent and return
        the apprioate number of intersection points.
        \param lineSegment The line segment that could possibly intersecting the arc
        \param arcSegment The arc segment that the program is checking to see if lineSegment is intersecting
        \param pointVec This is a point to an array which holds the vector points of the intersections
        \return Returns 0 if there are no intersections, 1 if the line is a tangent, and 2 if the line is a chord
    */ 
	int getLineToArcIntersection(edgeLineShape &lineSegment, arcShape &arcSegment, Vector *pointVec);
	
	//! This function will calculate the number of intersection points where two arcs intersect
    /*!
        This does the same thing as the getLineToArcIntersection function. Except, there can be more 
        intersections beyond 2 since we are dealing with 2 arcs
        \param arcSegment1 The arc segment which is intersecting another
        \param arcSegment2 The arc segment that is being checked to see if arcSegment1 is intersecting
        \param point A pointer to an array which will store all of the vector points for the intersection
        \return Returns the total number of intersections between arcSegment1 and arcSegment2
    */ 
	int getArcToArcIntersection(arcShape& arcSegment1, arcShape &arcSegment2, Vector *point);
    
public:
    
    //! This function is used to calculate the shortest distance between a line and a node
    /*!
        This function contains that same underlying principal that operates the getIntersection function
        \param selectedNode The node that the function calculating the distance from
        \param segment The line segment that the distance is being calculated from
        \return Returns the shortest distance between the selectedNode and segment
    */ 
	double calculateShortestDistance(node selectedNode, edgeLineShape segment);
    
    //! This function is used to calculate the shortest distance between a line and a block label
    /*!
        This function is the same as the calculateShortestDistance except the node is now a 
        blockLabel
        \param selectedLabel The label that the function calculating the distance from
        \param segment The line segment that the distance is being calculated to
        \return Returns the shortest distance between the selectedNode and the segment
    */ 
	double calculateShortestDistance(blockLabel selectedLabel, edgeLineShape segment);
    
    //! This function is used to calculate the shortest distance between a line and a point
    /*!
        This function is the same as the calculateShortestDistance except the node is now a 
        point. This version is primarly used when the user clicks on the mouse.
        \param selectedPoint The point that the function is calculating the distance from. This would contain cartesiant (or polar) coordiantes. 
        \param segment The line segment that the distance is being calculated to
        \return Returns the shortest distance between the point and the segment
    */ 
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