#ifndef ENUMS_H_
#define ENUMS_H_

//! Enum used to designate the mesh size
/*!
    This enum is used mainly to indicate what mesh size
    the user would like to apply to a particular area 
    The enum ranges from extremely fine to extremely coarse.
    There is also an option for a custom mesh size
*/ 
enum meshSize
{
    MESH_NONE,/*!< Value to indicate that there is no mesh size for the designated area */
    MESH_EXTREMELY_FINE,/*!< Values to indicate that the mesh needs to contain the smallest element size possible */
    MESH_EXTRA_FINE,/*!< Values to indicate that the mesh needs to contain very small element sizes */
    MESH_FINER,/*!< Value to indicate that the mesh needes to contain small element sizes */
    MESH_FINE,/*!< Value to indicate that the mesh needs to contain mesh sizes that are a little bit smaller then the default */ 
    MESH_NORMAL,/*!< Value used to indicate that the mesh needs to contain the default element size */
    MESH_COARSE,/*!< Value used to indicate that the mesh needs to contain elements that are a little bit bigger then the default element size */
    MESH_COARSER,/*!< Value used to indicate that the mesh neeeds to contain large element sizes */
    MESH_EXTRA_COARSE,/*!< Value used to indicate that the mesh needs to contain very large element sizes */
    MESH_EXTREMELY_COARSE,/*!< Value used to indicate that the mesh needs to contain the largest possible element size */
    MESH_CUSTOM /*!< Value used to indicate that the user is manually inputting the element size */
};




//! Enum used in the event table to disgiunish the event as a file menu event
/*!
    This enum is used to indicate that the event came from the file
    menu. This will also allow propery routing for the event to
    call the correct function
*/ 
enum FileMenuID
{
    ID_NO_FILE_ID,/*!< Default value for the enum */
    ID_FILE_NEW,/*!< Value used to indicate that the event is a file new event */
    ID_SAVE,/*!< Value used to indicate that the event is a save event */
    ID_SAVE_AS,/*!< Value used to indicate that the event is a save as event */
    ID_OPEN/*!< Value used to indicate that the event is a open event */
};

enum EditMenuID
{
    NO_EDIT_ID = 100,
    ID_UNDO,
    ID_COPY,
    ID_DELETE,
    ID_MOVE,
    ID_SCALE,
    ID_MIRROR,
    ID_CREATE_RADIUS,
    ID_CREATE_OPEN_BOUNDARY,
    ID_PREFERENCES, 
    ID_SELECT_GROUP,
    ID_EDIT_PROPERTY,
    ID_LUA_RUN
};


enum ViewMenuID
{
    NO_VIEW_ID = 200,
    ID_ZOOM_IN,
    ID_ZOOM_OUT,
    ID_ZOOM_WINDOW,
    ID_LUA_CONSOLE,
    ID_SHOW_STATUSBAR,
    ID_SHOW_BLOCK_NAMES,
    ID_SHOW_ORPHANS
};


enum GridMenuID
{
    NO_GRID_ID = 300,
    ID_SHOW_GRID,
    ID_SNAP_GRID,
    ID_SET_GRID_PREFERENCES
};



enum PropertiesMenuID
{
    NO_PROPERTY_ID = 400,
    ID_MATERIALS,
    ID_BOUNDARY,
    ID_POINT,
    ID_CONDUCTORS,
    ID_EXTERIOR_REGION,
    ID_MATERIAL_LIBRARY
};



enum MeshMenuID
{
    NO_MESH_MENU_ID = 500,
    ID_CREATE_MESH,
    ID_SHOW_MESH,
    ID_DELETE_MESH
};



enum AnalysisMenuID
{
    NO_ANALYSIS_MENU_ID = 600,
    ID_ANALYZE,
    ID_VIEW_RESULTS
};



//! Enum for the tool bar
enum ToolBarID
{
    ID_TOOLBAR_NEW_FILE = 700,
    ID_TOOLBAR_SAVE_FILE,
    ID_TOOLBAR_SAVE_FILE_AS,
    ID_TOOLBAR_OPEN_FILE,
    ID_TOOLBAR_ZOOM_IN,
    ID_TOOLBAR_ZOOM_OUT,
    ID_TOOLBAR_EDIT_PROPERTY,
    ID_TOOLBAR_MOVE,
    ID_TOOLBAR_COPY,
    ID_TOOLBAR_SCALE,
    ID_TOOLBAR_DELETE,
	ID_TOGGLE_NODE,
	ID_TOGGLE_LINE,
	ID_TOOLBAR_CREATE_MESH,
    ID_TOOLBAR_SOLVE,
    ID_TOOLBAR_VIEW_RESULTS
};

//! Enum for the menus of the menu bar
/*!
 * This is a general purpose enum
 * used for during the menu bar creation.
 * This enum is primaryly used 
 * for event proceuder routing. Normally,
 * these would go in their own enum. But since
 * there would be 2 additional enums with 2 items 
 * inside, it is more convient to place these in one
 * larger enum.
 */ 
enum menubarID
{
    ID_NO_ID = 800, /*!< Defuault value for this eneum */
    ID_MANUAL, /*!< Value used to indicate that the user sent a manual event */
    ID_LICENSE, /*!< Value used to indicate that the user sent a license event */
    ID_PROBLEM_PREFERNCES,/*!< Value used to indicate that the user sent a problem preferences event */
    ID_SOLVE_PROBLEM/*!< Value used to indicate that the event is a solve problem event */
};



