#ifndef OPENBOUNDARYDIALOG_H_
#define OPENBOUNDARYDIALOG_H_

#include <wx/wx.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/combobox.h>
#include <wx/string.h>
#include <wx/arrstr.h>
#include <wx/valnum.h>

#include <common/enums.h>


//! Dialog used to create the open boundary
/*!
    This class is used to create the dialog needed for the 
    user to input the parameters on creating an open boundary.
    When the class returns a wxID_OK, this means that the
    user wants to create the open boundary.
    For additional documentation on the wxDialog
    class refer to the following link:
    http://docs.wxwidgets.org/3.1.0/classwx_dialog.html
*/ 
class openBoundaryDialog : public wxDialog
{
private:

    //! Text box used to input the number of layers for the open boundary
    /*!
        The maximum number of layers that can be created is 12. 
        After 12, the increase in the number of layers will not effect
        the result of the simulation too much.
        Note that one layer consists of 2 concentric circles.
        For documentation on the wxTextCtrl class, refer to
        the following link:
        http://docs.wxwidgets.org/trunk/classwx_text_ctrl.html
    */ 
    wxTextCtrl *_numberLayersTextCtrl = new wxTextCtrl();
    
    //! Text box used to input the radius of the open boundary
    /*!
        The radius is the distance between the center point
        and the first layer that is created
    */ 
    wxTextCtrl *_radiusTextCtrl = new wxTextCtrl();
    
    //! Text box used to enter in the center X-point of the open boundary
    /*!
        For documentation on the wxTextCtrl class, refer to
        the following link:
        http://docs.wxwidgets.org/trunk/classwx_text_ctrl.html
    */ 
    wxTextCtrl *_horizontalCenterTextCtrl = new wxTextCtrl();
    
    //! Text box used to enter in the center Y-point of the open boundary
    /*!
        For documentation on the wxTextCtrl class, refer to
        the following link:
        http://docs.wxwidgets.org/trunk/classwx_text_ctrl.html
    */ 
    wxTextCtrl *_verticalCenterTextCtrl = new wxTextCtrl();
    
    //! Combo box used to select the boundary condition of the open boundary
    /*!
        Currently, the user can only select between Dirichlet boundary condition and
        Neumann boundary condition.
        For docmentation on the wxComboBox class, refer to the following link:
        http://docs.wxwidgets.org/trunk/classwx_combo_box.html
    */ 
    wxComboBox *_edgeTypeComboBox = new wxComboBox();
    
public:

    //! Constructor of the class
    /*!
        The contrustor of the class will create the
        dialog box and place all of the widgets into
        their corresponding places
        \param par Pointer to the parent window
    */ 
    openBoundaryDialog(wxWindow *par);
    
    //! Retrieves all of the parameters that the user entered into the dialog box
    /*!
        This function is called after the user clicks on the ok button
        and generates a wxID_OK event on the parent window.
        This function will retrieve all of the parameters that the user entered
        into the dialog box. The number of layers parameter is a long more
        so for convience. In the wxiwdgets library, there is not a function
        to convert a string to an int. But, there is a function to convert a string
        to a long. Therefor, a long datatype was choosen.
        \param numberLayers The number of layers that the user entered
        \param radius The radius of the open boundary that the user entered
        \param horizontalCenter The center X-point that the user entered for the open boundary 
        \param verticalCenter The center Y-point that the user entered for the open boundary 
        \param edgeType The boundary condition that the user selected for the open boundary
    */ 
    void getParameters(long &numberLayers, double &radius, double &horizontalCenter, double &verticalCenter, OpenBoundaryEdge &edgeType);
    
    //! The destructor for the class
    ~openBoundaryDialog();
};



#endif