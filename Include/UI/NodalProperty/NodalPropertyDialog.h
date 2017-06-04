#ifndef NODALPROPERTYDIALOG_H_
#define NODALPROPERTYDIALOG_H_

#include <string>
#include <iostream>
#include <iomanip>

#include <wx/wx.h>
#include <wx/stattext.h>
#include <wx/combobox.h>
#include <wx/arrstr.h>
#include <wx/statbox.h>
#include <wx/radiobut.h>
#include <wx/sizer.h>

#include <common/NodalProperty.h>
#include <common/enums.h>

//! Class that handles editing of the nodal properties
/*!
    This class creates a dialog which is then able to 
    expose the nodal property class to the user for editing.
    This class is able to accept a nodal property as an input. If this
    is the case, then the class will display the properties of the 
    nodal to the user for editing.
    For additional documentation of the wxdialog class, refer to the
    following link:
    http://docs.wxwidgets.org/3.1.0/classwx_dialog.html
*/ 
class nodalPropertyDialog : public wxDialog
{
private:

    //! The physics problem that the user has choosen
    /*!
        This variable is set in the constructor of the class. 
        The variable is used in order to determine which dialog to drawn.
        Draw it for a magnetic simulation or an electrostatic simulation
    */ 
    physicProblems _problem;

    //! The nodal property that is being edited 
    /*!
        For new nodal properties, this variable will contain the
        default parameters. For nodal properties that are being edited,
        this variable will contain the parameters of the nodal property
        that is being edited
    */
    nodalProperty _nodalProperty;

    //! Text box that is used to display the name of the nodal property
    /*!
        This text box is drawn so that the user is able to edit
        the name of the nodal property.
        For additional documentation on the wxTextCtrl class refer
        to the following link:
        http://docs.wxwidgets.org/3.1.0/classwx_text_ctrl.html
    */
    wxTextCtrl *nameTextCtrl = new wxTextCtrl();
    
    //! Generic text box
    /*!
        Depending on the simulation, this text box will
        edit the value for the Specified voltage Potential or
        the Specified Vector Potential.
        For additional documentation on the wxTextCtrl class refer
        to the following link:
        http://docs.wxwidgets.org/3.1.0/classwx_text_ctrl.html
    */ 
    wxTextCtrl *textCtrl1 = new wxTextCtrl();
    
    // Generic text box
    /*!
        Depending on the simulation, this text box will
        edit the value for the Point Charge Density or
        the Point Current.
        For additional documentation on the wxTextCtrl class refer
        to the following link:
        http://docs.wxwidgets.org/3.1.0/classwx_text_ctrl.html
    */ 
    wxTextCtrl *textCtrl2 = new wxTextCtrl();
    
    //! A generic radio button
    /*!
        This radio button is meant for selecting Specified Potential Property.
        For additional documentation on the wxTextCtrl class refer
        to the following link:
        http://docs.wxwidgets.org/3.1.0/classwx_text_ctrl.html
    */ 
    wxRadioButton *radioButton1 = new wxRadioButton();
    
    //! A generic radio button
    /*!
        This radio button is meant for selecting Point Charge Density
        or Point Current Property depending on the simulation.
        For additional documentation on the wxTextCtrl class refer
        to the following link:
        http://docs.wxwidgets.org/3.1.0/classwx_text_ctrl.html
    */ 
    wxRadioButton *radioButton2 = new wxRadioButton();
    
    //! Event procedure for the first radio button
    /*!
        Depending on the simulation, this function will enable the 
        Specified Voltage Potentional text box and disable the Point Charge Density
        text box. For magnetic simulations, this function will enable the
        Specified Vector Potential and disable the Point Current text box
        \param event Required parameter in order for the event procedure to work properly
    */ 
    void onRadioButton1Cllick(wxCommandEvent &event);
    
    //! Event procedure for the second radio button
    /*!
        Depending on the simulation, this function will disable the 
        Specified Voltage Potentional text box and enable the Point Charge Density
        text box. For magnetic simulations, this function will disable the
        Specified Vector Potential and enable the Point Current text box
        \param event Required parameter in order for the event procedure to work properly
    */ 
    void onRadioButton2Cllick(wxCommandEvent &event);
    
    //! Function that is called in order to change the values on the interface
    /*!
        This function is called after the creation of the dialog. If the user 
        sets a nodal property, then the program will need to update the 
        interface in order to display the appropriate values for the nodal property.
        This also applies if the user is creating a new nodal property. The program calls
        the clear nodal property function in order to reset the values stored in the nodal property.
        This function will also update the states of the radio buttons.
    */
    void updateInterface();
    
public:
    
    //! Constructor of the class
    /*!
        This function will set the variables within
        the class in order to draw the appropriate
        dialog depending on the simulation
        \param par Pointer to the parent window
        \param problem The physics problem that the user has choosen to run
    */
    nodalPropertyDialog(wxWindow *par, physicProblems problem);
    
    //! Function that is used to retrieve the nodal property from the dialog
    /*!
        This function is used in order to retrieve the parameters for the nodal property 
        that the user editted.
        \param nodalProp The nodal property that the user wants to save the parameters to
    */
    void getNodalProperty(nodalProperty &nodalProp);
    
    //! Function that is used in order to set the nodal property of the dialog
    /*!
        This function is primarly used when the program needs to edit
        a selected nodal property. This function will take the 
        user selection and set the nodal property variable within this class. The
        function will then update the interface in order to expose all of the 
        values of the nodal property
        \param nodalProp The nodal property condition that will be edited
    */
    void setNodalProperty(nodalProperty &nodalProp);
    
    //! Resets the nodal property  back to default value
    /*!
        This is useful when adding a new nodal property 
    */ 
    void clearNodalProperty();
    
    //! Creates the dialog
    /*!
        This function will create the actual dialog using the 
        variables setup in the constructor
    */ 
    void createDialog();
    
    //! The destructor of the class
    ~nodalPropertyDialog();
    
private:
    //! Required in order to do the event procedures
    wxDECLARE_EVENT_TABLE();
};


#endif