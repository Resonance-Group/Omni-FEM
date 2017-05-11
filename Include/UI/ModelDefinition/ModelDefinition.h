#ifndef MODELDEFINITION_H_
#define MODELDEFINITION_H_

#include <vector>
#include <algorithm>
#include <string>
#include <math.h>
#include <sstream>

#include <glew.h>
#include <freeglut.h>

#include <wx/wx.h>
#include <wx/gdicmn.h>
#include <wx/statusbr.h>

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
    
    //! A pointer to the status bar of the main window
    /*!
        This variable is primaliry used in order to update the text of the coordinate
        location of the mouse. This is the address of the main frame status bar
    */ 
    wxStatusBarBase *_statusBarTopWindow;
    
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
    
    //! This variable specifies the starting point of the a mirror line/zoom window/selection box
    /*!
        This variable is only used when the user would creates a mirror line, a zoom window box, or a selection box.
        This variable is not updated when the mouse moves over the canvas. The variable is first set to a value when the user
        presses down on the left mouse button. After this, the variable is set. When the mouse moves over the canvas,
        the _endPoint variable is updated. After a mirror,zoom window, or selection box function has been executed,
        the variable is reset back to the point (0, 0). The datatype is wxRealPoint becuase this stores the coordinate position
        of the mouse for the graph instead of the pixel coordinate.
    */ 
    wxRealPoint _startPoint;
   
    //! This variable specifices the end point of a mirror line/zoom window/selection box.
    /*!
        The purpose of the variable is to store the end point of a mirror line/zoom window/selection box.
        The variable is updated whenever the mouse is moved across the canvas. At the conclusion of the function
        executing either the mirror line/zoom window box/selection box, this variable is reset back to (0, 0). Again,
        the datatype is a wxRealPoint becuase this stores the coordinate position inside of the variable.
        \sa _startPoint
    */ 
    wxRealPoint _endPoint;
    
    //! The variable that contains all of the related functions for font render
    /*!
        The instance of the font rendering engine OGLFT. This handles all of the importing of the fonts and the 
        actual rendering of the font. For documentation regarding the OGLFT library, refer to the following link:
         
        http://oglft.sourceforge.net/
    */ 
    OGLFT::Grayscale *_fontRender;
    
    //! A function that converts the x pixel coordinate into a cartesian/polar coordinate
    /*!
        This function takes into account the _zoomX parameter and the _cameraX parameter. This fucntion also takes into account the aspect ratio of the screen
        in order to properly size the gird. In simple form, we multiply the pixel value by two and then divide by the screen width. Subtract the result by 1 and multiply
        this result by the aspect ratio and the zoom factor. Last, we add in the camera offset in order to obtain the mappping between the pixel coordinate plane and 
        the cartensian coordinate plane. The reason that this function works with the polar form is that the mapping is exactly the same; hwoever, the meaning of the 
        coordinate value has changed from cartesian to polar coordinate.
        \param xPixel The pixel value that needs to be converted into the cartensian plane. This is for the x-plane and ranges from 0 to the screen width.
        \return Returns the cartensian/polar coordinate of the pixel value.
    */ 
    double convertToXCoordinate(int xPixel)
    {
        return _zoomX * (((2.0 / (double)this->GetSize().GetWidth()) * ((double)xPixel - (double)this->GetSize().GetWidth() / 2.0)) / 1.0) * ((double)this->GetSize().GetWidth() / (double)this->GetSize().GetHeight()) + _cameraX;
    }
    
    //! A function that converts the y pixel coordinate into a cartesian/polar coordinate
    /*!
        This function performs the same way as the convertTOXCoordinate function. Except that this function does not take into account of the 
        aspect ratio since this is already taken into account by the convertToXCoordinate function. The math is a little reversed compared to the math
        for the convertToXCoordinate. Mathmatically speaking, this function will subtact the result of multipling the yPixel value by the half of the
        the canvas height from 1. Then multiply this result by the zoom Y factor and add in the camera Y offset.
        \param yPixel The pixel value that needs to be converted to the cartesian/polar plane. this is for the y-plane and ranges from 0 to the canvas height.
        \return Returns the cartesian/poalr coordiante of the y pixel value.
        \sa convertToXCoordinate
    */
    double convertToYCoordinate(int yPixel)
    {
        return _zoomY * ((-(2.0 / (double)this->GetSize().GetHeight()) * ((double)yPixel - (double)this->GetSize().GetHeight() / 2.0)) / 1.0) + _cameraY;
    }
    
    //! A function that will calculate the tolerance value used for selecting geometry shapes and creating the geometry
    /*!
        The tolerance is an imaginary buffer that gives the user a region in order to select a shape. The tolerance
        is also used in creating geometry. When a geometry shape is created (this primarily pertains to the block labels and nodes) 
        the program needs to make sure the the geomety is not created too close to another geometry in order to avoid convergence issues.
        The simulator uses this function in order to properly determine the "Keep out" area for the block labels and nodes.
        \return The function will return the tolerance value that reprents the width of the area that is either keep out or selectable.
    */
    double getTolerance()
    {
        return ((((_zoomX + _zoomY) / 2.0) / 25.0));
    }
    
    //! A function that will clear the selection of any selected geometries
    /*!
        The function will first check the state of the variables: _createNodes, _labelsAreSelected, _createLines, _arcsAreSelected, and _geometryGroupIsSelected.
        If the _createNodes flag is set to true, then the program will only loop through the entire node list and set the select status of the node to false.
        Same thing appplies to the _labelsAreSelected, _createLines, and _arcsAreSelected. Except they will effect their respectivey geometry shapes.
        If _geometryGroupIsSelected is set to true, then the program will loop through all geometry lists and deselect the geometry shape.
        The function will also set the variables _createNodes, _labelsAreSelected, _createLines, _arcsAreSelected, and _geometryGroupIsSelected to false 
        no matter what flag is set to true at the conclusion of the function
    */ 
    void clearSelection();
    
    //! Function that is called in order to update the user's view
    /*!
        Every time onPaintCanvas is called, this function is executed.
        This function will update the user's view of the scene.
        First, we size the viewport to be equal to the canvas height and width.
        Next, we clear the projection matrix and reset it according to the aspect ratio and the zoom factor.
        Lastly, we clear the modelmatrix and then shift the matrix according to the camera offset
     */ 
    void updateProjection();
    
    //! Function that will draw the grid on the screen. The grid consists of the grid markings, the grid axis, and the center.
    /*!
        This function will draw the grid markings, the axis for the grid along with the cneter crosshair in order to display where (0, 0)
        is for the frid. All of these are controlled by the user preference. For the grid preference, the function checks the variable
        _preferences in order to determine what should be drawn.
      
        Drawing the crosshair for the center point and drawing the axis is quite straight forward. Both function in a similiar manner.
        At the top of the drawGrid function, the coordinate min and max of the screen width and height is computed. Using the 4 numbers,
        the program is able to create the axis line. Where the x-axis line extends from 0 to the width of the canvas and the y-axis line
        extends from 0 to the height of the canvas. The min and max values are effected by the zoom and translation factors. In fact, 
        if you are to recompile the project with the glOrtho2D scaled to double what the code states, you will end up seeing the 
        grid axis move and zoom with the user. The reason the lines are not drawn on the screen when the user pans or zooms past the grid
        lines is that for both the x and y axis lines, neither take the other into account. For example, when the x line is drawn, the y value
        is zero and when the y-axis line is drawn, the x value is zero.
        
        Drawing the grid markings is not as straight forward. First, we check to see if the user has zoomed out toom much. If this is the 
        case, then the grid will be too dense for us to really see anything so don't bother to draw the grid. Next, we create the grid markings
        for the y-axis by calculating the number of times we need to loop through the code. For every 4th iteration, we need to draw the line 
        more bold in order to desginate this as a minor axis line. The program repeats this operation for the x-axis.
 
        \sa _preferences
    */ 
    void drawGrid();

    //! This function will take an x coordinate value and a y coordinate value and round the two values to the nearest grid marking
    /*! For the sake of the explanianation, imagine we are working with
        a 1D problem and that the point is between two grid markings.
        First, the program finds the modulus of the coordinate / gridStep.
        What this tells the program is the "distance" from the lower grid makeing to the point.
        If the point is beyond the halfway "mark" of two grid markings, the modulus will return a number 
        greater then gridStep / 2. If the point is below the halfway "mark",
        the program will simply take the point coordinate and subtract out the modulus.
        And this is the rounded answer.
        If the point is beyond the halfway "mark", the program will add the gridstep to the 
        point and then subtract out the modulus.
        For example, if a point is at 0.40 and the grid step size is 0.25, then the point 
        is between 0.25 and 0.5. The modulus of 0.40 % 0.25 will be 0.15. Since this is 
        greater then 0.25 / 2 = 0.125 (the halfway mark), we need to add 0.25 to 0.40 (0.25 + 0.4 = 0.65)
        Subtracting the modulus of 0.15 yeilds 0.5. The correct number to round 0.4 up to.
        The two parameters are passed in by reference.
        \param xCoordinate The x coordinate of a point that will be rounded to the nearest grid marking
        \param yCoordinate The y coordinate of a point that will be rounded to the nearest grid marking
    */ 
    void roundToNearestGrid(double &xCoordinate, double &yCoordinate);
    
    //! This is the event that is fired when the canvas is drawn or re-drawn
    /*!
        A very important function. Inside this function is all of the draw calls for the canvas.
        The canvas is redrawn by calling the function this->Refresh(). This will effectively 
        post a paintevent to the event handler which the computer will execute then this function.
        First, the function must set the context. This simply redirects all openGL commands to the canvas.
        Next, we need to create an instance of the wxPaintDC object becuase we are drawing to a canvas inside
        of an event procedure (For more documentation regarding the wxPaintDC class, refer to the following link:
        http://docs.wxwidgets.org/trunk/classwx_paint_d_c.html)
        Next, the program switches to the modelMatrix and deletes everything.
        Then, update the projection and draw the grid. The program will then loop through the entire
        node/line/arc/and label list and call their corresponding draw function to draw them on the canvas.
        For the label name that is displayed, it is required that the program pass the variable _fontRender into the draw call
        so that the function has access to all of the glyphs for drawing the text onto the screen.
        The function that actually draws everything to the screen is SwapBuffers().
        \param event A requirded event datatype needed for the event table to post the event function properyl and to route the event procedure to the correct function.
    */ 
	void onPaintCanvas(wxPaintEvent &event);
    
    //! The function that is called when a resize event occurs
    /*!
        Typically, a resize event occurs when the user resizes the main frame. In this case,
        the canvas needs to be resized with the main frame and in order to maintain consistency.
        This function handles the resize event for the canvas.
        For more documentation regarding the wxSizeEvent class, refer to the following documentation:
        http://docs.wxwidgets.org/3.1.0/classwx_size_event.html
        \param event A requirded event datatype needed for the event table to post the event function properyl and to route the event procedure to the correct function.
    */ 
    void onResize(wxSizeEvent &event);
    
    //! The event procedure that is executed every time the user moves the mouse wheel.
    /*!
        This function will query the GetWheelRotation from the event variable. This will determine if the mouse wheel moved counter-clock-wise or
        clock-wise. Depending on the status of getMouseZoomReverseState, a counter-clockwise motion will cause the canvas to zoom in and a clockwise rotation
        will cause the canvas to zoom out. If getMouseZoomReverseState is true, then the operation is reversed. The program changes the zoom variables (_zoomX and _zoomY)
        by a factor that is computed by 1.2^(GetWheelRotation/150). This value is multuplied by the current zoom factor (for x and y). The program will ensure that
        both zoom factors are equal to each other. If a user zoom windowed to a particular location, when the user zooms in or out of that location, the program 
        will reset the zoom factors back to equal to each other. The program will also calculate a small offset and add/subtract this from the _cameraX and _cameraY
        variables. This allows the program to pan towards/away from the current mouse position as the program is zooming in/out.
        \sa _cameraX, _cameraY, _zoomX, _zoomY
        \param event This variable is required for the event procedure to work properly. When called from the event table, this variable contains the datatype to retrieve how much the user rotated the mouse wheel
    */ 
    void onMouseWheel(wxMouseEvent &event);
    
    //! This is the function that is executed when the user moves the mouse pointer across the canvas
    /*!
        This is executed every time the user moves the mouse pointer across the canvas. THe program will check a series of status flags 
        and execute accordingly. The first flag that it checks is to see if the middel mouse button (the wheel button) is pressed down.
        This indicates that tehe user woudl like to pan across the canvas. Based on the change of pixels from the last event to the next,
        the program will calculate the shift for the _cameraX and _cameraY variables. The variables, _mousePixelX and _mousePixelY, store the
        last position of the mouse (in pixel units). The current position X and Y mouse pixels can be obtained from the function GetX() and GetY() located
        in the wxMouseEvent class. 
        If the middle mouse button is not pressed, the program will check to see if the left mouse button is pressed at the time that the mouse moved
        If so, the program will check if the canvas is to move a draggingNode/label or to update the position of the _endPoint becuase the user
        is drawing a mirror line or a selection window. 
        If the left mouse button is not pressed and the user has the right mouse button down when moving the mouse, the program will update the
        value of _endPoint variable. This occurs only if the program is in the mode to draw a selection window.
        Once the program is finished executing, the program will force the canvas to refresh the screen
        \sa _cameraX, _cameraY, _endPoint
        \param event This variable is required for the event procedure to function properly. The wxMouseEvent class stores the current mouse positon and the information needed to determine what mouse button is pressed at the time that the event is fired.
    */ 
    void onMouseMove(wxMouseEvent &event);
    
    //! Function that is executed everytime the user presses down on the left mouse button
    /*!
        This function is performing a number of different options. The primary function of this function
        is to add the geometry to the list. It does by checking the status _createNodes and _createLines and the position.
        This function will also initilize the _startPoint when in zoom window mode or when creating a mirror line
        When a down click occurs, the function will check if the booleans _doZoomWindow and _doMirrorLine are set to false.
        The function will check if the user wants to create nodes by checking if _createNodes is set to true.
        If so, the function will then scan through the entire node list and check if the mouse pointer is within the clickable area of the node.
        If so, the program will then save this node iterator. The saving function will return true if there are 2 iterators that
        have been saved. If the return is true, the program will check the boolean _createLines. If _createLines is true, the program
        will create a line between the two saved points. If false, the program will create an arc between the two points. The arc creation occurs
        later in the code becuase the code is designed to refresh the canvas such that both selected nodes are colored selected for the user's sake.
      
        If the user did not click on an area containing a node, then the program will add in a dragging node. This dragging node overrides 
        all checks for a node and is simply used as a display to show the user where they are dragging the node to. The actual node is created 
        in the function omMouseLeftUp.
      
        If _createNodes is false, this means that the user would like to create a dragging block label. Which the program will perform.
        \sa _createNodes, _createLines, onMouseLeftUp
        \param event This variable is required in order for the event table to properly route the event to the function.
    */ 
    void onMouseLeftDown(wxMouseEvent &event);
    
    //! Function that is responsible for adding the real block/node to the list
    /*!
        After the user has positioned the block label or node, when the user releases the button on the mouse
        this function is called. First, the function will check if both _doZoomWindow and _doMirrorLine are false.
        if so, the function will check if the user wants to create nodes or block labels by checking if _createNodes is true.
        If true, the function will delete the dragging node and add in the node with all of the checking (checking for intersections). The fucntion will also round the
        node to the nearest grid marking if the user wants to snap to the grid.
        If the user is creating block labels, then the function will do the same thing as the node except with block labels.
        However, if _doZoomWindow or _doMirrorLine are true, then the function execute their respective functions and set the _startPoint
        and _endPoint back to (0,0) and set _doZoomWindow or _doMirrorLine to false.
        \sa _doMirrorLine, _doZoomWindow, _createNodes
        \param event This variable is required in order for the event table to properly route the event to the function.
    */ 
    void onMouseLeftUp(wxMouseEvent &event);
    
    //! Function that is called when then user presses down on the mouse right button
    /*!
        This function begins the geometry selection processes. The program sets _startPoint and _endPoint equal to
        the current position of the mouse. If snapping grid is on, then the program will round the mouse position to the
        nearest grid position. The function will also set _doSelectionWindow to true.
        \sa _startPoint, _endPoint, _doSelectionWindow
        \param event This variable is required in order for the event table to properly route the event to the function.
    */ 
    void onMouseRightDown(wxMouseEvent &event);
    
    //! The function that is called when the user releases the right mouse button
    /*!
        This function completes the geometry selection process. First, the function will check if the current mouse position 
        is equal to the mouse position when the user started the process. If so, this could mean that the user selected an individual geometry
        shape. The function will then perform a series of checks to determine which geometry shape the user could have selected. This is 
        based on the distance between the geometry shape and the mouse pointer. If the user did click on a geometry shape, then the
        function will loop through all the other geometry lists and de-select any shapes that are not already selected (this only
        applies to the shapes that are different then the one selected). If the user clicked on a whitespace, then the function will
        de-select all geomerty shapes.
      
        If the variable _endPoint is greater then _startPoint on the y-plane but less then _startPoint on the x-plane, then 
        this would indicate that the user wants to select only nodes/block labels. This is determined by the variable _createNodes. If 
        true, then the user will select all ndoes within the box the user drew. If false, then the user will select the block labels.
        The program will always select a new group of nodes/labels. If the user would like to select an addiditonal set of nodes/labels,
        the the CTRL button must be pressed down. This logic applies to the lines/arcs. This function keeps a static count of all of the 
        selected geometry. This may be removed one day.
      
        To select a grouping of lines/arcs, the _endpoint variable must be less then _startPoint on the x and y-plane. The same
        logic applies for as above for the node/labels except the function will be looking at _createLines. However, in order to select a line/acr, 
        only one of the endpoints needs to be in the selection box.
      
        In order to select all of the geometry, the _endpoint must be greater then _startPoint on the x-plane. The y-plane is not looked at.
        In this mode, all of the geometry wll be selected and operated on. This would be mixed geometry mode. Again, the same logic as the
        nodes/labels applied to the mixed geometry where the user needs to have CTRL down in order to add to the curretn selection. In this mode,
        in order for a line/arc to be selected, both nodes need to be in the selection window.

        After executing, _doSelectionWindow is false.
      
        \sa onMouseLeftUp, _createNodes, _createLines
        \param event This variable is required in order for the event table to properly route the event to the function. This variable also contains the current pixel coordinate of the mouse.
    */ 
    void onMouseRightUp(wxMouseEvent &event);
    
    //! The function that is called in order to implement the zoom window functionality.
    /*!
        This function is called after the user release from the left mouse button and the _doZoomWindow is true.
        First, we determine the center point of the zoom window. Later, the openGL matrix will be equal to this offset.
        Next, the function determines what the viewport bounds are based on the middel point and the location of _startPoint and _endPoint.
        After execution, _doZoomWindow is false.
    */ 
    void doZoomWindow();
    
