#ifndef GEOMETRY_SHAPES_H_
#define GEOMETRY_SHAPES_H_

#include <math.h>
#include <vector>

#include <freeglut.h>
#include <gl.h>
#include <glu.h>

#include <wx/wx.h>
#include <wx/glcanvas.h>

#include <common/GeometryProperties/BlockProperty.h>
#include <common/GeometryProperties/NodeSettings.h>
#include <common/GeometryProperties/SegmentProperties.h>

#include <common/Vector.h>

//#include <UI/openGLGeometry.h>

/*! \class geometry2D
	\brief This is the base class for all of the geometry classes
*/
class geometry2D
{
protected:
	
	//! This is a boolean that willl indicate if the user selects the geometric shape
	bool isSelected = false;
    
    //! This is used to indicate if the geometry that is selected is for a group
    bool isGroupSelectedState = false;
	
	//! Data type used to store the group number that the shape is associated with
	int groupNumber = 0;

	//! This data type stroes the center x  position in Cartesian Coordiantes
	/*! 
		For arcs, this is the center of the circle.
		For lines, this is the midpoint
		For nodes and blocklabels, this would be the center of the square.
	*/
	double xCenterCoordinate;
	
	//! This data type stores the center y position in Cartesians Coordiantes
	double yCenterCoordinate;
    
public:
	
	geometry2D()
    {
        
    }
	
	//! Function used to set the X coordiante for the center point of the shape
	void setCenterXCoordinate(double xCenter)
    {
        xCenterCoordinate = xCenter;
    }
	
	//! Function used to set the Y coordiante for the center point of the shape
	void setCenterYCoordiante(double yCenter)
    {
        yCenterCoordinate = yCenter;
    }
	
	//! Function used to get the X Coordinate of the center point point of the shape
	double getCenterXCoordinate() const
    {
        return xCenterCoordinate;
    }
	
	//! Function used to get the Y Coordinate of the center point point of the shape
	double getCenterYCoordinate() const
    {
        return yCenterCoordinate;
    }

	
	//! Function used to set the group that the shape is assocated with
	void setGroup(int group)
    {
        groupNumber = group;
    }
	
	//! Function used to retrieive the group number that the shape is associated with
	int getGroup()
    {
        return groupNumber;
    }
	
	//! the function will be called when the user selects the geomtry shape
	void setSelectState(bool state)
    {
        isSelected = state;
    }
	
	//! This function will return the selected status
	bool getIsSelectedState()
    {
        return isSelected;
    }
    
    void setGroupSelectedState(bool state)
    {
        isGroupSelectedState = state;
    }
    
    bool getGroupSelectedState()
    {
        return isGroupSelectedState;
    }
    

};


class rectangleShape : public geometry2D
{
public:
    rectangleShape() : geometry2D()
    {
        
    }
    
	rectangleShape(double xCenterPoint, double yCenterPoint)
    {
        xCenterCoordinate = xCenterPoint;
        yCenterCoordinate = yCenterPoint;
        isSelected = false;
    }
	
	//! This function will get the distance between two points. The first being itself and the second, the input. The values that are taken in are the x and y coordinate of the second point
	double getDistance(double xp, double yp)
    {
        return sqrt(pow((xCenterCoordinate - xp), 2) + pow((yCenterCoordinate - yp), 2));
    }
	
	//! This is the function that is called in order to draw the rectangle. One thing that is 
	virtual void draw()
    {
        
    }
};



class node : public rectangleShape
{
private:
	//! The nodes are stored in array. For quickier accesssing, this will store the index which is associated with the node
	int _nodeIndex;
    
    nodeSetting _nodalSettings;
public:
	node(double xCenter, double yCenter) : rectangleShape(xCenter, yCenter)
    {

    }
    
    node()
    {
        
    }
    
    void setCenter(double xCoor, double yCoor)
    {
        xCenterCoordinate = xCoor;
        yCenterCoordinate = yCoor;
    }
	
	//! This function will draw the shape
	virtual void draw()
    {
        if(isSelected)
            glColor3d(1.0, 0.0, 0.0);
        else
            glColor3d(0.0, 0.0, 0.0);
    
        glPointSize(6.0);
    
        glBegin(GL_POINTS);
            glVertex2d(xCenterCoordinate, yCenterCoordinate);
        glEnd();
    
        glColor3d(1.0, 1.0, 1.0);
        glPointSize(4.25);
    
        glBegin(GL_POINTS);
            glVertex2d(xCenterCoordinate, yCenterCoordinate);
        glEnd();
    }
	
	void setNodeIndex(int index) 
    {
        _nodeIndex = index;
    }
	
	int getNodeIndex() const
    {
        return _nodeIndex;
    }
    
    void setNodeSettings(nodeSetting setting)
    {
        _nodalSettings = setting;
    }
	
