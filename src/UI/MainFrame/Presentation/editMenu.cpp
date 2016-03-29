/*
	This file will contain all of the class implementation for the edit menu in the menu bar of the main fram
*/

#include "UI/OmniFEMFrame.h"

void OmniFEMMainFrame::onPreferences(wxCommandEvent &event)
{
	int windowX, windowY;
	this->GetSize(&windowX, &windowY);
	
	wxMessageBox(std::to_string(windowX) + " x " + std::to_string(windowY), "Preferences", wxOK | wxICON_INFORMATION);
}


void OmniFEMMainFrame::onLuaRun(wxCommandEvent &event)
{
	wxMessageBox("Running Lua Script", "Lua", wxOK | wxICON_INFORMATION);
}
