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

//#include <UI/NodalProperty/NodalPropertyDialog.h>

class conductorPropertySetDialog : public wxDialog
{
private:
    //! This will contain a local copy of the circuit list. This will allow for easy editing
    std::vector<circuitProperty> _circuitList;
    
    std::vector<conductorProperty> _conductorList;
    
    //! This is the combo box containing the current avaiable magnetic boundary
    wxComboBox *selection = new wxComboBox();
    
    /*! /brief 
     *  The string array containing the names of the different circuits
     *  This variable is actually used once to load the initial state of the names into the combo box.
     *  Once the forum is loaded, this variable is no longer used as the combo box list can be directly edited.
     */ 
    wxArrayString *circuitNameArray = new wxArrayString();
    
    /*! /brief 
     *  The string array containing the names of the different conductors
     *  This variable is actually used once to load the initial state of the names into the combo box.
     *  Once the forum is loaded, this variable is no longer used as the combo box list can be directly edited.
     */ 
    wxArrayString *conductorNameArray = new wxArrayString();
    
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
    
    //! This contains the dialog that is used to edit and add the magnetic boundary to/from the list
    circuitPropertyDialog *_circuitPropertyDialog = new circuitPropertyDialog();
    
public:
    //! This is the constructor for the class. This constructor is for a magnetic material
    conductorPropertySetDialog(std::vector<circuitProperty> circuitList);
    
    //! This is the destructor for the class. This will take the material list and save it back into memory
    ~conductorPropertySetDialog();
    
    //! This function needs to be called in order to retrieve the editted list once the dialog is closed
    std::vector<circuitProperty> getCircuitList();
    
private:
    wxDECLARE_EVENT_TABLE();  
    
    
};


#endif