#include "UI/OmniFEMFrame.h"


void OmniFEMMainFrame::onDispGrid(wxCommandEvent &event)
{
    
}



void OmniFEMMainFrame::onSnapGrid(wxCommandEvent &event)
{
    
}



void OmniFEMMainFrame::onSetGridPreferences(wxCommandEvent &event)
{
    gridPreferences *test = new gridPreferences();
    if(test->ShowModal() == wxID_OK)
    {
        
    }
}