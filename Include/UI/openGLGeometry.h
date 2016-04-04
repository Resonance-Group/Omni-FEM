#ifndef OPENGLGEOMETRY_H_
#define OPENGLGEOMETRY_H_

#include <wx/wx.h>
#include <wx/glcanvas.h>
#include <freeglut.h>
#include <gl.h>
#include <glu.h>

#define COLOR_MODE_CYAN 0
#define COLOR_MODE_MULTI 1


class geometryEditorContext : public wxGLContext
{
public:
	geometryEditorContext(wxGLCanvas *canvas);
	
};



class geometryEditorCanvas : public wxGLCanvas
{
public:
	//! This would be used for initilizeing the openGL settings
	geometryEditorCanvas(wxWindow *par, const wxPoint &position, const wxSize &size);
	
	int colormode = COLOR_MODE_MULTI;
	
private:
	void onGeometryPaint(wxPaintEvent &event);
	
	geometryEditorContext *canvasContext;
	
	void render();
	
	void onResize(wxSizeEvent &event);
	
	DECLARE_EVENT_TABLE();
};


#endif