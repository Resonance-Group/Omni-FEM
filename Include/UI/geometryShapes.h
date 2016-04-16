#ifndef GEOMETRY_SHAPES_H_
#define GEOMETRY_SHAPES_H_

#include <wx/wx.h>
#include <wx/glcanvas.h>
#include <UI/common.h>
#include <freeglut.h>
#include <gl.h>
#include <glu.h>
//#include <UI/openGLGeometry.h>


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