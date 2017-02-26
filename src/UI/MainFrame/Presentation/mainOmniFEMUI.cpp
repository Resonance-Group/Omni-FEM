#include "UI/OmniFEMFrame.h"


/***************
 * Constructor *
 ***************/
 
bool OmniFEMApp::OnInit()
{
   OmniFEMMainFrame *frame = new OmniFEMMainFrame("Omni-FEM", wxPoint(50, 50), minSize);
   frame->Show(true);
   return true; 
}

/****************************
 * Function Implementations *
 ****************************/
 
OmniFEMMainFrame::OmniFEMMainFrame(const wxString &title, const wxPoint &pos, const wxSize &size) : wxFrame(NULL, wxID_ANY, title, pos, size)
{
	minSize = size;
	
    /* This creates the main menu Bar at the top */
    menuBar->Append(menuFile, "&File");
    menuBar->Append(menuEdit, "&Edit");
    menuBar->Append(menuView, "&View");
    menuBar->Append(menuGrid, "&Grid");
    menuBar->Append(menuProperties, "&Properties");
    menuBar->Append(menuMesh, "&Mesh");
    menuBar->Append(analysisMenu, "&Analysis");
    menuBar->Append(menuHelp, "&Help");
    
    
    /* Creating the menu listing of File menu */
    menuFile->Append(menubarID::ID_menubarNew, "&New\tCtrl-N");
    menuFile->Append(menubarID::ID_menubarSave, "&Save\tCtrl-S");
    menuFile->Append(menubarID::ID_menubarSaveAs, "&Save As");
	menuFile->Append(menubarID::ID_menubarOpen, "&Open");
    menuFile->AppendSeparator();
    menuFile->Append(wxID_EXIT);
    
    /* Creating the menu listinging of the Edit Menu */
    menuEdit->Append(EditMenuID::ID_UNDO, "&Undo");
    menuEdit->Append(EditMenuID::ID_COPY, "&Copy");
    menuEdit->Append(EditMenuID::ID_DELETE, "&Delete");
    menuEdit->Append(EditMenuID::ID_MOVE, "&Move");
    menuEdit->Append(EditMenuID::ID_SCALE, "&Scale");
    menuEdit->Append(EditMenuID::ID_MIRROR, "&Mirror");
    menuEdit->Append(EditMenuID::ID_CREATE_RADIUS, "&Create Radius");
    menuEdit->Append(EditMenuID::ID_CREATE_OPEN_BOUNDARY, "&Create Open Boundary");
    menuEdit->AppendSeparator();
    menuEdit->Append(EditMenuID::ID_PREFERENCES, "&Preferences\tCtrl-P");
	
	/* Creting the menu listing of the View Menu */
    menuView->Append(ViewMenuID::ID_ZOOM_IN, "&Zoom In");
    menuView->Append(ViewMenuID::ID_ZOOM_OUT, "&Zoom Out");
    menuView->Append(ViewMenuID::ID_ZOOM_WINDOW, "&Zoom Window");
    menuView->AppendSeparator();
    menuView->Append(ViewMenuID::ID_SHOW_BLOCK_NAMES, "&Show Block Name");
	menuView->Append(ViewMenuID::ID_SHOW_ORPHANS, "&Show Orphans");
    menuView->AppendSeparator();
    menuView->Append(ViewMenuID::ID_SHOW_STATUSBAR, "&Status Bar");
    menuView->Append(ViewMenuID::ID_LUA_CONSOLE, "&Lua Console");
    
    /* Create hte menu listing for the grid menu option */
    menuGrid->Append(GridMenuID::ID_SHOW_GRID, "&Display Grid");
    menuGrid->Append(GridMenuID::ID_SNAP_GRID, "&Snap to Grid");
    menuGrid->Append(GridMenuID::ID_SET_GRID_PREFERENCES, "&Set Grid Preferences");
    
    /* Create the menu listing for the properties option */
    menuProperties->Append(PropertiesMenuID::ID_MATERIALS, "&Materials\tCtrl-M");
    menuProperties->Append(PropertiesMenuID::ID_BOUNDARY, "&Boundary Conditions\tCtrl-B");
    menuProperties->Append(PropertiesMenuID::ID_POINT, "&Nodal Properties");
    menuProperties->Append(PropertiesMenuID::ID_CONDUCTORS, "&Circuits/Conductors");
    menuProperties->Append(PropertiesMenuID::ID_EXTERIOR_REGION, "&Exterior Region");
    menuProperties->AppendSeparator();
    menuProperties->Append(PropertiesMenuID::ID_MATERIAL_LIBRARY, "&Materials Library\tCtrl-L");
    
    
	/* Create the menu listing for the mesh menu */
	menuMesh->Append(menubarID::ID_menubarCreateMesh, "&Create Mesh");
	menuMesh->Append(menubarID::ID_menubarShowMesh, "&Show Mesh");
	menuMesh->Append(menubarID::ID_menubarDeleteMesh, "&Delete Mesh");
    
    /* Creating the listinf of the Analysis menu */
    analysisMenu->Append(AnalysisMenuID::ID_ANALYZE, "Analyze");
    analysisMenu->Append(AnalysisMenuID::ID_VIEW_RESULTS, "View Results");
    
    /* Creates the menu listing of the help menu */
    menuHelp->Append(menubarID::ID_menubarManual, "View Manual");
    menuHelp->AppendSeparator();
    menuHelp->Append(menubarID::ID_menubarLicense, "License");
    menuHelp->Append(wxID_ABOUT);
    
    /* Create and display the menu bar */
    SetMenuBar(menuBar);
    CreateStatusBar();
    
    SetStatusText("Omni-FEM Simulator");

	createTopToolBar();
	this->GetClientSize(&clientSizeWidth, &clientSizeLength);
	
	createInitialStartupClient();
	enableToolMenuBar(false);
	
	
	this->SetMinSize(minSize);
	this->SetMaxSize(minSize);
	this->SetInitialSize(minSize);
	
	
}





