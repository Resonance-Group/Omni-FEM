#ifndef OMNIFEMFrame_H_
#define OMNIFEMFrame_H_

#include <wx/wx.h>
#include <wx/aboutdlg.h>
#include <wx/stdpaths.h>
#include <string.h>
#include <wx/textctrl.h>
#include <wx/stattext.h>
#include <UI/problemDefinition.h>
#include <wx/listbox.h>
#include <wx/sizer.h>
#include <wx/treectrl.h>
#include <UI/geometryEditor2D.h>
#include <UI/common.h>


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
	
	This will contain all of the data that the presentation will need access to.
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
	
	//! Function used to get the current physics of the problem 
	physicProblems getProblemPhysics();
	
	//! Function used to set the current physics problem
	void setProblemPhysics(physicProblems phy);
	
	//! This function will retrive the border width for the box sizer
	int getBorderWidth();
	
	//! This will retrieve the workspace/solution name
	wxString getworkspaceName();
	
	//! This will set the workspace/solution name
	void setWorkspaceName(wxString name);
	
	//! This will set the main tree ID for the tree control
	void setRootTreeID(wxTreeItemId tree);
	
	//! This will return the main tree ID for the tree control
	/* 
		This is not an actual interger ID but rather the whole class
	*/
	wxTreeItemId getRootTreeID();
	
	//! This will retreive the problem IF from the simuation object
	wxTreeItemId getSimProblemID();
	
	//! This will set the problem IF in the simulation object
	void setSimProblemID(wxTreeItemId problemID);
	
	//! This will set the geometry ID of the simulation object
	void setSimGeometryID(wxTreeItemId geometryID);
	
	//! This will get the geometry ID of the simulation object
	wxTreeItemId getSimGeometryID();
	
	//! This will set the Material ID of the simulation object
	void setSimMaterialsID(wxTreeItemId materialsID);
	
	//! This will get the material ID of the simulation object
	wxTreeItemId getSimMaterialsID();
	
	//! This will set the mesh ID of the simulation object
	void setSimMeshID(wxTreeItemId simMeshID);
	
	//! This will get the mesh ID of the simulation object
	wxTreeItemId getSimMeshID();
	
	//! This will set the simulation name
	void setSimulationName(wxString simName);
	
	//! This will retieve the simulation name
	wxString getSimulationName();
	
	/************
	* Variables *
	*************/
private:
	
	//! The state of OmniFEM
	/*!
		This variable holds the current state of OmniFEM
	*/
	systemState omniFEMSystemState = systemState::initialStartUp;
	
	//! This object is created for each physics problem
	/*!
		This is setting up for future additions where the model tree builder
		will be able to display more then one physics problem per solution.
		Each phyics problem will be it's own object in code
	*/
	problemDefinition definition;
	
	//! This variable stores the border size
	int borderSize = 5;
	
	//! The name of the solution/workspace
	wxString workspaceName = "untitled";
	
	//! This variable is used to store the data for the tree control in the model builder window
	wxTreeItemId rootTree;
};