    /*! /brief
    *   This function returns the address of the variable that contains the setting for the node.
    *   These settings are specificially settings such as nodal properties, material,etc.
    */ 
    nodeSetting *getNodeSetting()
    {
        return &_nodalSettings;
    }
    
    bool operator==(const node &a_node)
    {
        if(xCenterCoordinate == a_node.getCenterXCoordinate() && yCenterCoordinate == a_node.getCenterYCoordinate())
            return true;
        else
            return false;
    }
};



class edgeLineShape : public geometry2D
{
private:
    segmentProperty _property;
    
protected:
	/*! \brief  A line is composed of 2 nodes.
	 *			The nodes are stored in a vector array (which is a dynamically allocated array)
	 *			How do we tell the object which node the line connects to?
	 *			We differenatiate by using the index of the array.
	 *			This variables stores the index of first node which connects the line.
	 */	
	int _nodeIndex1;
	
	/*! \brief  A line is composed of 2 nodes.
	 *			The nodes are stored in a vector array (which is a dynamically allocated array)
	 *			How do we tell the object which node the line connects to?
	 *			We differenatiate by using the index of the array.
	 *			This variables stores the index of second node which connects the line.
	 */
	int _nodeIndex2;
	
	//! Status to indicate if the line is hidden in the post-Processor
	bool _isHidden;
	
	//! The length of the line?
	double _maxSideLength;
    
    node *_firstNode;
    
    node *_secondNode;
    
public:
	edgeLineShape()
    {
        
    }
    
    void setFirstNode(node &a_Node)
    {
        _firstNode = &a_Node;
    }
    
    node getFirstNode()
    {
        return *_firstNode;
    }
    
    void setSecondNode(node &a_node)
    {
        _secondNode = &a_node;
    }
    
    node getSecondNode()
    {
        return *_secondNode;
    }
	
	void setFirstNodeIndex(int index)
    {
        _nodeIndex1 = index;
    }
    
	void setSecondNodeIndex(int index)
    {
        _nodeIndex2 = index;
    }
	
	int getFirstNodeIndex() const
    {
        return _nodeIndex1;
    }
    
	int getSecondNodeIndex() const
    {
        return _nodeIndex2;
    }
	
	void setHiddenStatus(bool status)
    {
        _isHidden = status;
    }
    
	bool getHiddenStatus()
    {
        return _isHidden;
    }
    
    virtual void draw(double node1X, double node1Y, double node2X, double node2Y)
    {
        glLineWidth(2.0);
        glBegin(GL_LINES);
            if(isSelected)
                glColor3f(1.0f, 0.0f, 0.0f);
            else
                glColor3f(0.0f, 0.0f, 0.0f);
            glVertex2d(node1X, node1Y);
            glVertex2d(node2X, node2Y);
        glEnd();
        glLineWidth(0.5);
    }
    
    segmentProperty *getSegmentProperty()
    {
        return &_property;
    } 
	
    void setSegmentProperty(segmentProperty property)
    {
        _property = property;
    }
};



class blockLabel : public rectangleShape
{
private:
	double maxArea;
	
	std::string blockType;
	
	bool isExternal;
	
	bool isDefault;
public:
    void draw()
    {
        if(isSelected)
            glColor3d(1.0, 0.0, 0.0);
        else
            glColor3d(0.0, 0.0, 1.0);
    
        glPointSize(6.0);
    
        glBegin(GL_POINTS);
            glVertex2d(xCenterCoordinate, yCenterCoordinate);
        glEnd();
    
        glColor3d(1.0, 1.0, 1.0);
        glPointSize(4.25);
    
        glBegin(GL_POINTS);
            glVertex2d(xCenterCoordinate, yCenterCoordinate);
        glEnd();
    }
	

};



/*! This class inherits from the edgeLineShape class bescause an arc is like a line but with an angle */
class arcShape : public edgeLineShape
{
private:
	bool _isHidden;
	
	unsigned int _numSegments = 3;
	
    //! This data is the angle of the arc used in calculations. This should be in degrees
	double _arcAngle = 30;
    
    //! The radius of the arc from the center point
    double _radius;
    
    bool _isCounterClockWise = true;
public:
	arcShape()
    {
        _nodeIndex1 = 0;
        _nodeIndex2 = 0;
	
        _isHidden = false;
	
        _arcAngle = 90.0d;
        _maxSideLength = 10.0d;
    }
	
	void setArcAngle(double angleOfArc)
    {
        _arcAngle = abs(angleOfArc);
        if(angleOfArc > 0)
            _isCounterClockWise = true;
        else
            _isCounterClockWise = false;
    }
	
	double getArcAngle()
    {
        return _arcAngle;
    }

	
	void setNumSegments(unsigned int segments)
    {
        _numSegments = segments;
    }
	
