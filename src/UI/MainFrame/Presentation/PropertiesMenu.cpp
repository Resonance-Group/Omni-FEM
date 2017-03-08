#include "UI/OmniFEMFrame.h"



void OmniFEMMainFrame::onMaterials(wxCommandEvent &event)
{
    if(_model->getProblemParameters()->getPhysicsProblem() == physicProblems::PROB_ELECTROSTATIC)
    {
        materialDialog *materialDiag = new materialDialog(_model->getProblemParameters()->getElectricalMaterialList());
        if(materialDiag->ShowModal() == wxID_OK)
        {
            _model->getProblemParameters()->setMaterialList(materialDiag->getElectroMaterialList());
        }
    }
    else if(_model->getProblemParameters()->getPhysicsProblem() == physicProblems::PROB_MAGNETICS)
    {
        materialDialog *materialDiag = new materialDialog(_model->getProblemParameters()->getMagnetMaterialList()); 
        if(materialDiag->ShowModal() == wxID_OK)
        {
            _model->getProblemParameters()->setMaterialList(materialDiag->getMagenticMaterialList());
        }
    }
}



void OmniFEMMainFrame::onBoundary(wxCommandEvent &event)
{
    if(_model->getProblemParameters()->getPhysicsProblem() == physicProblems::PROB_ELECTROSTATIC)
    {
        boundaryDialog *boundaryDia = new boundaryDialog(_model->getProblemParameters()->getElectricalBoundaryList());
        if(boundaryDia->ShowModal() == wxID_OK)
        {
            _model->getProblemParameters()->setBoundaryList(boundaryDia->getElectrostaticBoundaryList());
        }
    }
    else if(_model->getProblemParameters()->getPhysicsProblem() == physicProblems::PROB_MAGNETICS)
    {
        boundaryDialog *boundaryDia = new boundaryDialog(_model->getProblemParameters()->getMagneticBoundaryList());
        if(boundaryDia->ShowModal() == wxID_OK)
        {
            _model->getProblemParameters()->setBoundaryList(boundaryDia->getMagneticBoundaryList());
        }
    }
}



void OmniFEMMainFrame::onPointProperty(wxCommandEvent &event)
{
    if(_model->getProblemParameters()->getPhysicsProblem() == physicProblems::PROB_ELECTROSTATIC)
    {
        nodalPropertiesDialog *diag = new nodalPropertiesDialog(_model->getProblemParameters()->getNodalList(), physicProblems::PROB_ELECTROSTATIC);
        if(diag->ShowModal() == wxID_OK)
        {
            _model->getProblemParameters()->setNodalList(diag->getNodalPropertyList());
        }
    }
    else if(_model->getProblemParameters()->getPhysicsProblem() == physicProblems::PROB_MAGNETICS)
    {
        nodalPropertiesDialog *diag = new nodalPropertiesDialog(_model->getProblemParameters()->getNodalList(), physicProblems::PROB_MAGNETICS);
        if(diag->ShowModal() == wxID_OK)
        {
            _model->getProblemParameters()->setNodalList(diag->getNodalPropertyList());
        }
    }
}



void OmniFEMMainFrame::onCircuitsConductor(wxCommandEvent &event)
{
    if(_model->getProblemParameters()->getPhysicsProblem() == physicProblems::PROB_ELECTROSTATIC)
    {
        conductorPropertySetDialog *diag = new conductorPropertySetDialog(_model->getProblemParameters()->getConductorList());
        if(diag->ShowModal() == wxID_OK)
        {
            _model->getProblemParameters()->setConductorList(diag->getConductorList());
        }
    }
    else if(_model->getProblemParameters()->getPhysicsProblem() == physicProblems::PROB_MAGNETICS)
    {
        conductorPropertySetDialog *diag = new conductorPropertySetDialog(_model->getProblemParameters()->getCircuitList());
        if(diag->ShowModal() == wxID_OK)
        {
            _model->getProblemParameters()->setCircuitList(diag->getCircuitList());
        }
    }
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