public:
    //! This is the constructor for the class
    /*!
        The constructor will initilize some of the private variables. Inside, the program sets up the openGL state machine and
        also initilizes the datatype that holds the font
        \param par A pointer to the parent window
        \param point The point on the parent window where the top left corner will be placed
        \param size The initial size of the canvas
        \param definition This is a reference to the global problem definition
        \param statusBar A reference to the parent status bar
    */ 
    modelDefinition(wxWindow *par, const wxPoint &point, const wxSize &size, problemDefinition &definition, wxStatusBarBase *statusBar);

    //! This function will update the _preferences with a new user defined preferences
    /*!
        This function is primarly used when the user needs to change something in the grid preferences object.
        \sa _preferences
    */ 
    void setGridPreferences(gridPreferences &preferences)
    {
        _preferences = preferences;
        this->Refresh();
    }
    
    //! Retrieves the grid preferences object for editing.
    /*!
        \sa _preferences
        \return Returns a pointer pointing to the location of the grid preferences object
    */ 
    gridPreferences* getGridPreferences()
    {
        return &_preferences;
    }
    
    //! This function will set the state of the create node flag equal to the value of state
    /*!
        \sa _createNodes
        \param state True or False value indicting if the create node flag should be true or false. True if the user wants to edit nodes. Otherwise false if the user needs to edit block labels
    */ 
    void setCreateNodeState(bool state)
    {
        _createNodes = state;
    }
    
    //! This function will set the state of the create line flag equal to the value of state
    /*!
        \sa _createLines
        \param state True or False value indicting if the create line flag should be true or false. True if the user wants to edit lines. Otherwise false if the user needs to edit arcs
    */ 
    void setCreateLinesState(bool state)
    {
        _createLines = state;
    }
    
    //! Returns the value of the create node flag
    /*!
        \sa _createNodes
        \return Returns true if the user wants to edit nodes. False if the user wants to edit block labels
    */
    bool getCreateNodeState()
    {
        return _createNodes;
    }
    
    //! Returns the value of the create line flag
    /*!
        \sa _createLines
        \return Returns true if the user wants to edit lines. False if the user wants to edit arcs.
    */ 
    bool getCreateLineState()
    {
        return _createLines;
    }
    
    //! Sets the state of the zoom window flag to the value of state
    /*!
        \sa _doZoomWindow
        \param state Set to True if the canvas needs to execute a zoom window routine
    */ 
    void setZoomWindow(bool state)
    {
        _doZoomWindow = state;
    }
    
    //! Gets the state of the zoom window flag
    /*!
        \sa _doZoomWindow
        \return Returns True if the canvas is in zoom window mode. Otherwise, returns false.
    */ 
    bool getZoomWindow()
    {
        return _doZoomWindow;
    }
    
    //! Sets that state of the mirror flag equal to the value provided in state
    /*!
        \sa _doMirrorLine
        \param state True if the user wants the program to perform a mirror operation on selected geometry pieces. Otherwise false
    */ 
    void setMirrorLineState(bool state)
    {
        _doMirrorLine = state;
    }
    
    //! Gets the state of the mirror flag
    /*!
        \sa _doMirrorLine
        \return Function returns true if the program is in the process of performing a mirror operation. Otherwise false.
    */ 
    bool getMirrorLineState()
    {
        return _doMirrorLine;
    }
    
    //! Will cause the canvas to zoom in by a pre determined factor.
    /*!
        This function will zoom in by a pre determined factor. This factor was determined by experimentation.
        The function will zomm in towards the center of the current position of the screen.
    */ 
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
    
    //! Will cause the canvas to zoom out by a pre determined factor.
    /*!
        This function will zoom out by a pre determined factor. This factor was determined by experimentation.
        The function will zomm out away from the center of the current position of the screen.
    */ 
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
    
    //! This function is called when the user needs to deleted any of the selected geometry
    /*!
        No matter what, this function will scan through all of the node/labels/arc/lines lists to see if any are selected.
        This may seem time consuming but in a test with 1000 lines and 2000 nodes, the delete operation was not hindered by this large amount
        If there are any nodes selected, the program will scan through the entire line and arc list to determine what line(s) and/or arc(s) the 
        node is apart of. For any lines or arcs that the node is connected to, the progam will mark these for deletion.
      
        For all geometry shapes, if the last geomety shape is selected in its respective list, then the program will immediately break out of the loop.
        This idea also extends to the case if there is only one geometry shape in its respective list.
        The for loop does not automatically increment the iterator but rather, this is done outside of the for loop. It was discovered that
        during an erasing operation, the iterator would become invalidated and incrementing an invalid iterator would cause the value to be 
        in an unknown state. It was decided to increment the iterator in the loop itself. When the iterator is to be erased, the program
        first increments the iterator and then erases the previous iterator. This prevents any invalidated errors from occuring.
    */ 
    void deleteSelection();
    
    //! This will allow the user to edit the settings for the selected node(s)/label(s)/arc(s)/line(s).
    /*! 
        Depending on the state of the nodes selected flag and the lines selected flag and the labels selected flag and the 
        arcs selected flag, this function will scan through the apprioate geometry list to find the first selected geometry.
        Once found, the program will extract the cooresponding property and display for the user to edit. It is done this way 
        because if the user selected a set of nodes, for example, then it doesnt really matter from which node the program
        pulls the settings since after execution all of the selected nodes will contain the same proprety. This is the case for 
        all geometry shapes. 
      
        In the event that the user selects mixed geometry, the user can only change the group that the geomety shapes belong to.
        Again, the program will scan through all of the lists to find the first selected shape, starting with the node list first.
        Once the property has been set, the program will scan through all lists and any geometry shapes selected, the program will
        set the group number as specified by the user.
    */ 
    void editSelection();
    
    //! If a properties name is changes or if the property is deleted, this will reset the properties
    void updateProperties(bool scanConductorProperty, bool scanNodalProperty, bool scanBoundaryProperty, bool scanMaterialProperty, bool scanCircuitProperty);
    
    //! Selects a group of geometry objects based on their group ID (speciffied by groupNumber).
    /*!
        Depending on the value of geometry, this function will select all of the nodes or lines or labels or arcs
        that have the same goup ID as groupNumber. If a mixed geometry is needed to selected, then this function
        will scan through all lists to select all of the nodes/labels/lines/arcs that contain the same group ID as
        groupNumber
        \sa EditGeometry
        \param geometry This arguement determines which geometry shape to select. Or if a all of the geomtry should be selected.
        \param groupNumber Specifies which group ID that should be selected
    */ 
    void selectGroup(EditGeometry geometry, unsigned int groupNumber);
    
    //! This function will move any selected geomtry by the units of horizontalShift for the x-plane and verticalShift for the y-plane
    /*!
        THe program will first check if a mixed geomrty selection occured. If not, the function will then check the lines are selected flag. If not, 
        the program will check if the arcs are selected flag is set. For both lines and arcs, the program will iterate through the entire arc/line list 
        and for the arcs/lines that are selected, the program will then select the corresponding nodes. The function mainly deals with moving the nodes.
        By moving the node, you move the arc/line along with it. Once done with this section, the program will deselect all lnies/arcs.
      
        If the mixed geometry is selected, then the program will loop through all of the line and arc lists and move any corresponding nodes. If the node is selected, then the node
        will be moved. If not, then the node will not be moved. If the node is shifted, then the program will deselect the node to enusre that it does not get shifted
        a second time.
      
        The program will then check if the labels are selected flag is set or if the mixed geometry flag is set. If so, the program will shift any selected labels
      
        Lastly, the program will loop the node list and shift any remaining selected nodes for a mixed geometry. This section is alos able to handle
        if nodes are just selected.
        
        At the end of the function, the program will scan through the node and arc and line lists to check if there are any intercetions with the 
        geomtry. If so, handle accordingly.
        \param horizontalShift Arguement that specifies how much to move the selected geometry by in the x-plane
        \param verticalShift Arguement that specifies how much to move the selected geomtry by in the y-plane
    */ 
    void moveTranslateSelection(double horizontalShift, double verticalShift);
    
    //! Function that will rotate any selected goemtry by angularShift units about the point aboutPoint
    /*!
        The logic for this function follows the logic for the function moveTranslateSelection.
        However, instead of adding to the center of a node, this function calculates a new center
        based on the anfular shift and the current position of the node and the point which to rotate
        about and sets the node's center to the newly calculated center.
        The forumla that calculates the new center was inspired by the following stackoverflow post:
        http://stackoverflow.com/questions/14842090/rotate-line-around-center-point-given-two-vertices
        \param angularShift The angle to shift the geometry by in degrees
        \param aboutPoint The center point of the angular shift
    */
    void moveRotateSelection(double angularShift, wxRealPoint aboutPoint);
    
    //! This function will move any selected geometry away from a point by a given distance which is based on the scalingFactor arguement
    /*!
        For any lines or arcs selected, the function will select the nodes, set the selected nodes flag and unset the select arc/line flag then 
        the function will call itself.
        The function will then move the nodes away from a point given by basePoint. THe amount that the node is moved by is determined
        by the argument scalingFactor and the relationship is linear.
        In most cases, basePoint is equal to the center all selected geometry shapes. This is determined by the bounadign box which 
        can be obtained by calling the function getBoundingBox
        \sa getBoundingBox
        \param scalingFactor The factor by which to scale the distance between the selected geometry by
        \param basePoint The center point of the scaling
    */ 
    void scaleSelection(double scalingFactor, wxRealPoint basePoint);
    
    //! This function will mirror any selected geometry across a line defined by pointOne and pointTwo
    /*!
        This function takes into account the 3 different cases of a mirror. On the canvas, the user draws a mirror line.
        The 3 cases this mirror line can have are vertical, horizontal, and diagonal. For each geometry shape, these 3 cases
        must be taken into account. The program will first calculate the slope of the mirror line. The slope will determine
        which of the three cases the user created.
      
        Mirroring nodes and labels are relatively simple. First, the program will calculate the y-intercept of the mirror line.
        Next, the program will calculate the perpendicular slope of the mirrored point. Then the program will calculate the 
        y-intercept of the of the line that the mirrored point is on. Lastly, the progam will caluclate the point where the 
        two lines cross and from there, we can calculate the distance between the node and the intersection. By knowing
        this distance, the mirrored point will have the same distance.
      
        For lines and arcs, the calculation is a little more invovled. The process described above is applied to both end points
        of the line/arc.However, the program will automatically select the two mirrored points in order to draw a line between
        them. IF the node already exists, then the program will scan through the entire node list and select the existing node.
      
        All properties of the node/line/label/arc is copied over to the mirrored geometry.
        \param pointOne The first point of the mirror line. This is not a pixel coordinate.
        \param pointTwo The second point of the mirror line. This is not a pixel coordinate
    */ 
    void mirrorSelection(wxRealPoint pointOne, wxRealPoint pointTwo);
    
    //! Fucntion that will perform a linear copy specified by horizontalShift and verticalShift.
    /*!
        This function will create numberOfCOpies number of copies in a more linear fashion. The logic follows that 
        of the function moveTranslateSelection except there is a for loop whose limit is governed by numberOfCopies.
        This for loop will determine the position of each node. For lines and arcs, the creation of a new line/arc 
        for a copy follows the logic in mirror selection. Where the program will create a node, select this node and copy any 
        nodal properties from the master shape to the newly create node, create a second and perform the same steps as the first 
        one, and lastly, create the arc/line connecting the two nodes together. All segment properties is copied over from the master
        line/arc to the newly created line/arc. If the endpoint already exists, then the program will loop through
        the entire node list to find the endpoint and select it for line/arc creation.
        \sa mirrorSelection, moveTranslateSelection
        \param horizontalShift The x-plane distance between the new geometry shapes (and the distance between the master shape and the newly created one).
        \param verticalShift The y-plane distance between the new geometry shapes (and the distance between the master shape and the newly created one).
        \param numberOfCopies This is the number of copies that need to be made.
    */ 
    void copyTranslateSelection(double horizontalShift, double verticalShift, unsigned int numberOfCopies);
    
    //! The function that will copy geometry shapes around a point defined by aboutPoint
    /*!
        The copy logic follows that of copyTranslateSelection. However, the function will rotate the copied 
        shapes by the angularShift. The rotational logic is similiar to that of moveRotateSelection.
        \sa copyTranslateSelection, moveRotateSelection
        \param angularShift The angular distance between each newly copied shape (This is also the angular distance between the master shape and the first copied shape) in degrees
        \param aboutPoint The center point to perform the rotate copy
        \param numberOfCopies This is the number of copies that need to be made.
    */ 
    void copyRotateSelection(double angularShift, wxRealPoint aboutPoint, unsigned int numberOfCopies);
    
    //! The function that will select any dangling nodes.
    /*!
        A node is considered dangling when the node does not form a closed boundary.
        This occurs if there is just 1 line or arc connected to the node.
        This function will go through the entire node list and highlight any nodes
        that only have 1 arc or line connected to it
    */ 
    void displayDanglingNodes();
    
    //! The function that will create a circular boundary with layers
    /*!
        This function will loop through numberLayers number of layers and create a series con concentric circles about the centerPoint.
        the number of concentric circles that are created is numberLayers + 1. This function will automatically place the node point and
        select the node point for arc generation. If the node point already exists, the program will scan through the entire list 
        and select the node for arc creation. The program will also automatically create new materials to fit the boundary and place the 
        block label automatically. All block labels are designed to fit between 0 - 90 deg and will be staggered. For the arcs, the arc
        is broken into 50 pieces. For a DIRICHLET boundary condition, the program will create a new boundary condition called 
        V (or A)=0 and set it to the newly created arc. 
        \param numberLayers This will determine how many boundary layers are created
        \param radius The distance from the first layer to centerPoint
        \param centerPoint The center of the open boundary
        \param boundaryType The type of boundary that this open boundary will be.
    */ 
    void createOpenBoundary(unsigned int numberLayers, double radius, wxRealPoint centerPoint, OpenBoundaryEdge boundaryType);
    
    //! A function that will determine the box the bounds any selected geometry
    /*!
        No matter what geoemtry is selected, the program will first scan through any of the selected geomety, look at the node points and
        give the pointOne and pointTwo an initial value of the first selected node (either selected by user or selected becuase of a 
        corresponding line or arc). Next, the program will loop through the node list and determine which combination
        creates the highest point of the bounding box (which is the highest left most point) and the lowest (which is the lowest right
        most point. If arcs or lines are selected, then the program will look at their corresponding end points to determine 
        the highest and lowest point.
      
        Once found, the highest point will become pointOne and the lowest point will become pointTwo
        \param pointOne This is a returned value that is the highest left most point of the bounding box
        \param pointTwo This is a returned value that is the lowest right most point of the bounding box
    */ 
    void getBoundingBox(wxRealPoint &pointOne, wxRealPoint &pointTwo);
    
    //! Intermediate function call that is used to call the function geometryEditor2D::createFillet(double radius)
    /*!
        \param filletRadius A positive real number that specifies what the radius is of the fillet
    */ 
    void createFillet(double filletRadius);
    
private:
    //! This is a macro in order to let wxWidgets understand that there are events within the class
    wxDECLARE_EVENT_TABLE(); 
};

#endif