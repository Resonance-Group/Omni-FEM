/*
	This file will contain all of the class implementation for the mesh menu in the menu bar of the main fram
*/

#include "UI/OmniFEMFrame.h"
#include "Mesh/meshMaker.h"

void OmniFEMMainFrame::onCreateMesh(wxCommandEvent &event)
{
	meshMaker meshTest(_model->getModelNodeList(), _model->getModelBlockList(), _model->getModelLineList(), _model->getModelArcList());
	OmniFEMMsg::instance()->displayWindow(Status_Windows::MESH_STATUS_WINDOW);
	meshTest.mesh(_model->getMeshModel());
	_model->checkModelIsValid();
	_model->Refresh();
}


void OmniFEMMainFrame::onShowMesh(wxCommandEvent &event)
{
	wxMessageBox("Mesh Shown", "Show Mesh", wxOK | wxCANCEL | wxICON_STOP);
}


void OmniFEMMainFrame::onDeleteMesh(wxCommandEvent &event)
{
	int response = wxMessageBox("Delete Mesh Confirm", "Mesh Delete", wxOK | wxCANCEL | wxICON_WARNING);
	
	if(response == wxOK)
	{
		wxMessageBox("Mesh Deleted", "Delete Mesh", wxOK | wxICON_NONE);
	}
	else
	{
		wxMessageBox("Mesh Preserved", "Delete Mesh", wxOK | wxICON_NONE);
	}
}