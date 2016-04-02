#include <UI/geometryEditor2D.h>


geometryEditor2DPresentation::geometryEditor2DPresentation(wxWindow *par, const wxPoint &position, const wxSize &size) : wxPanel(par, wxID_ANY, position, size, wxBORDER_SIMPLE)
{
	wxStaticText *geometryBuilderName = new wxStaticText(this, wxID_ANY, "Model Builder", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
	geometryBuilderName->SetFont(wxFont(FONTSIZE, wxDEFAULT, wxNORMAL, wxNORMAL));
	int tempWidth, tempHeight;// This are intermediate variables
	
	
	this->GetSize(&tempWidth, &tempHeight);
	
	controller.setDrawingHeightAbstract(tempHeight - FONTSIZE - BMPBUTTONSIZE - BORDER); 
	controller.setDrawingWidthAbstract(tempWidth - 2 * BORDER);// The 20 is for a 10 pt border 
	
	drawingCanvas = new wxGLCanvas(this, wxID_ANY, 0, wxPoint(10, FONTSIZE + BMPBUTTONSIZE), wxSize(controller.getDrawingWidthAbstract(), controller.getDrawingHeightAbstract()), wxBORDER_DOUBLE | wxBORDER_RAISED);
	drawingContext = new wxGLContext(drawingCanvas);	
	
	drawingCanvas->SetCurrent();
	
	glClearColor(0, 0, 0, 0);
}




