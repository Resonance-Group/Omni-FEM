#include <UI/openGLGeometry.h>
#include <string.h>

#include <math.h>

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
	glTranslated((float)this->GetSize().x / 2.0f, (float)this->GetSize().y / 2.0f, 0.0f);// This will move the camera to the center of the screen
    
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	/*	
		This will setup the screen such that the x value will extend from the left (x = 0) to the right (x = canvas->GetSize().x)
		As for the y value, it will extend from the top (y = 0) to the bottom (y = canvas->GetSize().y)
		By default, the screen is the the unit square. This command changes that 
	*/
//	glOrtho(0.0, canvasWidth, canvasHeight, 0.0, 1.0, -1.0);
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
	/* Ensure that there are no errors */
	GLenum error = glGetError();
	if(error != GL_NO_ERROR)
	{
	//	wxMessageBox("Error - " + gluErrorString(error));
		return;
	}

	boundaryList.Add("<None>");
    glMatrixMode(GL_MODELVIEW);
}



void geometryEditorCanvas::updateProjection()
{
 //   glPopMatrix();
    // First, load the projection matrix and reset the view to a default view
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
 //   glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
 //   glOrtho(0.0, canvasWidth, canvasHeight, 0.0, 0.0, 0.0);
    
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
	
//    glPushMatrix();
}


void geometryEditorCanvas::drawGrid()
{
	updateProjection();
    
    glLineWidth(1.0);
    glEnable(GL_LINE_STIPPLE);
    /* 
     * The binary form is able to display the concept of glLineStipple for 
     * new users better then the Hex form. Although, the function is able to accept Hex
     * For an idea of how glLineStipple work, refer to the following link
     * http://images.slideplayer.com/16/4964597/slides/slide_9.jpg
     * 
     */ 
    glLineStipple(1, 0b0000100001000010);
    
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
	
	if(event.GetKeyCode() == DEL_KEY)
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
					if(firstSelectedNodeIndex != -1 && (nodeIterator->getCenterXCoordinate() == nodeList[firstSelectedNodeIndex].getCenterXCoordinate()) && (nodeIterator->getCenterYCoordinate() == nodeList[firstSelectedNodeIndex].getCenterYCoordinate()))
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
	
	
	// Converts the mouse pointer into a cartesian graph position
	mouseGraphX = (((2.0 / canvasWidth) * (mouseX - canvasWidth / 2.0)) / zoomFactor) * (canvasWidth / canvasHeight) + cameraX;
	mouseGraphY = (-(2.0 / canvasHeight) * (mouseY - canvasHeight / 2.0)) / zoomFactor + cameraY;
  
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
//    return (((2.0 / canvasWidth) * xPixel - 1) / zoomFactor * (canvasWidth / canvasHeight) + cameraX);
    return (((2.0 / canvasWidth) * ((double)xPixel - canvasWidth / 2.0)) / zoomFactor) * (canvasWidth / canvasHeight) + cameraX;
}




double geometryEditorCanvas::convertToYCoordinate(int yPixel)
{
//	return -((2.0 / canvasHeight) * yPixel - 1) / zoomFactor + cameraY;
    return (-(2.0 / canvasHeight) * ((double)yPixel - canvasHeight / 2.0)) / zoomFactor + cameraY;
}



