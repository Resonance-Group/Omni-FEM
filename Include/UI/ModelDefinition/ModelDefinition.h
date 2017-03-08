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
#include <freeglut.h>
#include <gl.h>
#include <glu.h>

#include <wx/wx.h>

#include <common/ProblemDefinition.h>
#include <common/GridPreferences.h>

#include <UI/geometryShapes.h>

class modelDefinition : public wxGLCanvas
{
private:
    problemDefinition _parameters;
    
    gridPreferences _preferences;
    
    //! This is the context which will be associated to the class
	wxGLContext *_geometryContext;
    
    std::vector<node> _nodeList;
    
	std::vector<blockLabel> _blockLabelList;
    
	std::vector<edgeLineShape> _lineList;
    
	std::vector<arcShape> _arcList;
    
    double _zoomFactor = 1;
    
    double _cameraX = 0;
    
    double _cameraY = 0;
    
    double _gridStep = 0.05;
    
    void updateProjection();
    
    void drawGrid();
    
    double convertToXCoordinate(int xPixel);
    
    double convertToYCoordinate(int yPixel); 
    
    //! This is the event that is fired when the canvas is drawn or re-drawn
	void onPaintCanvas(wxPaintEvent &event);
    

public:
    modelDefinition(wxWindow *par, const wxPoint &point, const wxSize &size);

    problemDefinition* getProblemParameters()
    {
        return &_parameters;
    }
    
    gridPreferences* getGridPreferences()
    {
        return &_preferences;
    }
    
    void updateGrid()
    {
        this->Refresh();
    }
    
    void changeSize(wxSize size)
    {
        this->SetSize(size);
    }
    
private:
    wxDECLARE_EVENT_TABLE(); 
};

#endif