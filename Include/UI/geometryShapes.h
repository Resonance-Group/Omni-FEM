#ifndef GEOMETRY_SHAPES_H_
#define GEOMETRY_SHAPES_H_

#include <wx/wx.h>
#include <wx/glcanvas.h>
//#include <UI/common.h>
#include <freeglut.h>
#include <gl.h>
#include <glu.h>
#include <math.h>

//#include <UI/openGLGeometry.h>

/*! \class geometry2D
	\brief This is the base class for all of the geometry classes
*/
class geometry2D
{
public:
	
	geometry2D();
	
//	void refresh();
	
	//! This will set the number of vertexs for the shape
	/*	
	 *	For a line shape, there will need to be 2 vertices.
	 *	For a triangle, there will be 3 vertices
	 *	For a rectangle, there will be 4 vertices
	 *	For polygons, there will be 5+ vertices
	 *	The circle is a special case will have 0 vertices
	 */
	void setVertexNumber(int number);
	
	//! This will get the number of vertices
	int getVertexNumber();
	
	//! Function used to set the X coordiante for the center point of the shape
	void setCenterXCoordinate(double xCenter);
	
	//! Function used to set the Y coordiante for the center point of the shape
	void setCenterYCoordiante(double yCenter);
	
	//! Function used to get the X Coordinate of the center point point of the shape
	double getCenterXCoordinate() const;
	
	//! Function used to get the Y Coordinate of the center point point of the shape
	double getCenterYCoordinate() const;
	
	//! Function used to set the group that the shape is assocated with
	void setGroup(int group);
	
	//! Function used to retrieive the group number that the shape is associated with
	int getGroup();
	
	//! the function will be called when the user selects the geomtry shape
	void toggleSelect();
	
	//! This function will return the selected status
	bool getIsSelected();
protected:
	
	//! The number of vertices for the geometry shape
	int numberOfVertices;
	
	//! This is a boolean that willl indicate if the user selects the geometric shape
	bool isSelected;
	
	//! Data type used to store the group number that the shape is associated with
	int groupNumber;

	//! This data type stroes the center x  position
	double xCenterCoordinate;
	
	//! This data type stores the center y position
	double yCenterCoordinate;
};



class edgeLineShape : public geometry2D
{
public:
	edgeLineShape();
	
	void setFirstNodeIndex(int index);
	void setSecondNodeIndex(int index);
	
	int getFirstNodeIndex() const;
	int getSecondNodeIndex() const;
	
	void setHiddenStatus(bool status);
	bool getHiddenStatus();
	
	void setBoundaryMarker(std::string boundary);
    std::string getBoundaryMarker();
    
    void setConductor(std::string conductor);
    std::string getConductor();
    
    virtual void draw(int node1X, int node1Y, int node2X, int node2Y);
	
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
	std::string boundaryMarker;
	
	//! The conductor that the line is associated with
	std::string inConductor;
};



class rectangleShape : public geometry2D
{
public:
	rectangleShape(double xCenterPoint, double yCenterPoint);
	rectangleShape();
    
//	void getArea();
//	void getParameter();
	
//	double getSideLengthA();
//	double getSideLengthB();
	
//	double getXPoint();
//	double getYPoint();
	
//	void setSideLengthA(double length);
//	void setSideLengthB(double length);
	
	double getDistance(double xp, double yp);
	
	//! This is the function that is called in order to draw the rectangle. One thing that is 
	virtual void draw();
private:
//	double sideLengthA;
//	double sideLengthB;
};



class node : public rectangleShape
{
public:
	node(double xCenter, double yCenter);
	node();
    
	//! This function will set the center xPixel value used in drawing the shape 
	void setCenterXPixel(int xPix);
    
    void setCenter(double xCoor, double yCoor);
	
	//! This function will set the center yPixel value used in drawing the shape 
	void setCenterYPixel(int yPix);
	
	int getCenterXPixel();
	
	int getCenterYPixel();
	
	//! This function will draw the shape
	void draw();
	
	void setNodeIndex(int index);
	
	int getNodeIndex();
	
private:
	//! This variable stores the x coordinate for the center in pixels
	int xPixel;

	//! This variable stores the y coordinate for the center in pixels	
	int yPixel;
	
	//! The nodes are stored in array. For quickier accesssing, this will store the index which is associated with the node
	int nodeIndex;
};



class blockLabel : public rectangleShape
{
public:
	blockLabel();
	
	
	
private:
	double maxArea;
	
	std::string blockType;
	
	bool isExternal;
	
	bool isDefault;
};



class arcShape : public edgeLineShape
{
public:
	arcShape();
	
	void setArcLength(double lengthOfArc);
	
	double getArcLength();

private:
	
	bool isNormalDirection;
	
	bool isHidden;
	
	double maxSideLength;
	
	double arcLength;
	
	std::string boundaryMarker;
	
	std::string inConductor;
	
	
};



class circleShape : public arcShape
{
	
};



class ellipseShape : public circleShape
{
	
};




#endif