#ifndef ESTATICBOUNDARYPROPERTYDIALOG_H_
#define ESTATICBOUNDARYPROPERTYDIALOG_H_

#include <string>
#include <iostream>
#include <iomanip>

#include <wx/wx.h>
#include <wx/stattext.h>
#include <wx/combobox.h>
#include <wx/arrstr.h>
#include <wx/statbox.h>
#include <wx/sizer.h>

#include <common/enums.h>
#include <common/ElectricalBoundary.h>

//! Class that handles editing the electrostatic boundary
/*!
    This class creates a dialog which is then able to 
    expose the electrical boundary class to the user for editing.
    This class is able to accept a boundary as an input. If this
    is the case, then the class will display the properties of the 
    boundary to the user for editing. 
    For additional documentation of the wxdialog class, refer to the
    following link:
    http://docs.wxwidgets.org/3.1.0/classwx_dialog.html
*/ 
class electricalStaticBoundaryDialog : public wxDialog
{
private:
    //! The boundary that is being edited 
    /*!
        For new boundaries, this variable will contain the
        default parameters. For boundaries that are being edited,
        this variable will contain the parameters of the boundary
        that is being edited
    */ 
    electricalBoundary _boundary;
    
    //! Array that stores all of the boundary condition names
    /*!
        This variable stores the names of the different boundary conditions
        for the electrostatic simulation. For additional
        documentation on the wxArraryString refer to the following link:
        http://docs.wxwidgets.org/trunk/classwx_array_string.html
    */ 
    wxArrayString *BCNameArray = new wxArrayString();
    
    //! The combo box that allows the user to select the boundary condition
    /*!
        This combo box is drawn on the dialog allowing the user to choose
        from the different boundary condition types. 
        If the user selects the Periodic or Anti-Periodic 
        boundary condition from the combo box, then the 
        text boxes for the other boundary conditions will
        be greyed out preventing user inputs. For 
        additional documentation on the wxComboBox class refere
        to the following link:
        http://docs.wxwidgets.org/trunk/classwx_combo_box.html
    */ 
    wxComboBox *BCComboBox = new wxComboBox();
    
    //! Text box that is used to display the name of the boundary condition
    /*!
        This text box is drawn so that the user is able to edit
        the name of the boundary.
        For additional documentation on the wxTextCtrl class refer
        to the following link:
        http://docs.wxwidgets.org/3.1.0/classwx_text_ctrl.html
    */ 
    wxTextCtrl *nameTextCtrl = new wxTextCtrl();
    
    //! Text box used to edit the fixed voltage boundary condition value
    /*!
        This text box is used to edit the fixed voltage value when 
        the user selects Fixed Voltage from the combo box.
        For additional documentation on the wxTextCtrl class
        refer to the following link:
        http://docs.wxwidgets.org/3.1.0/classwx_text_ctrl.html
    */ 
    wxTextCtrl *fixedVoltageTextCtrl = new wxTextCtrl();
    
    //! Text box used to edit the surface charge boundary condition value
    /*!
        This text box is used to edit the surface charge value when 
        the user selects Surface Change Density from the combo box.
        For additional documentation on the wxTextCtrl class
        refer to the following link:
        http://docs.wxwidgets.org/3.1.0/classwx_text_ctrl.html
    */ 
    wxTextCtrl *surfaceChargeTextCtrl = new wxTextCtrl();
    
    //! Text box used to edit the c0 boundary condition value
    /*!
        This text box is used to edit the c0 value when 
        the user selects Mixed  from the combo box.
        For additional documentation on the wxTextCtrl class
        refer to the following link:
        http://docs.wxwidgets.org/3.1.0/classwx_text_ctrl.html
    */ 
    wxTextCtrl *c0TextCtrl = new wxTextCtrl();
    
    //! Text box used to edit the c1 boundary condition value
    /*!
        This text box is used to edit the c1 value when 
        the user selects Mixed from the combo box.
        For additional documentation on the wxTextCtrl class
        refer to the following link:
        http://docs.wxwidgets.org/3.1.0/classwx_text_ctrl.html
    */ 
    wxTextCtrl *c1TextCtrl = new wxTextCtrl();
    
    //! Event procedure that is fired when the user changes a selection on the combo box
    /*!
        This function will grey out the different text boxes based on the 
        boundary condition that the user selects from the combo box
        \param event Required parameter in order to route the event procedure correctly
    */ 
    void onComboBox(wxCommandEvent &event);
    
    //! Function that is called in order to change the values in the text boxes
    /*!
        This function is called after the creation of the dialog. If the user 
        sets a boudnary condition, then the program will need to update the 
        interface in order to display the apprioate values for the boundary.
        This also applies if the user is creating a new boundary. The program calls
        the clear boudnary function in order to reset the values stored in the boundary
        condition.
    */ 
    void updateInterface();
    
public:
    //! Constructor of the class
    /*!
        This function will create the dialog and
        place all of the relevent widgets onto the 
        dialog and position all widgets where
        they need to go.
        \param par Pointer to the parent window
    */ 
    electricalStaticBoundaryDialog(wxWindow *par);
    
    //! Function that is used in order to set the boundary condition of the dialog
    /*!
        This function is primarly used when the program needs to edit
        a selected boundary condition. This function will take the 
        user selection and set the boudnary variable within this class. The
        function will then update the interface in order to expose all of the 
        values of the boundary
        \param bonudary The boundary condition that will be edited
    */ 
    void setBoundaryCondition(electricalBoundary &boundary);
    
    //! Function that is used to retrieve the boundary condition from the dialog
    /*!
        This function is used in order to retrieve the parameters for the boundary 
        that the user editted.
        \param boundary The electrical boundary that the user wants to save the infomation to
    */ 
    void getBoundaryCondition(electricalBoundary &boundary);
    
    //! Resets the boundary variable back to default value
    /*!
        This is useful when adding a new boundary condition
    */ 
    void clearBoundary();
    
    //! The destructor of the class
    ~electricalStaticBoundaryDialog();
    
private:
    //! Required for event procedure to work
    wxDECLARE_EVENT_TABLE();
};


#endif