/*
	This file will contain all of the class implementation for the edit menu in the menu bar of the main fram
*/

#include "UI/OmniFEM.h"

void OmniFEMMainFrame::onViewResults(wxCommandEvent &event)
{
	wxMessageBox("You are viewing results!", "Results", wxOK | wxCANCEL | wxICON_INFORMATION);
}