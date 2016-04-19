#ifndef OPENGLGEOMETRY_H_
#define OPENGLGEOMETRY_H_

#include <wx/wx.h>
#include <wx/glcanvas.h>
#include <UI/common.h>
#include <freeglut.h>
#include <gl.h>
#include <glu.h>
#include <UI/geometryShapes.h>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <UI/wxGLString.h>



class geometryEditorCanvas : public wxGLCanvas
{
public:
	//! This would be used for initilizeing the openGL settings
	/*! 
		The code found in this constructor is used to initilize the openGL settings.
		It is also initlizing wxWidgets so that OpenGL commands can be used
	*/
	geometryEditorCanvas(wxWindow *par, const wxPoint &position, const wxSize &size);
	
	
private:
    //! This is the event that is fired when the canvas is drawn or re-drawn
	void onGeometryPaint(wxPaintEvent &event);
	
    //! Rendering the geometry
	void render();
	
	//! This function will convert a xpoint (pixel) to an x-coordinate value
	/*
		This is 1/2 of the mapping function. The function follow the idea presented in the following webpage:
    *   https://msdn.microsoft.com/en-us/library/jj635757(v=vs.85).aspx
    *   
    *   The mapping is a affline transformation and the program is using the equation:
    *   x' = ax + by + c (The coefficients used here are defined as private variables)
    *   The coefficients can be solved with the use of matrices. The program will need to
    *   resolve for the coefficients when the zoom changes
	*/
	double convertToXCoordinate(double xPoint, double yPoint);
	
	//! This function will convert a ypoint (pixel) to an y-coordinate value
	/*
		This is 1/2 of the mapping function. The function follow the idea presented in the following webpage:
    *   https://msdn.microsoft.com/en-us/library/jj635757(v=vs.85).aspx
    *   
    *   The mapping is a affline transformation and the program is using the equation:
    *   y' = bx - ay + d (The coefficients used here are defined as private variables)
    *   The coefficients can be solved with the use of matrices. The program will need to
    *   resolve for the coefficients when the zoom changes
	*/
	double convertToYCoordinate(double xPoint, double yPoint);
	
    //! The event that will be fired when the window experiences a resize
	void onResize(wxSizeEvent &event);
	
 //   int viewPortMode = ViewPortMode::VIEWPORT_MODE_FULL;
    
    //! The event that will be fired when a key on the keyboard is pressed down
    void onKeyDown(wxKeyEvent &event);
	
	//! The event that is fired when the mouse wheel is rolled
	/*
		This event is primarly for zooming the view
	*/
	void onMouseWheel(wxMouseEvent &event);
	
	//! This event will cause the focus to be transfered to the canvas
	void onEnterWindow(wxMouseEvent &event);
	
	//! This event will cause the focus to be transfered back to the parent window
	void onLeavingWindow(wxMouseEvent &event);
	
	//! This event is fired when the mouse moves on the canvas
	/*
		Currently, this functions updates the mouseX and mouseY variables which store the coordinates of the mouse
		pointer. The reference is the the top left corner of the canvas
	*/
	void onMouseMove(wxMouseEvent &event);
	
	void onMouseLeftDown(wxMouseEvent &event);
	
	void drawGrid();
	/************
	* Variables *
	*************/
private:	
	
    //! This is the context which will be associated to the class
	wxGLContext *geometryContext;
	
	double canvasWidth = 0;
	double canvasHeight = 0;
	
	float zoomX = 1;
	float zoomY = 1;
	
	//! This variable will give the mouse x coordinate wrt top left corner of canvas.
	int mouseX;
	
	//! This variable will give the mouse y coordinate wrt top left corner of canvas.
	int mouseY;
	
	//! This will give the mouse x coordinate in the cartesian plane of the canvas
	double mouseGraphX;
	
	//! This will be the mouse y coordinate in the cartesian plane of the canvas
	double mouseGraphY;
	
	double coordinateFactorWidth;

	double coordinateFactorHeight;
	
	double zoomFactor = 2;
	
	double totalZoom = 1;

	const int factor = 10;
    
    //! This is a coefficient that is used to define the mapping of the pixels to the coordinate system used in the program. This 
    /*
     *  For more complete documentation, please read documentation for the function that 
     *  uses this variable
     * 
     */ 
    double Acoeff = (double)-0.0393804;
	
    //! This is a coefficient that is used to define the mapping of the pixels to the coordinate system used in the program. This 
    /*
     *  For more complete documentation, please read documentation for the function that 
     *  uses this variable
     * 
     */  
    double Bcoeff = (double)-0.0166944;
    
    //! This is a coefficient that is used to define the mapping of the pixels to the coordinate system used in the program. This 
    /*
     *  For more complete documentation, please read documentation for the function that 
     *  uses this variable
     * 
     */ 
     double Ccoeff = (double)-10.0;
     
     //! This is a coefficient that is used to define the mapping of the pixels to the coordinate system used in the program. This 
    /*
     *  For more complete documentation, please read documentation for the function that 
     *  uses this variable
     * 
     */ 
     double Dcoeff = (double)10.0;
    //! These variables contain the screen offset
	GLfloat cameraX = 0.0f, cameraY = 0.0f;
	
    wxGLString *debugCoordinate;
    
    wxGLString *debugPixelCoordinate;
    
	nodePoint *testPoint;
	
	DECLARE_EVENT_TABLE();
};





#endif