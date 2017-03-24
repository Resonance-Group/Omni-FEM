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



void modelDefinition::deleteSelection()
{
    if(_editor.getNodeList()->size() > 1)
    {
        std::vector<node> nodesToKeep;
        for(std::vector<node>::iterator nodeIterator = _editor.getNodeList()->begin(); nodeIterator != _editor.getNodeList()->end(); ++nodeIterator)
        {
            if(nodeIterator->getIsSelectedState())
            {
                if(_editor.getLineList()->size() > 0)
                {
                    /* Need to cycle through the entire line list and arc list in order to determine which arc/line the node is associated with and delete that arc/line by selecting i.
                     * The deletion of the arc/line occurs later in the code*/
                    
                    for(std::vector<edgeLineShape>::iterator lineIterator = _editor.getLineList()->begin(); lineIterator != _editor.getLineList()->end(); ++lineIterator)
                    {
                        if(lineIterator->getFirstNode() == *nodeIterator || lineIterator->getSecondNode() == *nodeIterator)
                        {
                            lineIterator->setSelectState(true);
                        }
                    }
                }
                    
                if(_editor.getArcList()->size() > 0)
                {
                    for(std::vector<arcShape>::iterator arcIterator = _editor.getArcList()->begin(); arcIterator != _editor.getArcList()->end(); ++arcIterator)
                    {
                        if(arcIterator->getFirstNode() == *nodeIterator || arcIterator->getSecondNode() == *nodeIterator)
                        {
                            arcIterator->setSelectState(true);
                        }
                    }
                }
            }
            else
                nodesToKeep.push_back(*nodeIterator);
        }
            
        _editor.setNodeList(nodesToKeep);
    }
    else if(_editor.getNodeList()->size() == 1 && _editor.getNodeList()->at(0).getIsSelectedState())
    {
        _editor.getNodeList()->clear();
    }
        
    if(_editor.getLineList()->size() > 1)
    {
        std::vector<edgeLineShape> linesToKeep;
        for(std::vector<edgeLineShape>::iterator lineIterator = _editor.getLineList()->begin(); lineIterator != _editor.getLineList()->end(); ++lineIterator)
        {
            if(!lineIterator->getIsSelectedState())
            {
                linesToKeep.push_back(*lineIterator);
            }
        }
        _editor.setLineList(linesToKeep);
    }
    else if(_editor.getLineList()->size() == 1 && _editor.getLineList()->at(0).getIsSelectedState())
    {
        _editor.getLineList()->clear();
    }
        
    if(_editor.getArcList()->size() > 1)
    {
        std::vector<arcShape> acrsToKeep;
        for(std::vector<arcShape>::iterator arcIterator = _editor.getArcList()->begin(); arcIterator != _editor.getArcList()->end(); ++arcIterator)
        {
            if(!arcIterator->getIsSelectedState())
            {
                acrsToKeep.push_back(*arcIterator);
            }
        }
        _editor.setArcList(acrsToKeep);
    }
    else if(_editor.getArcList()->size() == 1 && _editor.getArcList()->at(0).getIsSelectedState())
    {
        _editor.getArcList()->clear();
    }
        
    if(_editor.getBlockLabelList()->size() > 1)
    {
        std::vector<blockLabel> labelsToKeep;
        wxGLStringArray labelNamesToKeep;
        int i = 0;
        for(std::vector<blockLabel>::iterator blockIterator = _editor.getBlockLabelList()->begin(); blockIterator != _editor.getBlockLabelList()->end(); ++blockIterator)
        {
            if(!blockIterator->getIsSelectedState())
            {
                labelsToKeep.push_back(*blockIterator);
                 //   labelNamesToKeep.addString(_editor.getBlockNameArray()->get(i));
            }
            i++;
        }
        _editor.setBlockLabelList(labelsToKeep);
        _editor.setLabelNameArray(labelNamesToKeep);
    }
    else if(_editor.getBlockLabelList()->size() == 1 && _editor.getBlockLabelList()->at(0).getIsSelectedState())
    {
        _editor.getBlockLabelList()->clear();
         //   _editor.getBlockNameArray()->getStringArray->clear();
    }
        
    this->Refresh();
    return;
}



void modelDefinition::zoomIn()
{
    _zoomFactor *= pow(1.2, (300.0) / 150.0);

    this->Refresh();
}



void modelDefinition::zoomOut()
{
    _zoomFactor *= pow(1.2, -(300.0) / 150.0);
    
    this->Refresh();
}




