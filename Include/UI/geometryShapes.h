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
public:
	
	geometry2D()
    {
        
    }
	
//	void refresh();
	
	//! This will set the number of vertexs for the shape
	/*	
	 *	For a line shape, there will need to be 2 vertices.
	 *	For a triangle, there will be 3 vertices
	 *	For a rectangle, there will be 4 vertices
	 *	For polygons, there will be 5+ vertices
	 *	The circle is a special case will have 0 vertices
	 */
	void setVertexNumber(int number)
    {
        numberOfVertices = number;
    }
	
	//! This will get the number of vertices
	int getVertexNumber()
    {
        return numberOfVertices;
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
    
protected:
	
	//! The number of vertices for the geometry shape
	int numberOfVertices;
	
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
};



class edgeLineShape : public geometry2D
{
private:
    segmentProperty _property;
    
public:
	edgeLineShape();
	
	void setFirstNodeIndex(int index);
	void setSecondNodeIndex(int index);
	
	int getFirstNodeIndex() const;
	int getSecondNodeIndex() const;
	
	void setHiddenStatus(bool status);
	bool getHiddenStatus();
	
	void setBoundaryMarker(wxString boundary);
    wxString getBoundaryMarker();
    
    void setConductor(std::string conductor);
    std::string getConductor();
    
    virtual void draw(double node1X, double node1Y, double node2X, double node2Y);
    
    segmentProperty *getSegmentProperty()
    {
        return &_property;
    } 
	
protected:
	/*! \brief  A line is composed of 2 nodes.
	 *			The nodes are stored in a vector array (which is a dynamically allocated array)
	 *			How do we tell the object which node the line connects to?
	 *			We differenatiate by using the index of the array.
	 *			This variables stores the index of first node which connects the line.
	 */	
	int nodeIndex1;
	
	/*! \brief  A line is composed of 2 nodes.
	 *			The nodes are stored in a vector array (which is a dynamically allocated array)
	 *			How do we tell the object which node the line connects to?
	 *			We differenatiate by using the index of the array.
	 *			This variables stores the index of second node which connects the line.
	 */
	int nodeIndex2;
	
	//! Status to indicate if the line is hidden
	bool isHidden;
	
	//! The length of the line?
	double maxSideLength;
	
	//! The boundary that the line is associated with
	wxString boundaryMarker;
	
	//! The conductor that the line is associated with
	std::string inConductor;
};



class rectangleShape : public geometry2D
{
public:
	rectangleShape(double xCenterPoint, double yCenterPoint);
	rectangleShape();
	
	double getDistance(double xp, double yp);
	
	//! This is the function that is called in order to draw the rectangle. One thing that is 
	virtual void draw();
};



class node : public rectangleShape
{
private:
	//! The nodes are stored in array. For quickier accesssing, this will store the index which is associated with the node
	int nodeIndex;
    
    nodeSetting _nodalSettings;
public:
	node(double xCenter, double yCenter);
	node();
    
    void setCenter(double xCoor, double yCoor);
	
	//! This function will draw the shape
	void draw();
	
	void setNodeIndex(int index);
	
	int getNodeIndex();
    
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



class blockLabel : public rectangleShape
{
private:
	double maxArea;
	
	std::string blockType;
	
	bool isExternal;
	
	bool isDefault;
public:
	blockLabel();
	

};



/*! This class inherits from the edgeLineShape class bescause an arc is like a line but with an angle */
class arcShape : public edgeLineShape
{
private:
    
	bool isNormalDirection;
	
	bool isHidden;
	
	unsigned int numSegments = 3;
	
    //! This data is the angle of the arc used in calculations. This should be in degrees
	double arcAngle = 30;
    
    //! The radius of the arc from the center point
    double radius;
    
    bool isCounterClockWise = true;
    
    double startNodeXCoordinate;
    
    double startNodeYCoordinate;
    
    double endNodeXCoordinate;
    
    double endNodeYCoordinate;
public:
	arcShape();
	
	void setArcAngle(double angleOfArc);
	
	double getArcAngle();
	
	void setNumSegments(unsigned int segments);
	
	unsigned int getnumSegments();
    
    void draw();

    /*! \brief  This function will be calculating the radius and center point of the arc
	 *			The idea is as follows:
     *          By knowing the 2 endpoints and the arc angle, we are able to caluclate the radius and the center point
     *          For the radius, this is the law of cosines: c^2 = 2 * R^2 * (1 - cos(theta) )
                where c is the length of the sector through the beginning and starting endpoints and theta is the arc angle
                Then, we can calculate the 
	 */
    void calculate(std::vector<node> &arcNodeList);
    
    double getRadius();
    
    double getArcLength();
    

	
};



#endif