#ifndef GEOMETRY_SHAPES_H_
#define GEOMETRY_SHAPES_H_

#include <wx/wx.h>
#include <wx/glcanvas.h>
#include <UI/common.h>
#include <freeglut.h>
#include <gl.h>
#include <glu.h>
//#include <UI/openGLGeometry.h>


class geometry2D
{
public:
	
	geometry2D();
	
	void refresh();
	
	void setVertexNumber(int number);
	
	int getVertexNumber();
private:
	int numberOfVertexs;
	bool isSelected;
};



class edgeLineShape : geometry2D
{
	
};



class rectangleShape : edgeLineShape
{
public:
	rectangleShape();
	
	void getArea();
	void getParameter();
	
	double getSideLengthA();
	double getSideLengthB();
	
	void setSideLengthA(double length);
	void setSideLengthB(double length);
	
	void draw();
private:
	double sideLengthA;
	double sideLengthB;
	
	
	
};



class node : rectangleShape
{
	
};




class arcShape : geometry2D
{
	
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