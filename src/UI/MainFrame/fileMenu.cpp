/*
	This file will contain all of the class implementation for the file menu in the menu bar of the main fram
*/

//#define BOOST_NO_EXCEPTIONS

#include "UI/OmniFEMFrame.h"
#include <fstream>
#include <istream>
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

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/vector.hpp>


#include <common/GridPreferences.h>
#include <UI/GeometryEditor2D.h>




void OmniFEMMainFrame::onNewFile(wxCommandEvent &event)
{
    if(_UIState == systemState::MODEL_DEFINING || _UIState == systemState::PHYSICS_CHOOSING || _UIState == systemState::SIMULATING || _UIState == systemState::VIEWING_RESULTS)
    {
        // Create a message box confirming that the user would like to create a new file 
        if(wxMessageBox("Create New File?", "New File", wxOK | wxCANCEL | wxICON_QUESTION) == wxCANCEL)
            return;
    }
    enableToolMenuBar(false);
	_problemDefinition.defintionClear();
	_saveFilePath = "";
	if(_UIState == systemState::MODEL_DEFINING)
	{
		delete(_model);
	}
    createProblemChoosingClient();
}


void OmniFEMMainFrame::onOpenFile(wxCommandEvent &event)
{	
	wxFileDialog openFileDialog(this, "Open File", "", "", "", wxFD_OPEN | wxFD_FILE_MUST_EXIST | wxFD_CHANGE_DIR);
	
	if(openFileDialog.ShowModal() != wxID_CANCEL)
	{
		if(_UIState != systemState::MODEL_DEFINING)
			createModelDefiningClient();
			
		wxString appendedTitle = "Omni-FEM - ";
		wxString fileName;
		std::string tempFileName = openFileDialog.GetFilename().ToStdString();
		for(int i = 0; i < (tempFileName.length() - 8); i++)
			fileName += wxString(tempFileName[i]);
		appendedTitle.append(fileName.ToStdString());
		this->SetTitle(appendedTitle);
		_saveFilePath = openFileDialog.GetPath();
		_problemDefinition.defintionClear();
		load(openFileDialog.GetPath());
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
	wxString pathName(filePath);
	
	if(!pathName.Contains(wxString(".omniFEM")))
		pathName += wxString(".omniFEM");
	
	std::ofstream ofs(pathName.ToStdString());
	
	if(ofs.is_open())// TODO: Check to see if is_open will return true if another program has the filde already opened
	{
		boost::archive::text_oarchive oa(ofs);
		oa << _problemDefinition;
		gridPreferences tempPreferences;
		geometryEditor2D tempEditor;
		std::vector<double> tempSomething;
		_model->getParameters(tempPreferences, tempEditor, tempSomething);
		//oa << _model;
		oa << tempPreferences;
		oa << tempEditor;
		oa << tempSomething;
	}
	else
	{
		wxMessageBox("Please close all instances of the file before saving");
	}
	
	ofs.close();
}



void OmniFEMMainFrame::load(string filePath)
{
	std::ifstream loadFile(filePath);
	
	if(loadFile.is_open())
	{
		//modelDefinition temp(this, wxPoint(6, 6), this->GetClientSize(), _problemDefinition, this->GetStatusBar());
		//modelDefinition tempDefintion = (*_model);
		boost::archive::text_iarchive ia(loadFile);
		gridPreferences tempPreferences;
		geometryEditor2D tempEditor;
		std::vector<double> tempSomething;
		
		ia >> _problemDefinition;
		ia >> tempPreferences;
		ia >> tempEditor;
		ia >> tempSomething;
		
		_model->setParameters(tempPreferences, tempEditor, tempSomething);
		
		_model->Refresh();
	}
}