void geometryEditorCanvas::onGeometryPaint(wxPaintEvent &event)
{
	wxGLCanvas::SetCurrent(*geometryContext);// This will make sure the the openGL commands are routed to the wxGLCanvas object
	wxPaintDC dc(this);// This is required for drawing
	
    glMatrixMode(GL_MODELVIEW);
    glClear(GL_COLOR_BUFFER_BIT);
    
 //   glDisable(GL_DEPTH_TEST);
    updateProjection();
    drawGrid();
    glMatrixMode(GL_MODELVIEW);
	if(lineList.size() > 0)
	{
   //     updateProjection();
		for(int i = 0; i < lineList.size(); i++)
		{
            // Look into passing the nodeList vector by reference to the draw function and doing this in the draw function
			lineList[i].draw(nodeList[lineList[i].getFirstNodeIndex()].getCenterXCoordinate(), nodeList[lineList[i].getFirstNodeIndex()].getCenterYCoordinate(), nodeList[lineList[i].getSecondNodeIndex()].getCenterXCoordinate(), nodeList[lineList[i].getSecondNodeIndex()].getCenterYCoordinate());
		}
	}
	
    if(arcList.size() > 0)
    {
        for(std::vector<arcShape>::iterator arcIterator = arcList.begin(); arcIterator != arcList.end(); ++arcIterator)
        {
            arcIterator->draw();
        }
    }
    
	if(nodeList.size() > 0)
	{
  //      updateProjection();
		for(std::vector<node>::iterator nodeIterator = nodeList.begin(); nodeIterator != nodeList.end(); ++nodeIterator)
		{
            /* Interestingly, the function does not have to convert the cartesian coordinates into pixels and draw
             * The reason for this is unknown. 
             */ 
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
    double tempMouseX = event.GetX();
    double tempMouseY = event.GetY();
    
    if(event.GetWheelRotation() != 0)
    {
        double temp1X, temp2Y;
        
        temp1X = (((2.0 / canvasWidth) * (event.GetX() - canvasWidth / 2.0)) / zoomFactor) * (canvasWidth / canvasHeight);
        temp2Y = (-(2.0 / canvasHeight) * (event.GetY() - canvasHeight / 2.0)) / zoomFactor;
        
        cameraX += temp1X;
        cameraY += temp2Y;
        
        if(event.GetWheelRotation() > 0)
            zoomFactor = zoomFactor * pow(1.2, -(event.GetWheelDelta()) / 150.0);
        else
            zoomFactor = zoomFactor * pow(1.2, (event.GetWheelDelta()) / 150.0);
        
        /* This will recalculate the new position of the mouse. Assuming that the mouse does not move at all during the process
         * This also enables the feature where the zoom will zoom in/out at the position of the mouse */
        temp1X = (((2.0 / canvasWidth) * (event.GetX() - canvasWidth / 2.0)) / zoomFactor) * (canvasWidth / canvasHeight);
        temp2Y = (-(2.0 / canvasHeight) * (event.GetY() - canvasHeight / 2.0)) / zoomFactor;
        
        cameraX -= temp1X;
        cameraY -= temp2Y;
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
        double temp1 = convertToXCoordinate(mouseX);
        double temp2 = convertToYCoordinate(mouseY);
		addNode(temp1, temp2, 0);
		this->Refresh();
		return;
	}
	
	for(int i = 0; i < lineList.size(); i++)
	{
		
	}
	
    /* This section will be for node handling */
	for(int i = 0; i < nodeList.size(); i++)
	{
		if(((mouseGraphX >= nodeList[i].getCenterXCoordinate() - 0.01 * zoomFactor) && (mouseGraphX <= nodeList[i].getCenterXCoordinate() + 0.01 * zoomFactor) && (mouseGraphY <= nodeList[i].getCenterYCoordinate() + 0.01 * zoomFactor) && (mouseGraphY >=nodeList[i].getCenterYCoordinate() - 0.01 * zoomFactor)) && nodeSelected == false)
		{
			if(blockLabelCreationIsEnabled)
				return;
			else if(event.ShiftDown())
			{
				/*	This section will first chewxMouseEvent &eventck to see if any other shape is selected.
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
                /* This section will clear any nodes that were selected such that the one that was 
                 * selected is the only one that is selected
                 */ 
				for (int j = 0; j < nodeList.size(); j++)
				{
					if(nodeList[j].getIsSelected())
						nodeList[j].toggleSelect();
				}
				nodeList[i].toggleSelect(); // Select the one that the user wants
				firstSelectedNodeIndex = i;
				this->Refresh();// Update the screen
				return; // quit the function
			}
			else
			{
                /* This section deals with creating a line between the two nodes
                 */ 
				if(lineCreationFlag)
				{
					
					double tempXCoor, tempYCoor;
					for(int k = 0; k < lineList.size(); k++)
					{
                        /* In this fucntion, we already have the index to the first node the user selected
                         * i would be the index of the second node the user selected.
                         * k is the index to the line segment. The purpose of the fuction
                         * tempx and tempyCoor are simply temporarl coordinates that are used as a midway.
                         */ 
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
					
					wxTextCtrl *arcAngle = new wxTextCtrl(dialogPanel, wxID_ANY, "35", wxPoint(101, 35), wxSize(156, 20));
					wxTextCtrl *maxSegment = new wxTextCtrl(dialogPanel, wxID_ANY, "10", wxPoint(101, 80), wxSize(156, 20));

					wxComboBox *boundaryComboBox = new wxComboBox(dialogPanel, wxID_ANY, "<None>", wxPoint(101, 122), wxSize(156, 21), boundaryList);
					
					if(arcSegmentDlg->ShowModal() == wxID_OK)
					{
						/* If the user clicked on ok to idicate they are done, we will then set the properties to an arc segment and add the segment to the geometry */
						double arcAngleVal = 0.0;
						double maxSegmentVal = 0.0;
						int index = boundaryComboBox->GetSelection();
						wxString test = boundaryList.Item(index);
						
						arcAngle->GetValue().ToDouble(&arcAngleVal);
						arcSegment.setArcAngle(arcAngleVal);
						
						maxSegment->GetValue().ToDouble(&maxSegmentVal);
						arcSegment.setNumSegments(maxSegmentVal);
						
						//arcSegment.setBoundaryMarker(test);
						arcSegment.setBoundaryMarker(test);
						
						arcSegment.setFirstNodeIndex(firstSelectedNodeIndex);
						arcSegment.setSecondNodeIndex(nodeList[i].getNodeIndex());
						
                        arcSegment.calculate(nodeList);
                        
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



void geometryEditorCanvas::onMouseRightDown(wxMouseEvent &event)
{
    std::string test1 = std::to_string(mouseGraphX);
    std::string test2 = std::to_string(mouseX);
    test1.append(" , ");
    test1.append(std::to_string(mouseGraphY));
    
    test2.append(" , ");
    test2.append(std::to_string(mouseY));
    
    wxMessageBox(test1);
    wxMessageBox(test2);
 //   wxMessageBox(stringMouseXCoor.str());
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
    EVT_RIGHT_DOWN(geometryEditorCanvas::onMouseRightDown)
wxEND_EVENT_TABLE()

//nodePoint::drawnodePoint(GLdouble xcoordinate, GL)