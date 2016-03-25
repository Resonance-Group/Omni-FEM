#ifndef OMNIFEMFrame_H_
#define OMNIFEMFrame_H_

#include <wx/wx.h>
#include <wx/aboutdlg.h>
#include <wx/stdpaths.h>
#include <string.h>
#include <wx/textctrl.h>
#include <wx/stattext.h>
#include <UI/problemDefinition.h>

// For documenting code, see: https://www.stack.nl/~dimitri/doxygen/manual/docblocks.html

class OmniFEMApp : public wxApp
{
	private:
	
		wxSize minSize = wxSize(450, 340);
	
    public:
        virtual bool OnInit();
};



enum class systemState
{
	initialStartUp = 0,
	dimensionChoosing = 1,
	problemChooseing = 2,
	problemDefining = 3,
	simulatingProblem = 4,
	viewingResults = 5
};



/*! \class OmniFEMMainFrameAbstraction
	\brief The class representing the abstraction layer for OmniFEM's main frame
	
	More detailed description
*/
class OmniFEMMainFrameAbstraction
{
	
public:
	//! This is the main constructor for the class
	OmniFEMMainFrameAbstraction();
	
	//! This will return the state of OmniFEM
	/*!
		/return The state of OmniFEM
	*/
	systemState getOmniFEMState();

	//! This function will set the state of OmniFEM.
	/*!
		This function will also call an event in order to update the presentation approiately
		/param omniFEMState The state that OmniFEM will be going into.
	*/
	void setOmniFEMState(systemState omniFEMState);
	
	//! Function to get the current problem dimension
	problemDimension getProblemDimension();
	
	//! Function to set the problem dimension
	void setProblemDimension(problemDimension dimension);
	
	/************
	* Variables *
	*************/
private:
	
	//! The state of OmniFEM
	/*!
		This variable holds the current state of OmniFEM
	*/
	systemState omniFEMSystemState = systemState::initialStartUp;
	
	problemDefinition definition;
	
	
};



/*! \class OmniFEMMainFrameController
 *  \brief The class representing the controller layer for OmniFEM's main frame
 * 
 *  This class contains all of the processing calls in order to manage the OmniFEM MainFrame.
 *  
*/
class OmniFEMMainFrameController
{
/* Constructor */
public:
	OmniFEMMainFrameController();
	
	/************
	* Variables *
	*************/
private:
	
	OmniFEMMainFrameAbstraction abstractionLayer;
	
	/**********************
	* Function Prototypes *
	***********************/
public:

	//! This function will update the systemState of OmniFEM in the abstraction layer
	void updateOmniFEMState(systemState omniFEMState);
    
    //! This will get the current state of OmniFEM contained in the abstraction layer
    systemState getOmniFEMState();
	
	//! This function will set the problem dimension in the 
	void setAbstractProblemDim(problemDimension dim);
	
	//! This function will be used to get the problem dimension from the abstraction layer
	problemDimension getAbstractProblemDim();
	
};



/* This class is akin to the global data structure */
class OmniFEMMainFrame : public wxFrame
{
public:
    OmniFEMMainFrame(const wxString &title, const wxPoint &pos, const wxSize &size);
private:
	/***********************************
	* Prototypes for creating the menu *
	************************************/
	
    /* This section is for the File menu */
    void onNewFile(wxCommandEvent &event);
    void OnSave(wxCommandEvent &event);
    void onSaveAs(wxCommandEvent &event);
	void onOpenFile(wxCommandEvent &event);
    
    /* This section is for the Edit menu */
	void onLuaRun(wxCommandEvent &event);
    void onPreferences(wxCommandEvent &event);
	
	/* This section is for the View Menu */
	void onViewResults(wxCommandEvent &event);
	
	/* This section is for the Problem Menu */
	void onPrecision(wxCommandEvent &event);
	
	/* This section is for the Mesh menu */
	void onCreateMesh(wxCommandEvent &event);
	void onShowMesh(wxCommandEvent &event);
	void onDeleteMesh(wxCommandEvent &event);
    
