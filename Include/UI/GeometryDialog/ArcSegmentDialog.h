#ifndef ARC_SEGMENT_DIALOG_H_
#define ARC_SEGMENT_DIALOG_H_

#include <vector>
#include <string>
#include <iostream>
#include <iomanip>

#include <wx/wx.h>
#include <wx/textctrl.h>
#include <wx/stattext.h>
#include <wx/sizer.h>
#include <wx/combobox.h>
#include <wx/arrstr.h>
#include <wx/valnum.h>

#include <common/enums.h>
#include <common/ElectricalBoundary.h>
#include <common/MagneticBoundary.h>

#include <UI/geometryShapes.h>


//! Class that is used to create the dialog for creating a new arc
/*!
    This class is used to create the dialog when the user
    needs to create a new arc. THe dialog will contain text boxes
    to allow the user to enter in the arc angle and the number of
    segments that the arc will be composed of. This class
    will generate a wxID_OK event once the user
    presses ok.
    For documentation on the wxDialog class, refer to the following link:
    http://docs.wxwidgets.org/3.1.0/classwx_dialog.html
*/ 
class arcSegmentDialog : public wxDialog
{
private:

    //! The physics problem that the user has selected.
    /*!
        This variable is set in the constructor and is dependent on
        which boundary was passed into the constructor. This will cause 
        will help determine which boudnary list to operate on.
    */
    physicProblems _problem = physicProblems::NO_PHYSICS_DEFINED;

    //! Pointer pointing to the global electricl boundary list
    std::vector<electricalBoundary> *_localElectricalBoundaryList;
    
    //! Pointer pointing ot hte global magnetic boundary list. 
    std::vector<magneticBoundary> *_localMagneticBoundaryList;
    
    //! Text box used to modify the arc angle for the arc
    /*!
        For documentation on the wxTextCtrl class, refer to
        the following link:
        http://docs.wxwidgets.org/trunk/classwx_text_ctrl.html
    */ 
    wxTextCtrl *_arcAngleTextCtrl = new wxTextCtrl();
    
    //! Text box used to modify the number of segments that compose the arc
    /*!
        For documentation on the wxTextCtrl class, refer to
        the following link:
        http://docs.wxwidgets.org/trunk/classwx_text_ctrl.html
    */ 
    wxTextCtrl *_segmentTextCtrl = new wxTextCtrl();
    
    //! Combo box used to select the boundary that can be associated with arc
    /*!
        For documentation on the wxComboBox class, refer to
        the following link:
        http://docs.wxwidgets.org/trunk/classwx_combo_box.html
    */ 
    wxComboBox *_boundaryComboBox = new wxComboBox();
    
    //! This is a local arc shape that is will be edited
    /*!
        For new arcs, this will take on the values that the user
        selects. Once the user clicks on the ok button, this 
        variable will be returned in order to add it to the global
        arc list. For arcs that will be edited, this variable
        will take on any arc passed into the setArcParameter function
    */ 
    arcShape _localArcShape;
    
    //! Function that is called in order to update the interface
    /*!
        This function is called when the program sets the local arc shape from
        a selected arc. This function will update the text boxes and the combo
        boxes to match the current values of the selected arcs or the arc
        that was passed into the set arc parameter.
        This function is also useful for when the dialog needs to be cleared and updated
    */ 
    void updateInterface();
    
    //! Function that creates the dialog
    /*!
        This function will create the dialog from the
        variables setup in the constructor
    */ 
    void createDialog();
    
public:
    //! Constructor for the class
    /*!
        This constructor will setup the dialog for an electrical simulation
    */
    arcSegmentDialog(wxWindow *par, std::vector<electricalBoundary> *list);
    
    //! Constructor for the class
    /*!
        This constructor will setup the dialog for magnetic simulation
    */
    arcSegmentDialog(wxWindow *par, std::vector<magneticBoundary> *list);
    
    //! Function that is used to clear the local arc class
    /*!
        This function will reset the local arc object
        back to default parameters
    */ 
    void clearParameter();
    
    //! Function that is called to set the local arc object to the shape
    /*!
        This function will set the local arc shape to the shape passed
        into the function
        \param shape The arc shape that the user will be editing in the dialog
    */ 
    void setArcParameter(arcShape shape);
    
    //! Function that retrieves the local arc shape
    /*!
        This function will return the local arc shape by placing
        the arc parameters into an arc shape geometry object 
        specified by the user
        \param shape The arc shape that the user would like to place the 
                    local arc shape into
    */ 
    void getArcParameter(arcShape &shape);
};

#endif