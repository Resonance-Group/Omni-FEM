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
    controller.createNodalDialog();
}



void OmniFEMMainFrame::onCircuitsConductor(wxCommandEvent &event)
{
    controller.createCircuitsConductorsDialog();
}



void OmniFEMMainFrame::onExteriorRegion(wxCommandEvent &event)
{
    
}


void OmniFEMMainFrame::onMatLibrary(wxCommandEvent &event)
{
    
}