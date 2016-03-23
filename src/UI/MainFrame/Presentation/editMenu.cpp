/*
	This file will contain all of the class implementation for the edit menu in the menu bar of the main fram
*/

#include "UI/OmniFEMFrame.h"

void OmniFEMMainFrame::onPreferences(wxCommandEvent &event)
{
    wxMessageBox("Preferences are located here", "Preferences", wxOK | wxICON_INFORMATION);
}


void OmniFEMMainFrame::onLuaRun(wxCommandEvent &event)
{
	wxMessageBox("Running Lua Script", "Lua", wxOK | wxICON_INFORMATION);
}
