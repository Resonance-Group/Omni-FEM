#include <UI/geometryEditor2D.h>


geometryEditor2DPresentation::geometryEditor2DPresentation(wxWindow *par, const wxPoint &position, const wxSize &size) : wxPanel(par, wxID_ANY, position, size, wxBORDER_SIMPLE)
{
	wxStaticText *geometryBuilderName = new wxStaticText(this, wxID_ANY, "Model Builder", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
	geometryBuilderName->SetFont(wxFont(FONTSIZE, wxDEFAULT, wxNORMAL, wxNORMAL));
	int tempHeight, tempWidth;
	
	this->GetSize(&tempWidth, &tempHeight);
	
	controller.setDrawingHeightAbstract(tempHeight - FONTSIZE - BMPBUTTONSIZE - BORDER); 
	controller.setDrawingWidthAbstract(tempWidth - 2 * BORDER);// The 20 is for a 10 pt border 
	
	drawingCanvas = new geometryEditorCanvas(this, wxPoint(10, FONTSIZE + BMPBUTTONSIZE), wxSize(controller.getDrawingWidthAbstract(), controller.getDrawingHeightAbstract()));
	
}


wxBEGIN_EVENT_TABLE(geometryEditor2DPresentation, wxPanel)

wxEND_EVENT_TABLE()