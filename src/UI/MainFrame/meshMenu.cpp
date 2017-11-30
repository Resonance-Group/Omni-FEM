/*
	This file will contain all of the class implementation for the mesh menu in the menu bar of the main fram
*/

#include "UI/OmniFEMFrame.h"
#include "Mesh/meshMaker.h"

void OmniFEMMainFrame::onCreateMesh(wxCommandEvent &event)
{
	meshMaker meshTest(_model->getModelNodeList(), _model->getModelBlockList(), _model->getModelLineList(), _model->getModelArcList());
	OmniFEMMsg::instance()->displayWindow(Status_Windows::MESH_STATUS_WINDOW);
	_model->deleteMesh();
	meshTest.mesh(_model->getMeshModel(), _problemDefinition.getMeshSettings());
	_model->checkModelIsValid();
	_model->Refresh();
}


void OmniFEMMainFrame::onShowMesh(wxCommandEvent &event)
{
	_model->toggleMesh();
	OmniFEMMsg::instance()->MsgStatus("Display mesh toggled to " + std::to_string(_model->getShowMeshState()));
	_model->Refresh();
}


void OmniFEMMainFrame::onDeleteMesh(wxCommandEvent &event)
{
	if(wxMessageBox("Delete Mesh Confirm", "Mesh Delete", wxOK | wxCANCEL | wxICON_WARNING) == wxOK)
	{
		wxMessageBox("Mesh Deleted", "Delete Mesh", wxOK | wxICON_NONE);
		_model->deleteMesh();
		OmniFEMMsg::instance()->MsgStatus("Mesh deleted");
		_model->Refresh();
	}
	else
	{
		wxMessageBox("Mesh Preserved", "Delete Mesh", wxOK | wxICON_NONE);
	}
}