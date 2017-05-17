#ifndef OMNIFEMFrame_H_
#define OMNIFEMFrame_H_

#include <string.h>
#include <algorithm>

#include <wx/wx.h>
#include <wx/aboutdlg.h>
#include <wx/stdpaths.h>
#include <wx/listbox.h>
#include <wx/sizer.h>
#include <wx/treectrl.h>

#include <UI/GeometryEditor2D.h>
#include <UI/common.h>

#include <UI/MaterialsDialog/MaterialDialog.h>
#include <UI/MaterialsDialog/MaterialsLibrary.h>
#include <UI/BoundaryDialog/BoundaryDialog.h>
#include <UI/NodalProperty/PropertyDialog.h>
#include <UI/ConductorsDialog/ConductorPropSetDialog.h>

#include <UI/PreferencesDialog.h>
#include <UI/ExteriorRegion.h>

#include <UI/EditMenu/MoveCopyDialog.h>
#include <UI/EditMenu/ScalingDialog.h>
#include <UI/EditMenu/MirrorDialog.h>
#include <UI/EditMenu/OpenBoundaryDialog.h>
#include <UI/EditMenu/GlobalPreferencesDialog.h>
#include <UI/EditMenu/SelectGroupDialog.h>

#include <UI/ViewMenu/ZoomWindow.h>
#include <UI/ViewMenu/LuaConsole.h>

#include <UI/GridPreferencesDialog.h>

#include <UI/ModelDefinition/ModelDefinition.h>

#include <common/enums.h>



// For documenting code, see: https://www.stack.nl/~dimitri/doxygen/manual/docblocks.html

//! This is the base class of the application
/*!
    This is the class that is first called in order to start the 
    application running. Without this class, Omni-FEM would not be able to run at all.
    The class derives from the wxApp class since this is required by wxwidgets for
    proper functionality.
    For documentation regarding wxApp class, refer to the following link:
    http://docs.wxwidgets.org/3.1.0/classwx_app.html
*/ 
class OmniFEMApp : public wxApp
{	
public:
    //! Function that is called to start Omni-FEM
    virtual bool OnInit();
};



//! This is the main class for Omni-FEM.
/*!
    This class handles all of UI drawing for what the user sees.
    The class will route any event procedures to their proper function 
    when the user clicks on an icon.
    The class derives from the wxFrame as this is the most base class for a frame
    thus giving the class the most flexability in terms of usage
    For additional documentation on the wxFrame class, refer to the following link:
    http://docs.wxwidgets.org/trunk/classwx_frame.html
*/
class OmniFEMMainFrame : public wxFrame
{
public:
    
    //! The constructor for the class
    /*!
        It is in the constructor where Omni-FEM sets up the fame that will
        display the menu items. In the constructor, the program creates all
        of the toolbars that the user will see along with the first frame that
        appears to the user
        \param title The title of the frame
        \param pos The starting position of the frame
    */ 
    OmniFEMMainFrame(const wxString &title, const wxPoint &pos);
private:

    /************
	* Variables *
	*************/
    
	//! The glCanvas that is created in order for the user to draw their geomtry
    /*!
        This is the object that is used on the frame in order to allow the user to draw the
        geometry. The model is the 2D model that the user will be able to create by creating 
        nodes and connecting the node together by arcs or lines. The user can also create block labels
        The user can create lines or block labels and arcs or lines. The ability to switch between the
        creation of these is toggled by the onToggleNodeCreation and onToggleLineCreation functions
        which is called when the user clicks on the node and line icon.
    */ 
    modelDefinition *_model;
    
    //! This is the global definiton for the problem
    /*!
        In this object, the program stores all of the lists for the materials,
        boundary conitions, conductor properties, what physics problems, etc.
        An address to this object must be passed into the modelDefiniton object
        becuase the modelDefinition object must be able to see the different preferences
        that the user is setting and have access to these such as the boundary conditions 
        and the materials
    */ 
    problemDefinition _problemDefinition;
    
    //! Boolean used to indicate if the user would like to display the status menu
    bool _displayStatusMenu = true;
	
	//! The menu bar for the main window
	wxMenuBar *_menuBar = new wxMenuBar;
	
	//! This would be the file menu in the menu bar
    wxMenu *_menuFile = new wxMenu;
	
