#ifndef GEOMETRY_SHAPES_H_
#define GEOMETRY_SHAPES_H_

#include <math.h>

#include <glew.h>
#include <freeglut.h>

#include <wx/wx.h>

#include <common/Vector.h>

#include <common/GeometryProperties/BlockProperty.h>
#include <common/GeometryProperties/NodeSettings.h>
#include <common/GeometryProperties/SegmentProperties.h>

#include <UI/ModelDefinition/OGLFT.h>

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

/**
 * @class geometry2D
 * @author Phillip
 * @date 16/06/17
 * @file geometryShapes.h
 * @brief   This is the base class for all of the geometry shapes
 *          This class contains all of the properties and methods that
 *          is common through out all of the geometry shapes.
 *          For example, a boolean to describe if the geometry shape
 *          is selected or not and the x and y coordinate
 *          position for the center.
 */
class geometry2D
{
private:
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive &ar, const unsigned int version)
	{
		ar & xCenterCoordinate;
		ar & yCenterCoordinate;
	}
protected:
	
	//! This is a boolean that willl indicate if the user selects the geometric shape
	bool _isSelected = false;

	//! This data type stroes the center x  position in Cartesian Coordiantes
	/*! 
		For arcs, this is the center of the circle.
		For lines, this is the midpoint
		For nodes and blocklabels, this would be the center of the square.
	*/
	double xCenterCoordinate = 0;
	
	//! This data type stores the center y position in Cartesians Coordiantes
    /*!
        For arcs, this is the center of the circle.
		For lines, this is the midpoint
		For nodes and blocklabels, this would be the center of the square.
    */ 
	double yCenterCoordinate = 0;
    
public:
	
    //! The constructor for the class
	geometry2D()
    {
        
    }
	
	//! Function used to set the X coordinate for the center point of the shape
    /**
     * @brief This function will set the center X coordinate position for the shape
     * @param xCenter The center position of the geometry shape in the x-plane
     */
	void setCenterXCoordinate(double xCenter)
    {
        xCenterCoordinate = xCenter;
    }
	
	//! Function used to set the Y coordiante for the center point of the shape
    /**
     * @brief This function will set the center Y coordinate position for the shape
     * @param yCenter The center position of the geometry shape in the y-plane
     */
	void setCenterYCoordiante(double yCenter)
    {
        yCenterCoordinate = yCenter;
    }
	
	//! Function used to get the X Coordinate of the center point point of the shape
    /**
     * @brief Retrieves the x position of the center 
     * @return Returns a number representing the center X coordinate
     */
	double getCenterXCoordinate() const
    {
        return xCenterCoordinate;
    }
	
	//! Function used to get the Y Coordinate of the center point point of the shape
    /**
     * @brief Retrieves the y position of the center
     * @return Returns a number representing the center Y coordinate
     */
	double getCenterYCoordinate() const
    {
        return yCenterCoordinate;
    }

	//! the function will be called when the user selects the geomtry shape
    /**
     * @brief Sets the select state of the geometry shape
     * @param state Set to true in order to indicate if the geometry
     *              piece is to be selected. All selected geometry piecces
     *              will turn red.
     */
	void setSelectState(bool state)
    {
        _isSelected = state;
    }
	
	//! This function will return the selected status
    /**
     * @brief Retrieves the selected state of the geometry piece
     * @return Returns true if geometry piece is selected. Otherwise, returns false
     */
	bool getIsSelectedState()
    {
        return _isSelected;
    }
	
	/**
	 * @brief Returns the center point of the geometry piece
	 * @return Returns the wxRealPoint representing the center of the geometry
	 */
	wxRealPoint getCenter()
	{
		return wxRealPoint(xCenterCoordinate, yCenterCoordinate);
	}
};

/**
 * @class rectangleShape
 * @author Phillip
 * @date 16/06/17
 * @file geometryShapes.h
 * @brief   This is the base class for the block label and the node shapes.
 *          Both are rectangles but, one is drawn black and the other is
 *          drawn blue. They also have different properties that are
 *          associated with them,
 */
class rectangleShape : public geometry2D
{
private:
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive &ar, const unsigned int version)
	{
		ar & boost::serialization::base_object<geometry2D>(*this);
	}
    
    //! Boolean used to determine if the node/block label is draggin
    /*!
        Dragging occurs when the user holds the left mouse button down.
        The node/block label will drag across the screen. Note that this
        mode overwites all geometry checks and only when the use releases the 
        mouse button does the program place a node/block label with 
        the checks onto the canvas
    */ 
    bool _isDragging = false;
    
