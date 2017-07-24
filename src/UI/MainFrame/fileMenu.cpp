/*
	This file will contain all of the class implementation for the file menu in the menu bar of the main fram
*/

#include "UI/OmniFEMFrame.h"
#include <fstream>
#include "UI/geometryShapes.h"

#include <common/ElectricalBoundary.h>
#include <common/ElectroStaticMaterial.h>
#include <common/ElectrostaticPreference.h>
#include <common/ConductorProperty.h>

#include <common/CircuitProperty.h>
#include <common/MagneticBoundary.h>
#include <common/MagneticMaterial.h>
#include <common/MagneticPreference.h>

#include <common/NodalProperty.h>

#include <common/ExteriorRegion.h>

void OmniFEMMainFrame::onNewFile(wxCommandEvent &event)
{
    if(_UIState == systemState::MODEL_DEFINING || _UIState == systemState::PHYSICS_CHOOSING || _UIState == systemState::SIMULATING || _UIState == systemState::VIEWING_RESULTS)
    {
        // Create a message box confirming that the user would like to create a new file 
        if(wxMessageBox("Create New File?", "New File", wxOK | wxCANCEL | wxICON_QUESTION) == wxCANCEL)
            return;
    }
    enableToolMenuBar(false);
    createProblemChoosingClient();
}


void OmniFEMMainFrame::onOpenFile(wxCommandEvent &event)
{	
	wxFileDialog openFileDialog(this, "Open File", "", "", "", wxFD_OPEN | wxFD_FILE_MUST_EXIST | wxFD_CHANGE_DIR);
	
	if(openFileDialog.ShowModal() != wxID_CANCEL)
	{
		wxMessageBox("File has been opened", "Open File", wxOK | wxICON_INFORMATION);
	}
}


void OmniFEMMainFrame::OnSave(wxCommandEvent &event)
{
	if(_saveFilePath != "")
	{
		save(_saveFilePath);
	}
	else
	{
		wxFileDialog saveFileDialog(this, "Save File", "", "", "", wxFD_SAVE | wxFD_OVERWRITE_PROMPT | wxFD_CHANGE_DIR);
		if(saveFileDialog.ShowModal() != wxID_CANCEL)
		{
			wxString appendedTitle = "Omni-FEM - ";
            wxString fileName;
            if(saveFileDialog.GetFilename().Contains(wxString(".omniFEM")))
            {
                std::string tempFileName = saveFileDialog.GetFilename().ToStdString();
                for(int i = 0; i < (tempFileName.length() - 8); i++)
                    fileName += wxString(tempFileName[i]);
            }
            else
                fileName = saveFileDialog.GetFilename();
			_problemDefinition.setName(fileName);
			appendedTitle.append(_problemDefinition.getName());
			this->SetTitle(appendedTitle);
			_saveFilePath = saveFileDialog.GetPath();
			save(_saveFilePath);
		}
	}
}



void OmniFEMMainFrame::onSaveAs(wxCommandEvent &event)
{
	wxFileDialog saveFileDialog(this, "Save File As", "", "", "", wxFD_SAVE | wxFD_OVERWRITE_PROMPT | wxFD_CHANGE_DIR);
	
	if(saveFileDialog.ShowModal() != wxID_CANCEL)
	{
        wxString appendedTitle = "Omni-FEM - ";
		wxString fileName;
		if(saveFileDialog.GetFilename().Contains(wxString(".omniFEM")))
		{
			std::string tempFileName = saveFileDialog.GetFilename().ToStdString();
			for(int i = 0; i < (tempFileName.length() - 8); i++)
				fileName += wxString(tempFileName[i]);
		}
		else
			fileName = saveFileDialog.GetFilename();
			
		_problemDefinition.setName(fileName);
        appendedTitle.append(_problemDefinition.getName());
        this->SetTitle(appendedTitle);
		_saveFilePath = saveFileDialog.GetPath();
		save(_saveFilePath);
	}
}



