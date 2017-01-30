#ifndef ENUMS_H_
#define ENUMS_H_



//! Enum contianing the dimension of the problem
/*! 
	Please note that Omni-FEM does not support all of these dimensions.
	Some are placed here as a place holder for future releases
*/
enum class problemDimension
{
	zero_Dimension = 0,
	one_dimension = 1,
	two_dimension = 2,
	three_dimension = 3
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
	electrostatics = 0,
	magnetics = 1
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



//! This enum will be used to designate the different Boundary conditions
enum bcEnum
{
    /* The first part are the BC conditions that appear in both simulations E-stat and magnetics */
    MIXED,
    PERIODIC,
    ANTIPERIODIC,
    /* This is specific for Magnetics */
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
    
    //! An experimental BC
    STRATEGIC_DUAL_IMAGE,
    /* These are specific for E-stat */
    FIXED_VOLTAGE,
    SURFACE_CHARGE_DENSITY
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
    ID_ComboBox2
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

enum CustomEvent
{
    MagneticMaterial
};

#endif