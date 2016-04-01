/* This file contains the main data for the OmniFEM.
	For example, this structure s*/
#include "UI/OmniFEMFrame.h"

OmniFEMMainFrameAbstraction::OmniFEMMainFrameAbstraction()
{
	
}
	
	

systemState OmniFEMMainFrameAbstraction::getOmniFEMState()
{
	return omniFEMSystemState;
}



void OmniFEMMainFrameAbstraction::setOmniFEMState(systemState omniFEMState)
{
	omniFEMSystemState = omniFEMState;
}



problemDimension OmniFEMMainFrameAbstraction::getProblemDimension()
{
	return definition.getCurrentDimension();
}



void OmniFEMMainFrameAbstraction::setProblemDimension(problemDimension dimension)
{
	definition.setProblemDimension(dimension);
}


void OmniFEMMainFrameAbstraction::setProblemPhysics(physicProblems phy)
{
	definition.setPhysicsProblem(phy);
}



physicProblems OmniFEMMainFrameAbstraction::getProblemPhysics()
{
	return definition.getPhysicProblem();
}

int OmniFEMMainFrameAbstraction::getBorderWidth()
{
	return borderSize;
}



wxString OmniFEMMainFrameAbstraction::getworkspaceName()
{
	return workspaceName;
}



void OmniFEMMainFrameAbstraction::setWorkspaceName(wxString name)
{
	workspaceName = name;
}



void OmniFEMMainFrameAbstraction::setRootTreeID(wxTreeItemId tree)
{
	rootTree = tree;
}



wxTreeItemId OmniFEMMainFrameAbstraction::getRootTreeID()
{
	return rootTree;
}



void OmniFEMMainFrameAbstraction::setSimProblemID(wxTreeItemId problemID)
{
	definition.setProblemID(problemID);
}



wxTreeItemId OmniFEMMainFrameAbstraction::getSimProblemID()
{
	return definition.getProblemID();
}



void OmniFEMMainFrameAbstraction::setSimGeometryID(wxTreeItemId geometryID)
{
	definition.setGeometryID(geometryID);
}



wxTreeItemId OmniFEMMainFrameAbstraction::getSimGeometryID()
{
	return definition.getGeometryID();
}



void OmniFEMMainFrameAbstraction::setSimMaterialsID(wxTreeItemId materialsID)
{
	definition.setMaterialsID(materialsID);
}



wxTreeItemId OmniFEMMainFrameAbstraction::getSimMaterialsID()
{
	return definition.getMaterialsID();
}



void OmniFEMMainFrameAbstraction::setSimMeshID(wxTreeItemId simMeshID)
{
	definition.setMeshID(simMeshID);
}



wxTreeItemId OmniFEMMainFrameAbstraction::getSimMeshID()
{
	return definition.getMeshID();
}



void OmniFEMMainFrameAbstraction::setSimulationName(wxString simName)
{
	definition.setProblemName(simName);
}



wxString OmniFEMMainFrameAbstraction::getSimulationName()
{
	return definition.getProblemName();
}