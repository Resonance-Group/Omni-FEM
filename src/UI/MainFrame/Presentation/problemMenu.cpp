/*
	This file will contain all of the class implementation for the problem menu in the menu bar of the main fram
*/

#include "UI/OmniFEMFrame.h"

void OmniFEMMainFrame::onPrecision(wxCommandEvent &event)
{
	wxMessageBox("Precision set", "Precision", wxOK | wxICON_INFORMATION);
	wxMessageBox("test", "test", wxOK);
}