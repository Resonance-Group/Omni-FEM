#include "OmniFEM.h"


bool OmniFEMApp::OnInit()
{
   OmniFEMMainFrame *frame = new OmniFEMMainFrame("Omni-FEM", wxPoint(50, 50), wxSize(450, 340) );
   frame->Show( true );
   return true; 
}


OmniFEMMainFrame::OmniFEMMainFrame(const wxString &title, const wxPoint &pos, const wxSize &size) : wxFrame(NULL, wxID_ANY, title, pos, size)
{
    wxMenu *menuFile = new wxMenu;
    
    menuFile->Append(ID_New, "&New\tCtrl-N");
    menuFile->Append(ID_Save, "&Save\tCtrl-S");
    menuFile->Append(ID_SaveAs, "&Save As");
    menuFile->AppendSeparator();
    menuFile->Append(wxID_EXIT);
    
    wxMenu *menuHelp = new wxMenu;
    menuHelp->Append(wxID_ABOUT);
    
    wxMenuBar *menuBar = new wxMenuBar;
    menuBar->Append(menuFile, "&File");
    menuBar->Append(menuHelp, "&Help");
    
    SetMenuBar(menuBar);
    CreateStatusBar();
    
    SetStatusText("Menu test for Omni-FEM");
}

void OmniFEMMainFrame::OnExit(wxCommandEvent &event)
{
    Close(true);
}

void OmniFEMMainFrame::onNewFile(wxCommandEvent &event)
{
    wxMessageBox("Created New File", "New File Creation", wxOK | wxICON_INFORMATION);
}
void OmniFEMMainFrame::OnAbout(wxCommandEvent &event)
{
    wxMessageBox("This is a test", "New File", wxOK | wxICON_INFORMATION);
}

void OmniFEMMainFrame::OnSave(wxCommandEvent &event)
{
    wxMessageBox("Work saved", "Save", wxOK | wxICON_INFORMATION);
}

void OmniFEMMainFrame::onSaveAs(wxCommandEvent &event)
{
    wxMessageBox("Work saved in location", "Saved As", wxOK | wxICON_INFORMATION);
}
