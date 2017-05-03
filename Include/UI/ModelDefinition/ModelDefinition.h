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
#include <UI/GeometryDialog/EditGroupDialog.h>

#include <UI/ModelDefinition/OGLFT.h>

#include <UI/geometryShapes.h>
#include <UI/GeometryEditor2D.h>
#include <UI/common.h>


//! The model class the handles the dispaying of objects
/*!
    This class is designed to handle the bulk of dispalying the geometry onto a glCanvas.
    This class will handle the drawing of any nodes/arcs/lines/labels. Along
    with any zooming, mouse moving, dragging, snapping to grid, and selecting geometry objects.
    Other functionality in the class include creating copies of selected geometry and moving selected geometry.
    THe modelDefinition inherits from the wxGLCanvas class because the modelDefinition class
    handles all direct calls for openGL.
    Refer to the following link for documentation of wxGLCanvas class:
    http://docs.wxwidgets.org/3.1.0/classwx_g_l_canvas.html
*/ 
class modelDefinition : public wxGLCanvas
{
private:

    //! This is the context which will be associated to the class.
    /*!
        A context is used for the glCanvans becuase there needs to be a record
        of the state of an openGL machince. This also servces as a connection
        between openGL and the canvas.
        For further documentation of the wxGLCanvas object, refer to the following link:
        http://docs.wxwidgets.org/3.1.0/classwx_g_l_context.html
    */ 
	wxGLContext *_geometryContext;
    
    //! This is the address for the problem definition contained in the main frame object.
    /*!
        This is simply a local variable for easier access to the state of Omni-FEM.
        This couldn't be a direct copy because the modelDefinition would need to be able to 
        see any changes that the user makes while to program is running. With this being a pointer,
        we are now pointing to the address which will allow the user to make changes to the top level
        and the changes will properaget downward
     */ 
    problemDefinition *_localDefinition;
    
    //! The local variable containing all of the grid preferences.
    /*! 
        For a detailed explanation, refer to the apprioate documentation for the gridPreferences class.
        In short, this variable stores the current state of the grid. The state of if the grid should be drawn,
        if geometry should be snapped to the grid, if block labels should be displayed, etc. All of these 
        status variables are stored in this variable which is access through out the modelDefinition class
    */ 
    gridPreferences _preferences;
    
    //! The local variable containing all of the code for calculating anything related to the geometry.
    /*!
        For a detailed explanation, refer to the documentation for the geometryEditor2D class.
        In short, this variable contains all of the code necessary for calculating any geometric functions.
        If there is an intersection between the arcs or lines or node or block labels.
        This variable also contains the data structures which hold the lists of the geometry shapes.
        Anytime a draw event occurs or the class needs to loop through any combination of the geometry
        shapes, this variable is accessed
     */ 
    geometryEditor2D _editor;
    
    //! The variable that contains the zoom factor in the x direction.
    /*!
        Zooming could be taken as one variable. However, having two variables for zooming
        allows a greater ability for configuring the glViewport especially for the zoom window.
        Still, in many cases in order to convert a two variable zoom factor into one, the 
        program takes the average between the x and the y zoom factors
     */ 
    double _zoomX = 1.0;
    
    //! The variable that contains the zoom factor in the y-direction.
    /*
        See the documentation for the _zoomX variable for a detailed description
     */ 
    double _zoomY = 1.0;
    
    //! The varable that contains the viewport offset in the x-direction.
    /*!
        In order to emulate panning across an infinite grid, the program uses glTranslate function.
        Every time that a paint event is fired, the program will alwys reset itself back to the default position 
        which is the view port being centered at 0,0 with coordinate number 1 above, -1 below, 1 to the right, and -1 to the left.
        Then, the program will translate the viewport _cameraX and _cameraY number of steps to the proper location.
        For more documentation on this matter, refer to the function updateProjection(). THis function implements the idea.
     */ 
    double _cameraX = 0;
    
    //! The varibale that contains the viewport offset in the y-direction.
    /*!
        For a detailed explaniation refer to the documentation for the _cameraX variable
     */ 
    double _cameraY = 0;
    
    //! Holds the pixel value for hte previous location of the mouse in the x-direction
    /*!
        This variable is not used for much except for calculating the _cameraX/_cameraY values 
        when the user pans across the canvas. In the calculation, the program looks to find the difference
        between the current mouse position and the previous mouse position (which is this variable) and from there 
        determines how much to increment the _cameraX/_cameraY values by. For a more detailed description of this,
        refer to the documentation of for the function onMouseMove(wxMouseEvent &event).
        As a side note, this is the pixel value and not the coordiante value.
    */ 
    int _mouseXPixel = 0;
    
    //! Holds the pixel value for the previous location of the mouse in the y-Direction
    /*!
        Refer to the documentation for the _mouseXPixel for a detailed description of this variable
     */ 
    int _mouseYPixel = 0;
    
    //! A status flag to indicate to the program to perform a zoom window
    /*
        When the user clicks on the zooom window, this boolean becomes true. When it is true,
        the program's abaility to create nodes/lines/arcs will be overridden to create a 
        zoom window which is a dotted line. On the up release of the left mouse button,
        the program will check if this boolean is true and if so, resize the glviewport and 
        the projection matrix in order to match the zoom window that the user created.
        After completetion, this variable will be set back to false.
     */ 
    bool _doZoomWindow = false;
    
    //! A status flag to indicate to the program that a mirror operation will be performed
    /*!
        When the user would like perform a mirror operation on selected geometry, this 
        status boolean will be set to true. Like the _doZoomWindow flag, this flag will override the
        program's abaility to create geometry in favor of creating the mirror line.
        On the release of the right mouse button, if this boolean is set to true, the program
        will execute the mirror function and after completetion, will reset this variable back
        to false.
    */ 
    bool _doMirrorLine = false;
    
