#ifndef MAGNETIC_PREFERENCE_H_
#define MAGNETIC_PREFERENCE_H_

#include <wx/string.h>

#include <common/enums.h>
#include <math.h>

/*! /class magneticPref
 *  /brief THis class is used to store all of the preferences for the magnetic physics problem
 *  For ease, all data types will be public
 */
class magneticPreference
{
private:
    //! This is the AC frequeny that will be used when solving the problem in conjuction with the "circuit simulation"
    double _frequency = 0;
    
    //! This value is the length of the geometry that is into the page direction.
    double _depth = 1;
    
    //! This number specifies the stopping criteria for the linear solver
    double _precision = powf(10, -8);
    
    //! May not need this since this was used in the triangle problem. But, triangle adds points to the mesh to ensure no angles are smaller then the specified angle here
    double _minAngle = 30;
    
    //! The unit the is associated with the dimensions prescribed in the models geometry
    unitLengthEnum _lengthUnit = unitLengthEnum::INCHES;
    
    //! This property determiens what graphing system the user will be in (Cartesian or polar)
    planarCoordinateEnum _coordinateType = CARTESIAN;
    
    //! This 
    problemTypeEnum _probType = PLANAR;
    
    //! This sets what type of solver Omni-FEM will use to solve the ac problems
    acSolverEnum _acSolver = SUCCAPPROX;
    
    wxString _comments;
    
public:
    
    //! This will set the frequency that the problem is going to simulate the AC circuits
    void setFrequency(double &freq)
    {
        _frequency = freq;
    }
    
    double getFrequency()
    {
        return _frequency;
    }
    
    void setDepth(double &depth)
    {
        _depth = depth;
    }
    
    
    double getDepth()
    {
        return _depth;
    }
    
    
    void setPrecision(double &precision)
    {
        _precision = precision;
    }
    
    
    double getPrecision()
    {
        return _precision;
    }
    
    void setMinAngle(double &minAngle)
    {
        _minAngle = minAngle;
    }
    
    
    double getMinAngle()
    {
        return _minAngle;
    }
    
    void setUnitLength(unitLengthEnum unit)
    {
        _lengthUnit = unit;
    }
    
    unitLengthEnum getUnitLength()
    {
        return _lengthUnit;
    }
    
    void setPlanarCoordinate(planarCoordinateEnum &coordinateSystem)
    {
        _coordinateType = coordinateSystem;
    }
    
    planarCoordinateEnum getPlanarCoordinate()
    {
        return _coordinateType;
    }
    
    void setProblemType(problemTypeEnum type)
    {
        _probType = type;
    }
    
    problemTypeEnum getProblemType()
    {
        return _probType;
    }
    
    void setACSolver(acSolverEnum solver)
    {
        _acSolver = solver;
    }
    
    acSolverEnum getACSolver()
    {
        return _acSolver;
    }
    
    void setComments(wxString comments)
    {
        _comments = comments;
    }
    
    wxString getComments()
    {
        return _comments;
    }
    
};

#endif