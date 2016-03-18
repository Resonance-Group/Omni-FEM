

#ifdef OMNIFEM_H_
	#include "UI/OmniFEM.h"
#endif


void OmniFEMMainFrame::OnAbout(wxCommandEvent &event)
{
    wxMessageBox("This is a test", "New File", wxOK | wxICON_INFORMATION);
}

void OmniFEMMainFrame::onManual(wxCommandEvent &event)
{
    wxMessageBox("This is the manual", "Manual", wxOK | wxICON_INFORMATION);
}

void OmniFEMMainFrame::onLicense(wxCommandEvent &event)
{
    wxMessageBox("This is the license", "License", wxOK | wxICON_INFORMATION);
}

