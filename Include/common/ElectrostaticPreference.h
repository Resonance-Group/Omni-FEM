#ifndef ELECTROSTATICPREF_H_
#define ELECTROSTATICPREF_H_

#include <common/enums.h>
#include <math.h>

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
    double _gridSize = 0.25;
    bool _showGridState = true;
    bool _showOriginState = false;
    bool _showBlockNamesState = true;
    double _pixelperunit = 100;
    planarCoordinateEnum _coordinateType = CARTESIAN;
    problemTypeEnum _probType = PLANAR;
    
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
 
};

#endif