public:

    //! The constructor for the class
    rectangleShape() : geometry2D()
    {
        
    }
    
    //! The constructor for the clas
    /*!
        This constructor is called only when there is 
        a specific x and y center coordinate to specify
        \param xCenterPoint The x-coordinate position of the center
        \param yCenterPoint The y-coordinate position of the center
    */ 
	rectangleShape(double xCenterPoint, double yCenterPoint) : geometry2D()
    {
        xCenterCoordinate = xCenterPoint;
        yCenterCoordinate = yCenterPoint;
    }
	
	/**
	 * @brief Computes the distance between the rectangle shape and a given point
	 * @param xp The x-coordinate position of the location to calculate the distance to
	 * @param yp The y-coordinate position of the location to calculate the distance to
	 * @return Returns a number representing the distance between a point in space and the rectangle shape
	 */
    double getDistance(double xp, double yp)
    {
        return sqrt(pow((xCenterCoordinate - xp), 2) + pow((yCenterCoordinate - yp), 2));
    }
    
    /**
     * @brief   Computes the distance between the rectangle shape and a wxRealPoint.
     *          This function operates much like the function getDistance(double xp, double yp)
     *          except the parameter is in a more convient format
     * @param point The wxRealPoint in space to calculate the distance to
     * @return Returns a number representing the distance between a point in space and the rectangle shape
     */
    double getDistance(wxRealPoint point)
    {
        return sqrt(pow((xCenterCoordinate - point.x), 2) + pow((yCenterCoordinate - point.y), 2));
    }
    
    /**
     * @brief Computes the distance between the rectangle shape and another rectangle shape
     * @param testNode The other rectangle shape to compute the distance to
     * @return Returns a number representing the distance between a point in space and the rectangle shape
     */
    double getDistance(rectangleShape testNode)
    {
        return sqrt(pow(xCenterCoordinate - testNode.getCenterXCoordinate(), 2) + pow(yCenterCoordinate - testNode.getCenterYCoordinate(), 2));
    }
    
    /**
     * @brief Function that is called in order to reset the center of the rectangle object
     * @param xCoor The new center in the x-plane
     * @param yCoor The new center in the y-plane
     */
    void setCenter(double xCoor, double yCoor)
    {
        xCenterCoordinate = xCoor;
        yCenterCoordinate = yCoor;
    }
    
    /**
     * @brief This function will move the position of the center
     * @param xCoor The amount to move the center by in the x-position
     * @param yCoor THe amount to move the center by in the y-position
     */
    void moveCenter(double xCoor, double yCoor)
    {
        xCenterCoordinate += xCoor;
        yCenterCoordinate += yCoor;
    }
    
    /**
     * @brief Retrieves the dragging state of the rectangle object
     * @return Returns true if the rectangle object is dragging
     */
    bool getDraggingState()
    {
        return _isDragging;
    }
    
    /**
     * @brief Sets the dragging state of the rectangle object
     * @param state Set to true if the rectangle object needs to be dragged. Otherwise, set to false
     */
    void setDraggingState(bool state)
    {
        _isDragging = state;
    }
	
	/**
	 * @brief 	This is the draw function for hte rectangle object. Note that for a generic retangle objecy
	 * 			nothing is drawn.
	 */
	virtual void draw()
    {
        
    }
    
    bool operator==(const rectangleShape &a_node)
    {
        if(xCenterCoordinate == a_node.getCenterXCoordinate() && yCenterCoordinate == a_node.getCenterYCoordinate())
            return true;
        else
            return false;
    }
    
    bool operator!=(const rectangleShape &a_node)
    {
        if(!(xCenterCoordinate == a_node.getCenterXCoordinate() && yCenterCoordinate == a_node.getCenterYCoordinate()))
            return true;
        else
            return false;
    }
};



/**
 * @class node
 * @author Phillip
 * @date 18/06/17
 * @file geometryShapes.h
 * @brief   This is the object that is used for nodes. This handles any specific node
 *          items such as the nodal property and the draw method for the node
 */
class node : public rectangleShape
{
private:
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive &ar, const unsigned int version)
	{
		ar & boost::serialization::base_object<rectangleShape>(*this);
		ar & _nodalSettings;
		ar & _nodeNumber;
	}
    //! The nodal property for the node
    /*!
        This object contains all of the nodal settings that are relevant to the node.
        When the user wants to edit the properties of the node, the data structure of this
        variable is exposed to the user for editing
     */ 
    nodeSetting _nodalSettings;
	
	//! Number that represents the nodal ID
	/*!
		The nodal ID is used to correctly associate the lines/arcs
		to the correct node. THis number is obtained
		by determining how many nodes were created
	*/ 
	unsigned long _nodeNumber;
	
	//! Boolean used to describe if the node was visited. This is used in the mesh maker class.
	bool p_isVisited = false;
	
	int p_GModelTagNumber = 0;
public:

    //! The constructor for the class
	node(double xCenter, double yCenter) : rectangleShape(xCenter, yCenter)
    {

    }
    
    //! The constructor for the class
    node()
    {
        
    }
	
	/**
	 * @brief Sets the GModel tag number for the vertex. This function is primarly used in the 
	 * mesh module and uses the GModel tag number to quickly look up the GVertex that the 
	 * node belongs to.
	 * @param number The GModel tag number
	 */
	void setGModalTagNumber(int number)
	{
		p_GModelTagNumber = number;
	}
	
	/**
	 * @brief Retrieves the GModel for the vertex
	 * @return Returns the GModel. If the vertex has not been created in GMSH, this function will return 0
	 */
	int getGModalTagNumber()
	{
		return p_GModelTagNumber;
	}
    
	/**
	 * @brief This function is called when the program needs to draw the object on the 
     *          glCanvas. To make a node, the program draws a white point on top of a 
     *          block point. When the user selects the node, the black is turned to
     *          red.
	 */
	void draw()
    {
        glPointSize(6.0);
		
        glBegin(GL_POINTS);
        
			if(_isSelected)
				glColor3d(1.0, 0.0, 0.0);
			else
				glColor3d(0.0, 0.0, 0.0);
            
            glVertex2d(xCenterCoordinate, yCenterCoordinate);
        glEnd();
    
        glColor3d(1.0, 1.0, 1.0);
        glPointSize(4.25);
    
        glBegin(GL_POINTS);
            glVertex2d(xCenterCoordinate, yCenterCoordinate);
        glEnd();
        
        glColor3d(0.0, 0.0, 0.0);
    }
    
    /**
     * @brief Sets the nodal settings of the node
     * @param setting The settings that the node should become
     */
    void setNodeSettings(nodeSetting setting)
    {
        _nodalSettings = setting;
    }
	
    /**
     * @brief Retrieves the nodal settings belonging to the node
     * @return Returns an address to the nodal settings for the node
     */
    nodeSetting *getNodeSetting()
    {
        return &_nodalSettings;
    }
	
	/**
	 * @brief 	Function that is used to set the noda ID of the node.
	 * 			This ID is used to associate the node to the arc/line.
	 * @param id The ID number of the node.
	 */
	void setNodeID(unsigned long id)
	{
		_nodeNumber = id;
	}
	
	/**
	 * @brief Function that is used to retrieve the nodal ID of the node.
	 * @return Returns a number representing the nodal ID of the node.
	 */
	unsigned long getNodeID()
	{
		return _nodeNumber;
	}
};



/**
 * @class blockLabel
 * @author phillip
 * @date 24/06/17
 * @file geometryShapes.h
 * @brief Class that is used to handle the geometry shape of a block label.
 * 			This class stores the property of the block label and handles 
 * 			the drawing of the block label and the drawing of the text that
 * 			is associated with the block label
 */
