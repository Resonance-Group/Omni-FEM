#ifndef SELECT_GROUP_DIALOG_H_
#define SELECT_GROUP_DIALOG_H_

#include <wx/wx.h>
#include <wx/radiobut.h>
#include <wx/textctrl.h>
#include <wx/stattext.h>
#include <wx/sizer.h>
#include <wx/valnum.h>

#include <common/enums.h>

//! Class that handles the creation of the select group dialog
/*!
    This dialog will allow the user to select a specific set of
    geometry shapes and select what group from the set of geometry shapes.
    The user can also select all of the geometry shapes that belong
    to a particular group number. If the user clicks on the ok
    button, this class will generate a wxID_OK event on the parent window
    For documentation on the wxDialog class, refer to the following link:
    http://docs.wxwidgets.org/3.1.0/classwx_dialog.html
*/ 
class selectGroupDialog : public wxDialog
{
private:
    
    //! Radio button used to select the node geometries
    /*!
        For documentation on the wxRadioButton class, refer to 
        the following link:
        http://docs.wxwidgets.org/trunk/classwx_radio_button.html
    */ 
    wxRadioButton *_nodeRadioButton = new wxRadioButton();
    
    //! Radio button used to select the line geometries
    /*!
        For documentation on the wxRadioButton class, refer to 
        the following link:
        http://docs.wxwidgets.org/trunk/classwx_radio_button.html
    */
    wxRadioButton *_lineRadioButton = new wxRadioButton();
    
    //! Radio button used to select the arc geometries
    /*!
        For documentation on the wxRadioButton class, refer to 
        the following link:
        http://docs.wxwidgets.org/trunk/classwx_radio_button.html
    */
    wxRadioButton *_arcRadioButton = new wxRadioButton();
    
    //! Radio button used to select the block label geometries
    /*!
        For documentation on the wxRadioButton class, refer to 
        the following link:
        http://docs.wxwidgets.org/trunk/classwx_radio_button.html
    */
    wxRadioButton *_labelRadioButton = new wxRadioButton();
    
    //! Radio button used to select the all of the geometries
    /*!
        For documentation on the wxRadioButton class, refer to 
        the following link:
        http://docs.wxwidgets.org/trunk/classwx_radio_button.html
    */
    wxRadioButton *_allRadioButton = new wxRadioButton();
    
    //! Text box used to enter in the group number for the selection
    /*!
        For documentation on the wxTextCtrl class, refer to
        the following link:
        http://docs.wxwidgets.org/trunk/classwx_text_ctrl.html
    */ 
    wxTextCtrl *_groupNumberSelect = new wxTextCtrl();
public:

    //! Constructor for the class 
    /*!
        This constructor will create the dialog window that 
        the user can see and interact with. 
        \param par Pointer to the parent window of the dialog
    */ 
    selectGroupDialog(wxWindow *par);
    
    //! Retrieves which radio button was checked and the group number that the user entered in
    /*!
        \param groupNumber The group number that the user entered into the text box
        \return Returns a value which dictates which geomerty shape the user
                wants to select
    */ 
    EditGeometry getGroupNumber(unsigned int &groupNumber);
};


#endif