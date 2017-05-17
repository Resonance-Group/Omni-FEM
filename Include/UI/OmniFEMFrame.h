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
    /*!
        The menu bar is kind of like a container where it contains all of the listings of the different
        wxMenu classes. 
        For additional documentation on the wxMenuBar class, refer to the following link:
        http://docs.wxwidgets.org/3.1.0/classwx_menu_bar.html
    */ 
	wxMenuBar *_menuBar = new wxMenuBar;
	
	//! The file selection for the menu bar
    /*!
        For additional documentation on the wxMenu class, refer to the following link:
        http://docs.wxwidgets.org/trunk/classwx_menu.html
    */ 
    wxMenu *_menuFile = new wxMenu;
	
	//! The edit menu for the menu bar
    /*!
        For additional documentation on the wxMenu class, refer to the following link:
        http://docs.wxwidgets.org/trunk/classwx_menu.html
    */ 
    wxMenu *_menuEdit = new wxMenu;
	
	//! The view menu for the menu bar
    /*!
        For additional documentation on the wxMenu class, refer to the following link:
        http://docs.wxwidgets.org/trunk/classwx_menu.html
    */ 
    wxMenu *_menuView = new wxMenu;
	
	//! The problem menu for the menu bar
    /*!
        For additional documentation on the wxMenu class, refer to the following link:
        http://docs.wxwidgets.org/trunk/classwx_menu.html
    */ 
    wxMenu *_menuProblem = new wxMenu;
	
    //! The grid menu for the menu bar
    /*!
        For additional documentation on the wxMenu class, refer to the following link:
        http://docs.wxwidgets.org/trunk/classwx_menu.html
    */ 
    wxMenu *_menuGrid = new wxMenu;
    
    //! The properties menu for the menu bar
    /*!
        For additional documentation on the wxMenu class, refer to the following link:
        http://docs.wxwidgets.org/trunk/classwx_menu.html
    */ 
    wxMenu *_menuProperties = new wxMenu;
    
    //! The mesh menu for the menu bar
    /*!
        For additional documentation on the wxMenu class, refer to the following link:
        http://docs.wxwidgets.org/trunk/classwx_menu.html
    */ 
    wxMenu *_menuMesh = new wxMenu;
    
    //! The analysis menu for the menu bar
    /*!
        For additional documentation on the wxMenu class, refer to the following link:
        http://docs.wxwidgets.org/trunk/classwx_menu.html
    */ 
    wxMenu *_analysisMenu = new wxMenu;
    
	//! The help menu for the menu bar
    /*!
        For additional documentation on the wxMenu class, refer to the following link:
        http://docs.wxwidgets.org/trunk/classwx_menu.html
    */ 
    wxMenu *_menuHelp = new wxMenu;
    
    //! The list box that contains the selection of the different physics problems
    /*!
        This object is used to display the selection of the different physics problems
        that the user is able to choose from. This Once choosen, the selection will be 
        converted into physics problem enum which is used to determine which dialog to
        show depending on the physics selection.
        For additional documentation on the wxListBox object, refer to the following link:
        http://docs.wxwidgets.org/trunk/classwx_list_box.html
    */ 
    wxListBox *_physicsProblemsListBox;
    
    //! Variable that is used to indicate which state the UI is in.
    /*! 
        This variable is used through the OmniFEMMainFrame class. 
        The variable indicates what state the UI is in which will dictate what
        widgets are drawn on the frame and will dictate what widgets are 
        deleted on the frame when the user moves between UI states
    */ 
    systemState _UIState = systemState::ON_START_UP_STATE;


	/***********************************
	* Prototypes for creating the menu *
	************************************/
	
    /* This section is for the File menu */
    
    //! Event procedure for the new file event
    /*!
        This event is thrown every time the user clicks on 
        File->New or when the user clicks on the new file icon
        in the tool bar. This event is also filed on the start up menu
        when the user can choose from either creating a new simulation
        or opening an exisitng simulation
        For additional documentation on the wxCommandEvent object, refer
        to the following link:
        http://docs.wxwidgets.org/3.0/classwx_command_event.html
        \param event A required parameter for the event procedure to work properly
    */ 
    void onNewFile(wxCommandEvent &event);
    
    //! Event procedure for the save event
    /*!
        This event is fired everytime the user goes to
        file->Save, clicks onthe save icon on the toolbar, 
        or presses the key combination Ctrl+s. This will automatically
        save the file to the current directory that the file is located in.
        If the file does not exist, then this function will
        call the save as function in order to allow the user to 
        select the location to save the file at
        For additional documentation on the wxCommandEvent object, refer
        to the following link:
        http://docs.wxwidgets.org/3.0/classwx_command_event.html
        \param event A required parameter for the event procedure to work properly
    */ 
    void OnSave(wxCommandEvent &event);
    
    //! Event procedure for the Save As event
    /*!
        This event is fired every time that the user
        goes to File->SaveAs. This function will bring up a dialog
        box giving the user the ability to choose the location where
        they would like to save their simulation as
        For additional documentation on the wxCommandEvent object, refer
        to the following link:
        http://docs.wxwidgets.org/3.0/classwx_command_event.html
        \param event A required parameter for the event procedure to work properly
    */ 
    void onSaveAs(wxCommandEvent &event);
    
    //! Event procedure for the Open File event
    /*!
        This event is fired every time the user clicks on File->Open or
        the Open file icon in the tool bar or when the
        user chooses to open a new simulation on the startup screen
        The function will bring up a dialog box asking the user
        for the location of the file.
        For additional documentation on the wxCommandEvent object, refer
        to the following link:
        http://docs.wxwidgets.org/3.0/classwx_command_event.html
        \param event A required parameter for the event procedure to work properly
    */ 
	void onOpenFile(wxCommandEvent &event);
    
    /* This section is for the Edit menu */
    
    //! Event procedure that is fired when the user needs to run a lua script
    /*!
        This event is executed when the the user clicks on Edit->Lua Run. This 
        function will open a dialog box in order to allow the user to choose 
        the location of the lua script.
        For additional documentation on the wxCommandEvent object, refer
        to the following link:
        http://docs.wxwidgets.org/3.0/classwx_command_event.html
        \param event A required parameter for the event procedure to work properly
    */ 
	void onLuaRun(wxCommandEvent &event);
    
    //! Event procedure that is fired in order to bring up the system preferences menu
    /*!
        This event is fired when the user clicks on Edit->Preferences or when the user
        presses the key combination Ctrl+P. This function will display the system preferences
        menu which will allow the user to edit all settings within the simulator
        envirnoment
        For additional documentation on the wxCommandEvent object, refer
        to the following link:
        http://docs.wxwidgets.org/3.0/classwx_command_event.html
        \param event A required parameter for the event procedure to work properly
    */ 
    void onPreferences(wxCommandEvent &event);
    
    //! Event procedure that is fired when the user would like to copy any selected geometries
    /*!
        This event is fired every time that the user clicks on Edit->Copy, clicks on the 
        copy icon, or presses the keyboard combination Ctrl+C. This function
        will bring up the copy dialog where the user needs to enter parameters about 
        copying the geometry.
        For additional documentation on the wxCommandEvent object, refer
        to the following link:
        http://docs.wxwidgets.org/3.0/classwx_command_event.html
        \param event A required parameter for the event procedure to work properly
    */ 
    void onCopy(wxCommandEvent &event);
    
    //! Procedure that is fired when the user would like to scale the geometry
    /*!
        This event is fired every time the user clicks on Edit->Scale or when the user clicks on the Scale icon.
        This function will bring up the scale dialog. However, before the scale dialog is displayed,
        the program will calculate the center of the selected geometry and place this center into 
        the base point of the scale dialog. The user has the option of using that center
        or to specifya new center.
        For additional documentation on the wxCommandEvent object, refer
        to the following link:
        http://docs.wxwidgets.org/3.0/classwx_command_event.html
        \param event A required parameter for the event procedure to work properly
    */ 
    void onScale(wxCommandEvent &event);
    
    //! Event procedure that is fired when the user needs to mirror selected geometry
    /*!
        This event is fired each time the user clicks on Edit->Mirror. This will place
        the canvas into mirror selection state where the user needs to draw a mirror on 
        the canvas in order to indicate how they would like to mirror the geometry. Once
        drawn, the program will calculate all neccessary parameters in order to 
        mirror the geometry.
        For additional documentation on the wxCommandEvent object, refer
        to the following link:
        http://docs.wxwidgets.org/3.0/classwx_command_event.html
        \param event A required parameter for the event procedure to work properly
    */ 
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
