#include <UI/geometryEditor2D.h>


geometryEditorCanvas::geometryEditorCanvas(wxWindow *par, const wxPoint &position, const wxSize &size) : wxGLCanvas(par, wxID_ANY, NULL, position, size, wxBORDER_DOUBLE | wxBORDER_RAISED)
{

}



void geometryEditorCanvas::onGeometryPaint(wxPaintEvent &event)
{
	wxPaintDC dc(this);
	
	const wxSize canvasSize = GetSize();
	canvasContext = new geometryEditorContext(this);
	
	glViewport(0, 0, canvasSize.x, canvasSize.y);
	
	canvasContext->renderGeometry();
	
	SwapBuffers();
	
//	wxMessageBox("test");
}



wxBEGIN_EVENT_TABLE(geometryEditorCanvas, wxGLCanvas)
	EVT_PAINT(geometryEditorCanvas::onGeometryPaint)
wxEND_EVENT_TABLE()