class blockLabel : public rectangleShape
{
private:
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive &ar, const unsigned int version)
	{
		ar & boost::serialization::base_object<rectangleShape>(*this);
		ar & _property;
	}
    //! The block property that is associated with the block label
	/*!
		This property contains properties for the mesh size of a particular region
		and what material should be associated with the particular region.
	*/ 
    blockProperty _property;
	
	//! This property is used in the mesher to keep track all of the block labels are used
	bool p_isUsed = false;
	
public:

	/**
	 * @brief	This is the draw method for the block label. This will
	 * 			create it similiar to the node geometry class; however,
	 * 			the bottom point is colored blue as default. When selected,
	 * 			it will change colors to red.
	 */
    void draw()
    {
        glPointSize(6.0);
        
        if(_isSelected)
            glColor3d(1.0, 0.0, 0.0);
        else
            glColor3d(0.0, 0.0, 1.0);
    
        glBegin(GL_POINTS);
            glVertex2d(xCenterCoordinate, yCenterCoordinate);
        glEnd();
    
        glColor3d(1.0, 1.0, 1.0);
        glPointSize(4.25);
    
        glBegin(GL_POINTS);
            glVertex2d(xCenterCoordinate, yCenterCoordinate);
        glEnd();
    }
	
	/**
	 * @brief Sets the state of the is used variable. Setting the variable will indicate if the
	 * 		label has been used by the mesher
	 * @param state Set to true to indicate the label has been assigned to a face. otherwise, set to false
	 */
	void setUsedState(bool state)
	{
		p_isUsed = state;
	}
	
	/**
	 * @brief Returns the used state
	 * @return If the block label is assigned to a face, will return true. Otherwise, false
	 */
	bool getUsedState()
	{
		return p_isUsed;
	}
    
	/**
	 * @brief 	Draws the text for the block label onto the screen. The text that is drawn is the material
	 * 			associated with the block label
	 * @param textRender 	A pointer to the OGLFT object that needs to be used
	 * 						for drawing the text
	 * @param factor		This is a constant that determines the distance as to
	 * 						where the text is drawn on the screen. A factor to how much 
	 * 						of an offset the text needs to be drawn at from the center 
	 * 						point of the block label.
	 */
    void drawBlockName(OGLFT::Grayscale *textRender, double factor)
    {
        double offset = 0.02 * factor;
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        textRender->draw(xCenterCoordinate + offset, yCenterCoordinate + offset, _property.getMaterialName().c_str());
    }
    
	/**
	 * @brief Draws the circuit name that is associated with the block label onto the screen
	 * @param textRender A pointer to hte OGLFT object that is to be used for drawing the text
	 * @param factor	This is a constant that detemines how far of an offset that the 
	 * 					text should be drawn from the center of the block label
	 */
    void drawCircuitName(OGLFT::Grayscale *textRender, double factor)
    {
        double offset = 0.02 * factor;
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        if(_property.getCircuitName() != "None")
            textRender->draw(xCenterCoordinate + offset, yCenterCoordinate - offset, _property.getCircuitName().c_str());
    }
	
	/**
	 * @brief Retrieves the block property that is associated with the block label
	 * @return A pointer pointing to the block property for the block label
	 */
    blockProperty *getProperty()
    {
        return &_property;
    }
    
	/**
	 * @brief Sets the property that is to be associated with the block label
	 * @param property The property that is to be associated with the block label
	 */
    void setPorperty(blockProperty property)
    {
        _property = property;
    }
};


/**
 * @class simplifiedEdge
 * @author Phillip
 * @date 04/04/18
 * @file geometryShapes.h
 * @brief This class is a more simple edge object. This is prirmaryly used in the mesher class. This edge
 * 			class is used to provide a simple implementation for an edge t make computing less costly.
			The class only contains the start and end nodes and the midpoint of the edge. THere are no 
			nodes to link the edge.
 */
class simplifiedEdge
{
private:
	wxRealPoint p_firstPoint = wxRealPoint(0, 0);
	
	wxRealPoint p_secondPoint = wxRealPoint(0, 0);
	
	wxRealPoint p_midPoint = wxRealPoint(0, 0);
	
	unsigned long p_arcID = 0;
	
	bool p_isSwapped = false;
	
	bool p_willDelete = false;
	
public:

	simplifiedEdge(wxRealPoint firstPoint, wxRealPoint secondPoint, wxRealPoint midPoint, unsigned long arcID = 0)
	{
		p_firstPoint = firstPoint;
		p_secondPoint = secondPoint;
		p_midPoint = midPoint;
		p_arcID = arcID;
	}
	
	simplifiedEdge()
	{
		
	}
	
	void swap()
	{
		wxRealPoint temp = p_firstPoint;
		p_firstPoint = p_secondPoint;
		p_secondPoint = temp;
		p_isSwapped = true;
	}
	
	void setStartPoint(wxRealPoint firstPoint)
	{
		p_firstPoint = firstPoint;
	}
	
	wxRealPoint getStartPoint()
	{
		return p_firstPoint;
	}
	
	void setEndPoint(wxRealPoint secondPoint)
	{
		p_secondPoint = secondPoint;
	}
	
	wxRealPoint getEndPoint()
	{
		return p_secondPoint;
	}
	
	void setMidPoint(wxRealPoint midPoint)
	{
		p_midPoint = midPoint;
	}
	
	wxRealPoint getMidPoint()
	{
		return p_midPoint;
	}
	
	/**
	 * @brief 	Tests if a point is to the Left/On/Right of the line. The orientation will be from the 
	 * 			first node to the second node
	 * @param point The point to test if it is Left/On/Right of the line
	 * @return 	Will return > 0 if point is to the left of the line. Returns == 0 if point lies on the line and
	 * 			returns < 0 if point is to the right of the line.
	 */
	double isLeft(wxRealPoint point)
	{
		return ((p_secondPoint.x - p_firstPoint.x) * (point.y - p_firstPoint.y)
					-(point.x - p_firstPoint.x) * (p_secondPoint.y - p_firstPoint.y));
	}
	
	unsigned long getArcID()
	{
		return p_arcID;
	}
	
	bool getSwappedState()
	{
		return p_isSwapped;
	}
	
