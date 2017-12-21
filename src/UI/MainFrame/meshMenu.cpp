/*
	This file will contain all of the class implementation for the mesh menu in the menu bar of the main fram
*/

#include "UI/OmniFEMFrame.h"
#include "Mesh/meshMaker.h"

void OmniFEMMainFrame::onCreateMesh(wxCommandEvent &event)
{
	if(_model->getModelBlockList()->size() > 0)
	{
		if(_model->getModelNodeList()->size() >= 3 && (_model->getModelLineList()->size() >= 3 || _model->getModelArcList()->size() >= 3))
		{
			if(_problemDefinition.getSaveFilePath() != wxEmptyString)
			{
				if(_model->displayDanglingNodes() == 0)
				{
					meshMaker mesher(_problemDefinition, _model);
					OmniFEMMsg::instance()->displayWindow(Status_Windows::MESH_STATUS_WINDOW);
					_model->deleteMesh();
					mesher.mesh();
					if(_model->checkModelIsValid())
						_model->Refresh();
				}
				else
					wxMessageBox("Open boudnaries exist. Simulation must contain only closed boundaries", "Warning", wxICON_EXCLAMATION | wxOK);
			}
			else
				wxMessageBox("Save location of simulation must be specified before meshing", "Warning", wxICON_EXCLAMATION | wxOK);
		}
		else
			wxMessageBox("Not enough lines or nodes to create mesh", "Warning", wxICON_EXCLAMATION | wxOK);
	}
	else
		wxMessageBox("Need to have at least 1 block label in the geometry", "Warning", wxICON_EXCLAMATION | wxOK);
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