void OmniFEMMainFrame::enableToolMenuBar(bool enable)
{
	menuBar->Enable(menubarID::ID_menubarShowMesh,	enable);
	menuBar->Enable(menubarID::ID_menubarSave,		enable);
	menuBar->Enable(menubarID::ID_menubarSaveAs,		enable);
	menuBar->Enable(EditMenuID::ID_PREFERENCES,	enable);
	menuBar->Enable(menubarID::ID_menubarCreateMesh,	enable);
	menuBar->Enable(menubarID::ID_menubarDeleteMesh,	enable);
	
	mainFrameToolBar->EnableTool(toolbarID::ID_ToolBarSave,	enable);
}




void OmniFEMMainFrame::createInitialStartupClient()
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
	else if(currentState == systemState::initialStartUp)
		initialStartPanel->Destroy();
	else if(currentState == systemState::problemDefining)
	{
		//problemDefiningPanel->Destroy();
//		this->SetSize(minSize);
//this
//this->SetSize(500, 500);
		enableToolMenuBar(false);
//		this->SetMinSize(minSize);
//		this->SetMaxSize(minSize);
	}
		
    dimSelectPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(clientSizeWidth, clientSizeLength), wxBORDER_SIMPLE);
	
    wxButton *TwoDimButton = new wxButton(dimSelectPanel, buttonID::ID_buttonTwoDim, "2-D", wxPoint(10, 50), wxSize(50, 50));
	wxButton *backButton = new wxButton(dimSelectPanel, buttonID::ID_buttonBack, "Back", wxPoint(5, clientSizeLength - 25 - 5), wxSize(100, 25));
	
	wxStaticText *text = new wxStaticText(dimSelectPanel, wxID_ANY, "Choose Spatial Dimension:", wxPoint(5, 5));
	
	
	controller.updateOmniFEMState(systemState::dimensionChoosing);
}



void OmniFEMMainFrame::createProblemChoosingClient()
{
    wxArrayString arrayPhysicsProblem;
    
    arrayPhysicsProblem.Add("Electrostatics");
	arrayPhysicsProblem.Add("Magnetics");
    
	dimSelectPanel->Destroy();
	
	problemSelectPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(clientSizeWidth, clientSizeLength), wxBORDER_SIMPLE);
	
	wxButton *backButton = new wxButton(problemSelectPanel, buttonID::ID_buttonBack, "Back", wxPoint(5, clientSizeLength - 25 - 5), wxSize(100, 25));
	wxButton *finishButton = new wxButton(problemSelectPanel, buttonID::ID_buttonFinish, "Finish", wxPoint(125, clientSizeLength - 25 - 5), wxSize(100, 25));
	wxStaticText *text = new wxStaticText(problemSelectPanel, wxID_ANY, "Select Physics Problem:", wxPoint(5, 5));
	
	physicsProblems->Create(problemSelectPanel, comboListBoxID::ID_physicsProblems, wxPoint(5, 50), wxDefaultSize, arrayPhysicsProblem, wxLB_SINGLE); 
	physicsProblems->SetSelection(0);
	
	controller.updateOmniFEMState(systemState::problemChooseing);
}



