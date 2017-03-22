/*
	This file will contain all of the class implementation for the edit menu in the menu bar of the main fram
*/

#include "UI/OmniFEMFrame.h"
#include <common/MagneticPreference.h>

void OmniFEMMainFrame::onPreferences(wxCommandEvent &event)
{
    globalPreferencesDialog *test = new globalPreferencesDialog(this, _model->getGridPreferences(), _problemDefinition.getElectricalPreferences());
    if(test->ShowModal() == wxID_OK)
    {
        
    }
}



void OmniFEMMainFrame::onCopy(wxCommandEvent &event)
{
    moveCopyDialog *test = new moveCopyDialog(this, false);
    if(test->ShowModal() == wxID_OK)
    {
        
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
    mirrorDialog *test = new mirrorDialog(this);
    if(test->ShowModal() == wxID_OK)
    {
        
    }
}



void OmniFEMMainFrame::onUndo(wxCommandEvent &event)
{
    
}



void OmniFEMMainFrame::onDelete(wxCommandEvent &event)
{
    
}



void OmniFEMMainFrame::onMove(wxCommandEvent &event)
{
    moveCopyDialog *test = new moveCopyDialog(this, true);
    if(test->ShowModal() == wxID_OK)
    {
        
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


void OmniFEMMainFrame::onLuaRun(wxCommandEvent &event)
{
	wxMessageBox("Running Lua Script", "Lua", wxOK | wxICON_INFORMATION);
}