	//! This would be the edit menu in the menu bar
    wxMenu *_menuEdit = new wxMenu;
	
	//! This would be the view menu in the menu bar
    wxMenu *_menuView = new wxMenu;
	
	//! This would be the problem menu in the menu bar
    wxMenu *_menuProblem = new wxMenu;
	
    //! The Grid menu in the menu bar
    wxMenu *_menuGrid = new wxMenu;
    
    //! The properties menu in the menu bar
    wxMenu *_menuProperties = new wxMenu;
    
    //! This would be the mesh menu in the menu bar
    wxMenu *_menuMesh = new wxMenu;
    
    //! This is the menu entry for hte analsis
    wxMenu *_analysisMenu = new wxMenu;
    
	//! This would be the help menu in the menu bar
    wxMenu *_menuHelp = new wxMenu;
    
    wxListBox *_physicsProblemsListBox;
    
    systemState _UIState = systemState::ON_START_UP_STATE;


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
    void onCopy(wxCommandEvent &event);
    void onScale(wxCommandEvent &event);
    void onMirror(wxCommandEvent &event);
    void onUndo(wxCommandEvent &event);
    void onDelete(wxCommandEvent &event);
    void onMove(wxCommandEvent &event);
    void onCreateRadius(wxCommandEvent &event);
    void onCreateOpenBoundary(wxCommandEvent &event);
    void onSelectGroup(wxCommandEvent &event);
    void onEditProperty(wxCommandEvent &event);
	
	/* This section is for the View Menu */
    void onZoomIn(wxCommandEvent &event);
    void onZoomOut(wxCommandEvent &event);
    void onZoomWindow(wxCommandEvent &event);
    void onBlockName(wxCommandEvent &event);
    void onOrphans(wxCommandEvent &event);
    void onStatusBar(wxCommandEvent &event);
    void onLua(wxCommandEvent &event);
    
    /* This section is for the Problem Menu */
    void onProblemPreferences(wxCommandEvent &event);
	
    /* This section is for the Grid Menu */
    void onDispGrid(wxCommandEvent &event);
    void onSnapGrid(wxCommandEvent &event);
    void onSetGridPreferences(wxCommandEvent &event);
    
    /* Thos section is for the Properties Menu */
    void onMaterials(wxCommandEvent &event);
    void onBoundary(wxCommandEvent &event);
    void onPointProperty(wxCommandEvent &event);
    void onCircuitsConductor(wxCommandEvent &event);
    void onExteriorRegion(wxCommandEvent &event);
    void onMatLibrary(wxCommandEvent &event);
    
	/* This section is for the Mesh menu */
	void onCreateMesh(wxCommandEvent &event);
	void onShowMesh(wxCommandEvent &event);
	void onDeleteMesh(wxCommandEvent &event);
    
    /* This section is for the Analysis menu */
    void onAnalyze(wxCommandEvent &event);
    void onViewResults(wxCommandEvent &event);
    
	//! Event called to view the manual
    void onManual(wxCommandEvent &event);
	
	//! Event called to view the manual
    void onLicense(wxCommandEvent &event);
	
	//! Event called to view the manual
    void OnAbout(wxCommandEvent &event);
    
	//! Event called to view the manual
    void OnExit(wxCommandEvent &event);
    
    //! Event that is called when the user wants to toggle between node and block label creation
    void onToggleNodeCreation(wxCommandEvent &event)
    {
        if(_UIState == systemState::MODEL_DEFINING)
        {
            _model->setCreateNodeState(!_model->getCreateNodeState());
        }
    }
    
    //! Event that is called when the user wants to toggle between line and arc label creation
    void onToggleLineCreation(wxCommandEvent &event)
    {
        if(_UIState == systemState::MODEL_DEFINING)
        {
            _model->setCreateLinesState(!_model->getCreateLineState());
        }
    }
    
    void onSolveProblem(wxCommandEvent &event)
    {
        return;
    }
	
    void onDisplayResults(wxCommandEvent &event)
    {
        return;
    }
    
    void onGLCanvasMouseMove(wxCommandEvent &event);

 	/*****************************
	* Prototypes for client area *
	******************************/   
	
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

    wxDECLARE_EVENT_TABLE();
};












#endif /* OMNIFEM_H_ */