void OmniFEMMainFrame::createModelDefiningClient()
{
	systemState currentState = controller.getOmniFEMState();
	
	
	if(currentState == systemState::initialStartUp)
		initialStartPanel->Destroy();
	else if(currentState == systemState::dimensionChoosing)
		dimSelectPanel->Destroy();
	else if(currentState == systemState::problemChooseing)
		problemSelectPanel->Destroy();
		
	enableToolMenuBar(true);
	
	this->SetMaxSize(wxSize(-1, -1));
	this->SetSize(960, 544);
	this->SetMinSize(wxSize(960, 544));
	
	
	wxSize modelBuilderPanelSize = wxSize((int)((double)0.17 * (double)clientSizeWidth - (double)20), (int)((double)0.66 * (double)clientSizeLength));
	
	/* This section is creating the general layout of the panel using he sizers in wxWidgets */
	modelBuilderTreePanel = new wxPanel(this, panelID::ID_modelBuilderTree, wxDefaultPosition, modelBuilderPanelSize, wxBORDER_SIMPLE | wxVSCROLL | wxHSCROLL);
	groupOneSizer->Add(modelBuilderTreePanel, 1, wxALIGN_LEFT | wxALL | wxEXPAND, controller.getBorderSize());

	//geometryBuilderPanel = new wxPanel(this, panelID::ID_geometryBuilder, wxDefaultPosition, wxSize((int)((double)0.66 * (double)clientSizeWidth), (int)((double)0.66 * (double)clientSizeLength)), wxBORDER_SIMPLE);
	twoDimGeometryEditor = new geometryEditor2DPresentation(this, wxDefaultPosition, wxSize((int)((double)0.66 * (double)clientSizeWidth), (int)((double)0.66 * (double)clientSizeLength)));
	
	groupOneSizer->Add(twoDimGeometryEditor, 3, wxALIGN_CENTER | wxALL | wxEXPAND, controller.getBorderSize());// THe middle frame will get the highest propoty when sizing becuase this is what the user will use most often
	
	settingsPanel = new wxPanel(this, panelID::ID_settings, wxDefaultPosition, wxSize((int)((double)0.17 * (double)clientSizeWidth - (double)20), (int)((double)0.66 * (double)clientSizeLength)), wxBORDER_SIMPLE);
	groupOneSizer->Add(settingsPanel, 1, wxALIGN_RIGHT | wxALL | wxEXPAND, controller.getBorderSize());
	
	vertBoxSizer->Add(groupOneSizer, 1, wxALL | wxEXPAND, controller.getBorderSize());
	
	statusInfoPanel = new wxPanel(this, panelID::ID_status, wxDefaultPosition, wxSize(clientSizeWidth - 20, clientSizeLength - (int)((double)0.66 * (double)clientSizeLength + (double)20) - 10), wxBORDER_SIMPLE);
	vertBoxSizer->Add(statusInfoPanel, 0, wxEXPAND | wxALL, controller.getBorderSize());
	
	
	/* This section is populating the layout with everything that is needed for the user */
	/*********************************
	* Tree Ctrl (Hiearchary Listbox) *
	**********************************/
	
	modelbuilderTreeCtrl = new wxTreeCtrl(modelBuilderTreePanel, wxID_ANY, wxDefaultPosition, modelBuilderPanelSize - wxSize(2, 0), wxTR_TWIST_BUTTONS | wxTR_NO_LINES | wxTR_FULL_ROW_HIGHLIGHT | wxTR_SINGLE | wxTR_HAS_BUTTONS);// The -2 appears in the size in order to give some extra room for hte scroll bars
	
	controller.setRootTreeIDAbstraction(modelbuilderTreeCtrl->AddRoot(controller.getWorkspaceNameAbstraction()));// This is the highest level
	
	controller.setAbstractProblemID(modelbuilderTreeCtrl->AppendItem(controller.getRootTreeIDAbstraction(), controller.getAbstractSimName()));// This will be for the project
	
	controller.setAbstractGeometryID(modelbuilderTreeCtrl->AppendItem(controller.getAbstractProblemID(), "Geometry"));
	controller.setAbstractMaterialsID(modelbuilderTreeCtrl->AppendItem(controller.getAbstractProblemID(), "Materials"));
	controller.setAbstractMeshID(modelbuilderTreeCtrl->AppendItem(controller.getAbstractProblemID(), "Mesh"));
	
	modelbuilderTreeCtrl->ExpandAll();
	
	/*******************
	* Geometry Builder *
	********************/
//	wxGLCanvas *test = new wxGLCanvas(twoDimDeometryEditor);
//	twoDimGeometryEditor->createOpenGLCanvas();
//	twoDimGeometryEditor->render();
	this->SetSizer(vertBoxSizer);
	this->Layout();
	
	controller.updateOmniFEMState(systemState::problemDefining);
	
}

	/********************
	 * Event Procedures *
	 ********************/
	 
void OmniFEMMainFrame::physicsProblemComboBox(wxCommandEvent &event)
{
	int physicsSelection = event.GetSelection();
	
	if(physicsSelection == 0)
		controller.setAbstractProblemPhysics(physicProblems::electrostatics);
	else if(physicsSelection == 1)
		controller.setAbstractProblemPhysics(physicProblems::magnetics);
}


void OmniFEMMainFrame::onResize(wxSizeEvent &event)
{
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
    EVT_BUTTON(buttonID::ID_buttonTwoDim, OmniFEMMainFrame::onTwoDimButton)
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

	EVT_LISTBOX(comboListBoxID::ID_physicsProblems, OmniFEMMainFrame::physicsProblemComboBox)
    
wxEND_EVENT_TABLE()

wxIMPLEMENT_APP(OmniFEMApp);// This is where int main is located inside of