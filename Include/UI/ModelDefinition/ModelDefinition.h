/* The purpose of this file will be to create the canvas to which the user will need to interact with
 * This class will contain an object(s) that will contain most of the definitions of the physics problem.
 * For example, this class will containt the list of boundary conditions, material properties, etc.
 * The reason for this desgin was that it would be easier for data access when the user needs to manipulate
 * the data or whent he user needs to set lines or nodes to specific sets of data.
 * Other methods invovled creating a custom class which can be tricky
 */ 

#ifndef MODELDEFINITION_H_
#define MODELDEFINITION_H_

#include <vector>
#include <algorithm>
#include <string>
#include <math.h>

#include <glew.h>
#include <freeglut.h>
/*
#include <freeglut.h>
#include <gl.h>
#include <glu.h>
*/
#include <wx/wx.h>
#include <wx/gdicmn.h>

#include <common/ProblemDefinition.h>
#include <common/GridPreferences.h>
#include <common/wxGLString.h>
#include <common/plfcolony.h>

#include <common/GeometryProperties/NodeSettings.h>

#include <UI/GeometryDialog/BlockPropertyDialog.h>
#include <UI/GeometryDialog/NodalSettingDialog.h>
#include <UI/GeometryDialog/SegmentPropertyDialog.h>
#include <UI/GeometryDialog/ArcSegmentDialog.h>

#include <UI/geometryShapes.h>
#include <UI/GeometryEditor2D.h>
#include <UI/common.h>

#include <UI/ModelDefinition/glText.h>

class modelDefinition : public wxGLCanvas
{
private:
    //! This is the context which will be associated to the class
	wxGLContext *_geometryContext;
    
    //! This is the address for the master definition contained in the main frame
    problemDefinition *_localDefinition;
    
    gridPreferences _preferences;
    
    geometryEditor2D _editor;
    
    glText *_textRendering;
    
    double _zoomX = 1.0;
    
    double _zoomY = 1.0;
    
    double _cameraX = 0;
    
    double _cameraY = 0;
    
    int _mouseXPixel = 0;// This is the pixel coordinate
    
    int _mouseYPixel = 0;
    
    bool _doZoomWindow = false;
    
    bool _isFirstInitlized = false;
    
    //! This is the variable that will determine to create nodes/block labels
    bool _createNodes = true;
    
    //! This is the variable that will determine to create lines/arcs
    bool _createLines = true;
    
    bool _nodesAreSelected = false;
    
    bool _linesAreSelected = false;
    
    bool _arcsAreSelected = false;
    
    bool _labelsAreSelected = false;
    
    bool _geometryIsSelected = false;
    
    wxRealPoint _windowZoomStartPoint;
    
    wxRealPoint _windowZoomEndPoint;
    
    double convertToXCoordinate(int xPixel)
    {
        return _zoomX * (((2.0 / this->GetSize().GetWidth()) * ((double)xPixel - this->GetSize().GetWidth() / 2.0)) / 1.0) * (this->GetSize().GetWidth() / this->GetSize().GetHeight()) + _cameraX;
    }
    
    double convertToYCoordinate(int yPixel)
    {
        return _zoomY * (-(2.0 / this->GetSize().GetHeight()) * ((double)yPixel - this->GetSize().GetHeight() / 2.0)) / 1.0 + _cameraY;
    }
    
    double getTolerance()
    {
        return (1 / (((_zoomX + _zoomY) / 2.0) * 50));
    }
    
    void clearSelection();

    void updateProjection();
    
    void drawGrid();

    void roundToNearestGrid(double &xCoordinate, double &yCoordinate);
    
    //! This is the event that is fired when the canvas is drawn or re-drawn
	void onPaintCanvas(wxPaintEvent &event);
    
    void onResize(wxSizeEvent &event);
    
    void onMouseWheel(wxMouseEvent &event);
    
    void onMouseMove(wxMouseEvent &event);
    
    void onMouseLeftDown(wxMouseEvent &event);
    
    void onMouseLeftUp(wxMouseEvent &event);
    
    void onMouseRightDown(wxMouseEvent &event);
    
    void onKeyDown(wxKeyEvent &event);
    
    void onEnterWindow(wxMouseEvent &event)
    {
      //  this->SetFocus();
    }
    
    void doZoomWindow();
    
public:
    modelDefinition(wxWindow *par, const wxPoint &point, const wxSize &size, problemDefinition &definition);

    void setGridPreferences(gridPreferences &preferences)
    {
        _preferences = preferences;
        this->Refresh();
    }
    
    gridPreferences* getGridPreferences()
    {
        return &_preferences;
    }
    
    void setCreateNodeState(bool state)
    {
        _createNodes = state;
    }
    
    void setCreateLinesState(bool state)
    {
        _createLines = state;
    }
    
    bool getCreateNodeState()
    {
        return _createNodes;
    }
    
    bool getCreateLineState()
    {
        return _createLines;
    }
    
    void setZoomWindow(bool state)
    {
        _doZoomWindow = state;
    }
    
    bool getZoomWindow()
    {
        return _doZoomWindow;
    }
    
    void zoomIn()
    {
        _zoomX *= pow(1.2, -(300.0) / 150.0);
        _zoomY *= pow(1.2, -(300.0) / 150.0);
        
        if(_zoomX > _zoomY)
            _zoomY = _zoomX;
        else if(_zoomY > _zoomX)
            _zoomX = _zoomY;

        this->Refresh();
    }
    
    void zoomOut()
    {
        _zoomX *= pow(1.2, (300.0) / 150.0);
        _zoomY *= pow(1.2, (300.0) / 150.0);
        
        if(_zoomX > _zoomY)
            _zoomY = _zoomX;
        else if(_zoomY > _zoomX)
            _zoomX = _zoomY;
        
        this->Refresh();
    }
    
    void deleteSelection();
    
    //! This will allow the user to edit the settings for the particular node/label/arc/line. It is in this calss because this class has access to the master settings list
    void editSelection();
    
    //! If a properties name is changes or if the property is deleted, this will reset the properties
    void updateProperties(bool scanConductorProperty, bool scanNodalProperty, bool scanBoundaryProperty, bool scanMaterialProperty, bool scanCircuitProperty);
    
    void selectGroup(EditGeometry geometry, unsigned int groupNumber);
    
    void moveTranslateSelection(double horizontalShift, double verticalShift);
    
    void moveRotateSelection(double angularShift, wxPoint aboutPoint);
    
    void scaleSelection(double scalingFactor, wxPoint basePoint);
    
    void mirrorSelection(wxPoint pointOne, wxPoint pointTwo);
    
    void copyTranslateSelection(double horizontalShift, double verticalShift, unsigned int numberOfCopies);
    
    void copyRotateSelection(double angularShift, wxPoint aboutPoint, unsigned int numberOfCopies);
    
    
    
private:
    wxDECLARE_EVENT_TABLE(); 
};

#endif