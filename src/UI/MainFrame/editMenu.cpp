/*
	This file will contain all of the class implementation for the edit menu in the menu bar of the main fram
*/

#include "UI/OmniFEMFrame.h"
#include <common/MagneticPreference.h>
#include <UI/EditMenu/CreateFilletDialog.h>


void OmniFEMMainFrame::onPreferences(wxCommandEvent &event)
{
    if(_problemDefinition.getPhysicsProblem() == physicProblems::PROB_ELECTROSTATIC)
    {
        globalPreferencesDialog *globalPreference = new globalPreferencesDialog(this, _model->getGridPreferences(), _problemDefinition.getElectricalPreferences(), _problemDefinition.getMeshSettings());
        if(globalPreference->ShowModal() == wxID_OK)
        {
            electroStaticPreference newElectriclPreferences;
			meshSettings tempSettings;
            globalPreference->getPreferences(newElectriclPreferences, tempSettings);
            _problemDefinition.setPreferences(newElectriclPreferences);
			_problemDefinition.setMeshSettings(tempSettings);
            _model->Refresh();
            _menuGrid->Check(GridMenuID::ID_SHOW_GRID, _model->getGridPreferences()->getShowGridState());
            _menuGrid->Check(GridMenuID::ID_SNAP_GRID, _model->getGridPreferences()->getSnapGridState());
            _menuView->Check(ViewMenuID::ID_SHOW_BLOCK_NAMES, _model->getGridPreferences()->getShowBlockNameState());
        }
    }
    else if(_problemDefinition.getPhysicsProblem() == physicProblems::PROB_MAGNETICS)
    {
        globalPreferencesDialog *globalPreference = new globalPreferencesDialog(this, _model->getGridPreferences(), _problemDefinition.getMagneticPreference(), _problemDefinition.getMeshSettings());
        if(globalPreference->ShowModal() == wxID_OK)
        {
            magneticPreference newMagneticPreferences;
			meshSettings tempSettings;
            globalPreference->getPreferences(newMagneticPreferences, tempSettings);
            _problemDefinition.setPreferences(newMagneticPreferences);
			_problemDefinition.setMeshSettings(tempSettings);
            _model->Refresh();
            _menuGrid->Check(GridMenuID::ID_SHOW_GRID, _model->getGridPreferences()->getShowGridState());
            _menuGrid->Check(GridMenuID::ID_SNAP_GRID, _model->getGridPreferences()->getSnapGridState());
            _menuView->Check(ViewMenuID::ID_SHOW_BLOCK_NAMES, _model->getGridPreferences()->getShowBlockNameState());
        }
    }
    
    if(_problemDefinition.getElectricalPreferences().getProblemType() == problemTypeEnum::AXISYMMETRIC || _problemDefinition.getMagneticPreference().getProblemType() == problemTypeEnum::AXISYMMETRIC)
        _menuBar->Enable(PropertiesMenuID::ID_EXTERIOR_REGION, true);
    else
        _menuBar->Enable(PropertiesMenuID::ID_EXTERIOR_REGION, false);
}



void OmniFEMMainFrame::onCopy(wxCommandEvent &event)
{
    moveCopyDialog *copyDialog = new moveCopyDialog(this, false);
    if(copyDialog->ShowModal() == wxID_OK)
    {
        if(copyDialog->rotationIsSelected())
        {
            unsigned int copies;
            wxRealPoint point;
            double angle;
            copyDialog->getRotationCopy(point, angle, copies);
            _model->copyRotateSelection(angle, point, copies);
        }
        else
        {
            unsigned int copies;
            double xShift, yShift;
            copyDialog->getTranslationCopy(xShift, yShift, copies);
            _model->copyTranslateSelection(xShift, yShift, copies);
        }
    }
}


void OmniFEMMainFrame::onScale(wxCommandEvent &event)
{
    wxRealPoint topPoint, bottomPoint, centerPoint, scalingPoint;
    
    double sf;
    
    _model->getBoundingBox(topPoint, bottomPoint);
    
    centerPoint.x = (topPoint.x + bottomPoint.x) / 2.0;
    centerPoint.y = (topPoint.y + bottomPoint.y) / 2.0;
    
    scaleDialog *scaleDlg = new scaleDialog(this, centerPoint);
    if(scaleDlg->ShowModal() == wxID_OK)
    {
        scaleDlg->getScalingParameters(sf, scalingPoint);
        _model->scaleSelection(sf, scalingPoint);
    }
}



