#include <UI/ModelDefinition/ModelDefinition.h>


modelDefinition::modelDefinition(wxWindow *par, const wxPoint &point, const wxSize &size, problemDefinition &definition) : wxGLCanvas(par, wxID_ANY, NULL, point, size, wxBORDER_DOUBLE | wxBORDER_RAISED)
{
    _geometryContext = new wxGLContext(this);
	wxGLCanvas::SetCurrent(*_geometryContext);
    wxPaintDC dc(this);
    
    _localDefinition = &definition;
    
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
    
    if(_localDefinition->getPhysicsProblem() == physicProblems::PROB_ELECTROSTATIC)
        _textRendering = new glText(physicProblems::PROB_ELECTROSTATIC);
    else if(_localDefinition->getPhysicsProblem() == physicProblems::PROB_MAGNETICS)
        _textRendering = new glText(physicProblems::PROB_MAGNETICS);
}



void modelDefinition::deleteSelection()
{
    
    if(_editor.getNodeList()->size() > 1 && _nodesAreSelected)
    {
        for(plf::colony<node>::iterator nodeIterator = _editor.getNodeList()->begin(); nodeIterator != _editor.getNodeList()->end();)
        {
            plf::colony<node>::iterator endTest = _editor.getNodeList()->end();
            if(nodeIterator->getIsSelectedState())
            {
                if(_editor.getLineList()->size() > 1)
                {
                    /* Need to cycle through the entire line list and arc list in order to determine which arc/line the node is associated with and delete that arc/line by selecting i.
                     * The deletion of the arc/line occurs later in the code*/
                    
                    for(plf::colony<edgeLineShape>::iterator lineIterator = _editor.getLineList()->begin(); lineIterator != _editor.getLineList()->end(); )
                    {
                        if(*lineIterator->getFirstNode() == *nodeIterator || *lineIterator->getSecondNode() == *nodeIterator)
                        {
                            lineIterator->setSelectState(true);
                        }
                        
                        ++lineIterator;
                    }
                }

                    
                if(_editor.getArcList()->size() > 0)
                {
                    for(plf::colony<arcShape>::iterator arcIterator = _editor.getArcList()->begin(); arcIterator != _editor.getArcList()->end(); ++arcIterator)
                    {
                        if(*arcIterator->getFirstNode() == *nodeIterator || *arcIterator->getSecondNode() == *nodeIterator)
                        {
                            arcIterator->setSelectState(true);
                        }
                    }
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
    }
    else if(_editor.getNodeList()->size() == 1 && _editor.getNodeList()->begin()->getIsSelectedState())
    {
        _editor.getNodeList()->clear();
    }

    if(_editor.getLineList()->size() > 1)
    {
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
    }
    else if(_editor.getLineList()->size() == 1)
    {
        _editor.getLineList()->clear();
    }
        
    if(_editor.getArcList()->size() > 1)
    {
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
    }
    else if(_editor.getArcList()->size() == 1 && _editor.getArcList()->begin()->getIsSelectedState())
    {
        _editor.getArcList()->clear();
    }
        
    if(_editor.getBlockLabelList()->size() > 1)
    {
        wxGLStringArray labelNamesToKeep;
        int i = 0;
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
                 //   labelNamesToKeep.addString(_editor.getBlockNameArray()->get(i));
            }
            else
                blockIterator++;
            i++;
        }
        _editor.setLabelNameArray(labelNamesToKeep);
    }
    else if(_editor.getBlockLabelList()->size() == 1 && _editor.getBlockLabelList()->begin()->getIsSelectedState())
    {
        _editor.getBlockLabelList()->clear();
         //   _editor.getBlockNameArray()->getStringArray->clear();
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
            dialog = new segmentPropertyDialog(this, _localDefinition->getElectricalBoundaryList(), _localDefinition->getConductorList(), selectedProperty, false);
        else if(_localDefinition->getPhysicsProblem() == physicProblems::PROB_MAGNETICS)
            dialog = new segmentPropertyDialog(this, _localDefinition->getMagneticBoundaryList(), selectedProperty, false);
            
        if(dialog->ShowModal() == wxID_OK)
        {
            dialog->getSegmentProperty(selectedProperty);
            
            for(plf::colony<edgeLineShape>::iterator lineIterator = _editor.getLineList()->begin(); lineIterator != _editor.getLineList()->end(); ++lineIterator)
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
        
        for(plf::colony<arcShape>::iterator arcIterator = _editor.getArcList()->begin(); arcIterator != _editor.getArcList()->end(); ++arcIterator)
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
            
            for(plf::colony<arcShape>::iterator arcIterator = _editor.getArcList()->begin(); arcIterator != _editor.getArcList()->end(); ++arcIterator)
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
            dialog->getBlockProperty(selectedBlockLabel);
            
            for(plf::colony<blockLabel>::iterator blockIterator = _editor.getBlockLabelList()->begin(); blockIterator != _editor.getBlockLabelList()->end(); ++blockIterator)
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
        for(plf::colony<node>::iterator nodeIterator = _editor.getNodeList()->begin(); nodeIterator != _editor.getNodeList()->end(); ++nodeIterator)
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
        
        for(plf::colony<edgeLineShape>::iterator lineIterator = _editor.getLineList()->begin(); lineIterator != _editor.getLineList()->end(); ++lineIterator)
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
        
        for(plf::colony<arcShape>::iterator arcIterator = _editor.getArcList()->begin(); arcIterator != _editor.getArcList()->end(); ++arcIterator)
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
        for(plf::colony<node>::iterator nodeIterator = _editor.getNodeList()->begin(); nodeIterator != _editor.getNodeList()->end(); ++nodeIterator)
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
        for(plf::colony<edgeLineShape>::iterator lineIterator = _editor.getLineList()->begin(); lineIterator != _editor.getLineList()->end(); ++lineIterator)
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
        
        for(plf::colony<arcShape>::iterator arcIterator = _editor.getArcList()->begin(); arcIterator != _editor.getArcList()->end(); ++arcIterator)
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
        for(plf::colony<blockLabel>::iterator blockIterator = _editor.getBlockLabelList()->begin(); blockIterator != _editor.getBlockLabelList()->end(); ++blockIterator)
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
        for(plf::colony<blockLabel>::iterator blockIterator = _editor.getBlockLabelList()->begin(); blockIterator != _editor.getBlockLabelList()->end(); ++blockIterator)
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
        for(plf::colony<node>::iterator nodeIterator = _editor.getNodeList()->begin(); nodeIterator != _editor.getNodeList()->end(); ++nodeIterator)
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
        for(plf::colony<edgeLineShape>::iterator lineIterator = _editor.getLineList()->begin(); lineIterator != _editor.getLineList()->end(); ++lineIterator)
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
        for(plf::colony<arcShape>::iterator arcIterator = _editor.getArcList()->begin(); arcIterator != _editor.getArcList()->end(); ++arcIterator)
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
        for(plf::colony<blockLabel>::iterator blockIterator = _editor.getBlockLabelList()->begin(); blockIterator != _editor.getBlockLabelList()->end(); ++blockIterator)
        {
            if(blockIterator->getProperty()->getGroupNumber() == groupNumber)
            {
                blockIterator->setSelectState(true);
            }
        }
    }
    
    this->Refresh();
    return;
}



void modelDefinition::moveTranslateSelection(double horizontalShift, double verticalShift)
{
    if(_nodesAreSelected)
    {
        for(plf::colony<node>::iterator nodeIterator = _editor.getNodeList()->begin(); nodeIterator != _editor.getNodeList()->end(); ++nodeIterator)
        {
            if(nodeIterator->getIsSelectedState())
            {
                // Update the node with the translated coordinates
                nodeIterator->moveCenter(horizontalShift, verticalShift);
            }
        }
    }
    else if(_labelsAreSelected)
    {
        for(plf::colony<blockLabel>::iterator blockIterator = _editor.getBlockLabelList()->begin(); blockIterator != _editor.getBlockLabelList()->end(); ++blockIterator)
        {
            if(blockIterator->getIsSelectedState())
                blockIterator->moveCenter(horizontalShift, verticalShift);
        }
    }
    else if(_linesAreSelected)
    {
        for(plf::colony<edgeLineShape>::iterator lineIterator = _editor.getLineList()->begin(); lineIterator != _editor.getLineList()->end(); ++lineIterator)
        {
            if(lineIterator->getIsSelectedState())
            {
                if(!lineIterator->getFirstNode()->getIsSelectedState())
                {
                    lineIterator->getFirstNode()->moveCenter(horizontalShift, verticalShift);
                    lineIterator->getFirstNode()->setSelectState(true);
                }
                
                if(!lineIterator->getSecondNode()->getIsSelectedState())
                {
                    lineIterator->getSecondNode()->moveCenter(horizontalShift, verticalShift);
                    lineIterator->getSecondNode()->setSelectState(true);
                }
            }
        }
    }
    else if(_arcsAreSelected)
    {
        for(plf::colony<arcShape>::iterator arcIterator = _editor.getArcList()->begin(); arcIterator != _editor.getArcList()->end(); ++arcIterator)
        {
            if(arcIterator->getIsSelectedState())
            {
                if(!arcIterator->getFirstNode()->getIsSelectedState())
                {
                    arcIterator->getFirstNode()->moveCenter(horizontalShift, verticalShift);
                    arcIterator->getFirstNode()->setSelectState(true);
                }
                
                if(!arcIterator->getSecondNode()->getIsSelectedState())
                {
                    arcIterator->getSecondNode()->moveCenter(horizontalShift, verticalShift);
                    arcIterator->getSecondNode()->setSelectState(true);
                }
                
                arcIterator->calculate(); // The center and radius of the arc will need to be recalculated after it is moved
            }
        } 
    }
    
    if(_nodesAreSelected || _linesAreSelected || _arcsAreSelected)
    {
        
    }
    
    clearSelection();
    this->Refresh();
    return;
}


// TODO: Test the functionality for the arcs once these are coded in
void modelDefinition::moveRotateSelection(double angularShift, wxRealPoint aboutPoint)
{
    if(_nodesAreSelected)
    {
        for(plf::colony<node>::iterator nodeIterator = _editor.getNodeList()->begin(); nodeIterator != _editor.getNodeList()->end(); ++nodeIterator)
        {
            if(nodeIterator->getIsSelectedState())
            {
                // Calculate the radius and the new position of the node
                double radius = nodeIterator->getDistance(aboutPoint);
                double horizontalShift = nodeIterator->getCenterXCoordinate() + (radius * cos(angularShift * PI / 180.0));
                double verticalShift = nodeIterator->getCenterYCoordinate() + (radius * sin(angularShift * PI / 180.0));
                // Update the node with the translated coordinates
                nodeIterator->setCenter(horizontalShift, verticalShift);
            }
        }
    }
    else if(_labelsAreSelected)
    {
        for(plf::colony<blockLabel>::iterator blockIterator = _editor.getBlockLabelList()->begin(); blockIterator != _editor.getBlockLabelList()->end(); ++blockIterator)
        {
            if(blockIterator->getIsSelectedState())
            {
                double radius = blockIterator->getDistance(aboutPoint);
                double horizontalShift = aboutPoint.x + (radius * cos(angularShift * PI / 180.0));
                double verticalShift = aboutPoint.y + (radius * sin(angularShift * PI / 180.0));
                blockIterator->setCenter(horizontalShift, verticalShift);
            }   
        }
    }
    else if(_linesAreSelected)
    {
        for(plf::colony<edgeLineShape>::iterator lineIterator = _editor.getLineList()->begin(); lineIterator != _editor.getLineList()->end(); ++lineIterator)
        {
            if(lineIterator->getIsSelectedState())
            { 
                double horizontalShift1 = (lineIterator->getFirstNode()->getCenterXCoordinate() - aboutPoint.x) * cos(-angularShift * PI / 180.0) + (lineIterator->getFirstNode()->getCenterYCoordinate() - aboutPoint.y) * sin(-angularShift * PI / 180.0) + aboutPoint.x;
                double verticalShift1 = -(lineIterator->getFirstNode()->getCenterXCoordinate() - aboutPoint.x) * sin(-angularShift * PI / 180.0) + (lineIterator->getFirstNode()->getCenterYCoordinate() - aboutPoint.y) * cos(-angularShift * PI / 180.0) + aboutPoint.y;
                
                double horizontalShift2 = (lineIterator->getSecondNode()->getCenterXCoordinate() - aboutPoint.x) * cos(-angularShift * PI / 180.0) + (lineIterator->getSecondNode()->getCenterYCoordinate() - aboutPoint.y) * sin(-angularShift * PI / 180.0) + aboutPoint.x;
                double verticalShift2 = -(lineIterator->getSecondNode()->getCenterXCoordinate() - aboutPoint.x) * sin(-angularShift * PI / 180.0) + (lineIterator->getSecondNode()->getCenterYCoordinate() - aboutPoint.y) * cos(-angularShift * PI / 180.0) + aboutPoint.y;
                
                if(!lineIterator->getFirstNode()->getIsSelectedState())
                {
                    lineIterator->getFirstNode()->setCenter(horizontalShift1, verticalShift1);
                    lineIterator->getFirstNode()->setSelectState(true);
                }
                
                if(!lineIterator->getSecondNode()->getIsSelectedState())
                {
                    lineIterator->getSecondNode()->setCenter(horizontalShift2, verticalShift2);
                    lineIterator->getSecondNode()->setSelectState(true);
                }
            }
        }
    }
    else if(_arcsAreSelected)
    {
        for(plf::colony<arcShape>::iterator arcIterator = _editor.getArcList()->begin(); arcIterator != _editor.getArcList()->end(); ++arcIterator)
        {
            if(arcIterator->getIsSelectedState())
            {
                double horizontalShift1 = (arcIterator->getFirstNode()->getCenterXCoordinate() - aboutPoint.x) * cos(-angularShift * PI / 180.0) + (arcIterator->getFirstNode()->getCenterYCoordinate() - aboutPoint.y) * sin(-angularShift * PI / 180.0) + aboutPoint.x;
                double verticalShift1 = -(arcIterator->getFirstNode()->getCenterXCoordinate() - aboutPoint.x) * sin(-angularShift * PI / 180.0) + (arcIterator->getFirstNode()->getCenterYCoordinate() - aboutPoint.y) * cos(-angularShift * PI / 180.0) + aboutPoint.y;
                
                double horizontalShift2 = (arcIterator->getSecondNode()->getCenterXCoordinate() - aboutPoint.x) * cos(-angularShift * PI / 180.0) + (arcIterator->getSecondNode()->getCenterYCoordinate() - aboutPoint.y) * sin(-angularShift * PI / 180.0) + aboutPoint.x;
                double verticalShift2 = -(arcIterator->getSecondNode()->getCenterXCoordinate() - aboutPoint.x) * sin(-angularShift * PI / 180.0) + (arcIterator->getSecondNode()->getCenterYCoordinate() - aboutPoint.y) * cos(-angularShift * PI / 180.0) + aboutPoint.y;
                
                if(!arcIterator->getFirstNode()->getIsSelectedState())
                {
                    arcIterator->getFirstNode()->setCenter(horizontalShift1, verticalShift1);
                    arcIterator->getFirstNode()->setSelectState(true);
                }
                
                if(!arcIterator->getSecondNode()->getIsSelectedState())
                {
                    arcIterator->getSecondNode()->setCenter(horizontalShift2, verticalShift2);
                    arcIterator->getSecondNode()->setSelectState(true);
                }
                arcIterator->calculate();
            }
        }
    }
    
    clearSelection();
    this->Refresh();
    return;
}



void modelDefinition::scaleSelection(double scalingFactor, wxRealPoint basePoint)
{
    
}



void modelDefinition::mirrorSelection(wxRealPoint pointOne, wxRealPoint pointTwo)
{
    if(pointOne == pointTwo)
        return;
        
    if(_nodesAreSelected)
    {
        // This is the slope of the mirror line
        double slope = (pointOne.y - pointTwo.y) / (pointOne.x - pointTwo.x);
        
        // This is the case for if the mirror line is a horizontol line
        if(slope == 0)
        {
            for(plf::colony<node>::iterator nodeIterator = _editor.getNodeList()->begin(); nodeIterator != _editor.getNodeList()->end(); ++nodeIterator)
            {
                if(nodeIterator->getIsSelectedState())
                {
                    double distance = nodeIterator->getCenterYCoordinate() - pointOne.y;
                    
                    if(_editor.addNode(nodeIterator->getCenterXCoordinate(), pointOne.y - distance))
                        _editor.getNodeList()->back()->setNodeSettings(*nodeIterator->getNodeSetting());
                }
            }
            this->Refresh();
            return;
        }
        else if(slope == INFINITY || slope == -INFINITY)
        {
            // This is the case for if the mirror line is a vertical line
            for(plf::colony<node>::iterator nodeIterator = _editor.getNodeList()->begin(); nodeIterator != _editor.getNodeList()->end(); ++nodeIterator)
            {
                if(nodeIterator->getIsSelectedState())
                {
                    double distance = pointOne.x - nodeIterator->getCenterXCoordinate();
                    
                    if(_editor.addNode(pointOne.x + distance, nodeIterator->getCenterYCoordinate()))
                        _editor.getNodeList()->back()->setNodeSettings(*nodeIterator->getNodeSetting());
                }
            }
            this->Refresh();
            return;
        }
        
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
                
                if(_editor.addNode(2 * intersectionPointx - nodeIterator->getCenterXCoordinate(), 2 * intersectionPointy - nodeIterator->getCenterYCoordinate()))
                    _editor.getNodeList()->back()->setNodeSettings(*nodeIterator->getNodeSetting());
            }
        }
    }
    else if(_labelsAreSelected)
    {
        // This is the slope of the mirror line
        double slope = (pointOne.y - pointTwo.y) / (pointOne.x - pointTwo.x);
        
        // This is the case for if the mirror line is a horizontol line
        if(slope == 0)
        {
            for(plf::colony<blockLabel>::iterator blockIterator = _editor.getBlockLabelList()->begin(); blockIterator != _editor.getBlockLabelList()->end(); ++blockIterator)
            {
                if(blockIterator->getIsSelectedState())
                {
                    double distance = blockIterator->getCenterYCoordinate() - pointOne.y;
                    
                    if(_editor.addBlockLabel(blockIterator->getCenterXCoordinate(), pointOne.y - distance))
                        _editor.getBlockLabelList()->back()->setPorperty(*blockIterator->getProperty());
                }
            }
            this->Refresh();
            return;
        }
        else if(slope == INFINITY || slope == -INFINITY)
        {
            // This is the case for if the mirror line is a vertical line
            for(plf::colony<blockLabel>::iterator blockIterator = _editor.getBlockLabelList()->begin(); blockIterator != _editor.getBlockLabelList()->end(); ++blockIterator)
            {
                if(blockIterator->getIsSelectedState())
                {
                    double distance = pointOne.x - blockIterator->getCenterXCoordinate();
                    
                    if(_editor.addBlockLabel(pointOne.x + distance, blockIterator->getCenterYCoordinate()))
                        _editor.getBlockLabelList()->back()->setPorperty(*blockIterator->getProperty());
                }
            }
            this->Refresh();
            return;
        }
        
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
                
                if(_editor.addNode(2 * intersectionPointx - blockIterator->getCenterXCoordinate(), 2 * intersectionPointy - blockIterator->getCenterYCoordinate()))
                    _editor.getBlockLabelList()->back()->setPorperty(*blockIterator->getProperty());
            }
        }
    }
    else if(_linesAreSelected)
    {
        /* The logic for this function follows that of the logic for mirroring the node; however, since this is 
         * a line, we will have to apply this logic to both the endpoints of the line. We will also need to check to see if the 
         * endpoints of the line already exists or if the endpoint is being drawn ontop of a block label. 
         * If either is the case, the function will have to handle these case in soem way
         */ 
        
        // This is the slope of the mirror line
        double slope = (pointOne.y - pointTwo.y) / (pointOne.x - pointTwo.x);
        
        // This is the case for if the mirror line is a horizontol line
        if(slope == 0)
        {
            for(plf::colony<edgeLineShape>::iterator lineIterator = _editor.getLineList()->begin(); lineIterator != _editor.getLineList()->end(); ++lineIterator)
            {
                if(lineIterator->getIsSelectedState())
                {
                    double distance = lineIterator->getFirstNode()->getCenterYCoordinate() - pointOne.y;
                    
                    // First, we attempt to create a node at the mirrored spot. The function will return false if another node is already present
                    // or, if a block label is present. In the event of a node already present, then we need to find out which node it is and set the nodeIndex to be that node for line creation
                    // If a block label is present, we will have to ignore the creation of line.
                    // The same logic applies for the second node of the line
                    if(_editor.addNode(lineIterator->getFirstNode()->getCenterXCoordinate(), pointOne.y - distance))
                    {
                        _editor.getNodeList()->back()->setNodeSettings(*lineIterator->getFirstNode()->getNodeSetting());
                        _editor.setNodeIndex(*_editor.getNodeList()->back());
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
                    
                    distance = lineIterator->getSecondNode()->getCenterYCoordinate() - pointOne.y;
                    
                    if(_editor.addNode(lineIterator->getSecondNode()->getCenterXCoordinate(), pointOne.y - distance))
                    {
                        _editor.getNodeList()->back()->setNodeSettings(*lineIterator->getSecondNode()->getNodeSetting());
                        _editor.setNodeIndex(*_editor.getNodeList()->back());
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
                    
                    if(_editor.addLine())
                        _editor.getLineList()->back()->setSegmentProperty(*lineIterator->getSegmentProperty());
                }
            }

            this->Refresh();
            return;
        }
        else if(slope == INFINITY || slope == -INFINITY)
        {
            /* THis is the case for it the mirror line is vertical */
            for(plf::colony<edgeLineShape>::iterator lineIterator = _editor.getLineList()->begin(); lineIterator != _editor.getLineList()->end(); ++lineIterator)
            {
                if(lineIterator->getIsSelectedState())
                {
                    double distance = pointOne.x - lineIterator->getFirstNode()->getCenterXCoordinate();
                    
                    if(_editor.addNode(pointOne.x + distance, lineIterator->getFirstNode()->getCenterYCoordinate()))
                    {
                        _editor.getNodeList()->back()->setNodeSettings(*lineIterator->getFirstNode()->getNodeSetting());
                        _editor.setNodeIndex(*_editor.getNodeList()->back());
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
                    
                    distance = pointOne.x - lineIterator->getSecondNode()->getCenterXCoordinate();
                    
                    if(_editor.addNode(pointOne.x + distance, lineIterator->getSecondNode()->getCenterYCoordinate()))
                    {
                        _editor.getNodeList()->back()->setNodeSettings(*lineIterator->getSecondNode()->getNodeSetting());
                        _editor.setNodeIndex(*_editor.getNodeList()->back());
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
                    
                    if(_editor.addLine())
                        _editor.getLineList()->back()->setSegmentProperty(*lineIterator->getSegmentProperty());
                }
            }
            
            this->Refresh();
            return;
        }
        
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
                
                if(_editor.addNode(2 * intersectionPointx - lineIterator->getFirstNode()->getCenterXCoordinate(), 2 * intersectionPointy - lineIterator->getFirstNode()->getCenterYCoordinate()))
                {
                    _editor.getNodeList()->back()->setNodeSettings(*lineIterator->getFirstNode()->getNodeSetting());
                    _editor.setNodeIndex(*_editor.getNodeList()->back());
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
                
                // Re-calculate some of the parameters for the second node of the line
                b2 = lineIterator->getSecondNode()->getCenterYCoordinate() - perpSlope * lineIterator->getSecondNode()->getCenterXCoordinate();
                intersectionPointx = (b1 - b2) / (perpSlope - slope);
                intersectionPointy = slope * intersectionPointx + b1;
                
                if(_editor.addNode(2 * intersectionPointx - lineIterator->getSecondNode()->getCenterXCoordinate(), 2 * intersectionPointy - lineIterator->getSecondNode()->getCenterYCoordinate()))
                {
                    _editor.getNodeList()->back()->setNodeSettings(*lineIterator->getSecondNode()->getNodeSetting());
                    _editor.setNodeIndex(*_editor.getNodeList()->back());
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
                
                if(_editor.addLine())
                    _editor.getLineList()->back()->setSegmentProperty(*lineIterator->getSegmentProperty());                
            }
        }
    }
    else if(_arcsAreSelected)
    {
        /* TODO: test the code for arcs */
    // This is the slope of the mirror line
        double slope = (pointOne.y - pointTwo.y) / (pointOne.x - pointTwo.x);
        
        // This is the case for if the mirror line is a horizontol line
        if(slope == 0)
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
                    if(_editor.addNode(arcIterator->getFirstNode()->getCenterXCoordinate(), pointOne.y - distance))
                    {
                        _editor.getNodeList()->back()->setNodeSettings(*arcIterator->getFirstNode()->getNodeSetting());
                        _editor.setNodeIndex(*_editor.getNodeList()->back());
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
                    
                    distance = arcIterator->getSecondNode()->getCenterYCoordinate() - pointOne.y;
                    
                    if(_editor.addNode(arcIterator->getSecondNode()->getCenterXCoordinate(), pointOne.y - distance))
                    {
                        _editor.getNodeList()->back()->setNodeSettings(*arcIterator->getSecondNode()->getNodeSetting());
                        _editor.setNodeIndex(*_editor.getNodeList()->back());
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
                    
                    if(_editor.addArc(*arcIterator, getTolerance(), true))
                    {
                        _editor.getArcList()->back()->setSegmentProperty(*arcIterator->getSegmentProperty());
                        _editor.getArcList()->back()->calculate();
                    }
                }
            }

            this->Refresh();
            return;
        }
        else if(slope == INFINITY || slope == -INFINITY)
        {
            /* THis is the case for it the mirror line is vertical */
            for(plf::colony<arcShape>::iterator arcIterator = _editor.getArcList()->begin(); arcIterator != _editor.getArcList()->end(); ++arcIterator)
            {
                if(arcIterator->getIsSelectedState())
                {
                    double distance = pointOne.x - arcIterator->getFirstNode()->getCenterXCoordinate();
                    
                    if(_editor.addNode(pointOne.x + distance, arcIterator->getFirstNode()->getCenterYCoordinate()))
                    {
                        _editor.getNodeList()->back()->setNodeSettings(*arcIterator->getFirstNode()->getNodeSetting());
                        _editor.setNodeIndex(*_editor.getNodeList()->back());
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
                    
                    distance = pointOne.x - arcIterator->getSecondNode()->getCenterXCoordinate();
                    
                    if(_editor.addNode(pointOne.x + distance, arcIterator->getSecondNode()->getCenterYCoordinate()))
                    {
                        _editor.getNodeList()->back()->setNodeSettings(*arcIterator->getSecondNode()->getNodeSetting());
                        _editor.setNodeIndex(*_editor.getNodeList()->back());
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
                    
                    if(_editor.addArc(*arcIterator, getTolerance(), true))
                    {
                        _editor.getArcList()->back()->setSegmentProperty(*arcIterator->getSegmentProperty());
                        _editor.getArcList()->back()->calculate();
                    }
                }
            }
            
            this->Refresh();
            return;
        }
        
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
                
                if(_editor.addNode(2 * intersectionPointx - arcIterator->getFirstNode()->getCenterXCoordinate(), 2 * intersectionPointy - arcIterator->getFirstNode()->getCenterYCoordinate()))
                {
                    _editor.getNodeList()->back()->setNodeSettings(*arcIterator->getFirstNode()->getNodeSetting());
                    _editor.setNodeIndex(*_editor.getNodeList()->back());
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
                
                // Re-calculate some of the parameters for the second node of the line
                b2 = arcIterator->getSecondNode()->getCenterYCoordinate() - perpSlope * arcIterator->getSecondNode()->getCenterXCoordinate();
                intersectionPointx = (b1 - b2) / (perpSlope - slope);
                intersectionPointy = slope * intersectionPointx + b1;
                
                if(_editor.addNode(2 * intersectionPointx - arcIterator->getSecondNode()->getCenterXCoordinate(), 2 * intersectionPointy - arcIterator->getSecondNode()->getCenterYCoordinate()))
                {
                    _editor.getNodeList()->back()->setNodeSettings(*arcIterator->getSecondNode()->getNodeSetting());
                    _editor.setNodeIndex(*_editor.getNodeList()->back());
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
                
                if(_editor.addArc(*arcIterator, getTolerance(), true))
                {
                    _editor.getArcList()->back()->setSegmentProperty(*arcIterator->getSegmentProperty());
                    _editor.getArcList()->back()->calculate();
                }                
            }
        }
    }
    
    this->Refresh();
    return;
}



void modelDefinition::copyTranslateSelection(double horizontalShift, double verticalShift, unsigned int numberOfCopies)
{
    if(_nodesAreSelected)
    {
        // Make copies of those nodes
        for(plf::colony<node>::iterator nodeIterator = _editor.getNodeList()->begin(); nodeIterator != _editor.getNodeList()->end(); ++nodeIterator)
        {
            if(nodeIterator->getIsSelectedState())
            {
                for(unsigned int i = 1; i < (numberOfCopies + 1); i++)
                {
                    _editor.addNode(nodeIterator->getCenterXCoordinate() + i * horizontalShift, nodeIterator->getCenterYCoordinate() + i * verticalShift);
                    _editor.getNodeList()->back()->setNodeSettings(*nodeIterator->getNodeSetting());
                }
            }
        }
    }
    else if(_labelsAreSelected)
    {
        for(plf::colony<blockLabel>::iterator blockIterator = _editor.getBlockLabelList()->begin(); blockIterator != _editor.getBlockLabelList()->end(); ++blockIterator)
        {
            if(blockIterator->getIsSelectedState())
            {
                for(unsigned int i = 1; i < (numberOfCopies + 1); i++)
                {
                    blockProperty copy = *blockIterator->getProperty();
                    _editor.addBlockLabel(blockIterator->getCenterXCoordinate() + i * horizontalShift, blockIterator->getCenterYCoordinate() + i * verticalShift);
                    _editor.getBlockLabelList()->back()->setPorperty(copy);
                }
            }
        }
    }
    else if(_linesAreSelected)
    {        
        for(plf::colony<edgeLineShape>::iterator lineIterator = _editor.getLineList()->begin(); lineIterator != _editor.getLineList()->end(); ++lineIterator)
        {
            if(lineIterator->getIsSelectedState())
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
                    node testNode;
                    bool doesExist = false;
                    testNode.setCenter(lineIterator->getFirstNode()->getCenterXCoordinate() + i * horizontalShift, lineIterator->getFirstNode()->getCenterYCoordinate() + i * verticalShift);
                    
                    for(plf::colony<node>::iterator nodeIterator = _editor.getNodeList()->begin(); nodeIterator != _editor.getNodeList()->end(); ++nodeIterator)
                    {
                        if(*nodeIterator == testNode)
                        {
                            _editor.setNodeIndex(*nodeIterator);
                            doesExist = true;
                            break;
                        }
                    }
                    
                    if(!doesExist)
                    {
                        _editor.addNode(lineIterator->getFirstNode()->getCenterXCoordinate() + i * horizontalShift, lineIterator->getFirstNode()->getCenterYCoordinate() + i * verticalShift);
                        _editor.getNodeList()->back()->setNodeSettings(*lineIterator->getFirstNode()->getNodeSetting());
                        _editor.setNodeIndex(*_editor.getNodeList()->back()); 
                    }
                    else
                        doesExist = false;
                        
                    testNode.setCenter(lineIterator->getSecondNode()->getCenterXCoordinate() + i * horizontalShift, lineIterator->getSecondNode()->getCenterYCoordinate() + i * verticalShift);
                    
                    for(plf::colony<node>::iterator nodeIterator = _editor.getNodeList()->begin(); nodeIterator != _editor.getNodeList()->end(); ++nodeIterator)
                    {
                        if(*nodeIterator == testNode)
                        {
                            _editor.setNodeIndex(*nodeIterator);
                            doesExist = true;
                            break;
                        }
                    }
                    
                    if(!doesExist)
                    {
                        _editor.addNode(lineIterator->getSecondNode()->getCenterXCoordinate() + i * horizontalShift, lineIterator->getSecondNode()->getCenterYCoordinate() + i * verticalShift);
                        _editor.getNodeList()->back()->setNodeSettings(*lineIterator->getSecondNode()->getNodeSetting());
                        _editor.setNodeIndex(*_editor.getNodeList()->back());
                    }
                    
                    _editor.addLine();
                    _editor.getLineList()->back()->setSegmentProperty(*lineIterator->getSegmentProperty());
                }
            }
        }
    }
    else if(_arcsAreSelected)
    {
        for(plf::colony<arcShape>::iterator arcIterator = _editor.getArcList()->begin(); arcIterator != _editor.getArcList()->end(); ++arcIterator)
        {
            if(arcIterator->getIsSelectedState())
            {
                for(unsigned int i = 1; i < (numberOfCopies + 1); i++)
                {
                    node testNode;
                    bool doesExist = false;
                    testNode.setCenter(arcIterator->getFirstNode()->getCenterXCoordinate() + i * horizontalShift, arcIterator->getFirstNode()->getCenterYCoordinate() + i * verticalShift);
                    
                    for(plf::colony<node>::iterator nodeIterator = _editor.getNodeList()->begin(); nodeIterator != _editor.getNodeList()->end(); ++nodeIterator)
                    {
                        if(*nodeIterator == testNode)
                        {
                            _editor.setNodeIndex(*nodeIterator);
                            doesExist = true;
                            break;
                        }
                    }
                    
                    if(!doesExist)
                    {
                        _editor.addNode(arcIterator->getFirstNode()->getCenterXCoordinate() + i * horizontalShift, arcIterator->getFirstNode()->getCenterYCoordinate() + i * verticalShift);
                        _editor.getNodeList()->back()->setNodeSettings(*arcIterator->getFirstNode()->getNodeSetting());
                        _editor.setNodeIndex(*_editor.getNodeList()->back()); 
                    }
                    else
                        doesExist = false;
                        
                    testNode.setCenter(arcIterator->getSecondNode()->getCenterXCoordinate() + i * horizontalShift, arcIterator->getSecondNode()->getCenterYCoordinate() + i * verticalShift);
                    
                    for(plf::colony<node>::iterator nodeIterator = _editor.getNodeList()->begin(); nodeIterator != _editor.getNodeList()->end(); ++nodeIterator)
                    {
                        if(*nodeIterator == testNode)
                        {
                            _editor.setNodeIndex(*nodeIterator);
                            doesExist = true;
                            break;
                        }
                    }
                    
                    if(!doesExist)
                    {
                        _editor.addNode(arcIterator->getSecondNode()->getCenterXCoordinate() + i * horizontalShift, arcIterator->getSecondNode()->getCenterYCoordinate() + i * verticalShift);
                        _editor.getNodeList()->back()->setNodeSettings(*arcIterator->getSecondNode()->getNodeSetting());
                        _editor.setNodeIndex(*_editor.getNodeList()->back());
                    }
                    
                    _editor.addArc(*arcIterator, 0, false);
                    
                    _editor.getArcList()->back()->setSegmentProperty(*arcIterator->getSegmentProperty()); // This line may not be necessary but once arcs can be drawn and selected, this needs testing
                    _editor.getArcList()->back()->calculate();
                }
            }
        }
    }
    
    clearSelection();
    this->Refresh();
    return;
}


void modelDefinition::copyRotateSelection(double angularShift, wxRealPoint aboutPoint, unsigned int numberOfCopies)
{
    if(_nodesAreSelected)
    {
        for(plf::colony<node>::iterator nodeIterator = _editor.getNodeList()->begin(); nodeIterator != _editor.getNodeList()->end(); ++nodeIterator)
        {
            if(nodeIterator->getIsSelectedState())
            {
                double radius = nodeIterator->getDistance(aboutPoint);
                
                for(unsigned int i = 1; i < (numberOfCopies + 1); i++)
                {
                   // Calculate the radius and the new position of the node
                    double horizontalShift = aboutPoint.x + (radius * cos(i * angularShift * PI / 180.0));
                    double verticalShift = aboutPoint.y + (radius * sin(i * angularShift * PI / 180.0));
                    // Update the node with the translated coordinates
                    _editor.addNode(horizontalShift, verticalShift);
                    _editor.getNodeList()->back()->setNodeSettings(*nodeIterator->getNodeSetting());
                }
                
            }
        }
    }
    else if(_labelsAreSelected)
    {
        for(plf::colony<blockLabel>::iterator blockIterator = _editor.getBlockLabelList()->begin(); blockIterator != _editor.getBlockLabelList()->end(); ++blockIterator)
        {
            if(blockIterator->getIsSelectedState())
            {
                double radius = blockIterator->getDistance(aboutPoint);
                
                for(unsigned int i = 1; i < (numberOfCopies + 1); i++)
                {
                    blockProperty transfer = *blockIterator->getProperty();
                    double horizontalShift = aboutPoint.x + (radius * cos(i * angularShift * PI / 180.0));
                    double verticalShift = aboutPoint.y + (radius * sin(i * angularShift * PI / 180.0));
                    _editor.addBlockLabel(horizontalShift, verticalShift);
                    _editor.getBlockLabelList()->back()->setPorperty(transfer);
                }
                
            }
        } 
    }
    else if(_linesAreSelected)
    {
        for(plf::colony<edgeLineShape>::iterator lineIterator = _editor.getLineList()->begin(); lineIterator != _editor.getLineList()->end(); ++lineIterator)
        {
            if(lineIterator->getIsSelectedState())
            {
                for(unsigned int i = 1; i < (numberOfCopies + 1); i++)
                {
                    double horizontalShift1 = (lineIterator->getFirstNode()->getCenterXCoordinate() - aboutPoint.x) * cos(-i * angularShift * PI / 180.0) + (lineIterator->getFirstNode()->getCenterYCoordinate() - aboutPoint.y) * sin(-i * angularShift * PI / 180.0) + aboutPoint.x;
                    double verticalShift1 = -(lineIterator->getFirstNode()->getCenterXCoordinate() - aboutPoint.x) * sin(-i * angularShift * PI / 180.0) + (lineIterator->getFirstNode()->getCenterYCoordinate() - aboutPoint.y) * cos(-i * angularShift * PI / 180.0) + aboutPoint.y;
                    
                    double horizontalShift2 = (lineIterator->getSecondNode()->getCenterXCoordinate() - aboutPoint.x) * cos(-i * angularShift * PI / 180.0) + (lineIterator->getSecondNode()->getCenterYCoordinate() - aboutPoint.y) * sin(-i * angularShift * PI / 180.0) + aboutPoint.x;
                    double verticalShift2 = -(lineIterator->getSecondNode()->getCenterXCoordinate() - aboutPoint.x) * sin(-i * angularShift * PI / 180.0) + (lineIterator->getSecondNode()->getCenterYCoordinate() - aboutPoint.y) * cos(-i * angularShift * PI / 180.0) + aboutPoint.y;
                
                    _editor.addNode(horizontalShift1, verticalShift1);
                    _editor.getNodeList()->back()->setNodeSettings(*lineIterator->getFirstNode()->getNodeSetting());
                   
                    _editor.addNode(horizontalShift2, verticalShift2);
                    _editor.getNodeList()->back()->setNodeSettings(*lineIterator->getSecondNode()->getNodeSetting());
                    
                    plf::colony<node>::iterator lastItem = _editor.getNodeList()->back();
                    _editor.setNodeIndex(*lastItem);
                    
                    --lastItem;
                    _editor.setNodeIndex(*lastItem);
                    
                    _editor.addLine();
                    _editor.getLineList()->back()->setSegmentProperty(*lineIterator->getSegmentProperty());
                }
            }
        }
    }
    else if(_arcsAreSelected)
    {
        for(plf::colony<arcShape>::iterator arcIterator = _editor.getArcList()->begin(); arcIterator != _editor.getArcList()->end(); ++arcIterator)
        {
            if(arcIterator->getIsSelectedState())
            {
                for(unsigned int i = 1; i < (numberOfCopies + 1); i++)
                {
                    double horizontalShift1 = (arcIterator->getFirstNode()->getCenterXCoordinate() - aboutPoint.x) * cos(-i * angularShift * PI / 180.0) + (arcIterator->getFirstNode()->getCenterYCoordinate() - aboutPoint.y) * sin(-i * angularShift * PI / 180.0) + aboutPoint.x;
                    double verticalShift1 = -(arcIterator->getFirstNode()->getCenterXCoordinate() - aboutPoint.x) * sin(-i * angularShift * PI / 180.0) + (arcIterator->getFirstNode()->getCenterYCoordinate() - aboutPoint.y) * cos(-i * angularShift * PI / 180.0) + aboutPoint.y;
                    
                    double horizontalShift2 = (arcIterator->getSecondNode()->getCenterXCoordinate() - aboutPoint.x) * cos(-i * angularShift * PI / 180.0) + (arcIterator->getSecondNode()->getCenterYCoordinate() - aboutPoint.y) * sin(-i * angularShift * PI / 180.0) + aboutPoint.x;
                    double verticalShift2 = -(arcIterator->getSecondNode()->getCenterXCoordinate() - aboutPoint.x) * sin(-i * angularShift * PI / 180.0) + (arcIterator->getSecondNode()->getCenterYCoordinate() - aboutPoint.y) * cos(-i * angularShift * PI / 180.0) + aboutPoint.y;
                    
                    _editor.addNode(horizontalShift1, verticalShift1);
                    _editor.getNodeList()->back()->setNodeSettings(*arcIterator->getFirstNode()->getNodeSetting());
                   
                    _editor.addNode(horizontalShift2, verticalShift2);
                    _editor.getNodeList()->back()->setNodeSettings(*arcIterator->getSecondNode()->getNodeSetting());

                    plf::colony<node>::iterator lastItem = _editor.getNodeList()->back();
                    _editor.setNodeIndex(*lastItem);
                
                    --lastItem;
                    _editor.setNodeIndex(*lastItem);
                    
                    _editor.addArc(*arcIterator, 0, false);
                    
                    _editor.getLineList()->back()->setSegmentProperty(*arcIterator->getSegmentProperty()); // This line may not be necessary but once arcs can be drawn and selected, this needs testing
                    _editor.getArcList()->back()->calculate();
                }
            }
        }
    }
    
    clearSelection();
    this->Refresh();
    return;
}

void modelDefinition::displayOpenBoundary()
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
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    glOrtho(-_zoomX, _zoomX, -_zoomY, _zoomY, -1.0, 1.0);
    
    glMatrixMode(GL_MODELVIEW);
    
    //Reset to modelview matrix
	glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    glViewport(0, 0, (double)this->GetSize().GetWidth(), (double)this->GetSize().GetHeight());
    /* This section will handle the translation (panning) and scaled (zooming). 
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



void modelDefinition::clearSelection()
{
    if(_createNodes)
    {
        for(plf::colony<node>::iterator nodeIterator = _editor.getNodeList()->begin(); nodeIterator != _editor.getNodeList()->end(); ++nodeIterator)
        {
            if(nodeIterator->getIsSelectedState())
                nodeIterator->setSelectState(false);
        }
    }
    else if(!_createNodes || _labelsAreSelected)
    {
        for(plf::colony<blockLabel>::iterator blockIterator = _editor.getBlockLabelList()->begin(); blockIterator != _editor.getBlockLabelList()->end(); ++blockIterator)
        {
            if(blockIterator->getIsSelectedState())
                blockIterator->setSelectState(false);
        }
    }
    
    if(_createLines)
    {
        for(plf::colony<edgeLineShape>::iterator lineIterator = _editor.getLineList()->begin(); lineIterator != _editor.getLineList()->end(); ++lineIterator)
        {
            if(lineIterator->getIsSelectedState())
                lineIterator->setSelectState(false);
        }
    }
    else if(!_createLines || _arcsAreSelected)
    {
        for(plf::colony<arcShape>::iterator arcIterator = _editor.getArcList()->begin(); arcIterator != _editor.getArcList()->end(); ++arcIterator)
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
    
    glMatrixMode(GL_MODELVIEW);
    glClear(GL_COLOR_BUFFER_BIT);

    updateProjection();
    drawGrid();
    glMatrixMode(GL_MODELVIEW);
    

    if(_editor.getLineList()->size() > 0)
    {
        for(plf::colony<edgeLineShape>::iterator lineIterator = _editor.getLineList()->begin(); lineIterator != _editor.getLineList()->end(); ++lineIterator)
        {
            lineIterator->draw();
        }
    }
    
    if(_editor.getArcList()->size() > 0)
    {
        for(plf::colony<arcShape>::iterator arcIterator = _editor.getArcList()->begin(); arcIterator != _editor.getArcList()->end(); ++arcIterator)
        {
            arcIterator->draw();
        }
    }
    
    if(_editor.getBlockLabelList()->size() > 0)
    {
        for(plf::colony<blockLabel>::iterator blockIterator = _editor.getBlockLabelList()->begin(); blockIterator != _editor.getBlockLabelList()->end(); ++blockIterator)
        {
            blockIterator->draw();
        }
    }
    
    if(_editor.getNodeList()->size() > 0)
    {
        for(plf::colony<node>::iterator nodeIterator = _editor.getNodeList()->begin(); nodeIterator != _editor.getNodeList()->end(); ++nodeIterator)
        {
            nodeIterator->draw();
        }
    }
    
    
    
    if(_preferences.getShowBlockNameState())
    {
        _textRendering->renderBlockLabelText();
    }
    
    if(_doZoomWindow)
    {
                /* The code for drawing the grid was adapted from the Agros2D project */
        glLineWidth(3.0);
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
        
        glBegin(GL_LINES);
            glColor3d(0.0, 0.0, 0.0);
            glVertex2d(_startPoint.x, _startPoint.y);
            glVertex2d(_endPoint.x, _endPoint.y);
        glEnd();
        glDisable(GL_LINE_STIPPLE);
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
        
        _cameraX += (((2.0 / this->GetSize().GetWidth()) * (event.GetX() - this->GetSize().GetWidth() / 2.0)) * _zoomX) * (this->GetSize().GetWidth() / this->GetSize().GetHeight());
        _cameraY += (-(2.0 / this->GetSize().GetHeight()) * (event.GetY() - this->GetSize().GetHeight() / 2.0)) * _zoomY;
        
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
        
        _cameraX -= (((2.0 / this->GetSize().GetWidth()) * (event.GetX() - this->GetSize().GetWidth() / 2.0)) * _zoomX) * (this->GetSize().GetWidth() / this->GetSize().GetHeight());
        _cameraY -= (-(2.0 / this->GetSize().GetHeight()) * (event.GetY() - this->GetSize().GetHeight() / 2.0)) * _zoomY;
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
        _cameraX -= (2.0 / this->GetSize().GetWidth()) * ((double)dx * _zoomX) * (this->GetSize().GetWidth() / this->GetSize().GetHeight());
        _cameraY += (2.0 / this->GetSize().GetHeight()) * ((double)dy * _zoomY);
    }
    else if(event.ButtonIsDown(wxMOUSE_BTN_LEFT))
    {
        if(!_doZoomWindow && !_doMirrorLine)
        {
            if(_createNodes && !_geometryIsSelected)
            {
                if(_editor.getNodeList()->size() > 0 && _editor.getNodeList()->back()->getDraggingState())
                {
                    double tempX = convertToXCoordinate(event.GetX());
                    double tempY = convertToYCoordinate(event.GetY());
                    // Update the last node entry with new x and y coordinates and round if on snap grid
                    if(_preferences.getSnapGridState())
                    {
                        roundToNearestGrid(tempX, tempY);
                        _editor.getNodeList()->back()->setCenter(tempX, tempY);
                    }
                    else
                    {
                        _editor.getNodeList()->back()->setCenter(tempX, tempY);
                    }
                }
            }
            else if(!_createNodes)
            {
                if(_editor.getBlockLabelList()->size() > 0 && _editor.getBlockLabelList()->back()->getDraggingState())
                {
                    // Update the last bloc labe with new x and y coordinates and round if on snap grid
                    if(_preferences.getSnapGridState())
                    {
                        double tempX = convertToXCoordinate(event.GetX());
                        double tempY = convertToYCoordinate(event.GetY());
                        roundToNearestGrid(tempX, tempY);
                        _editor.getBlockLabelList()->back()->setCenter(tempX, tempY);
                    }
                    else
                    {
                        _editor.getBlockLabelList()->back()->setCenter(convertToXCoordinate(event.GetX()), convertToYCoordinate(event.GetY()));
                    }
                    
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
    
    this->Refresh();
    return;
}



void modelDefinition::onMouseLeftDown(wxMouseEvent &event)
{
    wxGLCanvas::SetCurrent(*_geometryContext);
    
    clearSelection();
    
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
                                    _editor.addArc(tempShape, getTolerance(), true);
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
                        nodeIterator->setSelectState(true);
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
    }
    else if(_doZoomWindow || _doMirrorLine)
    {
        double tempX = convertToXCoordinate(event.GetX());
        double tempY = convertToYCoordinate(event.GetY());
        
        if(_preferences.getSnapGridState())
            roundToNearestGrid(tempX, tempY);
            
        _startPoint = wxRealPoint(tempX, tempY);
        _endPoint = wxRealPoint(tempX, tempY);
    }
    
    this->Refresh();
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
            if(_editor.getNodeList()->size() > 0)
            {
                double tempX = convertToXCoordinate(event.GetX());
                double tempY = convertToYCoordinate(event.GetY());
                
                if(_preferences.getSnapGridState())
                    roundToNearestGrid(tempX, tempY);
                
                if(_editor.getNodeList()->back()->getDraggingState())
                {
                    _editor.getNodeList()->erase(_editor.getNodeList()->back());
                    _editor.addNode(tempX, tempY);
                }
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

                if(_editor.getBlockLabelList()->back()->getDraggingState())
                {
                    _editor.getBlockLabelList()->erase(_editor.getBlockLabelList()->back()); 
                    _editor.addBlockLabel(tempX, tempY);
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
        for(plf::colony<node>::iterator nodeIterator = _editor.getNodeList()->begin(); nodeIterator != _editor.getNodeList()->end(); ++nodeIterator)
        {
            if(nodeIterator->getDistance(xCoordinate, yCoordinate) < getTolerance())
            {
                // Add in code to remove previousely selected geometry that is different then the one already selected
                if(_linesAreSelected)
                {
                    for(plf::colony<edgeLineShape>::iterator lineIterator = _editor.getLineList()->begin(); lineIterator != _editor.getLineList()->end(); ++lineIterator)
                    {
                        lineIterator->setSelectState(false);
                        linesSelected = 0;
                    }
                }
                else if(_arcsAreSelected)
                {
                   for(plf::colony<arcShape>::iterator arcIterator = _editor.getArcList()->begin(); arcIterator != _editor.getArcList()->end(); ++arcIterator)
                    {
                        arcIterator->setSelectState(false);
                        arcsSelected = 0;
                    } 
                }
                else if(_labelsAreSelected)
                {
                   for(plf::colony<blockLabel>::iterator blockIterator = _editor.getBlockLabelList()->begin(); blockIterator != _editor.getBlockLabelList()->end(); ++blockIterator)
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
        for(plf::colony<blockLabel>::iterator blockIterator = _editor.getBlockLabelList()->begin(); blockIterator != _editor.getBlockLabelList()->end(); ++blockIterator)
        {
            if(blockIterator->getDistance(xCoordinate, yCoordinate) < getTolerance())
            {
                if(_nodesAreSelected)
                {
                    for(plf::colony<node>::iterator nodeIterator = _editor.getNodeList()->begin(); nodeIterator != _editor.getNodeList()->end(); ++nodeIterator)
                    {
                        nodeIterator->setSelectState(false);
                        nodesSeleted = 0;
                    }
                }
                else if(_arcsAreSelected)
                {
                   for(plf::colony<arcShape>::iterator arcIterator = _editor.getArcList()->begin(); arcIterator != _editor.getArcList()->end(); ++arcIterator)
                    {
                        arcIterator->setSelectState(false);
                        arcsSelected = 0;
                    } 
                }
                else if(_linesAreSelected)
                {
                    for(plf::colony<edgeLineShape>::iterator lineIterator = _editor.getLineList()->begin(); lineIterator != _editor.getLineList()->end(); ++lineIterator)
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
        for(plf::colony<edgeLineShape>::iterator lineIterator = _editor.getLineList()->begin(); lineIterator != _editor.getLineList()->end(); ++lineIterator)
        {
            if(_editor.calculateShortestDistance(xCoordinate, yCoordinate, *lineIterator) < getTolerance())
            {
                if(_nodesAreSelected)
                {
                    for(plf::colony<node>::iterator nodeIterator = _editor.getNodeList()->begin(); nodeIterator != _editor.getNodeList()->end(); ++nodeIterator)
                    {
                        nodeIterator->setSelectState(false);
                        nodesSeleted = 0;
                    }
                }
                else if(_arcsAreSelected)
                {
                   for(plf::colony<arcShape>::iterator arcIterator = _editor.getArcList()->begin(); arcIterator != _editor.getArcList()->end(); ++arcIterator)
                    {
                        arcIterator->setSelectState(false);
                        arcsSelected = 0;
                    } 
                }
                else if(_labelsAreSelected)
                {
                   for(plf::colony<blockLabel>::iterator blockIterator = _editor.getBlockLabelList()->begin(); blockIterator != _editor.getBlockLabelList()->end(); ++blockIterator)
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
        for(plf::colony<arcShape>::iterator arcIterator = _editor.getArcList()->begin(); arcIterator != _editor.getArcList()->end(); ++arcIterator)
        {
            if(_editor.calculateShortestDistanceFromArc(*arcIterator, xCoordinate, yCoordinate) < getTolerance())
            {
                if(_nodesAreSelected)
                {
                    for(plf::colony<node>::iterator nodeIterator = _editor.getNodeList()->begin(); nodeIterator != _editor.getNodeList()->end(); ++nodeIterator)
                    {
                        nodeIterator->setSelectState(false);
                        nodesSeleted = 0;
                    }
                }
                else if(_linesAreSelected)
                {
                    for(plf::colony<edgeLineShape>::iterator lineIterator = _editor.getLineList()->begin(); lineIterator != _editor.getLineList()->end(); ++lineIterator)
                    {
                        lineIterator->setSelectState(false);
                        linesSelected = 0;
                    }
                }
                else if(_labelsAreSelected)
                {
                   for(plf::colony<blockLabel>::iterator blockIterator = _editor.getBlockLabelList()->begin(); blockIterator != _editor.getBlockLabelList()->end(); ++blockIterator)
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
        for(plf::colony<node>::iterator nodeIterator = _editor.getNodeList()->begin(); nodeIterator != _editor.getNodeList()->end(); ++nodeIterator)
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
        for(plf::colony<edgeLineShape>::iterator lineIterator = _editor.getLineList()->begin(); lineIterator != _editor.getLineList()->end(); ++lineIterator)
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
       for(plf::colony<blockLabel>::iterator blockIterator = _editor.getBlockLabelList()->begin(); blockIterator != _editor.getBlockLabelList()->end(); ++blockIterator)
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
       for(plf::colony<arcShape>::iterator arcIterator = _editor.getArcList()->begin(); arcIterator != _editor.getArcList()->end(); ++arcIterator)
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