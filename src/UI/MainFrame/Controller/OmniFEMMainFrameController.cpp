#include "UI/MainFrameController.h"


OmniFEMMainFrameController::OmniFEMMainFrameController()
{
	
}



void OmniFEMMainFrameController::updateOmniFEMState(systemState omniFEMState)
{
	abstractionLayer.setOmniFEMState(omniFEMState);
}



systemState OmniFEMMainFrameController::getOmniFEMState()
{
    return abstractionLayer.getOmniFEMState();
}



void OmniFEMMainFrameController::setAbstractProblemDim(problemDimension dim)
{
	abstractionLayer.setProblemDimension(dim);
}



problemDimension OmniFEMMainFrameController::getAbstractProblemDim()
{
	return abstractionLayer.getProblemDimension();
}



physicProblems OmniFEMMainFrameController::getAbstractProblemPhysics()
{
	return abstractionLayer.getProblemPhysics();
}



void OmniFEMMainFrameController::setAbstractProblemPhysics(physicProblems phy)
{
	abstractionLayer.setProblemPhysics(phy);
}

int OmniFEMMainFrameController::getBorderSize()
{
	return abstractionLayer.getBorderWidth();
}



void OmniFEMMainFrameController::setWorkspaceNameAbstraction(wxString name)
{
	abstractionLayer.setWorkspaceName(name);
}



wxString OmniFEMMainFrameController::getWorkspaceNameAbstraction()
{
	return abstractionLayer.getworkspaceName();
}



void OmniFEMMainFrameController::setRootTreeIDAbstraction(wxTreeItemId tree)
{
	abstractionLayer.setRootTreeID(tree);
}



wxTreeItemId OmniFEMMainFrameController::getRootTreeIDAbstraction()
{
	return abstractionLayer.getRootTreeID();
}



void OmniFEMMainFrameController::setAbstractProblemID(wxTreeItemId problemID)
{
	abstractionLayer.setSimProblemID(problemID);
}



wxTreeItemId OmniFEMMainFrameController::getAbstractProblemID()
{
	return abstractionLayer.getSimProblemID();
}



void OmniFEMMainFrameController::setAbstractGeometryID(wxTreeItemId geometryID)
{
	abstractionLayer.setSimGeometryID(geometryID);
}



wxTreeItemId OmniFEMMainFrameController::getAbstractGeometryID()
{
	return abstractionLayer.getSimGeometryID();
}



void OmniFEMMainFrameController::setAbstractMaterialsID(wxTreeItemId materialsID)
{
	abstractionLayer.setSimMaterialsID(materialsID);
}



wxTreeItemId OmniFEMMainFrameController::getAbstractMaterialsID()
{
	return abstractionLayer.getSimMaterialsID();
}



void OmniFEMMainFrameController::setAbstractMeshID(wxTreeItemId simMeshID)
{
	abstractionLayer.setSimMeshID(simMeshID);
}



wxTreeItemId OmniFEMMainFrameController::getAbstractMeshID()
{
	return abstractionLayer.getSimMeshID();
}



void OmniFEMMainFrameController::setAbstractSimName(wxString name)
{
	abstractionLayer.setSimulationName(name);
}



wxString OmniFEMMainFrameController::getAbstractSimName()
{
	return abstractionLayer.getSimulationName();
}



void OmniFEMMainFrameController::createMaterialDialog()
{
    if(abstractionLayer.getProblemPhysics() == physicProblems::electrostatics)
    {
        static std::vector<electrostaticMaterial> test;
        materialDialog *materialDiag = new materialDialog(test);
        if(materialDiag->ShowModal() == wxID_OK)
        {
            test = materialDiag->getElectroMaterialList();
        }
    }
    else if(abstractionLayer.getProblemPhysics() == physicProblems::magnetics)
    {
        static std::vector<magneticMaterial> test;
        materialDialog *materialDiag = new materialDialog(test); 
        if(materialDiag->ShowModal() == wxID_OK)
        {
            test = materialDiag->getMagenticMaterialList();
        }
    }
}


void OmniFEMMainFrameController::createBoundaryDialog()
{
    
    if(abstractionLayer.getProblemPhysics() == physicProblems::electrostatics)
    {
        static std::vector<electricalBoundary> test;
        boundaryDialog *boundaryDia = new boundaryDialog(test);
        if(boundaryDia->ShowModal() == wxID_OK)
        {
            test = boundaryDia->getElectrostaticBoundaryList();
        }
    }
    else if(abstractionLayer.getProblemPhysics() == physicProblems::magnetics)
    {
        static std::vector<magneticBoundary> test;
        boundaryDialog *boundaryDia = new boundaryDialog(test);
        if(boundaryDia->ShowModal() == wxID_OK)
        {
            test = boundaryDia->getMagneticBoundaryList();
        }
    }
}



void OmniFEMMainFrameController::createNodalDialog()
{
    if(abstractionLayer.getProblemPhysics() == physicProblems::electrostatics)
    {
        static std::vector<nodalProperty> test;
        nodalPropertiesDialog *diag = new nodalPropertiesDialog(test, physicProblems::electrostatics);
        if(diag->ShowModal() == wxID_OK)
        {
            test = diag->getNodalPropertyList();
        }
    }
    else if(abstractionLayer.getProblemPhysics() == physicProblems::magnetics)
    {
        static std::vector<nodalProperty> test;
        nodalPropertiesDialog *diag = new nodalPropertiesDialog(test, physicProblems::magnetics);
        if(diag->ShowModal() == wxID_OK)
        {
            test = diag->getNodalPropertyList();
        }
    }
}



void OmniFEMMainFrameController::createCircuitsConductorsDialog()
{
    
    
    if(abstractionLayer.getProblemPhysics() == physicProblems::electrostatics)
    {
        static std::vector<conductorProperty> test;
        conductorPropertySetDialog *diag = new conductorPropertySetDialog(test);
        if(diag->ShowModal() == wxID_OK)
        {
            test = diag->getConductorList();
        }
    }
    else if(abstractionLayer.getProblemPhysics() == physicProblems::magnetics)
    {
        static std::vector<circuitProperty> test;
        conductorPropertySetDialog *diag = new conductorPropertySetDialog(test);
        if(diag->ShowModal() == wxID_OK)
        {
            test = diag->getCircuitList();
        }
    }
}