void modelDefinition::editSelection()
{
    if(_nodesAreSelected)
    {
        /* All of the other if statements follow the same logic as displayed here */
        setNodalPropertyDialog *dialog;
        nodeSetting selectedNodeSetting;
        /* this will grab the first node's nodal setting. Whichever node is selected, it will aloways grab the first one. 
         * The thinking is this that if there are multiple selections, the user wants to set them all to be the same
         * so it doesnt really matter if the first, second, third, or fifth node is different because the settings will all be the same
         */ 
        for(std::vector<node>::iterator nodeIterator = _editor.getNodeList()->begin(); nodeIterator != _editor.getNodeList()->end(); ++nodeIterator)
        {
            if(nodeIterator->getIsSelectedState())
            {
                selectedNodeSetting = *nodeIterator->getNodeSetting();
                break;
            }
        }
        // Create and display the dialog dependign on the physics problem
        if(_localDefinition->getPhysicsProblem() == physicProblems::PROB_ELECTROSTATIC)
            dialog = new setNodalPropertyDialog(this, _localDefinition->getNodalPropertyList(), selectedNodeSetting, _localDefinition->getConductorList());
        else if(_localDefinition->getPhysicsProblem() == physicProblems::PROB_MAGNETICS)
            dialog = new setNodalPropertyDialog(this, _localDefinition->getNodalPropertyList(), selectedNodeSetting); 
        
        if(dialog->ShowModal() == wxID_OK)
        {
            dialog->getNodalSettings(selectedNodeSetting);// Might as well use the existing nodeSetting object
            
            /* THis will loop through all of the nodes and set the nodes to the new nodal settings if the nodes were the selected ones. */
            for(std::vector<node>::iterator nodeIterator = _editor.getNodeList()->begin(); nodeIterator != _editor.getNodeList()->end(); ++nodeIterator)
            {
                if(nodeIterator->getIsSelectedState())
                {
                    nodeIterator->setNodeSettings(selectedNodeSetting);
                }
            }
        }
        delete(dialog);
    }
    else if(_linesAreSelected)
    {
        /* TODO: Sicne the lines are currently not able to be selected, this code will need to be tested after the bug for selecting the lines is fixed */
        segmentPropertyDialog *dialog;
        segmentProperty selectedProperty;
        
        for(std::vector<edgeLineShape>::iterator lineIterator = _editor.getLineList()->begin(); lineIterator != _editor.getLineList()->end(); ++lineIterator)
        {
            if(lineIterator->getIsSelectedState())
            {
                selectedProperty = *lineIterator->getSegmentProperty();
                break;
            }
        }
        
        if(_localDefinition->getPhysicsProblem() == physicProblems::PROB_ELECTROSTATIC)
            dialog = new segmentPropertyDialog(this, _localDefinition->getElectricalBoundaryList(), _localDefinition->getConductorList(), selectedProperty, false);
        else if(_localDefinition->getPhysicsProblem() == physicProblems::PROB_MAGNETICS)
            dialog = new segmentPropertyDialog(this, _localDefinition->getMagneticBoundaryList(), selectedProperty, false);
            
        if(dialog->ShowModal() == wxID_OK)
        {
            dialog->getSegmentProperty(selectedProperty);
            
            for(std::vector<edgeLineShape>::iterator lineIterator = _editor.getLineList()->begin(); lineIterator != _editor.getLineList()->end(); ++lineIterator)
            {
                if(lineIterator->getIsSelectedState())
                    lineIterator->setSegmentProperty(selectedProperty);
            }
        }
        delete(dialog);
    }
    else if(_arcsAreSelected)
    {
        // TODO: SInce the arcs are currently not able to be drawn or selected, this code will need to be tested after the two bugs are fixed
        segmentPropertyDialog *dialog;
        segmentProperty selectedProperty;
        
        for(std::vector<arcShape>::iterator arcIterator = _editor.getArcList()->begin(); arcIterator != _editor.getArcList()->end(); ++arcIterator)
        {
            if(arcIterator->getIsSelectedState())
            {
                selectedProperty = *arcIterator->getSegmentProperty();
                break;
            }
        }
        
        if(_localDefinition->getPhysicsProblem() == physicProblems::PROB_ELECTROSTATIC)
            dialog = new segmentPropertyDialog(this, _localDefinition->getElectricalBoundaryList(), _localDefinition->getConductorList(), selectedProperty, true);
        else if(_localDefinition->getPhysicsProblem() == physicProblems::PROB_MAGNETICS)
            dialog = new segmentPropertyDialog(this, _localDefinition->getMagneticBoundaryList(), selectedProperty, true);
            
        if(dialog->ShowModal() == wxID_OK)
        {
            dialog->getSegmentProperty(selectedProperty);
            
            for(std::vector<arcShape>::iterator arcIterator = _editor.getArcList()->begin(); arcIterator != _editor.getArcList()->end(); ++arcIterator)
            {
                if(arcIterator->getIsSelectedState())
                    arcIterator->setSegmentProperty(selectedProperty);
            }
        }
        delete(dialog);
    }
    else if(_labelsAreSelected)
    {
        blockPropertyDialog *dialog;
        blockProperty selectedBlockLabel;
        
        for(std::vector<blockLabel>::iterator blockIterator = _editor.getBlockLabelList()->begin(); blockIterator != _editor.getBlockLabelList()->end(); ++blockIterator)
        {
            if(blockIterator->getIsSelectedState())
            {
                selectedBlockLabel = blockIterator->getProperty();
                break;
            }
        }
        
        if(_localDefinition->getPhysicsProblem() == physicProblems::PROB_ELECTROSTATIC)
            dialog = new blockPropertyDialog(this, _localDefinition->getElectricalMaterialList(), selectedBlockLabel, _localDefinition->getElectricalPreferences().isAxistmmetric());
        else if(_localDefinition->getPhysicsProblem() == physicProblems::PROB_MAGNETICS)
            dialog = new blockPropertyDialog(this, _localDefinition->getMagnetMaterialList(), _localDefinition->getCircuitList(), selectedBlockLabel, _localDefinition->getMagneticPreference().isAxistmmetric());

        if(dialog->ShowModal() == wxID_OK)
        {
            dialog->getBlockProperty(selectedBlockLabel);
            
            for(std::vector<blockLabel>::iterator blockIterator = _editor.getBlockLabelList()->begin(); blockIterator != _editor.getBlockLabelList()->end(); ++blockIterator)
            {
                if(blockIterator->getIsSelectedState())
                    blockIterator->setPorperty(selectedBlockLabel);
            }
        }
        delete(dialog);
    }
}


