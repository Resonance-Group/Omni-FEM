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
    if(_UIState == systemState::MODEL_DEFINING)
    {
        gridPreferences *temp = _model->getGridPreferences();
        gridPreferencesDialog *preferencesDia = new gridPreferencesDialog();
        preferencesDia->setParameters(*temp);
        if(preferencesDia->ShowModal() == wxID_OK)
        {
            preferencesDia->getParameters(*temp);
            _model->setGridPreferences(*temp);
        }
    }
}