    /* This section is for the Help menu */
	
	//! Event called to view the manual
    void onManual(wxCommandEvent &event);
	
	//! Event called to view the manual
    void onLicense(wxCommandEvent &event);
	
	//! Event called to view the manual
    void OnAbout(wxCommandEvent &event);
    
	//! Event called to view the manual
    void OnExit(wxCommandEvent &event);
	

 	/*****************************
	* Prototypes for client area *
	******************************/   
    
	//! Function that is called to begin the creating a new simulation
	/*
		This will be called in order for the user to choose the dimesnion of the simulation
	*/
    void createDimensionClient();
	
	
	//! Function that is called to create the initial client area
	void createInitialStartup();
	
	
	//! This function is called when the user is ready to choose their physics simulation
	void createProblemChoosingClient();
	
	
	//! This function is called to create the client for defining the physics problem
	/*
		Defining would be creating the geometry, creating the mesh, determining boundary conditions, etc.
	*/
	void createModelDefiningClient();
	
	
	//! This function is called when the user would like to view the results.
	/*
		When the view wants to view results, this function is called in order to create the client frame for viewing
		the results
	*/
	void createResultsViewingClient();
	
	/*************************
	* Prototypes for toolbar *
	**************************/
	
	//! Function called that will create the toolbar for the main frame
	void createTopToolBar();
	
    /*************************
	* Prototypes for buttons *
	**************************/
    
	//! Function called when the user chooses the two dim button
    void onTwoDimButton(wxCommandEvent &event);
	
	//! Function called when the back button is pressed 
	void onBackButton(wxCommandEvent &event);
	
    /********************
	* Prototypes Others *
	*********************/	
	
	//! Event called when a resize event occurs
	void onResize(wxSizeEvent &event);	
	
	//! This is a function that will be for the initial state of Omni-FEM. With items on the toolbar greyed out and menus not accessible
	void initialStartSettings();
	
	/************
	* Variables *
	*************/
	
	int clientSizeWidth, clientSizeLength;
	
	wxMenuBar *menuBar = new wxMenuBar;
    wxMenu *menuFile = new wxMenu;
    wxMenu *menuEdit = new wxMenu;
    wxMenu *menuView = new wxMenu;
    wxMenu *menuMesh = new wxMenu;
    wxMenu *menuProblem = new wxMenu;
    wxMenu *menuHelp = new wxMenu;
	
	wxToolBar *mainFrameToolBar = new wxToolBar();
	
	wxPanel *initialStartPanel = new wxPanel();
	wxPanel *dimSelectPanel;
	wxPanel *problemSelectPanel;
	wxPanel *problemDefiningPanel;
	wxPanel *viewResultsPanel;
	
	wxSize minSize = wxSize(450, 340);
	
	OmniFEMMainFrameController controller;
	
    wxDECLARE_EVENT_TABLE();
};



/* Enum for the menus of the menu bar */
enum menubarID
{
    ID_menubarNew = 1,
    ID_menubarSave = 2,
    ID_menubarSaveAs = 3,
    ID_menubarPreferences = 4,
    ID_menubarManual = 5,
    ID_menubarLicense = 6,
	ID_menubarViewResults = 7,
	ID_menubarCreateMesh = 9,
	ID_menubarShowMesh = 10,
	ID_menubarDeleteMesh = 11,
	ID_menubarPrecision = 12,
	ID_menubarOpen = 13,
	ID_menubarLUASCRIPT = 14,

};


enum toolbarID
{
	ID_ToolBarNew = 1,
	ID_ToolBarOpen = 2,
	ID_ToolBarSave = 3
};


enum buttonID
{
	ID_buttonTwoDim = 1,
	ID_buttonBack = 2,
	ID_buttonNew = 3,
	ID_buttonOpen = 4
	
};














#endif /* OMNIFEM_H_ */
