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

#endif