#ifndef GEOMETRY_SHAPES_H_
#define GEOMETRY_SHAPES_H_

#include <wx/wx.h>
#include <wx/glcanvas.h>
#include <UI/common.h>
#include <freeglut.h>
#include <gl.h>
#include <glu.h>
//#include <UI/openGLGeometry.h>

/*! \class geometry2D
	\brief This is the base class for all of the geometry classes
*/
class geometry2D
{
public:
	
	geometry2D();
	
	void refresh();
	
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
	
	//! the function will be called when the user selects the geomtry shape
	void toggleSelect();
private:
	
	//! The number of vertices for the geometry shape
	int numberOfVertices;
	
	//! This is a boolean that willl indicate if the user selects the geometric shape
	bool isSelected;
};



class edgeLineShape : geometry2D
{
public:
	edgeLineShape();
	
	void setFirstNodeIndex(int index);
	void setSecondNodeIndex(int index);
	
	int getFirstNodeIndex();
	int getSecondNodeIndex();
private:
	/*! \brief  A line is composed of 2 nodes.
	 *			The nodes are stored in a vector array (which is a dynamically allocated array)
	 *			How do we tell the object which node the line connects to?
	 *			We differenatiate by using the index of the array.
	 *			This variables stores the index of first node which connects the line.
	 */
	int nodeIndex1
	
	/*! \brief  A line is composed of 2 nodes.
	 *			The nodes are stored in a vector array (which is a dynamically allocated array)
	 *			How do we tell the object which node the line connects to?
	 *			We differenatiate by using the index of the array.
	 *			This variables stores the index of second node which connects the line.
	 */
	int nodeIndex2;
};



class rectangleShape : edgeLineShape
{
public:
	rectangleShape();
	rectangleShape(double xCenterPoint, double yCenterPoint);
	
	void getArea();
	void getParameter();
	
	double getSideLengthA();
	double getSideLengthB();
	
	double getXPoint();
	double getYPoint();
	
	void setSideLengthA(double length);
	void setSideLengthB(double length);
	
	void draw();
private:
	double sideLengthA;
	double sideLengthB;
	
	//! This is the point in x of the center for the node
	double xPoint;
	
	//! This is the point in y of the center for the node
	double yPoint;
};



class node : rectangleShape
{
public:
	node(double xCenter, double yCenter);
	
	//! This function will retunr the distance between this object and another
	double getDistance(double x, double y);
	
};


class blockLabel : node
{
	
};

class arcShape : geometry2D
{
public:
	arcShape();

	void setFirstNodeIndex(int index);
	void setSecondNodeIndex(int index);
	
	int getFirstNodeIndex();
	int getSecondNodeIndex();
private:
	/*! \brief  An arc is composed of 2 nodes.
	 *			The nodes are stored in a vector array (which is a dynamically allocated array)
	 *			How do we tell the object which node the line connects to?
	 *			We differenatiate by using the index of the array.
	 *			This variables stores the index of first node which connects the line.
	 */
	int nodeIndex1
	
	/*! \brief  An arc is composed of 2 nodes.
	 *			The nodes are stored in a vector array (which is a dynamically allocated array)
	 *			How do we tell the object which node the line connects to?
	 *			We differenatiate by using the index of the array.
	 *			This variables stores the index of second node which connects the line.
	 */
	int nodeIndex2;	
};



class circleShape : arcShape
{
	
};



class ellipseShape : circleShape
{
	
};

/*! \class nodePoint
	\brief This class is used to create a node
*/
class nodePoint
{
public:
	//! The constructor will be called in order to draw the node at scoordinate and ycoordinate
	nodePoint(GLdouble xcoordinate, GLdouble ycoordinate, wxGLCanvas *parent);
	
	/************
	* Variables *
	*************/
private:
	//! The x point for the center
	GLdouble xPoint;
	
	//! The y point for the center
	GLdouble yPoint;
	
	GLdouble pixelXPoint;
	
	GLdouble pixelYPoint;
};


#endif