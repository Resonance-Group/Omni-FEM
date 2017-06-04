#ifndef CIRCUITPROPERTYDIALOG_H_
#define CIRCUITPROPERTYDIALOG_H_

#include <string>
#include <iostream>
#include <iomanip>

#include <wx/wx.h>
#include <wx/stattext.h>
#include <wx/combobox.h>
#include <wx/arrstr.h>
#include <wx/statbox.h>
#include <wx/sizer.h>
#include <wx/radiobut.h>

#include <common/enums.h>
#include <common/CircuitProperty.h>

//! Class that handles editing of the circuits
/*!
    This class creates a dialog which is then able to 
    expose the circuit property class to the user for editing.
    This class is able to accept a circuit as an input. If this
    is the case, then the class will display the properties of the 
    circuit to the user for editing. This particular class is 
    used in magnetic simualtions.
    For additional documentation of the wxdialog class, refer to the
    following link:
    http://docs.wxwidgets.org/3.1.0/classwx_dialog.html
*/ 
class circuitPropertyDialog : public wxDialog
{
private:
    //! The circuit that is being edited 
    /*!
        For new circuits, this variable will contain the
        default parameters. For circuits that are being edited,
        this variable will contain the parameters of the circuit
        that is being edited
    */
    circuitProperty _circuitProperty;
    
    //! Text box that is used to display the name of the circuit
    /*!
        This text box is drawn so that the user is able to edit
        the name of the circuit.
        For additional documentation on the wxTextCtrl class refer
        to the following link:
        http://docs.wxwidgets.org/3.1.0/classwx_text_ctrl.html
    */
    wxTextCtrl *nameTextCtrl = new wxTextCtrl();
    
    //! Text box that is used to display the value current going through a circuit
    /*!
        This text box is drawn so that the user is able to edit
        the value of the current flowing through the circuit.
        For parallel circuits, this value is split between the different
        branches. For series circuits, this value is the same for all regions
        marked by this property.
        For additional documentation on the wxTextCtrl class refer
        to the following link:
        http://docs.wxwidgets.org/3.1.0/classwx_text_ctrl.html
    */
    wxTextCtrl *circuitCurrentTextCtrl = new wxTextCtrl();
    
    //! Radio button used to specify that the circuit is parallel
    /*!
        This radio button is used to allow the user to select the
        circuit as a parallel circuit
        For additional documentation for the wxRadioButton class
        refer to the following link:
        http://docs.wxwidgets.org/trunk/classwx_radio_button.html
    */ 
    wxRadioButton *radioButton1 = new wxRadioButton();
    
    //! Radio button used to specify that the circuit is series
    /*!
        This radio button is used to allow the user to select the
        circuit as a series circuit
        For additional documentation for the wxRadioButton class
        refer to the following link:
        http://docs.wxwidgets.org/trunk/classwx_radio_button.html
    */
    wxRadioButton *radioButton2 = new wxRadioButton();
    
    //! Function that is called in order to change the values on the interface
    /*!
        This function is called after the creation of the dialog. If the user 
        sets a circuit, then the program will need to update the 
        interface in order to display the apprioate values for the circuit.
        This also applies if the user is creating a new circuit. The program calls
        the clear circuit function in order to reset the values stored in the circuit.
        This function will also update the states of the radio buttons.
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
    circuitPropertyDialog(wxWindow *par);
    
    //! Function that is used to retrieve the circuit from the dialog
    /*!
        This function is used in order to retrieve the parameters for the circuit 
        that the user editted.
        \param newCircuit The circuit that the user wants to save the parameters to
    */
    void getNewCircuit(circuitProperty &newCircuit);
    
    //! Function that is used in order to set the circuit of the dialog
    /*!
        This function is primarly used when the program needs to edit
        a selected circuit. This function will take the 
        user selection and set the circuit variable within this class. The
        function will then update the interface in order to expose all of the 
        values of the circuit
        \param circuit The circuit condition that will be edited
    */
    void setCircuit(circuitProperty &circuit);
    
    //! Resets the circuit back to default value
    /*!
        This is useful when adding a new circuit
    */ 
    void clearCircuit();
    
    //! The destructor of the class
    ~circuitPropertyDialog();
};




#endif