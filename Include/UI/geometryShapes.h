#ifndef GEOMETRY_SHAPES_H_
#define GEOMETRY_SHAPES_H_

#include <math.h>

#include <glew.h>
#include <freeglut.h>

#include <wx/wx.h>
#include <wx/glcanvas.h>

#include <common/GeometryProperties/BlockProperty.h>
#include <common/GeometryProperties/NodeSettings.h>
#include <common/GeometryProperties/SegmentProperties.h>

#include <UI/ModelDefinition/OGLFT.h>

#include <common/Vector.h>

/*! \class geometry2D
	\brief This is the base class for all of the geometry classes
*/
class geometry2D
{
protected:
	
	//! This is a boolean that willl indicate if the user selects the geometric shape
	bool _isSelected = false;
    
    //! This is used to indicate if the geometry that is selected is for a group
    bool isGroupSelectedState = false;

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

	//! the function will be called when the user selects the geomtry shape
	void setSelectState(bool state)
    {
        _isSelected = state;
    }
	
	//! This function will return the selected status
	bool getIsSelectedState()
    {
        return _isSelected;
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
private:

    bool _isDragging = false;
    
public:
    rectangleShape() : geometry2D()
    {
        
    }
    
	rectangleShape(double xCenterPoint, double yCenterPoint) : geometry2D()
    {
        xCenterCoordinate = xCenterPoint;
        yCenterCoordinate = yCenterPoint;
    }
	
	//! This function will get the distance between two points. The first being itself and the second, the input. The values that are taken in are the x and y coordinate of the second point
	double getDistance(double xp, double yp)
    {
        return sqrt(pow((xCenterCoordinate - xp), 2) + pow((yCenterCoordinate - yp), 2));
    }
    
    double getDistance(wxRealPoint point)
    {
        return sqrt(pow((xCenterCoordinate - point.x), 2) + pow((yCenterCoordinate - point.y), 2));
    }
    
    double getDistance(rectangleShape testNode)
    {
        return sqrt(pow(xCenterCoordinate - testNode.getCenterXCoordinate(), 2) + pow(yCenterCoordinate - testNode.getCenterYCoordinate(), 2));
    }
    
    void setCenter(double xCoor, double yCoor)
    {
        xCenterCoordinate = xCoor;
        yCenterCoordinate = yCoor;
    }
    
    void moveCenter(double xCoor, double yCoor)
    {
        xCenterCoordinate += xCoor;
        yCenterCoordinate += yCoor;
    }
    
    bool getDraggingState()
    {
        return _isDragging;
    }
    
    void setDraggingState(bool state)
    {
        _isDragging = state;
    }
	
	//! This is the function that is called in order to draw the rectangle. One thing that is 
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



class node : public rectangleShape
{
private:
    nodeSetting _nodalSettings;
public:
	node(double xCenter, double yCenter) : rectangleShape(xCenter, yCenter)
    {

    }
    
    node()
    {
        
    }
    
	//! This function will draw the shape
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
    
    
};



class edgeLineShape : public geometry2D
{
protected:
    segmentProperty _property;
    
protected:
	
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
    
    node *getFirstNode()
    {
        return _firstNode;
    }
    
    void setSecondNode(node &a_node)
    {
        _secondNode = &a_node;
    }
    
    node *getSecondNode()
    {
        return _secondNode;
    }
    
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
	std::string blockType;
    
    blockProperty _property;
public:
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
    
    void drawBlockName(OGLFT::Grayscale *textRender, double factor)
    {
        double offset = 0.02 * factor;
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        textRender->draw(xCenterCoordinate + offset, yCenterCoordinate + offset, _property.getMaterialName().c_str());
    }
    
    void drawCircuitName(OGLFT::Grayscale *textRender, double factor)
    {
        double offset = 0.02 * factor;
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        if(_property.getCircuitName() != "None")
            textRender->draw(xCenterCoordinate + offset, yCenterCoordinate - offset, _property.getCircuitName().c_str());
    }
	
    blockProperty *getProperty()
    {
        return &_property;
    }
    
    blockProperty *getAddressProperty()
    {
        return &_property;
    }
    
    void setPorperty(blockProperty property)
    {
        _property = property;
    }
    
    

};



/*! This class inherits from the edgeLineShape class bescause an arc is like a line but with an angle */
class arcShape : public edgeLineShape
{
private:
	unsigned int _numSegments = 3;
	
    //! This data is the angle of the arc used in calculations. This should be in degrees
	double _arcAngle = 30;
    
    //! The radius of the arc from the center point
    double _radius;
    
    bool _isCounterClockWise = true;
public:
	arcShape()
    {
        
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
        if(_isCounterClockWise)
            return _arcAngle;
        else
            return -_arcAngle;
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
        if(_isSelected)
            glColor3d(1.0, 0.0, 0.0);
        else
            glColor3d(0.0, 0.0, 0.0);
            
        
        if(_numSegments == -1)// Hey this code needs to be looked at!
        {
            if(_arcAngle < 10)
                _numSegments = 10;
            else
                _numSegments = _arcAngle / 3.0;
        }
        else if(_numSegments < 2)
            _numSegments = 2;
        
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
     * See this forum post: http://mymathforum.com/algebra/21368-find-equation-circle-given-two-points-arc-angle.html
     * 
     * This function will be calculating the radius and center point of the arc
	 *			The idea is as follows:
     *          By knowing the 2 endpoints and the arc angle, we are able to caluclate the radius and the center point
     *          For the radius, this is the law of cosines: c^2 = 2 * R^2 * (1 - cos(theta) )
                where c is the length of the sector through the beginning and starting endpoints and theta is the arc angle
                Then, we can calculate the 
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
            // TOD: Come up with new logic here
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
            
            return;
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
            
            return;
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
            
            return;
        }
        
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
        
        return;
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