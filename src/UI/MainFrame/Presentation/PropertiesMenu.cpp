#include "UI/OmniFEMFrame.h"



void OmniFEMMainFrame::onMaterials(wxCommandEvent &event)
{
    if(_problemDefinition.getPhysicsProblem() == physicProblems::PROB_ELECTROSTATIC)
    {
        materialDialog *materialDiag = new materialDialog(this, _problemDefinition.getElectricalMaterialList());
        if(materialDiag->ShowModal() == wxID_OK)
        {
            _problemDefinition.setMaterialList(materialDiag->getElectroMaterialList());
        }
    }
    else if(_problemDefinition.getPhysicsProblem() == physicProblems::PROB_MAGNETICS)
    {
        materialDialog *materialDiag = new materialDialog(this, _problemDefinition.getMagnetMaterialList()); 
        if(materialDiag->ShowModal() == wxID_OK)
        {
            _problemDefinition.setMaterialList(materialDiag->getMagenticMaterialList());
        }
    }
}



void OmniFEMMainFrame::onBoundary(wxCommandEvent &event)
{
    if(_problemDefinition.getPhysicsProblem() == physicProblems::PROB_ELECTROSTATIC)
    {
        boundaryDialog *boundaryDia = new boundaryDialog(this, _problemDefinition.getElectricalBoundaryList());
        if(boundaryDia->ShowModal() == wxID_OK)
        {
            _problemDefinition.setBoundaryList(boundaryDia->getElectrostaticBoundaryList());
        }
    }
    else if(_problemDefinition.getPhysicsProblem() == physicProblems::PROB_MAGNETICS)
    {
        boundaryDialog *boundaryDia = new boundaryDialog(this, _problemDefinition.getMagneticBoundaryList());
        if(boundaryDia->ShowModal() == wxID_OK)
        {
            _problemDefinition.setBoundaryList(boundaryDia->getMagneticBoundaryList());
        }
    }
}



void OmniFEMMainFrame::onPointProperty(wxCommandEvent &event)
{
    if(_problemDefinition.getPhysicsProblem() == physicProblems::PROB_ELECTROSTATIC)
    {
        nodalPropertiesDialog *diag = new nodalPropertiesDialog(this, _problemDefinition.getNodalList(), physicProblems::PROB_ELECTROSTATIC);
        if(diag->ShowModal() == wxID_OK)
        {
            _problemDefinition.setNodalList(diag->getNodalPropertyList());
        }
    }
    else if(_problemDefinition.getPhysicsProblem() == physicProblems::PROB_MAGNETICS)
    {
        nodalPropertiesDialog *diag = new nodalPropertiesDialog(this, _problemDefinition.getNodalList(), physicProblems::PROB_MAGNETICS);
        if(diag->ShowModal() == wxID_OK)
        {
            _problemDefinition.setNodalList(diag->getNodalPropertyList());
        }
    }
}



void OmniFEMMainFrame::onCircuitsConductor(wxCommandEvent &event)
{
    if(_problemDefinition.getPhysicsProblem() == physicProblems::PROB_ELECTROSTATIC)
    {
        conductorPropertySetDialog *diag = new conductorPropertySetDialog(this, _problemDefinition.getConductorList());
        if(diag->ShowModal() == wxID_OK)
        {
            _problemDefinition.setConductorList(diag->getConductorList());
        }
    }
    else if(_problemDefinition.getPhysicsProblem() == physicProblems::PROB_MAGNETICS)
    {
        conductorPropertySetDialog *diag = new conductorPropertySetDialog(this, _problemDefinition.getCircuitList());
        if(diag->ShowModal() == wxID_OK)
        {
            _problemDefinition.setCircuitList(diag->getCircuitList());
        }
    }
}



void OmniFEMMainFrame::onExteriorRegion(wxCommandEvent &event)
{
    static double centerTest = 5.3;
    static double radius1Test = 1.2;
    static double radius2Test = 7.3;
    exteriorRegionDialog *test = new exteriorRegionDialog(this);
    test->setParameters(centerTest, radius1Test, radius2Test);
    if(test->ShowModal() == wxID_OK)
    {
        test->getParameters(centerTest, radius1Test, radius2Test);
    }
}


void OmniFEMMainFrame::onMatLibrary(wxCommandEvent &event)
{
    std::vector<electrostaticMaterial> test;
    materialLibraryDialog *test2 = new materialLibraryDialog(this, test);
    if(test2->ShowModal() == wxID_OK)
    {
        
    }
}