/*
	This file will contain all of the class implementation for the edit menu in the menu bar of the main fram
*/

#include "UI/OmniFEMFrame.h"


void OmniFEMMainFrame::onZoomIn(wxCommandEvent &event)
{
    std::vector<electrostaticMaterial> test;
    blockProperty test3;
    blockPropertyDialog *test4 = new blockPropertyDialog(test, test3, false);
    if(test4->ShowModal() == wxID_OK)
    {
        test4->getBlockProperty(test3);
    }
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