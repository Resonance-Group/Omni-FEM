#include <UI/ModelDefinition/ModelDefinition.h>

wxDEFINE_EVENT(MOUSE_MOVE, wxCommandEvent);

modelDefinition::modelDefinition(wxWindow *par, const wxPoint &point, const wxSize &size, problemDefinition &definition, wxStatusBarBase *statusBar) : wxGLCanvas(par, wxID_ANY, NULL, point, size, wxBORDER_DOUBLE | wxBORDER_RAISED)
{
    _geometryContext = new wxGLContext(this);
	wxGLCanvas::SetCurrent(*_geometryContext);
    wxPaintDC dc(this);
    
    _localDefinition = &definition;
    _statusBarTopWindow = statusBar;
    
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
		return;
	}
    
    glMatrixMode(GL_MODELVIEW);
        
    _fontRender = new OGLFT::Grayscale("/usr/share/fonts/truetype/dejavu/DejaVuSansMono.ttf", 8);
}



void modelDefinition::deleteSelection()
{
    /* This section is for iterating through all of the nodes */
    for(plf::colony<node>::iterator nodeIterator = _editor.getNodeList()->begin(); nodeIterator != _editor.getNodeList()->end();)
    {
        if(nodeIterator->getIsSelectedState())
        {
            /* Need to cycle through the entire line list and arc list in order to determine which arc/line the node is associated with and delete that arc/line by selecting i.
             * The deletion of the arc/line occurs later in the code*/
            
            for(plf::colony<edgeLineShape>::iterator lineIterator = _editor.getLineList()->begin(); lineIterator != _editor.getLineList()->end(); ++lineIterator)
            {
                if(*lineIterator->getFirstNode() == *nodeIterator || *lineIterator->getSecondNode() == *nodeIterator)
                    lineIterator->setSelectState(true);
            }

            for(plf::colony<arcShape>::iterator arcIterator = _editor.getArcList()->begin(); arcIterator != _editor.getArcList()->end(); ++arcIterator)
            {
                if(*arcIterator->getFirstNode() == *nodeIterator || *arcIterator->getSecondNode() == *nodeIterator)
                    arcIterator->setSelectState(true);
            }
            
            if(nodeIterator == _editor.getNodeList()->back())
            {
                _editor.getNodeList()->erase(nodeIterator);
                break;
            }
            else
            {
                /* Bug Fix: This applies for all of the other geometry shapes
                * At first, the for loop was for(plf::colony<node>::iterator nodeIterator = _editor.getNodeList()->begin(); nodeIterator != _editor.getNodeList()->end(); ++nodeIterator)
                * This creates issue at this line because orginally, the line was _editor.getNodeList()->erase(nodeIterator);. For the plf::colony class, when
                * an element is erased, it invalidates the element. For the iterators, since the iterator is pointing to the element that was just erased, nodeIterator is now
                * pointing to an invalidated element in the colony object.
                * The fix is to have the nodeIterator be incremented first and then pass in the value of nodeIterator before the increment.
                * This way the nodeIterator will never be pointing to an invalidated element.
                */ 
                _editor.getNodeList()->erase(nodeIterator++);
            }

            if(_editor.getNodeList()->size() == 0)
                break;
        }
        else
            nodeIterator++;
            
    }
    
    /* This section is for deleting all of the arcs */
    for(plf::colony<arcShape>::iterator arcIterator = _editor.getArcList()->begin(); arcIterator != _editor.getArcList()->end();)
    {
        if(arcIterator->getIsSelectedState())
        {
            if(arcIterator == _editor.getArcList()->back())
            {
                _editor.getArcList()->erase(arcIterator);
                break;
            }
            else
                _editor.getArcList()->erase(arcIterator++);
            
            if(_editor.getArcList()->size() == 0)
                break;
        }
        else
            arcIterator++;
    }
    
    /* This section is for deleting all of the lines */
    for(plf::colony<edgeLineShape>::iterator lineIterator = _editor.getLineList()->begin(); lineIterator != _editor.getLineList()->end();)
    {
        if(lineIterator->getIsSelectedState())
        {
            /* Bug fix: At first the code did not check if the line iterator was on the back
             * This causes problems becuase if the last iterator was deleted, then we are incrementing an invalidated iterator
             * which creates another invalidated iterator that is not equal to the end iterator of the list.
             * When you erase an invalidated iterator, the program crashes.
             * The same logic applies for the other geometry shapes
             */ 
            if(lineIterator == _editor.getLineList()->back())
            {
                _editor.getLineList()->erase(lineIterator);
                break;
            }
            else
                _editor.getLineList()->erase(lineIterator++);
            
            if(_editor.getLineList()->size() == 0)
                break;
        }
        else
            lineIterator++;
    }
    
    /* This section is for deleting all of the labels */
    for(plf::colony<blockLabel>::iterator blockIterator = _editor.getBlockLabelList()->begin(); blockIterator != _editor.getBlockLabelList()->end();)
    {
        if(blockIterator->getIsSelectedState())
        {
            if(blockIterator == _editor.getBlockLabelList()->back())
            {
                _editor.getBlockLabelList()->erase(blockIterator);
                break;
            }
            else
                _editor.getBlockLabelList()->erase(blockIterator++);
            
            if(_editor.getBlockLabelList()->size() == 0)
                break;
        }
        else
            blockIterator++;
    }
    
    this->Refresh();
    return;
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
        for(plf::colony<node>::iterator nodeIterator = _editor.getNodeList()->begin(); nodeIterator != _editor.getNodeList()->end(); ++nodeIterator)
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
            for(plf::colony<node>::iterator nodeIterator = _editor.getNodeList()->begin(); nodeIterator != _editor.getNodeList()->end(); ++nodeIterator)
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
        segmentPropertyDialog *dialog;
        segmentProperty selectedProperty;
        
        for(plf::colony<edgeLineShape>::iterator lineIterator = _editor.getLineList()->begin(); lineIterator != _editor.getLineList()->end(); ++lineIterator)
        {
            if(lineIterator->getIsSelectedState())
            {
                selectedProperty = *lineIterator->getSegmentProperty();
                break;
            }
        }
        
        if(_localDefinition->getPhysicsProblem() == physicProblems::PROB_ELECTROSTATIC)
            dialog = new segmentPropertyDialog(this, *_localDefinition->getElectricalBoundaryList(), *_localDefinition->getConductorList(), selectedProperty, false);
        else if(_localDefinition->getPhysicsProblem() == physicProblems::PROB_MAGNETICS)
            dialog = new segmentPropertyDialog(this, *_localDefinition->getMagneticBoundaryList(), selectedProperty, false);
            
        if(dialog->ShowModal() == wxID_OK)
        {
            dialog->getSegmentProperty(selectedProperty);
            
            for(plf::colony<edgeLineShape>::iterator lineIterator = _editor.getLineList()->begin(); lineIterator != _editor.getLineList()->end(); ++lineIterator)
            {
                if(lineIterator->getIsSelectedState())
                    lineIterator->setSegmentProperty(selectedProperty);
            }
        }
        _editor.checkIntersections(EditGeometry::EDIT_LINES, getTolerance());// This is mainly for if a line moved from being hidden to being real
        delete(dialog);
    }
    else if(_arcsAreSelected)
    {
        segmentPropertyDialog *dialog;
        segmentProperty selectedProperty;
        
        for(plf::colony<arcShape>::iterator arcIterator = _editor.getArcList()->begin(); arcIterator != _editor.getArcList()->end(); ++arcIterator)
        {
            if(arcIterator->getIsSelectedState())
            {
                selectedProperty = *arcIterator->getSegmentProperty();
                break;
            }
        }
        
        if(_localDefinition->getPhysicsProblem() == physicProblems::PROB_ELECTROSTATIC)
            dialog = new segmentPropertyDialog(this, *_localDefinition->getElectricalBoundaryList(), *_localDefinition->getConductorList(), selectedProperty, true);
        else if(_localDefinition->getPhysicsProblem() == physicProblems::PROB_MAGNETICS)
            dialog = new segmentPropertyDialog(this, *_localDefinition->getMagneticBoundaryList(), selectedProperty, true);
            
        if(dialog->ShowModal() == wxID_OK)
        {
            dialog->getSegmentProperty(selectedProperty);
            
            for(plf::colony<arcShape>::iterator arcIterator = _editor.getArcList()->begin(); arcIterator != _editor.getArcList()->end(); ++arcIterator)
            {
                if(arcIterator->getIsSelectedState())
                    arcIterator->setSegmentProperty(selectedProperty);
            }
        }
        _editor.checkIntersections(EditGeometry::EDIT_ARCS, getTolerance());
        delete(dialog);
    }
    else if(_labelsAreSelected)
    {
        blockPropertyDialog *dialog;
        blockProperty selectedBlockLabel;
        
        for(plf::colony<blockLabel>::iterator blockIterator = _editor.getBlockLabelList()->begin(); blockIterator != _editor.getBlockLabelList()->end(); ++blockIterator)
        {
            if(blockIterator->getIsSelectedState())
            {
                selectedBlockLabel = *blockIterator->getProperty();
                break;
            }
        }
        
        if(_localDefinition->getPhysicsProblem() == physicProblems::PROB_ELECTROSTATIC)
            dialog = new blockPropertyDialog(this, _localDefinition->getElectricalMaterialList(), selectedBlockLabel, _localDefinition->getElectricalPreferences().isAxistmmetric());
        else if(_localDefinition->getPhysicsProblem() == physicProblems::PROB_MAGNETICS)
            dialog = new blockPropertyDialog(this, _localDefinition->getMagnetMaterialList(), _localDefinition->getCircuitList(), selectedBlockLabel, _localDefinition->getMagneticPreference().isAxistmmetric());

        if(dialog->ShowModal() == wxID_OK)
        {
            bool firstIsSet = false;
            dialog->getBlockProperty(selectedBlockLabel);
            
            for(plf::colony<blockLabel>::iterator blockIterator = _editor.getBlockLabelList()->begin(); blockIterator != _editor.getBlockLabelList()->end(); ++blockIterator)
            {
                /* This will clear the default flag of the block label no matter what. If the user did select the label
                 * to be the defualt, then in the next few lines the program will set that flag to the block label
                 * since we copy the user set parameters and place them into the block label
                 */ 
                if(selectedBlockLabel.getDefaultState())
                    blockIterator->getProperty()->setDefaultState(false);
                    
                if(blockIterator->getIsSelectedState())
                {
                    blockIterator->setPorperty(selectedBlockLabel);
                    // This will ensure that only 1 block at a time will be set to default state
                    if(firstIsSet)
                        blockIterator->getProperty()->setDefaultState(false);
                    firstIsSet = true;
                }
            }
        }
        delete(dialog);
    }
    else if(_geometryGroupIsSelected)
    {
        unsigned int groupNumber;
        editGroupNumberDialog *dialog;
        // Create a dialog which will only allow the user to change the group number of all selected geometry
        // The nodes are selected as the geometry to get the group number becuase if lines/arcs are seleted, then their two nodes need to be selected as well
        for(plf::colony<node>::iterator nodeIterator = _editor.getNodeList()->begin(); nodeIterator != _editor.getNodeList()->end(); ++nodeIterator)
        {
            if(nodeIterator->getIsSelectedState())
            {
                groupNumber = nodeIterator->getNodeSetting()->getGroupNumber();
                break;
            }
        }
        
        dialog = new editGroupNumberDialog(this, groupNumber);
        
        if(dialog->ShowModal() == wxID_OK)
        {
            groupNumber = dialog->getGroupNumber();
            
            // Iterate through everything that is selected and set the group number to the one that the user selected
            for(plf::colony<node>::iterator nodeIterator = _editor.getNodeList()->begin(); nodeIterator != _editor.getNodeList()->end(); ++nodeIterator)
            {
                if(nodeIterator->getIsSelectedState())
                    nodeIterator->getNodeSetting()->setGroupNumber(groupNumber);
            }
            
            for(plf::colony<blockLabel>::iterator blockIterator = _editor.getBlockLabelList()->begin(); blockIterator != _editor.getBlockLabelList()->end(); ++blockIterator)
            {
                if(blockIterator->getIsSelectedState())
                    blockIterator->getProperty()->setGroupNumber(groupNumber);
            }
            
            for(plf::colony<arcShape>::iterator arcIterator = _editor.getArcList()->begin(); arcIterator != _editor.getArcList()->end(); ++arcIterator)
            {
                if(arcIterator->getIsSelectedState())
                    arcIterator->getSegmentProperty()->setGroupNumber(groupNumber);
            }
            
            for(plf::colony<edgeLineShape>::iterator lineIterator = _editor.getLineList()->begin(); lineIterator != _editor.getLineList()->end(); ++lineIterator)
            {
                if(lineIterator->getIsSelectedState())
                    lineIterator->getSegmentProperty()->setGroupNumber(groupNumber);
            }
        }
    }
    
    
    this->Refresh();
    return;
}



