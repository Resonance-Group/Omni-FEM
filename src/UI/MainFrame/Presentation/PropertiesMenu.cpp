#include "UI/OmniFEMFrame.h"



void OmniFEMMainFrame::onMaterials(wxCommandEvent &event)
{
//    controller.createMaterialDialog();
}



void OmniFEMMainFrame::onBoundary(wxCommandEvent &event)
{
//    controller.createBoundaryDialog();
}



void OmniFEMMainFrame::onPointProperty(wxCommandEvent &event)
{
 //   controller.createNodalDialog();
}



void OmniFEMMainFrame::onCircuitsConductor(wxCommandEvent &event)
{
 //   controller.createCircuitsConductorsDialog();
}



void OmniFEMMainFrame::onExteriorRegion(wxCommandEvent &event)
{
    static double centerTest = 5.3;
    static double radius1Test = 1.2;
    static double radius2Test = 7.3;
    exteriorRegionDialog *test = new exteriorRegionDialog();
    test->setParameters(centerTest, radius1Test, radius2Test);
    if(test->ShowModal() == wxID_OK)
    {
        test->getParameters(centerTest, radius1Test, radius2Test);
    }
}


void OmniFEMMainFrame::onMatLibrary(wxCommandEvent &event)
{
    std::vector<electrostaticMaterial> test;
    materialLibraryDialog *test2 = new materialLibraryDialog(test);
    if(test2->ShowModal() == wxID_OK)
    {
        
    }
}