	void setDeleteStatus()
	{
		p_willDelete = true;
	}
	
	bool getDeleteState() const
	{
		return p_willDelete;
	}
};

/**
 * @class edgeLineShape
 * @author Phillip
 * @date 18/06/17
 * @file geometryShapes.h
 * @brief   This class handles the lines that the user creates. 
 *          Each line is composed of a segment property and 
 *          two nodes. For quick access, the nodes are pointers to
 *          the nodes that connect the lines together.
 */
class edgeLineShape : public geometry2D
{
private:
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive &ar, const unsigned int version)
	{
		ar & boost::serialization::base_object<geometry2D>(*this);
		ar & _property;
		ar & p_firstNodeNumber;
		ar & p_secondNodeNumber;
		ar & p_distance;
		ar & p_xMid;
		ar & p_yMid;
	}
protected:
	//! The node number for the first node
	/*!
		For saving, this is useful because we are node able to save the 
		actual pointer. We would have to save the object that it points to
		instead. But, if there are mulple lines emitting from one node
		then the node will be save multple times. This is not 
		very efficient. Instead, we will track the node number for each
		node that connects the line. This way, when we load the data from 
		file, we have a way to quickly rebuild the node pointers for each line
	*/ 
	unsigned long p_firstNodeNumber = 0;
	
	//! The node number for the second node
	/*!
		For saving, this is useful because we are node able to save the 
		actual pointer. We would have to save the object that it points to
		instead. But, if there are mulple lines emitting from one node
		then the node will be save multple times. This is not 
		very efficient. Instead, we will track the node number for each
		node that connects the line. his way, when we load the data from 
		file, we have a way to quickly rebuild the node pointers for each line
	*/ 
	unsigned long p_secondNodeNumber = 0;
	
    //! The property of the line segment
    /*!
        This property contains details on the group number and any
        boundary conditions that are associated with the line
    */ 
    segmentProperty _property;
    
	//! Pointer for the first node
	/*!
		This points to the first node of the 
		edge line shape (basically a segment)
	*/ 
    node *_firstNode = nullptr;
    
	//! Pointer for the first node
	/*!
		This points to the first node of the 
		edge line shape (basically a segment)
	*/ 
    node *_secondNode = nullptr;
	
	//! Boolean used to determine if the lines segment is an arc
	bool p_isArc = false;
	
	//! ID number of the arc. Will be zero for lines
	unsigned long p_arcID = 0;
	
	//! Boolean used to describe if the line segment was visited for contour finding
	bool p_isVisited = false;
	
	//! The distance that the edge tranverses
	double p_distance = 0;
	
	//! The radius of an arc from the center point
    double _radius = 0.0;
	
	//! The x coordinate point for the mid point of the edge
	double p_xMid = 0;
	
	//! The y coordinate position of the mid point of the edge
	double p_yMid = 0;
	
	//! Boolean used to indicate if the first and second nodes are swapped
	bool p_isSwapped = false;
	
	/**
	 * @brief Performs the dot product on two points. This function is mainly used 
	 * in the winding number algorithm to detect if a point lies within a specific geometry. This function is 
	 * used in the case that the edge is an arc.
	 * @param firstPoint The first point
	 * @param secondPoint The second point
	 * @return Returns a number representing the dot product of the two points
	 */
	double dotProduct(wxRealPoint firstPoint, wxRealPoint secondPoint)
	{
		return (firstPoint.x * secondPoint.x) + (firstPoint.y * secondPoint.y);
	}
	
	/**
	 * @brief Performs the cross product on two points. This function is mainly used 
	 * in the winding number algorithm to detect if a point lies within a specific geometry. This function is 
	 * used in the case that the edge is an arc.
	 * @param firstPoint The first point
	 * @param secondPoint The second point
	 * @return Returns a number representing the cross product of the two points
	 */
	double crossProduct(wxRealPoint firstPoint, wxRealPoint secondPoint)
	{
		return (firstPoint.x * secondPoint.y) - (secondPoint.x * firstPoint.y);
	}
	
	/**
	 * @brief This fucntion will check if the two parameters are the same sign. This function is mainly used 
	 * in the winding number algorithm to detect if a point lies within a specific geometry. This function is 
	 * used in the case that the edge is an arc.
	 * @param firstValue The firs value
	 * @param secondValue The second value
	 * @return Returns true if the first and second values are the same sign. Otherwise, returns false.
	 */
	bool isSameSign(double firstValue, double secondValue)
	{
		return (signbit(firstValue) == signbit(secondValue));
	}
    
