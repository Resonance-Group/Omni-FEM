/*
	This file will contain all of the class implementation for the edit menu in the menu bar of the main fram
*/

#include "UI/OmniFEMFrame.h"
#include <common/MagneticPreference.h>

void OmniFEMMainFrame::onPreferences(wxCommandEvent &event)
{
    if(_problemDefinition.getPhysicsProblem() == physicProblems::PROB_ELECTROSTATIC)
    {
        globalPreferencesDialog *globalPreference = new globalPreferencesDialog(this, _model->getGridPreferences(), _problemDefinition.getElectricalPreferences());
        if(globalPreference->ShowModal() == wxID_OK)
        {
            electroStaticPreference newElectriclPreferences;
            globalPreference->getPreferences(newElectriclPreferences);
            _problemDefinition.setPreferences(newElectriclPreferences);
            _model->Refresh();
            _menuGrid->Check(GridMenuID::ID_SHOW_GRID, _model->getGridPreferences()->getShowGridState());
            _menuGrid->Check(GridMenuID::ID_SNAP_GRID, _model->getGridPreferences()->getSnapGridState());
            _menuView->Check(ViewMenuID::ID_SHOW_BLOCK_NAMES, _model->getGridPreferences()->getShowBlockNameState());
        }
    }
    else if(_problemDefinition.getPhysicsProblem() == physicProblems::PROB_MAGNETICS)
    {
        globalPreferencesDialog *globalPreference = new globalPreferencesDialog(this, _model->getGridPreferences(), _problemDefinition.getMagneticPreference());
        if(globalPreference->ShowModal() == wxID_OK)
        {
            magneticPreference newMagneticPreferences;
            globalPreference->getPreferences(newMagneticPreferences);
            _problemDefinition.setPreferences(newMagneticPreferences);
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
    wxPoint test1 = wxPoint(0, 0);
    scaleDialog *test = new scaleDialog(this, test1);
    if(test->ShowModal() == wxID_OK)
    {
        
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
    
}


void OmniFEMMainFrame::onCreateOpenBoundary(wxCommandEvent &event)
{
    openBoundaryDialog *test = new openBoundaryDialog(this);
    if(test->ShowModal() == wxID_OK)
    {
        
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
