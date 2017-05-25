/*
	This file will contain all of the class implementation for the help menu in the menu bar of the main fram
*/

#include "UI/OmniFEMFrame.h"

void OmniFEMMainFrame::OnAbout(wxCommandEvent &event)
{
    wxAboutDialogInfo info;
	
	wxArrayString developers;
	developers.Add("Phillip Mobley <phillipmobley@resonancegroupusa.com>");
	
	info.SetName("Omni-FEM");
	info.SetVersion("Pre-Alpha");
	info.SetDescription("An Open Source Finite Element Simulator");
	info.SetCopyright("	(C) 2017 Phillip Mobley <phillipmobley@resonancegroupusa.com\r\n"
						"(C) 2016 SCASE	<scase@eng.utoledo.edu>");
	info.SetDevelopers(developers);
	
	wxAboutBox(info);
}

void OmniFEMMainFrame::onManual(wxCommandEvent &event)
{
    wxMessageBox("This is the manual", "Manual", wxOK | wxICON_INFORMATION);
}

void OmniFEMMainFrame::onLicense(wxCommandEvent &event)
{
    wxMessageBox("This is the license", "License", wxOK | wxICON_INFORMATION);
}


