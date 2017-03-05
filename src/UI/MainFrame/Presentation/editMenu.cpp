/*
	This file will contain all of the class implementation for the edit menu in the menu bar of the main fram
*/

#include "UI/OmniFEMFrame.h"
#include <common/MagneticPreference.h>

void OmniFEMMainFrame::onPreferences(wxCommandEvent &event)
{
    /*
    if(controller.getAbstractProblemPhysics() == physicProblems::electrostatics)
    {
        static electroStaticPreference test;
        preferencesDialog *newDiag = new preferencesDialog(test);
        if(newDiag->ShowModal() == wxID_OK)
        {
            newDiag->getPreferences(test);
        }
    }
    else if(controller.getAbstractProblemPhysics() == physicProblems::magnetics)
    {
        static magneticPreference test;
        preferencesDialog *newDiag = new preferencesDialog(test);
        if(newDiag->ShowModal() == wxID_OK)
        {
            newDiag->getPreferences(test);
        }
    }
     */ 
}



void OmniFEMMainFrame::onCopy(wxCommandEvent &event)
{
    moveCopyDialog *test = new moveCopyDialog(false);
    if(test->ShowModal() == wxID_OK)
    {
        
    }
}


void OmniFEMMainFrame::onScale(wxCommandEvent &event)
{
    wxPoint test1 = wxPoint(0, 0);
    scaleDialog *test = new scaleDialog(test1);
    if(test->ShowModal() == wxID_OK)
    {
        
    }
}



void OmniFEMMainFrame::onMirror(wxCommandEvent &event)
{
    mirrorDialog *test = new mirrorDialog();
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
    moveCopyDialog *test = new moveCopyDialog(true);
    if(test->ShowModal() == wxID_OK)
    {
        
    }
}



void OmniFEMMainFrame::onCreateRadius(wxCommandEvent &event)
{
    
} 



void OmniFEMMainFrame::onCreateOpenBoundary(wxCommandEvent &event)
{
    openBoundaryDialog *test = new openBoundaryDialog();
    if(test->ShowModal() == wxID_OK)
    {
        
    }
}


void OmniFEMMainFrame::onLuaRun(wxCommandEvent &event)
{
	wxMessageBox("Running Lua Script", "Lua", wxOK | wxICON_INFORMATION);
}