	unsigned int getnumSegments()
    {
        return _numSegments;
    }
    
    
    void draw()
    {
     //   double startAngle = ((atan2(yCenterCoordinate - startNodeYCoordinate, xCenterCoordinate - startNodeXCoordinate) * 180.0) / PI)  - 180.0;
        /* Computes the start and stop angle for the arc. atan returns in radians. This gets converted to degrees */
        
        if(_numSegments == -1)
        {
            if(_arcAngle < 10)
                _numSegments = 10;
            else
                _numSegments = _arcAngle / 3.0;
        }
        else if(_numSegments < 2)
            _numSegments = 2;
        
        double theta = 0;
        if(_isCounterClockWise)
            theta = (_arcAngle) / (double)_numSegments;
        else
            theta = (-_arcAngle) / (double)_numSegments;
            
        double startAngle = atan2(yCenterCoordinate - _firstNode->getCenterYCoordinate(), xCenterCoordinate - _firstNode->getCenterXCoordinate()) * (180.0 / PI) - 180.0;
        
        glBegin(GL_LINE_STRIP);
            glVertex2d(_firstNode->getCenterXCoordinate(), _firstNode->getCenterYCoordinate());
            
            for(int i = 1; i < _numSegments; i++)
            {
                double arc = (startAngle + i * theta) * (PI / 180); 
                double x = _radius * cos(arc);
                double y = _radius * sin(arc);
                
                glVertex2d(xCenterCoordinate + x, yCenterCoordinate + y);
            }
            glVertex2d(_secondNode->getCenterXCoordinate(), _secondNode->getCenterYCoordinate());
        glEnd();
    }	

    /*! \brief  This function will be calculating the radius and center point of the arc
	 *			The idea is as follows:
     *          By knowing the 2 endpoints and the arc angle, we are able to caluclate the radius and the center point
     *          For the radius, this is the law of cosines: c^2 = 2 * R^2 * (1 - cos(theta) )
                where c is the length of the sector through the beginning and starting endpoints and theta is the arc angle
                Then, we can calculate the 
	 */
    void calculate(std::vector<node> &arcNodeList)
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
     /*   if(arcNodeList[nodeIndex2].getCenterXCoordinate() > arcNodeList[nodeIndex1].getCenterXCoordinate())
        {
            startNodeXCoordinate = arcNodeList[nodeIndex2].getCenterXCoordinate();
            endNodeXCoordinate = arcNodeList[nodeIndex1].getCenterXCoordinate();
            
            startNodeYCoordinate = arcNodeList[nodeIndex2].getCenterYCoordinate();
            endNodeYCoordinate =  arcNodeList[nodeIndex1].getCenterYCoordinate();
        }*/
     //   else

        distanceSquared = pow(_firstNode->getCenterXCoordinate() - _secondNode->getCenterXCoordinate(), 2) + pow(_firstNode->getCenterYCoordinate() - _secondNode->getCenterYCoordinate(), 2);
        
        _radius = sqrt(distanceSquared / (2.0 * (1.0 - cos(_arcAngle * PI / 180.0))));// Fun fact, the cosine function evaluates in radians
        
        xMid = (_firstNode->getCenterXCoordinate() + _secondNode->getCenterXCoordinate()) / 2.0;
        
        yMid = (_firstNode->getCenterYCoordinate() + _secondNode->getCenterYCoordinate()) / 2.0;
        
        slope = (_firstNode->getCenterYCoordinate() - _secondNode->getCenterYCoordinate()) / (_firstNode->getCenterXCoordinate() - _secondNode->getCenterXCoordinate());
        
        midSlope = -1.0 / slope;
        
        a = sqrt(pow(_radius, 2) - (distanceSquared / 4.0)); // This is just an intermediate varable to make calculations easier
        
        if((_firstNode->getCenterYCoordinate() > _secondNode->getCenterYCoordinate() && _isCounterClockWise) || (_firstNode->getCenterYCoordinate() < _secondNode->getCenterYCoordinate() && !_isCounterClockWise))
        {
            // This will calculate the center that is below the arc.
            // If the start node is lower then the end node, the logic is reversed. This portion will create
            // the center above the arc.
            xCenterCoordinate = xMid + a / sqrt(pow(midSlope, 2) + 1);
            yCenterCoordinate = yMid + (midSlope * a) / sqrt(pow(midSlope, 2) + 1);
        }
        else
        {
            // This will calculate the center above the arc
            xCenterCoordinate = xMid - a / sqrt(pow(midSlope, 2) + 1);
            yCenterCoordinate = yMid - (midSlope * a) / sqrt(pow(midSlope, 2) + 1);
        }

    }
    
    double getRadius()
    {
        return _radius;
    }	
    
    double getArcLength()
    {
        return _radius * _arcAngle * (PI / 180.0);
    }
    

	
};



#endif