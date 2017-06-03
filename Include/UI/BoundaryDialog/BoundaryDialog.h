#ifndef BOUNDARY_DIALOG_H_
#define BOUNDARY_DIALOG_H_

#include <vector>

#include <wx/wx.h>
#include <wx/stattext.h>
#include <wx/combobox.h>
#include <wx/arrstr.h>
#include <wx/sizer.h>

#include <common/BoundaryConditions.h>
#include <common/ElectricalBoundary.h>
#include <common/MagneticBoundary.h>
#include <common/enums.h>

#include <UI/BoundaryDialog/MagneticBoundaryPropertyDiaglog.h>
#include <UI/BoundaryDialog/EstaticboundaryPropertyDialog.h>



//! Class that handles the dialog for editing the boundary lists
/*!
    This class does not handle the creation/modifying of individual boundary objects that 
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
class boundaryDialog : public wxDialog
{
private:

    //! Pointer to the global magnetic boundary list
    std::vector<magneticBoundary> *_magneticBoundaryList;
    
    //! Pointer to the global electrical boundary list
    std::vector<electricalBoundary> *_electricalBoundaryList;
    
    //! Variable that keeps track of the simulation problem the user selected
    /*!
        This variable is set when the boundary list is passed into the constructor.
        If a magnetic boundary condition is passed, then this variable will be set for
        magnetics simulation. THis will effect whcih property dialog is drawn next
    */ 
    physicProblems _problem;
    
    //! Combo box that contains the listing of all of the names of the list
    wxComboBox *_selection = new wxComboBox();
    
    //! Event procedure that is called when the user presses the Add Property button
    /*!
        This function will create the apprioate dialog box in order to add a boundary
        to the list. The dialog box that gets created is dependent the problem variable.
        Once the user is finished on adding the property, the function will add the 
        property to the blobal list. This function will also alert the user
        if they created a property with the same name already. This is not prevent the 
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
        This function will bring up the apprioate dialog box in order to modify the settings
        of the property that is selected in the combo box. This will only occur if there is more
        then 1 element within the list
        \param event A required parameter in order to properly route the event procedure
    */ 
    void onModifyProperty(wxCommandEvent &event);
    
    //! Creates the actual dialog
    /*!
        The constructors of the class sets up the different variables that are necessary 
        before the dialog is created. This function actually creates the dialog
        utilizing the variables that we just setup in the constructor
    */ 
    void makeDialog();
    
public:

    //! This is the constructor for the class. This constructor is for a magnetic boundary
    /*!
        \param par A pointer to the parent window
        \param boundaryList A pointer to the global magnetic boundary list
    */ 
    boundaryDialog(wxWindow *par, std::vector<magneticBoundary> *boundaryList);
    
    //! This is the constructor for the electrical boundary
    /*!
        \param par A pointer to the parent window
        \param boundaryList A pointer to the global electrical boundary list
    */ 
    boundaryDialog(wxWindow *par, std::vector<electricalBoundary> *boundaryList);
    
    //! This is the destructor for the class.
    ~boundaryDialog();
    
private:
    //! Required function for the event procedures to work properly
    wxDECLARE_EVENT_TABLE();
};


#endif