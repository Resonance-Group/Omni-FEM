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
#include <common/Vector.h>
#include <math.h>
#include <UI/geometryEditorController.h>
#include <sstream>

using namespace std;

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
	double convertToXCoordinate(int xPixel, int cameraOffset);
    double convertToXCoordinate(int xPixel);
	
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
	double convertToYCoordinate(int yPixel, int cameraOffset);
	double convertToYCoordinate(int yPixel);
    
	//! Converts a (x, y) coordinate point to a pixel coordinate. Returns the X pixel point
	/*
	 * 	This is 1/2 of a feature. The coorseopnding function is convertToYPixel.
	 *  Both need to be called in order to create a pixel pair.
	 */
	double convertToXPixel(double XCoor, int cameraOffset);
	double convertToXPixel(double XCoor);
    
	//! Converts a (x, y) coordinate point to a pixel coordinate. Returns the Y pixel point
	/*
	 * 	This is 1/2 of a feature. The coorseopnding function is convertToXPixel.
	 *  Both need to be called in order to create a pixel pair.
	 */
	double convertToYPixel(double YCoor);
    double convertToYPixel(double YCoor, int cameraOffset);
	
	//! This is the function that is called when the user would like to add a new node
	void addNode(double xPoint, double yPoint, double distance);
	
	//! This function will be called in order to create a line between 2 nodes
	void addLineSegment(int node0, int node1, edgeLineShape *parseSegment);
	
	//! This function will add an arc segment between two selected nodes
	void addArcSegment(arcShape &arcSeg, double tolerance = 0);
	
	/*! This function will check to see if there is an intersection between two lines. If so, get the node of intersection and return true
     * node0 is the first node that the user selects
     * node1 is the second node that the user selects
     * lineSegment is the line segment index that will be checked for an intersection
     * intersectionXPoint and YPoint are the (X, Y) intercetion points of the two lines
     */
	bool getIntersection(int node0, int node1, int lineSegment, double &intercetionXPoint, double &intercestionYPoint);
	
	//! This function is called in order to toggel the block list creation flag
	void toggleBlockListCreation();
	
	//! This fuinction is to be used on geometry objects to convert their center coordinate value into a center Pixel value. 
	void convertPixelToCoor(double xPoint, double yPoint, int &xPixel, int &yPixel);
	
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
	
	//! This function will determine the center and the radius of the given arc.
	void getCircle(arcShape &arc, Vector &center, double &radius);
	
	/*! This function will calculate the shortest distance from a point to an arc */
	double shortestDistanceFromArc(Vector point, arcShape &arcSegment);
	
	/*! This function will get the number of instersection points where a line and an arc intersect */
	int getLineToArcIntersection(edgeLineShape &lineSegment, arcShape &arcSegment, Vector *pointVec);
	
	/*! This function will calculate the number of intersection points where two arcs intersect */
	int getArcToArcIntersection(edgeLineShape &segment, arcShape &arc, Vector &intersectionVector);
    
    /*! This function needs to be called whenever there is a draw. */
    void updateProjection();
    
    /*! Function called when the Right mouse button is clicked */
    void onMouseRightDown(wxMouseEvent &event);
    
	/************
	* Variables *
	*************/
private:	
	
    //! This is the context which will be associated to the class
	wxGLContext *geometryContext;
	
	//! This is the controller potion for the geometry editor
	geometryEditorController geoController;
	
	double canvasWidth = 0;// The height of the canvas
	double canvasHeight = 0;// The width of the canvas /* These two comments need to be confirmed */
	
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
	
	double zoomFactor = 1;
	
	double totalZoom = 1;

	const int factor = 10;
    
    double gridStep = 0.05; // This variable controls the grid step which controls how the graph is drawn
    
    //! This is a coefficient that is used to define the mapping of the pixels to the coordinate system used in the program. This 
    /*
     *  For more complete documentation, please read documentation for the function that 
     *  uses this variable
     * 
     */ 
    double Ycoeff = (double)-0.0829876d;
	
    //! This is a coefficient that is used to define the mapping of the pixels to the coordinate system used in the program. This 
    /*
     *  For more complete documentation, please read documentation for the function that 
     *  uses this variable
     * 
     */  
    double Xcoeff = (double)0.0326264d;
    
    //! This is a coefficient that is used to define the mapping of the pixels to the coordinate system used in the program. This 
    /*
     *  For more complete documentation, please read documentation for the function that 
     *  uses this variable
     * 
     */ 
     double graphOffset = (double)10.0d;
	 
    //! These variables contain the screen offset
	float cameraX = 0.0f, cameraY = 0.0f;
	
	//! This variable will store the index of the first selected node.
	/*!
	 *	This variable is used to determine which two nodes the user would 
		like to create an arc or line segment
	 */
	int firstSelectedNodeIndex = -1;
	
	//! This is a flag which indicates the user would like to create a block label
	bool blockLabelCreationIsEnabled = false;
	
	//! This flag will indicate if the user would like to create an arc or a line
	bool lineCreationFlag = false;
	
	bool recalculatenodeCenters;
	
	/*! This array string will contain all of the boudy lists in it */
	wxArrayString boundaryList;
	
    wxGLString *debugCoordinate;
    
    wxGLString *debugPixelCoordinate;
	
	std::vector<node> nodeList;
	std::vector<blockLabel> blockLabelList;
	std::vector<edgeLineShape> lineList;
	std::vector<arcShape> arcList;
	
    std::ostringstream stringMouseXCoor, stringMouseYCoor, stringMousePixelX, stringMousePixelY;// THis is for debugging
    
	DECLARE_EVENT_TABLE();
};





#endif