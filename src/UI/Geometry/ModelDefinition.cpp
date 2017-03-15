#include <UI/ModelDefinition/ModelDefinition.h>


modelDefinition::modelDefinition(wxWindow *par, const wxPoint &point, const wxSize &size, problemDefinition &definition) : wxGLCanvas(par, wxID_ANY, NULL, point, size, wxBORDER_DOUBLE | wxBORDER_RAISED)
{
    _geometryContext = new wxGLContext(this);
	wxGLCanvas::SetCurrent(*_geometryContext);
    
    _localDefinition = &definition;
    
    _editor.setZoomFactorAddress(_zoomFactor);
    
    glViewport(0, 0, (double)this->GetSize().GetWidth(), (double)this->GetSize().GetHeight());
    
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glMatrixMode(GL_MODELVIEW);// The matrix mode specifies which matrix stack is the target for matrix operations
	glLoadIdentity();// Initial value
	glTranslated((float)this->GetSize().GetWidth() / 2.0f, (float)this->GetSize().GetHeight() / 2.0f, 0.0f);// This will move the camera to the center of the screen
    
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
    
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
    GLenum error = glGetError();
	if(error != GL_NO_ERROR)
	{
	//	wxMessageBox("Error - " + gluErrorString(error));
		return;
	}
    
    glMatrixMode(GL_MODELVIEW);
}


void modelDefinition::updateProjection()
{
    // First, load the projection matrix and reset the view to a default view
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    //Reset to modelview matrix
	glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    /* This section will handle the translation (panning) and scaled (zooming). 
     * Needs to be called each time a draw occurs in order to update the placement of all the components */
    if(_zoomFactor < 1e-9)
        _zoomFactor = 1e-9;
    
    if(_zoomFactor > 1e6)
        _zoomFactor = 1e6;
    
    
    
    glScaled(_zoomFactor / (this->GetSize().GetWidth() / this->GetSize().GetHeight()), _zoomFactor, 1.0);

    glTranslated(-_cameraX, -_cameraY, 0.0);
}

void modelDefinition::drawGrid()
{
    double cornerMinX = convertToXCoordinate(0);
    double cornerMinY = convertToYCoordinate(0);

    double cornerMaxX = convertToXCoordinate(this->GetSize().GetWidth());
    double cornerMaxY = convertToYCoordinate(this->GetSize().GetHeight());
    
    if(_preferences.getShowGridState())
    {
        /* The code for drawing the grid was adapted from the Agros2D project */
        glLineWidth(1.0);
        glEnable(GL_LINE_STIPPLE);
        /* 
        * The binary form is able to display the concept of glLineStipple for 
        * new users better then the Hex form. Although, the function is able to accept Hex
        * For an idea of how glLineStipple work, refer to the following link
        * http://images.slideplayer.com/16/4964597/slides/slide_9.jpg
        * 
        */ 
        glLineStipple(1, 0b0001100011000110);
    
        glBegin(GL_LINES);
            if(((cornerMaxX - cornerMinX) / _preferences.getGridStep() + (cornerMinY - cornerMaxY) / _preferences.getGridStep() < 200) && ((cornerMaxX - cornerMinX) / _preferences.getGridStep() > 0) && ((cornerMinY - cornerMaxY) / _preferences.getGridStep() > 0))
            {
                /* Create the grid for the vertical lines first */
                for(int i = cornerMinX / _preferences.getGridStep() - 1; i < cornerMaxX / _preferences.getGridStep() + 1; i++)
                {
                    if(i % 4 == 0)
                    {
                        glLineWidth(1.0);
                        glColor3d(0.0, 0.0, 0.0);
                    }
                    else
                    {
                        glLineWidth(0.5);
                        glColor3d(0.65, 0.65, 0.65);
                    }
                    
                    glVertex2d(i * _preferences.getGridStep(), cornerMinY);
                
                    glVertex2d(i * _preferences.getGridStep(), cornerMaxY);
                }
            
                /* Create the grid for the horizontal lines */
                for(int i = cornerMaxY / _preferences.getGridStep() - 1; i < cornerMinY / _preferences.getGridStep() + 1; i++)
                {
                    if(i % 4 == 0)
                    {
                        glLineWidth(1.0);
                        glColor3d(0.0, 0.0, 0.0);
                    }
                    else
                    {
                        glLineWidth(0.5);
                        glColor3d(0.65, 0.65, 0.65);
                    }
                    
                    glVertex2d(cornerMinX, i * _preferences.getGridStep());
                    glVertex2d(cornerMaxX, i * _preferences.getGridStep());
                }
            }
        
        glEnd();
        glDisable(GL_LINE_STIPPLE);
    }

    if(_preferences.getShowAxisState())
    {
        /* Create the center axis */    
        glColor3d(0.0, 0.0, 0.0);
        glLineWidth(1.5);
    
        glBegin(GL_LINES);
            glVertex2d(0, cornerMinY);
            glVertex2d(0, cornerMaxY);
        
            glVertex2d(cornerMinX, 0);
            glVertex2d(cornerMaxX, 0);
        glEnd();
    }
    
    /* This will create a crosshairs to indicate the location of the origin */
    if(_preferences.getShowOriginState())
    {
        glColor3d(0.4, 0.4, 0.4);
        glLineWidth(1.5);
        
        glBegin(GL_LINES);
            glVertex2d(0, -0.25);
            glVertex2d(0, 0.25);
            
            glVertex2d(-0.25, 0);
            glVertex2d(0.25, 0);
        glEnd();
    }
    
    glLineWidth(0.5);// Resets the line width back to the default
}