public:
	//! Constructor for the generic class
	edgeLineShape()
    {
        
    }
	
	/**
	 * @brief Calculates the distance that the two points of the edge span. THis must be called after the line is created.
	 * The distance is primarly used in the mesh module.
	 */
	virtual void calculateDistance()
	{
		if(_firstNode && _secondNode)
		{
			p_distance = sqrt(pow(_firstNode->getCenterXCoordinate() - _secondNode->getCenterXCoordinate(), 2) + pow(_firstNode->getCenterYCoordinate() - _secondNode->getCenterYCoordinate(), 2));
			xCenterCoordinate = (_firstNode->getCenterXCoordinate() + _secondNode->getCenterXCoordinate()) / 2.0;
			yCenterCoordinate = (_firstNode->getCenterYCoordinate() + _secondNode->getCenterYCoordinate()) / 2.0;
			p_xMid = xCenterCoordinate;
			p_yMid = yCenterCoordinate;
		}
	}
	
	/**
	 * @brief Returns the distance that spans across the two points of the edge. For arcs, this would be 
	 * the arc length. This is mainly used in the mesh module.
	 * @return Returns a number representing the distance between the two points. For arcs, this would be the arc length.
	 */
	double getDistance()
	{
		return p_distance;
	}
	
	/**
	 * @brief Function that will return whether or not the segment is an arc 
	 * @return Returns true if the line segment is an arc. Otherwise returns false
	 */
	bool isArc()
	{
		return p_isArc;
	}
	
	/**
	 * @brief Gets the arc ID associated with the line segment. This only applies to arcs
	 * @return Returns a number that indicates the arc ID. If the edge is a line, then this will return 0
	 */
	unsigned long getArcID()
	{
		return p_arcID;
	}
	
	/**
	 * @brief Gets the state of the visited variable.
	 * @return Returns true if the contour algorthim visisted the line segment or if the line
	 * segment was used in a closed contour. Otherwise, returns false
	 */
	bool getVisitedStatus()
	{
		return p_isVisited;
	}
	
	/**
	 * @brief Set the state of the visited variable.
	 * @param state Set to true to indicate that the edge has been visited.
	 */
	void setVisitedStatus(bool state)
	{
		p_isVisited = state;
	}
    
	/**
	 * @brief Sets the first node of the line segment
	 * @param a_Node The first node of the line segment
	 */
    void setFirstNode(node &a_Node)
    {
        _firstNode = &a_Node;
		p_firstNodeNumber = _firstNode->getNodeID();
    }
    
	/**
	 * @brief Gets the first node of the line segment
	 * @return Retruns a pointer pointing to the first node of the line segment
	 */
    node *getFirstNode()
    {
        return _firstNode;
    }
    
	/**
	 * @brief Sets the second node of the line segment
	 * @param a_node The second node of the line segment
	 */
    void setSecondNode(node &a_node)
    {
        _secondNode = &a_node;
		p_secondNodeNumber = _secondNode->getNodeID();
    }
    
	/**
	 * @brief Retrieves the second node of the line segment
	 * @return Returns a pointer pointing to the second node of the line segment
	 */
    node *getSecondNode()
    {
        return _secondNode;
    }
    
	/**
	 * @brief This is the draw method for the line segment. This differs from the arc segment class since this 
	 * 			is a straight line. The defualt color is black. If the line is selected, then the line
	 * 			will change colors to red
	 */
    void draw()
    {			
        if(_property.getHiddenState())
        {
            glEnable(GL_LINE_STIPPLE);
            glLineStipple(1, 0b0001100011000110);
        }
  
        glLineWidth(2.0);
        glBegin(GL_LINES);
            if(_isSelected)
                glColor3f(1.0f, 0.0f, 0.0f);
            else
                glColor3f(0.0f, 0.0f, 0.0f);
            glVertex2d(_firstNode->getCenterXCoordinate(), _firstNode->getCenterYCoordinate());
            glVertex2d(_secondNode->getCenterXCoordinate(), _secondNode->getCenterYCoordinate());
        glEnd();
        glLineWidth(0.5);
        glDisable(GL_LINE_STIPPLE);
    }
    
	/**
	 * @brief Retrieves the segment properties of the line segment
	 * @return Returns the segment property object that is associated with the line segment
	 */
    segmentProperty *getSegmentProperty()
    {
        return &_property;
    } 
	
	/**
	 * @brief Sets the segment properties of the line segment
	 * @param property 	The segment property that the line segment will
	 * 					be associated with
	 */
    void setSegmentProperty(segmentProperty property)
    {
        _property = property;
    }
	
	/**
	 * @brief Retrieves the node ID that belongs to the first node of the line segment
	 * @return Returns a number representing the node ID of the first node
	 */
	unsigned long getFirstNodeID()
	{
		return p_firstNodeNumber;
	}
	
	/**
	 * @brief Retrieves the node ID that belongs to the second node of the line segment
	 * @return Returns a number representing the node ID of the second node
	 */
	unsigned long getSecondNodeID()
	{
		return p_secondNodeNumber;
	}
	
	bool operator==(edgeLineShape edge)
	{
		if(!this->p_isArc && !edge.isArc())
		{
			if(((*this->getFirstNode()) == (*edge.getFirstNode())) && ((*this->getSecondNode()) == (*edge.getSecondNode())))
				return true;
			else
				return false;
		}
		else if((this->p_isArc && edge.isArc()) && (this->getArcID() == edge.getArcID()))
			return true;
		else
			return false;
	}
	
	/**
	 * @brief 	Tests if a point is to the Left/On/Right of the line. The orientation will be from the 
	 * 			first node to the second node
	 * @param point The point to test if it is Left/On/Right of the line
	 * @return 	Will return > 0 if point is to the left of the line. Returns == 0 if point lies on the line and
	 * 			returns < 0 if point is to the right of the line.
	 */
	double isLeft(wxRealPoint point)
	{
		if(!p_isArc)
		{
			return ((_secondNode->getCenterXCoordinate() - _firstNode->getCenterXCoordinate()) * (point.y - _firstNode->getCenterYCoordinate()) 
						- (point.x - _firstNode->getCenterXCoordinate()) * (_secondNode->getCenterYCoordinate() - _firstNode->getCenterYCoordinate()));	
		}
		else
		{
			double result = 0;
			
			if(isSameSign(crossProduct(point - _firstNode->getCenter(), _secondNode->getCenter() - _firstNode->getCenter()), 
							crossProduct(this->getCenter() - _firstNode->getCenter(), _secondNode->getCenter() - _firstNode->getCenter())))
			{
				result = dotProduct(point - _firstNode->getCenter(), _secondNode->getCenter() - _firstNode->getCenter()) / 
							dotProduct(_secondNode->getCenter() - _firstNode->getCenter(), _secondNode->getCenter() - _firstNode->getCenter());
				
				if(result >= 0 && result <= 1)
					return 1.0;
				else
					return -1.0;
			}
			else
			{
				result = dotProduct(point - this->getCenter(), point - this->getCenter());
				
				if(result <= pow(_radius, 2))
					return 1.0;
				else
					return -1.0;
			}
			
			
		}
	}
	
	/**
	 * @brief Gets the midpoint of the edge. For lines, this is the exact midpoint.
	 * For asrcs, this returns the midpoint of the arc line
	 * @return Returns a wxRealPoint representing the midpoint of the edge
	 */
	wxRealPoint getMidPoint()
	{
		return wxRealPoint(p_xMid, p_yMid);
	}
	
	/**
	 * @brief 	This function is called in order to swap the ending and starting node.
	 * 			This is mainly used in the algorithm for PIP in order to ensure that all of 
	 * 			the edges are oriented the same way
	 */
	void swap()
	{
		node *temp = _firstNode;
		unsigned long tempNumber = p_firstNodeNumber;
		
		_firstNode = _secondNode;
		_secondNode = temp;
		
		p_firstNodeNumber = p_secondNodeNumber;
		p_secondNodeNumber = tempNumber;
		
		p_isSwapped = !p_isSwapped;
	}
	
	bool getSwappedState()
	{
		return p_isSwapped;
	}
	
	std::vector<simplifiedEdge> getBoundingEdges()
	{
		std::vector<simplifiedEdge> returnVector;
		
		returnVector.push_back(simplifiedEdge(_firstNode->getCenter(), _secondNode->getCenter(), this->getCenter()));
		
		return returnVector;
	}
};