// TODO: Test the functionality of the arcs and lines when the bugs are fixed in these two objects
void modelDefinition::updateProperties(bool scanConductorProperty, bool scanNodalProperty, bool scanBoundaryProperty, bool scanMaterialProperty, bool scanCircuitProperty)
{
    if(scanConductorProperty)
    {
        for(std::vector<node>::iterator nodeIterator = _editor.getNodeList()->begin(); nodeIterator != _editor.getNodeList()->end(); ++nodeIterator)
        {
            bool conductorPropertyIsPresent = false;
            if(nodeIterator->getNodeSetting()->getConductorPropertyName() != "None")
            {
                for(int i = 0; i < _localDefinition->getConductorList().size(); i++)
                {
                    if(nodeIterator->getNodeSetting()->getConductorPropertyName() == _localDefinition->getConductorList().at(i).getName())
                    {
                        conductorPropertyIsPresent = true;
                        break;
                    }
                }
                if(!conductorPropertyIsPresent)
                    nodeIterator->getNodeSetting()->setConductorPropertyName("None");
            }
        }
        
        for(std::vector<edgeLineShape>::iterator lineIterator = _editor.getLineList()->begin(); lineIterator != _editor.getLineList()->end(); ++lineIterator)
        {
            bool conductorPropertyIsPresent = false;
            if(lineIterator->getSegmentProperty()->getConductorName() != "None")
            {
                for(int i = 0; i < _localDefinition->getConductorList().size(); i++)
                {
                    if(lineIterator->getSegmentProperty()->getConductorName() == _localDefinition->getConductorList().at(i).getName() && !conductorPropertyIsPresent)
                    {
                        conductorPropertyIsPresent = true;
                        break;
                    }
                }
                
                if(!conductorPropertyIsPresent)
                    lineIterator->getSegmentProperty()->setConductorName("None");
            }
        }
        
        for(std::vector<arcShape>::iterator arcIterator = _editor.getArcList()->begin(); arcIterator != _editor.getArcList()->end(); ++arcIterator)
        {
            bool conductorPropertyIsPresent = false;
            if(arcIterator->getSegmentProperty()->getConductorName() != "None")
            {
                for(int i = 0; i < _localDefinition->getConductorList().size(); i++)
                {
                    if(arcIterator->getSegmentProperty()->getConductorName() == _localDefinition->getConductorList().at(i).getName() && !conductorPropertyIsPresent)
                    {
                        conductorPropertyIsPresent = true;
                        break;
                    }
                }
                
                if(!conductorPropertyIsPresent)
                    arcIterator->getSegmentProperty()->setConductorName("None");
            }
        }
    }
    else if(scanNodalProperty)
    {
        for(std::vector<node>::iterator nodeIterator = _editor.getNodeList()->begin(); nodeIterator != _editor.getNodeList()->end(); ++nodeIterator)
        {
            bool nodalPropertyIsPresent = false;
            if(nodeIterator->getNodeSetting()->getNodalPropertyName() != "None")
            {
                for(int i = 0; i < _localDefinition->getNodalPropertyList().size(); i++)
                {
                    // THis section will take the nodeIterator object and comapre it against each property that is related to the node. It will only compare against the name
                    // IF the problem is electrostatics, we will also compare against the conductor property.
                    // IF the property name is found in the master list, the loop will break and move onto the next node object.
                    // If not, then the property name within the node object will be changed back to none.
                    // This logic continues for the other geometry shape cases
                    if(nodeIterator->getNodeSetting()->getNodalPropertyName() == _localDefinition->getNodalPropertyList().at(i).getName() && !nodalPropertyIsPresent)
                    {
                        nodalPropertyIsPresent = true;
                        break;
                    }
                }
                
                if(!nodalPropertyIsPresent)
                    nodeIterator->getNodeSetting()->setNodalPropertyName("None");
            }
        }
    }
    else if(scanBoundaryProperty)
    {
        for(std::vector<edgeLineShape>::iterator lineIterator = _editor.getLineList()->begin(); lineIterator != _editor.getLineList()->end(); ++lineIterator)
        {
            bool boundaryIsPresent = false;
            if(_localDefinition->getPhysicsProblem() == physicProblems::PROB_ELECTROSTATIC)
            {
                if(lineIterator->getSegmentProperty()->getBoundaryName() != "None")
                {
                    for(int i = 0; i < _localDefinition->getElectricalBoundaryList().size(); i++)
                    {
                        if(lineIterator->getSegmentProperty()->getBoundaryName() == _localDefinition->getElectricalBoundaryList().at(i).getBoundaryName() && !boundaryIsPresent)
                        {
                            boundaryIsPresent = true;
                            break;
                        }
                    }
                    
                    if(!boundaryIsPresent)
                        lineIterator->getSegmentProperty()->setBoundaryName("None");
                }
            }
            else if (_localDefinition->getPhysicsProblem() == physicProblems::PROB_MAGNETICS)
            {
                bool boundaryIsPresent = false;
                if(lineIterator->getSegmentProperty()->getBoundaryName() != "None")
                {
                    for(int i = 0; i < _localDefinition->getMagneticBoundaryList().size(); i++)
                    {
                        if(lineIterator->getSegmentProperty()->getBoundaryName() == _localDefinition->getElectricalBoundaryList().at(i).getBoundaryName())
                        {
                            boundaryIsPresent = true;
                            break;
                        }
                    }
                    
                    if(!boundaryIsPresent)
                        lineIterator->getSegmentProperty()->setBoundaryName("None");
                }
            }
        }
        
        for(std::vector<arcShape>::iterator arcIterator = _editor.getArcList()->begin(); arcIterator != _editor.getArcList()->end(); ++arcIterator)
        {
            bool boundaryIsPresent = false;
            if(_localDefinition->getPhysicsProblem() == physicProblems::PROB_ELECTROSTATIC)
            {
                if(arcIterator->getSegmentProperty()->getBoundaryName() != "None")
                {
                    for(int i = 0; i < _localDefinition->getElectricalBoundaryList().size(); i++)
                    {
                        if(arcIterator->getSegmentProperty()->getBoundaryName() == _localDefinition->getElectricalBoundaryList().at(i).getBoundaryName() && !boundaryIsPresent)
                        {
                            boundaryIsPresent = true;
                            break;
                        }
                    }
                    
                    if(!boundaryIsPresent)
                        arcIterator->getSegmentProperty()->setBoundaryName("None");
                }
            }
            else if (_localDefinition->getPhysicsProblem() == physicProblems::PROB_MAGNETICS)
            {
                bool boundaryIsPresent = false;
                if(arcIterator->getSegmentProperty()->getBoundaryName() != "None")
                {
                    for(int i = 0; i < _localDefinition->getMagneticBoundaryList().size(); i++)
                    {
                        if(arcIterator->getSegmentProperty()->getBoundaryName() == _localDefinition->getElectricalBoundaryList().at(i).getBoundaryName())
                        {
                            boundaryIsPresent = true;
                            break;
                        }
                    }
                    
                    if(!boundaryIsPresent)
                        arcIterator->getSegmentProperty()->setBoundaryName("None");
                }
            }
        }
    }
    else if(scanMaterialProperty)
    {
        for(std::vector<blockLabel>::iterator blockIterator = _editor.getBlockLabelList()->begin(); blockIterator != _editor.getBlockLabelList()->end(); ++blockIterator)
        {
            bool materialIsPresent = false;
            
            if(_localDefinition->getPhysicsProblem() == physicProblems::PROB_ELECTROSTATIC)
            {
                if(blockIterator->getAddressProperty()->getMaterialName() != "None")
                {
                    for(int i = 0; i < _localDefinition->getElectricalMaterialList().size(); i++)
                    {
                        if(blockIterator->getAddressProperty()->getMaterialName() == _localDefinition->getElectricalMaterialList().at(i).getName())
                        {
                            materialIsPresent = true;
                            break;
                        }
                    }
                    
                    if(!materialIsPresent)
                        blockIterator->getAddressProperty()->setMaterialName("None");
                }
                else if(_localDefinition->getPhysicsProblem() == physicProblems::PROB_MAGNETICS)
                {
                    if(blockIterator->getAddressProperty()->getMaterialName() != "None")
                    {
                        for(int i = 0; i < _localDefinition->getMagnetMaterialList().size(); i++)
                        {
                            if(blockIterator->getAddressProperty()->getMaterialName() == _localDefinition->getMagnetMaterialList().at(i).getName())
                            {
                                materialIsPresent = true;
                                break;
                            }
                        }
                        
                        if(!materialIsPresent)
                            blockIterator->getAddressProperty()->setMaterialName("None");
                    }
                }
            }
        }
    }
    else if(scanCircuitProperty)
    {
        for(std::vector<blockLabel>::iterator blockIterator = _editor.getBlockLabelList()->begin(); blockIterator != _editor.getBlockLabelList()->end(); ++blockIterator)
        {
            bool circuitIsPresent = false;
            if(blockIterator->getAddressProperty()->getCircuitName() != "None")
            {
                for(int i = 0; i < _localDefinition->getCircuitList().size(); i++)
                {
                    if(blockIterator->getAddressProperty()->getCircuitName() == _localDefinition->getCircuitList().at(i).getName())
                    {
                        circuitIsPresent = true;
                        break;
                    }
                }
                
                if(!circuitIsPresent)
                    blockIterator->getAddressProperty()->setCircuitName("None");
            }
        }
    }
}



