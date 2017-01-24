#ifndef ELECTROSTATICPREF_H_
#define ELECTROSTATICPREF_H_

#include <common/enums.h>
#include <math.h>

/*! /class electroStaticPref
 *  /brief
 *  This class contains all of the settings that the user can change for solving the electro static portion of 
 *  the simualor
 */ 
class electroStaticPref
{
public:
    double depth = 1;
    double precision = powf(10, -8);
    double gridSize = 0.25;
    bool showGrid = True;
    bool showOrigin = False;
    bool showBlockNames = True;
    double pixelperunit = 100;
    planarCoordinateEnum coordinateType = CARTESIAN;
    problemTypeEnum probType = PLANAR;
 
}

#endif