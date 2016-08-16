#include <UI/openGLGeometry.h>
#include <string.h>

#include <math.h>

class tempXCoor;
class tempXCoor;
class tempXCoor;
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

	boundaryList.Add("<None>");
}


void geometryEditorCanvas::render()
{

	
    
    
}



void geometryEditorCanvas::updateProjection()
{
    // First, load the projection matrix and reset the view to a default view
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
    
    
    //Reset to modelview matrix
	glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
	
    /* This section will handle the translation (panning) and scaled (zooming). 
     * Needs to be called each time a draw occurs in order to update the placement of all the components */
    if(zoomFactor < 1e-9)
        zoomFactor = 1e-9;
    
    if(zoomFactor > 1e6)
        zoomFactor = 1e6;
        
    glScaled(zoomFactor / (canvasWidth / canvasHeight), zoomFactor, 1.0);
    glTranslated(-cameraX, -cameraY, 0.0);
	
    
}


void geometryEditorCanvas::drawGrid()
{
	updateProjection();
    
    glLineWidth(1.0);
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(1, 0x1C47);
    
    double cornerMinX = convertToXCoordinate(0);
    double cornerMinY = convertToYCoordinate(0);
    
    double cornerMaxX = convertToXCoordinate(canvasWidth);
    double cornerMaxY = convertToYCoordinate(canvasHeight);
    
    glBegin(GL_LINES);
    
        if(((cornerMaxX - cornerMinX) / gridStep + (cornerMinY - cornerMaxY) / gridStep < 200) && ((cornerMaxX - cornerMinX) / gridStep > 0) && ((cornerMinY - cornerMaxY) / gridStep > 0))
        {
            /* Create the grid for the vertical lines first */
            for(int i = cornerMinX / gridStep - 1; i < cornerMaxX / gridStep + 1; i++)
            {
                if(i % 5 == 0)
                    glColor3d(0.0, 0.0, 0.0);
                else
                    glColor3d(0.6, 0.6, 0.6);
                    
                glVertex2d(i * gridStep, cornerMinY);
                
                glVertex2d(i * gridStep, cornerMaxY);
            }
            
            /* Create the grid for the horizontal lines */
            for(int i = cornerMaxY / gridStep - 1; i < cornerMinY / gridStep + 1; i++)
            {
                if(i % 5 == 0)
                    glColor3d(0.0, 0.0, 0.0);
                else
                    glColor3d(0.6, 0.6, 0.6);
                    
                glVertex2d(cornerMinX, i * gridStep);
                glVertex2d(cornerMaxX, i * gridStep);
            }
        }
        
    glEnd();
    glDisable(GL_LINE_STIPPLE);
    
    /* Create the center axis */    
    glColor3d(0.0, 0.0, 0.0);
    glLineWidth(1.5);
    
    glBegin(GL_LINES);
        glVertex2d(0, cornerMinY);
        glVertex2d(0, cornerMaxY);
        
        glVertex2d(cornerMinX, 0);
        glVertex2d(cornerMaxX, 0);
    glEnd();
    
    
    glLineWidth(0.5);// Resets the line width back to the default
}



void geometryEditorCanvas::onKeyDown(wxKeyEvent &event)
{
	std::vector<int> deletednodes;
	
	
	if(event.GetKeyCode() != DEL_KEY)
	{
		if(event.GetKeyCode() == LETTER_W || event.GetKeyCode() == LETTER_w)
		{
			cameraY -= 0.1f;
		}
		else if(event.GetKeyCode() == LETTER_S || event.GetKeyCode() == LETTER_s)
		{
			cameraY += 0.1f;
		}	
		else if(event.GetKeyCode() == LETTER_A || event.GetKeyCode() == LETTER_a)
		{
			cameraX -= 0.1f;
		}
		else if(event.GetKeyCode() == LETTER_d || event.GetKeyCode() == LETTER_D)
		{	
			cameraX += 0.1f;
		}
	}
	else
	{
		if(nodeList.size() == 1)
		{
			nodeList.clear();
		}
		else
		{
			for(std::vector<node>::iterator nodeIterator = nodeList.begin(); nodeIterator != nodeList.end(); ++nodeIterator)
			{
				if(nodeIterator->getIsSelected())
				{
					nodeList.erase(nodeIterator);
					nodeIterator = nodeList.begin();
					if(firstSelectedNodeIndex != -1 && (nodeIterator->getCenterXPixel() == nodeList[firstSelectedNodeIndex].getCenterXPixel()) && (nodeIterator->getCenterYPixel() == nodeList[firstSelectedNodeIndex].getCenterYPixel()))
					{
						firstSelectedNodeIndex = -1;
					}
				}
			}
			
			if(nodeList.size() == 1 && nodeList[0].getIsSelected() == true)
			{
				nodeList.clear();
			}
				
		}
	}

    this->Refresh();// This will force the canvas to experience a redraw event
}