void modelDefinition::selectGroup(EditGeometry geometry, unsigned int groupNumber)
{
    clearSelection();
    
    if(geometry == EditGeometry::EDIT_NODES)
    {
        _nodesAreSelected = true;
        for(std::vector<node>::iterator nodeIterator = _editor.getNodeList()->begin(); nodeIterator != _editor.getNodeList()->end(); ++nodeIterator)
        {
            if(nodeIterator->getNodeSetting()->getGroupNumber() == groupNumber)
            {
                nodeIterator->setSelectState(true);
            }
        }
    }
    else if(geometry == EditGeometry::EDIT_LINES)
    {
        _linesAreSelected = true;
        for(std::vector<edgeLineShape>::iterator lineIterator = _editor.getLineList()->begin(); lineIterator != _editor.getLineList()->end(); ++lineIterator)
        {
            if(lineIterator->getSegmentProperty()->getGroupNumber() == groupNumber)
            {
                lineIterator->setSelectState(true);
            }
        }
    }
    else if(geometry == EditGeometry::EDIT_ARCS)
    {
        _arcsAreSelected = true;
        for(std::vector<arcShape>::iterator arcIterator = _editor.getArcList()->begin(); arcIterator != _editor.getArcList()->end(); ++arcIterator)
        {
            if(arcIterator->getSegmentProperty()->getGroupNumber() == groupNumber)
            {
                arcIterator->setSelectState(true);
            }
        }
    }
    else if(geometry == EditGeometry::EDIT_LABELS)
    {
        _labelsAreSelected = true;
        for(std::vector<blockLabel>::iterator blockIterator = _editor.getBlockLabelList()->begin(); blockIterator != _editor.getBlockLabelList()->end(); ++blockIterator)
        {
            if(blockIterator->getProperty().getGroupNumber() == groupNumber)
            {
                blockIterator->setSelectState(true);
            }
        }
    }
    
    this->Refresh();
    return;
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



void modelDefinition::clearSelection()
{
    if(_createNodes)
    {
        for(std::vector<node>::iterator nodeIterator = _editor.getNodeList()->begin(); nodeIterator != _editor.getNodeList()->end(); ++nodeIterator)
        {
            if(nodeIterator->getIsSelectedState())
                nodeIterator->setSelectState(false);
        }
    }
    elseif(!_createNodes || _labelsAreSelected)
    {
        for(std::vector<blockLabel>::iterator blockIterator = _editor.getBlockLabelList()->begin(); blockIterator != _editor.getBlockLabelList()->end(); ++blockIterator)
        {
            if(blockIterator->getIsSelectedState())
                blockIterator->setSelectState(false);
        }
    }
    
    if(_createLines)
    {
        for(std::vector<edgeLineShape>::iterator lineIterator = _editor.getLineList()->begin(); lineIterator != _editor.getLineList()->end(); ++lineIterator)
        {
            if(lineIterator->getIsSelectedState())
                lineIterator->setSelectState(false);
        }
    }
    else if(!_createLines || _arcsAreSelected)
    {
        for(std::vector<arcShape>::iterator arcIterator = _editor.getArcList()->begin(); arcIterator != _editor.getArcList()->end(); ++arcIterator)
        {
            if(arcIterator->getIsSelectedState())
                arcIterator->setSelectState(false);
        }
    }
    
    _nodesAreSelected = false;
    _linesAreSelected = false;
    _arcsAreSelected = false;
    _labelsAreSelected = false;
}


/* This function gets called everytime a draw routine is needed */
void modelDefinition::onPaintCanvas(wxPaintEvent &event)
{
    wxGLCanvas::SetCurrent(*_geometryContext);// This will make sure the the openGL commands are routed to the wxGLCanvas object
	wxPaintDC dc(this);// This is required for drawing
//    wxDC test(this);
	
    glMatrixMode(GL_MODELVIEW);
    glClear(GL_COLOR_BUFFER_BIT);
    
    updateProjection();
    drawGrid();
    glMatrixMode(GL_MODELVIEW);
    

    if(_editor.getLineList()->size() > 0)
    {
        for(std::vector<edgeLineShape>::iterator lineIterator = _editor.getLineList()->begin(); lineIterator != _editor.getLineList()->end(); ++lineIterator)
        {
            lineIterator->draw();
        }
    }
    
    if(_editor.getArcList()->size() > 0)
    {
        for(std::vector<arcShape>::iterator arcIterator = _editor.getArcList()->begin(); arcIterator != _editor.getArcList()->end(); ++arcIterator)
        {
            arcIterator->draw();
        }
    }
    
    if(_editor.getBlockLabelList()->size() > 0)
    {
        for(std::vector<blockLabel>::iterator blockIterator = _editor.getBlockLabelList()->begin(); blockIterator != _editor.getBlockLabelList()->end(); ++blockIterator)
        {
            blockIterator->draw();
        }
    }
    
    if(_editor.getNodeList()->size() > 0)
    {
        for(std::vector<node>::iterator nodeIterator = _editor.getNodeList()->begin(); nodeIterator != _editor.getNodeList()->end(); ++nodeIterator)
        {
            nodeIterator->draw();
        }
    }
    

  //  if(_preferences.getShowBlockNameState() && _editor.getBlockNameArray()->getNameArraySize() > 0)
  //  {
 /*       glEnable(GL_TEXTURE_2D);
        if(!_isFirstInitlized)
        {
           _editor.getBlockNameArray()->consolidate(&dc);
           _editor.getBlockNameArray()->setFont(wxFont(8.25, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
           _isFirstInitlized = true;
        }
        _editor.getBlockNameArray()->bind();
        glColor3b(0, 0, 0);
        
        _editor.renderBlockNames();
        glDisable(GL_TEXTURE_2D);*/
 //   }
    
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
    else if(event.ButtonIsDown(wxMOUSE_BTN_LEFT))
    {
        if(_createNodes && !_geometryIsSelected && _editor.getNodeList()->back().getDraggingState())
        {
            double tempX = convertToXCoordinate(event.GetX());
            double tempY = convertToYCoordinate(event.GetY());
            // Update the last node entry with new x and y coordinates and round if on snap grid
            if(_preferences.getSnapGridState())
            {
                roundToNearestGrid(tempX, tempY);
                _editor.getNodeList()->at(_editor.getNodeList()->size() - 1).setCenter(tempX, tempY);
            }
            else
            {
                _editor.getNodeList()->at(_editor.getNodeList()->size() - 1).setCenter(tempX, tempY);
            }
        }
        else if(!_createNodes)
        {
            // Update the last bloc labe with new x and y coordinates and round if on snap grid
            if(_preferences.getSnapGridState())
            {
                double tempX = convertToXCoordinate(event.GetX());
                double tempY = convertToYCoordinate(event.GetY());
                roundToNearestGrid(tempX, tempY);
                _editor.getBlockLabelList()->at(_editor.getBlockLabelList()->size() - 1).setCenter(tempX, tempY);
            }
            else
            {
                _editor.getBlockLabelList()->at(_editor.getBlockLabelList()->size() - 1).setCenter(convertToXCoordinate(event.GetX()), convertToYCoordinate(event.GetY()));
            }
        }
    }
    
    this->Refresh();
}



void modelDefinition::onMouseLeftDown(wxMouseEvent &event)
{
    wxGLCanvas::SetCurrent(*_geometryContext);
    
    clearSelection();
    
    if(_createNodes)
    {
        for(int i = 0; i < _editor.getNodeList()->size(); i++)
        {
            if(_editor.getNodeList()->at(i).getDistance(convertToXCoordinate(event.GetX()), convertToYCoordinate(event.GetY())) < 1 / (_zoomFactor * 10))// The multiplier will be some number between 10 and 100
            {
                if(_editor.setNodeIndex(i))
                {
                    
                    if(_createLines )
                    {
                        //Create the line
                        _editor.addLine();
                        _geometryIsSelected = false;
                        this->Refresh();
                        return;
                    }
                    else
                    {
                        arcSegmentDialog *newArcDialog;
                        if(_localDefinition->getPhysicsProblem() == physicProblems::PROB_ELECTROSTATIC)
                        {
                            arcSegmentDialog *newArcDialog = new arcSegmentDialog(this, _localDefinition->getElectricalBoundaryList());
                            if(newArcDialog->ShowModal() == wxID_OK)
                            {
                                arcShape tempShape;
                                newArcDialog->getArcParameter(tempShape);
                                _editor.addArc(tempShape, (_zoomFactor * 10), true);
                            }
                            else
                                _editor.resetIndexs();
                            delete(newArcDialog);
                        }
                        else if(_localDefinition->getPhysicsProblem() == physicProblems::PROB_MAGNETICS)
                        {
                           arcSegmentDialog *newArcDialog = new arcSegmentDialog(this, _localDefinition->getMagneticBoundaryList());
                            if(newArcDialog->ShowModal() == wxID_OK)
                            {
                                arcShape tempShape;
                                newArcDialog->getArcParameter(tempShape);
                                _editor.addArc(tempShape, (_zoomFactor * 10), true);
                            }
                            else
                                _editor.resetIndexs();
                            delete(newArcDialog);
                        }
                        _geometryIsSelected = false;
                        this->Refresh();
                        return;
                    }
                }
                else
                {
                    //Toggle the node to be selected
                    _editor.getNodeList()->at(i).setSelectState(true);
                    _geometryIsSelected = true;
                    this->Refresh();
                    return;
                }
            }
        }
        //Create the node at the point of the mouse with grid snapping
        if(_preferences.getSnapGridState())
        {
            double tempX = convertToXCoordinate(event.GetX());
            double tempY = convertToYCoordinate(event.GetY());
            roundToNearestGrid(tempX, tempY);
            _editor.addDragNode(tempX, tempY);
        }
        else
            _editor.addDragNode(convertToXCoordinate(event.GetX()), convertToYCoordinate(event.GetY()));
        
        _geometryIsSelected = false;
        _editor.resetIndexs();
        this->Refresh();// Draw the node at the mouse location
        return;
    }
    else
    {
        double tempX = convertToXCoordinate(event.GetX());
        double tempY = convertToYCoordinate(event.GetY());
        if(_preferences.getSnapGridState())
            roundToNearestGrid(tempX, tempY);
            
        _editor.addDragBlockLabel(tempX, tempY);

        this->Refresh();
        return;
    }
    
    this->Refresh();
    return;
}

void modelDefinition::onMouseLeftUp(wxMouseEvent &event)
{
    // OK so in order to re-validate the node (in order to break lines / arcs up into two pieces and what not), we first have to remove the last item, and then push it back on.
    if(_createNodes)
    {
        double tempX = convertToXCoordinate(event.GetX());
        double tempY = convertToYCoordinate(event.GetY());
        
        if(_preferences.getSnapGridState())
            roundToNearestGrid(tempX, tempY);

        if(_editor.getNodeList()->back().getDraggingState())
        {
            _editor.getNodeList()->pop_back();
            _editor.addNode(tempX, tempY);
        }
    }
    else
    {
        double tempX = convertToXCoordinate(event.GetX());
        double tempY = convertToYCoordinate(event.GetY());

        if(_preferences.getSnapGridState())
            roundToNearestGrid(tempX, tempY);

        if(_editor.getBlockLabelList()->back().getDraggingState())
        {
            _editor.getBlockLabelList()->pop_back(); 
            _editor.addBlockLabel(tempX, tempY);
        }
    }
    this->Refresh();
    return;
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
    double xCoordinate = convertToXCoordinate(event.GetX());
    double yCoordinate = convertToYCoordinate(event.GetY());
    
    /* these nodes are only meant to keep track of the number of shapes selected and to assist with setting the boolean _(geometryName)isSelected */
    static unsigned int nodesSeleted = 0;
    static unsigned int labelsSelected = 0;
    static unsigned int linesSelected = 0;
    static unsigned int arcsSelected = 0;

    if(_editor.getNodeList()->size() > 0)
    {
        for(std::vector<node>::iterator nodeIterator = _editor.getNodeList()->begin(); nodeIterator != _editor.getNodeList()->end(); ++nodeIterator)
        {
            if(nodeIterator->getDistance(xCoordinate, yCoordinate) < 1 / (_zoomFactor * 10))
            {
                // Add in code to remove previousely selected geometry that is different then the one already selected
                if(_linesAreSelected)
                {
                    for(std::vector<edgeLineShape>::iterator lineIterator = _editor.getLineList()->begin(); lineIterator != _editor.getLineList()->end(); ++lineIterator)
                    {
                        lineIterator->setSelectState(false);
                        linesSelected = 0;
                    }
                }
                else if(_arcsAreSelected)
                {
                   for(std::vector<arcShape>::iterator arcIterator = _editor.getArcList()->begin(); arcIterator != _editor.getArcList()->end(); ++arcIterator)
                    {
                        arcIterator->setSelectState(false);
                        arcsSelected = 0;
                    } 
                }
                else if(_labelsAreSelected)
                {
                   for(std::vector<blockLabel>::iterator blockIterator = _editor.getBlockLabelList()->begin(); blockIterator != _editor.getBlockLabelList()->end(); ++blockIterator)
                    {
                        blockIterator->setSelectState(false);
                        labelsSelected = 0;
                    } 
                }
                
                nodeIterator->setSelectState(!nodeIterator->getIsSelectedState());
                _nodesAreSelected = true;
                if(nodeIterator->getIsSelectedState())
                    nodesSeleted++;
                else
                {
                    nodesSeleted--;
                    if(nodesSeleted == 0)
                        _nodesAreSelected = false;
                }
                this->Refresh();
                return;
            }
        }
    }
    
    if(_editor.getBlockLabelList()->size() > 0)
    {
        for(std::vector<blockLabel>::iterator blockIterator = _editor.getBlockLabelList()->begin(); blockIterator != _editor.getBlockLabelList()->end(); ++blockIterator)
        {
            if(blockIterator->getDistance(xCoordinate, yCoordinate) < 1 / (_zoomFactor * 10))
            {
                if(_nodesAreSelected)
                {
                    for(std::vector<node>::iterator nodeIterator = _editor.getNodeList()->begin(); nodeIterator != _editor.getNodeList()->end(); ++nodeIterator)
                    {
                        nodeIterator->setSelectState(false);
                        nodesSeleted = 0;
                    }
                }
                else if(_arcsAreSelected)
                {
                   for(std::vector<arcShape>::iterator arcIterator = _editor.getArcList()->begin(); arcIterator != _editor.getArcList()->end(); ++arcIterator)
                    {
                        arcIterator->setSelectState(false);
                        arcsSelected = 0;
                    } 
                }
                else if(_linesAreSelected)
                {
                    for(std::vector<edgeLineShape>::iterator lineIterator = _editor.getLineList()->begin(); lineIterator != _editor.getLineList()->end(); ++lineIterator)
                    {
                        lineIterator->setSelectState(false);
                        linesSelected = 0;
                    }
                }
                
                _labelsAreSelected = true;
                blockIterator->setSelectState(!blockIterator->getIsSelectedState());
                
                if(blockIterator->getIsSelectedState())
                    labelsSelected++;
                else
                {
                    labelsSelected--;
                    if(labelsSelected == 0)
                        _labelsAreSelected = false;
                }
                
                
                this->Refresh();
                return;
            }
        }
    }
    
    if(_editor.getLineList()->size() > 0)
    {
        for(std::vector<edgeLineShape>::iterator lineIterator = _editor.getLineList()->begin(); lineIterator != _editor.getLineList()->end(); ++lineIterator)
        {
            if(_editor.calculateShortestDistance(xCoordinate, yCoordinate, *lineIterator) < 1 / (_zoomFactor * 10))
            {
                if(_nodesAreSelected)
                {
                    for(std::vector<node>::iterator nodeIterator = _editor.getNodeList()->begin(); nodeIterator != _editor.getNodeList()->end(); ++nodeIterator)
                    {
                        nodeIterator->setSelectState(false);
                        nodesSeleted = 0;
                    }
                }
                else if(_arcsAreSelected)
                {
                   for(std::vector<arcShape>::iterator arcIterator = _editor.getArcList()->begin(); arcIterator != _editor.getArcList()->end(); ++arcIterator)
                    {
                        arcIterator->setSelectState(false);
                        arcsSelected = 0;
                    } 
                }
                else if(_labelsAreSelected)
                {
                   for(std::vector<blockLabel>::iterator blockIterator = _editor.getBlockLabelList()->begin(); blockIterator != _editor.getBlockLabelList()->end(); ++blockIterator)
                    {
                        blockIterator->setSelectState(false);
                        labelsSelected = 0;
                    } 
                }
                
                _linesAreSelected = true;
                
                lineIterator->setSelectState(!lineIterator->getIsSelectedState());
                
                if(lineIterator->getIsSelectedState())
                    linesSelected++;
                else
                {
                    linesSelected--;
                    if(linesSelected == 0)
                        _linesAreSelected = false;
                }
                
                this->Refresh();
                return;
            }
        }
    }
    
    if(_editor.getArcList()->size() > 0)
    {
        for(std::vector<arcShape>::iterator arcIterator = _editor.getArcList()->begin(); arcIterator != _editor.getArcList()->end(); ++arcIterator)
        {
            if(_editor.calculateShortestDistanceFromArc(*arcIterator, xCoordinate, yCoordinate) < 1 / (_zoomFactor * 10))
            {
                if(_nodesAreSelected)
                {
                    for(std::vector<node>::iterator nodeIterator = _editor.getNodeList()->begin(); nodeIterator != _editor.getNodeList()->end(); ++nodeIterator)
                    {
                        nodeIterator->setSelectState(false);
                        nodesSeleted = 0;
                    }
                }
                else if(_linesAreSelected)
                {
                    for(std::vector<edgeLineShape>::iterator lineIterator = _editor.getLineList()->begin(); lineIterator != _editor.getLineList()->end(); ++lineIterator)
                    {
                        lineIterator->setSelectState(false);
                        linesSelected = 0;
                    }
                }
                else if(_labelsAreSelected)
                {
                   for(std::vector<blockLabel>::iterator blockIterator = _editor.getBlockLabelList()->begin(); blockIterator != _editor.getBlockLabelList()->end(); ++blockIterator)
                    {
                        blockIterator->setSelectState(false);
                        labelsSelected = 0;
                    } 
                }
                
                _arcsAreSelected = true;
                
                arcIterator->setSelectState(!arcIterator->getIsSelectedState());
                
                if(arcIterator->getIsSelectedState())
                    arcsSelected++;
                else
                {
                    arcsSelected--;
                    if(arcsSelected == 0)
                        _arcsAreSelected = false;
                }
                
                this->Refresh();
                return;
            }
        }
    }
    
    /* This section is for if the user clicks on empty white space */
    if(_nodesAreSelected)
    {
        for(std::vector<node>::iterator nodeIterator = _editor.getNodeList()->begin(); nodeIterator != _editor.getNodeList()->end(); ++nodeIterator)
        {
            nodeIterator->setSelectState(false);
        }
        nodesSeleted = 0;
        _nodesAreSelected = false;
        this->Refresh();
        return;
    }
    else if(_linesAreSelected)
    {
        for(std::vector<edgeLineShape>::iterator lineIterator = _editor.getLineList()->begin(); lineIterator != _editor.getLineList()->end(); ++lineIterator)
        {
            lineIterator->setSelectState(false);
        }
        linesSelected = 0;
        _linesAreSelected = false;
        this->Refresh();
        return;
    }
    else if(_labelsAreSelected)
    {
       for(std::vector<blockLabel>::iterator blockIterator = _editor.getBlockLabelList()->begin(); blockIterator != _editor.getBlockLabelList()->end(); ++blockIterator)
        {
            blockIterator->setSelectState(false);
        }
        labelsSelected = 0;
        _labelsAreSelected = false;
        this->Refresh();
        return; 
    }
    else if(_arcsAreSelected)
    {
       for(std::vector<arcShape>::iterator arcIterator = _editor.getArcList()->begin(); arcIterator != _editor.getArcList()->end(); ++arcIterator)
        {
            arcIterator->setSelectState(false);
        }
        arcsSelected = 0;
        _arcsAreSelected = false;
        this->Refresh();
        return;
    }
    
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
}




void modelDefinition::onKeyDown(wxKeyEvent &event)
{
    if(event.GetKeyCode() == DEL_KEY || event.GetKeyCode() == LETTER_d)
    {
        deleteSelection();
    }
    else if(event.GetKeyCode() == LETTER_e)
    {
        editSelection();
    }
    else if(event.GetKeyCode() == LETTER_b)
        _createNodes = !_createNodes;
    else if(event.GetKeyCode() == LETTER_a)
        _createLines = !_createLines;
}



wxBEGIN_EVENT_TABLE(modelDefinition, wxGLCanvas)
    EVT_PAINT(modelDefinition::onPaintCanvas)
    EVT_SIZE(modelDefinition::onResize)
    EVT_ENTER_WINDOW(modelDefinition::onEnterWindow)
    EVT_KEY_DOWN(modelDefinition::onKeyDown)
    /* This section is the event procedure for the mouse controls */
    EVT_MOUSEWHEEL(modelDefinition::onMouseWheel)
    EVT_MOTION(modelDefinition::onMouseMove)
    EVT_LEFT_DOWN(modelDefinition::onMouseLeftDown)
    EVT_LEFT_UP(modelDefinition::onMouseLeftUp)
    EVT_RIGHT_DOWN(modelDefinition::onMouseRightDown)
wxEND_EVENT_TABLE()