/*
	This file will contain all of the class implementation for the edit menu in the menu bar of the main fram
*/

#include "UI/OmniFEMFrame.h"


void OmniFEMMainFrame::onZoomIn(wxCommandEvent &event)
{
    _model->zoomIn();
}



void OmniFEMMainFrame::onZoomOut(wxCommandEvent &event)
{
    _model->zoomOut();
}



void OmniFEMMainFrame::onZoomWindow(wxCommandEvent &event)
{
    if(_UIState == systemState::MODEL_DEFINING)
    {
        _model->setZoomWindow(!_model->getZoomWindow());
    }
}



void OmniFEMMainFrame::onBlockName(wxCommandEvent &event)
{
    _model->getGridPreferences()->setShowBlockNameState(_menuView->IsChecked(ViewMenuID::ID_SHOW_BLOCK_NAMES));
    _model->Refresh();
}



void OmniFEMMainFrame::onOrphans(wxCommandEvent &event)
{
    _model->displayDanglingNodes();
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
    _displayStatusMenu = _menuView->IsChecked(ViewMenuID::ID_SHOW_STATUSBAR);
    
    if(_displayStatusMenu)
    {
        this->SetStatusText("Omni-FEM Simulator");
    }
    else
    {
        this->SetStatusText(wxEmptyString);
    }
}