double modelDefinition::convertToXCoordinate(int xPixel)
{
    return (((2.0 / this->GetSize().GetWidth()) * ((double)xPixel - this->GetSize().GetWidth() / 2.0)) / _zoomFactor) * (this->GetSize().GetWidth() / this->GetSize().GetHeight()) + _cameraX;
}



double modelDefinition::convertToYCoordinate(int yPixel)
{
    return (-(2.0 / this->GetSize().GetHeight()) * ((double)yPixel - this->GetSize().GetHeight() / 2.0)) / _zoomFactor + _cameraY;
}


/* This function gets called everytime a draw routine is needed */
void modelDefinition::onPaintCanvas(wxPaintEvent &event)
{
    wxGLCanvas::SetCurrent(*_geometryContext);// This will make sure the the openGL commands are routed to the wxGLCanvas object
	wxPaintDC dc(this);// This is required for drawing
	
    glMatrixMode(GL_MODELVIEW);
    glClear(GL_COLOR_BUFFER_BIT);
    
    updateProjection();
    drawGrid();
    glMatrixMode(GL_MODELVIEW);
    

    if(_editor.getLineList()->size() > 0)
    {
        for(std::vector<edgeLineShape>::iterator lineIterator = _editor.getLineList()->begin(); lineIterator != _editor.getLineList()->end(); ++lineIterator)
        {
            lineIterator->draw(_editor.getNodeList()->at(lineIterator->getFirstNodeIndex()).getCenterXCoordinate(), _editor.getNodeList()->at(lineIterator->getFirstNodeIndex()).getCenterYCoordinate(), _editor.getNodeList()->at(lineIterator->getSecondNodeIndex()).getCenterXCoordinate(), _editor.getNodeList()->at(lineIterator->getSecondNodeIndex()).getCenterYCoordinate());
        }
    }
    
    if(_editor.getArcList()->size() > 0)
    {
        for(std::vector<arcShape>::iterator arcIterator = _editor.getArcList()->begin(); arcIterator != _editor.getArcList()->end(); ++arcIterator)
        {
            arcIterator->draw();
        }
    }
    
    if(_editor.getNodeList()->size() > 0)
    {
        for(std::vector<node>::iterator nodeIterator = _editor.getNodeList()->begin(); nodeIterator != _editor.getNodeList()->end(); ++nodeIterator)
        {
            nodeIterator->draw();
        }
    }
    
    SwapBuffers();
}



void modelDefinition::onResize(wxSizeEvent &event)
{
    wxGLCanvas::SetCurrent(*_geometryContext);
    /* This section of the code will resize the viewport when a resize event occurs and then move the view back to the center of the grid
     * This is considered the initial starting position. The glLoadIdentity() function returns the matrix back to the the 
     * default condition
     */ 
    glViewport(0, 0, (double)this->GetSize().GetWidth(), (double)this->GetSize().GetHeight());
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslated((float)this->GetSize().GetWidth() / 2.0f, (float)this->GetSize().GetHeight() / 2.0f, 0.0f);
   
 // The code below is not needed at this time. But the class needs to be created a little more in order to accurately determine that the code is in fact not needed
/*  glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
    */
    
    this->Refresh();
}