void geometryEditorCanvas::onMouseMove(wxMouseEvent &event)
{
    int dx = event.GetX() - mouseX;
    int dy = event.GetY() - mouseY;
    
	mouseX = event.GetX();
	mouseY = event.GetY();
	std::stringstream stringMouseXCoor, stringMouseYCoor, stringMousePixelX, stringMousePixelY;
	
	// Converts the mouse pointer into a cartesian graph position
	mouseGraphX = (((2.0 / canvasWidth) * (mouseX - canvasWidth / 2.0)) / zoomFactor) * (canvasWidth / canvasHeight);
	mouseGraphY = (-(2.0 / canvasHeight) * (mouseY - canvasHeight / 2.0)) / zoomFactor;
    
    stringMouseXCoor << std::fixed << setprecision(3) << mouseGraphX;
	stringMouseYCoor << std::fixed << setprecision(3) << mouseGraphY;
    
    stringMousePixelX << std::fixed << setprecision(1) << mouseX;
    stringMousePixelY << std::fixed << setprecision(1) << mouseY;
    
    if(event.ButtonIsDown(wxMOUSE_BTN_MIDDLE))
    {
        cameraX -= (2.0 / canvasWidth) * (dx / zoomFactor) * (canvasWidth / canvasHeight);
        cameraY += (2.0 / canvasHeight) * (dy / zoomFactor);
    }

    this->Refresh();
}



double geometryEditorCanvas::convertToXCoordinate(int xPixel)
{
//	return (Xcoeff * ((double)xPixel) - graphOffset);
    return (((2.0 / canvasWidth) * xPixel - 1) / zoomFactor * (canvasWidth / canvasHeight) + cameraX);
}


double geometryEditorCanvas::convertToXCoordinate(int xPixel, int cameraOffset)
{
	return (Xcoeff * ((double)xPixel - cameraOffset) - graphOffset);
}


double geometryEditorCanvas::convertToYCoordinate(int yPixel)
{
	return -((2.0 / canvasHeight) * yPixel - 1) / zoomFactor + cameraY;
}


double geometryEditorCanvas::convertToYCoordinate(int yPixel, int cameraOffset)
{
	return (Ycoeff* ((double)yPixel - cameraOffset) + graphOffset);
}


double geometryEditorCanvas::convertToXPixel(double XCoor)
{
	return ((1.0 + (XCoor - cameraX)) * zoomFactor / (canvasWidth / canvasHeight) + cameraX);
}


int geometryEditorCanvas::convertToXPixel(double XCoor, int cameraOffset)
{
	return (int)((XCoor + graphOffset) / Xcoeff) + cameraOffset;
}


double geometryEditorCanvas::convertToYPixel(double YCoor)
{
	return ((1.0 + (YCoor - cameraY) * zoomFactor) * canvasHeight / 2.0); // Due to there being errors in the double data type, a small offset of 3 needed to be introduced
}

int geometryEditorCanvas::convertToYPixel(double YCoor, int cameraOffset)
{
	return (int)((YCoor - graphOffset) / Ycoeff) + 3 + cameraOffset; // Due to there being errors in the double data type, a small offset of 3 needed to be introduced
}


void geometryEditorCanvas::convertPixelToCoor(double xPoint, double yPoint, int &xPixel, int &yPixel)
{
	xPixel = convertToXPixel(xPoint);
	
	yPixel = convertToYPixel(yPoint);
}


