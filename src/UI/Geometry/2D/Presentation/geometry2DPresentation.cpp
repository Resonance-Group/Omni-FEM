#include <UI/geometryEditor2D.h>


geometryEditor2DPresentation::geometryEditor2DPresentation(wxWindow *par, const wxPoint &position, const wxSize &size) : wxPanel(par, wxID_ANY, position, size, wxBORDER_SIMPLE)
{
	wxStaticText *geometryBuilderName = new wxStaticText(this, wxID_ANY, "Model Builder", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
	geometryBuilderName->SetFont(wxFont(FONTSIZE, wxDEFAULT, wxNORMAL, wxNORMAL));
	int tempWidth, tempHeight;// This are intermediate variables
	int argc;
	char* args[9];
	
	this->GetSize(&tempWidth, &tempHeight);
	
	controller.setDrawingHeightAbstract(tempHeight - FONTSIZE - BMPBUTTONSIZE - BORDER); 
	controller.setDrawingWidthAbstract(tempWidth - 2 * BORDER);// The 20 is for a 10 pt border 
	
//	drawingCanvas = new wxGLCanvas(this, wxID_ANY, 0, wxPoint(10, FONTSIZE + BMPBUTTONSIZE), wxSize(controller.getDrawingWidthAbstract(), controller.getDrawingHeightAbstract()), wxBORDER_DOUBLE | wxBORDER_RAISED);
	drawingContext = new wxGLContext(drawingCanvas = new wxGLCanvas(this, wxID_ANY, 0, wxPoint(10, FONTSIZE + BMPBUTTONSIZE), wxSize(controller.getDrawingWidthAbstract(), controller.getDrawingHeightAbstract()), wxBORDER_DOUBLE | wxBORDER_RAISED));	
	

	
//	glClearColor(1, 0, 0, 0);

}



void geometryEditor2DPresentation::render()
{
	drawingCanvas->SetCurrent(drawingCanvas);

//	glutInit(&argc, args);
//	glutInitContextVersion(2, 1);
//	glutInitDisplayMode(GLUT_DOUBLE);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glClearColor(0.f, 0.f, 0.f, 1.f);
	
	GLenum error = glGetError();
	if(error != GL_NO_ERROR)
	{
	//	wxMessageBox("Error - " + gluErrorString(error));
		return;
	}

	glClear(GL_COLOR_BUFFER_BIT);
	
	glBegin(GL_QUADS);
		glVertex2f(-0.5f, -0.5f);
		glVertex2f(0.5f, -0.5f);
		glVertex2f(0.5f, 0.5f);
		glVertex2f(-0.5f, 0.5f);
	glEnd();
	
	drawingCanvas->SwapBuffers();
}