void modelDefinition::onMouseWheel(wxMouseEvent &event)
{
    if(event.GetWheelRotation() != 0)
    {
        /* This section of the code was adapted from Agro2D */
        
        _cameraX += (((2.0 / this->GetSize().GetWidth()) * (event.GetX() - this->GetSize().GetWidth() / 2.0)) / _zoomFactor) * (this->GetSize().GetWidth() / this->GetSize().GetHeight());
        _cameraY += (-(2.0 / this->GetSize().GetHeight()) * (event.GetY() - this->GetSize().GetHeight() / 2.0)) / _zoomFactor;
        
        if(!_preferences.getMouseZoomReverseState())
        {
            if(event.GetWheelRotation() > 0)
                _zoomFactor *= pow(1.2, -(event.GetWheelDelta()) / 150.0);
            else
                _zoomFactor *= pow(1.2, (event.GetWheelDelta()) / 150.0);
        }
        else
        {
            if(event.GetWheelRotation() < 0)
                _zoomFactor *= pow(1.2, -(event.GetWheelDelta()) / 150.0);
            else
                _zoomFactor *= pow(1.2, (event.GetWheelDelta()) / 150.0);
        }
        
        /* This will recalculate the new position of the mouse. Assuming that the mouse does not move at all during the process
         * This also enables the feature where the zoom will zoom in/out at the position of the mouse */
        
        _cameraX -= (((2.0 / this->GetSize().GetWidth()) * (event.GetX() - this->GetSize().GetWidth() / 2.0)) / _zoomFactor) * (this->GetSize().GetWidth() / this->GetSize().GetHeight());
        _cameraY -= (-(2.0 / this->GetSize().GetHeight()) * (event.GetY() - this->GetSize().GetHeight() / 2.0)) / _zoomFactor;
    }
	
    this->Refresh();// This will force the canvas to experience a redraw event
}



void modelDefinition::onMouseMove(wxMouseEvent &event)
{
    int dx = event.GetX() - _mouseXPixel;
    int dy = event.GetY() - _mouseYPixel;
    
	_mouseXPixel = event.GetX();
	_mouseYPixel = event.GetY();
    
    if(event.ButtonIsDown(wxMOUSE_BTN_MIDDLE))
    {
        _cameraX -= (2.0 / this->GetSize().GetWidth()) * ((double)dx / _zoomFactor) * (this->GetSize().GetWidth() / this->GetSize().GetHeight());
        _cameraY += (2.0 / this->GetSize().GetHeight()) * ((double)dy / _zoomFactor);
    }
    
    this->Refresh();
}