/*! This class inherits from the edgeLineShape class bescause an arc is like a line but with an angle */
class arcShape : public edgeLineShape
{
private:
	friend class boost::serialization::access;
	
	template<class Archive>
	void serialize(Archive &ar, const unsigned int version)
	{
		ar & boost::serialization::base_object<edgeLineShape>(*this);
		ar & _numSegments;
		ar & _arcAngle;
		ar & _radius;
		ar & _isCounterClockWise;
		ar & p_isArc;
		ar & p_arcID;
	}
	
	//! The number of segments that comprises the arc
	unsigned int _numSegments = 3;
	
    //! This data is the angle of the arc used in calculations. This should be in degrees
	double _arcAngle = 30;
	
    //! Boolean used to determine if the arc is clockwise or counterclock-wise
    bool _isCounterClockWise = true;
public:
	/**
	 * @brief The constructor for the clase
	 */
	arcShape()
    {
        p_isArc = true;
    }
	
	/**
	 * @brief Calculates the arc length of the arc.
	 */
	void calculateDistance()
	{
		p_distance = _radius * _arcAngle * (PI / 180.0);
	}
	
	/**
	 * @brief Sets the angle fo the arc. The angle stored is always positive. A boolean specifies if
	 * the angle is + or -.
	 * @param angleOfArc Sets the angle of the arc in degrees
	 */
	void setArcAngle(double angleOfArc)
    {
        _arcAngle = abs(angleOfArc);
        if(angleOfArc > 0)
            _isCounterClockWise = true;
        else
            _isCounterClockWise = false;
    }
	
	/**
	 * @brief Retrieves the arc angle
	 * @return Returns a number representing the arc angle. + is CCW - is CW
	 */
	double getArcAngle()
    {
        if(_isCounterClockWise)
            return _arcAngle;
        else
            return -_arcAngle;
    }

	/**
	 * @brief Specifies the number of segments that will be used to draw the arc
	 * @param segments The number of segments to use to draw the arc
	 */
	void setNumSegments(unsigned int segments)
    {
        _numSegments = segments;
    }
	
	/**
	 * @brief Retrieves the number of segments to draw the arc
	 * @return Returns a number to represent the number of segments used to draw the arc on the screen
	 */
	unsigned int getnumSegments()
    {
        return _numSegments;
    }
    
    /**
     * @brief The function that is called in order to draw the arc on the screen
	 * This function will call the necessary OpenGL functions in order to draw the 
	 * arc on the OpenGL canvas
     */
    void draw()
    {
        if(_isSelected)
            glColor3d(1.0, 0.0, 0.0);
        else
            glColor3d(0.0, 0.0, 0.0);
			
		if(p_distance == 0)
			calculateDistance();
        
        if(_property.getHiddenState())
        {
            glEnable(GL_LINE_STIPPLE);
            glLineStipple(1, 0b0001100011000110);
        }
        
        double angle = -(_arcAngle / (double)_numSegments);
        
        glBegin(GL_LINE_STRIP);
            glVertex2d(_firstNode->getCenterXCoordinate(), _firstNode->getCenterYCoordinate());
            for(int i = 1; i <= (_numSegments - 1); i++)
            {
                double xPoint = (_firstNode->getCenterXCoordinate() - xCenterCoordinate) * cos(i * angle * PI / 180.0) + (_firstNode->getCenterYCoordinate() - yCenterCoordinate) * sin(i * angle * PI / 180.0) + xCenterCoordinate;
                double yPoint = -(_firstNode->getCenterXCoordinate() - xCenterCoordinate) * sin(i * angle * PI / 180.0) + (_firstNode->getCenterYCoordinate() - yCenterCoordinate) * cos(i * angle * PI / 180.0) + yCenterCoordinate;
                glVertex2d(xPoint, yPoint);
            }
            glVertex2d(_secondNode->getCenterXCoordinate(), _secondNode->getCenterYCoordinate());
        glEnd();
  
        glDisable(GL_LINE_STIPPLE); 
    }	

