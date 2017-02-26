#ifndef GRID_PREFERENCES_H_
#define GRID_PREFERENCES_H_

#include <common/enums.h>

class gridPreferences
{
private:

    double _ppu = 100;
    
    double _gridSize = 0.25;
    
    planarCoordinateEnum _coordinateSystem;
    
    bool _isShowGrid = true;
    
    bool _isSnapGrid = false;
    
    bool _isShowOrigin = true;
    
    bool _isShowBlockName = true;
    
public:

    void setPPU(double ppu)
    {
        _ppu = ppu;
    }
    
    double getPPU()
    {
        return _ppu;
    }
    
    void setGridSize(double size)
    {
        _gridSize = size;
    }
    
    double getGridSize()
    {
        return _gridSize;
    }
    
    void setCoordinateSystem(planarCoordinateEnum system)
    {
        _coordinateSystem = system;
    }
    
    planarCoordinateEnum getCoordinateSystem()
    {
        return _coordinateSystem;
    }
    
    void setShowGridState(bool willShowGrid)
    {
        _isShowGrid = willShowGrid;
    }
    
    bool getShowGridState()
    {
        return _isShowGrid;
    }
    
    void setSnapGridState(bool willSnapGrid)
    {
        _isSnapGrid = willSnapGrid;
    }
    
    bool getSnapGridState()
    {
        return _isSnapGrid;
    }
    
    void setShowOriginState(bool willShowOrigin)
    {
        _isShowOrigin = willShowOrigin;
    }
    
    bool getShowOriginState()
    {
        return _isShowOrigin;
    }
    
    void setShowBlockNameState(bool willShowBlockName)
    {
        _isShowBlockName = willShowBlockName;
    }
    
    bool getShowBlockNameState()
    {
        return _isShowBlockName;
    }
};
    


#endif