//! Enum containing the different physics problems
/*!
	This is the enum that is used to determine what physics problem 
	will be simulated. This could effect the view of some menus.
	For a later addition of multiphysics, this system will need
	to be revised.
	
	For now, the enum number must correspond to the index number in the wxArrayString object.
*/
enum class physicProblems
{
    NO_PHYSICS_DEFINED,
    PROB_ELECTROSTATIC,
    PROB_MAGNETICS
};


enum class systemState
{
    ON_START_UP_STATE,
    INITIAL_START_UP,
    PHYSICS_CHOOSING,
    MODEL_DEFINING,
    SIMULATING,
    VIEWING_RESULTS
};

//! This enum is used to set the AC SOlver that Omni-FEM will use
enum acSolverEnum
{
    SUCCAPPROX,
    NEWTON
};


//! This enum is used to set the units that Omni-FEM will use
enum unitLengthEnum
{
    INCHES,
    MILLIMETERS,
    CENTIMETERS,
    METERS,
    MILS,
    MICROMETERS
};



//! This enum is used to set what coordinate system Omni-FEM should use when solving
enum planarCoordinateEnum
{
    NO_COORDINATE_DEFINED,
    CARTESIAN,
    POLAR
};



//! This enum is used to specify what problem type Omni-FEM needs to use when solving
enum problemTypeEnum
{
    PLANAR,
    AXISYMMETRIC
};



//! For the magnetics solver, this enum will inform Omni-FEM if laminations or wire should be used in solving. This sets a specific region to be laminated or wired
enum lamWireEnum
{
    NOT_LAMINATED_OR_STRANDED,
    LAMINATED_IN_PLANE,
    LAMINATED_PARALLEL_X_OR_R_AXISYMMETRIC,
    LAMINATED_PARALLEL_Y_OR_Z_AXISYMMETRIC,
    MAGNET_WIRE,
    PLAIN_STRANDED_WIRE,
    LITZ_WIRE,
    SQUARE_WIRE, 
    CCA_10,
    CCA_15
};



//! This enum will be used to designate the different Boundary conditions for the magnetic Boundary Conditions
enum bcEnumMagnetic
{
    /*!
     *  The vector potental A is prescribed along a given boundary. This boundary condition
     *  can be used to presribe the flux passing normal to a boundary, since the normal
     *  flux is equal to the tangential derivative of A along the bounary.
     *  The parameters are identified by A0, A1, A2, and phi
     */ 
    PRESCRIBE_A,
    /*! 
     *  This boundary condition denotes an interface with a material subject to eddy currents at
     *  high enough frequencies suc hthat the skin dpeth in the material
     *  is very small. The boundary condition is a Robin boundary condition with complex
     *  coefficients of the form:
     *  da/dn + ((1 + j) / delta) * A = 0.
     *  where n denotes the direction of the outward normal to the boundary and delta
     *  denotes the skin depth of the material the the frequency of interest
     *  delta = sqrt(2 / (omega * mur * mu0 * sigma))
     */ 
    SMALL_SKIN_DEPTH,
    MIXED,
    //! An experimental BC
    STRATEGIC_DUAL_IMAGE,
    PERIODIC,
    ANTIPERIODIC
};


enum bcEnumElectroStatic
{
   /* These are specific for E-stat */
    FIXED_VOLTAGE,
    SURFACE_CHARGE_DENSITY,
    E_STATIC_MIXED, 
    E_STATIC_PERIODIC,
    E_STATIC_ANTIPERIODIC
};


//! This enum is used for the properties dialog box
enum propertiesDialogEnum
{
    ID_ButtonOk,
    ID_ButtonAdd,
    ID_ButtonDelete,
    ID_ButtonModify
};

//! This enum is a general enum for frames that will include buttons or other widgets
enum generalFrameButton
{
    ID_ComboBox1,
    ID_ComboBox2,
    ID_RadioButton1,
    ID_RadioButton2, 
    ID_CHECKBOX1, 
    ID_BUTTON1,
    ID_BUTTON2,
    ID_BUTTON3,
    ID_TREECTRL1,
    ID_TREECTRL2,
    ID_LISTBOX
};

enum magneticBlockPropertyDiag
{
    ID_TextControl1,
    ID_TextControl2,
    ID_TextControl3,
    ID_TextControl4,
    ID_TextControl5,
    ID_TextControl6,
    ID_TextControl7,
    ID_TextControl8,
    ID_TextControl9,
    ID_TextControl10,
    ID_TextControl11,
    ID_TextControl12,
    ID_TextControl13
};

//! Enum for the buttons
enum buttonID
{
    ID_NO_BUTTON,
	ID_buttonTwoDim,
	ID_buttonBack,
	ID_buttonNew,
	ID_buttonOpen,
	ID_buttonFinish
};


enum OpenBoundaryEdge
{
    NO_BOUNDARY_DEFINED,
    DIRICHLET,
    NEUMANN
};

enum EditGeometry
{
    EDIT_NONE,
    EDIT_NODES,
    EDIT_LINES,
    EDIT_ARCS,
    EDIT_LABELS,
    EDIT_ALL
};



#endif