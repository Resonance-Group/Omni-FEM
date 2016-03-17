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
    menuFile->Append(ID_Hello, "&New\tCtrl-N");
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

void OmniFEMMainFrame::OnHello(wxCommandEvent &event)
{
    wxLogMessage("TEST");
}
void OmniFEMMainFrame::OnAbout(wxCommandEvent &event)
{
    wxMessageBox("This is a test", "Test", wxOK | wxICON_INFORMATION);
}