void geometryEditorCanvas::onGeometryPaint(wxPaintEvent &event)
{
	wxGLCanvas::SetCurrent(*geometryContext);// This will make sure the the openGL commands are routed to the wxGLCanvas object
	wxPaintDC dc(this);// This is required for drawing
	
    glMatrixMode(GL_MODELVIEW);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glDisable(GL_DEPTH_TEST);
    
	drawGrid();
    
	if(lineList.size() > 0)
	{
        updateProjection();
		for(int i = 0; i < lineList.size(); i++)
		{
			lineList[i].draw(nodeList[lineList[i].getFirstNodeIndex()].getCenterXPixel(), nodeList[lineList[i].getFirstNodeIndex()].getCenterYPixel(), nodeList[lineList[i].getSecondNodeIndex()].getCenterXPixel(), nodeList[lineList[i].getSecondNodeIndex()].getCenterYPixel());
		}
	}
	
	if(nodeList.size() > 0)
	{
        updateProjection();
		for(std::vector<node>::iterator nodeIterator = nodeList.begin(); nodeIterator != nodeList.end(); ++nodeIterator)
		{
			int tempX = 0;
			int tempY = 0;
			convertPixelToCoor(nodeIterator->getCenterXCoordinate(), nodeIterator->getCenterYCoordinate(), tempX, tempY);

			nodeIterator->setCenterXPixel(tempX);
			nodeIterator->setCenterYPixel(tempY);
		
			nodeIterator->draw();
		}
	}
	
	SwapBuffers();// Display the output
}


void geometryEditorCanvas::onResize(wxSizeEvent &event)
{
	canvasHeight = (double)this->GetSize().y;
	canvasWidth = (double)this->GetSize().x;
	
	this->Refresh();
}


void geometryEditorCanvas::toggleBlockListCreation()
{
	if(blockLabelCreationIsEnabled == false)
		blockLabelCreationIsEnabled = true;
	else
		blockLabelCreationIsEnabled = false;
}

