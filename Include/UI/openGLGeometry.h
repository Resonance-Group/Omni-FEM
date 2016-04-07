#ifndef OPENGLGEOMETRY_H_
#define OPENGLGEOMETRY_H_

#include <wx/wx.h>
#include <wx/glcanvas.h>
#include <UI/common.h>
#include <freeglut.h>
#include <gl.h>
#include <glu.h>


class LTexture
{
public:
	LTexture();
	~LTexture();
	
	bool loadTexturesFromPixels32(GLuint *pixels, GLuint width, GLuint height);
	void freeTexture();
	void render(GLfloat x, GLfloat y);
	
};


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
	/************
	* Variables *
	*************/
private:	
	
    //! This is the context which will be associated to the class
	wxGLContext *geometryContext;
	
	float canvasWidth = 0;
	float canvasHeight = 0;
	float zoomX = 1;
	float zoomY = 1;
	
	int mouseX;
	int mouseY;
	
	GLfloat cameraX = 0.0f, cameraY = 0.0f;
	
	DECLARE_EVENT_TABLE();
};


/*! \class nodePoint
	\brief This class is used to create a node
*/
class nodePoint
{
public:
	nodePoint();
	
	//! This function will draw the node with the center at xcoordinate and ycoordinate
	void drawnodePoint(GLfloat xcoordinate, GLfloat ycoordinate);
	
	/************
	* Variables *
	*************/
};


#endif