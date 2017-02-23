/*
	This file will contain all of the class implementation for the edit menu in the menu bar of the main fram
*/

#include "UI/OmniFEMFrame.h"

void OmniFEMMainFrame::onViewResults(wxCommandEvent &event)
{
	wxMessageBox("You are viewing results!", "Results", wxOK | wxCANCEL | wxICON_INFORMATION);
}



void OmniFEMMainFrame::onZoomIn(wxCommandEvent &event)
{
    
}



void OmniFEMMainFrame::onZoomOut(wxCommandEvent &event)
{
    
}



void OmniFEMMainFrame::onZoomWindow(wxCommandEvent &event)
{
    zoomWindow *test = new zoomWindow();
    if(test->ShowModal() == wxID_OK)
    {
        
    }
}



void OmniFEMMainFrame::onBlockName(wxCommandEvent &event)
{
    
}



void OmniFEMMainFrame::onOrphans(wxCommandEvent &event)
{
    
}



void OmniFEMMainFrame::onLua(wxCommandEvent &event)
{
    luaConsole *test = new luaConsole();
    if(test->ShowModal() == wxID_OK)
    {
        
    }
}



void OmniFEMMainFrame::onStatusBar(wxCommandEvent &event)
{
    
}