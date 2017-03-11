#ifndef ELECTROSTATICPREF_H_
#define ELECTROSTATICPREF_H_

#include <math.h>

#include <wx/string.h>

#include <common/enums.h>

/*! /class electroStaticPref
 *  /brief
 *  This class contains all of the settings that the user can change for solving the electro static portion of 
 *  the simualor
 */ 
class electroStaticPreference
{
private:
    double _depth = 1;
    
    double _precision = powf(10, -8);
    
    double _minAngle = 30;
    
    wxString _comments;
    
    planarCoordinateEnum _coordinateType = CARTESIAN;
    
    problemTypeEnum _probType = PLANAR;
    
    unitLengthEnum _unitLength = INCHES;
    
public:

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
    
    void setCoordinateType(planarCoordinateEnum coordianteSystem)
    {
        _coordinateType = coordianteSystem;
    }
    
    planarCoordinateEnum getCoordinateType()
    {
        return _coordinateType;
    }
    
    void setProblemType(problemTypeEnum prob)
    {
        _probType = prob;
    }
    
    problemTypeEnum getProblemType()
    {
        return _probType;
    }
    
    void setUnitLength(unitLengthEnum unit)
    {
        _unitLength = unit;
    }
    
    unitLengthEnum getUnitLength()
    {
        return _unitLength;
    }
    
    void setMinAngle(double angle)
    {
        _minAngle = angle;
    }
    
    double getMinAngle()
    {
        return _minAngle;
    }
    
    void setComments(wxString comment)
    {
        _comments = comment;
    }
    
    wxString getComments()
    {
        return _comments;
    }
 
};

#endif
