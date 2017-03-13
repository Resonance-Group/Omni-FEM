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
#include <string>
#include <math.h>

#include <freeglut.h>
#include <gl.h>
#include <glu.h>

#include <wx/wx.h>

#include <common/ProblemDefinition.h>
#include <common/GridPreferences.h>

#include <UI/GeometryDialog/BlockPropertyDialog.h>
#include <UI/GeometryDialog/NodalSettingDialog.h>
#include <UI/GeometryDialog/SegmentPropertyDialog.h>
#include <UI/GeometryDialog/ArcSegmentDialog.h>

#include <UI/geometryShapes.h>
#include <UI/GeometryEditor2D.h>

class modelDefinition : public wxGLCanvas
{
private:
    //! This is the context which will be associated to the class
	wxGLContext *_geometryContext;
    
    //! This is the address for the master definition contained in the main frame
    problemDefinition *_localDefinition;
    
    gridPreferences _preferences;
    
    geometryEditor2D _editor;
    
    double _zoomFactor = 1;
    
    double _cameraX = 0;
    
    double _cameraY = 0;
    
    int _mouseXPixel = 0;// This is the pixel coordinate
    
    int _mouseYPixel = 0;
    
    //! This is the variable that will determine to create nodes/block labels
    bool _createNodes = true;
    
    //! This is the variable that will determine to create lines/arcs
    bool _createLines = true;
    
    double convertToXCoordinate(int xPixel);
    
    double convertToYCoordinate(int yPixel);

    void updateProjection();
    
    void drawGrid();

    void roundToNearestGrid(double &xCoordinate, double &yCoordinate);
    
    //! This is the event that is fired when the canvas is drawn or re-drawn
	void onPaintCanvas(wxPaintEvent &event);
    
    void onResize(wxSizeEvent &event);
    
    void onMouseWheel(wxMouseEvent &event);
    
    void onMouseMove(wxMouseEvent &event);
    
    void onMouseLeftDown(wxMouseEvent &event);
    
    void onMouseRightDown(wxMouseEvent &event);
    
    void onEnterWindow(wxMouseEvent &event)
    {
        this->SetFocus();
    }
    
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
    
private:
    wxDECLARE_EVENT_TABLE(); 
};

#endif