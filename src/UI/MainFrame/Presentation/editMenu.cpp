/*
	This file will contain all of the class implementation for the edit menu in the menu bar of the main fram
*/

#include "UI/OmniFEMFrame.h"
#include <common/MagneticPreference.h>

void OmniFEMMainFrame::onPreferences(wxCommandEvent &event)
{
    magneticPreference test;
	preferencesDialog *newDiag = new preferencesDialog(test);
    if(newDiag->ShowModal() == wxID_OK)
    {
        
    }
}


void OmniFEMMainFrame::onLuaRun(wxCommandEvent &event)
{
	wxMessageBox("Running Lua Script", "Lua", wxOK | wxICON_INFORMATION);
}