void modelDefinition::onMouseLeftDown(wxMouseEvent &event)
{
    wxGLCanvas::SetCurrent(*_geometryContext);
    bool nodeSelected = false;
    
    if(!_createNodes)
    {
        // Handle the create of block labels here
        return;
    }
    else if(_editor.getNodeList()->size() == 0)
	{
		if(_preferences.getSnapGridState())
        {
            double tempX = convertToXCoordinate(event.GetX());
            double tempY = convertToYCoordinate(event.GetY());
            roundToNearestGrid(tempX, tempY);
            _editor.addNode(tempX, tempY);
        }
        else
            _editor.addNode(convertToXCoordinate(event.GetX()), convertToYCoordinate(event.GetY()));
            
		this->Refresh();
		return;
	}
    
    for(unsigned long i = 0; i < _editor.getLineList()->size(); i++)
    {
        
    }
    
    for(unsigned long i = 0; i < _editor.getNodeList()->size(); i++)
    {
        if(((convertToXCoordinate(_mouseXPixel) >= _editor.getNodeList()->at(i).getCenterXCoordinate() - 0.01 * _zoomFactor) && (convertToXCoordinate(_mouseXPixel) <= _editor.getNodeList()->at(i).getCenterXCoordinate() + 0.01 * _zoomFactor) && (convertToYCoordinate(_mouseYPixel) <= _editor.getNodeList()->at(i).getCenterYCoordinate() + 0.01 * _zoomFactor) && (convertToYCoordinate(_mouseYPixel) >= _editor.getNodeList()->at(i).getCenterYCoordinate() - 0.01 * _zoomFactor)) && nodeSelected == false)
        {
            if(!_createNodes)
                return;
            else if(event.ShiftDown())
            {
                /*	This section will first chewxMouseEvent &eventck to see if any other shape is selected.
					If the shape is selected, then toggle the selection.
					As a last step, the function will then toggle select the selected node */
				
				if(_editor.getBlockLabelList()->size() > 0)
				{
					for(std::vector<blockLabel>::iterator blockLabelIterator = _editor.getBlockLabelList()->begin(); blockLabelIterator != _editor.getBlockLabelList()->end(); ++blockLabelIterator)
					{
                        if(blockLabelIterator->getIsSelectedState())
                            blockLabelIterator->setSelectState(false);
					}
				}
				
				if(_editor.getArcList()->size() > 0)
				{
                    for(std::vector<arcShape>::iterator arcIterator = _editor.getArcList()->begin(); arcIterator != _editor.getArcList()->end(); ++arcIterator)
                    {
                        if(arcIterator->getIsSelectedState())
                            arcIterator->setSelectState(false);
                    }
				}
				
				if(_editor.getLineList()->size() > 0)
				{
                    for(std::vector<edgeLineShape>::iterator lineIterator = _editor.getLineList()->begin(); lineIterator != _editor.getLineList()->end(); ++lineIterator)
                    {
                        if(lineIterator->getIsSelectedState())
                            lineIterator->setSelectState(false);
                    }
				}
                _editor.getNodeList()->at(i).setSelectState(true);
                this->Refresh();
                return;
            }
            else if(_editor.getFirstSelectedNodeIndex() == -1)
            {
                for(std::vector<node>::iterator nodeIterator = _editor.getNodeList()->begin(); nodeIterator != _editor.getNodeList()->end(); ++nodeIterator)
                {
                    if(nodeIterator->getIsSelectedState())
                        nodeIterator->setSelectState(false);
                }
                
                _editor.getNodeList()->at(i).setSelectState(true);
                _editor.setFirstSelectedNodeIndex(i);
                this->Refresh();
                return;
            }
            else
            {
                if(_createLines)
                {
                    double tempXCoor, tempYCoor;
					for(int k = 0; k < _editor.getLineList()->size(); k++)
					{
                        /* In this fucntion, we already have the index to the first node the user selected
                         * i would be the index of the second node the user selected.
                         * k is the index to the line segment. The purpose of the fuction
                         * tempx and tempyCoor are simply temporarl coordinates that are used as a midway.
                         */ 
                          
						if(_editor.getIntersection(_editor.getFirstSelectedNodeIndex(), i, k, tempXCoor, tempYCoor) == true)
						{
							_editor.addNode(tempXCoor, tempYCoor);
						}
					}
					
					_editor.addLine(_editor.getFirstSelectedNodeIndex(), _editor.getNodeList()->at(i).getNodeIndex(), NULL);
                }
                else
                {
                    arcSegmentDialog *dialog;
                    
                    if(_localDefinition->getPhysicsProblem() == physicProblems::PROB_ELECTROSTATIC)
                        dialog = new arcSegmentDialog(this, _localDefinition->getElectricalBoundaryList());
                    else if(_localDefinition->getPhysicsProblem() == physicProblems::PROB_MAGNETICS)
                        dialog = new arcSegmentDialog(this, _localDefinition->getMagneticBoundaryList());
                        
                    if(dialog->ShowModal() == wxID_OK)
                    {
                        arcShape temp;
                        dialog->getArcParameter(temp);
                        temp.setFirstNodeIndex(_editor.getFirstSelectedNodeIndex());
                        temp.setSecondNodeIndex(_editor.getNodeList()->at(i).getNodeIndex());
                        temp.calculate(*_editor.getNodeList());
                        _editor.addArc(temp, 0);
                    }
                }
                
                _editor.getNodeList()->at(_editor.getFirstSelectedNodeIndex()).setSelectState(false);
                _editor.setFirstSelectedNodeIndex(-1);
                this->Refresh();
                return;
            }
        }
    }
    
    if(_preferences.getSnapGridState())
    {
        double tempX = convertToXCoordinate(_mouseXPixel);
        double tempY = convertToYCoordinate(_mouseYPixel);
        roundToNearestGrid(tempX, tempY);
        _editor.addNode(tempX, tempY);
    }
    else
        _editor.addNode(convertToXCoordinate(_mouseXPixel), convertToYCoordinate(_mouseYPixel));
        
    this->Refresh();
}



