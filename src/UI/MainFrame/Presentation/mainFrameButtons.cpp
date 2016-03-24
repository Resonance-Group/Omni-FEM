// This file will contain all of the function definitons for the different buttons on the main UI
#include "UI/OmniFEMFrame.h"


void OmniFEMMainFrame::onTwoDimButton(wxCommandEvent &event)
{
    wxMessageBox("Creating 2D problem", "system", wxOK | wxICON_INFORMATION);
}