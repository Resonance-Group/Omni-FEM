#include "UI/OmniFEMFrame.h"


/***************
 * Constructor *
 ***************/
 
bool OmniFEMApp::OnInit()
{
   OmniFEMMainFrame *frame = new OmniFEMMainFrame("Omni-FEM", wxPoint(50, 50));
   frame->Show(true);
   return true; 
}

/****************************
 * Function Implementations *
 ****************************/
 
OmniFEMMainFrame::OmniFEMMainFrame(const wxString &title, const wxPoint &pos) : wxFrame(NULL, wxID_ANY, title, pos)
{
    /* This creates the main menu Bar at the top */
    _menuBar->Append(_menuFile, "&File");
    _menuBar->Append(_menuEdit, "&Edit");
    _menuBar->Append(_menuView, "&View");
    _menuBar->Append(_menuGrid, "&Grid");
    _menuBar->Append(_menuProperties, "&Properties");
    _menuBar->Append(_menuMesh, "&Mesh");
    _menuBar->Append(_analysisMenu, "&Analysis");
    _menuBar->Append(_menuHelp, "&Help");
    
    /* Creating the menu listing of File menu */
    _menuFile->Append(menubarID::ID_menubarNew, "&New\tCtrl-N");
    _menuFile->Append(menubarID::ID_menubarSave, "&Save\tCtrl-S");
    _menuFile->Append(menubarID::ID_menubarSaveAs, "&Save As");
	_menuFile->Append(menubarID::ID_menubarOpen, "&Open");
    _menuFile->AppendSeparator();
    _menuFile->Append(wxID_EXIT);
    
    /* Creating the menu listinging of the Edit Menu */
    _menuEdit->Append(EditMenuID::ID_UNDO, "&Undo");
    _menuEdit->Append(EditMenuID::ID_COPY, "&Copy");
    _menuEdit->Append(EditMenuID::ID_DELETE, "&Delete");
    _menuEdit->Append(EditMenuID::ID_MOVE, "&Move");
    _menuEdit->Append(EditMenuID::ID_SCALE, "&Scale");
    _menuEdit->Append(EditMenuID::ID_MIRROR, "&Mirror");
    _menuEdit->Append(EditMenuID::ID_CREATE_RADIUS, "&Create Radius");
    _menuEdit->Append(EditMenuID::ID_CREATE_OPEN_BOUNDARY, "&Create Open Boundary");
    _menuEdit->AppendSeparator();
    _menuEdit->Append(EditMenuID::ID_PREFERENCES, "&Preferences\tCtrl-P");
	
	/* Creting the menu listing of the View Menu */
    _menuView->Append(ViewMenuID::ID_ZOOM_IN, "&Zoom In");
    _menuView->Append(ViewMenuID::ID_ZOOM_OUT, "&Zoom Out");
    _menuView->Append(ViewMenuID::ID_ZOOM_WINDOW, "&Zoom Window");
    _menuView->AppendSeparator();
    _menuView->Append(ViewMenuID::ID_SHOW_BLOCK_NAMES, "&Show Block Name");
	_menuView->Append(ViewMenuID::ID_SHOW_ORPHANS, "&Show Orphans");
    _menuView->AppendSeparator();
    _menuView->Append(ViewMenuID::ID_SHOW_STATUSBAR, "&Status Bar");
    _menuView->Append(ViewMenuID::ID_LUA_CONSOLE, "&Lua Console");
    
    /* Create the menu listing for the grid menu option */
    _menuGrid->Append(GridMenuID::ID_SHOW_GRID, "&Display Grid");
    _menuGrid->Append(GridMenuID::ID_SNAP_GRID, "&Snap to Grid");
    _menuGrid->Append(GridMenuID::ID_SET_GRID_PREFERENCES, "&Set Grid Preferences");
    
    /* Create the menu listing for the properties option */
    _menuProperties->Append(PropertiesMenuID::ID_MATERIALS, "&Materials\tCtrl-M");
    _menuProperties->Append(PropertiesMenuID::ID_BOUNDARY, "&Boundary Conditions\tCtrl-B");
    _menuProperties->Append(PropertiesMenuID::ID_POINT, "&Nodal Properties");
    _menuProperties->Append(PropertiesMenuID::ID_CONDUCTORS, "&Circuits/Conductors");
    _menuProperties->Append(PropertiesMenuID::ID_EXTERIOR_REGION, "&Exterior Region");
    _menuProperties->AppendSeparator();
    _menuProperties->Append(PropertiesMenuID::ID_MATERIAL_LIBRARY, "&Materials Library\tCtrl-L");
    
	/* Create the menu listing for the mesh menu */
	_menuMesh->Append(menubarID::ID_menubarCreateMesh, "&Create Mesh");
	_menuMesh->Append(menubarID::ID_menubarShowMesh, "&Show Mesh");
	_menuMesh->Append(menubarID::ID_menubarDeleteMesh, "&Delete Mesh");
    
    /* Creating the listinf of the Analysis menu */
    _analysisMenu->Append(AnalysisMenuID::ID_ANALYZE, "Analyze");
    _analysisMenu->Append(AnalysisMenuID::ID_VIEW_RESULTS, "View Results");
    
    /* Creates the menu listing of the help menu */
    _menuHelp->Append(menubarID::ID_menubarManual, "View Manual");
    _menuHelp->AppendSeparator();
    _menuHelp->Append(menubarID::ID_menubarLicense, "License");
    _menuHelp->Append(wxID_ABOUT);
    
    /* Create and display the menu bar */
    SetMenuBar(_menuBar);
    CreateStatusBar();
    
    SetStatusText("Omni-FEM Simulator");
	
	createInitialStartupClient();
	enableToolMenuBar(false);
}





