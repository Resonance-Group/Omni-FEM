/*
	This file will contain all of the class implementation for the file menu in the menu bar of the main fram
*/

#include "UI/OmniFEM.h"

void OmniFEMMainFrame::onNewFile(wxCommandEvent &event)
{
    wxMessageBox("Created New File", "New File Creation", wxOK | wxICON_INFORMATION);
}



void OmniFEMMainFrame::OnSave(wxCommandEvent &event)
{
    wxMessageBox("Work saved", "Save", wxOK | wxICON_INFORMATION);
}



void OmniFEMMainFrame::onSaveAs(wxCommandEvent &event)
{
    wxMessageBox("Work saved in location", "Saved As", wxOK | wxICON_INFORMATION);
}