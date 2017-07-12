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
        This function contains the same underlying principal that operates the getIntersection function
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
    
    //! This function is used to calculate the shortest distance between a point and an arc
    /*!
        This function is primarly used when the used left clicks on the canvas.
        \sa shortestDistanceFromArc
        \param selectedPoint The point that the function us calculating the distance from. This would contain the cartesian (or polar) coordiantes.
        \param arcSegment The arc segment that the distance is being calculated to.
        \return Returns the shortest distance between the point and the segment
    */ 
    double calculateShortestDistanceFromArc(wxRealPoint selectedPoint, arcShape arcSegment)
    {
        return shortestDistanceFromArc(Vector(selectedPoint.x, selectedPoint.y), arcSegment);
    }
    
    //! This function will save the address of two node objects that are to be used for line/arc creation
    /*!
        This function will edit the _nodeInterator1 and _nodeInterator2 variables that are used to save the address
        of two selected nodes. These nodes are use for creating a line or arc between the nodes.
        \sa  _nodeInterator1, _nodeInterator2
        \param nodeAddress The address of a node that will be used for line/arc creation
        \return Returns true if 2 nodes have been saved. Otherwise, return false
    */ 
    bool setNodeIndex(node &nodeAddress)
    {
        if(_nodeInterator1 == nullptr)
        {
            _nodeInterator1 = &nodeAddress;
            return false;
        }
        else if(_nodeInterator2 == nullptr)
        {
            _nodeInterator2 = &nodeAddress;
            return true;
        }
        
        return false;
    }

    //! Function that will return a pointer to the node list
    /*!
        By returning a pointer to the node list, this makes it much easier to edit the node list or to grab additional datatypes for
        example if the programmer needs ot loop through the entire node list. There is no requirement for a copy of memory. This
        method actually saves memory since we are only returning an address
        \return Returns a pointer pointing to the node list
    */ 
    plf::colony<node> *getNodeList()
    {
        return &_nodeList;
    }
    
    //! Function that is used to set the node list
    /*!
        \param list The node list that _nodeList will be set to
    */ 
    void setNodeList(plf::colony<node> list)
    {
        _nodeList = list;
    }
    
    //! Function that will get the block list and return a pointer pointing to the block list
    /*!
        Works similair to getNodeList() but is for the block labels
        \sa getNodeList()
        \return Returns a pointer pointing to the block labels list
    */ 
    plf::colony<blockLabel> *getBlockLabelList()
    {
        return &_blockLabelList;
    }
    
    //! Function that is used to set the node list
    /*!
        \param list The node list that _nodeList will be set to
    */ 
    void setBlockLabelList(plf::colony<blockLabel> list)
    {
        _blockLabelList = list;
    }
    
    //! Function that will get the line list and return a pointer pointing to the line list
    /*!
        Works similair to getNodeList() but is for the line labels
        \sa getNodeList()
        \return Returns a pointer pointing to the line labels list
    */ 
    plf::colony<edgeLineShape> *getLineList()
    {
        return &_lineList;
    }
    
    //! Function that is used to set the line list
    /*!
        \param list The line list that _lineList will be set to
    */ 
    void setLineList(plf::colony<edgeLineShape> list)
    {
        _lineList = list;
    }
    
    //! Function that will get the arc list and return a pointer pointing to the arc list
    /*!
        Works similair to getNodeList() but is for the arc labels
        \sa getNodeList()
        \return Returns a pointer pointing to the arc labels list
    */ 
    plf::colony<arcShape> *getArcList()
    {
        return &_arcList;
    }
    
    //! Function that is used to set the arc list
    /*!
        \param list The arc list that _arcList will be set to
    */ 
    void setArcList(plf::colony<arcShape> list)
    {
        _arcList = list;
    }
    
    //! Function that is called in order to add a node a list
    /*!
        This function will perform all neccessary checks into order to 
        add the node to the list. The checks include, if a node was placed
        ontop of another node or blocklabel, if a node was placed ontop
        of a line and if a node was placed ontop of an arc.
        In the case that the node was placed ontop of a node or blocklabel,
        the function will not add a node to the list. 
        If the node is placed ontop an line or arc, then the function will
        break the line or arc up into two lines or arcs.
        \param xPoint The x-point location in cartesian coordinates to add the node
        \param yPoint The y-point location in cartesian coordinates to add the node
        \param distanceNode This is a tolerance parameter in which this value specifies the minimum distance when a node is ontop of another node/label or how close a node needs to be to an arc/line in order to break the arc/line into 2 seperate pieces
        \return Function returns True if node was successfully added. Otherwise, return False. A false condition occurs if the node is placed ontop of another node/label.
    */ 
    bool addNode(double xPoint, double yPoint, double distanceNode);
    
    //! Adds a node to the list for the purpose of dragging
    /*!
        This function is called alot when the user wants to add a node to the canvas.
        First, this function will get called on the down of the left mouse button.
        This will override any checks to allow the user to drag the node to the proper location
        Once there, the user will release the left mouse button which will call the function
        addNode which contains all of the needed checks. A node that is created by this function
        is only temporary. The arguements here are to give the node a starting position.
        \sa addNode
        \param xPoint The x part of the location to added a dragging node
        \param yPoint The y part of the location to add a dragging node
    */ 
    void addDragNode(double xPoint, double yPoint)
    {
        node newNode;
        newNode.setCenter(xPoint, yPoint);
        newNode.setDraggingState(true);
        _lastNodeAdded = _nodeList.insert(newNode);
    }
    
    //! Function that is called to add a block label to the block label list
    /*!
        This function contains all of the checks needed in order to add a block label to the 
        list of block labels. This function will check to see if the blockl label is 
        placed on top of a node, ontop of another block label, ontop of a 
        line and ontop of an arc. If any of these conditions are true, then the
        block label will not be created.
        \param xPoint The x-coordinate of the location where the block lable is to be placed. This is in the cartesian coordinates (or polar)
        \param yPoint The y-coordinate of the location where the block label is to be placed. This is in cartesian coordinates (or polar)
        \param tolerance This is a tolerance parameter in which this value specifies the minimum distance when a block label is ontop of a node, another block label, arc, and line in order for the block label to not be added
        \return Returns True if the block label is able to be added. Otherwise, returns False.
    */ 
    bool addBlockLabel(double xPoint, double yPoint, double tolerance);
    
    //! This function adds a block label to the list for thr purpose of dragging the label across the canvas
    /*!
        This function has the same purpose as the addDragnode function except 
        this function works with block labels
        \sa addDragNode
        \param xPoint The x-coordinate of the location where the block lable is to be placed. This is in the cartesian coordinates (or polar)
        \param yPoint The y-coordinate of the location where the block label is to be placed. This is in cartesian coordinates (or polar)
    */ 
    void addDragBlockLabel(double xPoint, double yPoint)
    {
        blockLabel newLabel;
        newLabel.setCenter(xPoint, yPoint);
        newLabel.setDraggingState(true);
        _lastBlockLabelAdded = _blockLabelList.insert(newLabel);
    }
    
    //! Function that is called in order to add a line to the line list
    /*!
        This is the main function that is called if the user (or program) would
        like to add a line to the line list. This function takes in the address
        of the two points. The function will also perform an necessary checks to
        see if the line passes through a node, if the line has already been created
        and if there are any intersections with any arcs or other lines. If 
        any of these cases are true, then the function will handle all of the cases apprioately.
        There are addition to checks to determine the user has selected two node already as endpoints
        or if the user is passing in the address to the two nodes for line creation
        \param firstNode The first endpoint of the line
        \param secondNode The second endpoint of the line
        \param tolerance This is the value that is used for if any nodes need to be created, the value is passed into the addNode function
        \return Returns True if the line is successfully created. Otherwise returns False. A false condition occurs if the line has already been created, if the two endpoints are the same, or if one of the two nodes does not exist. 
    */ 
    bool addLine(node *firstNode, node *secondNode, double tolerance = 0);
    
    //! Function that is used to add a line where the nodes are not addresses
    /*!
        This is a wrapper function where the arguements are not 
        address to the endpoints (nodes) of the line. This function
        will convert them to addresses and call the addLine function that takes
        in addresses.
        \sa addNode
        \param firstNode The first endpoint of the line
        \param secondNode The second endpoint of the line
        \param tolerance This is the value that is used for if any nodes need to be created, the value is passed into the addNode function
        \return Returns True if the line is successfully created. Otherwise returns False.
    */ 
    bool addLine(node &firstNode, node &secondNode, double tolerance)
    {
        return addLine(&firstNode, &secondNode, tolerance);
    }
    
    //! Function that is called to add a line to the list where the two nodes have already been selected
    /*!
        This function calls the addLine function and passes in null pointers as the arguments
        By passing in null pointers, this tells the addLine function that two endpoints 
        have already been selected are are saved in the variables _nodeInterator1 and _nodeInterator2.
        \sa addLine
        \param tolerance This is the value that is used for if any nodes need to be created, the value is passed into the addNode function
        \return Returns True if the line is successfully added. Otherwise, returns false.
    */ 
    bool addLine(double tolerance = 0)
    {
        return addLine(nullptr, nullptr, tolerance);
    }
    
    //! Function that is called when the user or the program needs to add an arc to the arc list
    /*!
        For arcs, an arc shape containing the selected nodes, boundary conditions, and nuumber of segments
        should be passed into here first. Mainly becuase the arc needs to be setup before any calculation can 
        be done on the arc and it simplifies the number of arguments needed for the function to work.
        One thing to note about arcs is that the order of selection matters. All arcs are drawn as 
        counterclockwise being positive. Therefor, an arc is drawn concave if the endpoint to the right
        is selected first and convex if the node to the left is selected first.
        This function also checks and handles the following cases: if the arc crosses a node,
        if the arc intersects another arc or if the arc intersects a line, and if the arc already exists 
        in the list.
        The function can handle first the selection of the endpoints but it is highly recommmanded
        that the arSeg argument contains the selection of the nodes, any BC, and number of segments before 
        calling this function.
        \param arcSeg The arc that is to be added to the list 
        \param tolerance This is the value that is used for if any nodes need to be created at intersection points. This value is passed into the addNode function
        \param nodesAreSelected Boolean used to indicate if the program needs to check the selected nodes variables to grab which nodes the user has selected
        \return Returns True if the function successfully added the arc to the list. Otherwise returns False. A false condition occurs if the arc is already in the list, if the two selected nodes are the same, or if one of the two selected nodes does not exist 
    */ 
    bool addArc(arcShape &arcSeg, double tolerance, bool nodesAreSelected);
    
    //! Function that is called in order to reset the seelected nodes variables back to null pointers
    /*!
        The default value for _nodeInterator1 and _nodeInterator2 is the null pointer. This function
        is typically called at the end of the add line and add arc functions. This function
        is also called if adding a line/arc fails.
    */ 
    void resetIndexs()
    {
        _nodeInterator1 = nullptr;
        _nodeInterator2 = nullptr;
    }
    
    //! Function that is called in order to swap the two selected nodes variable
    /*!
        This function is mainly for any arc related algoritms. For arcs, the order
        of the selected nodes matters. If the node to the right is selected first, then
        the arc will be drawn concave style. If the node to the left is selected first,
        then the arc will be drawn convex style
    */ 
    void switchIndex()
    {
        node *temp = _nodeInterator1;
        _nodeInterator1 = _nodeInterator2;
        _nodeInterator2 = temp;
    }
    
    //! Function that is used to grab the last node that was added to the colony
    /*!
        In short, the colony datatype is not a sorted list. This means that the node that
        is added to the list does not mean that the node is on the top of the list.
        The node could easily be in somewhere in the middle. For more documentation regarding
        the colony datatype, refer to the following link:
        http://plflib.org/colony.htm
        So, during a copy routine, if the program is copying a line or arc, then the program will
        need to grab the location of the last node added. Iterators and pointers are similiar to each other.
        So much so, that they are handled the same. So the iterator was choosen as a convience.
        \return The function returns an iterator which is pointing to the location of the last added node to the colony.
    */ 
    plf::colony<node>::iterator getLastNodeAdd()
    {
        return _lastNodeAdded;
    }
    
    //! Function that is used to get the last line added to the colony
    /*!
        Works the same way as getLastNodeAdd() except this works with lines
        \sa getLastNode()
        \return The function returns an iterator which is pointing to the location of the last added line to the colony.
    */ 
    plf::colony<edgeLineShape>::iterator getLastLineAdded()
    {
        return _lastLineAdded;
    }
    
    //! Function that is used to get the last arc added to the arc colony
    /*!
        Works the same way as getLastNodeAdd() except this works with arcs
        \sa getLastNode()
        \return The function returns an iterator which is pointing to the location of the last added arc to the colony.
    */ 
    plf::colony<arcShape>::iterator getLastArcAdded()
    {
        return _lastArcAdded;
    }
    
    //! Function that is used to get the last block label added to the block label colony
    /*!
        Works the same way as getLastNodeAdd() except this works with block labels
        \sa getLastNode()
        \return The function returns an iterator which is pointing to the location of the last added block label to the colony.
    */
    plf::colony<blockLabel>::iterator getLastBlockLabelAdded()
    {
        return _lastBlockLabelAdded;
    }
    
    //! Function that is used to check all of the geomtery and determine if there are any intersections with any shapes
    /*!
        This function is primarly used after a user moves a geometry shape around. During a move, there could be intersections between 
        nodes/lines/arcs. This function will check all geometry (or the selected geometry) if any intersections. If there are intersections,
        then the function will place a node at the intersections. As for block labels, the function will check to see if after a move, there
        are any block labels ontop of a geometry piece, if so, this function will return true.
        \param editedGeometry Arguement that is used to specify what geometry needs to be checked for intersections
        \param tolerance This is the value that is used for if any nodes need to be created at intersection points. This value is passed into the addNode function
        \return Returns True if there are any block labels ontop of another geometry shape. Otherwise, returns False.
    */ 
    bool checkIntersections(EditGeometry editedGeometry, double tolerance);
    
    //! Function that is used to create a fillet where two lines or two arcs or one line and one arc converge at.
    /*!
        This function will loop through the entire node list and find the nodes that are selected for fillet creation.
        If the node is selected, the function will ensure that there is only two lines or two arcs or one line and one arc
        that converges to the node. Construction lines/arcs are not counted.
        The function has three different cases for if two lines or two arcs or one line and one arc converge at the node.
        If there function is able to succesfully create a fillet, the function will return true. If the function 
        is unable to create the fillet, the function will leave the node intact and there will be no change to what is drawn
        on the screen. 
        \param radius The radius of the fillet
        \return Returns true if even one fillet is succesfully created. Otherwise returns False.
    */ 
    bool createFillet(double radius);
};

#endif