void OmniFEMMainFrame::save(string filePath)
{
	std::ofstream saveFile;
	wxString pathName(filePath);
	
	if(!pathName.Contains(wxString(".omniFEM")))
		pathName += wxString(".omniFEM");

	saveFile.open(pathName.ToStdString(), std::ofstream::out);
	if(saveFile.is_open())
	{	
		saveFile << "v1.0" << std::endl;
		saveFile << (int)_problemDefinition.getPhysicsProblem() << std::endl;
		saveFile << (int)_model->getGridPreferences()->getCoordinateSystem() << std::endl;
		if(_problemDefinition.getPhysicsProblem() == physicProblems::PROB_ELECTROSTATIC)
		{
			saveFile << _problemDefinition.getElectricalPreferences().getComments().ToStdString() << std::endl;
			saveFile << "\\-\\" << endl;
			saveFile << _problemDefinition.getElectricalPreferences().getDepth() << std::endl;
			saveFile << _problemDefinition.getElectricalPreferences().getMinAngle() << std::endl;
			saveFile << _problemDefinition.getElectricalPreferences().getPrecision() << std::endl;
			saveFile << (int)_problemDefinition.getElectricalPreferences().getProblemType() << std::endl;
			saveFile << (int)_problemDefinition.getElectricalPreferences().getUnitLength() << std::endl;
			
			saveFile << "MATERIALS" << std::endl;
			for(std::vector<electrostaticMaterial>::iterator materialIterator = _problemDefinition.getElectricalMaterialList()->begin(); materialIterator != _problemDefinition.getElectricalMaterialList()->end(); materialIterator++)
			{
				wxString name = wxString(materialIterator->getName());
				wxString relativePermittivityX = wxString(std::to_string(materialIterator->getEpsilonX()));
				wxString relativePermittivityY = wxString(std::to_string(materialIterator->getEpsilonY()));
				wxString chargeDensity = wxString(std::to_string(materialIterator->getChargeDensity()));
				wxString combinedForm = name + wxString(",") + relativePermittivityX + wxString(",") + relativePermittivityY + wxString(",") + chargeDensity;
				saveFile << combinedForm.ToStdString() << std::endl;
			}
			
			saveFile << "BOUNDARYCONDITIONS" << std::endl;
			for(std::vector<electricalBoundary>::iterator boundaryIterator = _problemDefinition.getElectricalBoundaryList()->begin(); boundaryIterator != _problemDefinition.getElectricalBoundaryList()->end(); boundaryIterator++)
			{
				wxString name = wxString(boundaryIterator->getBoundaryName());
				wxString boundaryType = wxString(std::to_string((int)boundaryIterator->getBC()));
				wxString c0 = wxString(std::to_string(boundaryIterator->getC0Value()));
				wxString c1 = wxString(std::to_string(boundaryIterator->getC1Value()));
				wxString sigma = wxString(std::to_string(boundaryIterator->getSigma()));
				wxString voltage = wxString(std::to_string(boundaryIterator->getVoltage()));
				wxString combinedForm = name + wxString(",") + boundaryType + wxString(",") + c0 + wxString(",") + c1 + wxString(",") + sigma + wxString(",") + voltage;
				saveFile << combinedForm.ToStdString() << endl;
			}
			
			saveFile << "NODEPROPERTIES" << std::endl;
			for(std::vector<nodalProperty>::iterator nodalIterator = _problemDefinition.getNodalPropertyList()->begin(); nodalIterator != _problemDefinition.getNodalPropertyList()->end(); nodalIterator++)
			{
				
			}
			
			saveFile << "CONDUCTORPROPERTIES" << std::endl;
			for(std::vector<conductorProperty>::iterator conductorIterator = _problemDefinition.getConductorList()->begin(); conductorIterator != _problemDefinition.getConductorList()->end(); conductorIterator++)
			{
				
			}
			
			wxString exteriorRegionData = wxString(std::to_string(_problemDefinition.getExteriorRegion()->getCenter())) + wxString(",") + wxString(std::to_string(_problemDefinition.getExteriorRegion()->getRadiusExterior())) + wxString(",") + wxString(std::to_string(_problemDefinition.getExteriorRegion()->getRadiusInterior()));
			saveFile << exteriorRegionData.ToStdString() << endl;
		}
		else if(_problemDefinition.getPhysicsProblem() == physicProblems::PROB_MAGNETICS)
		{
			saveFile << _problemDefinition.getMagneticPreference().getComments().ToStdString() << std::endl;
			saveFile << "\\-\\" << std::endl;
			saveFile << _problemDefinition.getMagneticPreference().getDepth() << std::endl;
			saveFile << (int)_problemDefinition.getMagneticPreference().getACSolver() << std::endl;
			saveFile << _problemDefinition.getMagneticPreference().getFrequency() << std::endl;
			saveFile << _problemDefinition.getMagneticPreference().getMinAngle() << std::endl;
			saveFile << _problemDefinition.getMagneticPreference().getPrecision() << std::endl;
			saveFile << (int)_problemDefinition.getMagneticPreference().getProblemType() << std::endl;
			saveFile << (int)_problemDefinition.getMagneticPreference().getUnitLength() << std::endl;
		}
		
		for(plf::colony<node>::iterator nodeIterator = _model->getModelNodeList()->begin(); nodeIterator != _model->getModelNodeList()->end(); nodeIterator++)
		{
			
		}
		
		for(plf::colony<edgeLineShape>::iterator lineIterator = _model->getModelLineList()->begin(); lineIterator != _model->getModelLineList()->end(); lineIterator++)
		{
			
		}

		for(plf::colony<arcShape>::iterator arcIterator = _model->getModelArcList()->begin(); arcIterator != _model->getModelArcList()->end(); arcIterator++)
		{
			
		}
		
		for(plf::colony<blockLabel>::iterator labelIterator = _model->getModelBlockList()->begin(); labelIterator != _model->getModelBlockList()->end(); labelIterator++)
		{
			
		}
	}	
	else
	{
		wxMessageBox("Please close all instances of the file before saving");
	}
	saveFile.close();
}