/*! \class OmniFEMMainFrameController
 *  \brief The class representing the controller layer for OmniFEM's main frame
 * 
 *  This class contains all of the processing calls in order to manage the OmniFEM MainFrame.
 *	This class handles the presentation of the main frame for Omni-FEM and is thus one of the largest objects in the whole program
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
	
	//! This function will get the physics problem in the abstraction
	physicProblems getAbstractProblemPhysics();
	
	//! This function will set the phycis problem in the abstraction
	void setAbstractProblemPhysics(physicProblems phy);
	
	//! This function will retrieve the border size of the boxSizer.
	int getBorderSize();
	
	//! This will get the workspace/solution name from the abstraction layer
	wxString getWorkspaceNameAbstraction();
	
	//! This will set the workspace name in the abstraction layer
	void setWorkspaceNameAbstraction(wxString name);
	
	//! This will set the root tree ID object in the abstraction layer
	void setRootTreeIDAbstraction(wxTreeItemId tree);
	
	//! This will get the root tree ID object from the abstraction layer
	wxTreeItemId getRootTreeIDAbstraction();
	
	//! This will retreive the problem ID from the abstraction layer
	wxTreeItemId getAbstractProblemID();
	
	//! This will set the problem IF in the simulation object
	void setAbstractProblemID(wxTreeItemId problemID);
	
	//! This will set the geometry ID of the simulation object
	void setAbstractGeometryID(wxTreeItemId geometryID);
	
	//! This will get the geometry ID of the simulation object
	wxTreeItemId getAbstractGeometryID();
	
	//! This will set the Material ID of the simulation object
	void setAbstractMaterialsID(wxTreeItemId materialsID);
	
	//! This will get the material ID of the simulation object
	wxTreeItemId getAbstractMaterialsID();
	
	//! This will set the mesh ID of the simulation object
	void setAbstractMeshID(wxTreeItemId simMeshID);
	
	//! This will get the mesh ID of the simulation object
	wxTreeItemId getAbstractMeshID();

	//! This will retrieve the simulation name from the abstract layer
	wxString getAbstractSimName();
	
	//! This will set the simulation name in the abstraction layer
	void setAbstractSimName(wxString name);
	
};



/*! \class OmniFEMMainFrame
 *  \brief The main class for everything
 * 
 *  This class is also the presentation layer of the main frame
 */
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
	void createInitialStartupClient();
	
	
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
	
	void onFinishButton(wxCommandEvent &event);
	
    /********************
	* Prototypes Others *
	*********************/	
	
	//! Event called when a resize event occurs
	void onResize(wxSizeEvent &event);	
	
	//! This is a function that will be for the initial state of Omni-FEM. With items on the toolbar greyed out and menus not accessible
	void enableToolMenuBar(bool enable);
	
	//! This is the function that is called when the combox box is clicked for choosing a physics problem
	void physicsProblemComboBox(wxCommandEvent &event);
	
	/************
	* Variables *
	*************/
	
	//! Stores the client size of the main window in the x direction
	int clientSizeWidth;
	
	//! Stores the client size of the main window in the y direction
	int clientSizeLength;
	
	//! The menu bar for the main window
	wxMenuBar *menuBar = new wxMenuBar;
	
	wxBoxSizer *groupOneSizer = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer *vertBoxSizer = new wxBoxSizer(wxVERTICAL);
	
	//! This would be the file menu in the menu bar
    wxMenu *menuFile = new wxMenu;
	
	//! This would be the edit menu in the menu bar
    wxMenu *menuEdit = new wxMenu;
	
	//! This would be the view menu in the menu bar
    wxMenu *menuView = new wxMenu;
	
	//! This would be the mesh menu in the menu bar
    wxMenu *menuMesh = new wxMenu;
	
	//! This would be the problem menu in the menu bar
    wxMenu *menuProblem = new wxMenu;
	
	//! This would be the help menu in the menu bar
    wxMenu *menuHelp = new wxMenu;
	
	//! This is the object for the toolbar of the main window
	wxToolBar *mainFrameToolBar = new wxToolBar();
	
	//! Creates the panel for the first screen
	wxPanel *initialStartPanel = new wxPanel();
	
	//! Panel for selecting the dimension
	wxPanel *dimSelectPanel;
	
	//! Panel for selecting the physics problem
	wxPanel *problemSelectPanel;
	
	//! This panel will be used in the model builder window. The purpose is to display status messages
	wxPanel *statusInfoPanel;
	
	//! This panel will be used in the problem defining state
	/*
		This object will be a list listing commonly acessed parameters. Such as listing
		the materials used, the geometry along with the different simualtions associated with teh project
	*/
	wxPanel *modelBuilderTreePanel;
	
	//! This panel will be used to draw the geometry on 
	wxPanel *geometryBuilderPanel;
	
	//! This panel will be used to dispaly settings that are selected
	wxPanel *settingsPanel;
	
	wxPanel *viewResultsPanel;
	
	//! Sets the mininimum size that the window for OMni-FEM is allowed to have
	wxSize minSize = wxSize(450, 340);
	
	//! The string of the physics problems that Omni-FEM can simulate
	wxArrayString arrayPhysicsProblem;
	
	
	OmniFEMMainFrameController controller;
	
	wxTreeCtrl *modelbuilderTreeCtrl;
	
	geometryEditor2DPresentation *twoDimGeometryEditor;
	
    wxDECLARE_EVENT_TABLE();
};












#endif /* OMNIFEM_H_ */
