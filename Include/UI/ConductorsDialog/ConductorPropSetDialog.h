#ifndef CONDUCTORS_PROPERTY_SET_H_
#define CONDUCTORS_PROPERTY_SET_H_

#include <vector>

#include <wx/wx.h>
#include <wx/stattext.h>
#include <wx/combobox.h>
#include <wx/arrstr.h>
#include <wx/sizer.h>

#include <common/CircuitProperty.h>
#include <common/ConductorProperty.h>
#include <common/enums.h>

#include <UI/ConductorsDialog/CircuitPropertyDialog.h>
#include <UI/ConductorsDialog/ConductorPropertyDialog.h>


//! Class that handles the dialog for editing the conductor lists
/*!
    This class does not handle the creation/modifying of individual conductor objects that 
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
class conductorPropertySetDialog : public wxDialog
{
private:
    //! This will contain a local copy of the circuit list. This will allow for easy editing
    std::vector<circuitProperty> *_circuitList;
    
    std::vector<conductorProperty> *_conductorList;
    
    physicProblems _problem;
    
    //! This is the combo box containing the current avaiable magnetic boundary
    wxComboBox *_selection = new wxComboBox();
    
    /*! /brief
        This function is called when the Add Property button is called.
        This fucntion will create another dialog box and add a property to the ;ist once the user is finished
    */ 
    void onAddProperty(wxCommandEvent &event);
    
    /*! /brief
     *  This function will be called when the delete button is pressed
     *  This function will remove the selection from the list.
     */
    void onDeleteProperty(wxCommandEvent &event);
    
    /*! /brief
     *  This function will be called when the modify button is pressed
     *  This function will create another dialog box allowing the user to modif the property
     */
    void onModifyProperty(wxCommandEvent &event);
    
    void makeDialog();
    
public:
    //! This is the constructor for the class. This constructor is for a magnetic material
    conductorPropertySetDialog(wxWindow *par, std::vector<circuitProperty> *circuitList);
    
    conductorPropertySetDialog(wxWindow *par, std::vector<conductorProperty> *conductorList);
    
    //! This is the destructor for the class. This will take the material list and save it back into memory
    ~conductorPropertySetDialog();
    
private:
    wxDECLARE_EVENT_TABLE();  
    
    
};


#endif