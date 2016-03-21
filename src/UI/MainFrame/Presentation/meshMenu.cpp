/*
	This file will contain all of the class implementation for the mesh menu in the menu bar of the main fram
*/

#include "UI/OmniFEM.h"

void OmniFEMMainFrame::onCreateMesh(wxCommandEvent &event)
{
	wxMessageBox("Mesh Created", "Create Mesh", wxOK | wxCANCEL | wxICON_EXCLAMATION);
}


void OmniFEMMainFrame::onShowMesh(wxCommandEvent &event)
{
	wxMessageBox("Mesh Shown", "Show Mesh", wxOK | wxCANCEL | wxICON_STOP);
}


void OmniFEMMainFrame::onDeleteMesh(wxCommandEvent &event)
{
	int response = wxMessageBox("Delete Mesh Confirm", "Mesh Delete", wxOK | wxCANCEL | wxICON_WARNING);
	
	if(response == wxOK)
	{
		wxMessageBox("Mesh Deleted", "Delete Mesh", wxOK | wxICON_NONE);
	}
	else
	{
		wxMessageBox("Mesh Preserved", "Delete Mesh", wxOK | wxICON_NONE);
	}
}