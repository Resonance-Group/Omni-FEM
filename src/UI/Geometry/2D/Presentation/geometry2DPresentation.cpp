#include <UI/geometryEditor2D.h>


geometryEditor2DPresentation::geometryEditor2DPresentation(wxWindow *par, const wxPoint &position, const wxSize &size) : wxPanel(par, wxID_ANY, position, size, wxBORDER_SIMPLE)
{
	wxStaticText *geometryBuilderName = new wxStaticText(this, wxID_ANY, "Model Builder", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
	geometryBuilderName->SetFont(wxFont(12, wxDEFAULT, wxNORMAL, wxNORMAL));
	
	createOpenGLCanvas();
}



void geometryEditor2DPresentation::createOpenGLCanvas()
{
//	drawingCanvas = new wxGLCanvas(this, wxID_ANY, 0, wxDefaultPosition, wxDefaultSize);
//	drawingContext = new wxGLContext(drawingCanvas);
}