    //! A status flag to draw a selection box rectangle
    /*!
        When a user wants to select a group of geometry objects, this status flag will be set to true.
        Like the flags _doMirrorLine and _doZoomWindow, this will override the program's ability to
        create geometry objects. On the up release of the right mouse button, the program will
        check if this flag is true and if so, execute the necessary functions in order to select a group
        of geometry objects within the window. This flag will be set back to false upon the completetion 
        of this process
     */ 
    bool _doSelectionWindow = false;
    
    //! This is a status variable which will indicate to the program whether or not the user is creating nodes or block labels
    /*!
        This is the status varaible that the simulator uses in order to determine if the user will be creating nodes or block labels
        This variable does not effect the users abaility to select nodes or block labels. This variable is primarily used when the user
        presses down on the left mouse button. This variable will also effect what geometry is selected when the user performs a left up motion
        on the selection window. The variable is true when the user needs to create nodes and false when the user needs to create block labels
    */ 
    bool _createNodes = true;
    
    //! This is a status variable that will indicate to the program whether or not the user will create lines/arcs
    /*!
        This variable has the same function and purpose as the _createNodes variable except for this variable applies to lines and arcs.
        This variable effects whetehr lines or arcs are selected when the user performs a left down motion when creating a selection window
        This variable is true when the user whats to create lines and false when the user wants to create arcs
     */ 
    bool _createLines = true;
    
    //! A status variable which tells the program that nodes have been selected.
    /*!
        When a user clicks the right mouse button, if the mouse pointer is above a node, then the this variable 
        will be set to true to keep track of which geometry objects are selected. THis is helpful in functions such as
        mirroring geometry, translating geometry, and copying the geometry. This boolean will only be set to false when 
        all nodes are deselected or if another geometry is selected that is different from the nodes.
        Also, the selection window process will effect this variable
     */ 
    bool _nodesAreSelected = false;
    
    //! A status variable that tells the program that the user is selecting or has selected lines
    /*!
        For a detailed description, see the documentation for _nodesAreSelected. The purpose
        and function of this status variable is the same for the status variable _nodesAreSelected
    */ 
    bool _linesAreSelected = false;
    
    //! A status variable that tells the program that the user is selecting or has selected arcs.
    /*!
        For a detailed description, see the documentation for _nodesAreSelected. The purpose
        and function of this status variable is the same for the status variable _nodesAreSelected
    */ 
    bool _arcsAreSelected = false;
    
    //! A status variable that tells the program that the user is selecting or has selected block labels.
    /*!
        For a detailed description, see the documentation for _nodesAreSelected. The purpose
        and function of this status variable is the same for the status variable _nodesAreSelected
    */ 
    bool _labelsAreSelected = false;
    
    //! A status variable that tells the program that a mix of the geometry shapes has been selected.
    /*!
        For a detailed description, see the documentation for _nodesAreSelected. The purpose
        and function of this status variable is the same for the status variable _nodesAreSelected.
        However, this variable is set to true only if a mixture of geometry is selected. This would occur during the
        group selection process where the user creates a window where the endpoint is greater then the start point 
        in the x-direction. When a mix of geometry is selected, this variable becomes true.
    */ 
    bool _geometryGroupIsSelected = false;
    
    //! A status flag that is set to true for if a node is selected
    /*!
        This selection differs from the _nodesAreSelected variable becuase this status flag
        is set to true only when the user selects a node that is to be used for creating lines/arcs
     */ 
    bool _geometryIsSelected = false;
    
    wxRealPoint _startPoint;
    
    wxRealPoint _endPoint;
    
    OGLFT::Grayscale *_fontRender;
    
    double convertToXCoordinate(int xPixel)
    {
        return _zoomX * (((2.0 / (double)this->GetSize().GetWidth()) * ((double)xPixel - (double)this->GetSize().GetWidth() / 2.0)) / 1.0) * ((double)this->GetSize().GetWidth() / (double)this->GetSize().GetHeight()) + _cameraX;
    }
    
    double convertToYCoordinate(int yPixel)
    {
        return _zoomY * ((-(2.0 / (double)this->GetSize().GetHeight()) * ((double)yPixel - (double)this->GetSize().GetHeight() / 2.0)) / 1.0) + _cameraY;
    }
    
    double getTolerance()
    {
        return ((((_zoomX + _zoomY) / 2.0) / 25.0));
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
    
    void onMouseRightUp(wxMouseEvent &event);
    
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
    
    void setMirrorLineState(bool state)
    {
        _doMirrorLine = state;
    }
    
    bool getMirrorLineState()
    {
        return _doMirrorLine;
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
    
    void moveRotateSelection(double angularShift, wxRealPoint aboutPoint);
    
    void scaleSelection(double scalingFactor, wxRealPoint basePoint);
    
    void mirrorSelection(wxRealPoint pointOne, wxRealPoint pointTwo);
    
    void copyTranslateSelection(double horizontalShift, double verticalShift, unsigned int numberOfCopies);
    
    void copyRotateSelection(double angularShift, wxRealPoint aboutPoint, unsigned int numberOfCopies);
    
    void displayDanglingNodes();
    
    void createOpenBoundary(unsigned int numberLayers, double radius, wxRealPoint centerPoint, OpenBoundaryEdge boundaryType);
    
    //! pointOne is the point that for the boundaing box that is the highest left most point. Pointtwo is hte lowest right most point 
    void getBoundingBox(wxRealPoint &pointOne, wxRealPoint &pointTwo);
    
    void createFillet(double filletRadius);
    
private:
    wxDECLARE_EVENT_TABLE(); 
};

#endif