void OmniFEMMainFrame::enableToolMenuBar(bool enable)
{
	_menuBar->Enable(menubarID::ID_menubarShowMesh,	enable);
	_menuBar->Enable(menubarID::ID_menubarSave, enable);
	_menuBar->Enable(menubarID::ID_menubarSaveAs, enable);
	
	_menuBar->Enable(menubarID::ID_menubarCreateMesh, enable);
	_menuBar->Enable(menubarID::ID_menubarDeleteMesh, enable);
    
    _menuBar->Enable(EditMenuID::ID_COPY, enable);
    _menuBar->Enable(EditMenuID::ID_PREFERENCES, enable);
    _menuBar->Enable(EditMenuID::ID_CREATE_OPEN_BOUNDARY, enable);
    _menuBar->Enable(EditMenuID::ID_CREATE_RADIUS, enable);
    _menuBar->Enable(EditMenuID::ID_DELETE, enable);
    _menuBar->Enable(EditMenuID::ID_MIRROR, enable);
    _menuBar->Enable(EditMenuID::ID_MOVE, enable);
    _menuBar->Enable(EditMenuID::ID_SCALE, enable);
    _menuBar->Enable(EditMenuID::ID_UNDO, enable);
    
    _menuBar->Enable(ViewMenuID::ID_LUA_CONSOLE, enable);
    _menuBar->Enable(ViewMenuID::ID_SHOW_BLOCK_NAMES, enable);
    _menuBar->Enable(ViewMenuID::ID_SHOW_ORPHANS, enable);
    _menuBar->Enable(ViewMenuID::ID_SHOW_STATUSBAR, enable);
    _menuBar->Enable(ViewMenuID::ID_ZOOM_IN, enable);
    _menuBar->Enable(ViewMenuID::ID_ZOOM_OUT, enable);
    _menuBar->Enable(ViewMenuID::ID_ZOOM_WINDOW, enable);
    
    _menuBar->Enable(GridMenuID::ID_SET_GRID_PREFERENCES, enable);
    _menuBar->Enable(GridMenuID::ID_SHOW_GRID, enable);
    _menuBar->Enable(GridMenuID::ID_SNAP_GRID, enable);
    
    _menuBar->Enable(PropertiesMenuID::ID_BOUNDARY, enable);
    _menuBar->Enable(PropertiesMenuID::ID_CONDUCTORS, enable);
    _menuBar->Enable(PropertiesMenuID::ID_EXTERIOR_REGION, enable);
    _menuBar->Enable(PropertiesMenuID::ID_MATERIAL_LIBRARY, enable);
    _menuBar->Enable(PropertiesMenuID::ID_MATERIALS, enable);
    _menuBar->Enable(PropertiesMenuID::ID_POINT, enable);
    
    _menuBar->Enable(AnalysisMenuID::ID_ANALYZE, enable);
    _menuBar->Enable(AnalysisMenuID::ID_VIEW_RESULTS, enable);
}