void modelDefinition::roundToNearestGrid(double &xCoordinate, double &yCoordinate)
{
    /* How to code works. For the sake of the explanianation, imagine we are working with
     * a 1D problem and that the point is between two grid markings.
     * So first, we find the modulus of the coordinate / gridStep.
     * What this tells us is the "distance" from the lower grid makring to the point.
     * If the point is beyond the half way "mark", te modulus will return a number 
     * greater then gridStep / 2. If the point is below the halfway "mark",
     * you can simply take the point coordinate and subtract out the modulus.
     * If the point is beyond the halfway "mark", you have to add the gridstep to the 
     * point and then subtract out the modulus.
     * For example, if a point is at 0.40 and the grid step size is 0.25, then the point 
     * is between 0.25 and 0.5. The modulus of 0.40 % 0.25 will be 0.15. Since this is 
     * greater then 0.25 / 2 = 0.125 (the halfway mark), we need to add 0.25 to 0.40 (0.25 + 0.4 = 0.65)
     * Subtracting the modulus of 0.15 yeilds 0.5. The correct number to round 0.4 up to.
     */ 
    double xCoordRemainder = fmod(abs(xCoordinate), _preferences.getGridStep());
    double yCoordRemainder = fmod(abs(yCoordinate), _preferences.getGridStep());
    
    if(xCoordRemainder != 0)
    {
        if(xCoordinate < 0)
        {
            if(xCoordRemainder <= (_preferences.getGridStep() / 2.0))
                xCoordinate = -(abs(xCoordinate) - xCoordRemainder); 
            else
                xCoordinate = -(abs(xCoordinate) - xCoordRemainder + _preferences.getGridStep()); 
               
        }
        else
        {
            if(xCoordRemainder <= (_preferences.getGridStep() / 2.0))
                xCoordinate -= xCoordRemainder;
            else
                xCoordinate = xCoordinate + _preferences.getGridStep() - xCoordRemainder;
        }
    }
    
    if(yCoordRemainder != 0)
    {
        if(yCoordinate < 0)
        {
            if(yCoordRemainder <= (_preferences.getGridStep() / 2.0))
                yCoordinate = -(abs(yCoordinate) - yCoordRemainder); 
            else
                yCoordinate = -(abs(yCoordinate) - yCoordRemainder + _preferences.getGridStep()); 
               
        }
        else
        {
            if(yCoordRemainder <= (_preferences.getGridStep() / 2.0))
                yCoordinate -= yCoordRemainder;
            else
                yCoordinate = yCoordinate + _preferences.getGridStep() - yCoordRemainder;
        }
    }
}



void modelDefinition::onMouseRightDown(wxMouseEvent &event)
{
    if(event.ControlDown())
    {
        std::string combineStringPixel;
        std::string combineStringCoord = "(";
    
        combineStringPixel = "(";
        combineStringPixel.append(std::to_string(_mouseXPixel));
        combineStringPixel.append(", ");
        combineStringPixel.append(std::to_string(_mouseYPixel));
        combineStringPixel.append(")");
    
        combineStringCoord.append(std::to_string(convertToXCoordinate(_mouseXPixel)));
        combineStringCoord.append(", ");
        combineStringCoord.append(std::to_string(convertToYCoordinate(_mouseYPixel)));
        combineStringCoord.append(")");
    
        wxMessageBox(combineStringCoord);
    }
    else
    {
        arcSegmentDialog *test = new arcSegmentDialog(this, _localDefinition->getElectricalBoundaryList());
        if(test->ShowModal() == wxID_OK)
        {
            
        }
    }
}



wxBEGIN_EVENT_TABLE(modelDefinition, wxGLCanvas)
    EVT_PAINT(modelDefinition::onPaintCanvas)
    EVT_SIZE(modelDefinition::onResize)
    EVT_ENTER_WINDOW(modelDefinition::onEnterWindow)
    /* This section is the event procedure for the mouse controls */
    EVT_MOUSEWHEEL(modelDefinition::onMouseWheel)
    EVT_MOTION(modelDefinition::onMouseMove)
    EVT_LEFT_DOWN(modelDefinition::onMouseLeftDown)
    EVT_RIGHT_DOWN(modelDefinition::onMouseRightDown)
wxEND_EVENT_TABLE()