void modelDefinition::updateProperties(EditProperty property)
{
    switch(property)
    {
        case EditProperty::EDIT_CONDUCTOR:
        {
            for(plf::colony<node>::iterator nodeIterator = _editor.getNodeList()->begin(); nodeIterator != _editor.getNodeList()->end(); ++nodeIterator)
            {
                bool conductorPropertyIsPresent = false;
                if(nodeIterator->getNodeSetting()->getConductorPropertyName() != "None" && _localDefinition->getConductorList() != nullptr)
                {
                    for(int i = 0; i < _localDefinition->getConductorList()->size(); i++)
                    {
                        if(nodeIterator->getNodeSetting()->getConductorPropertyName() == _localDefinition->getConductorList()->at(i).getName())
                        {
                            conductorPropertyIsPresent = true;
                            break;
                        }
                    }
                    if(!conductorPropertyIsPresent)
                        nodeIterator->getNodeSetting()->setConductorPropertyName("None");
                }
            }
            
            for(plf::colony<edgeLineShape>::iterator lineIterator = _editor.getLineList()->begin(); lineIterator != _editor.getLineList()->end(); ++lineIterator)
            {
                bool conductorPropertyIsPresent = false;
                if(lineIterator->getSegmentProperty()->getConductorName() != "None" && _localDefinition->getConductorList() != nullptr)
                {
                    for(int i = 0; i < _localDefinition->getConductorList()->size(); i++)
                    {
                        if(lineIterator->getSegmentProperty()->getConductorName() == _localDefinition->getConductorList()->at(i).getName() && !conductorPropertyIsPresent)
                        {
                            conductorPropertyIsPresent = true;
                            break;
                        }
                    }
                    
                    if(!conductorPropertyIsPresent)
                        lineIterator->getSegmentProperty()->setConductorName("None");
                }
            }
            
            for(plf::colony<arcShape>::iterator arcIterator = _editor.getArcList()->begin(); arcIterator != _editor.getArcList()->end(); ++arcIterator)
            {
                bool conductorPropertyIsPresent = false;
                if(arcIterator->getSegmentProperty()->getConductorName() != "None" && _localDefinition->getConductorList() != nullptr)
                {
                    for(int i = 0; i < _localDefinition->getConductorList()->size(); i++)
                    {
                        if(arcIterator->getSegmentProperty()->getConductorName() == _localDefinition->getConductorList()->at(i).getName() && !conductorPropertyIsPresent)
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
        break;
        case EditProperty::EDIT_NODAL:
        {
            for(plf::colony<node>::iterator nodeIterator = _editor.getNodeList()->begin(); nodeIterator != _editor.getNodeList()->end(); ++nodeIterator)
            {
                bool nodalPropertyIsPresent = false;
                if(nodeIterator->getNodeSetting()->getNodalPropertyName() != "None")
                {
                    for(int i = 0; i < _localDefinition->getNodalPropertyList()->size(); i++)
                    {
                        // THis section will take the nodeIterator object and comapre it against each property that is related to the node. It will only compare against the name
                        // IF the problem is electrostatics, we will also compare against the conductor property.
                        // IF the property name is found in the master list, the loop will break and move onto the next node object.
                        // If not, then the property name within the node object will be changed back to none.
                        // This logic continues for the other geometry shape cases
                        if(nodeIterator->getNodeSetting()->getNodalPropertyName() == _localDefinition->getNodalPropertyList()->at(i).getName() && !nodalPropertyIsPresent)
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
        break;
        case EditProperty::EDIT_BOUNDARY:
        {
            for(plf::colony<edgeLineShape>::iterator lineIterator = _editor.getLineList()->begin(); lineIterator != _editor.getLineList()->end(); ++lineIterator)
            {
                bool boundaryIsPresent = false;
                if(_localDefinition->getPhysicsProblem() == physicProblems::PROB_ELECTROSTATIC && _localDefinition->getElectricalBoundaryList() != nullptr)
                {
                    if(lineIterator->getSegmentProperty()->getBoundaryName() != "None")
                    {
                        for(int i = 0; i < _localDefinition->getElectricalBoundaryList()->size(); i++)
                        {
                            if(lineIterator->getSegmentProperty()->getBoundaryName() == _localDefinition->getElectricalBoundaryList()->at(i).getBoundaryName() && !boundaryIsPresent)
                            {
                                boundaryIsPresent = true;
                                break;
                            }
                        }
                        
                        if(!boundaryIsPresent)
                            lineIterator->getSegmentProperty()->setBoundaryName("None");
                    }
                }
                else if (_localDefinition->getPhysicsProblem() == physicProblems::PROB_MAGNETICS && _localDefinition->getElectricalBoundaryList() != nullptr)
                {
                    bool boundaryIsPresent = false;
                    if(lineIterator->getSegmentProperty()->getBoundaryName() != "None")
                    {
                        for(int i = 0; i < _localDefinition->getMagneticBoundaryList()->size(); i++)
                        {
                            if(lineIterator->getSegmentProperty()->getBoundaryName() == _localDefinition->getElectricalBoundaryList()->at(i).getBoundaryName())
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
            
            for(plf::colony<arcShape>::iterator arcIterator = _editor.getArcList()->begin(); arcIterator != _editor.getArcList()->end(); ++arcIterator)
            {
                bool boundaryIsPresent = false;
                if(_localDefinition->getPhysicsProblem() == physicProblems::PROB_ELECTROSTATIC && _localDefinition->getElectricalBoundaryList() != nullptr)
                {
                    if(arcIterator->getSegmentProperty()->getBoundaryName() != "None")
                    {
                        for(int i = 0; i < _localDefinition->getElectricalBoundaryList()->size(); i++)
                        {
                            if(arcIterator->getSegmentProperty()->getBoundaryName() == _localDefinition->getElectricalBoundaryList()->at(i).getBoundaryName() && !boundaryIsPresent)
                            {
                                boundaryIsPresent = true;
                                break;
                            }
                        }
                        
                        if(!boundaryIsPresent)
                            arcIterator->getSegmentProperty()->setBoundaryName("None");
                    }
                }
                else if (_localDefinition->getPhysicsProblem() == physicProblems::PROB_MAGNETICS && _localDefinition->getElectricalBoundaryList() != nullptr)
                {
                    bool boundaryIsPresent = false;
                    if(arcIterator->getSegmentProperty()->getBoundaryName() != "None")
                    {
                        for(int i = 0; i < _localDefinition->getMagneticBoundaryList()->size(); i++)
                        {
                            if(arcIterator->getSegmentProperty()->getBoundaryName() == _localDefinition->getElectricalBoundaryList()->at(i).getBoundaryName())
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
        break;
        case EditProperty::EDIT_MATERIAL:
        {
            for(plf::colony<blockLabel>::iterator blockIterator = _editor.getBlockLabelList()->begin(); blockIterator != _editor.getBlockLabelList()->end(); ++blockIterator)
            {
                bool materialIsPresent = false;
                
                switch(_localDefinition->getPhysicsProblem())
                {
                    case physicProblems::PROB_ELECTROSTATIC:
                    {
                        if(_localDefinition->getElectricalMaterialList() != nullptr)
                        {
                            if(blockIterator->getProperty()->getMaterialName() != "None")
                            {
                                for(int i = 0; i < _localDefinition->getElectricalMaterialList()->size(); i++)
                                {
                                    if(blockIterator->getProperty()->getMaterialName() == _localDefinition->getElectricalMaterialList()->at(i).getName())
                                    {
                                        materialIsPresent = true;
                                        break;
                                    }
                                }
                                
                                if(!materialIsPresent)
                                    blockIterator->getProperty()->setMaterialName("None");
                            }
                        }
                    }
                    break;
                    case physicProblems::PROB_MAGNETICS:
                    {
                        if(_localDefinition->getMagnetMaterialList() != nullptr)
                        {
                            if(blockIterator->getProperty()->getMaterialName() != "None")
                            {
                                for(int i = 0; i < _localDefinition->getMagnetMaterialList()->size(); i++)
                                {
                                    if(blockIterator->getProperty()->getMaterialName() == _localDefinition->getMagnetMaterialList()->at(i).getName())
                                    {
                                        materialIsPresent = true;
                                        break;
                                    }
                                }
                                
                                if(!materialIsPresent)
                                    blockIterator->getProperty()->setMaterialName("None");
                            }
                        }
                    }
                    break;
                    default:
                        break;
                }
            }
        }
        break;
        case EditProperty::EDIT_CIRCUIT:
        {
            for(plf::colony<blockLabel>::iterator blockIterator = _editor.getBlockLabelList()->begin(); blockIterator != _editor.getBlockLabelList()->end(); ++blockIterator)
            {
                bool circuitIsPresent = false;
                if(blockIterator->getProperty()->getCircuitName() != "None" && _localDefinition->getConductorList() != nullptr)
                {
                    for(int i = 0; i < _localDefinition->getCircuitList()->size(); i++)
                    {
                        if(blockIterator->getProperty()->getCircuitName() == _localDefinition->getCircuitList()->at(i).getName())
                        {
                            circuitIsPresent = true;
                            break;
                        }
                    }
                    
                    if(!circuitIsPresent)
                        blockIterator->getProperty()->setCircuitName("None");
                }
            }
        }
        break;
        default:
            break;
    }
}


void modelDefinition::selectGroup(EditGeometry geometry, unsigned int groupNumber)
{
    clearSelection();
    
    switch(geometry)
    {
        case EditGeometry::EDIT_NODES:
            for(plf::colony<node>::iterator nodeIterator = _editor.getNodeList()->begin(); nodeIterator != _editor.getNodeList()->end(); ++nodeIterator)
            {
                if(nodeIterator->getNodeSetting()->getGroupNumber() == groupNumber)
                {
                    nodeIterator->setSelectState(true);
                    _nodesAreSelected = true;
                }
            }
            break;
            
        case EditGeometry::EDIT_LINES:
            for(plf::colony<edgeLineShape>::iterator lineIterator = _editor.getLineList()->begin(); lineIterator != _editor.getLineList()->end(); ++lineIterator)
            {
                if(lineIterator->getSegmentProperty()->getGroupNumber() == groupNumber)
                {
                    lineIterator->setSelectState(true);
                    _linesAreSelected = true;
                }
            }
            break;
            
        case EditGeometry::EDIT_ARCS:
            for(plf::colony<arcShape>::iterator arcIterator = _editor.getArcList()->begin(); arcIterator != _editor.getArcList()->end(); ++arcIterator)
            {
                if(arcIterator->getSegmentProperty()->getGroupNumber() == groupNumber)
                {
                    arcIterator->setSelectState(true);
                    _arcsAreSelected = true;
                }
            }
            break;
        
        case EditGeometry::EDIT_LABELS:
            for(plf::colony<blockLabel>::iterator blockIterator = _editor.getBlockLabelList()->begin(); blockIterator != _editor.getBlockLabelList()->end(); ++blockIterator)
            {
                if(blockIterator->getProperty()->getGroupNumber() == groupNumber)
                {
                    blockIterator->setSelectState(true);
                    _labelsAreSelected = true;
                }
            }             
            break;

        case EditGeometry::EDIT_ALL:
            _geometryGroupIsSelected = true;
            
            for(plf::colony<node>::iterator nodeIterator = _editor.getNodeList()->begin(); nodeIterator != _editor.getNodeList()->end(); ++nodeIterator)
            {
                if(nodeIterator->getNodeSetting()->getGroupNumber() == groupNumber)
                {
                    nodeIterator->setSelectState(true);
                }
            }
            
            for(plf::colony<edgeLineShape>::iterator lineIterator = _editor.getLineList()->begin(); lineIterator != _editor.getLineList()->end(); ++lineIterator)
            {
                if(lineIterator->getSegmentProperty()->getGroupNumber() == groupNumber)
                {
                    lineIterator->setSelectState(true);
                }
            }
            
            for(plf::colony<arcShape>::iterator arcIterator = _editor.getArcList()->begin(); arcIterator != _editor.getArcList()->end(); ++arcIterator)
            {
                if(arcIterator->getSegmentProperty()->getGroupNumber() == groupNumber)
                {
                    arcIterator->setSelectState(true);
                }
            }
            
            for(plf::colony<blockLabel>::iterator blockIterator = _editor.getBlockLabelList()->begin(); blockIterator != _editor.getBlockLabelList()->end(); ++blockIterator)
            {
                if(blockIterator->getProperty()->getGroupNumber() == groupNumber)
                {
                    blockIterator->setSelectState(true);
                }
            } 
            break;
        default:
            break;
    }

    
    this->Refresh();
    return;
}



void modelDefinition::moveTranslateSelection(double horizontalShift, double verticalShift)
{
    // First, we are going to scan through all of the lines/arcs and check the nodes that are to be moved (and uncheck all of the lines/arcs)
    
    if(!_geometryGroupIsSelected)
    {
        if(_arcsAreSelected)
        {
            for(plf::colony<arcShape>::iterator arcIterator = _editor.getArcList()->begin(); arcIterator != _editor.getArcList()->end(); ++arcIterator)
            {
                if(arcIterator->getIsSelectedState())
                {
                    arcIterator->getFirstNode()->setSelectState(true);
                    arcIterator->getSecondNode()->setSelectState(true);
                    arcIterator->setSelectState(false);
                }
            }
            _arcsAreSelected = false;
        }
        else if(_linesAreSelected)
        {
            for(plf::colony<edgeLineShape>::iterator lineIterator = _editor.getLineList()->begin(); lineIterator != _editor.getLineList()->end(); ++lineIterator)
            {
                if(lineIterator->getIsSelectedState())
                {
                    lineIterator->getFirstNode()->setSelectState(true);
                    lineIterator->getSecondNode()->setSelectState(true);
                    lineIterator->setSelectState(false);
                }
            }
             _linesAreSelected = false;
        }
        
    }
    else 
    {
        // If mixed geometery is selected then lets go ahead and move all of the nodes that are associated with the lines and arcs.
        // Also check to make sure that the node is actually selected for moving. If it is, then move it and deselect the node
        for(plf::colony<arcShape>::iterator arcIterator = _editor.getArcList()->begin(); arcIterator != _editor.getArcList()->end(); ++arcIterator)
        {
            if(arcIterator->getIsSelectedState())
            {
                if(arcIterator->getFirstNode()->getIsSelectedState())
                {
                    arcIterator->getFirstNode()->moveCenter(horizontalShift, verticalShift);
                    arcIterator->getFirstNode()->setSelectState(false);
                }
                
                if(arcIterator->getSecondNode()->getIsSelectedState())
                {
                    arcIterator->getSecondNode()->moveCenter(horizontalShift, verticalShift);
                    arcIterator->getSecondNode()->setSelectState(false);
                }
                arcIterator->setSelectState(false);
                arcIterator->calculate(); // The center and radius of the arc will need to be recalculated after it is moved
            }
        }
        
        
        
        for(plf::colony<edgeLineShape>::iterator lineIterator = _editor.getLineList()->begin(); lineIterator != _editor.getLineList()->end(); ++lineIterator)
        {
            if(lineIterator->getIsSelectedState())
            {
                if(lineIterator->getFirstNode()->getIsSelectedState())
                {
                    lineIterator->getFirstNode()->moveCenter(horizontalShift, verticalShift);
                    lineIterator->getFirstNode()->setSelectState(false);
                }
                
                if(lineIterator->getSecondNode()->getIsSelectedState())
                {
                    lineIterator->getSecondNode()->moveCenter(horizontalShift, verticalShift);
                    lineIterator->getSecondNode()->setSelectState(false);
                }
                lineIterator->setSelectState(false);
            }
        }
    }
    
    if(_labelsAreSelected || _geometryGroupIsSelected)
    {
        for(plf::colony<blockLabel>::iterator blockIterator = _editor.getBlockLabelList()->begin(); blockIterator != _editor.getBlockLabelList()->end(); ++blockIterator)
        {
            if(blockIterator->getIsSelectedState())
            {
                blockIterator->moveCenter(horizontalShift, verticalShift);
                blockIterator->setSelectState(false);
            }
        }
        _labelsAreSelected = false;
    }
    
    
    // Now we want to go ahead and move any of the selected nodes
    for(plf::colony<node>::iterator nodeIterator = _editor.getNodeList()->begin(); nodeIterator != _editor.getNodeList()->end(); ++nodeIterator)
    {
        if(nodeIterator->getIsSelectedState())
        {
            // Update the node with the translated coordinates
            nodeIterator->moveCenter(horizontalShift, verticalShift);
            nodeIterator->setSelectState(false);
        }
        
        // After moving the nodes, we need to then make sure all of the arcs have been updated with the new node positions
        for(plf::colony<arcShape>::iterator arcIterator = _editor.getArcList()->begin(); arcIterator != _editor.getArcList()->end(); ++arcIterator)
        {
            if(*arcIterator->getFirstNode() == *nodeIterator || *arcIterator->getSecondNode() == *nodeIterator)
            {
                arcIterator->calculate(); // The center and radius of the arc will need to be recalculated after one of the nodes has moved
            }
        }
    }
    
    _labelsAreSelected = _editor.checkIntersections(EditGeometry::EDIT_ALL, getTolerance());
    
    _geometryGroupIsSelected = false;
    _nodesAreSelected = false;
    
    this->Refresh();
    return;
}



void modelDefinition::moveRotateSelection(double angularShift, wxRealPoint aboutPoint)
{
    if(!_geometryGroupIsSelected)
    {
        // If we have a specific type of geometry selected, mark the corresponding nodes for moving and deselect the actual geometry
        if(_arcsAreSelected)
        {
            for(plf::colony<arcShape>::iterator arcIterator = _editor.getArcList()->begin(); arcIterator != _editor.getArcList()->end(); ++arcIterator)
            {
                if(arcIterator->getIsSelectedState())
                {
                    arcIterator->getFirstNode()->setSelectState(true);
                    arcIterator->getSecondNode()->setSelectState(true);
                    arcIterator->setSelectState(false);
                }
            }
            _arcsAreSelected = false;
        }
        else if(_linesAreSelected)
        {
            for(plf::colony<edgeLineShape>::iterator lineIterator = _editor.getLineList()->begin(); lineIterator != _editor.getLineList()->end(); ++lineIterator)
            {
                if(lineIterator->getIsSelectedState())
                {
                    lineIterator->getFirstNode()->setSelectState(true);
                    lineIterator->getSecondNode()->setSelectState(true);
                    lineIterator->setSelectState(false);
                }
            }
            _linesAreSelected = false;
        }
        
    }
    else 
    {
        // If mixed geometery is selected then lets go ahead and move all of the nodes that are associated with the lines and arcs.
        // Also check to make sure that the node is actually selected for moving. If it is, then move it and deselect the node
        for(plf::colony<arcShape>::iterator arcIterator = _editor.getArcList()->begin(); arcIterator != _editor.getArcList()->end(); ++arcIterator)
        {
            if(arcIterator->getIsSelectedState())
            {
                double horizontalShift1 = (arcIterator->getFirstNode()->getCenterXCoordinate() - aboutPoint.x) * cos(-angularShift * PI / 180.0) + (arcIterator->getFirstNode()->getCenterYCoordinate() - aboutPoint.y) * sin(-angularShift * PI / 180.0) + aboutPoint.x;
                double verticalShift1 = -(arcIterator->getFirstNode()->getCenterXCoordinate() - aboutPoint.x) * sin(-angularShift * PI / 180.0) + (arcIterator->getFirstNode()->getCenterYCoordinate() - aboutPoint.y) * cos(-angularShift * PI / 180.0) + aboutPoint.y;
                
                double horizontalShift2 = (arcIterator->getSecondNode()->getCenterXCoordinate() - aboutPoint.x) * cos(-angularShift * PI / 180.0) + (arcIterator->getSecondNode()->getCenterYCoordinate() - aboutPoint.y) * sin(-angularShift * PI / 180.0) + aboutPoint.x;
                double verticalShift2 = -(arcIterator->getSecondNode()->getCenterXCoordinate() - aboutPoint.x) * sin(-angularShift * PI / 180.0) + (arcIterator->getSecondNode()->getCenterYCoordinate() - aboutPoint.y) * cos(-angularShift * PI / 180.0) + aboutPoint.y;
                
                if(arcIterator->getFirstNode()->getIsSelectedState())
                {
                    arcIterator->getFirstNode()->setCenter(horizontalShift1, verticalShift1);
                    arcIterator->getFirstNode()->setSelectState(false);
                }
                
                if(arcIterator->getSecondNode()->getIsSelectedState())
                {
                    arcIterator->getSecondNode()->setCenter(horizontalShift2, verticalShift2);
                    arcIterator->getSecondNode()->setSelectState(false);
                }
                arcIterator->calculate();
                arcIterator->setSelectState(false);
            }
        }
        
        for(plf::colony<edgeLineShape>::iterator lineIterator = _editor.getLineList()->begin(); lineIterator != _editor.getLineList()->end(); ++lineIterator)
        {
            if(lineIterator->getIsSelectedState())
            {
                /* This code was inspired by the following post: http://stackoverflow.com/questions/14842090/rotate-line-around-center-point-given-two-vertices */      
                double horizontalShift1 = (lineIterator->getFirstNode()->getCenterXCoordinate() - aboutPoint.x) * cos(-angularShift * PI / 180.0) + (lineIterator->getFirstNode()->getCenterYCoordinate() - aboutPoint.y) * sin(-angularShift * PI / 180.0) + aboutPoint.x;
                double verticalShift1 = -(lineIterator->getFirstNode()->getCenterXCoordinate() - aboutPoint.x) * sin(-angularShift * PI / 180.0) + (lineIterator->getFirstNode()->getCenterYCoordinate() - aboutPoint.y) * cos(-angularShift * PI / 180.0) + aboutPoint.y;
                
                double horizontalShift2 = (lineIterator->getSecondNode()->getCenterXCoordinate() - aboutPoint.x) * cos(-angularShift * PI / 180.0) + (lineIterator->getSecondNode()->getCenterYCoordinate() - aboutPoint.y) * sin(-angularShift * PI / 180.0) + aboutPoint.x;
                double verticalShift2 = -(lineIterator->getSecondNode()->getCenterXCoordinate() - aboutPoint.x) * sin(-angularShift * PI / 180.0) + (lineIterator->getSecondNode()->getCenterYCoordinate() - aboutPoint.y) * cos(-angularShift * PI / 180.0) + aboutPoint.y;
                
                if(lineIterator->getFirstNode()->getIsSelectedState())
                {
                    lineIterator->getFirstNode()->setCenter(horizontalShift1, verticalShift1);
                    lineIterator->getFirstNode()->setSelectState(false);
                }
                
                if(lineIterator->getSecondNode()->getIsSelectedState())
                {
                    lineIterator->getSecondNode()->setCenter(horizontalShift2, verticalShift2);
                    lineIterator->getSecondNode()->setSelectState(false);
                }
                
                lineIterator->setSelectState(false);
            }
        }
    }
    
    if(_labelsAreSelected || _geometryGroupIsSelected)
    {
        for(plf::colony<blockLabel>::iterator blockIterator = _editor.getBlockLabelList()->begin(); blockIterator != _editor.getBlockLabelList()->end(); ++blockIterator)
        {
            if(blockIterator->getIsSelectedState())
            {
                double horizontalShift = (blockIterator->getCenterXCoordinate() - aboutPoint.x) * cos(-angularShift * PI / 180.0) + (blockIterator->getCenterYCoordinate() - aboutPoint.y) * sin(-angularShift * PI / 180.0) + aboutPoint.x;
                double verticalShift = -(blockIterator->getCenterXCoordinate() - aboutPoint.x) * sin(-angularShift * PI / 180.0) + (blockIterator->getCenterYCoordinate() - aboutPoint.y) * cos(-angularShift * PI / 180.0) + aboutPoint.y;
            
                blockIterator->setCenter(horizontalShift, verticalShift);
                blockIterator->setSelectState(false);
            }   
        }
        _labelsAreSelected = false;
    }
    
    
    // Now we want to go ahead and move any of the selected nodes
    for(plf::colony<node>::iterator nodeIterator = _editor.getNodeList()->begin(); nodeIterator != _editor.getNodeList()->end(); ++nodeIterator)
    {
        if(nodeIterator->getIsSelectedState())
        {
            double horizontalShift = (nodeIterator->getCenterXCoordinate() - aboutPoint.x) * cos(-angularShift * PI / 180.0) + (nodeIterator->getCenterYCoordinate() - aboutPoint.y) * sin(-angularShift * PI / 180.0) + aboutPoint.x;
            double verticalShift = -(nodeIterator->getCenterXCoordinate() - aboutPoint.x) * sin(-angularShift * PI / 180.0) + (nodeIterator->getCenterYCoordinate() - aboutPoint.y) * cos(-angularShift * PI / 180.0) + aboutPoint.y;
            
            // Update the node with the translated coordinates
            nodeIterator->setCenter(horizontalShift, verticalShift);
            nodeIterator->setSelectState(false);
        }
        
        // After moving the nodes, we need to then make sure all of the arcs have been updated with the new node positions
        for(plf::colony<arcShape>::iterator arcIterator = _editor.getArcList()->begin(); arcIterator != _editor.getArcList()->end(); ++arcIterator)
        {
            if(*arcIterator->getFirstNode() == *nodeIterator || *arcIterator->getSecondNode() == *nodeIterator)
            {
                arcIterator->calculate(); // The center and radius of the arc will need to be recalculated after one of the nodes has moved
            }
        }
    }
    
    _labelsAreSelected = _editor.checkIntersections(EditGeometry::EDIT_ALL, getTolerance());
    
    _geometryGroupIsSelected = false;
    _nodesAreSelected = false;

    this->Refresh();
    return;
}



void modelDefinition::scaleSelection(double scalingFactor, wxRealPoint basePoint)
{
    // This function was based off of the FEMM function located in CbeladrawDoc::ScaleMove
    if(_nodesAreSelected)
    {
        for(plf::colony<node>::iterator nodeIterator = _editor.getNodeList()->begin(); nodeIterator != _editor.getNodeList()->end(); ++nodeIterator)
        {
            if(nodeIterator->getIsSelectedState())
            {
                nodeIterator->setCenter(basePoint.x + scalingFactor * (nodeIterator->getCenterXCoordinate() - basePoint.x), basePoint.y + scalingFactor * (nodeIterator->getCenterYCoordinate() - basePoint.y));
                nodeIterator->setSelectState(false);
            }
        }
        
        _nodesAreSelected = false;
        
        if(_arcsAreSelected)
        {
            // After moving the nodes, we need to then make sure all of the arcs have been updated with the new node positions
            for(plf::colony<arcShape>::iterator arcIterator = _editor.getArcList()->begin(); arcIterator != _editor.getArcList()->end(); ++arcIterator)
            {
                arcIterator->calculate(); // The center and radius of the arc will need to be recalculated after one of the nodes has moved
            } 
        }
        
        // TODO: insert a function to check for any intersections and valid points here
        
        this->Refresh();
        return;
    }
    else if(_labelsAreSelected)
    {
        for(plf::colony<blockLabel>::iterator blockIterator = _editor.getBlockLabelList()->begin(); blockIterator != _editor.getBlockLabelList()->end(); ++blockIterator)
        {
            if(blockIterator->getIsSelectedState())
            {
                blockIterator->setCenter(basePoint.x + scalingFactor * (blockIterator->getCenterXCoordinate() - basePoint.x), basePoint.y + scalingFactor * (blockIterator->getCenterYCoordinate() - basePoint.y));
                blockIterator->setSelectState(false);
            }
        }
        
        _labelsAreSelected = false;
        // TODO: insert a function to check for any intersections and valid points here
        
        clearSelection();
        this->Refresh();
        return;
    }
    else if(_linesAreSelected)
    {
        for(plf::colony<edgeLineShape>::iterator lineIterator = _editor.getLineList()->begin(); lineIterator != _editor.getLineList()->end(); ++lineIterator)
        {
            if(lineIterator->getIsSelectedState())
            {
                lineIterator->getFirstNode()->setSelectState(true);
                lineIterator->getSecondNode()->setSelectState(true);
                lineIterator->setSelectState(false);
            }
        } 
        
        _linesAreSelected = false;
        _nodesAreSelected = true;
        scaleSelection(scalingFactor, basePoint); // Yeah recusive!
        return;
    }
    else if(_arcsAreSelected)
    {
        for(plf::colony<arcShape>::iterator arcIterator = _editor.getArcList()->begin(); arcIterator != _editor.getArcList()->end(); ++arcIterator)
        {
            if(arcIterator->getIsSelectedState())
            {
                arcIterator->getFirstNode()->setSelectState(true);
                arcIterator->getSecondNode()->setSelectState(true);
                arcIterator->setSelectState(false);
            }
        }
        
        _arcsAreSelected = false;
        _nodesAreSelected = true;
        scaleSelection(scalingFactor, basePoint); // Yeah recusive!
        return;
    }
    else if(_geometryGroupIsSelected)
    {
        for(plf::colony<arcShape>::iterator arcIterator = _editor.getArcList()->begin(); arcIterator != _editor.getArcList()->end(); ++arcIterator)
        {
            if(arcIterator->getIsSelectedState())
            {
                // WE need to make sure that the arc nodes are in fact selected
                arcIterator->getFirstNode()->setSelectState(true);
                arcIterator->getSecondNode()->setSelectState(true);
                arcIterator->setSelectState(false);
            }
        }
        
        for(plf::colony<edgeLineShape>::iterator lineIterator = _editor.getLineList()->begin(); lineIterator != _editor.getLineList()->end(); ++lineIterator)
        {
            if(lineIterator->getIsSelectedState())
            {
                lineIterator->getFirstNode()->setSelectState(true);
                lineIterator->getSecondNode()->setSelectState(true);
                lineIterator->setSelectState(false);
            }
        } 
        
        _nodesAreSelected = true;
        _arcsAreSelected = true;
        scaleSelection(scalingFactor, basePoint); // scale all of the selected nodes first
        
        _labelsAreSelected = true;
        scaleSelection(scalingFactor, basePoint); // last, scale all of the block labels
        // Ensure all geometry is not selected
        _nodesAreSelected = false;
        _labelsAreSelected = false;
        _linesAreSelected = false;
        _arcsAreSelected = false;
        _geometryIsSelected = false;
        
        _labelsAreSelected = _editor.checkIntersections(EditGeometry::EDIT_ALL, getTolerance());// Check to make sure that there are no intersections
        
        this->Refresh();
        return;
    }
    
    return;
}



void modelDefinition::mirrorSelection(wxRealPoint pointOne, wxRealPoint pointTwo)
{
    /*
     * Currently, there are three cases that we need to consider.
     * First, if the slope of the mirror line is 0 (this is a horizontal line).
     * Second if the slope of the mirror is infinite (this is a vertical line)
     * Third, everything else in between
     * These three cases must be taken into account for each different setting. If only lines/nodes/arcs/labels are selected or if a mix is selected
     */ 
    if(pointOne == pointTwo)
        return;
    
    double slope = (pointOne.y - pointTwo.y) / (pointOne.x - pointTwo.x);
    
    if(slope == 0)
    {
        if(_linesAreSelected || _geometryGroupIsSelected)
        {
            /* The logic for this function follows that of the logic for mirroring the node; however, since this is 
             * a line, we will have to apply this logic to both the endpoints of the line. We will also need to check to see if the 
             * endpoints of the line already exists or if the endpoint is being drawn ontop of a block label. 
             * If either is the case, the function will have to handle these case in soem way
             */ 
            for(plf::colony<edgeLineShape>::iterator lineIterator = _editor.getLineList()->begin(); lineIterator != _editor.getLineList()->end(); ++lineIterator)
            {
                if(lineIterator->getIsSelectedState())
                {
                    double distance = lineIterator->getFirstNode()->getCenterYCoordinate() - pointOne.y;// THis is the distance between the mirror and the node
                    
                    // First, we attempt to create a node at the mirrored spot. The function will return false if another node is already present
                    // or, if a block label is present. In the event of a node already present, then we need to find out which node it is and set the nodeIndex to be that node for line creation
                    // If a block label is present, we will have to ignore the creation of line. BUt we will still place the other node
                    // The same logic applies for the second node of the line
                    if(_editor.addNode(lineIterator->getFirstNode()->getCenterXCoordinate(), pointOne.y - distance, getTolerance() / 4.0))
                    {
                        _editor.getLastNodeAdd()->setNodeSettings(*lineIterator->getFirstNode()->getNodeSetting());
                        _editor.setNodeIndex(*_editor.getLastNodeAdd());
                    }
                    else
                    {
                        node testNode;
                        testNode.setCenter(lineIterator->getFirstNode()->getCenterXCoordinate(), pointOne.y - distance);
                        for(plf::colony<node>::iterator nodeIterator = _editor.getNodeList()->begin(); nodeIterator != _editor.getNodeList()->end(); ++nodeIterator)
                        {
                            // TODO: This if statement will also need to check to see if the node is within the tolerance also
                            if(testNode == *nodeIterator)
                            {
                                _editor.setNodeIndex(*nodeIterator);
                                break;
                            }
                        }
                    }
                    
                    lineIterator->getFirstNode()->setSelectState(false);
                    
                    distance = lineIterator->getSecondNode()->getCenterYCoordinate() - pointOne.y;
                    
                    if(_editor.addNode(lineIterator->getSecondNode()->getCenterXCoordinate(), pointOne.y - distance, getTolerance() / 4.0))
                    {
                        _editor.getLastNodeAdd()->setNodeSettings(*lineIterator->getSecondNode()->getNodeSetting());
                        _editor.setNodeIndex(*_editor.getLastNodeAdd());
                    }
                    else
                    {
                        node testNode;
                        testNode.setCenter(lineIterator->getSecondNode()->getCenterXCoordinate(), pointOne.y - distance);
                        for(plf::colony<node>::iterator nodeIterator = _editor.getNodeList()->begin(); nodeIterator != _editor.getNodeList()->end(); ++nodeIterator)
                        {
                            // TODO: This if statement will also need to check to see if the node is within the tolerance also
                            if(testNode == *nodeIterator)
                            {
                                _editor.setNodeIndex(*nodeIterator);
                                break;
                            }
                        }
                    }
                    
                    lineIterator->getSecondNode()->setSelectState(false);
                    
                    if(_editor.addLine(getTolerance()))
                        _editor.getLastLineAdded()->setSegmentProperty(*lineIterator->getSegmentProperty());
                    lineIterator->setSelectState(false);
                }
            }
            _linesAreSelected = false;
        }
        
        if(_arcsAreSelected || _geometryGroupIsSelected)
        {
            for(plf::colony<arcShape>::iterator arcIterator = _editor.getArcList()->begin(); arcIterator != _editor.getArcList()->end(); ++arcIterator)
            {
                if(arcIterator->getIsSelectedState())
                {
                    double distance = arcIterator->getFirstNode()->getCenterYCoordinate() - pointOne.y;
                    
                    // First, we attempt to create a node at the mirrored spot. The function will return false if another node is already present
                    // or, if a block label is present. In the event of a node already present, then we need to find out which node it is and set the nodeIndex to be that node for line creation
                    // If a block label is present, we will have to ignore the creation of line.
                    // The same logic applies for the second node of the line
                    if(_editor.addNode(arcIterator->getFirstNode()->getCenterXCoordinate(), pointOne.y - distance, getTolerance() / 4.0))
                    {
                        _editor.getLastNodeAdd()->setNodeSettings(*arcIterator->getFirstNode()->getNodeSetting());
                        _editor.setNodeIndex(*_editor.getLastNodeAdd());
                    }
                    else
                    {
                        node testNode;
                        testNode.setCenter(arcIterator->getFirstNode()->getCenterXCoordinate(), pointOne.y - distance);
                        for(plf::colony<node>::iterator nodeIterator = _editor.getNodeList()->begin(); nodeIterator != _editor.getNodeList()->end(); ++nodeIterator)
                        {
                            // TODO: This if statement will also need to check to see if the node is within the tolerance also
                            if(testNode == *nodeIterator)
                            {
                                _editor.setNodeIndex(*nodeIterator);
                                break;
                            }
                        }
                    }
                    
                    arcIterator->getFirstNode()->setSelectState(false);
                    
                    distance = arcIterator->getSecondNode()->getCenterYCoordinate() - pointOne.y;
                    
                    if(_editor.addNode(arcIterator->getSecondNode()->getCenterXCoordinate(), pointOne.y - distance, getTolerance() / 4.0))
                    {
                        _editor.getLastNodeAdd()->setNodeSettings(*arcIterator->getSecondNode()->getNodeSetting());
                        _editor.setNodeIndex(*_editor.getLastNodeAdd());
                    }
                    else
                    {
                        node testNode;
                        testNode.setCenter(arcIterator->getSecondNode()->getCenterXCoordinate(), pointOne.y - distance);
                        for(plf::colony<node>::iterator nodeIterator = _editor.getNodeList()->begin(); nodeIterator != _editor.getNodeList()->end(); ++nodeIterator)
                        {
                            // TODO: This if statement will also need to check to see if the node is within the tolerance also
                            if(testNode == *nodeIterator)
                            {
                                _editor.setNodeIndex(*nodeIterator);
                                break;
                            }
                        }
                    }
                    
                    arcIterator->getSecondNode()->setSelectState(false);
                    
                    arcShape tempArc;
                    tempArc.setSegmentProperty(*arcIterator->getSegmentProperty());
                    tempArc.setArcAngle(arcIterator->getArcAngle());
                    tempArc.setNumSegments(arcIterator->getnumSegments());
                    _editor.switchIndex();
                    _editor.addArc(tempArc, 0, true);
                    arcIterator->setSelectState(false);
                }
            }
            _arcsAreSelected = false;
        }
        
        if(_labelsAreSelected || _geometryGroupIsSelected)
        {
            for(plf::colony<blockLabel>::iterator blockIterator = _editor.getBlockLabelList()->begin(); blockIterator != _editor.getBlockLabelList()->end(); ++blockIterator)
            {
                if(blockIterator->getIsSelectedState())
                {
                    double distance = blockIterator->getCenterYCoordinate() - pointOne.y;
                    
                    if(_editor.addBlockLabel(blockIterator->getCenterXCoordinate(), pointOne.y - distance, getTolerance() / 4.0))
                        _editor.getLastBlockLabelAdded()->setPorperty(*blockIterator->getProperty());
                    blockIterator->setSelectState(false);
                }
            }
            _labelsAreSelected = false;
        }
        
        if(_nodesAreSelected || _geometryGroupIsSelected)
        {
            for(plf::colony<node>::iterator nodeIterator = _editor.getNodeList()->begin(); nodeIterator != _editor.getNodeList()->end(); ++nodeIterator)
            {
                if(nodeIterator->getIsSelectedState())
                {
                    double distance = nodeIterator->getCenterYCoordinate() - pointOne.y;
                    
                    if(_editor.addNode(nodeIterator->getCenterXCoordinate(), pointOne.y - distance, getTolerance() / 4.0))
                        _editor.getLastNodeAdd()->setNodeSettings(*nodeIterator->getNodeSetting());
                    nodeIterator->setSelectState(false);
                }
            }
            _nodesAreSelected = false;
        }
        
        _geometryGroupIsSelected = false;
    }
    else if(slope == INFINITY || slope == -INFINITY)
    {
        if(_linesAreSelected || _geometryGroupIsSelected)
        {
            /* THis is the case for it the mirror line is vertical */
            for(plf::colony<edgeLineShape>::iterator lineIterator = _editor.getLineList()->begin(); lineIterator != _editor.getLineList()->end(); ++lineIterator)
            {
                if(lineIterator->getIsSelectedState())
                {
                    double distance = pointOne.x - lineIterator->getFirstNode()->getCenterXCoordinate();
                    
                    if(_editor.addNode(pointOne.x + distance, lineIterator->getFirstNode()->getCenterYCoordinate(), getTolerance() / 4.0))
                    {
                        _editor.getLastNodeAdd()->setNodeSettings(*lineIterator->getFirstNode()->getNodeSetting());
                        _editor.setNodeIndex(*_editor.getLastNodeAdd());
                    }
                    else
                    {
                        node testNode;
                        testNode.setCenter(pointOne.x + distance, lineIterator->getFirstNode()->getCenterYCoordinate());
                        for(plf::colony<node>::iterator nodeIterator = _editor.getNodeList()->begin(); nodeIterator != _editor.getNodeList()->end(); ++nodeIterator)
                        {
                            // TODO: This if statement will also need to check to see if the node is within the tolerance also
                            if(testNode == *nodeIterator)
                            {
                                _editor.setNodeIndex(*nodeIterator);
                                break;
                            }
                        }
                    }
                    
                    lineIterator->getFirstNode()->setSelectState(false);
                    
                    distance = pointOne.x - lineIterator->getSecondNode()->getCenterXCoordinate();
                    
                    if(_editor.addNode(pointOne.x + distance, lineIterator->getSecondNode()->getCenterYCoordinate(), getTolerance() / 4.0))
                    {
                        _editor.getLastNodeAdd()->setNodeSettings(*lineIterator->getSecondNode()->getNodeSetting());
                        _editor.setNodeIndex(*_editor.getLastNodeAdd());
                    }
                    else
                    {
                        node testNode;
                        testNode.setCenter(pointOne.x + distance, lineIterator->getSecondNode()->getCenterYCoordinate());
                        for(plf::colony<node>::iterator nodeIterator = _editor.getNodeList()->begin(); nodeIterator != _editor.getNodeList()->end(); ++nodeIterator)
                        {
                            // TODO: This if statement will also need to check to see if the node is within the tolerance also
                            if(testNode == *nodeIterator)
                            {
                                _editor.setNodeIndex(*nodeIterator);
                                break;
                            }
                        }
                    }
                    
                    lineIterator->getSecondNode()->setSelectState(false);
                    
                    if(_editor.addLine(getTolerance()))
                        _editor.getLastLineAdded()->setSegmentProperty(*lineIterator->getSegmentProperty());
                    lineIterator->setSelectState(false);
                }
            }
            _linesAreSelected = false;
        }
        
        if(_arcsAreSelected || _geometryGroupIsSelected)
        {
            /* THis is the case for it the mirror line is vertical */
            for(plf::colony<arcShape>::iterator arcIterator = _editor.getArcList()->begin(); arcIterator != _editor.getArcList()->end(); ++arcIterator)
            {
                if(arcIterator->getIsSelectedState())
                {
                    double distance = pointOne.x - arcIterator->getFirstNode()->getCenterXCoordinate();
                    
                    if(_editor.addNode(pointOne.x + distance, arcIterator->getFirstNode()->getCenterYCoordinate(), getTolerance() / 4.0))
                    {
                        _editor.getLastNodeAdd()->setNodeSettings(*arcIterator->getFirstNode()->getNodeSetting());
                        _editor.setNodeIndex(*_editor.getLastNodeAdd());
                    }
                    else
                    {
                        node testNode;
                        testNode.setCenter(pointOne.x + distance, arcIterator->getFirstNode()->getCenterYCoordinate());
                        for(plf::colony<node>::iterator nodeIterator = _editor.getNodeList()->begin(); nodeIterator != _editor.getNodeList()->end(); ++nodeIterator)
                        {
                            // TODO: This if statement will also need to check to see if the node is within the tolerance also
                            if(testNode == *nodeIterator)
                            {
                                _editor.setNodeIndex(*nodeIterator);
                                break;
                            }
                        }
                    }
                    
                    arcIterator->getFirstNode()->setSelectState(false);
                    
                    distance = pointOne.x - arcIterator->getSecondNode()->getCenterXCoordinate();
                    
                    if(_editor.addNode(pointOne.x + distance, arcIterator->getSecondNode()->getCenterYCoordinate(), getTolerance() / 4.0))
                    {
                        _editor.getLastNodeAdd()->setNodeSettings(*arcIterator->getSecondNode()->getNodeSetting());
                        _editor.setNodeIndex(*_editor.getLastNodeAdd());
                    }
                    else
                    {
                        node testNode;
                        testNode.setCenter(pointOne.x + distance, arcIterator->getSecondNode()->getCenterYCoordinate());
                        for(plf::colony<node>::iterator nodeIterator = _editor.getNodeList()->begin(); nodeIterator != _editor.getNodeList()->end(); ++nodeIterator)
                        {
                            // TODO: This if statement will also need to check to see if the node is within the tolerance also
                            if(testNode == *nodeIterator)
                            {
                                _editor.setNodeIndex(*nodeIterator);
                                break;
                            }
                        }
                    }
                    
                    arcIterator->getSecondNode()->setSelectState(false);
                    
                    arcShape tempArc;
                    tempArc.setSegmentProperty(*arcIterator->getSegmentProperty());
                    tempArc.setArcAngle(arcIterator->getArcAngle());
                    tempArc.setNumSegments(arcIterator->getnumSegments());
                    _editor.switchIndex();
                    _editor.addArc(tempArc, 0, true);
                    arcIterator->setSelectState(false);
                }
            }
            _arcsAreSelected = false;
        }
        
        if(_labelsAreSelected || _geometryGroupIsSelected)
        {
            // This is the case for if the mirror line is a vertical line
            for(plf::colony<blockLabel>::iterator blockIterator = _editor.getBlockLabelList()->begin(); blockIterator != _editor.getBlockLabelList()->end(); ++blockIterator)
            {
                if(blockIterator->getIsSelectedState())
                {
                    double distance = pointOne.x - blockIterator->getCenterXCoordinate();
                    
                    if(_editor.addBlockLabel(pointOne.x + distance, blockIterator->getCenterYCoordinate(), getTolerance() / 4.0))
                        _editor.getLastBlockLabelAdded()->setPorperty(*blockIterator->getProperty());
                    blockIterator->setSelectState(false);
                }
            }
            _labelsAreSelected = false;
        }
        
        if(_nodesAreSelected || _geometryGroupIsSelected)
        {
            // This is the case for if the mirror line is a vertical line
            for(plf::colony<node>::iterator nodeIterator = _editor.getNodeList()->begin(); nodeIterator != _editor.getNodeList()->end(); ++nodeIterator)
            {
                if(nodeIterator->getIsSelectedState())
                {
                    double distance = pointOne.x - nodeIterator->getCenterXCoordinate();
                    
                    if(_editor.addNode(pointOne.x + distance, nodeIterator->getCenterYCoordinate(), getTolerance() / 4.0))
                        _editor.getLastNodeAdd()->setNodeSettings(*nodeIterator->getNodeSetting());
                    nodeIterator->setSelectState(false);
                }
            }
            _nodesAreSelected = false;
        }
        
        _geometryGroupIsSelected = false;
    }
    else // Everything else
    {
        if(_linesAreSelected || _geometryGroupIsSelected)
        {
            for(plf::colony<edgeLineShape>::iterator lineIterator = _editor.getLineList()->begin(); lineIterator != _editor.getLineList()->end(); ++lineIterator)
            {
                // This is the y-intercept of the mirror line
                double b1 = pointOne.y - slope * pointOne.x;
                
                // This is the slope for the perpendicular line
                double perpSlope = -1.0 / slope;
                
                if(lineIterator->getIsSelectedState())
                {
                    double b2 = lineIterator->getFirstNode()->getCenterYCoordinate() - perpSlope * lineIterator->getFirstNode()->getCenterXCoordinate();
                    
                    double intersectionPointx = (b1 - b2) / (perpSlope - slope);
                    double intersectionPointy = slope * intersectionPointx + b1;
                    
                    if(_editor.addNode(2 * intersectionPointx - lineIterator->getFirstNode()->getCenterXCoordinate(), 2 * intersectionPointy - lineIterator->getFirstNode()->getCenterYCoordinate(), getTolerance() / 4.0))
                    {
                        _editor.getLastNodeAdd()->setNodeSettings(*lineIterator->getFirstNode()->getNodeSetting());
                        _editor.setNodeIndex(*_editor.getLastNodeAdd());
                    }
                    else
                    {
                        node testNode;
                        testNode.setCenter(2 * intersectionPointx - lineIterator->getFirstNode()->getCenterXCoordinate(), 2 * intersectionPointy - lineIterator->getFirstNode()->getCenterYCoordinate());
                        for(plf::colony<node>::iterator nodeIterator = _editor.getNodeList()->begin(); nodeIterator != _editor.getNodeList()->end(); ++nodeIterator)
                        {
                            // TODO: This if statement will also need to check to see if the node is within the tolerance also
                            if(testNode == *nodeIterator)
                            {
                                _editor.setNodeIndex(*nodeIterator);
                                break;
                            }
                        }
                    }
                    
                    lineIterator->getFirstNode()->setSelectState(false);
                    
                    // Re-calculate some of the parameters for the second node of the line
                    b2 = lineIterator->getSecondNode()->getCenterYCoordinate() - perpSlope * lineIterator->getSecondNode()->getCenterXCoordinate();
                    intersectionPointx = (b1 - b2) / (perpSlope - slope);
                    intersectionPointy = slope * intersectionPointx + b1;
                    
                    if(_editor.addNode(2 * intersectionPointx - lineIterator->getSecondNode()->getCenterXCoordinate(), 2 * intersectionPointy - lineIterator->getSecondNode()->getCenterYCoordinate(), getTolerance() / 4.0))
                    {
                        _editor.getLastNodeAdd()->setNodeSettings(*lineIterator->getSecondNode()->getNodeSetting());
                        _editor.setNodeIndex(*_editor.getLastNodeAdd());
                    }
                    else
                    {
                        node testNode;
                        testNode.setCenter(2 * intersectionPointx - lineIterator->getSecondNode()->getCenterXCoordinate(), 2 * intersectionPointy - lineIterator->getSecondNode()->getCenterYCoordinate());
                        for(plf::colony<node>::iterator nodeIterator = _editor.getNodeList()->begin(); nodeIterator != _editor.getNodeList()->end(); ++nodeIterator)
                        {
                            // TODO: This if statement will also need to check to see if the node is within the tolerance also
                            if(testNode == *nodeIterator)
                            {
                                _editor.setNodeIndex(*nodeIterator);
                                break;
                            }
                        }
                    }
                    
                    lineIterator->getSecondNode()->setSelectState(false);
                    
                    if(_editor.addLine(getTolerance()))
                        _editor.getLastLineAdded()->setSegmentProperty(*lineIterator->getSegmentProperty());
                    lineIterator->setSelectState(false);
                }
            }
            _linesAreSelected = false;
        }
        
        if(_arcsAreSelected || _geometryGroupIsSelected)
        {
            for(plf::colony<arcShape>::iterator arcIterator = _editor.getArcList()->begin(); arcIterator != _editor.getArcList()->end(); ++arcIterator)
            {
                // This is the y-intercept of the mirror line
                double b1 = pointOne.y - slope * pointOne.x;
                
                // This is the slope for the perpendicular line
                double perpSlope = -1.0 / slope;
                    
                if(arcIterator->getIsSelectedState())
                {
                    
                    double b2 = arcIterator->getFirstNode()->getCenterYCoordinate() - perpSlope * arcIterator->getFirstNode()->getCenterXCoordinate();
                    
                    double intersectionPointx = (b1 - b2) / (perpSlope - slope);
                    double intersectionPointy = slope * intersectionPointx + b1;
                    
                    if(_editor.addNode(2 * intersectionPointx - arcIterator->getFirstNode()->getCenterXCoordinate(), 2 * intersectionPointy - arcIterator->getFirstNode()->getCenterYCoordinate(), getTolerance() / 4.0))
                    {
                        _editor.getLastNodeAdd()->setNodeSettings(*arcIterator->getFirstNode()->getNodeSetting());
                        _editor.setNodeIndex(*_editor.getLastNodeAdd());
                    }
                    else
                    {
                        node testNode;
                        testNode.setCenter(2 * intersectionPointx - arcIterator->getFirstNode()->getCenterXCoordinate(), 2 * intersectionPointy - arcIterator->getFirstNode()->getCenterYCoordinate());
                        for(plf::colony<node>::iterator nodeIterator = _editor.getNodeList()->begin(); nodeIterator != _editor.getNodeList()->end(); ++nodeIterator)
                        {
                            // TODO: This if statement will also need to check to see if the node is within the tolerance also
                            if(testNode == *nodeIterator)
                            {
                                _editor.setNodeIndex(*nodeIterator);
                                break;
                            }
                        }
                    }
                    
                    arcIterator->getFirstNode()->setSelectState(false);
                    
                    // Re-calculate some of the parameters for the second node of the line
                    b2 = arcIterator->getSecondNode()->getCenterYCoordinate() - perpSlope * arcIterator->getSecondNode()->getCenterXCoordinate();
                    intersectionPointx = (b1 - b2) / (perpSlope - slope);
                    intersectionPointy = slope * intersectionPointx + b1;
                    
                    if(_editor.addNode(2 * intersectionPointx - arcIterator->getSecondNode()->getCenterXCoordinate(), 2 * intersectionPointy - arcIterator->getSecondNode()->getCenterYCoordinate(), getTolerance() / 4.0))
                    {
                        _editor.getLastNodeAdd()->setNodeSettings(*arcIterator->getSecondNode()->getNodeSetting());
                        _editor.setNodeIndex(*_editor.getLastNodeAdd());
                    }
                    else
                    {
                        node testNode;
                        testNode.setCenter(2 * intersectionPointx - arcIterator->getSecondNode()->getCenterXCoordinate(), 2 * intersectionPointy - arcIterator->getSecondNode()->getCenterYCoordinate());
                        for(plf::colony<node>::iterator nodeIterator = _editor.getNodeList()->begin(); nodeIterator != _editor.getNodeList()->end(); ++nodeIterator)
                        {
                            // TODO: This if statement will also need to check to see if the node is within the tolerance also
                            if(testNode == *nodeIterator)
                            {
                                _editor.setNodeIndex(*nodeIterator);
                                break;
                            }
                        }
                    }
                    
                    arcIterator->getSecondNode()->setSelectState(false);
                    
                    arcShape tempArc;
                    tempArc.setSegmentProperty(*arcIterator->getSegmentProperty());
                    tempArc.setArcAngle(arcIterator->getArcAngle());
                    tempArc.setNumSegments(arcIterator->getnumSegments());
                    _editor.switchIndex();
                    _editor.addArc(tempArc, 0, true); 
                    arcIterator->setSelectState(false);
                }
            }
            _arcsAreSelected = false; 
        }
        
        if(_labelsAreSelected || _geometryGroupIsSelected)
        {
            // This is the y-intercept of the mirror line
            double b1 = pointOne.y - slope * pointOne.x;
            
            // This is the slope for the perpendicular line
            double perpSlope = -1.0 / slope;
            
            for(plf::colony<blockLabel>::iterator blockIterator = _editor.getBlockLabelList()->begin(); blockIterator != _editor.getBlockLabelList()->end(); ++blockIterator)
            {
                if(blockIterator->getIsSelectedState())
                {
                    // This is the y-intercept for the line that the mirrored point will be on
                    double b2 = blockIterator->getCenterYCoordinate() - perpSlope * blockIterator->getCenterXCoordinate();
                    
                    // This is the point where the mirror line and the line that the mirrored point is on intercet at
                    double intersectionPointx = (b1 - b2) / (perpSlope - slope);
                    double intersectionPointy = slope * intersectionPointx + b1;
                    
                    if(_editor.addBlockLabel(2 * intersectionPointx - blockIterator->getCenterXCoordinate(), 2 * intersectionPointy - blockIterator->getCenterYCoordinate(), getTolerance() / 4.0))
                        _editor.getLastBlockLabelAdded()->setPorperty(*blockIterator->getProperty());
                    blockIterator->setSelectState(false);
                }
            }
            _labelsAreSelected = false;
        }
        
        if(_nodesAreSelected || _geometryGroupIsSelected)
        {
            // This is the y-intercept of the mirror line
            double b1 = pointOne.y - slope * pointOne.x;
            
            // This is the slope for the perpendicular line
            double perpSlope = -1.0 / slope;
            
            for(plf::colony<node>::iterator nodeIterator = _editor.getNodeList()->begin(); nodeIterator != _editor.getNodeList()->end(); ++nodeIterator)
            {
                if(nodeIterator->getIsSelectedState())
                {
                    // This is the y-intercept for the line that the mirrored point will be on
                    double b2 = nodeIterator->getCenterYCoordinate() - perpSlope * nodeIterator->getCenterXCoordinate();
                    
                    // This is the point where the mirror line and the line that the mirrored point is on intercet at
                    double intersectionPointx = (b1 - b2) / (perpSlope - slope);
                    double intersectionPointy = slope * intersectionPointx + b1;
                    
                    if(_editor.addNode(2 * intersectionPointx - nodeIterator->getCenterXCoordinate(), 2 * intersectionPointy - nodeIterator->getCenterYCoordinate(), getTolerance() / 4.0))
                        _editor.getLastNodeAdd()->setNodeSettings(*nodeIterator->getNodeSetting());
                    nodeIterator->setSelectState(false);
                }
            }
            _nodesAreSelected = false;
        }
        _geometryGroupIsSelected = false;
    }
    
    _labelsAreSelected = _editor.checkIntersections(EditGeometry::EDIT_ALL, getTolerance());
    
    this->Refresh();
    return;
}



void modelDefinition::copyTranslateSelection(double horizontalShift, double verticalShift, unsigned int numberOfCopies)
{
    if(_linesAreSelected || _geometryGroupIsSelected)
    {
        plf::colony<edgeLineShape> selectedLines;
        for(plf::colony<edgeLineShape>::iterator lineIterator = _editor.getLineList()->begin(); lineIterator != _editor.getLineList()->end(); ++lineIterator)
        {
            if(lineIterator->getIsSelectedState())
            {
                selectedLines.insert(*lineIterator);
                lineIterator->setSelectState(false);
            }
        }
        
        for(plf::colony<edgeLineShape>::iterator lineIterator = selectedLines.begin(); lineIterator != selectedLines.end(); ++lineIterator)
        {
            for(unsigned int i = 1; i < (numberOfCopies + 1); i++)
            {
                
                /* Bug Fix:
                 * The issue was that if two or more lines were connected to a common node, then on the copy,
                 * some of the copied lines would not be connected to the propery node.
                 * The main issue behind this is that the program never checked to see if the node
                 * that was being copied was already copied.
                 * The fix is to iterate through the entire node list to ensure that the first node was not
                 * already copied. It would be compared against a test node. If it was already copied,
                 * then add the iterator to the class (for accessing when the line is ready to be drawn).
                 * Since this can occur for either the first or second node, we have to do this again to the
                 * second node. If the node does not exist, then create the node adn set the iterator in the 
                 * geometry editor class for line creation.
                 * The same logic applies to arcs
                 */
                 // TODO: Check FEMM code to make sure that it is necessary to have the tolerance here set to 0
                if(_editor.addNode(lineIterator->getFirstNode()->getCenterXCoordinate() + i * horizontalShift, lineIterator->getFirstNode()->getCenterYCoordinate() + i * verticalShift, getTolerance() / 8.0))
                {
                    _editor.getLastNodeAdd()->setNodeSettings(*lineIterator->getFirstNode()->getNodeSetting());
                    _editor.setNodeIndex(*_editor.getLastNodeAdd()); 
                }
                else
                {
                    node testNode;
                    testNode.setCenter(lineIterator->getFirstNode()->getCenterXCoordinate() + i * horizontalShift, lineIterator->getFirstNode()->getCenterYCoordinate() + i * verticalShift);
                    for(plf::colony<node>::iterator nodeIterator = _editor.getNodeList()->begin(); nodeIterator != _editor.getNodeList()->end(); ++nodeIterator)
                    {
                        // TODO: This if statement will need to check if the node is within tolerance
                        if(*nodeIterator == testNode)
                        {
                            _editor.setNodeIndex(*nodeIterator);
                            break;
                        }
                    }
                }
                
                lineIterator->getFirstNode()->setSelectState(false);
                
                if(_editor.addNode(lineIterator->getSecondNode()->getCenterXCoordinate() + i * horizontalShift, lineIterator->getSecondNode()->getCenterYCoordinate() + i * verticalShift, getTolerance() / 8.0))
                {
                    _editor.getLastNodeAdd()->setNodeSettings(*lineIterator->getSecondNode()->getNodeSetting());
                    _editor.setNodeIndex(*_editor.getLastNodeAdd());
                }
                else
                {
                    node testNode;
                    testNode.setCenter(lineIterator->getSecondNode()->getCenterXCoordinate() + i * horizontalShift, lineIterator->getSecondNode()->getCenterYCoordinate() + i * verticalShift);
                    for(plf::colony<node>::iterator nodeIterator = _editor.getNodeList()->begin(); nodeIterator != _editor.getNodeList()->end(); ++nodeIterator)
                    {
                        // TODO: This if statement will need to check if the node is within tolerance
                        if(*nodeIterator == testNode)
                        {
                            _editor.setNodeIndex(*nodeIterator);
                            break;
                        }
                    }
                }
                
                lineIterator->getSecondNode()->setSelectState(false);

                if(_editor.addLine(getTolerance()))
                    _editor.getLastLineAdded()->setSegmentProperty(*lineIterator->getSegmentProperty());
            }
        }
            
        _linesAreSelected = false;
    }
    
    if(_arcsAreSelected || _geometryGroupIsSelected)
    {
        plf::colony<arcShape> selectedArcs;
        
        for(plf::colony<arcShape>::iterator arcIterator = _editor.getArcList()->begin(); arcIterator != _editor.getArcList()->end(); ++arcIterator)
        {
            if(arcIterator->getIsSelectedState())
            {
                arcIterator->setSelectState(false);
                selectedArcs.insert(*arcIterator);
            }
        }
        
        for(plf::colony<arcShape>::iterator arcIterator = selectedArcs.begin(); arcIterator != selectedArcs.end(); ++arcIterator)
        {
            for(unsigned int i = 1; i < (numberOfCopies + 1); i++)
            {
                
                if(_editor.addNode(arcIterator->getFirstNode()->getCenterXCoordinate() + i * horizontalShift, arcIterator->getFirstNode()->getCenterYCoordinate() + i * verticalShift, getTolerance() / 8.0))
                {
                    _editor.getLastNodeAdd()->setNodeSettings(*arcIterator->getFirstNode()->getNodeSetting());
                    _editor.setNodeIndex(*_editor.getLastNodeAdd()); 
                }
                else
                {
                    node testNode;
                    testNode.setCenter(arcIterator->getFirstNode()->getCenterXCoordinate() + i * horizontalShift, arcIterator->getFirstNode()->getCenterYCoordinate() + i * verticalShift);
                    for(plf::colony<node>::iterator nodeIterator = _editor.getNodeList()->begin(); nodeIterator != _editor.getNodeList()->end(); ++nodeIterator)
                    {
                        // TODO: This if statement will need to check if the node is within tolerance
                        if(*nodeIterator == testNode)
                        {
                            _editor.setNodeIndex(*nodeIterator);
                            break;
                        }
                    }
                }
                
                arcIterator->getFirstNode()->setSelectState(false);
                
                if(_editor.addNode(arcIterator->getSecondNode()->getCenterXCoordinate() + i * horizontalShift, arcIterator->getSecondNode()->getCenterYCoordinate() + i * verticalShift, getTolerance() / 8.0))
                {
                    _editor.getLastNodeAdd()->setNodeSettings(*arcIterator->getSecondNode()->getNodeSetting());
                    _editor.setNodeIndex(*_editor.getLastNodeAdd());
                }
                else
                {
                    node testNode;
                    testNode.setCenter(arcIterator->getSecondNode()->getCenterXCoordinate() + i * horizontalShift, arcIterator->getSecondNode()->getCenterYCoordinate() + i * verticalShift);
                    for(plf::colony<node>::iterator nodeIterator = _editor.getNodeList()->begin(); nodeIterator != _editor.getNodeList()->end(); ++nodeIterator)
                    {
                        // TODO: This if statement will need to check if the node is within tolerance
                        if(*nodeIterator == testNode)
                        {
                            _editor.setNodeIndex(*nodeIterator);
                            break;
                        }
                    }
                }
                
                arcIterator->getSecondNode()->setSelectState(false);
                
                arcShape tempArc;
                tempArc.setSegmentProperty(*arcIterator->getSegmentProperty());
                tempArc.setArcAngle(arcIterator->getArcAngle());
                tempArc.setNumSegments(arcIterator->getnumSegments());
                
                _editor.addArc(tempArc, 0, true);
            }
        }
                
        _arcsAreSelected = false;
    }
    
    if(_nodesAreSelected || _geometryGroupIsSelected)
    {
        // Make copies of those nodes
        for(plf::colony<node>::iterator nodeIterator = _editor.getNodeList()->begin(); nodeIterator != _editor.getNodeList()->end(); ++nodeIterator)
        {
            if(nodeIterator->getIsSelectedState())
            {
                for(unsigned int i = 1; i < (numberOfCopies + 1); i++)
                {
                    if(_editor.addNode(nodeIterator->getCenterXCoordinate() + i * horizontalShift, nodeIterator->getCenterYCoordinate() + i * verticalShift, getTolerance() / 4.0))
                        _editor.getLastNodeAdd()->setNodeSettings(*nodeIterator->getNodeSetting());
                }
                nodeIterator->setSelectState(false);
            }
        }
        _nodesAreSelected = false;
    }
    
    if(_labelsAreSelected || _geometryGroupIsSelected)
    {
        for(plf::colony<blockLabel>::iterator blockIterator = _editor.getBlockLabelList()->begin(); blockIterator != _editor.getBlockLabelList()->end(); ++blockIterator)
        {
            if(blockIterator->getIsSelectedState())
            {
                for(unsigned int i = 1; i < (numberOfCopies + 1); i++)
                {
                    if(_editor.addBlockLabel(blockIterator->getCenterXCoordinate() + i * horizontalShift, blockIterator->getCenterYCoordinate() + i * verticalShift, getTolerance() / 4.0))
                        _editor.getLastBlockLabelAdded()->setPorperty(*blockIterator->getProperty());
                }
                blockIterator->setSelectState(false);
            }
        }
        _labelsAreSelected = false;
    }
    
    _geometryGroupIsSelected = false;
    
    this->Refresh();
    return;
}


void modelDefinition::copyRotateSelection(double angularShift, wxRealPoint aboutPoint, unsigned int numberOfCopies)
{
    if(_linesAreSelected || _geometryGroupIsSelected)
    {
        double tempShift = -angularShift;// I am not sure why this is necessary but for some reason, the program does not like a -i in the loop.
        plf::colony<edgeLineShape> selectedLines;
        for(plf::colony<edgeLineShape>::iterator lineIterator = _editor.getLineList()->begin(); lineIterator != _editor.getLineList()->end(); ++lineIterator)
        {
            if(lineIterator->getIsSelectedState())
            {
                lineIterator->setSelectState(false);
                selectedLines.insert(*lineIterator);
            }
        }
        
        for(plf::colony<edgeLineShape>::iterator lineIterator = selectedLines.begin(); lineIterator != selectedLines.end(); ++lineIterator)
        {   
            for(unsigned int i = 1; i < (numberOfCopies + 1); i++)
            {
                double horizontalShift1 = (lineIterator->getFirstNode()->getCenterXCoordinate() - aboutPoint.x) * cos(i * tempShift * PI / 180.0) + (lineIterator->getFirstNode()->getCenterYCoordinate() - aboutPoint.y) * sin(i * tempShift * PI / 180.0) + aboutPoint.x;
                double verticalShift1 = -(lineIterator->getFirstNode()->getCenterXCoordinate() - aboutPoint.x) * sin(i * tempShift * PI / 180.0) + (lineIterator->getFirstNode()->getCenterYCoordinate() - aboutPoint.y) * cos(i * tempShift * PI / 180.0) + aboutPoint.y;
                
                double horizontalShift2 = (lineIterator->getSecondNode()->getCenterXCoordinate() - aboutPoint.x) * cos(i * tempShift * PI / 180.0) + (lineIterator->getSecondNode()->getCenterYCoordinate() - aboutPoint.y) * sin(i * tempShift * PI / 180.0) + aboutPoint.x;
                double verticalShift2 = -(lineIterator->getSecondNode()->getCenterXCoordinate() - aboutPoint.x) * sin(i * tempShift * PI / 180.0) + (lineIterator->getSecondNode()->getCenterYCoordinate() - aboutPoint.y) * cos(i * tempShift * PI / 180.0) + aboutPoint.y;
            
                if(_editor.addNode(horizontalShift1, verticalShift1, getTolerance() / 8.0))
                {
                    _editor.getLastNodeAdd()->setNodeSettings(*lineIterator->getFirstNode()->getNodeSetting());
                    _editor.setNodeIndex(*_editor.getLastNodeAdd()); 
                }
                else
                {
                    node testNode;
                    testNode.setCenter(horizontalShift1, verticalShift1);
                    for(plf::colony<node>::iterator nodeIterator = _editor.getNodeList()->begin(); nodeIterator != _editor.getNodeList()->end(); ++nodeIterator)
                    {
                        if(*nodeIterator == testNode)
                        {
                            _editor.setNodeIndex(*nodeIterator);
                            break;
                        }
                    }
                }
                
                lineIterator->getFirstNode()->setSelectState(false);
               
                if(_editor.addNode(horizontalShift2, verticalShift2, getTolerance() / 8.0))
                {
                    _editor.getLastNodeAdd()->setNodeSettings(*lineIterator->getSecondNode()->getNodeSetting());
                    _editor.setNodeIndex(*_editor.getLastNodeAdd());  
                }
                else
                {
                    node testNode;
                    testNode.setCenter(horizontalShift2, verticalShift2);
                    for(plf::colony<node>::iterator nodeIterator = _editor.getNodeList()->begin(); nodeIterator != _editor.getNodeList()->end(); ++nodeIterator)
                    {
                        if(*nodeIterator == testNode)
                        {
                            _editor.setNodeIndex(*nodeIterator);
                            break;
                        }
                    }
                }
                
                lineIterator->getSecondNode()->setSelectState(false);

                if(_editor.addLine(getTolerance()))
                    _editor.getLastLineAdded()->setSegmentProperty(*lineIterator->getSegmentProperty());
            }
        }
                
        _linesAreSelected = false;
    }
    
    if(_arcsAreSelected || _geometryGroupIsSelected)
    {
        double tempShift = -angularShift;
        plf::colony<arcShape> selectedArcs;
        for(plf::colony<arcShape>::iterator arcIterator = _editor.getArcList()->begin(); arcIterator != _editor.getArcList()->end(); ++arcIterator)
        {
            if(arcIterator->getIsSelectedState())
            {
                arcIterator->setSelectState(false);
                selectedArcs.insert(*arcIterator);
            }
        }
        
        for(plf::colony<arcShape>::iterator arcIterator = selectedArcs.begin(); arcIterator != selectedArcs.end(); ++arcIterator)
        {
            for(unsigned int i = 1; i < (numberOfCopies + 1); i++)
            {
                double horizontalShift1 = (arcIterator->getFirstNode()->getCenterXCoordinate() - aboutPoint.x) * cos(i * tempShift * PI / 180.0) + (arcIterator->getFirstNode()->getCenterYCoordinate() - aboutPoint.y) * sin(i * tempShift * PI / 180.0) + aboutPoint.x;
                double verticalShift1 = -(arcIterator->getFirstNode()->getCenterXCoordinate() - aboutPoint.x) * sin(i * tempShift * PI / 180.0) + (arcIterator->getFirstNode()->getCenterYCoordinate() - aboutPoint.y) * cos(i * tempShift * PI / 180.0) + aboutPoint.y;
                
                double horizontalShift2 = (arcIterator->getSecondNode()->getCenterXCoordinate() - aboutPoint.x) * cos(i * tempShift * PI / 180.0) + (arcIterator->getSecondNode()->getCenterYCoordinate() - aboutPoint.y) * sin(i * tempShift * PI / 180.0) + aboutPoint.x;
                double verticalShift2 = -(arcIterator->getSecondNode()->getCenterXCoordinate() - aboutPoint.x) * sin(i * tempShift * PI / 180.0) + (arcIterator->getSecondNode()->getCenterYCoordinate() - aboutPoint.y) * cos(i * tempShift * PI / 180.0) + aboutPoint.y;
                
                if(_editor.addNode(horizontalShift1, verticalShift1, getTolerance() / 8.0))
                {
                    _editor.getLastNodeAdd()->setNodeSettings(*arcIterator->getFirstNode()->getNodeSetting());
                    _editor.setNodeIndex(*_editor.getLastNodeAdd());
                }
                else
                {
                    node testNode;
                    testNode.setCenter(horizontalShift1, verticalShift1);
                    for(plf::colony<node>::iterator nodeIterator = _editor.getNodeList()->begin(); nodeIterator != _editor.getNodeList()->end(); ++nodeIterator)
                    {
                        if(*nodeIterator == testNode)
                        {
                            _editor.setNodeIndex(*nodeIterator);
                            break;
                        }
                    }
                }
                
                arcIterator->getFirstNode()->setSelectState(false);
               
                if(_editor.addNode(horizontalShift2, verticalShift2, getTolerance() / 8.0))
                {
                    _editor.getLastNodeAdd()->setNodeSettings(*arcIterator->getSecondNode()->getNodeSetting());
                    _editor.setNodeIndex(*_editor.getLastNodeAdd());
                }
                else
                {
                    node testNode;
                    testNode.setCenter(horizontalShift2, verticalShift2);
                    for(plf::colony<node>::iterator nodeIterator = _editor.getNodeList()->begin(); nodeIterator != _editor.getNodeList()->end(); ++nodeIterator)
                    {
                        if(*nodeIterator == testNode)
                        {
                            _editor.setNodeIndex(*nodeIterator);
                            break;
                        }
                    }
                }
                
                arcIterator->getSecondNode()->setSelectState(false);

                arcShape tempArc;
                tempArc.setSegmentProperty(*arcIterator->getSegmentProperty());
                tempArc.setArcAngle(arcIterator->getArcAngle());
                tempArc.setNumSegments(arcIterator->getnumSegments());
                
                _editor.addArc(tempArc, 0, true);
            }
        }
                
        _arcsAreSelected = false;
    }
    
    if(_nodesAreSelected || _geometryGroupIsSelected)
    {
        double tempShift = -angularShift;
        for(plf::colony<node>::iterator nodeIterator = _editor.getNodeList()->begin(); nodeIterator != _editor.getNodeList()->end(); ++nodeIterator)
        {
            if(nodeIterator->getIsSelectedState())
            {
                double radius = nodeIterator->getDistance(aboutPoint);
                
                for(unsigned int i = 1; i < (numberOfCopies + 1); i++)
                {
                    double horizontalShift = (nodeIterator->getCenterXCoordinate() - aboutPoint.x) * cos(i * tempShift * PI / 180.0) + (nodeIterator->getCenterYCoordinate() - aboutPoint.y) * sin(i * tempShift * PI / 180.0) + aboutPoint.x;
                    double verticalShift = -(nodeIterator->getCenterXCoordinate() - aboutPoint.x) * sin(i * tempShift * PI / 180.0) + (nodeIterator->getCenterYCoordinate() - aboutPoint.y) * cos(i * tempShift * PI / 180.0) + aboutPoint.y;
                    // Update the node with the translated coordinates
                    if(_editor.addNode(horizontalShift, verticalShift, getTolerance() / 100.0))
                        _editor.getLastNodeAdd()->setNodeSettings(*nodeIterator->getNodeSetting());
                }
                nodeIterator->setSelectState(false);
            }
        }
        _nodesAreSelected = false;
    }
    
    if(_labelsAreSelected || _geometryGroupIsSelected)
    {
        double tempShift = -angularShift;
        for(plf::colony<blockLabel>::iterator blockIterator = _editor.getBlockLabelList()->begin(); blockIterator != _editor.getBlockLabelList()->end(); ++blockIterator)
        {
            if(blockIterator->getIsSelectedState())
            {
                double radius = blockIterator->getDistance(aboutPoint);
                
                for(unsigned int i = 1; i < (numberOfCopies + 1); i++)
                {
                    double horizontalShift = (blockIterator->getCenterXCoordinate() - aboutPoint.x) * cos(i * tempShift * PI / 180.0) + (blockIterator->getCenterYCoordinate() - aboutPoint.y) * sin(i * tempShift * PI / 180.0) + aboutPoint.x;
                    double verticalShift = -(blockIterator->getCenterXCoordinate() - aboutPoint.x) * sin(i * tempShift * PI / 180.0) + (blockIterator->getCenterYCoordinate() - aboutPoint.y) * cos(i * tempShift * PI / 180.0) + aboutPoint.y;
                    if(_editor.addBlockLabel(horizontalShift, verticalShift, getTolerance() / 100.0))
                        _editor.getLastBlockLabelAdded()->setPorperty(*blockIterator->getProperty());
                }
                blockIterator->setSelectState(false);
            }
        }
        _labelsAreSelected = false;
    }
    
    _geometryGroupIsSelected = false;
    
    this->Refresh();
    return;
}



void modelDefinition::displayDanglingNodes()
{
    clearSelection();
    
    _nodesAreSelected = true;
    
    for(plf::colony<node>::iterator nodeIterator = _editor.getNodeList()->begin(); nodeIterator != _editor.getNodeList()->end(); ++nodeIterator)
    {
        int numberOfConnectedLines = 0;
        
        for(plf::colony<edgeLineShape>::iterator lineIterator = _editor.getLineList()->begin(); lineIterator != _editor.getLineList()->end(); ++lineIterator)
        {
            if((*lineIterator->getFirstNode() == *nodeIterator || *lineIterator->getSecondNode() == *nodeIterator) && !lineIterator->getSegmentProperty()->getHiddenState())
                numberOfConnectedLines++;
        }
        
        if(numberOfConnectedLines <= 1)
        {
            for(plf::colony<arcShape>::iterator arcIterator = _editor.getArcList()->begin(); arcIterator != _editor.getArcList()->end(); ++arcIterator)
            {
                if((*arcIterator->getFirstNode() == *nodeIterator || *arcIterator->getSecondNode() == *nodeIterator) && !arcIterator->getSegmentProperty()->getHiddenState())
                    numberOfConnectedLines++;
            }
        }
        
        // If we only have a node connected to 1 arc or line, then we have a dangling node */
        if(numberOfConnectedLines <= 1)
            nodeIterator->setSelectState(true);
    }
    
    this->Refresh();
    return;
}



void modelDefinition::createOpenBoundary(unsigned int numberLayers, double radius, wxRealPoint centerPoint, OpenBoundaryEdge boundaryType)
{
    for(unsigned int i = 0; i < numberLayers + 1; i++)
    {
        // These guys are used to make sure that we can add another arc in the same process since the add arc function will reset the indexes.
        plf::colony<node>::iterator tempIteratorOne, tempIteratorTwo;
        
        // Attempt to add in the first node
        if(_editor.addNode(radius + i * 0.5, centerPoint.y, 0))
        {
            // Add in any node properties here
            tempIteratorOne = _editor.getLastNodeAdd();
            _editor.setNodeIndex(*tempIteratorOne);
        }
        else
        {
            node testNode;
            testNode.setCenter(radius + i * 0.5, centerPoint.y);
            for(plf::colony<node>::iterator nodeIterator = _editor.getNodeList()->begin(); nodeIterator != _editor.getNodeList()->end(); ++nodeIterator)
            {
                if(*nodeIterator == testNode || nodeIterator->getDistance(testNode) < getTolerance())
                {
                    _editor.setNodeIndex(*nodeIterator);
                    tempIteratorOne = nodeIterator;
                    break;
                }
            }
        }
        
        // Attempt to add in the second node of the arc
        if(_editor.addNode(-radius - i * 0.5, centerPoint.y, 0))
        {
            // Add in any node properties here
            tempIteratorTwo = _editor.getLastNodeAdd();
            _editor.setNodeIndex(*tempIteratorTwo);
        }
        else
        {
            node testNode;
            testNode.setCenter(-radius - i * 0.5, centerPoint.y);
            for(plf::colony<node>::iterator nodeIterator = _editor.getNodeList()->begin(); nodeIterator != _editor.getNodeList()->end(); ++nodeIterator)
            {
                if(*nodeIterator == testNode || nodeIterator->getDistance(testNode) < getTolerance())
                {
                    _editor.setNodeIndex(*nodeIterator);
                    tempIteratorTwo = nodeIterator;
                    break;
                }
            }
        }
        
        arcShape tempArcOne, tempArcTwo;
        tempArcOne.setArcAngle(180.0);// Create the arc with the arc in a positive direction
        tempArcOne.setNumSegments(50);
        if(_editor.addArc(tempArcOne, 0, true) && boundaryType == OpenBoundaryEdge::DIRICHLET)
        {
            if(_localDefinition->getPhysicsProblem() == physicProblems::PROB_ELECTROSTATIC)
                _editor.getLastArcAdded()->getSegmentProperty()->setBoundaryName("V=0");
            else
                _editor.getLastArcAdded()->getSegmentProperty()->setBoundaryName("A=0");
        }
        
        // Reverse the selected nodes (since all angles of the arc need to be positive)
        _editor.setNodeIndex(*tempIteratorTwo);
        _editor.setNodeIndex(*tempIteratorOne);
        
        // Set some basic arc properties
        tempArcTwo.setArcAngle(180.0);
        tempArcTwo.setNumSegments(50);
        
        if(_editor.addArc(tempArcTwo, 0, true) && boundaryType == OpenBoundaryEdge::DIRICHLET)
        {
            if(_localDefinition->getPhysicsProblem() == physicProblems::PROB_ELECTROSTATIC)
                _editor.getLastArcAdded()->getSegmentProperty()->setBoundaryName("V=0");
            else
                _editor.getLastArcAdded()->getSegmentProperty()->setBoundaryName("A=0");
        }
        
        if(i < numberLayers)
        {
            if(_editor.addBlockLabel(centerPoint.x + ((radius + 0.25 + i * 0.5) * cos(i * (90.0 / (double)numberLayers) * PI / 180.0)), centerPoint.y + ((radius + 0.25 + i * 0.5) * sin(i * (90.0 / (double)numberLayers) * PI / 180.0)), 0))
            {
                if(_localDefinition->getPhysicsProblem() == physicProblems::PROB_ELECTROSTATIC)
                {
                    wxString baseString = "e";
                    baseString.append(std::to_string(i + 1));
                    _editor.getLastBlockLabelAdded()->getProperty()->setMaterialName(baseString.ToStdString());
                }
                else
                {
                    wxString baseString = "u";
                    baseString.append(std::to_string(i + 1));
                    _editor.getLastBlockLabelAdded()->getProperty()->setMaterialName(baseString.ToStdString());
                }
            }
        }
    }
    this->Refresh();
    return;
}



void modelDefinition::getBoundingBox(wxRealPoint &pointOne, wxRealPoint &pointTwo)
{
    if((_nodesAreSelected || _geometryGroupIsSelected) && _editor.getNodeList()->size() > 0)
    {
        // First, we have to assign the iniitial value of the pointOne and pointTwo. This initial value needs to be one of the nodes in the selection
        for(plf::colony<node>::iterator nodeIterator = _editor.getNodeList()->begin(); nodeIterator != _editor.getNodeList()->end(); ++nodeIterator)
        {
            if(nodeIterator->getIsSelectedState())
            {
                pointOne.x = nodeIterator->getCenterXCoordinate();
                pointOne.y = nodeIterator->getCenterYCoordinate();
                
                pointTwo.x = nodeIterator->getCenterXCoordinate();
                pointTwo.y = nodeIterator->getCenterYCoordinate();
                break;
            }
        }
        
        // NOw we can iterate through all of the selected nodes and detemine the coordiantes of the boundaing box
        for(plf::colony<node>::iterator nodeIterator = _editor.getNodeList()->begin(); nodeIterator != _editor.getNodeList()->end(); ++nodeIterator)
        {
            if(nodeIterator->getIsSelectedState())
            {
                pointOne.x = std::min(nodeIterator->getCenterXCoordinate(), pointOne.x);
                pointTwo.x = std::max(nodeIterator->getCenterXCoordinate(), pointTwo.x);
                
                pointOne.y = std::max(nodeIterator->getCenterYCoordinate(), pointOne.y);
                pointTwo.y = std::min(nodeIterator->getCenterYCoordinate(), pointTwo.y);
            }
        }
    }
    
    if(_labelsAreSelected || _geometryGroupIsSelected)
    {
        if(!_geometryGroupIsSelected)
        {
            for(plf::colony<blockLabel>::iterator blockIterator = _editor.getBlockLabelList()->begin(); blockIterator != _editor.getBlockLabelList()->end(); ++blockIterator)
            {
                if(blockIterator->getIsSelectedState())
                {
                    pointOne.x = blockIterator->getCenterXCoordinate();
                    pointOne.y = blockIterator->getCenterYCoordinate();
                    
                    pointTwo.x = blockIterator->getCenterXCoordinate();
                    pointTwo.y = blockIterator->getCenterYCoordinate();
                    break;
                }
            }
        }
        
        
        for(plf::colony<blockLabel>::iterator blockIterator = _editor.getBlockLabelList()->begin(); blockIterator != _editor.getBlockLabelList()->end(); ++blockIterator)
        {
            if(blockIterator->getIsSelectedState())
            {
                pointOne.x = std::min(blockIterator->getCenterXCoordinate(), pointOne.x);
                pointTwo.x = std::max(blockIterator->getCenterXCoordinate(), pointTwo.x);
                
                pointOne.y = std::max(blockIterator->getCenterYCoordinate(), pointOne.y);
                pointTwo.y = std::min(blockIterator->getCenterYCoordinate(), pointTwo.y);
            }
        } 
    }
    
    if(_linesAreSelected || _geometryGroupIsSelected)
    {
        if(!_geometryGroupIsSelected)
        {
           for(plf::colony<edgeLineShape>::iterator lineIterator = _editor.getLineList()->begin(); lineIterator != _editor.getLineList()->end(); ++lineIterator)
            {
                if(lineIterator->getIsSelectedState())
                {
                    pointOne.x = lineIterator->getFirstNode()->getCenterXCoordinate();
                    pointOne.y = lineIterator->getFirstNode()->getCenterYCoordinate();
                    
                    pointTwo.x = lineIterator->getSecondNode()->getCenterXCoordinate();
                    pointTwo.y = lineIterator->getSecondNode()->getCenterYCoordinate();
                    
                    break;
                }
            } 
        }
        
        for(plf::colony<edgeLineShape>::iterator lineIterator = _editor.getLineList()->begin(); lineIterator != _editor.getLineList()->end(); ++lineIterator)
        {
            if(lineIterator->getIsSelectedState())
            {
                pointOne.x = std::min(lineIterator->getFirstNode()->getCenterXCoordinate(), pointOne.x);
                pointTwo.x = std::max(lineIterator->getFirstNode()->getCenterXCoordinate(), pointTwo.x);
                
                pointOne.y = std::max(lineIterator->getFirstNode()->getCenterYCoordinate(), pointOne.y);
                pointTwo.y = std::min(lineIterator->getFirstNode()->getCenterYCoordinate(), pointTwo.y);
                
                pointOne.x = std::min(lineIterator->getSecondNode()->getCenterXCoordinate(), pointOne.x);
                pointTwo.x = std::max(lineIterator->getSecondNode()->getCenterXCoordinate(), pointTwo.x);
                
                pointOne.y = std::max(lineIterator->getSecondNode()->getCenterYCoordinate(), pointOne.y);
                pointTwo.y = std::min(lineIterator->getSecondNode()->getCenterYCoordinate(), pointTwo.y);
            }
        }
    }
    
    if(_arcsAreSelected || _geometryGroupIsSelected)
    {
        if(!_geometryGroupIsSelected)
        {
           for(plf::colony<arcShape>::iterator arcIterator = _editor.getArcList()->begin(); arcIterator != _editor.getArcList()->end(); ++arcIterator)
            {
                if(arcIterator->getIsSelectedState())
                {
                    pointOne.x = arcIterator->getFirstNode()->getCenterXCoordinate();
                    pointOne.y = arcIterator->getFirstNode()->getCenterYCoordinate();
                    
                    pointTwo.x = arcIterator->getSecondNode()->getCenterXCoordinate();
                    pointTwo.y = arcIterator->getSecondNode()->getCenterYCoordinate();
                    
                    break;
                }
            } 
        }
        
        
        for(plf::colony<arcShape>::iterator arcIterator = _editor.getArcList()->begin(); arcIterator != _editor.getArcList()->end(); ++arcIterator)
        {
            // In case you are wondering, the recalculation of the arc's radius and center position occurs within the function that does the scaling
            if(arcIterator->getIsSelectedState())
            {
                pointOne.x = std::min(arcIterator->getFirstNode()->getCenterXCoordinate(), pointOne.x);
                pointTwo.x = std::max(arcIterator->getFirstNode()->getCenterXCoordinate(), pointTwo.x);
                
                pointOne.y = std::max(arcIterator->getFirstNode()->getCenterYCoordinate(), pointOne.y);
                pointTwo.y = std::min(arcIterator->getFirstNode()->getCenterYCoordinate(), pointTwo.y);
                
                pointOne.x = std::min(arcIterator->getSecondNode()->getCenterXCoordinate(), pointOne.x);
                pointTwo.x = std::max(arcIterator->getSecondNode()->getCenterXCoordinate(), pointTwo.x);
                
                pointOne.y = std::max(arcIterator->getSecondNode()->getCenterYCoordinate(), pointOne.y);
                pointTwo.y = std::min(arcIterator->getSecondNode()->getCenterYCoordinate(), pointTwo.y);
            }
        }
    }
    
    return;
}



void modelDefinition::createFillet(double filletRadius)
{
    // A check to ensure that the _editor.createFillet is never executed with a negative radius
    if(filletRadius < 0)
        return;
        
    _editor.createFillet(filletRadius);
    this->Refresh();
    return;
}



void modelDefinition::doZoomWindow()
{
    if(fabs(_endPoint.x - _startPoint.x) == 0 || fabs(_endPoint.y - _startPoint.y) == 0)
        return;
    
    double centerX = (_endPoint.x + _startPoint.x) / 2.0;
    double centerY = (_endPoint.y + _startPoint.y) / 2.0;
    
    /* These numbers calculate the distance between the center of the zoom window and the endpoints */
    double num1 = centerX - _startPoint.x;
    double num2 = _endPoint.x - centerX;
    double num3 = _startPoint.y - centerY;
    double num4 = centerY - _endPoint.y;
    
    _zoomX = fabs(std::max(num1, num2));
    _zoomY = fabs(std::max(num3, num4));
    
    _cameraX = centerX;
    _cameraY = centerY;
    
    return;
}



void modelDefinition::updateProjection()
{
        // First, load the projection matrix and reset the view to a default view
    glViewport(0, 0, (double)this->GetSize().GetWidth(), (double)this->GetSize().GetHeight());
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    double aspectRatio = (double)this->GetSize().GetWidth() / (double)this->GetSize().GetHeight();
    
    /*
     * So the bug is this that when the window is not the same for the width and height, everything is squashed.
     * We need to take into account the aspect ratio of the viewport. Thankfully, the size of the viewport is 
     * equal to the size of the canvas so this makes that math really easy.
     * Basically, the fix is is that we need to multiply the x zoom factor by the aspect ratio
     * in order for openGL to "resize" according to the aspect factor. This will case the x coordinate plane
     * to become more "dense" in the number of coordinate positions that it can hold.
     * For some more explanation on the matter, refer to the following link:
     * 
     * http://stackoverflow.com/questions/9071814/opengl-stretched-shapes-aspect-ratio
     * 
     */

    /* This section will handle the zooming. 
     * Needs to be called each time a draw occurs in order to update the placement of all the components */
    if(_zoomX < 1e-9 || _zoomY < 1e-9)
    {
        _zoomX = 1e-9;
        _zoomY = _zoomX;
    }
    
    if(_zoomX > 1e6 || _zoomY > 1e6)
    {
        _zoomX = 1e6;
        _zoomY = _zoomX;
    }
 
    glOrtho(-_zoomX * aspectRatio, _zoomX * aspectRatio, -_zoomY, _zoomY, -1.0, 1.0);
    
    //Reset to modelview matrix. This section handles the panning
	glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

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
            if(((cornerMaxX - cornerMinX) / _preferences.getGridStep() + (cornerMinY - cornerMaxY) / _preferences.getGridStep() < 300) && ((cornerMaxX - cornerMinX) / _preferences.getGridStep() > 0) && ((cornerMinY - cornerMaxY) / _preferences.getGridStep() > 0))
            {
                /* Create the grid for the vertical lines first */
                for(int i = cornerMinX / _preferences.getGridStep() - 1; i < cornerMaxX / _preferences.getGridStep() + 1; i++)
                {
                    if(i % 4 == 0)
                    {
                        glLineWidth(1.5);
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
                        glLineWidth(1.5);
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
        glLineWidth(1.7);
    
        glBegin(GL_LINES);
            glVertex2d(0, cornerMinY);
            glVertex2d(0, cornerMaxY);
        
            glVertex2d(cornerMinX, 0);
            glVertex2d(cornerMaxX, 0);
        glEnd();
        glLineWidth(0.5);// Resets the line width back to the default
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



void modelDefinition::clearSelection()
{

    for(plf::colony<node>::iterator nodeIterator = _editor.getNodeList()->begin(); nodeIterator != _editor.getNodeList()->end(); ++nodeIterator)
    {
        if(nodeIterator->getIsSelectedState())
            nodeIterator->setSelectState(false);
    }

    
    for(plf::colony<blockLabel>::iterator blockIterator = _editor.getBlockLabelList()->begin(); blockIterator != _editor.getBlockLabelList()->end(); ++blockIterator)
    {
        if(blockIterator->getIsSelectedState())
            blockIterator->setSelectState(false);
    }

    
    for(plf::colony<edgeLineShape>::iterator lineIterator = _editor.getLineList()->begin(); lineIterator != _editor.getLineList()->end(); ++lineIterator)
    {
        if(lineIterator->getIsSelectedState())
            lineIterator->setSelectState(false);
    }
    
    for(plf::colony<arcShape>::iterator arcIterator = _editor.getArcList()->begin(); arcIterator != _editor.getArcList()->end(); ++arcIterator)
    {
        if(arcIterator->getIsSelectedState())
            arcIterator->setSelectState(false);
    }

    
    _editor.resetIndexs();
    
    _nodesAreSelected = false;
    _linesAreSelected = false;
    _arcsAreSelected = false;
    _labelsAreSelected = false;
    _geometryGroupIsSelected = false;
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
    
    for(plf::colony<edgeLineShape>::iterator lineIterator = _editor.getLineList()->begin(); lineIterator != _editor.getLineList()->end(); ++lineIterator)
    {
        lineIterator->draw();
    }
    
    for(plf::colony<arcShape>::iterator arcIterator = _editor.getArcList()->begin(); arcIterator != _editor.getArcList()->end(); ++arcIterator)
    {
        arcIterator->draw();
    }
    
    for(plf::colony<node>::iterator nodeIterator = _editor.getNodeList()->begin(); nodeIterator != _editor.getNodeList()->end(); ++nodeIterator)
    {
        nodeIterator->draw();
    }
    
    for(plf::colony<blockLabel>::iterator blockIterator = _editor.getBlockLabelList()->begin(); blockIterator != _editor.getBlockLabelList()->end(); ++blockIterator)
    {
        blockIterator->draw();
        if(_preferences.getShowBlockNameState() && !blockIterator->getDraggingState())
        {
            blockIterator->drawBlockName(_fontRender, (_zoomX + _zoomY) / 2.0);
            if(_localDefinition->getPhysicsProblem() == physicProblems::PROB_MAGNETICS)
                blockIterator->drawCircuitName(_fontRender, (_zoomX + _zoomY) / 2.0);
        }
    }

    if(_doZoomWindow || _doSelectionWindow)// We are going to be drawing the same thing for this one
    {
        glLineWidth(3.0);
        glEnable(GL_LINE_STIPPLE);
        glLineStipple(1, 0b0001100011000110);
    
        glBegin(GL_LINES);
            glColor3d(0.0, 0.0, 0.0);
            glVertex2d(_startPoint.x, _startPoint.y);
            glVertex2d(_startPoint.x, _endPoint.y);
            
            glVertex2d(_startPoint.x, _endPoint.y);
            glVertex2d(_endPoint.x, _endPoint.y);
            
            glVertex2d(_endPoint.x, _endPoint.y);
            glVertex2d(_endPoint.x, _startPoint.y);
            
            glVertex2d(_endPoint.x, _startPoint.y);
            glVertex2d(_startPoint.x, _startPoint.y);
        glEnd();
        glDisable(GL_LINE_STIPPLE);
    }
    
    if(_doMirrorLine)
    {
        glLineWidth(3.0);
        glEnable(GL_LINE_STIPPLE);
        
   
        glLineStipple(1, 0b0001100011000110);
        glColor3d(0.0, 0.0, 0.0);
        glBegin(GL_LINES);
            glVertex2d(_startPoint.x, _startPoint.y);
            glVertex2d(_endPoint.x, _endPoint.y);
        glEnd();
         
        glDisable(GL_LINE_STIPPLE);
    }
    /*
     * This resets the color back to 0. Actually,
     * if this command is not called,
     * the white dot that is ontop of the black dot for a node
     * (To draw a node, we have a black point drawn first and 
     * a white point drawn ontop of it)
     * will not be drawn for the last node added
     */ 
    glColor3f(0.0, 0.0, 0.0);
    glColor3d(0.0, 0.0, 0.0);
  
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
        
        _cameraX += (((2.0 / (double)this->GetSize().GetWidth()) * (event.GetX() - (double)this->GetSize().GetWidth() / 2.0)) * _zoomX) * ((double)this->GetSize().GetWidth() / (double)this->GetSize().GetHeight());
        _cameraY += (-(2.0 / (double)this->GetSize().GetHeight()) * (event.GetY() - (double)this->GetSize().GetHeight() / 2.0)) * _zoomY;
        
        if(!_preferences.getMouseZoomReverseState())
        {
            if(event.GetWheelRotation() > 0)
            {
                _zoomX *= pow(1.2, -(event.GetWheelDelta()) / 150.0);
                _zoomY *= pow(1.2, -(event.GetWheelDelta()) / 150.0);
                if(_zoomX > _zoomY)
                    _zoomY = _zoomX;
                else if(_zoomY > _zoomX)
                    _zoomX = _zoomY;
            }
            else
            {
                _zoomX *= pow(1.2, (event.GetWheelDelta()) / 150.0);
                _zoomY *= pow(1.2, (event.GetWheelDelta()) / 150.0);
                if(_zoomX > _zoomY)
                    _zoomY = _zoomX;
                else if(_zoomY > _zoomX)
                    _zoomX = _zoomY;
            }
        }
        else
        {
            if(event.GetWheelRotation() < 0)
            {
                _zoomX *= pow(1.2, -(event.GetWheelDelta()) / 150.0);
                _zoomY *= pow(1.2, -(event.GetWheelDelta()) / 150.0);
                if(_zoomX > _zoomY)
                    _zoomY = _zoomX;
                else if(_zoomY > _zoomX)
                    _zoomX = _zoomY;
            }
            else
            {
                _zoomX *= pow(1.2, (event.GetWheelDelta()) / 150.0);
                _zoomY *= pow(1.2, (event.GetWheelDelta()) / 150.0);
                if(_zoomX > _zoomY)
                    _zoomY = _zoomX;
                else if(_zoomY > _zoomX)
                    _zoomX = _zoomY;
            }
        }
        
        /* This will recalculate the new position of the mouse. Assuming that the mouse does not move at all during the process
         * This also enables the feature where the zoom will zoom in/out at the position of the mouse */
        
        _cameraX -= (((2.0 / (double)this->GetSize().GetWidth()) * (event.GetX() - (double)this->GetSize().GetWidth() / 2.0)) * _zoomX) * ((double)this->GetSize().GetWidth() / (double)this->GetSize().GetHeight());
        _cameraY -= (-(2.0 / (double)this->GetSize().GetHeight()) * (event.GetY() - (double)this->GetSize().GetHeight() / 2.0)) * _zoomY;
    }
	
    this->Refresh();// This will force the canvas to experience a redraw event
}



void modelDefinition::onMouseMove(wxMouseEvent &event)
{
 //   wxCommandEvent updateStatusInformation;
 //   updateStatusInformation.
 //   wxEvent updateStatusBarEvent;
    wxCommandEvent customEvent(MOUSE_MOVE);
    
    int dx = event.GetX() - _mouseXPixel;
    int dy = event.GetY() - _mouseYPixel;
    
	_mouseXPixel = event.GetX();
	_mouseYPixel = event.GetY();
    

    
 //   customEvent.SetString(combinedString);
 //   wxPostEvent(this->GetParent(), customEvent);
    
    
    
    if(event.ButtonIsDown(wxMOUSE_BTN_MIDDLE))
    {
        /* For the _cameraX variable, this is -= instead of +=. For those not as inclined in math, this maybe confusing.
         * The program always takes the current position as the reference. To get the distan between two points (in one dimension in the x-plane) normally
         * you would perform x1 - x2 = d where x1 > x2. This would give you a positive answer. However, since x1 is equal to the current position, then if
         * x2 > x1, you get a negative answer. Therefor, you have the multiple the result by -1 in order to for the distance to be positive and add this result to 
         * the current position in order to move the point to the right. In the case that x2 < x1, then the distance is negative and you simply have to add the negative number to 
         * the current position in order to move the point to the left. Hence the need to have _camerX -= and not +=. This is not the case for _cameraY.
         * The _cameraY variable behaves more normal since we already take into account the postional shift in the equation
         */ 
        _cameraX -= (2.0 / (double)this->GetSize().GetWidth()) * ((double)dx * _zoomX) * ((double)this->GetSize().GetWidth() / (double)this->GetSize().GetHeight());
        _cameraY += (2.0 / (double)this->GetSize().GetHeight()) * ((double)dy * _zoomY);
        this->Refresh();
        return;
    }
    else if(event.ButtonIsDown(wxMOUSE_BTN_LEFT))
    {
        if(!_doZoomWindow && !_doMirrorLine)
        {
            if(_createNodes && !_geometryIsSelected)
            {
                if(_editor.getNodeList()->size() > 0 && _editor.getLastNodeAdd()->getDraggingState())
                {
                    double tempX = convertToXCoordinate(event.GetX());
                    double tempY = convertToYCoordinate(event.GetY());
                    if(_preferences.getSnapGridState())
                        roundToNearestGrid(tempX, tempY);
                    _editor.getLastNodeAdd()->setCenter(tempX, tempY);
                }
            }
            else if(!_createNodes)
            {
                if(_editor.getBlockLabelList()->size() > 0 && _editor.getLastBlockLabelAdded()->getDraggingState())
                {
                    double tempX = convertToXCoordinate(event.GetX());
                    double tempY = convertToYCoordinate(event.GetY());
                    if(_preferences.getSnapGridState())
                        roundToNearestGrid(tempX, tempY);
                    _editor.getLastBlockLabelAdded()->setCenter(tempX, tempY);
                }
            }
        }
        else if(_doZoomWindow || _doMirrorLine)
        {
            double tempX = convertToXCoordinate(event.GetX());
            double tempY = convertToYCoordinate(event.GetY());
            if(_preferences.getSnapGridState())
                roundToNearestGrid(tempX, tempY);
                
            _endPoint = wxRealPoint(tempX, tempY);
        }
    }
    else if(event.ButtonIsDown(wxMOUSE_BTN_RIGHT))
    {
        if(_doSelectionWindow)
        {
            _endPoint = wxRealPoint(convertToXCoordinate(event.GetX()), convertToYCoordinate(event.GetY()));
        }
    }
    
    std::stringstream xStream;
    std::stringstream yStream;
    
    xStream << std::fixed << std::setprecision(4) << convertToXCoordinate(_mouseXPixel);
    yStream << std::fixed << std::setprecision(4) << convertToYCoordinate(_mouseYPixel);
    
    wxString xCoordinateString = wxString(xStream.str());
    wxString yCoordinateString = wxString(yStream.str());
    wxString combinedString = wxString("(") + xCoordinateString + wxString(", ") + yCoordinateString + wxString(")");
    
    if(_localDefinition->getShowStatusBarState())
        _statusBarTopWindow->SetStatusText(wxString("Omni-FEM Simulator: ") + combinedString);
    
    this->Refresh();
    return;
}



void modelDefinition::onMouseLeftDown(wxMouseEvent &event)
{
    wxGLCanvas::SetCurrent(*_geometryContext);
    bool createArc = false;
    
    if(!_doZoomWindow && !_doMirrorLine)
    {    
        if(_createNodes)
        {
            for(plf::colony<node>::iterator nodeIterator = _editor.getNodeList()->begin(); nodeIterator != _editor.getNodeList()->end(); ++nodeIterator)
            {
                if(nodeIterator->getDistance(convertToXCoordinate(event.GetX()), convertToYCoordinate(event.GetY())) < getTolerance())// The multiplier will be some number between 10 and 100
                {
                    if(_editor.setNodeIndex(*nodeIterator))
                    {
                        
                        if(_createLines)
                        {
                            //Create the line
                            _editor.addLine();
                            _geometryIsSelected = false;
                            clearSelection();
                            this->Refresh();
                            return;
                        }
                        else
                        {
                            
                            createArc = true;
                            nodeIterator->setSelectState(true);
                            _geometryIsSelected = false;
                            this->Refresh();
                            break;
                        }
                    }
                    else
                    {
                        //Toggle the node to be selected
                        nodeIterator->setSelectState(true);
                        _geometryIsSelected = true;
                        this->Refresh();
                        return;
                    }
                }
            }
            
            if(!createArc)
            {
                double tempX = convertToXCoordinate(event.GetX());
                double tempY = convertToYCoordinate(event.GetY());
                //Create the node at the point of the mouse with grid snapping
                if(_preferences.getSnapGridState())
                    roundToNearestGrid(tempX, tempY);
                _editor.addDragNode(tempX, tempY);
                
                _geometryIsSelected = false;
                _editor.resetIndexs();
                clearSelection();
                this->Refresh();// Draw the node at the mouse location
                return;
            }
        }
        else
        {
            double tempX = convertToXCoordinate(event.GetX());
            double tempY = convertToYCoordinate(event.GetY());
            if(_preferences.getSnapGridState())
                roundToNearestGrid(tempX, tempY);
                
            _editor.addDragBlockLabel(tempX, tempY);
            
            clearSelection();
            this->Refresh();
            return;
        }
    }
    else if(_doZoomWindow || _doMirrorLine)
    {
        double tempX = convertToXCoordinate(event.GetX());
        double tempY = convertToYCoordinate(event.GetY());
        
        if(_preferences.getSnapGridState())
            roundToNearestGrid(tempX, tempY);
            
        _startPoint = wxRealPoint(tempX, tempY);
        _endPoint = wxRealPoint(tempX, tempY);
        
        this->Refresh();
        return;
    }
    
    if(createArc)
    {
        arcSegmentDialog *newArcDialog;
                            
        if(_localDefinition->getPhysicsProblem() == physicProblems::PROB_ELECTROSTATIC)
        {
            arcSegmentDialog *newArcDialog = new arcSegmentDialog(this, _localDefinition->getElectricalBoundaryList());
            if(newArcDialog->ShowModal() == wxID_OK)
            {
                arcShape tempShape;
                newArcDialog->getArcParameter(tempShape);
                _editor.addArc(tempShape, getTolerance(), true);
                this->Refresh();
                clearSelection();
                return;
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
                _editor.addArc(tempShape, getTolerance(), true);
                this->Refresh();
                clearSelection();
                return;
            }
            else
                _editor.resetIndexs();
            delete(newArcDialog);
        }
    }
    
    this->Refresh();
    clearSelection();
    return;
}

void modelDefinition::onMouseLeftUp(wxMouseEvent &event)
{
    if(!_doZoomWindow && !_doMirrorLine)
    {
        // OK so in order to re-validate the node (in order to break lines / arcs up into two pieces and what not), we first have to remove the last item, and then push it back on.
        if(_createNodes)
        {
            /* Bug fix here. A bug where if an empty canvas would get resized to full screen by double clicking on the top bar of the form, the program would sometimes crash
             * The issue was that the program was checking to see if the last node (or block label) was in a dragging state.
             * However, the last node doesn't exist.
             * The form would reload so quickly that sometimes the canvas would be able to detect the user on the releasing the left mouse.
             * The fix, check to make sure that the size of the array (vector) is greater then 0 to ensure the program does not check an empty 
             * position
             */ 
            if(_editor.getNodeList()->size() > 0 && _editor.getLastNodeAdd()->getDraggingState())
            {
                double tempX = convertToXCoordinate(event.GetX());
                double tempY = convertToYCoordinate(event.GetY());
                
                if(_preferences.getSnapGridState())
                    roundToNearestGrid(tempX, tempY);
                    
                _editor.getNodeList()->erase(_editor.getLastNodeAdd());
                _editor.addNode(tempX, tempY, getTolerance());
            }
        }
        else
        {
            if(_editor.getBlockLabelList()->size() > 0)
            {
                double tempX = convertToXCoordinate(event.GetX());
                double tempY = convertToYCoordinate(event.GetY());

                if(_preferences.getSnapGridState())
                    roundToNearestGrid(tempX, tempY);

                if(_editor.getLastBlockLabelAdded()->getDraggingState())
                {
                    _editor.getBlockLabelList()->erase(_editor.getLastBlockLabelAdded()); 
                    _editor.addBlockLabel(tempX, tempY, getTolerance());
                }
                
                /* Now we want to scan through the entire block label list to finc if there is one that is
                 * set to defualt, if there is, then copy the settings to the newly created label
                 */
                for(plf::colony<blockLabel>::iterator blockIterator = _editor.getBlockLabelList()->begin(); blockIterator != _editor.getBlockLabelList()->end(); ++blockIterator)
                {
                    if(blockIterator->getProperty()->getDefaultState())
                    {
                        _editor.getLastBlockLabelAdded()->setPorperty(*blockIterator->getProperty());
                        _editor.getLastBlockLabelAdded()->getProperty()->setDefaultState(false);
                        break;
                    }
                }
            }
        }
    }
    else if(_doZoomWindow && !_doMirrorLine)
    {
        _doZoomWindow = !_doZoomWindow;
        doZoomWindow();
        _startPoint = wxRealPoint(0, 0);
        _endPoint = wxRealPoint(0, 0);
    }
    else if(!_doZoomWindow && _doMirrorLine)
    {
        _doMirrorLine = !_doMirrorLine;
        mirrorSelection(_startPoint, _endPoint);
        _startPoint = wxRealPoint(0, 0);
        _endPoint = wxRealPoint(0, 0);
    }
    
    this->Refresh();
    return;
}



void modelDefinition::roundToNearestGrid(double &xCoordinate, double &yCoordinate)
{
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
    _startPoint = wxRealPoint(convertToXCoordinate(event.GetX()), convertToYCoordinate(event.GetY()));
    _endPoint = _startPoint;
    _doSelectionWindow = true;
}



void modelDefinition::onMouseRightUp(wxMouseEvent &event)
{
    /* these nodes are only meant to keep track of the number of shapes selected and to assist with setting the boolean _(geometryName)isSelected */
    static unsigned int nodesSeleted = 0;
    static unsigned int labelsSelected = 0;
    static unsigned int linesSelected = 0;
    static unsigned int arcsSelected = 0;
        
    if(_startPoint == _endPoint)
    {
        for(plf::colony<node>::iterator nodeIterator = _editor.getNodeList()->begin(); nodeIterator != _editor.getNodeList()->end(); ++nodeIterator)
        {
            if(fabs(nodeIterator->getDistance(_startPoint.x, _startPoint.y)) < getTolerance())
            {
                // First, if there is any geometry selected, we need to remove it
                if(_linesAreSelected || _geometryGroupIsSelected)
                {
                    for(plf::colony<edgeLineShape>::iterator lineIterator = _editor.getLineList()->begin(); lineIterator != _editor.getLineList()->end(); ++lineIterator)
                    {
                        lineIterator->setSelectState(false);
                        linesSelected = 0;
                    }
                }
                
                if(_arcsAreSelected || _geometryGroupIsSelected)
                {
                   for(plf::colony<arcShape>::iterator arcIterator = _editor.getArcList()->begin(); arcIterator != _editor.getArcList()->end(); ++arcIterator)
                    {
                        arcIterator->setSelectState(false);
                        arcsSelected = 0;
                        
                    } 
                }
                
                if(_labelsAreSelected || _geometryGroupIsSelected)
                {
                   for(plf::colony<blockLabel>::iterator blockIterator = _editor.getBlockLabelList()->begin(); blockIterator != _editor.getBlockLabelList()->end(); ++blockIterator)
                    {
                        blockIterator->setSelectState(false);
                        labelsSelected = 0;
                    } 
                }
                
                nodeIterator->setSelectState(!(nodeIterator->getIsSelectedState()));

                _nodesAreSelected = true;
                
                /* I placed this inside of the if statement for every iteration because if there is one, then this is valid. But, if the user did not click on one, then this logic beecomes invalid */
                _linesAreSelected = false;
                _arcsAreSelected = false;
                _labelsAreSelected = false;
                _geometryIsSelected = false;
                
                if(nodeIterator->getIsSelectedState())
                    nodesSeleted++;
                else
                {
                    nodesSeleted--;
                    if(nodesSeleted == 0)
                        _nodesAreSelected = false;
                }
                _doSelectionWindow = false;
                this->Refresh();
                return;
            }
        }
        
        for(plf::colony<blockLabel>::iterator blockIterator = _editor.getBlockLabelList()->begin(); blockIterator != _editor.getBlockLabelList()->end(); ++blockIterator)
        {
            if(fabs(blockIterator->getDistance(_startPoint.x, _startPoint.y)) < getTolerance())
            {
                if(_nodesAreSelected || _geometryGroupIsSelected)
                {
                    for(plf::colony<node>::iterator nodeIterator = _editor.getNodeList()->begin(); nodeIterator != _editor.getNodeList()->end(); ++nodeIterator)
                    {
                        nodeIterator->setSelectState(false);
                        nodesSeleted = 0;
                    }
                }
                
                if(_arcsAreSelected || _geometryGroupIsSelected)
                {
                   for(plf::colony<arcShape>::iterator arcIterator = _editor.getArcList()->begin(); arcIterator != _editor.getArcList()->end(); ++arcIterator)
                    {
                        arcIterator->setSelectState(false);
                        arcsSelected = 0;
                    } 
                }
                
                if(_linesAreSelected || _geometryGroupIsSelected)
                {
                    for(plf::colony<edgeLineShape>::iterator lineIterator = _editor.getLineList()->begin(); lineIterator != _editor.getLineList()->end(); ++lineIterator)
                    {
                        lineIterator->setSelectState(false);
                        linesSelected = 0;
                    }
                }
                
                _labelsAreSelected = true;
                _nodesAreSelected = false;
                _linesAreSelected = false;
                _arcsAreSelected = false;
                _geometryIsSelected = false;
                
                blockIterator->setSelectState(!blockIterator->getIsSelectedState());
                
                if(blockIterator->getIsSelectedState())
                    labelsSelected++;
                else
                {
                    labelsSelected--;
                    if(labelsSelected == 0)
                        _labelsAreSelected = false;
                }
                
                _doSelectionWindow = false;
                this->Refresh();
                return;
            }
        }
        
        for(plf::colony<edgeLineShape>::iterator lineIterator = _editor.getLineList()->begin(); lineIterator != _editor.getLineList()->end(); ++lineIterator)
        {
            if(fabs(_editor.calculateShortestDistance(_endPoint, *lineIterator)) < getTolerance())
            {
                if(_nodesAreSelected || _geometryGroupIsSelected)
                {
                    for(plf::colony<node>::iterator nodeIterator = _editor.getNodeList()->begin(); nodeIterator != _editor.getNodeList()->end(); ++nodeIterator)
                    {
                        nodeIterator->setSelectState(false);
                        nodesSeleted = 0;
                    }
                }
                
                if(_arcsAreSelected || _geometryGroupIsSelected)
                {
                   for(plf::colony<arcShape>::iterator arcIterator = _editor.getArcList()->begin(); arcIterator != _editor.getArcList()->end(); ++arcIterator)
                    {
                        arcIterator->setSelectState(false);
                        arcsSelected = 0;
                    } 
                }
                
                if(_labelsAreSelected || _geometryGroupIsSelected)
                {
                   for(plf::colony<blockLabel>::iterator blockIterator = _editor.getBlockLabelList()->begin(); blockIterator != _editor.getBlockLabelList()->end(); ++blockIterator)
                    {
                        blockIterator->setSelectState(false);
                        labelsSelected = 0;
                    } 
                }
                
                _linesAreSelected = true;
                _nodesAreSelected = false;
                _labelsAreSelected = false;
                _arcsAreSelected = false;
                _geometryIsSelected = false;
                
                lineIterator->setSelectState(!lineIterator->getIsSelectedState());
                
                if(lineIterator->getIsSelectedState())
                    linesSelected++;
                else
                {
                    linesSelected--;
                    if(linesSelected == 0)
                        _linesAreSelected = false;
                }
                
                _doSelectionWindow = false;
                this->Refresh();
                return;
            }
        }
        
        for(plf::colony<arcShape>::iterator arcIterator = _editor.getArcList()->begin(); arcIterator != _editor.getArcList()->end(); ++arcIterator)
        {
            if(fabs(_editor.calculateShortestDistanceFromArc(_endPoint, *arcIterator)) < getTolerance())
            {
                if(_nodesAreSelected || _geometryGroupIsSelected)
                {
                    for(plf::colony<node>::iterator nodeIterator = _editor.getNodeList()->begin(); nodeIterator != _editor.getNodeList()->end(); ++nodeIterator)
                    {
                        nodeIterator->setSelectState(false);
                        nodesSeleted = 0;
                    }
                }
                else if(_linesAreSelected || _geometryGroupIsSelected)
                {
                    for(plf::colony<edgeLineShape>::iterator lineIterator = _editor.getLineList()->begin(); lineIterator != _editor.getLineList()->end(); ++lineIterator)
                    {
                        lineIterator->setSelectState(false);
                        linesSelected = 0;
                    }
                }
                else if(_labelsAreSelected || _geometryGroupIsSelected)
                {
                   for(plf::colony<blockLabel>::iterator blockIterator = _editor.getBlockLabelList()->begin(); blockIterator != _editor.getBlockLabelList()->end(); ++blockIterator)
                    {
                        blockIterator->setSelectState(false);
                        labelsSelected = 0;
                    } 
                }
                
                _arcsAreSelected = true;
                _nodesAreSelected = false;
                _labelsAreSelected = false;
                _linesAreSelected = false;
                _geometryIsSelected = false;
                
                arcIterator->setSelectState(!arcIterator->getIsSelectedState());
                
                if(arcIterator->getIsSelectedState())
                    arcsSelected++;
                else
                {
                    arcsSelected--;
                    if(arcsSelected == 0)
                        _arcsAreSelected = false;
                }
                
                _doSelectionWindow = false;
                this->Refresh();
                return;
            }
        }
        // basically, if nothing is selected, then we should clear everyhing
        /* This section is for if the user clicks on empty white space */
        if(_nodesAreSelected || _geometryGroupIsSelected)
        {
            for(plf::colony<node>::iterator nodeIterator = _editor.getNodeList()->begin(); nodeIterator != _editor.getNodeList()->end(); ++nodeIterator)
            {
                nodeIterator->setSelectState(false);
            }
            nodesSeleted = 0;
            _nodesAreSelected = false;
        }
        
        if(_linesAreSelected || _geometryGroupIsSelected)
        {
            for(plf::colony<edgeLineShape>::iterator lineIterator = _editor.getLineList()->begin(); lineIterator != _editor.getLineList()->end(); ++lineIterator)
            {
                lineIterator->setSelectState(false);
            }
            linesSelected = 0;
            _linesAreSelected = false;
        }
        
        if(_labelsAreSelected || _geometryGroupIsSelected)
        {
            for(plf::colony<blockLabel>::iterator blockIterator = _editor.getBlockLabelList()->begin(); blockIterator != _editor.getBlockLabelList()->end(); ++blockIterator)
            {
                blockIterator->setSelectState(false);
            }
            labelsSelected = 0;
            _labelsAreSelected = false;
        }
        
        if(_arcsAreSelected || _geometryGroupIsSelected)
        {
           for(plf::colony<arcShape>::iterator arcIterator = _editor.getArcList()->begin(); arcIterator != _editor.getArcList()->end(); ++arcIterator)
            {
                arcIterator->setSelectState(false);
            }
            arcsSelected = 0;
            _arcsAreSelected = false;
        }
        
        _geometryGroupIsSelected = false;
        _doSelectionWindow = false;
        this->Refresh();
        return;
    }
    else if(_endPoint.y > _startPoint.y && _endPoint.x < _startPoint.x)
    {
        // Make sure to clear out everything else first
        if(_arcsAreSelected || _geometryGroupIsSelected)
        {
           for(plf::colony<arcShape>::iterator arcIterator = _editor.getArcList()->begin(); arcIterator != _editor.getArcList()->end(); ++arcIterator)
            {
                arcIterator->setSelectState(false);
            }
            arcsSelected = 0;
            _arcsAreSelected = false;
        }
        
        if(_linesAreSelected || _geometryGroupIsSelected)
        {
            for(plf::colony<edgeLineShape>::iterator lineIterator = _editor.getLineList()->begin(); lineIterator != _editor.getLineList()->end(); ++lineIterator)
            {
                lineIterator->setSelectState(false);
            }
            linesSelected = 0;
            _linesAreSelected = false;
        }
        
        if(_createNodes)
        {
            // This is the case for if the user wants to select all of the nodes within the window
            
            if(_labelsAreSelected || _geometryGroupIsSelected)
            {
                // Clear out any selected labels
                for(plf::colony<blockLabel>::iterator blockIterator = _editor.getBlockLabelList()->begin(); blockIterator != _editor.getBlockLabelList()->end(); ++blockIterator)
                {
                    blockIterator->setSelectState(false);
                }
                labelsSelected = 0;
                _labelsAreSelected = false;
            }
            

            // If the control key is not down (meaning that it is up) then this means that the user only wants to select a specific block of nodes (or lines/arcs/labels for their respective sections)
            if(!event.ControlDown())
            {
                for(plf::colony<node>::iterator nodeIterator = _editor.getNodeList()->begin(); nodeIterator != _editor.getNodeList()->end(); ++nodeIterator)
                {
                    nodeIterator->setSelectState(false);
                }
                nodesSeleted = 0;
                _nodesAreSelected = false;
            }
            
            
            for(plf::colony<node>::iterator nodeIterator = _editor.getNodeList()->begin(); nodeIterator != _editor.getNodeList()->end(); ++nodeIterator)
            {
                if((nodeIterator->getCenterXCoordinate() >= _endPoint.x && nodeIterator->getCenterXCoordinate() <= _startPoint.x) && (nodeIterator->getCenterYCoordinate() <= _endPoint.y && nodeIterator->getCenterYCoordinate() >= _startPoint.y))
                {
                    nodeIterator->setSelectState(true);
                    _nodesAreSelected = true;
                    nodesSeleted++;
                    _geometryGroupIsSelected = false;
                }
            }
        }
        else
        {
            // This is case for if the user has the create labels toggeled
            if(_nodesAreSelected || _geometryGroupIsSelected)
            {
                for(plf::colony<node>::iterator nodeIterator = _editor.getNodeList()->begin(); nodeIterator != _editor.getNodeList()->end(); ++nodeIterator)
                {
                    nodeIterator->setSelectState(false);
                }
                nodesSeleted = 0;
                _nodesAreSelected = false;
            }
            
            if(!event.ControlDown())
            {
                for(plf::colony<blockLabel>::iterator blockIterator = _editor.getBlockLabelList()->begin(); blockIterator != _editor.getBlockLabelList()->end(); ++blockIterator)
                {
                    blockIterator->setSelectState(false);
                }
                labelsSelected = 0;
                _labelsAreSelected = false;
            }
            
            for(plf::colony<blockLabel>::iterator blockIterator = _editor.getBlockLabelList()->begin(); blockIterator != _editor.getBlockLabelList()->end(); ++blockIterator)
            {
                if((blockIterator->getCenterXCoordinate() >= _endPoint.x && blockIterator->getCenterXCoordinate() <= _startPoint.x) && (blockIterator->getCenterYCoordinate() <= _endPoint.y && blockIterator->getCenterYCoordinate() >= _startPoint.y))
                {
                    blockIterator->setSelectState(true);
                    _labelsAreSelected = true;
                    labelsSelected++;
                    _geometryGroupIsSelected = false;
                }
            }
        }
    }
    else if(_endPoint.y < _startPoint.y && _endPoint.x < _startPoint.x)// This case is if teh endpoint is to the left of the start point and down. In this case, the user would like to select all of the arcs/lines within the area
    {
        // First, make sure to clear out everything else
        if(_nodesAreSelected || _geometryGroupIsSelected)
        {
            for(plf::colony<node>::iterator nodeIterator = _editor.getNodeList()->begin(); nodeIterator != _editor.getNodeList()->end(); ++nodeIterator)
            {
                nodeIterator->setSelectState(false);
            }
            nodesSeleted = 0;
            _nodesAreSelected = false;
        }
        
        if(_labelsAreSelected || _geometryGroupIsSelected)
        {
            for(plf::colony<blockLabel>::iterator blockIterator = _editor.getBlockLabelList()->begin(); blockIterator != _editor.getBlockLabelList()->end(); ++blockIterator)
            {
                blockIterator->setSelectState(false);
            }
            labelsSelected = 0;
            _labelsAreSelected = false;
        }
        
        if(_createLines)
        {
            // This case is for if the user has selected to edit the lines
            if(_arcsAreSelected || _geometryGroupIsSelected)
            {
                for(plf::colony<arcShape>::iterator arcIterator = _editor.getArcList()->begin(); arcIterator != _editor.getArcList()->end(); ++arcIterator)
                {
                    arcIterator->setSelectState(false);
                }
                arcsSelected = 0;
                _arcsAreSelected = false;
            }
            
            // IF the control button is up, make sure to clear out any selected lines
            if(!event.ControlDown())
            {
                for(plf::colony<edgeLineShape>::iterator lineIterator = _editor.getLineList()->begin(); lineIterator != _editor.getLineList()->end(); ++lineIterator)
                {
                    lineIterator->setSelectState(false);
                }
                linesSelected = 0;
                _linesAreSelected = false;
            }
            
            for(plf::colony<edgeLineShape>::iterator lineIterator = _editor.getLineList()->begin(); lineIterator != _editor.getLineList()->end(); ++lineIterator)
            {
                // In order to prevent a really long if statement, the logic for the selection of the line is pulled out for readability
                bool firstNodeIsSelected = (lineIterator->getFirstNode()->getCenterXCoordinate() >= _endPoint.x && lineIterator->getFirstNode()->getCenterXCoordinate() <= _startPoint.x) && (lineIterator->getFirstNode()->getCenterYCoordinate() >= _endPoint.y && lineIterator->getFirstNode()->getCenterYCoordinate() <= _startPoint.y);
                bool secondNodeIsSelected = (lineIterator->getSecondNode()->getCenterXCoordinate() >= _endPoint.x && lineIterator->getSecondNode()->getCenterXCoordinate() <= _startPoint.x) && (lineIterator->getSecondNode()->getCenterYCoordinate() >= _endPoint.y && lineIterator->getSecondNode()->getCenterYCoordinate() <= _startPoint.y);
                if(firstNodeIsSelected || secondNodeIsSelected)
                {
                    lineIterator->setSelectState(true);
                    _linesAreSelected = true;
                    linesSelected++;
                    _geometryGroupIsSelected = false;
                }   
            }
        }
        else
        {
            // This case if for if the user has selected to edit the arcs
            if(_linesAreSelected || _geometryGroupIsSelected)
            {
                // If there are any lines selected, make sure the clear these guys out also
                for(plf::colony<edgeLineShape>::iterator lineIterator = _editor.getLineList()->begin(); lineIterator != _editor.getLineList()->end(); ++lineIterator)
                {
                    lineIterator->setSelectState(false);
                }
                linesSelected = 0;
                _linesAreSelected = false;
                
            }
            
            // IF the control button is up, make sure to clear out any selected arcs
            if(!event.ControlDown())
            {
                for(plf::colony<arcShape>::iterator arcIterator = _editor.getArcList()->begin(); arcIterator != _editor.getArcList()->end(); ++arcIterator)
                {
                    arcIterator->setSelectState(false);
                }
                arcsSelected = 0;
                _arcsAreSelected = false;
            }
            
            for(plf::colony<arcShape>::iterator arcIterator = _editor.getArcList()->begin(); arcIterator != _editor.getArcList()->end(); ++arcIterator)
            {
                // In order to prevent a really long if statement, the logic for the selection of the line is pulled out for readability
                bool firstNodeIsSelected = (arcIterator->getFirstNode()->getCenterXCoordinate() >= _endPoint.x && arcIterator->getFirstNode()->getCenterXCoordinate() <= _startPoint.x) && (arcIterator->getFirstNode()->getCenterYCoordinate() >= _endPoint.y && arcIterator->getFirstNode()->getCenterYCoordinate() <= _startPoint.y);
                bool secondNodeIsSelected = (arcIterator->getSecondNode()->getCenterXCoordinate() >= _endPoint.x && arcIterator->getSecondNode()->getCenterXCoordinate() <= _startPoint.x) && (arcIterator->getSecondNode()->getCenterYCoordinate() >= _endPoint.y && arcIterator->getSecondNode()->getCenterYCoordinate() <= _startPoint.y);
                if(firstNodeIsSelected || secondNodeIsSelected)
                {
                    arcIterator->setSelectState(true);
                    _arcsAreSelected = true;
                    arcsSelected++;
                    _geometryGroupIsSelected = false;
                }    
            }
        }
    }
    else if(_endPoint.x > _startPoint.x)
    {
        /* For all geometry selection, we dont' neccessarily need to deselect everything first */
        _nodesAreSelected = false;
        _labelsAreSelected = false;
        _linesAreSelected = false;
        _arcsAreSelected = false;
        
        // This is the case for if the user wants to select all of the geometry
        if(!event.ControlDown())
        {
            // If the control button is still up, clear out all of the selected geometry
            for(plf::colony<node>::iterator nodeIterator = _editor.getNodeList()->begin(); nodeIterator != _editor.getNodeList()->end(); ++nodeIterator)
            {
                nodeIterator->setSelectState(false);
            }
            nodesSeleted = 0;
            
            for(plf::colony<blockLabel>::iterator blockIterator = _editor.getBlockLabelList()->begin(); blockIterator != _editor.getBlockLabelList()->end(); ++blockIterator)
            {
                blockIterator->setSelectState(false);
            }
            labelsSelected = 0;
            
            for(plf::colony<edgeLineShape>::iterator lineIterator = _editor.getLineList()->begin(); lineIterator != _editor.getLineList()->end(); ++lineIterator)
            {
                lineIterator->setSelectState(false);
            }
            linesSelected = 0;
            
            for(plf::colony<arcShape>::iterator arcIterator = _editor.getArcList()->begin(); arcIterator != _editor.getArcList()->end(); ++arcIterator)
            {
                arcIterator->setSelectState(false);
            }
            arcsSelected = 0;
        }
        
        // Now we check to see what geometry is in the window
        for(plf::colony<node>::iterator nodeIterator = _editor.getNodeList()->begin(); nodeIterator != _editor.getNodeList()->end(); ++nodeIterator)
        {
            if((nodeIterator->getCenterXCoordinate() <= _endPoint.x && nodeIterator->getCenterXCoordinate() >= _startPoint.x) && ((nodeIterator->getCenterYCoordinate() < _startPoint.y && nodeIterator->getCenterYCoordinate() > _endPoint.y) || (nodeIterator->getCenterYCoordinate() > _startPoint.y && nodeIterator->getCenterYCoordinate() < _endPoint.y)))
            {
                nodeIterator->setSelectState(true);
                nodesSeleted++;
                _geometryGroupIsSelected = true;
            }
        }
        
        for(plf::colony<blockLabel>::iterator blockIterator = _editor.getBlockLabelList()->begin(); blockIterator != _editor.getBlockLabelList()->end(); ++blockIterator)
        {
            if((blockIterator->getCenterXCoordinate() <= _endPoint.x && blockIterator->getCenterXCoordinate() >= _startPoint.x) && ((blockIterator->getCenterYCoordinate() < _startPoint.y && blockIterator->getCenterYCoordinate() > _endPoint.y) || (blockIterator->getCenterYCoordinate() > _startPoint.y && blockIterator->getCenterYCoordinate() < _endPoint.y)))
            {
                blockIterator->setSelectState(true);
                labelsSelected++;
                _geometryGroupIsSelected = true;
            }
        }
        
        for(plf::colony<edgeLineShape>::iterator lineIterator = _editor.getLineList()->begin(); lineIterator != _editor.getLineList()->end(); ++lineIterator)
        {
            // In order to prevent a really long if statement, the logic for the selection of the line is pulled out for readability
            if(lineIterator->getFirstNode()->getIsSelectedState() && lineIterator->getSecondNode()->getIsSelectedState())
            {
                lineIterator->setSelectState(true);
                linesSelected++;
                _geometryGroupIsSelected = true;
            }   
        }
        
        for(plf::colony<arcShape>::iterator arcIterator = _editor.getArcList()->begin(); arcIterator != _editor.getArcList()->end(); ++arcIterator)
        {
            // In order to prevent a really long if statement, the logic for the selection of the line is pulled out for readability
            if(arcIterator->getFirstNode()->getIsSelectedState() && arcIterator->getSecondNode()->getIsSelectedState())
            {
                arcIterator->setSelectState(true);
                arcsSelected++;
                _geometryGroupIsSelected = true;
            }    
        }
    }
    
    // Make sure to reset these two guys 
    _startPoint = wxRealPoint(0, 0);
    _endPoint = _startPoint;
    _doSelectionWindow = false;
    this->Refresh();
    return;
}



wxBEGIN_EVENT_TABLE(modelDefinition, wxGLCanvas)
    EVT_PAINT(modelDefinition::onPaintCanvas)
    EVT_SIZE(modelDefinition::onResize)
    /* This section is the event procedure for the mouse controls */
    EVT_MOUSEWHEEL(modelDefinition::onMouseWheel)
    EVT_MOTION(modelDefinition::onMouseMove)
    EVT_LEFT_DOWN(modelDefinition::onMouseLeftDown)
    EVT_LEFT_UP(modelDefinition::onMouseLeftUp)
    EVT_RIGHT_DOWN(modelDefinition::onMouseRightDown)
    EVT_RIGHT_UP(modelDefinition::onMouseRightUp)
wxEND_EVENT_TABLE()