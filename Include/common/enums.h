#ifndef ENUMS_H_
#define ENUMS_H_

//! This enum is used to set the AC SOlver that Omni-FEM will use
enum acSolverEnum
{
    SUCC.APPROX,
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
    LAMINATED_IN-PLANE,
    LAMINATED_PARALLEL_X_OR_R-AXISYMMETRIC,
    LAMINATED_PARALLEL_Y_OR_Z-AXISYMMETRIC,
    MAGNET_WIRE,
    PLAIN_STRANDED_WIRE,
    LITZ_WIRE,
    SQUARE_WIRE
};



//! This enum will be used to designate the different Boundary conditions
enum bcEnum
{
    /* The first part are the BC conditions that appear in both simulations E-stat and magnetics */
    MIXED,
    PERIODIC,
    ANTI-PERIODIC,
    /* This is specific for Magnetics */
    PRESCRIBE_A,
    SMALL_SKIN_DEPTH,
    STRATEGIC_DUAL_IMAGE,
    /* These are specific for E-stat */
    FIXED_VOLTAGE,
    SURFACE_CHARGE_DENSITY
};

#endif