void OmniFEMMainFrame::createInitialStartupClient()
{
    /* First, the function will need to destoy any other panels that are currently active */
	this->DestroyChildren();
    this->CreateStatusBar();
    this->SetStatusText("Omni-FEM Simulator");
    
    wxFont *font = new wxFont(8.5, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
    wxBoxSizer *buttonSizer = new wxBoxSizer(wxHORIZONTAL);
    wxPanel *initialStartPanel = new wxPanel(this, wxID_ANY);
	
	// This seciton will create a new panel and apply 2 buttons on the panel. 
	// The 2 buttons are associated with the panel and when the panel is destoryed, so are the buttons.
	
	wxButton *buttonNewFile = new wxButton(initialStartPanel, buttonID::ID_buttonNew, "New", wxDefaultPosition, wxSize(75, 23));
    buttonNewFile->SetFont(*font);
	wxButton *buttonOpenFile = new wxButton(initialStartPanel, buttonID::ID_buttonOpen, "Open", wxDefaultPosition, wxSize(75, 23));
    buttonOpenFile->SetFont(*font);
    
    buttonSizer->Add(buttonNewFile, 0, wxALL, 6);
    buttonSizer->Add(buttonOpenFile, 0, wxTOP | wxBOTTOM | wxRIGHT, 6);

    initialStartPanel->SetSizerAndFit(buttonSizer);
    
    this->SetMinSize(wxSize(initialStartPanel->GetSize().GetWidth(), initialStartPanel->GetSize().GetHeight() + this->GetStatusBar()->GetSize().GetHeight()));
    this->SetClientSize(initialStartPanel->GetSize());
    this->SetMaxSize(this->GetSize());
    

    _UIState = systemState::INITIAL_START_UP;
}



void OmniFEMMainFrame::createProblemChoosingClient()
{
    this->DestroyChildren();
    this->CreateStatusBar();
    this->SetStatusText("Omni-FEM Simulator");
    
    wxFont *font = new wxFont(8.5, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
    wxArrayString arrayPhysicsProblem;
    wxPanel *problemSelectPanel = new wxPanel();
    wxBoxSizer *footerSizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *topSizer = new wxBoxSizer(wxVERTICAL);
    _physicsProblemsListBox = new wxListBox();
    
    arrayPhysicsProblem.Add("Electrostatics");
	arrayPhysicsProblem.Add("Magnetics");
    
	problemSelectPanel->Create(this, wxID_ANY);
	
    wxStaticText *text = new wxStaticText(problemSelectPanel, wxID_ANY, "Select Physics Problem:");
    text->SetFont(*font);
    
    _physicsProblemsListBox->Create(problemSelectPanel, generalFrameButton::ID_LISTBOX, wxDefaultPosition, wxDefaultSize, arrayPhysicsProblem, wxLB_SINGLE); 
    _physicsProblemsListBox->SetFont(*font);
	_physicsProblemsListBox->SetSelection(0);
    
    topSizer->Add(text, 0, wxALL | wxALIGN_LEFT, 6);
    topSizer->Add(_physicsProblemsListBox, 0, wxLEFT | wxRIGHT | wxBOTTOM | wxALIGN_LEFT, 6);
    
	wxButton *backButton = new wxButton(problemSelectPanel, buttonID::ID_buttonBack, "Back", wxDefaultPosition, wxSize(75, 23));
    backButton->SetFont(*font);
	wxButton *finishButton = new wxButton(problemSelectPanel, buttonID::ID_buttonFinish, "Finish", wxDefaultPosition, wxSize(75, 23));
	finishButton->SetFont(*font);
    
    footerSizer->Add(backButton, 0, wxCENTER | wxLEFT | wxRIGHT | wxBOTTOM, 6);
    footerSizer->Add(finishButton, 0, wxCENTER | wxBOTTOM | wxRIGHT, 6);
    
    topSizer->Add(footerSizer, 0, wxALIGN_RIGHT);
    
    problemSelectPanel->SetSizerAndFit(topSizer);
    
    this->SetMaxSize(problemSelectPanel->GetSize() + (this->GetSize() - this->GetClientSize()));

    this->SetClientSize(problemSelectPanel->GetSize());
    
    this->SetMinSize(this->GetSize());

    _UIState = systemState::PHYSICS_CHOOSING;
}



void OmniFEMMainFrame::createModelDefiningClient()
{
    this->DestroyChildren();
    this->CreateStatusBar();
    this->SetStatusText("Omni-FEM Simulator");
    enableToolMenuBar(true);
    createTopToolBar();

//	wxSize modelBuilderPanelSize = wxSize((int)((double)0.17 * (double)clientSizeWidth - (double)20), (int)((double)0.66 * (double)clientSizeLength));

	/* This section is creating the general layout of the panel using he sizers in wxWidgets 
	modelBuilderTreePanel = new wxPanel(this, panelID::ID_modelBuilderTree, wxDefaultPosition, modelBuilderPanelSize, wxBORDER_SIMPLE | wxVSCROLL | wxHSCROLL);
//	groupOneSizer->Add(modelBuilderTreePanel, 1, wxALIGN_LEFT | wxALL | wxEXPAND, controller.getBorderSize());

	//geometryBuilderPanel = new wxPanel(this, panelID::ID_geometryBuilder, wxDefaultPosition, wxSize((int)((double)0.66 * (double)clientSizeWidth), (int)((double)0.66 * (double)clientSizeLength)), wxBORDER_SIMPLE);
	twoDimGeometryEditor = new geometryEditor2DPresentation(this, wxDefaultPosition, wxSize((int)((double)0.66 * (double)clientSizeWidth), (int)((double)0.66 * (double)clientSizeLength)));
	
//	groupOneSizer->Add(twoDimGeometryEditor, 3, wxALIGN_CENTER | wxALL | wxEXPAND, controller.getBorderSize());// THe middle frame will get the highest propoty when sizing becuase this is what the user will use most often
	
	settingsPanel = new wxPanel(this, panelID::ID_settings, wxDefaultPosition, wxSize((int)((double)0.17 * (double)clientSizeWidth - (double)20), (int)((double)0.66 * (double)clientSizeLength)), wxBORDER_SIMPLE);
//	groupOneSizer->Add(settingsPanel, 1, wxALIGN_RIGHT | wxALL | wxEXPAND, controller.getBorderSize());
	
//	vertBoxSizer->Add(groupOneSizer, 1, wxALL | wxEXPAND, controller.getBorderSize());
	
	statusInfoPanel = new wxPanel(this, panelID::ID_status, wxDefaultPosition, wxSize(clientSizeWidth - 20, clientSizeLength - (int)((double)0.66 * (double)clientSizeLength + (double)20) - 10), wxBORDER_SIMPLE);
//	vertBoxSizer->Add(statusInfoPanel, 0, wxEXPAND | wxALL, controller.getBorderSize());
	
	
	/* This section is populating the layout with everything that is needed for the user */
	/*********************************
	* Tree Ctrl (Hiearchary Listbox) *
	**********************************/
	
//	modelbuilderTreeCtrl = new wxTreeCtrl(modelBuilderTreePanel, wxID_ANY, wxDefaultPosition, modelBuilderPanelSize - wxSize(2, 0), wxTR_TWIST_BUTTONS | wxTR_NO_LINES | wxTR_FULL_ROW_HIGHLIGHT | wxTR_SINGLE | wxTR_HAS_BUTTONS);// The -2 appears in the size in order to give some extra room for hte scroll bars
	
//	controller.setRootTreeIDAbstraction(modelbuilderTreeCtrl->AddRoot(controller.getWorkspaceNameAbstraction()));// This is the highest level
	
//	controller.setAbstractProblemID(modelbuilderTreeCtrl->AppendItem(controller.getRootTreeIDAbstraction(), controller.getAbstractSimName()));// This will be for the project
//	
//	controller.setAbstractGeometryID(modelbuilderTreeCtrl->AppendItem(controller.getAbstractProblemID(), "Geometry"));
//	controller.setAbstractMaterialsID(modelbuilderTreeCtrl->AppendItem(controller.getAbstractProblemID(), "Materials"));
//	controller.setAbstractMeshID(modelbuilderTreeCtrl->AppendItem(controller.getAbstractProblemID(), "Mesh"));
	
//	modelbuilderTreeCtrl->ExpandAll();
	
	/*******************
	* Geometry Builder *
	********************/
//	wxGLCanvas *test = new wxGLCanvas(twoDimDeometryEditor);
//	twoDimGeometryEditor->createOpenGLCanvas();
//	twoDimGeometryEditor->render();
//	this->SetSizer(vertBoxSizer);
//	this->Layout();
	
//	controller.updateOmniFEMState(systemState::problemDefining);
	
}




void OmniFEMMainFrame::createTopToolBar()
{
    wxInitAllImageHandlers();
    
    wxStandardPaths path = wxStandardPaths::Get();
	wxImage::AddHandler(new wxPNGHandler);
    std::string test1 = path.GetAppDocumentsDir().ToStdString();
    std::string test2 = path.GetConfigDir().ToStdString();
    std::string test3 = path.GetDataDir().ToStdString();
    std::string test4 = path.GetDocumentsDir().ToStdString();
    std::string test5 = path.GetExecutablePath().ToStdString();
    std::string test6 = path.GetInstallPrefix().ToStdString();
    std::string test7 = path.GetLocalDataDir().ToStdString();
    std::string test8 = path.GetPluginsDir().ToStdString();
    std::string test9 = path.GetResourcesDir().ToStdString();
    std::string test10 = path.GetTempDir().ToStdString();
    std::string test11 = path.GetUserConfigDir().ToStdString();
    std::string test12 = path.GetUserDataDir().ToStdString();
    std::string test13 = path.GetUserLocalDataDir().ToStdString()''
	std::string resourcesDirectory = path.GetAppDocumentsDir().ToStdString() + std::string("/GitHub/Omni-FEM/src/UI/MainFrame/resources/");// equilivant to ~ in command line. This is for the path for the source code of the resources
    
    _mainFrameToolBar->Create(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTB_TOP | wxNO_BORDER);

	/* This section will need to load the images into memory */
	wxImage saveImage(resourcesDirectory + "save.png", wxBITMAP_TYPE_PNG);
	wxImage openImage(resourcesDirectory + "Open.png", wxBITMAP_TYPE_PNG);
	wxImage newFileImage(resourcesDirectory + "new_file.png", wxBITMAP_TYPE_PNG);
	
	/* This section will convert the images into bitmaps */
	wxBitmap saveBitmap(saveImage);
	wxBitmap openImageBitmap(openImage);
	wxBitmap newFileBitmap(newFileImage);
	
	/* This section will add the tool to the toolbar */
	_mainFrameToolBar->AddTool(toolbarID::ID_ToolBarNew, "New File", newFileBitmap);
	_mainFrameToolBar->AddTool(toolbarID::ID_ToolBarOpen, "Open", openImageBitmap);
	_mainFrameToolBar->AddTool(toolbarID::ID_ToolBarSave, "Save", saveBitmap);
	
	/* Enable the tooolbar and associate it with the main frame */
	_mainFrameToolBar->Realize();
	this->SetToolBar(_mainFrameToolBar);

}



void OmniFEMMainFrame::OnExit(wxCommandEvent &event)
{
    Close(true);
}









	/********************
	 * Event Procedures *
	 ********************/
	 
void OmniFEMMainFrame::physicsProblemComboBox(wxCommandEvent &event)
{
    /*
	int physicsSelection = event.GetSelection();
	
	if(physicsSelection == 0)
		controller.setAbstractProblemPhysics(physicProblems::electrostatics);
	else if(physicsSelection == 1)
		controller.setAbstractProblemPhysics(physicProblems::magnetics);
         */ 
}


void OmniFEMMainFrame::onResize(wxSizeEvent &event)
{
    /*
	systemState currentState = controller.getOmniFEMState();
	this->GetClientSize(&clientSizeWidth, &clientSizeLength);// This will update the client size
	
	if(currentState == systemState::initialStartUp || currentState == systemState::dimensionChoosing || currentState == systemState::problemChooseing)
	{
		return;
	}
	else if(currentState == systemState::problemDefining)
	{
		// geometryBuilderPanel = new wxPanel(this, panelID::ID_geometryBuilder, wxPoint((int)((double)0.17 * (double)clientSizeWidth), 10), wxSize((int)((double)0.66 * (double)clientSizeWidth), (int)((double)0.66 * (double)clientSizeLength)), wxBORDER_SIMPLE);
		// settingsPanel = new wxPanel(this, panelID::ID_settings, wxPoint((int)((double)0.82 * (double)clientSizeWidth + (double)20), 10), wxSize((int)((double)0.17 * (double)clientSizeWidth - (double)20), (int)((double)0.66 * (double)clientSizeLength)), wxBORDER_SIMPLE);
		// modelBuilderTreePanel = new wxPanel(this, panelID::ID_modelBuilderTree, wxPoint(10, 10), wxSize((int)((double)0.17 * (double)clientSizeWidth - (double)20), (int)((double)0.66 * (double)clientSizeLength)), wxBORDER_SIMPLE);
		// statusInfoPanel = new wxPanel(this, panelID::ID_status, wxPoint(10, (int)((double)0.66 * (double)clientSizeLength + (double)20)), wxSize(clientSizeWidth - 20, clientSizeLength - (int)((double)0.66 * (double)clientSizeLength + (double)20) - 10), wxBORDER_SIMPLE);
		this->Layout();
		
		wxSize newTreeCtrlDim = modelBuilderTreePanel->GetSize() - wxSize(2, 0);
		modelbuilderTreeCtrl->SetSize(newTreeCtrlDim);
	}
     */ 
}




void OmniFEMMainFrame::onBackButton(wxCommandEvent &event)
{
    createInitialStartupClient();
}



void OmniFEMMainFrame::onFinishButton(wxCommandEvent &event)
{
    int temp = _physicsProblemsListBox->GetSelection() + 1;
    _model.getProblemParameters()->setPhysicsProblem((physicProblems)temp);
	createModelDefiningClient();
}



	/**************
	* Event Table *
	***************/



wxBEGIN_EVENT_TABLE(OmniFEMMainFrame, wxFrame)
	/**********************
	* Menu event Handling *
	***********************/
	
    /* This section is for the file menu */
    EVT_MENU(menubarID::ID_menubarNew,   OmniFEMMainFrame::onNewFile)
    EVT_MENU(menubarID::ID_menubarSave, OmniFEMMainFrame::OnSave)
    EVT_MENU(menubarID::ID_menubarSaveAs, OmniFEMMainFrame::onSaveAs)
	EVT_MENU(menubarID::ID_menubarOpen, OmniFEMMainFrame::onOpenFile)
    
    /* This section is for the Edit menu */
	EVT_MENU(menubarID::ID_menubarLUASCRIPT, OmniFEMMainFrame::onLuaRun)
    EVT_MENU(EditMenuID::ID_PREFERENCES, OmniFEMMainFrame::onPreferences)
    EVT_MENU(EditMenuID::ID_COPY, OmniFEMMainFrame::onCopy)
    EVT_MENU(EditMenuID::ID_SCALE, OmniFEMMainFrame::onScale)
    EVT_MENU(EditMenuID::ID_MIRROR, OmniFEMMainFrame::onMirror)
    EVT_MENU(EditMenuID::ID_UNDO, OmniFEMMainFrame::onUndo)
    EVT_MENU(EditMenuID::ID_DELETE, OmniFEMMainFrame::onDelete)
    EVT_MENU(EditMenuID::ID_MOVE, OmniFEMMainFrame::onMove)
    EVT_MENU(EditMenuID::ID_CREATE_RADIUS, OmniFEMMainFrame::onCreateRadius)
    EVT_MENU(EditMenuID::ID_CREATE_OPEN_BOUNDARY, OmniFEMMainFrame::onCreateOpenBoundary)
	
	/* This section is for the View menu */
    EVT_MENU(ViewMenuID::ID_ZOOM_IN, OmniFEMMainFrame::onZoomIn)
    EVT_MENU(ViewMenuID::ID_ZOOM_OUT, OmniFEMMainFrame::onZoomOut)
    EVT_MENU(ViewMenuID::ID_ZOOM_WINDOW, OmniFEMMainFrame::onZoomWindow)
    EVT_MENU(ViewMenuID::ID_SHOW_BLOCK_NAMES, OmniFEMMainFrame::onBlockName)
    EVT_MENU(ViewMenuID::ID_SHOW_ORPHANS, OmniFEMMainFrame::onOrphans)
    EVT_MENU(ViewMenuID::ID_SHOW_STATUSBAR, OmniFEMMainFrame::onStatusBar)
    EVT_MENU(ViewMenuID::ID_LUA_CONSOLE, OmniFEMMainFrame::onLua)
	
    /* This section is for the Grid menu */
    EVT_MENU(GridMenuID::ID_SHOW_GRID, OmniFEMMainFrame::onDispGrid)
    EVT_MENU(GridMenuID::ID_SNAP_GRID, OmniFEMMainFrame::onSnapGrid)
    EVT_MENU(GridMenuID::ID_SET_GRID_PREFERENCES, OmniFEMMainFrame::onSetGridPreferences) 
    
    /* This section is for the Properties menu */
    EVT_MENU(PropertiesMenuID::ID_MATERIALS, OmniFEMMainFrame::onMaterials)
    EVT_MENU(PropertiesMenuID::ID_BOUNDARY, OmniFEMMainFrame::onBoundary)
    EVT_MENU(PropertiesMenuID::ID_POINT, OmniFEMMainFrame::onPointProperty)
    EVT_MENU(PropertiesMenuID::ID_CONDUCTORS, OmniFEMMainFrame::onCircuitsConductor)
    EVT_MENU(PropertiesMenuID::ID_EXTERIOR_REGION, OmniFEMMainFrame::onExteriorRegion)
    EVT_MENU(PropertiesMenuID::ID_MATERIAL_LIBRARY, OmniFEMMainFrame::onMatLibrary)
    
	/*This section is for the mesh menu */
    EVT_MENU(menubarID::ID_menubarCreateMesh, OmniFEMMainFrame::onCreateMesh)
	EVT_MENU(menubarID::ID_menubarShowMesh, OmniFEMMainFrame::onShowMesh)
	EVT_MENU(menubarID::ID_menubarDeleteMesh, OmniFEMMainFrame::onDeleteMesh)
    
    /* This section is for the Analysis menu */
    EVT_MENU(AnalysisMenuID::ID_ANALYZE, OmniFEMMainFrame::onViewResults)
	EVT_MENU(AnalysisMenuID::ID_VIEW_RESULTS, OmniFEMMainFrame::onAnalyze)
	
    /* This section is for the Help menu */
	EVT_MENU(menubarID::ID_menubarManual, OmniFEMMainFrame::onManual)
    EVT_MENU(menubarID::ID_menubarLicense, OmniFEMMainFrame::onLicense)
    EVT_MENU(wxID_ABOUT, OmniFEMMainFrame::OnAbout)
    
    /* Everything Else */
    EVT_MENU(wxID_EXIT,  OmniFEMMainFrame::OnExit)
	EVT_SIZE(OmniFEMMainFrame::onResize)
	
	/************************
	* Button Event Handling *
	*************************/
	
	EVT_BUTTON(buttonID::ID_buttonNew, OmniFEMMainFrame::onNewFile)
	EVT_BUTTON(buttonID::ID_buttonOpen, OmniFEMMainFrame::onOpenFile)
	EVT_BUTTON(buttonID::ID_buttonBack, OmniFEMMainFrame::onBackButton)
	EVT_BUTTON(buttonID::ID_buttonFinish, OmniFEMMainFrame::onFinishButton)
	
	/*************************
	* ToolBar Event Handling *
	**************************/	
	
	EVT_TOOL(toolbarID::ID_ToolBarNew, OmniFEMMainFrame::onNewFile)
	EVT_TOOL(toolbarID::ID_ToolBarOpen, OmniFEMMainFrame::onOpenFile)
	EVT_TOOL(toolbarID::ID_ToolBarSave, OmniFEMMainFrame::OnSave)
	
	/********
	* Other *
	*********/

	EVT_LISTBOX(generalFrameButton::ID_LISTBOX, OmniFEMMainFrame::physicsProblemComboBox)
    
wxEND_EVENT_TABLE()

wxIMPLEMENT_APP(OmniFEMApp);// This is where int main is located inside of