#include "UI/OmniFEMFrame.h"
#include <common/GridPreferences.h>


void OmniFEMMainFrame::onDispGrid(wxCommandEvent &event)
{
    
}



void OmniFEMMainFrame::onSnapGrid(wxCommandEvent &event)
{
    
}



void OmniFEMMainFrame::onSetGridPreferences(wxCommandEvent &event)
{
    gridPreferencesDialog *test = new gridPreferencesDialog();
    static gridPreferences test2;
    test->setParameters(test2);
    if(test->ShowModal() == wxID_OK)
    {
        test->getParameters(test2);
    }
}