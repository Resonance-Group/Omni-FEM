#ifndef EDIT_GROUP_DIALOG_H_
#define EDIT_GROUP_DIALOG_H_

#include <string>

#include <wx/wx.h>
#include <wx/textctrl.h>
#include <wx/stattext.h>
#include <wx/sizer.h>
#include <wx/valnum.h>


//! Dialog used to edit the group number of geometry
/*!
    This dialog is rather simple. This dialog will only
    appear if the user has selected a mix of geometry shapes.
    In this case, the only thing in common would be the group number.
    The user is able to specify a common group number
    for mixed geometry selection
*/ 
class editGroupNumberDialog : public wxDialog
{
private:
    
    //! The text box used to edit the group number
    /*!
        For documentation on the wxTextCtrl class, refer to
        the following link:
        http://docs.wxwidgets.org/trunk/classwx_text_ctrl.html
    */ 
    wxTextCtrl *_groupNumberTextCtrl = new wxTextCtrl();

public:

    //! The constructor of the class
    /*!
        This constructor will setup the dialog and place
        the widgets in their correct places. The text box
        will also take on the value passed into the groupNumber
        arguement of the function
        \param par Pointer to the parent window
        \param groupNumber The group number of the selected geometry pieces
    */ 
    editGroupNumberDialog(wxWindow *par, unsigned int groupNumber);
    
    //! Returns the group numer
    /*!
        \return Returns the group number that the user enterer
                into the text box
    */ 
    unsigned int getGroupNumber();
};





#endif