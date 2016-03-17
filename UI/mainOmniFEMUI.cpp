#include "OmniFEM.h"


bool OmniFEMApp::OnInit()
{
   OmniFEMMainFrame *frame = new OmniFEMMainFrame("Omni-FEM", wxPoint(50, 50), wxSize(450, 340) );
   frame->Show( true );
   return true; 
}


OmniFEMMainFrame::OmniFEMMainFrame(const wxString &title, const wxPoint &pos, const wxSize &size) : wxFrame(NULL, wxID_ANY, title, pos, size)
{
    /* Initilize variables */
    wxMenuBar *menuBar = new wxMenuBar;
    wxMenu *menuFile = new wxMenu;
    wxMenu *menuEdit = new wxMenu;
    wxMenu *menuView = new wxMenu;
    wxMenu *menuMesh = new wxMenu;
    wxMenu *menuProblem = new wxMenu;
    wxMenu *menuHelp = new wxMenu;
    
    /* This creates the main menu Bar at the top */
    menuBar->Append(menuFile, "&File");
    menuBar->Append(menuEdit, "&Edit");
    menuBar->Append(menuView, "&View");
    menuBar->Append(menuMesh, "&Mesh");
    menuBar->Append(menuProblem, "&Problem");
    menuBar->Append(menuHelp, "&Help");
    
    
    /* Creating the menu listing of File menu */
    menuFile->Append(ID_New, "&New\tCtrl-N");
    menuFile->Append(ID_Save, "&Save\tCtrl-S");
    menuFile->Append(ID_SaveAs, "&Save As");
    menuFile->AppendSeparator();
    menuFile->Append(wxID_EXIT);
    
    /* Creating the menu listinging of the Edit Menu */
    menuEdit->Append(ID_Preferences, "&Preferences\tCtrl-P");
    
    /* Creates the menu listing of the help menu */
    menuHelp->Append(wxID_ABOUT);
    
    /* Create and display the menu bar */
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

void OmniFEMMainFrame::onPreferences(wxCommandEvent &event)
{
    wxMessageBox("Preferences are located here", "Preferences", wxOK | wxICON_INFORMATION);
}