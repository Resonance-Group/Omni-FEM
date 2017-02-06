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
    std::vector<magneticMaterial> test;
   materialDialog *materialDiag = new materialDialog(test); 
   materialDiag->Show();
    
}