    /*! \brief  
		See this forum post: http://mymathforum.com/algebra/21368-find-equation-circle-given-two-points-arc-angle.html
      
		This function will be calculating the radius and center point of the arc
	 			The idea is as follows:
				By knowing the 2 endpoints and the arc angle, we are able to caluclate the radius and the center point
				For the radius, this is the law of cosines: c^2 = 2 * R^2 * (1 - cos(theta) )
                where c is the length of the sector through the beginning and starting endpoints and theta is the arc angle
                Then, we can calculate the radius by solving for R. Using the midpoint of line AB and the slope perpendicular to 
				line AB, we can use the slope-ponit form to find the equation of the line and then use Pythagorean Thereom's
				in order to find the arc's exact center
	 */
    void calculate()
    {
        /* The start node is considered the first node of the arc
         * the end node is considered the second node of the arc.
         * This is detictated by the order of the selection
         */ 
        double xMid = 0;
        double yMid = 0;
        double a = 0; // This variable is the distance from the midpoint of the two end points to the center of the arc
        double midSlope = 0;
        double slope = 0;
        double distanceSquared = 0;
        
        // Use this site for reference: http://mymathforum.com/algebra/21368-find-equation-circle-given-two-points-arc-angle.html
        distanceSquared = pow(_firstNode->getCenterXCoordinate() - _secondNode->getCenterXCoordinate(), 2) + pow(_firstNode->getCenterYCoordinate() - _secondNode->getCenterYCoordinate(), 2);
        
        _radius = sqrt(distanceSquared / (2.0 * (1.0 - cos(_arcAngle * PI / 180.0))));// Fun fact, the cosine function evaluates in radians
        
        xMid = (_firstNode->getCenterXCoordinate() + _secondNode->getCenterXCoordinate()) / 2.0;
        
        yMid = (_firstNode->getCenterYCoordinate() + _secondNode->getCenterYCoordinate()) / 2.0;
        
        slope = (_firstNode->getCenterYCoordinate() - _secondNode->getCenterYCoordinate()) / (_firstNode->getCenterXCoordinate() - _secondNode->getCenterXCoordinate());
        
        a = sqrt(pow(_radius, 2) - (distanceSquared / 4.0));
        
        if(std::isnan(a))// This will account for the case if the mid point is directly ontop of the center point
            a = 0;
        
        // We need two cases here. One for if the line between the first and second node has a slope of 0 and the other case being if the line is vertical
        if(slope >= 0 && slope <= 1e-9)
        {
            if((!(_firstNode->getCenterXCoordinate() > _secondNode->getCenterXCoordinate()) != (!_isCounterClockWise)))
            {
                // This will calculate the center that is below the arc.
                // If the start node is lower then the end node, the logic is reversed. This portion will create
                // the center above the arc.
                xCenterCoordinate = xMid;
                yCenterCoordinate = yMid + a;
            }
            else
            {
                // This will calculate the center above the arc
                xCenterCoordinate = xMid;
                yCenterCoordinate = yMid - a;
            }
        }
        else if(slope == INFINITY)
        {
            if((!(_firstNode->getCenterXCoordinate() > _secondNode->getCenterXCoordinate()) != (!_isCounterClockWise)))
            {
                // This will calculate the center that is below the arc.
                // If the start node is lower then the end node, the logic is reversed. This portion will create
                // the center above the arc.
                xCenterCoordinate = xMid + a;
                yCenterCoordinate = yMid;
            }
            else
            {
                // This will calculate the center above the arc
                xCenterCoordinate = xMid - a;
                yCenterCoordinate = yMid;
            }
        }
        else if(slope == -INFINITY)
        {
            if((!(_firstNode->getCenterYCoordinate() > _secondNode->getCenterYCoordinate()) != (!_isCounterClockWise)))
            {
                // This will calculate the center that is below the arc.
                // If the start node is lower then the end node, the logic is reversed. This portion will create
                // the center above the arc.
                xCenterCoordinate = xMid - a;
                yCenterCoordinate = yMid;
            }
            else
            {
                // This will calculate the center above the arc
                xCenterCoordinate = xMid + a;
                yCenterCoordinate = yMid;
            }
        }
		else
		{
			midSlope = -1.0 / slope;
			
			if(slope > 0)
			{
				if((!(_firstNode->getCenterXCoordinate() > _secondNode->getCenterXCoordinate()) != (!_isCounterClockWise)))
				{
					// This will calculate the center that is above the arc.
					// If the start node is lower then the end node, the logic is reversed. This portion will create
					// the center above the arc.

					xCenterCoordinate = xMid - a / sqrt(pow(midSlope, 2) + 1);
					yCenterCoordinate = yMid - (midSlope * a) / sqrt(pow(midSlope, 2) + 1);
				}
				else
				{
					// This will calculate the center below the arc
					
					xCenterCoordinate = xMid + a / sqrt(pow(midSlope, 2) + 1);
					yCenterCoordinate = yMid + (midSlope * a) / sqrt(pow(midSlope, 2) + 1);

				}
			}
			else if(slope < 0)
			{
				if(!(!(_firstNode->getCenterXCoordinate() > _secondNode->getCenterXCoordinate()) != (!_isCounterClockWise)))
				{
					// This will calculate the center that is above the arc.
					// If the start node is lower then the end node, the logic is reversed. This portion will create
					// the center above the arc.
					
					xCenterCoordinate = xMid - a / sqrt(pow(midSlope, 2) + 1);
					yCenterCoordinate = yMid - (midSlope * a) / sqrt(pow(midSlope, 2) + 1);
				}
				else
				{
					// This will calculate the center below the arc
					
					xCenterCoordinate = xMid + a / sqrt(pow(midSlope, 2) + 1);
					yCenterCoordinate = yMid + (midSlope * a) / sqrt(pow(midSlope, 2) + 1);
				}
			}
			
		}
		
		calculateDistance();
		
		double vx = xMid - xCenterCoordinate;
		double vy = yMid - yCenterCoordinate;
		
		double lev = sqrt(pow(vx, 2) + pow(vy, 2));
		
		if(lev == 0)
		{
			if(abs(slope) >= 0 && abs(slope) <= 1e-2)
			{
				if(_firstNode->getCenterXCoordinate() > _secondNode->getCenterXCoordinate())
				{
					p_xMid = xCenterCoordinate;
					p_yMid = yCenterCoordinate + _radius;
				}
				else
				{
					p_xMid = xCenterCoordinate;
					p_yMid = yCenterCoordinate - _radius;
				}
			}
			else if(slope == INFINITY || slope == -INFINITY)
			{
				if(_firstNode->getCenterYCoordinate() > _secondNode->getCenterYCoordinate())
				{
					p_xMid = xCenterCoordinate - _radius;
					p_yMid = yCenterCoordinate;
				}
				else
				{
					p_xMid = xCenterCoordinate + _radius;
					p_yMid = yCenterCoordinate;
				}
			}
		}
		else
		{
			p_xMid = xCenterCoordinate + _radius * vx / lev;
			p_yMid = yCenterCoordinate + _radius * vy / lev;
		}
		
        return;
    }
    
	/**
	 * @brief Retrieves the radius of the arc
	 * @return Returns a number reprenseting the radius of the arc
	 */
    double getRadius()
    {
        return _radius;
    }	
    
	/**
	 * @brief Retrieves the arc length
	 * @return Returns the arc length of the arc
	 */
    double getArcLength()
    {
        return p_distance;
    }
    
