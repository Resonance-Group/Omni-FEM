#include <UI/openGLGeometry.h>
#include <string.h>

geometryEditorCanvas::geometryEditorCanvas(wxWindow *par, const wxPoint &position, const wxSize &size) : wxGLCanvas(par, wxID_ANY, NULL, position, size, wxBORDER_DOUBLE | wxBORDER_RAISED)
{
	geometryContext = new wxGLContext(this);
	wxGLCanvas::SetCurrent(*geometryContext);
	canvasHeight = (float)this->GetSize().y;
	canvasWidth = (float)this->GetSize().x;
	
	glViewport(0, 0, canvasWidth, canvasHeight);// Set the viewport to see the rendering
	
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);// This will control the color of the background for the drawing canvas

	glMatrixMode(GL_MODELVIEW);// The matrix mode specifies which matrix stack is the target for matrix operations
	glLoadIdentity();// Initial value
//	glTranslated((float)this->GetSize().x / 2.0f, (float)this->GetSize().y / 2.0f, 0.0f);// This will move the camera to the center of the screen
    
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	/*	
		This will setup the screen such that the x value will extend from the left (x = 0) to the right (x = canvas->GetSize().x)
		As for the y value, it will extend from the top (y = 0) to the bottom (y = canvas->GetSize().y)
		By default, the screen is the the unit square. This command changes that 
	*/
	glOrtho(0.0, canvasWidth, canvasHeight, 0.0, 1.0, -1.0);
	
	/* Ensure that there are no errors */
	GLenum error = glGetError();
	if(error != GL_NO_ERROR)
	{
	//	wxMessageBox("Error - " + gluErrorString(error));
		return;
	}	
}


void geometryEditorCanvas::render()
{
	// Clears the color buffer
	glClear(GL_COLOR_BUFFER_BIT);
	
	//Reset to modelview matrix
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	
    glPushMatrix();
	
	glTranslatef(canvasWidth / 2.0f, canvasHeight / 2.0f, 0.0f);
	
    //Red quad
    glBegin( GL_QUADS );
        glColor3f( 1.f, 1.f, 1.f );
        glVertex2f( -canvasWidth / 4.f, -canvasHeight / 4.f );
        glVertex2f(  canvasWidth / 4.f, -canvasHeight / 4.f );
        glVertex2f(  canvasWidth / 4.f,  canvasHeight / 4.f );
        glVertex2f( -canvasWidth / 4.f,  canvasHeight / 4.f );
    glEnd();

    //Move to the right of the screen
    glTranslatef( canvasWidth, 0.f, 0.f );

    //Green quad
    glBegin( GL_QUADS );
        glColor3f( 0.f, 1.f, 0.f );
        glVertex2f( -canvasWidth / 4.f, -canvasHeight / 4.f );
        glVertex2f(  canvasWidth / 4.f, -canvasHeight / 4.f );
        glVertex2f(  canvasWidth / 4.f,  canvasHeight / 4.f );
        glVertex2f( -canvasWidth / 4.f,  canvasHeight / 4.f );
    glEnd();

    //Move to the lower right of the screen
    glTranslatef( 0.f, canvasHeight, 0.f );

    //Blue quad
    glBegin( GL_QUADS );
        glColor3f( 0.f, 0.f, 1.f );
        glVertex2f( -canvasWidth / 4.f, -canvasHeight / 4.f );
        glVertex2f(  canvasWidth / 4.f, -canvasHeight / 4.f );
        glVertex2f(  canvasWidth / 4.f,  canvasHeight / 4.f );
        glVertex2f( -canvasWidth / 4.f,  canvasHeight / 4.f );
    glEnd();

    //Move below the screen
    glTranslatef( -canvasWidth, 0.f, 0.f );

    //Yellow quad
    glBegin( GL_QUADS );
        glColor3f( 1.f, 1.f, 0.f );
        glVertex2f( -canvasWidth / 4.f, -canvasHeight / 4.f );
        glVertex2f(  canvasWidth / 4.f, -canvasHeight / 4.f );
        glVertex2f(  canvasWidth / 4.f,  canvasHeight / 4.f );
        glVertex2f( -canvasWidth / 4.f,  canvasHeight / 4.f );
    glEnd();
    
}


void geometryEditorCanvas::onKeyDown(wxKeyEvent &event)
{
    if(event.GetKeyCode() == LETTER_W || event.GetKeyCode() == LETTER_w)
    {
        cameraY -= 16.0f;
    }
	else if(event.GetKeyCode() == LETTER_S || event.GetKeyCode() == LETTER_s)
	{
		cameraY += 16.0f;
	}	
	else if(event.GetKeyCode() == LETTER_A || event.GetKeyCode() == LETTER_a)
	{
		cameraX -= 16.0f;
	}
	else if(event.GetKeyCode() == LETTER_d || event.GetKeyCode() == LETTER_D)
	{
		cameraX += 16.0f;
	}
    
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glLoadIdentity();
	
	glTranslated(cameraX, cameraY, 0.0f);
	glPushMatrix();
	
    this->Refresh();// This will force the canvas to experience a redraw event
}


void geometryEditorCanvas::onMouseMove(wxMouseEvent &event)
{
	mouseX = event.GetX();
	mouseY = event.GetY();
}


void geometryEditorCanvas::onGeometryPaint(wxPaintEvent &event)
{
	wxGLCanvas::SetCurrent(*geometryContext);// This will make sure the the openGL commands are routed to the wxGLCanvas object
	wxPaintDC dc(this);// This is required for drawing
	
	render();
	
	SwapBuffers();// Display the output
}


void geometryEditorCanvas::onResize(wxSizeEvent &event)
{
//	wxMessageBox("hello");
}



void geometryEditorCanvas::onMouseWheel(wxMouseEvent &event)
{
	if(event.GetWheelRotation() > 0)
	{
		zoomX += 1.5f;
		zoomY += 1.5f;
	}
	else if(event.GetWheelRotation() < 0)
	{
		zoomX -= 1.5f;
		zoomY -= 1.5f;
	}
	
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glLoadIdentity();
	
	glScalef(zoomX, zoomY, 0.0f);
	glPushMatrix();
	
    this->Refresh();// This will force the canvas to experience a redraw event
}


void geometryEditorCanvas::onEnterWindow(wxMouseEvent &event)
{
	this->SetFocus();
}



void geometryEditorCanvas::onLeavingWindow(wxMouseEvent &event)
{
	this->GetParent()->SetFocus();
}

wxBEGIN_EVENT_TABLE(geometryEditorCanvas, wxGLCanvas)
	EVT_PAINT(geometryEditorCanvas::onGeometryPaint)
	EVT_SIZE(geometryEditorCanvas::onResize)
    EVT_KEY_DOWN(geometryEditorCanvas::onKeyDown)
//	EVT_MOUSEWHEEL(geometryEditorCanvas::onMouseWheel)
	EVT_ENTER_WINDOW(geometryEditorCanvas::onEnterWindow)
	EVT_LEAVE_WINDOW(geometryEditorCanvas::onLeavingWindow)
	EVT_MOTION(geometryEditorCanvas::onMouseMove)
wxEND_EVENT_TABLE()