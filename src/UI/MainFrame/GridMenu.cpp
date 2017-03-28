#include "UI/OmniFEMFrame.h"
#include <common/GridPreferences.h>


void OmniFEMMainFrame::onDispGrid(wxCommandEvent &event)
{
    _model->getGridPreferences()->setShowGridState(_menuGrid->IsChecked(GridMenuID::ID_SHOW_GRID));
    _model->Refresh();
}



void OmniFEMMainFrame::onSnapGrid(wxCommandEvent &event)
{
    _model->getGridPreferences()->setSnapGridState(_menuGrid->IsChecked(GridMenuID::ID_SNAP_GRID));
    _model->Refresh();
}



void OmniFEMMainFrame::onSetGridPreferences(wxCommandEvent &event)
{
    if(_UIState == systemState::MODEL_DEFINING)
    {
        gridPreferences *temp = _model->getGridPreferences();
        gridPreferencesDialog *preferencesDia = new gridPreferencesDialog(this);
        preferencesDia->setParameters(*temp);
        if(preferencesDia->ShowModal() == wxID_OK)
        {
            preferencesDia->getParameters(*temp);
            _model->setGridPreferences(*temp);
            _menuGrid->Check(GridMenuID::ID_SHOW_GRID, _model->getGridPreferences()->getShowGridState());
            _menuGrid->Check(GridMenuID::ID_SNAP_GRID, _model->getGridPreferences()->getSnapGridState());
            _menuView->Check(ViewMenuID::ID_SHOW_BLOCK_NAMES, _model->getGridPreferences()->getShowBlockNameState());
        }
    }
}