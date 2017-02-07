#ifndef MAGNETIC_PREFERENCE_H_
#define MAGNETIC_PREFERENCE_H_

#include <common/enums.h>
#include <math.h>

/*! /class magneticPref
 *  /brief THis class is used to store all of the preferences for the magnetic physics problem
 *  For ease, all data types will be public
 */
class magneticPreference
{
public:
    //! This is the AC frequeny that will be used when solving the problem in conjuction with the "circuit simulation"
    double frequency = 0;
    
    //! This value is the length of the geometry that is into the page direction.
    double depth = 1;
    
    //! This number specifies the stopping criteria for the linear solver
    double precision = powf(10, -8);
    
    //! May not need this since this was used in the triangle problem. But, triangle adds points to the mesh to ensure no angles are smaller then the specified angle here
    double minAngle = 30;
    
    //! The unit the is associated with the dimensions prescribed in the models geometry
    unitLengthEnum lengthUnits = unitLengthEnum.INCHES;
    
    //! This property determiens what graphing system the user will be in (Cartesian or polar)
    planarCoordinateEnum coordinateType = CARTESIAN;
    
    //! This 
    problemTypeEnum probType = PLANAR;
    
    //! THis will determine how large grid spacing will be 
    double gridSize = 0.25;
    
    //! This will turn on/off the grid
    bool showGrid = True;
    
    //! This will turn on/off the marking for the origin
    bool showOrigin = False;
    
    //! This will turn on/off the block label name
    bool showBlockNames = False;
    
    // Not too sure at this time
    double pixels/unit = 100;
    
    //! This sets what type of solver Omni-FEM will use to solve the ac problems
    acSolverEnum acSolver = SUCCAPPROX;
    
    //! This will deteremine what type of wire Omni-FEM is working with when solving the circuit component
    lamWireEnum wireType = NOT_LAMINATED_OR_STRANDED;
}

#endif