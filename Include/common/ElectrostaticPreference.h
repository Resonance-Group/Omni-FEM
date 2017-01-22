#ifndef ELECTROSTATICPREF_H_
#define ELECTROSTATICPREF_H_

#include <common/enums.h>
#include <math.h>


class electroStaticPref
{
    double depth = 1;
    double precision = powf(10, -8);
    double gridSize = 0.25;
    bool showGrid = True;
    bool showOrigin = False;
    boool showBlockNames = True;
    double pixel/unit = 100;
    planarCoordinateEnum coordinateType = CARTESIAN;
    problemTypeEnum probType = PLANAR;
 
}

#endif