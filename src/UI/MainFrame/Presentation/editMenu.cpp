/*
	This file will contain all of the class implementation for the edit menu in the menu bar of the main fram
*/

#include "UI/OmniFEM.h"

void OmniFEMMainFrame::onPreferences(wxCommandEvent &event)
{
    wxMessageBox("Preferences are located here", "Preferences", wxOK | wxICON_INFORMATION);
}

