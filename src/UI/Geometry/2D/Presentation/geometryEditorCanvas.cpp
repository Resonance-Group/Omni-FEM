#include <UI/geometryEditor2D.h>


geometryEditorCanvas::geometryEditorCanvas(wxWindow *par, const wxPoint &position, const wxSize &size) : wxGLCanvas(par, wxID_ANY, NULL, position, size, wxBORDER_DOUBLE | wxBORDER_RAISED)
{

}


void geometryEditorCanvas::render()
{
	glClear(GL_COLOR_BUFFER_BIT);
	
	glBegin(GL_QUADS);
		glVertex2f(-0.5f, -0.5f);
		glVertex2f(0.5f, -0.5f);
		glVertex2f(0.5f, 0.5f);
		glVertex2f(-0.5f, 0.5f);
	glEnd();
}


/* This function gets called over and over */
void geometryEditorCanvas::onGeometryPaint(wxPaintEvent &event)
{
	wxPaintDC dc(this);
	
	const wxSize canvasSize = GetSize();// This will get the current size of the drawing canvas
	canvasContext = new geometryEditorContext(this);// initilize the context
	
	glViewport(0, 0, canvasSize.x, canvasSize.y);// Set the viewport to see the rendering
	
//	canvasContext->renderGeometry();// Render the geometry
	render();
	
	SwapBuffers();// Display the output
	
//	wxMessageBox("test");
}



wxBEGIN_EVENT_TABLE(geometryEditorCanvas, wxGLCanvas)
	EVT_PAINT(geometryEditorCanvas::onGeometryPaint)
wxEND_EVENT_TABLE()