	bool operator==(arcShape arc)
	{
		if(((*this->getFirstNode()) == (*arc.getFirstNode())) && ((*this->getSecondNode()) == (*arc.getSecondNode())) && (this->getCenterXCoordinate() == arc.getCenterXCoordinate()) && (this->getCenterYCoordinate() == arc.getCenterYCoordinate()))
			return true;
		else
			return false;
	}
	
	bool operator==(edgeLineShape edgeLine)
	{
		if(this->getArcID() == edgeLine.getArcID())
			return true;
		else
			return false;
	}
	
	/**
	 * @brief Sets the arc ID that belongs to the arc. This is useful
	 * when comparing two edges to see if they are equal
	 * @param id The ID that will be assigned to the arc
	 */
	void setArcID(unsigned long id)
	{
		p_arcID = id;
	}
	
	std::vector<simplifiedEdge> getBoundingEdges()
	{
		std::vector<simplifiedEdge> returnVector;
		
		wxRealPoint midPoint;
		wxRealPoint upperMid = this->getMidPoint();
		wxRealPoint point1;
		wxRealPoint point2;
		
		double circleRadius = 0;
		
		double theta = acos(1 - ((pow(this->getCenter().x + _radius - this->getMidPoint().x, 2) + pow(this->getCenter().y - this->getMidPoint().y, 2)) / (2 * pow(_radius, 2))));
		
		if(this->getMidPoint().y < this->getCenter().y)
			theta = theta * -1;
			
		upperMid.x = this->getCenter().x + (_radius + 0.1) * cos(theta);
		
		upperMid.y = this->getCenter().y + (_radius + 0.1) * sin(theta);
		
		midPoint.x = (_firstNode->getCenter().x + _secondNode->getCenter().x) / 2.0;
		midPoint.y = (_firstNode->getCenter().y + _secondNode->getCenter().y) / 2.0;
		
		returnVector.push_back(simplifiedEdge(_firstNode->getCenter(), _secondNode->getCenter(), midPoint, p_arcID));
		
		circleRadius = sqrt(pow(upperMid.x - midPoint.x, 2) + pow(upperMid.y - midPoint.y, 2));
		
		point1.x = _firstNode->getCenter().x + circleRadius * cos(theta);
		point1.y = _firstNode->getCenter().y + circleRadius * sin(theta);
		
		point2.x = _secondNode->getCenter().x + circleRadius * cos(theta);
		point2.y = _secondNode->getCenter().y + circleRadius * sin(theta);
		
		midPoint.x = (_firstNode->getCenter().x + point1.x) / 2.0;
		midPoint.y = (_firstNode->getCenter().y + point1.y) / 2.0;
		
		returnVector.push_back(simplifiedEdge(_firstNode->getCenter(), point1, midPoint));
		
		returnVector.push_back(simplifiedEdge(point1, point2, upperMid));
		
		midPoint.x = (_secondNode->getCenter().x + point2.x) / 2.0;
		midPoint.y = (_secondNode->getCenter().y + point2.y) / 2.0;
		
		returnVector.push_back(simplifiedEdge(point2, _secondNode->getCenter(), midPoint));
		
		return returnVector;
	}
};



class arcPolygon
{
private:
	std::vector<simplifiedEdge> p_polygonEdges;
	
	bool p_isSorted = false;
	
	bool p_isCCW = false;
	
	arcShape p_arc;
	
	bool p_isSwapped = false;
	
public:

	arcPolygon(std::vector<simplifiedEdge> edgeList, arcShape arc)
	{
		p_polygonEdges = edgeList;
		p_arc = arc;
	}
	
	void setSwapped()
	{
		p_isSwapped = true;
	}
	
	bool getSwappedState()
	{
		return p_isSwapped;
	}
	
	bool isInside(wxRealPoint point)
	{
		double subtractionTerms = 0;
		double additionTerms = 0;
		bool reverseWindingResult = false;
		int windingNumber = 0;
		bool isFirstRun = true;
		
		for(auto lineIterator = p_polygonEdges.begin(); lineIterator != p_polygonEdges.end(); lineIterator++)
		{
			auto nextLineIterator = lineIterator + 1;
			
			if(nextLineIterator == p_polygonEdges.end())
				nextLineIterator = p_polygonEdges.begin();
			
			if(isFirstRun)
			{
				if(lineIterator->getEndPoint() != nextLineIterator->getStartPoint())
				{
					if(lineIterator->getStartPoint() == nextLineIterator->getStartPoint())
						lineIterator->swap();
					else if(lineIterator->getStartPoint() == nextLineIterator->getEndPoint())
					{
						lineIterator->swap();
						nextLineIterator->swap();
					}
					else if(lineIterator->getEndPoint() == nextLineIterator->getEndPoint())
						nextLineIterator->swap();
				}
				
				isFirstRun = false;
			}
			else
			{
				if(lineIterator->getEndPoint() == nextLineIterator->getEndPoint())
					nextLineIterator->swap();
			}
			 
			additionTerms += (lineIterator->getStartPoint().x) * (lineIterator->getEndPoint().y);
			subtractionTerms += (lineIterator->getEndPoint().x) * (lineIterator->getStartPoint().y);
		}
		
		if(subtractionTerms > additionTerms)
			reverseWindingResult = true;
			
			
		for(auto lineIterator = p_polygonEdges.begin(); lineIterator != p_polygonEdges.end(); lineIterator++)
		{
			double isLeftResult = lineIterator->isLeft(point);
			
			if(reverseWindingResult)
				isLeftResult *= -1;
			
			if(lineIterator->getStartPoint().y <= point.y)
			{
				if(lineIterator->getEndPoint().y > point.y)
				{
					if(isLeftResult > 0)
						windingNumber++;
					else if(isLeftResult < 0)
						windingNumber--;
				}
			}
			else if(lineIterator->getEndPoint().y <= point.y)
			{
				if(isLeftResult < 0)
					windingNumber--;
				else if(isLeftResult > 0)
					windingNumber++;
			}
		}
		
		if(windingNumber > 0)
			return true;
		else
			return false;
	}
	
	std::vector<simplifiedEdge> getEdges()
	{
		return p_polygonEdges;
	}
	
	arcShape getArc()
	{
		return p_arc;
	}
};


#endif