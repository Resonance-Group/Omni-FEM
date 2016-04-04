#ifndef GEOMETRYEDITOR2D_H_
#define GEOMETRYEDITOR2D_H_

/*
	This file will contain all of the definitions for the 2D Geometry Editor
*/
#include <wx/wx.h>
#include <wx/glcanvas.h>
#include <wx/bmpbuttn.h>
#include <wx/window.h>
#include <UI/common.h>
#include <freeglut.h>
#include <gl.h>
#include <glu.h>



#define FONTSIZE		14
#define BORDER			10
#define BMPBUTTONSIZE	30

#define SCREEN_FPS		60

/*! \class geometryEditor2DAbstraction
	\brief The main class for the 2D geometry Editor
	
	This is the abstraction part of the 2D geometry editor
*/
class geometryEditor2DAbstraction
{
	/**********************
	* Function prototypes *
	***********************/
public:
	//! The constructor for the class. This is what will get called first in order to create and manipulate 2D geometry
//	geometryEditor2DAbstraction();
	
	//! Will query for the drawing width
	int getDrawingSizeWidth();
	
	//! Will set the drawing size width
	void setDrawingSizeWidth(int width);
	
	//! Will get the Height of the drawing canvas
	int getDrawingSizeHeight();
	
	//! Will set the height of the drawing canvas
	void setDrawingSizeHeight(int height);
	
	
	/************
	* Variables *
	*************/
private:

	//! This variable will store the X Value of the drawing canvas size
	int drawingSizeWidth;
	
	//! This will store the Y Value of the drawing canvas size
	int drawingSizeHeight;
	
};



/*! \class geometryEditor2DController
	\brief The main class for the 2D geometry Editor
	
	This is the controller part of the 2D geometry editor
*/
class geometryEditor2DController
{
	/**********************
	* Function prototypes *
	***********************/
public:
	//! The constructor for the class. This is what will get called first in order to create and manipulate 2D geometry
//	geometryEditor2DController();
	
	//! This will get the width from the abstract layer
	int getDrawingWidthAbstract();
	
	//! This will set the width in the abstract layer
	void setDrawingWidthAbstract(int width);
	
	//! This will get the height in the abstract layer
	int getDrawingHeightAbstract();
	
	//! This will set the drawing height in the abstract layer
	void setDrawingHeightAbstract(int height);
	
	
	/************
	* Variables *
	*************/
private:
	//! This is the varable object for the abstract layer
	geometryEditor2DAbstraction abstraction;

};



class geometryEditorContext : public wxGLContext
{
public:
	geometryEditorContext(wxGLCanvas *canvas);
	
	void renderGeometry();
};



class geometryEditorCanvas : public wxGLCanvas
{
public:
	geometryEditorCanvas(wxWindow *par, const wxPoint &position, const wxSize &size);
	
private:
	void onGeometryPaint(wxPaintEvent &event);
	
	geometryEditorContext *canvasContext;
	
	DECLARE_EVENT_TABLE();
};



/*! \class geometryEditor2DPresentation
	\brief The main class for the 2D geometry Editor
	
	This is the presentation part of the 2D geometry editor
*/
class geometryEditor2DPresentation : public wxPanel
{
	/**********************
	* Function prototypes *
	***********************/
public:
	//! The constructor for the class. This is what will get called first in order to create and manipulate 2D geometry
	geometryEditor2DPresentation(wxWindow *par, const wxPoint &position, const wxSize &size);
	
	
	/************
	* Variables *
	*************/
private:
	geometryEditorCanvas *drawingCanvas;
	geometryEditor2DController controller;
	
	DECLARE_EVENT_TABLE();
};









#endif