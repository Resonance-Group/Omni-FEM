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
    menuFile->Append(menubarID::ID_menubarNew, "&New\tCtrl-N");
    menuFile->Append(menubarID::ID_menubarSave, "&Save\tCtrl-S");
    menuFile->Append(menubarID::ID_menubarSaveAs, "&Save As");
	menuFile->Append(menubarID::ID_menubarOpen, "&Open");
    menuFile->AppendSeparator();
    menuFile->Append(wxID_EXIT);
    
    /* Creating the menu listinging of the Edit Menu */
	menuEdit->Append(menubarID::ID_menubarLUASCRIPT, "&Lua Script\tCtrl-L");
    menuEdit->Append(menubarID::ID_menubarPreferences, "&Preferences\tCtrl-P");
	
	/* Creting the menu listing of the View Menu */
	menuView->Append(menubarID::ID_menubarViewResults, "&View Results");
	
	/* Create the menu listing for the mesh menu */
	menuMesh->Append(menubarID::ID_menubarCreateMesh, "&Create Mesh");
	menuMesh->Append(menubarID::ID_menubarShowMesh, "&Show Mesh");
	menuMesh->Append(menubarID::ID_menubarDeleteMesh, "&Delete Mesh");
    
    /* Creates the menu listing of the help menu */
    menuHelp->Append(menubarID::ID_menubarManual, "View Manual");
    menuHelp->AppendSeparator();
    menuHelp->Append(menubarID::ID_menubarLicense, "License");
    menuHelp->Append(wxID_ABOUT);
	
	/*Create the menu listing of the Problem Menu */
	menuProblem->Append(menubarID::ID_menubarPrecision, "&Set Precision");
    
    /* Create and display the menu bar */
    SetMenuBar(menuBar);
    CreateStatusBar();
    
    SetStatusText("Omni-FEM Simulator");

	createTopToolBar();
	createInitialStartup();
	initialStartSettings();
	
	this->GetClientSize(&clientSizeWidth, &clientSizeLength);
	this->SetMinSize(minSize);
	this->SetMaxSize(minSize);
}





void OmniFEMMainFrame::initialStartSettings()
{
	menuBar->Enable(menubarID::ID_menubarShowMesh,	false);
	menuBar->Enable(menubarID::ID_menubarSave,		false);
	menuBar->Enable(menubarID::ID_menubarSaveAs,		false);
	menuBar->Enable(menubarID::ID_menubarPreferences,	false);
	menuBar->Enable(menubarID::ID_menubarViewResults,	false);
	menuBar->Enable(menubarID::ID_menubarCreateMesh,	false);
	menuBar->Enable(menubarID::ID_menubarDeleteMesh,	false);
	menuBar->Enable(menubarID::ID_menubarPrecision,	false);
	
	mainFrameToolBar->EnableTool(toolbarID::ID_ToolBarSave,	false);
}




void OmniFEMMainFrame::createInitialStartup()
{
	systemState currentState = controller.getOmniFEMState();
	
	/* First, the function will need to destoy any other panels that are currently active */
	if(currentState == systemState::dimensionChoosing)
	{
		dimSelectPanel->Destroy();
		initialStartPanel = new wxPanel();
	}
	
	// This seciton will create a new panel and apply 2 buttons on the panel. 
	// The 2 buttons are associated with the panel and when the panel is destoryed, so are the buttons.
	initialStartPanel->Create(this, wxID_ANY, wxDefaultPosition, wxSize(clientSizeWidth, clientSizeLength), wxBORDER_SIMPLE);
	
	wxButton *buttonNewFile = new wxButton(initialStartPanel, buttonID::ID_buttonNew, "New", wxPoint(10, 10), wxSize(100, 100));
	wxButton *buttonOpenFile = new wxButton(initialStartPanel, buttonID::ID_buttonOpen, "Open", wxPoint(10, 100 + (260 - 220)), wxSize(100, 100));

	controller.updateOmniFEMState(systemState::initialStartUp);
}



void OmniFEMMainFrame::createTopToolBar()
{
    wxStandardPaths path = wxStandardPaths::Get();
	wxImage::AddHandler(new wxPNGHandler);
	std::string resourcesDirectory = path.GetAppDocumentsDir().ToStdString() + std::string("/GitHub/Omni-FEM/src/UI/MainFrame/resources/");// equilivant to ~ in command line. This is for the path for the source code of the resources
    
    mainFrameToolBar->Create(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTB_TOP | wxNO_BORDER);

	/* This section will need to load the images into memory */
	wxImage saveImage(resourcesDirectory + "save.png", wxBITMAP_TYPE_PNG);
	wxImage openImage(resourcesDirectory + "Open.png", wxBITMAP_TYPE_PNG);
	wxImage newFileImage(resourcesDirectory + "new_file.png", wxBITMAP_TYPE_PNG);
	
	/* This section will convert the images into bitmaps */
	wxBitmap saveBitmap(saveImage);
	wxBitmap openImageBitmap(openImage);
	wxBitmap newFileBitmap(newFileImage);
	
	/* This section will add the tool to the toolbar */
	mainFrameToolBar->AddTool(toolbarID::ID_ToolBarNew, newFileBitmap, "New File");
	mainFrameToolBar->AddTool(toolbarID::ID_ToolBarOpen, openImageBitmap, "Open");
	mainFrameToolBar->AddTool(toolbarID::ID_ToolBarSave, saveBitmap, "Save");
	
	/* Enable the tooolbar and associate it with the main frame */
	mainFrameToolBar->Realize();
	this->SetToolBar(mainFrameToolBar);
}



void OmniFEMMainFrame::OnExit(wxCommandEvent &event)
{
    Close(true);
}



void OmniFEMMainFrame::createDimensionClient()
{
	systemState currentState = controller.getOmniFEMState();
	
	if(currentState == systemState::problemChooseing)
		problemSelectPanel->Destroy();
	else
		initialStartPanel->Destroy();
		
    dimSelectPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(clientSizeWidth, clientSizeLength), wxBORDER_SIMPLE);
    wxButton *TwoDimButton = new wxButton(dimSelectPanel, buttonID::ID_buttonTwoDim, "2-D", wxPoint(10, 50), wxSize(50, 50));
	wxButton *backButton = new wxButton(dimSelectPanel, buttonID::ID_buttonBack, "Back", wxPoint(10, 100 + (260 - 220)), wxSize(100, 25));
	wxStaticText *text = new wxStaticText(dimSelectPanel, wxID_ANY, "Choose Dimension:");
	
	
	controller.updateOmniFEMState(systemState::dimensionChoosing);
}



void OmniFEMMainFrame::createProblemChoosingClient()
{
	dimSelectPanel->Destroy();
	
	problemSelectPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(clientSizeWidth, clientSizeLength), wxBORDER_SIMPLE);
	
	wxButton *backButton = new wxButton(problemSelectPanel, buttonID::ID_buttonBack, "Back", wxPoint(10, 100 + (260 - 220)), wxSize(100, 25));
	
	controller.updateOmniFEMState(systemState::problemChooseing);
}



void OmniFEMMainFrame::onResize(wxSizeEvent &event)
{
	systemState currentState = controller.getOmniFEMState();
	this->GetClientSize(&clientSizeWidth, &clientSizeLength);// This will update the client size
	
	if(currentState == systemState::initialStartUp || currentState == systemState::dimensionChoosing || currentState == systemState::problemChooseing)
	{
		return;
	}
}