void geometryEditorCanvas::onMouseWheel(wxMouseEvent &event)
{
    if(event.GetWheelRotation() != 0)
    {
   //     wxMessageBox("Wheel Rotated");
        
        cameraX += mouseGraphX;
        cameraY += mouseGraphY;
        
        if(event.GetWheelRotation() > 0)
            zoomFactor = zoomFactor * pow(1.2, -(event.GetWheelDelta()) / 150.0);
        else
            zoomFactor = zoomFactor * pow(1.2, (event.GetWheelDelta()) / 150.0);
        
        /* This will recalculate the new position of the mouse. Assuming that the mouse does not move at all during the process */
        mouseGraphX = (((2.0 / canvasWidth) * (mouseX - canvasWidth / 2.0)) / zoomFactor) * (canvasWidth / canvasHeight);
        mouseGraphY = (-(2.0 / canvasHeight) * (mouseY - canvasHeight / 2.0)) / zoomFactor;
        
        cameraX -= mouseGraphX;
        cameraY -= mouseGraphY;
    }
	
    if(event.MiddleDown() && event.Dragging())
    {
        wxMessageBox("It works");
    }
	
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
	bool nodeSelected = false;
	
	
	if(blockLabelCreationIsEnabled)
	{
		if(!(nodeList.size() >= 2 && (lineList.size() > 0 || arcList.size() > 0)))
			return;
	}
	else if(nodeList.size() == 0)
	{
		addNode(mouseGraphX, mouseGraphY, 0);
		this->Refresh();
		return;
	}
	
	for(int i = 0; i < lineList.size(); i++)
	{
		
	}
	
    /* This section will be for node handling */
	for(int i = 0; i < nodeList.size(); i++)
	{
		if((((mouseX - cameraX) >= nodeList[i].getCenterXPixel() - 5) && ((mouseX - cameraX) <= nodeList[i].getCenterXPixel() + 5) && ((mouseY - cameraY) <= nodeList[i].getCenterYPixel() + 5) && ((mouseY - cameraY) >=nodeList[i].getCenterYPixel() - 5)) && nodeSelected == false)
		{
			if(blockLabelCreationIsEnabled)
				return;
			else if(event.ShiftDown())
			{
				/*	This section will first check to see if any other shape is selected.
					If the shape is selected, then toggle the selection.
					As a last step, the function will then toggle select the selected node
				*/
				if(blockLabelList.size() > 0)
				{
					for(int j = 0; j < blockLabelList.size(); j++)
					{
						if(blockLabelList[j].getIsSelected())
							blockLabelList[j].toggleSelect();
					}
				}
				
				if(arcList.size() > 0)
				{
					for(int j = 0; j < arcList.size(); j++)
					{
						if(arcList[j].getIsSelected())
							arcList[j].toggleSelect();
					}
				}
				
				if(lineList.size() > 0)
				{
					for(int j = 0; j < lineList.size(); j++)
					{
						if(lineList[j].getIsSelected())
							lineList[j].toggleSelect();
					}
				}
				
				nodeList[i].toggleSelect();
				this->Refresh();
				return;
			}
			else if(firstSelectedNodeIndex == -1)
			{
				for (int j = 0; j < nodeList.size(); j++)
				{
					if(nodeList[j].getIsSelected())
						nodeList[j].toggleSelect();
				}
				nodeList[i].toggleSelect();
				firstSelectedNodeIndex = i;
				this->Refresh();
				return;
			}
			else
			{
				if(lineCreationFlag)
				{
					
					double tempXCoor, tempYCoor;
					for(int k = 0; k < lineList.size(); k++)
					{
						if(getIntersection(firstSelectedNodeIndex, i, k, tempXCoor, tempYCoor) == true)
						{
							addNode(tempXCoor, tempYCoor, 0.01);
						}
					}
					
					addLineSegment(firstSelectedNodeIndex, nodeList[i].getNodeIndex(), NULL);
				}
				else
				{
					/* 
						This section of the code will calculate many features that make up the arc such as the arc Legnth.
						The add arcSegment will calculate anything needed for intercestions
					*/
					arcShape arcSegment;
					
					/* First, we will create a dialog box so that some basic propeties of the arc can be set by the user */
					wxDialog *arcSegmentDlg = new wxDialog(NULL, wxID_ANY, "Arc Segment Dialog", wxDefaultPosition, wxSize(269, 205));
					wxPanel *dialogPanel = new wxPanel(arcSegmentDlg);
					wxButton *buttonOk = new wxButton(dialogPanel, wxID_OK, "Ok", wxPoint(101, 165), wxSize(75, 23));
					wxButton *buttonCancel = new wxButton(dialogPanel, wxID_CANCEL, "Cancel", wxPoint(182, 165), wxSize(75, 23));
					
					wxFont *font = new wxFont(8.5, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
					
					wxStaticText *arcAngleText = new wxStaticText(dialogPanel, wxID_ANY, "Arc Angle (deg):", wxPoint(12, 38), wxSize(80,13));
					arcAngleText->SetFont(*font);
					
					wxStaticText *maxSegmentText = new wxStaticText(dialogPanel, wxID_ANY, "Max Segment:", wxPoint(12, 83), wxSize(72,13));
					maxSegmentText->SetFont(*font);
					
					wxStaticText *boundaryText = new wxStaticText(dialogPanel, wxID_ANY, "Boundary", wxPoint(12, 125), wxSize(52,13));
					boundaryText->SetFont(*font);
					
					wxTextCtrl *arcAngle = new wxTextCtrl(dialogPanel, wxID_ANY, "180", wxPoint(101, 35), wxSize(156, 20));
					wxTextCtrl *maxSegment = new wxTextCtrl(dialogPanel, wxID_ANY, "3", wxPoint(101, 80), wxSize(156, 20));

					wxComboBox *boundaryComboBox = new wxComboBox(dialogPanel, wxID_ANY, "", wxPoint(101, 122), wxSize(156, 21), boundaryList);
					
					if(arcSegmentDlg->ShowModal() == wxID_OK)
					{
						/* If the user clicked on ok to idicate they are done, we will then set the properties to an arc segment and add the segment to the geometry */
						double arcAngleVal = 0.0;
						double maxSegmentVal = 0.0;
						int index = boundaryComboBox->GetSelection();
						wxString test = boundaryList.Item(index);
						
						arcAngle->GetValue().ToDouble(&arcAngleVal);
						arcSegment.setArcLength(arcAngleVal);// This needs to be changed to reflect that it is really the arc angle and not length
						
						maxSegment->GetValue().ToDouble(&maxSegmentVal);
						arcSegment.setMaxSideLength(maxSegmentVal);
						
						//arcSegment.setBoundaryMarker(test);
						arcSegment.setBoundaryMarker(test);
						
						arcSegment.setFirstNodeIndex(firstSelectedNodeIndex);
						arcSegment.setSecondNodeIndex(nodeList[i].getNodeIndex());
						
						addArcSegment(arcSegment);
					}
				}
				
				nodeList[firstSelectedNodeIndex].toggleSelect();
				firstSelectedNodeIndex = -1;
				this->Refresh();
				return;
			}
		}			
	}
	
	addNode(mouseGraphX, mouseGraphY, 0);
	this->Refresh();
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