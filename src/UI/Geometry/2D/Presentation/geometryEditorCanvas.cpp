#include <UI/openGLGeometry.h>
#include <string.h>

#include <math.h>

using namespace std;

geometryEditorCanvas::geometryEditorCanvas(wxWindow *par, const wxPoint &position, const wxSize &size) : wxGLCanvas(par, wxID_ANY, NULL, position, size, wxBORDER_DOUBLE | wxBORDER_RAISED)
{
 //   debugCoordinate = new wxStaticText(this, wxID_ANY, "None", wxPoint(0, 10));
 //   debugPixelCoordinate = new wxStaticText(this, wxID_ANY, "None");
    // At startup, the canvas size is initially 613x241 pixels
    debugCoordinate = new wxGLString("None");
    debugPixelCoordinate = new wxGLString("none");
    
    
    
    this->SetLabel("none");
    
	geometryContext = new wxGLContext(this);
	wxGLCanvas::SetCurrent(*geometryContext);
	canvasHeight = (double)this->GetSize().y;
	canvasWidth = (double)this->GetSize().x;
	
	coordinateFactorWidth = canvasWidth / (double)factor;
	coordinateFactorHeight = canvasHeight / (double)factor;
	
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
	//Reset to modelview matrix
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
    glPushMatrix();
	
	glTranslatef(canvasWidth / 2.0f, canvasHeight / 2.0f, 0.0f);
	
    //Red quad
    glBegin( GL_QUADS );
        glColor3f( 0.f, 0.f, 0.f );
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


void geometryEditorCanvas::drawGrid()
{
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
    glPushMatrix();
	
//	glTranslatef(canvasWidth / 2.0f, canvasHeight / 2.0f, 0.0f);
	
	for(int heightLoop = -10; heightLoop <= 10; heightLoop++)
	{
		
		for(int widthLoop = -10; widthLoop <= 10; widthLoop++)
		{
			int tempYPixel = convertToYPixel((double)heightLoop);
			int tempXPixel = convertToXPixel((double)widthLoop);
			glBegin(GL_POINTS);
				glColor3f( 0.f, 0.f, 0.f );
				glVertex2i(tempXPixel, tempYPixel);
			glEnd();
		}
	}
}



void geometryEditorCanvas::onKeyDown(wxKeyEvent &event)
{
    if(event.GetKeyCode() == LETTER_W || event.GetKeyCode() == LETTER_w)
    {
        cameraY -= 1.0f;
    }
	else if(event.GetKeyCode() == LETTER_S || event.GetKeyCode() == LETTER_s)
	{
		cameraY += 1.0f;
	}	
	else if(event.GetKeyCode() == LETTER_A || event.GetKeyCode() == LETTER_a)
	{
		cameraX -= 1.0f;
	}
	else if(event.GetKeyCode() == LETTER_d || event.GetKeyCode() == LETTER_D)
	{	
		cameraX += 1.0f;
	}
    
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glLoadIdentity();
	
	glTranslatef(cameraX, cameraY, 0.0f);
	glPushMatrix();
	
    this->Refresh();// This will force the canvas to experience a redraw event
}



void geometryEditorCanvas::onMouseMove(wxMouseEvent &event)
{
	mouseX = event.GetX();
	mouseY = event.GetY();
	std::stringstream stringMouseXCoor, stringMouseYCoor, stringMousePixelX, stringMousePixelY;
	
	// Converts the mouse pointer into a cartesian graph position
	mouseGraphX = convertToXCoordinate((double)mouseX);
	mouseGraphY = convertToYCoordinate((double)mouseY);
    
    stringMouseXCoor << std::fixed << setprecision(3) << mouseGraphX;
	stringMouseYCoor << std::fixed << setprecision(3) << mouseGraphY;
    
    stringMousePixelX << std::fixed << setprecision(1) << mouseX;
    stringMousePixelY << std::fixed << setprecision(1) << mouseY;
    
 //   debugPixelCoordinate->SetLabel(stringMousePixelX.str() + " " + stringMousePixelY.str());
 //   debugCoordinate->SetLabel(stringMouseXCoor.str() + " " + stringMouseYCoor.str());
  //  this->Refresh();

}



double geometryEditorCanvas::convertToXCoordinate(int xPixel)
{
	return (Xcoeff * ((double)xPixel - cameraX) - graphOffset);
}



double geometryEditorCanvas::convertToYCoordinate(int yPixel)
{
	return (Ycoeff* ((double)yPixel - cameraY) + graphOffset);
}



int geometryEditorCanvas::convertToXPixel(double XCoor)
{
	return (int)((XCoor + graphOffset) / Xcoeff) + cameraX;
}


int geometryEditorCanvas::convertToYPixel(double YCoor)
{
	return (int)((YCoor - graphOffset) / Ycoeff) + 3 + cameraY; // Due to there being errors in the double data type, a small offset of 3 needed to be introduced
}



void geometryEditorCanvas::onGeometryPaint(wxPaintEvent &event)
{
	wxGLCanvas::SetCurrent(*geometryContext);// This will make sure the the openGL commands are routed to the wxGLCanvas object
	wxPaintDC dc(this);// This is required for drawing
	
    glClear(GL_COLOR_BUFFER_BIT);
	drawGrid();
	
	render();
	SwapBuffers();// Display the output
}


void geometryEditorCanvas::onResize(wxSizeEvent &event)
{
	canvasHeight = (double)this->GetSize().y;
	canvasWidth = (double)this->GetSize().x;
	
	this->Refresh();
}



void geometryEditorCanvas::onMouseWheel(wxMouseEvent &event)
{
	glMatrixMode(GL_MODELVIEW);
//	glPopMatrix();
//	glLoadIdentity();
	
	if(event.GetWheelRotation() > 0)
	{
		glOrtho(0.0, canvasWidth * zoomFactor, canvasHeight * zoomFactor, 0.0, 1.0, -1.0);
		//glScaled(zoomFactor, zoomFactor, 0.0d);
		totalZoom *= zoomFactor;
	}
	else if(event.GetWheelRotation() < 0)
	{
		glOrtho(0.0, (double)canvasWidth / zoomFactor, (double)canvasHeight / zoomFactor, 0.0, 1.0, -1.0);
		//glScaled(1.0d / zoomFactor, 1.0d / zoomFactor, 0.0d);
		totalZoom /= zoomFactor;
	}
	
//	glPushMatrix();
	
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



void geometryEditorCanvas::onMouseLeftDown(wxMouseEvent &event)
{
	wxGLCanvas::SetCurrent(*geometryContext);
	std::stringstream stringMouseXCoor, stringMouseYCoor, stringMousePixelX, stringMousePixelY;
	

    
    stringMouseXCoor << std::fixed << setprecision(3) << mouseGraphX;
	stringMouseYCoor << std::fixed << setprecision(3) << mouseGraphY;
	
	wxMessageBox(stringMouseXCoor.str() + " " + stringMouseYCoor.str());

//	testPoint = new nodePoint(mouseGraphX, mouseGraphY, this);

//	this->Refresh();
}

wxBEGIN_EVENT_TABLE(geometryEditorCanvas, wxGLCanvas)
	EVT_PAINT(geometryEditorCanvas::onGeometryPaint)
	EVT_SIZE(geometryEditorCanvas::onResize)
    EVT_KEY_DOWN(geometryEditorCanvas::onKeyDown)
	EVT_MOUSEWHEEL(geometryEditorCanvas::onMouseWheel)
	EVT_ENTER_WINDOW(geometryEditorCanvas::onEnterWindow)
	EVT_LEAVE_WINDOW(geometryEditorCanvas::onLeavingWindow)
	EVT_MOTION(geometryEditorCanvas::onMouseMove)
	EVT_LEFT_DOWN(geometryEditorCanvas::onMouseLeftDown)
wxEND_EVENT_TABLE()

//nodePoint::drawnodePoint(GLdouble xcoordinate, GL)