#include "UI/OmniFEMFrame.h"
#include <common/ExteriorRegion.h>



void OmniFEMMainFrame::onMaterials(wxCommandEvent &event)
{
    if(_problemDefinition.getPhysicsProblem() == physicProblems::PROB_ELECTROSTATIC)
    {
        materialDialog *materialDiag = new materialDialog(this, _problemDefinition.getElectricalMaterialList());
        if(materialDiag->ShowModal() == wxID_OK)
        {
            _model->updateProperties(EditProperty::EDIT_MATERIAL);
            _model->Refresh();
        }
    }
    else if(_problemDefinition.getPhysicsProblem() == physicProblems::PROB_MAGNETICS)
    {
        materialDialog *materialDiag = new materialDialog(this, _problemDefinition.getMagnetMaterialList()); 
        if(materialDiag->ShowModal() == wxID_OK)
        {
            _model->updateProperties(EditProperty::EDIT_MATERIAL);
            _model->Refresh();
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
            _model->updateProperties(EditProperty::EDIT_BOUNDARY);
        }
    }
    else if(_problemDefinition.getPhysicsProblem() == physicProblems::PROB_MAGNETICS)
    {
        boundaryDialog *boundaryDia = new boundaryDialog(this, _problemDefinition.getMagneticBoundaryList());
        if(boundaryDia->ShowModal() == wxID_OK)
        {
            _model->updateProperties(EditProperty::EDIT_BOUNDARY);
        }
    }
}



void OmniFEMMainFrame::onPointProperty(wxCommandEvent &event)
{
    if(_problemDefinition.getPhysicsProblem() == physicProblems::PROB_ELECTROSTATIC)
    {
        nodalPropertiesDialog *diag = new nodalPropertiesDialog(this, _problemDefinition.getNodalPropertyList(), physicProblems::PROB_ELECTROSTATIC);
        if(diag->ShowModal() == wxID_OK)
        {
            _model->updateProperties(EditProperty::EDIT_NODAL);
        }
    }
    else if(_problemDefinition.getPhysicsProblem() == physicProblems::PROB_MAGNETICS)
    {
        nodalPropertiesDialog *diag = new nodalPropertiesDialog(this, _problemDefinition.getNodalPropertyList(), physicProblems::PROB_MAGNETICS);
        if(diag->ShowModal() == wxID_OK)
        {
            _model->updateProperties(EditProperty::EDIT_NODAL);
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
            _model->updateProperties(EditProperty::EDIT_CONDUCTOR);
        }
    }
    else if(_problemDefinition.getPhysicsProblem() == physicProblems::PROB_MAGNETICS)
    {
        conductorPropertySetDialog *diag = new conductorPropertySetDialog(this, _problemDefinition.getCircuitList());
        if(diag->ShowModal() == wxID_OK)
        {
            _model->updateProperties(EditProperty::EDIT_CIRCUIT);
            _model->Refresh();
        }
    }
}



void OmniFEMMainFrame::onExteriorRegion(wxCommandEvent &event)
{
    exteriorRegionDialog *test = new exteriorRegionDialog(this);
	test->setParameters(*_problemDefinition.getExteriorRegion());
    if(test->ShowModal() == wxID_OK)
    {
		_problemDefinition.setExteriorRegion(test->getParameters());
    }
}


void OmniFEMMainFrame::onMatLibrary(wxCommandEvent &event)
{
    std::vector<electrostaticMaterial> test;
    materialLibraryDialog *library;
    
    if(_problemDefinition.getPhysicsProblem() == physicProblems::PROB_ELECTROSTATIC)
        library = new materialLibraryDialog(this, _problemDefinition.getElectricalMaterialList());
    else if(_problemDefinition.getPhysicsProblem() == physicProblems::PROB_MAGNETICS)
        library = new materialLibraryDialog(this, _problemDefinition.getMagnetMaterialList());

    if(library->ShowModal() == wxID_OK)
    {
       _model->updateProperties(EditProperty::EDIT_MATERIAL); 
    }
}