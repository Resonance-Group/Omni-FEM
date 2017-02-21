/*
	This file will contain all of the class implementation for the edit menu in the menu bar of the main fram
*/

#include "UI/OmniFEMFrame.h"
#include <common/MagneticPreference.h>

void OmniFEMMainFrame::onPreferences(wxCommandEvent &event)
{
    //static magneticPreference test;
    static electroStaticPreference test;
	preferencesDialog *newDiag = new preferencesDialog(test);
    if(newDiag->ShowModal() == wxID_OK)
    {
        newDiag->getPreferences(test);
    }
}



void OmniFEMMainFrame::onCopy(wxCommandEvent &event)
{
    copyDialog *test = new copyDialog();
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


void OmniFEMMainFrame::onLuaRun(wxCommandEvent &event)
{
	wxMessageBox("Running Lua Script", "Lua", wxOK | wxICON_INFORMATION);
}
