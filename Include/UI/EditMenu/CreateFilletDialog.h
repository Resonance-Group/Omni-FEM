#ifndef CREATE_FILLET_DIALOG_H_
#define CREATE_FILLET_DIALOG_H_

#include <wx/wx.h>
#include <wx/stattext.h>
#include <wx/valnum.h>
#include <wx/sizer.h>


//! Class that is used to enter a radius for the fillet
/*!
    Probably the simplest class in the program,
    This class is used to create the dialog
    that the user will use in order to enter a value for the radius of
    the fillet.
    For additional documentation of the wxdialog class, refer to the
    following link:
    http://docs.wxwidgets.org/3.1.0/classwx_dialog.html
*/ 
class createFilletDialog : public wxDialog
{
private:
    
    //! Text box used to edit the radius
    /*!
        This text box is used to enter in the 
        radius of the fillet.
        For additional documentation on the wxTextCtrl class refer
        to the following link:
        http://docs.wxwidgets.org/3.1.0/classwx_text_ctrl.html
    */ 
    wxTextCtrl *_radiusTextCtrl = new wxTextCtrl();
    
public:
    //! Constructor of the class
    /*!
        This function will create the dialog and
        place all of the relevent widgets onto the 
        dialog and position all widgets where
        they need to go.
        \param par Pointer to the parent window
    */
    createFilletDialog(wxWindow *par);
    
    //! Returns the radius
    /*!
        This function will return the radius that the
        user enter into the text box
    */ 
    double getRadius();
};





#endif