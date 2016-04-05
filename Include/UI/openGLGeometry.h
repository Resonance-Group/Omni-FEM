#ifndef OPENGLGEOMETRY_H_
#define OPENGLGEOMETRY_H_

#include <wx/wx.h>
#include <wx/glcanvas.h>
#include <freeglut.h>
#include <gl.h>
#include <glu.h>

#define COLOR_MODE_CYAN 0
#define COLOR_MODE_MULTI 1


class geometryEditorCanvas : public wxGLCanvas
{
public:
	//! This would be used for initilizeing the openGL settings
	/*! 
		The code found in this constructor is used to initilize the openGL settings.
		It is also initlizing wxWidgets so that OpenGL commands can be used
	*/
	geometryEditorCanvas(wxWindow *par, const wxPoint &position, const wxSize &size);
	
	int colormode = COLOR_MODE_MULTI;
	
private:
	void onGeometryPaint(wxPaintEvent &event);
	
	void render();
	
	void onResize(wxSizeEvent &event);
	
	wxGLContext *geometryContext;
	
	DECLARE_EVENT_TABLE();
};


enum ViewPortMode
{
	VIEWPORT_MODE_FULL,
	VIEWPORT_MODE_HALF_CENTER,
	VIEWPORT_MODE_HALF_TOP,
	VIEWPORT_MODE_QUAD,
	VIEWPORT_MODE_RADAR
};

#endif