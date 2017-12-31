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
#include <wx/filefn.h> 

#include <UI/GeometryEditor2D.h>
#include <UI/common.h>

#include <UI/MaterialsDialog/MaterialDialog.h>
#include <UI/MaterialsDialog/MaterialsLibrary.h>
#include <UI/BoundaryDialog/BoundaryDialog.h>
#include <UI/NodalProperty/PropertyDialog.h>
#include <UI/ConductorsDialog/ConductorPropSetDialog.h>

#include <UI/PreferencesDialog.h>
#include <UI/ExteriorRegion.h>
#include <UI/AddNodeDialog.h>

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
#include "common/OmniFEMMessage.h"
#include <common/ProblemDefinition.h>


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
	
	~OmniFEMMainFrame()
	{
		delete OmniFEMMsg::instance();
	}
private:

    /************
	* Variables *
	*************/
	
	//! A local copy of the path file for the saved file
	/*!
		This is primarly used during a saved event. For a saved as event,
		the contents are replaced by what the user choose in the dialog
	*/ 
	string _saveFilePath = "";
    
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
        This variable is used through out the OmniFEMMainFrame class. 
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
        file->Save, clicks on the save icon on the toolbar, 
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
    
    //! Event procedure that is exeucted when the user needs to quite the program.
    /*!
        This function is executed when the user clicks on File->Quit.
        This will exit out of the program and stop all processes.
        For additional documentation on the wxCommandEvent object, refer
        to the following link:
        http://docs.wxwidgets.org/3.0/classwx_command_event.html
        \param event A required parameter for the event procedure to work properly
    */ 
    void OnExit(wxCommandEvent &event);
    
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
    
    //! Event procedure that is fired when the user needs to undo their last action
    /*!
        This function currently doesn't do anything. But this
        function would undo the users last action. More
        documentation will come as the function is coded more
        For additional documentation on the wxCommandEvent object, refer
        to the following link:
        http://docs.wxwidgets.org/3.0/classwx_command_event.html
        \param event A required parameter for the event procedure to work properly
    */ 
    void onUndo(wxCommandEvent &event);
    
    //! The event that is fired when the user needs to delete selected geometry
    /*!
        This event is fired each time the user clicks on Edit->Delete, on the 
        delete icon, or when the delete key is pressed on the keyboard. This function will
        delete any selected geometry and remove it from the list.
        For additional documentation on the wxCommandEvent object, refer
        to the following link:
        http://docs.wxwidgets.org/3.0/classwx_command_event.html
        \param event A required parameter for the event procedure to work properly
    */ 
    void onDelete(wxCommandEvent &event);
	
	//! 
	/**
	 * @brief 	Event that is fired when the user needs to add a node manually. A dialog will appear
	 * 			prompting the user to set the x and y values of the node. If the user clicks ok,
	 * 			then the node will be added. If Cancel is clicked, the node will not be added
	 * @param event Required parameter for proper event procedure to work
	 */
	void onAddNode(wxCommandEvent &event)
	{
		addNodeDialog *nodeDialog = new addNodeDialog(this);
		
		if(nodeDialog->ShowModal() == wxID_OK)
		{
			wxRealPoint nodePoint = nodeDialog->getPoint();
			
			_model->addNodePoint(nodePoint);
			_model->Refresh();
		}
		
		delete nodeDialog;
	}
    
    //! Event procedure that is fired when the user needs to move the geometry
    /*!
        This event is fired when the user clicks on Edit->Move or
        clicks on the move icon in the toolbar. This function will
        call the apprioate function in the modelDefinition object 
        in order to move any selected geometry.This function
        will create the move geometry dialog box which will give the 
        user the option to move the geometry about a point or
        to translate the geometry.
        For additional documentation on the wxCommandEvent object, refer
        to the following link:
        http://docs.wxwidgets.org/3.0/classwx_command_event.html
        \param event A required parameter for the event procedure to work properly
    */ 
    void onMove(wxCommandEvent &event);
    
    //! Event procedure that is fired when the user needs to create a fillet
    /*!
        This event is fired when the user clicks on Edit->Create Fillet from
        the toolbar. This fucntion will create a dialog box allowing the user to 
        input their desired radius for the fillet. Once the user presses
        ok, the function will call the apprioate function in the modelDefinition
        class in order to create the fillet. If for any reason the program is unable
        to create the fillet, then the UI will not be updated and the selected node(s)
        will be uneffected.
        For additional documentation on the wxCommandEvent object, refer
        to the following link:
        http://docs.wxwidgets.org/3.0/classwx_command_event.html
        \param event A required parameter for the event procedure to work properly
     */ 
    void onCreateRadius(wxCommandEvent &event);
    
    //! Event procedure that is fired when the user needs to create an open boundary
    /*! 
        This event is fired when the user clicks on Edit->Create Open Boundary 
        in the toolbar. This function will create the Open Boundary dialog box
        allowing the user to input the number of layers, the radius, and the
        center position and the boundary type. Once selected, the program 
        will create concentric circles with the correct number of layers, 
        material block labels at the desired radius
        For additional documentation on the wxCommandEvent object, refer
        to the following link:
        http://docs.wxwidgets.org/3.0/classwx_command_event.html
        \param event A required parameter for the event procedure to work properly
    */ 
    void onCreateOpenBoundary(wxCommandEvent &event);
    
    //! This event is fired when the user needs to select a group of geometry
    /*!
        THis event is fired when the user clicks on Edit->Select Group from the toolbar
        or when the user presses Ctrl+A. This function will create the select group dialog
        allowing the user to select specific geometry groups (nodes/lines/arcs/block labels) 
        or all of the geometry that corresponds to a particular group number
        For additional documentation on the wxCommandEvent object, refer
        to the following link:
        http://docs.wxwidgets.org/3.0/classwx_command_event.html
        \param event A required parameter for the event procedure to work properly
    */ 
    void onSelectGroup(wxCommandEvent &event);
    
    //! This event is fired when the user needs to edit the properties of any selected geometry
    /*!
        This event is fired when the user clicks on Edit->Edit Property, selects the 
        Edit Property icon in the toolbar, or when the user presse the key combination Ctrl+E.
        This function will bring up the apprioate dialog box to edit the property of
        any selected geometry. If mixed geometry is selected, then the dialog box that appears
        is for changing the group number
        For additional documentation on the wxCommandEvent object, refer
        to the following link:
        http://docs.wxwidgets.org/3.0/classwx_command_event.html
        \param event A required parameter for the event procedure to work properly
    */ 
    void onEditProperty(wxCommandEvent &event);
	
	/* This section is for the View Menu */
    //! Event procedure that is fired when the user needs to zoom in on the model canvas
    /*!
        This event is fired when the user clicks on Edit->Zoom In on the menu or when
        the user clicks on the zoom in icon in the toolbar. This will cause the canvas to zoom in
        by a fixed amount
        For additional documentation on the wxCommandEvent object, refer
        to the following link:
        http://docs.wxwidgets.org/3.0/classwx_command_event.html
        \param event A required parameter for the event procedure to work properly
    */ 
    void onZoomIn(wxCommandEvent &event);
    
    //! Event procedure that is fired when the user needs to zoom out on the model canvas
    /*!
        This event is fired when the user clicks on Edit->Zoom Out on the menu or when
        the user clicks on the zoom out icon in the toolbar. This will cause the canvas to zoom out
        by a fixed amount
        For additional documentation on the wxCommandEvent object, refer
        to the following link:
        http://docs.wxwidgets.org/3.0/classwx_command_event.html
        \param event A required parameter for the event procedure to work properly
    */ 
    void onZoomOut(wxCommandEvent &event);
    
    //! Event procedure that is fired when the user wants to zoom in on a specific area
    /*!
        This function will place the modelDefinition into the zoom window state which will
        allow the user to draw a box around the area that they would like to zoom in on.
        For additional documentation on the wxCommandEvent object, refer
        to the following link:
        http://docs.wxwidgets.org/3.0/classwx_command_event.html
        \param event A required parameter for the event procedure to work properly
    */ 
    void onZoomWindow(wxCommandEvent &event);
    
    //! Event procedure that is fired when the user toggles the Show Block Name option in the View menubar.
    /*!
        This function will toggle the display of the block names by setting toggleing
        the value in the modelDefinition class.
        For additional documentation on the wxCommandEvent object, refer
        to the following link:
        http://docs.wxwidgets.org/3.0/classwx_command_event.html
        \param event A required parameter for the event procedure to work properly
    */ 
    void onBlockName(wxCommandEvent &event);
    
    //! Event procedure that is fired when the user needs to see any Open Boundaries
    /*!
        Although this says orphans, this function will cause the modelDefinition class
        to select any nodes that are Open Boundaries. 
        A node is considered an open boundary if there is only one line or one arc
        connected to the node. This function is exeucted each time the user 
        clicks on View->Show Open Boundaries
        For additional documentation on the wxCommandEvent object, refer
        to the following link:
        http://docs.wxwidgets.org/3.0/classwx_command_event.html
        \param event A required parameter for the event procedure to work properly
    */ 
    void onOrphans(wxCommandEvent &event);
    
    //! Event Procedure that is fired when the user would like to toggle the display of hte status bar
    /*!
        This functoin is executed each time the user clicks on View->Status Bar. The function
        uses the state of the check mark in the menu bar to determine if there should be a 
        status bar displayed. If the status bar is displayed, then there will be a check mark.
        Otherwise, there will be no check mark.
        For additional documentation on the wxCommandEvent object, refer
        to the following link:
        http://docs.wxwidgets.org/3.0/classwx_command_event.html
        \param event A required parameter for the event procedure to work properly 
    */ 
    void onStatusBar(wxCommandEvent &event);
    
    //! Event procedure that is fired when the user needs to bring up the Lua console
    /*!
        The lua console is an in-house lua editor that can execute lua functions.
        This function will create and display the lua console for the user to utilize
        For additional documentation on the wxCommandEvent object, refer
        to the following link:
        http://docs.wxwidgets.org/3.0/classwx_command_event.html
        \param event A required parameter for the event procedure to work properly
    */ 
    void onLua(wxCommandEvent &event);
    
    /* This section is for the Problem Menu */
    
    //! Event procedure that is fired when the user needs to change the problem preferences for the simulation
    /*!
        This function is exeucted when the user clicks on Problem->Problem Preferences.
        This function will create the problem definition dialog box which will allow the user
        to change any preferences related to the physics problem. This includes 
        the problem type, lenght units, depth, solver precision, and min angle.
        For additional documentation on the wxCommandEvent object, refer
        to the following link:
        http://docs.wxwidgets.org/3.0/classwx_command_event.html
        \param event A required parameter for the event procedure to work properly
    */ 
    void onProblemPreferences(wxCommandEvent &event);
    
    //! Event procedure that is fired when the user is ready to solve the simulation
    /*!
        This function is exeucted when the user clicks on Problem->Solve or the solve icon in the toolbar.
        This function is currently a work in progress. THis function will begin the dealII solver
        to solve the physics problem.
        For additional documentation on the wxCommandEvent object, refer
        to the following link:
        http://docs.wxwidgets.org/3.0/classwx_command_event.html
        \param event A required parameter for the event procedure to work properly
    */ 
    void onSolveProblem(wxCommandEvent &event)
    {
		if(wxFileExists(_problemDefinition.getSaveFilePath() + "/" + _problemDefinition.getName() + ".msh"))
		{
			wxMessageBox("Running simulation", "Info");
		}
		else
			wxMessageBox("No mesh file created. Mesh the geometry first before simulation", "Warning", wxICON_EXCLAMATION | wxOK);
    }
	
    /* This section is for the Grid Menu */
    
    //! Event procedure that is fired each time the user clicks on Grid->Display Grid.
    /*!
        This function will set the display grid boolean to the value, located in the grid preferences object in the modelDefintion, of the display grid menubar option.
        This option is a boolean meaning that if there is a check, then the program will display the grid 
        since a check means true. Otherwise, the program will not display the grid.
        For additional documentation on the wxCommandEvent object, refer
        to the following link:
        http://docs.wxwidgets.org/3.0/classwx_command_event.html
        \param event A required parameter for the event procedure to work properly
    */ 
    void onDispGrid(wxCommandEvent &event);
    
    //! Event procedure that is fired each time the user clicks on Grid->Snap Grid.
    /*!
        This function will set the snap grid boolean to the value, located in the grid preferences object in the modelDefintion, of the snap grid menubar option.
        This option is a boolean meaning that if there is a check, then the program will snap any blcok labels or nodes (or selection windows or mirror lines) to the grid 
        since a check means true. Otherwise, the program will not snap to the grid.
        For additional documentation on the wxCommandEvent object, refer
        to the following link:
        http://docs.wxwidgets.org/3.0/classwx_command_event.html
        \param event A required parameter for the event procedure to work properly
    */ 
    void onSnapGrid(wxCommandEvent &event);
    
    //! Event procedure that is fired when the user needs to change any grid preferences.
    /*!
        This fucntion will create the Grid Preferences dialog which will allow the user to set grid preferences such
        as displaying the grid, displaying the origin, displaying grid axis, etc. This function will get the current
        values for the grid preferences and load these values into the dialog. If the user changes any of the values,
        the program will save these new values into the modelDefintion class. For Show grid, Snap Grid, and Show Block Names,
        the program will check/uncheck the apprioate menu bar option if the value has changed.
        For additional documentation on the wxCommandEvent object, refer
        to the following link:
        http://docs.wxwidgets.org/3.0/classwx_command_event.html
        \param event A required parameter for the event procedure to work properly
    */ 
    void onSetGridPreferences(wxCommandEvent &event);
    
    /* Thos section is for the Properties Menu */
    
    //! Event procedure that is fired when the user needs to edit the material list
    /*! 
        This function is executed when the user clicks on Properties->Materials or presses
        the key combination Ctrl+M. The function will bring up the Material Definition dialog
        box allowing the user to edit the material list. If the user clicks on ok,
        then the program will set the material list found in the problemDefinition object 
        and update any geometry containing the material.
        For additional documentation on the wxCommandEvent object, refer
        to the following link:
        http://docs.wxwidgets.org/3.0/classwx_command_event.html
        \param event A required parameter for the event procedure to work properly
    */ 
    void onMaterials(wxCommandEvent &event);
    
    //! Event procedure that is fired when the user needs to edit the boundary list
    /*! 
        This function is executed when the user clicks on Properties->Boundary Condition or presses
        the key combination Ctrl+B. The function will bring up the Boundary Definition dialog
        box allowing the user to edit the boundary list. If the user clicks on ok,
        then the program will set the boundary list found in the problemDefinition object 
        and update any geometry containing the boundary.
        For additional documentation on the wxCommandEvent object, refer
        to the following link:
        http://docs.wxwidgets.org/3.0/classwx_command_event.html
        \param event A required parameter for the event procedure to work properly
    */ 
    void onBoundary(wxCommandEvent &event);
    
    //! Event procedure that is fired when the user needs to edit the nodal list
    /*! 
        This function is executed when the user clicks on Properties->Nodal Properties
        The function will bring up the Nodal Definition dialog
        box allowing the user to edit the nodal list. If the user clicks on ok,
        then the program will set the nodal list found in the problemDefinition object 
        and update any geometry containing the nodal.
        For additional documentation on the wxCommandEvent object, refer
        to the following link:
        http://docs.wxwidgets.org/3.0/classwx_command_event.html
        \param event A required parameter for the event procedure to work properly
    */ 
    void onPointProperty(wxCommandEvent &event);
    
    //! Event procedure that is fired when the user needs to edit the conductor list
    /*! 
        This function is executed when the user clicks on Properties->Conductors
        The function will bring up the Conductor Definition dialog
        box allowing the user to edit the conductor list. If the user clicks on ok,
        then the program will set the conductor list found in the problemDefinition object 
        and update any geometry containing the conductor.
        For additional documentation on the wxCommandEvent object, refer
        to the following link:
        http://docs.wxwidgets.org/3.0/classwx_command_event.html
        \param event A required parameter for the event procedure to work properly
    */
    void onCircuitsConductor(wxCommandEvent &event);
    
    //! Event procedure that is fired when the user needs to edit the exterior region
    /*! 
        This function is executed when the user clicks on Properties->Exterior Region.
        The function will bring up the Exterior Region dialog
        box allowing the user to edit the exterior region. Please
        note that by default, this option is greyed out and will
        only be avaiable if the probem type is set to Axisymmetric.
        For additional documentation on the wxCommandEvent object, refer
        to the following link:
        http://docs.wxwidgets.org/3.0/classwx_command_event.html
        \param event A required parameter for the event procedure to work properly
    */
    void onExteriorRegion(wxCommandEvent &event);
    
    //! Event procedure that is fired when the user needs to access the material library.
    /*!
        This function is executed when the user clicks on Properties->Material Library 
        or pressing the key combination Ctrl+L. This function will bring up the Material
        Library dialog and will display all of the materials within the library and what is 
        currently being using in the simulation. The dialog will allow the user to add in new materials
        into the library from the simulation material listing or to edit any material.
        For additional documentation on the wxCommandEvent object, refer
        to the following link:
        http://docs.wxwidgets.org/3.0/classwx_command_event.html
        \param event A required parameter for the event procedure to work properly
    */ 
    void onMatLibrary(wxCommandEvent &event);
    
	/* This section is for the Mesh menu */
    
    //! Event procedure that is fired when the user is ready to create the mesh from the geometry
    /*! 
        This function is executed each time the user clicks on Mesh->Create Mesh or 
        when the user clicks on the create mesh icon in the toolbar.
        Currently, this is being worked on and additional documentation 
        will come when things are rady
        For additional documentation on the wxCommandEvent object, refer
        to the following link:
        http://docs.wxwidgets.org/3.0/classwx_command_event.html
        \param event A required parameter for the event procedure to work properly
    */ 
	void onCreateMesh(wxCommandEvent &event);
    
    //! Event procedure that is fired when the user would like to display the mesh with the geometry on the canvas
    /*!
        This function is executed each time the user clicks on Mesh->Create Mesh.
        The idea behind this function is that this function will toggle the displaying of the mesh
        on the canvas. This display will go alongside that of the geometry.
        For additional documentation on the wxCommandEvent object, refer
        to the following link:
        http://docs.wxwidgets.org/3.0/classwx_command_event.html
        \param event A required parameter for the event procedure to work properly
    */ 
	void onShowMesh(wxCommandEvent &event);
    
    //! Event proceudre that is fired when the user needs to delete the mesh
    /*!
        This function is executed when the user clicks on Mesh->Delete Mesh.
        This will delete the mesh from memory.
        For additional documentation on the wxCommandEvent object, refer
        to the following link:
        http://docs.wxwidgets.org/3.0/classwx_command_event.html
        \param event A required parameter for the event procedure to work properly
    */ 
	void onDeleteMesh(wxCommandEvent &event);
    
    /* This section is for the Analysis menu */
    
    //! Event procedure that is executed each time the user needs to view something
    /*!
        This function is exeucted each time the user clicks on Analysis->Analyze.
        This is currently being worked on any will be updated later
        For additional documentation on the wxCommandEvent object, refer
        to the following link:
        http://docs.wxwidgets.org/3.0/classwx_command_event.html
        \param event A required parameter for the event procedure to work properly
    */ 
    void onAnalyze(wxCommandEvent &event);
    
    //! Event procedure that is executed each time the user needs to view the results of the simulation
    /*!
        This function is exeucted each time the user clicks on Analysis->View Results or clicks on the view results icon in the toolbar.
        This will create a new frame allowing the user to view the results of the simulation
        For additional documentation on the wxCommandEvent object, refer
        to the following link:
        http://docs.wxwidgets.org/3.0/classwx_command_event.html
        \param event A required parameter for the event procedure to work properly
    */ 
    void onViewResults(wxCommandEvent &event);
    
    /* This section is for the Help menu option */
    
	//! Event Procedure that is fired when the user needs to view the manual
    /*!
        This event is fired each time the user clicks on Help->View Manual.
        This function will bring up the website (or open the pdf file) of the manual
        For additional documentation on the wxCommandEvent object, refer
        to the following link:
        http://docs.wxwidgets.org/3.0/classwx_command_event.html
        \param event A required parameter for the event procedure to work properly
    */ 
    void onManual(wxCommandEvent &event);
	
	//! Event procedure that is fired when the user needs to see the license associated with the simulator
    /*!
        This function is executed each time the user clicks on Help->View License.
        This will bring up a copy of the GNU public v3 license that is used for the program to be
        open source.
        For additional documentation on the wxCommandEvent object, refer
        to the following link:
        http://docs.wxwidgets.org/3.0/classwx_command_event.html
        \param event A required parameter for the event procedure to work properly
    */ 
    void onLicense(wxCommandEvent &event);
	
	//! Event procedure that is fired when the user needs to see what verison the simualtor is currently at.
    /*!
        This function is executed each time the user clicks on Help->About. This will bring 
        up the about dialog which will provide some general information about the simulator such as
        author contact information, current version, and copyright infomation and any acknowlegements
        For additional documentation on the wxCommandEvent object, refer
        to the following link:
        http://docs.wxwidgets.org/3.0/classwx_command_event.html
        \param event A required parameter for the event procedure to work properly
    */ 
    void OnAbout(wxCommandEvent &event);
    
	
    //! Event that is called when the user wants to toggle between node and block label creation
    /*!
        For additional documentation on the wxCommandEvent object, refer
        to the following link:
        http://docs.wxwidgets.org/3.0/classwx_command_event.html
        \param event A required parameter for the event procedure to work properly
    */ 
    void onToggleNodeCreation(wxCommandEvent &event)
    {
        if(_UIState == systemState::MODEL_DEFINING)
        {
            _model->setCreateNodeState(!_model->getCreateNodeState());
        }
    }
    
    //! Event that is called when the user wants to toggle between line and arc label creation
    /*!
        For additional documentation on the wxCommandEvent object, refer
        to the following link:
        http://docs.wxwidgets.org/3.0/classwx_command_event.html
        \param event A required parameter for the event procedure to work properly
    */ 
    void onToggleLineCreation(wxCommandEvent &event)
    {
        if(_UIState == systemState::MODEL_DEFINING)
        {
            _model->setCreateLinesState(!_model->getCreateLineState());
        }
    }
    
    //! Event procedure that is fired when the user moves the mouse pointer across the canvas screen
    /*!
        This function will simply update the status bar with the current coordinate position of the mouse
        For additional documentation on the wxCommandEvent object, refer
        to the following link:
        http://docs.wxwidgets.org/3.0/classwx_command_event.html
        \param event A required parameter for the event procedure to work properly.
    */ 
    void onGLCanvasMouseMove(wxCommandEvent &event);
    
    //! Event procedure that is fired when the user press a key on the keyboard
    /*!
        Any keyboard bindings that are not on the toolbar can be found here. 
        This event is fired each time that the user presses a button on the keyboard.
        For additional documentation on the wxCommandEvent object, refer
        to the following link:
        http://docs.wxwidgets.org/3.0/classwx_command_event.html
        \param event A required parameter for the event procedure to work properly. This will contain the 
                     data for which key was pressed by the user
    */ 
    void onKeyDown(wxKeyEvent &event);

 	/*****************************
	* Prototypes for client area *
	******************************/   
	
	//! Function that is called to create the initial client area
    /*!
        This function is only called on start-up and is the
        first screen that the user sees
    */ 
	void createInitialStartupClient();
	
	//! This function is called when the user is ready to choose their physics simulation
    /*!
        This function is called when the user presses on new on the startup screen
        or when the user is ready for a new simulation by clicking on File->New.
        For this function to work properly, the frame must be cleared of any items
        from the previouse state and then it will draw the approiate items 
        on the screen.
        The user is able to choose the different physics simulations that they need to perform
        from the menu. After choosing, the function will call the createModelDefinitingClient
        in order to allow the user to begin creating their geometry
    */ 
	void createProblemChoosingClient();
	
	
	//! This function is called to create the client for defining the physics problem
	/*
		This function is called when the user is ready to create the model for the simulation.
        This function will draw the toolbar and the canvas for the user to use. It will
        also enable the menu bar for the user to click on.
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
    /*!
        This function is executed when the createModelDefiningClient function
        is executed
        \sa createModelDefinitingClient()
    */ 
	void createTopToolBar();
	
    /*************************
	* Prototypes for buttons *
	**************************/
	
	//! Function called when the back button is pressed
    /*!
        This function is exectured when the user is on the problem selection client
        where the two buttons are back or finish. When user clicks on the back button,
        this function is executed. The function does not use any of the parameters
        in the wxCommandEvent object but this is required for proper routing of the event.
        For additional documentation on the wxCommandEvent object, refer
        to the following link:
        http://docs.wxwidgets.org/3.0/classwx_command_event.html
        \param event A required parameter for the event procedure to work properly.
    */ 
	void onBackButton(wxCommandEvent &event);
	
    //! Function that is called when the finish button is preseed
    /*!
        This function is exectured when the user is on the problem selection client
        where the two buttons are back or finish. When user clicks on the finish button,
        this function is executed. The function does not use any of the parameters
        in the wxCommandEvent object but this is required for proper routing of the event.
        For additional documentation on the wxCommandEvent object, refer
        to the following link:
        http://docs.wxwidgets.org/3.0/classwx_command_event.html
        \param event A required parameter for the event procedure to work properly.
    */ 
	void onFinishButton(wxCommandEvent &event);
	
    /********************
	* Prototypes Others *
	*********************/	
	
	//! Event called when a resize event occurs
    /*!
        A resize event occurs whenever the user expands or collaspes the
        main frame. This event will also calculate the size needed for 
        the canvas to stay in within propotion to the client area of
        the frame. 
        For additional documentation on the wxSizeEvent object, refer
        to the following link:
        http://docs.wxwidgets.org/3.1.0/classwx_size_event.html
        \param event A required parameter for the event procedure to work properly. In this function, the object is not used
    */ 
	void onResize(wxSizeEvent &event);	
	
	//! This fucntion will enable/disable the menubar
    /*!
        This fucntion is called on the start up in order to disable the menubar. 
        The menu bar is enabled when the state of the UI is in the model defining
        state. Otherwise, the menubar is alwasy disabled
        \param enable Boolean to enable or disable the menu bar. True means the menu bar is enable. False for disable
    */ 
	void enableToolMenuBar(bool enable);
	
	/**
	 * @brief Function that is called which will save the data structures to a file choosen by the user
	 * @param filePath The path where the data should be saved to
	 */
	void save(string filePath);
	
	/**
	 * @brief Function that is called which will load the data into the data structures from a file choosen by the user
	 * @param filePath The path where the file is located
	 */
	void load(string filePath);
    
    //! Function that is needed in order to tell the wx library that this class has event procedures
    wxDECLARE_EVENT_TABLE();
};

#endif /* OMNIFEM_H_ */
