#include "UI/OmniFEM.h"


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
	
	/* Creting the menu listing of the View Menu */
	menuView->Append(ID_ViewResults, "&View Results");
	
	/* Create the menu listing for the mesh menu */
	menuMesh->Append(ID_CreateMesh, "&Create Mesh");
	menuMesh->Append(ID_ShowMesh, "&Show Mesh");
	menuMesh->Append(ID_DeleteMesh, "&Delete Mesh");
    
    /* Creates the menu listing of the help menu */
    menuHelp->Append(ID_Manual, "View Manual");
    menuHelp->AppendSeparator();
    menuHelp->Append(ID_License, "License");
    menuHelp->Append(wxID_ABOUT);
	
	/*Create the menu listing of the Problem Menu */
	menuProblem->Append(ID_Precision, "&Set Precision");
    
    /* Create and display the menu bar */
    SetMenuBar(menuBar);
    CreateStatusBar();
    
    SetStatusText("Omni-FEM Simulator");
}



void OmniFEMMainFrame::OnExit(wxCommandEvent &event)
{
    Close(true);
}














