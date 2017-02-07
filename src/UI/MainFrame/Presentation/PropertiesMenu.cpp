#include "UI/OmniFEMFrame.h"



void OmniFEMMainFrame::onMaterials(wxCommandEvent &event)
{
    controller.createMaterialDialog();
}



void OmniFEMMainFrame::onBoundary(wxCommandEvent &event)
{
    controller.createBoundaryDialog();
}



void OmniFEMMainFrame::onPointProperty(wxCommandEvent &event)
{
    
}



void OmniFEMMainFrame::onCircuitsConductor(wxCommandEvent &event)
{
    
}



void OmniFEMMainFrame::onMatLibrary(wxCommandEvent &event)
{
    
}