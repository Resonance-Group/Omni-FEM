/*
	This file will contain all of the class implementation for the file menu in the menu bar of the main fram
*/

#include "UI/OmniFEMFrame.h"

void OmniFEMMainFrame::onNewFile(wxCommandEvent &event)
{
    if(_UIState == systemState::MODEL_DEFINING || _UIState == systemState::PHYSICS_CHOOSING || _UIState == systemState::SIMULATING || _UIState == systemState::VIEWING_RESULTS)
    {
        // Create a message box confirming that the user would like to create a new file 
        if(wxMessageBox("Create New File?", "New File", wxOK | wxCANCEL | wxICON_QUESTION) == wxCANCEL)
            return;
    }
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
	wxFileDialog saveFileDialog(this, "Save File", "", "", "", wxFD_SAVE | wxFD_OVERWRITE_PROMPT | wxFD_CHANGE_DIR);
	
	if(saveFileDialog.ShowModal() != wxID_CANCEL)
	{

	}
}



void OmniFEMMainFrame::onSaveAs(wxCommandEvent &event)
{
	wxFileDialog saveFileDialog(this, "Save File As", "", "", "", wxFD_SAVE | wxFD_OVERWRITE_PROMPT | wxFD_CHANGE_DIR);
	
	if(saveFileDialog.ShowModal() != wxID_CANCEL)
	{
        wxString appendedTitle = "Omni-FEM - ";
		_problemDefinition.setName(saveFileDialog.GetFilename());
        appendedTitle.append(_problemDefinition.getName());
        this->SetTitle(appendedTitle);
	}
}