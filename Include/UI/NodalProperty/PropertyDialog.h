#ifndef NODAL_PROPERTY_DIALOG_H_
#define NODAL_PROPERTY_DIALOG_H_

#include <vector>

#include <wx/wx.h>
#include <wx/stattext.h>
#include <wx/combobox.h>
#include <wx/arrstr.h>
#include <wx/sizer.h>

#include <common/NodalProperty.h>
#include <common/enums.h>

#include <UI/NodalProperty/NodalPropertyDialog.h>


//! Class that handles the dialog for editing the nodal property list
/*!
    This class does not handle the creation/modifying of individual nodal property objects that 
    the user selects. Rather, this class handles the editing of the list as a whole.
    This dialog will allow the user to add an item to the list, modify an existing item,
    or remove an item from the list. For modifying or adding the elements in the list,
    this class will call the approiate dialog in order to perform this action.
    This class inherits from the dialog class because it allows for the easy creation
    of ok/cancel buttons. This class is intended to be created in order to operate as
    modal.
    For additional documentation for the wxDialog class, refer to the following link:
    http://docs.wxwidgets.org/3.1.0/classwx_dialog.html
*/
class nodalPropertiesDialog : public wxDialog
{
private:

    //! Pointer pointing to the global nodal property list
    /*!
        Since there is no significant difference between electrostatic and magnetics, this will handle both cases
    */
    std::vector<nodalProperty> *_nodalPropertyList;
    
    //! Variable that keeps track of the simulation problem the user selected
    /*!
        This variable is set when the constructor is called.
        This will take on the value that is supplied to the constructor.
        This value will effect how the nodal property dialog is drawn.
    */
    physicProblems _problem;
    
    //! This is the combo box containing all of the names of the nodal properties
    wxComboBox *_selection = new wxComboBox();

    //! Event procedure that is called when the user presses the Add Property button
    /*!
        This function will create the appropriate dialog box in order to add a nodal property
        to the list. The dialog box that gets created is dependent on the problem variable.
        Once the user is finished on adding the property, the function will add the 
        property to the global list. This function will also alert the user
        if they created a property with the same name already. This is not preventing the 
        creation of the property as the user can go and modify the name of the property.
        If there are two properties with the same name, this can cause the program to 
        operate in an unknown state.
        \param event A required parameter in order to properly route the event procedure
    */  
    void onAddProperty(wxCommandEvent &event);
    
    //! Event Procedure that is called when the user clicks on the Delete Property button
    /*!
        This function will remove the property that is selected in the combo box from the
        the list. This will only occur if there are more then 1 elements within the list
        \param event A required parameter in order to properly route the event procedure
    */
    void onDeleteProperty(wxCommandEvent &event);
    
    //! Event procedure that is called when the user clicks on the Modify Property button
    /*!
        This function will bring up the appropriate dialog box in order to modify the settings
        of the property that is selected in the combo box. This will only occur if there is more
        then 1 element within the list
        \param event A required parameter in order to properly route the event procedure
    */
    void onModifyProperty(wxCommandEvent &event);

public:
    //! This is the constructor for the class.
    /*!
        Since the same nodal list is used for the simualtions,
        the program will need to pass in the variable that saves
        which simulation the user selected. Also,
        this function handles the creation of the dialog box
        \param par The parent window of the dialog box
        \param nodalPropertyList A pointer to the global nodal property list
        \param problem The physics problem that the user selected
    */ 
    nodalPropertiesDialog(wxWindow *par, std::vector<nodalProperty> *nodalPropertyList, physicProblems problem);
    
    //! This is the destructor for the class.
    ~nodalPropertiesDialog();
    
private:
    //! Required function for the event procedures to work properly
    wxDECLARE_EVENT_TABLE();  
};

#endif