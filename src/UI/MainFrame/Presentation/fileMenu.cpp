/*
	This file will contain all of the class implementation for the file menu in the menu bar of the main fram
*/

#include "UI/OmniFEMFrame.h"

void OmniFEMMainFrame::onNewFile(wxCommandEvent &event)
{
    wxMessageBox("Created New File", "New File Creation", wxOK | wxICON_INFORMATION);
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
		wxMessageBox("Work saved", "Save", wxOK | wxICON_INFORMATION);
	}
    
}



void OmniFEMMainFrame::onSaveAs(wxCommandEvent &event)
{
	wxFileDialog saveFileDialog(this, "Save File", "", "", "", wxFD_SAVE | wxFD_OVERWRITE_PROMPT | wxFD_CHANGE_DIR);
	
	if(saveFileDialog.ShowModal() != wxID_CANCEL)
	{
		wxMessageBox("Work saved", "Save", wxOK | wxICON_INFORMATION);
	}
    
}