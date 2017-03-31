#ifndef GRID_PREFERENCES_H_
#define GRID_PREFERENCES_H_

#include <common/enums.h>

class gridPreferences
{
private:
    
    double _gridStep = 0.25;
    
    planarCoordinateEnum _coordinateSystem;
    
    bool _isShowGrid = true;
    
    bool _isSnapGrid = false;
    
    bool _isShowOrigin = false;
    
    bool _isShowBlockName = true;
    
    bool _isShowAxis = true;
    
    bool _reverseMouseZoom = false;
    
public:
    
    void setGridStep(double size)
    {
        _gridStep = size;
    }
    
    double getGridStep()
    {
        return _gridStep;
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
    
    void setShowAxisState(bool state)
    {
        _isShowAxis = state;
    }
    
    bool getShowAxisState()
    {
        return _isShowAxis;
    }
    
    void setMouseZoomReverseState(bool state)
    {
        _reverseMouseZoom = state;
    }
    
    bool getMouseZoomReverseState()
    {
        return _reverseMouseZoom;
    }
};
    


#endif