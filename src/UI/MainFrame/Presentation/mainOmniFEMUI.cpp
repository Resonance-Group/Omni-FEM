#include "UI/OmniFEMFrame.h"


bool OmniFEMApp::OnInit()
{
   OmniFEMMainFrame *frame = new OmniFEMMainFrame("Omni-FEM", wxPoint(50, 50), minSize);
   frame->Show(true);
   return true; 
}


OmniFEMMainFrame::OmniFEMMainFrame(const wxString &title, const wxPoint &pos, const wxSize &size) : wxFrame(NULL, wxID_ANY, title, pos, size)
{
	minSize = size;
	
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
	menuFile->Append(ID_Open, "&Open");
    menuFile->AppendSeparator();
    menuFile->Append(wxID_EXIT);
    
    /* Creating the menu listinging of the Edit Menu */
	menuEdit->Append(ID_LUASCRIPT, "&Lua Script\tCtrl-L");
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

	createTopToolBar();
	
//	this->GetClientSize(clientSizeX, clientSizeY);
	
	// This seciton will create a new panel and apply 2 buttons on the panel. 
	// The 2 buttons are associated with the panel and when the panel is destoryed, so are the buttons.
	clientAreaPanel->Create(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_SIMPLE);
	
	wxButton *buttonNewFile = new wxButton(clientAreaPanel, ID_New, "New", wxPoint(10, 10), wxSize(100, 100));
	wxButton *buttonOpenFile = new wxButton(clientAreaPanel, ID_Open, "Open", wxPoint(10, 100 + (260 - 220)), wxSize(100, 100));
}



/*!
 * The function used to create the toolbar at of the main window
 */
void OmniFEMMainFrame::createTopToolBar()
{
	wxToolBar *tempToolBar = new wxToolBar(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTB_TOP | wxNO_BORDER);	
    wxStandardPaths path = wxStandardPaths::Get();
	wxImage::AddHandler(new wxPNGHandler);
	std::string resourcesDirectory = path.GetAppDocumentsDir().ToStdString() + std::string("/GitHub/Omni-FEM/src/UI/MainFrame/resources/");// equilivant to ~ in command line. This is for the path for the source code of the resources
    
    //    mainFrameToolBar->Create(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTB_TOP | wxNO_BORDER);
    mainFrameToolBar = tempToolBar;
	/* This section will need to load the images into memory */
	wxImage saveImage(resourcesDirectory + "save.png", wxBITMAP_TYPE_PNG);
	wxImage openImage(resourcesDirectory + "Open.png", wxBITMAP_TYPE_PNG);
	wxImage newFileImage(resourcesDirectory + "new_file.png", wxBITMAP_TYPE_PNG);
	
	/* This section will convert the images into bitmaps */
	wxBitmap saveBitmap(saveImage);
	wxBitmap openImageBitmap(openImage);
	wxBitmap newFileBitmap(newFileImage);
	
	/* This section will add the tool to the toolbar */
	mainFrameToolBar->AddTool(ID_New, newFileBitmap, "New File");
	mainFrameToolBar->AddTool(ID_Open, openImageBitmap, "Open");
	mainFrameToolBar->AddTool(ID_SaveAs, saveBitmap, "Save");
	
	/* Enable the tooolbar and associate it with the main frame */
	mainFrameToolBar->Realize();
	this->SetToolBar(mainFrameToolBar);
	
//	mainFrameToolBar->EnableTool(ID_SaveAs, false);
}


void OmniFEMMainFrame::OnExit(wxCommandEvent &event)
{
    Close(true);
}



void OmniFEMMainFrame::createDimensionClient()
{
    clientAreaPanel->Destroy();
    clientAreaPanel->Create(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_SIMPLE);
    wxButton *TwoDimButton = new wxButton(clientAreaPanel, ID_TwoDim, "2-D", wxPoint(10, 10), wxSize(100, 100));
}


void OmniFEMMainFrame::onResize(wxSizeEvent &event)
{
	/*
	wxSize frameSize = event.GetSize();
	int minXsize = minSize.GetWidth();
	int minYsize = minSize.GetHeight();
	
	int currentXsize = this->GetWindowBorderSize().GetWidth();
	int currentYsize = this->GetWindowBorderSize().GetHeight();
	
	if(currentXsize < minXsize)
	{
		this->SetSize(wxSize(minXsize, currentYsize));
	}
	else if (currentYsize < minYsize)
	{
		this->SetSize(wxSize(currentXsize, minYsize));
	}
	*/
	
	
}