void OmniFEMMainFrame::onMirror(wxCommandEvent &event)
{
    _model->setMirrorLineState(!_model->getMirrorLineState());
}



void OmniFEMMainFrame::onUndo(wxCommandEvent &event)
{
    
}



void OmniFEMMainFrame::onDelete(wxCommandEvent &event)
{
    _model->deleteSelection();
}



void OmniFEMMainFrame::onMove(wxCommandEvent &event)
{
    moveCopyDialog *moveDialog = new moveCopyDialog(this, true);
    if(moveDialog->ShowModal() == wxID_OK)
    {
        if(moveDialog->rotationIsSelected())
        {
            wxRealPoint point;
            double angle = 0;
            moveDialog->getRotationMove(point, angle);
            _model->moveRotateSelection(angle, point);
        }
        else
        {
            double xShift, yShift;
            moveDialog->getTranslationMove(xShift, yShift);
            _model->moveTranslateSelection(xShift, yShift);
        }
    }
}



void OmniFEMMainFrame::onCreateRadius(wxCommandEvent &event)
{
    createFilletDialog *radiusDialog = new createFilletDialog(this);
    if(radiusDialog->ShowModal() == wxID_OK)
    {
        double radiusValue = radiusDialog->getRadius();
        _model->createFillet(radiusValue);
    }
}


void OmniFEMMainFrame::onCreateOpenBoundary(wxCommandEvent &event)
{
    openBoundaryDialog *boundary = new openBoundaryDialog(this);
    if(boundary->ShowModal() == wxID_OK)
    {
        long layerNumber;
        double radius;
        double centerX;
        double centerY;
        wxRealPoint centerPoint;
        OpenBoundaryEdge boundaryEdge;
        boundary->getParameters(layerNumber, radius, centerX, centerY, boundaryEdge);
        centerPoint.x = centerX;
        centerPoint.y = centerY;
        if(_problemDefinition.getPhysicsProblem() == physicProblems::PROB_ELECTROSTATIC)
        {
            /* It is expected that the user only places one of these within a problem.
             * If more then one is used, then we will have duplicates on this matter
             */ 
            for(long i = 0; i < layerNumber; i++)
            {
                electrostaticMaterial material;
                wxString baseString = "e";
                baseString.append(std::to_string(i + 1));
                material.setName(baseString.ToStdString());
                _problemDefinition.getElectricalMaterialList()->push_back(material);
            }
            
            if(boundaryEdge == OpenBoundaryEdge::DIRICHLET)
            {
                electricalBoundary boundary;
                boundary.setBoundaryName("V=0");
                _problemDefinition.addBoundaryCondition(boundary);
            }
        }
        else if(_problemDefinition.getPhysicsProblem() == physicProblems::PROB_MAGNETICS)
        {
           for(long i = 0; i < layerNumber; i++)
            {
                magneticMaterial material;
                wxString baseString = "u";
                baseString.append(std::to_string(i + 1));
                material.setName(baseString.ToStdString());
                _problemDefinition.getMagnetMaterialList()->push_back(material);
            }
            
            if(boundaryEdge == OpenBoundaryEdge::DIRICHLET)
            {
                magneticBoundary boundary;
                boundary.setBoundaryName("A=0");
                _problemDefinition.addBoundaryCondition(boundary);
            } 
        }
        // First create the different block properties and boundary conditions needed for the open bounary to work
        _model->createOpenBoundary((unsigned int)layerNumber, radius, centerPoint, boundaryEdge);
    }
}


void OmniFEMMainFrame::onSelectGroup(wxCommandEvent &event)
{
    selectGroupDialog *dialog = new selectGroupDialog(this);
    if(dialog->ShowModal() == wxID_OK)
    {
        unsigned int groupNumber = 0;
        EditGeometry geometrySelection = dialog->getGroupNumber(groupNumber);
        _model->selectGroup(geometrySelection, groupNumber);
    }
} 




void OmniFEMMainFrame::onEditProperty(wxCommandEvent &event)
{
    _model->editSelection();
}




void OmniFEMMainFrame::onLuaRun(wxCommandEvent &event)
{
	wxMessageBox("Running Lua Script", "Lua", wxOK | wxICON_INFORMATION);
}
