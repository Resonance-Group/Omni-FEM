#include <UI/openGLGeometry.h>
#include <string.h>

#include <math.h>

geometryEditorCanvas::geometryEditorCanvas(wxWindow *par, const wxPoint &position, const wxSize &size) : wxGLCanvas(par, wxID_ANY, NULL, position, size, wxBORDER_DOUBLE | wxBORDER_RAISED)
{

}



void geometryEditorCanvas::updateProjection()
{

}


void geometryEditorCanvas::drawGrid()
{

}



void geometryEditorCanvas::onKeyDown(wxKeyEvent &event)
{
    /*
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
     * */
}



void geometryEditorCanvas::onMouseMove(wxMouseEvent &event)
{
    
}



double geometryEditorCanvas::convertToXCoordinate(int xPixel)
{
    return 0;
}




double geometryEditorCanvas::convertToYCoordinate(int yPixel)
{
    return 0;
}



void geometryEditorCanvas::onGeometryPaint(wxPaintEvent &event)
{
    /*
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
             * 
			nodeIterator->draw();
		}
	}
     */ 
}


void geometryEditorCanvas::onResize(wxSizeEvent &event)
{

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

}


void geometryEditorCanvas::onEnterWindow(wxMouseEvent &event)
{

}



void geometryEditorCanvas::onLeavingWindow(wxMouseEvent &event)
{

}



void geometryEditorCanvas::onMouseLeftDown(wxMouseEvent &event)
{
    /*
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
	
    /* This section will be for node handling 
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
                  
				if(lineCreationFlag)
				{
					
					double tempXCoor, tempYCoor;
					for(int k = 0; k < lineList.size(); k++)
					{
                        /* In this fucntion, we already have the index to the first node the user selected
                         * i would be the index of the second node the user selected.
                         * k is the index to the line segment. The purpose of the fuction
                         * tempx and tempyCoor are simply temporarl coordinates that are used as a midway.
                          
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
					
					arcShape arcSegment;
					
					/* First, we will create a dialog box so that some basic propeties of the arc can be set by the user 
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
						/* If the user clicked on ok to idicate they are done, we will then set the properties to an arc segment and add the segment to the geometry 
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
     */
}



void geometryEditorCanvas::onMouseRightDown(wxMouseEvent &event)
{

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