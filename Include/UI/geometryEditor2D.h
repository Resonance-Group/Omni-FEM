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
	geometryEditor2DAbstraction();
	
	
	
	/************
	* Variables *
	*************/
private:
	
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
	geometryEditor2DController();
	
	
	
	/************
	* Variables *
	*************/
private:
	
//! The object for the abstract layer of the 
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
	void createOpenGLCanvas();
	
private:
	
	
	
	/************
	* Variables *
	*************/
private:
	wxGLCanvas *drawingCanvas;
	wxGLContext *drawingContext;
//	wxGLAttributes dispAttributes;
};








#endif