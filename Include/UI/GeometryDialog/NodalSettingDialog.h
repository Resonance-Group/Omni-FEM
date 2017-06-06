#ifndef SET_NODAL_PROPERTY_H_
#define SET_NODAL_PROPERTY_H_

#include <vector>

#include <wx/wx.h>
#include <wx/stattext.h>
#include <wx/combobox.h>
#include <wx/textctrl.h>
#include <wx/sizer.h>
#include <wx/arrstr.h>

#include <common/NodalProperty.h>
#include <common/GeometryProperties/NodeSettings.h>
#include <common/ConductorProperty.h>


//! Dialog that is used to edit the nodal properties of a node
/*!
    This class dialog is created when the user needs to edit the 
    nodal properties of a node. After clicking the ok button,
    this class will generate a wxID_OK event.
    For documentation on the wxDialog class, refer to the 
    following link:
    http://docs.wxwidgets.org/3.1.0/classwx_dialog.html
*/ 
class setNodalPropertyDialog : public wxDialog
{
private:

    //! physics problem the the user has choosen
    /*!
        This variable controls what gets drawn on the screen and what is returned.
        This variable is set in the cnostructor and depends on which constructor is called
    */ 
    physicProblems _problem = physicProblems::NO_PHYSICS_DEFINED;
    
    //! Pointer that points to the global nodal property list
    std::vector<nodalProperty> *_nodalList;
    
    //! Pointer that points to hte global conductor list
    /*!
        This variable is only used if the user selected an electrical simulation
    */ 
    std::vector<conductorProperty> *_conductorList;
    
    //! Local variable to hold the edited nodal property
    /*!
        In order for this dialog to appear, the user must have a selected node.
        The function will pass on the properties of the selected node to this variable
        where the program will expose the properties to the user.
    */ 
    nodeSetting _nodeSetting;
    
    //! Combo box used to select the nodal property that will be associated with the selected node(s)
    /*!
        Can be either Succisive Approxamation or Newton.
        For documenation on the wxComboBox class, refer to the following
        link:
        http://docs.wxwidgets.org/trunk/classwx_combo_box.html
    */
    wxComboBox *_nodePropertyComboBox = new wxComboBox();
    
    //! Text box used to edit the group number associated with the selected node(s)
    /*!
        For documentation on the wxTextCtrl class, refer to
        the following link:
        http://docs.wxwidgets.org/trunk/classwx_text_ctrl.html
    */
    wxTextCtrl *_groupTextCtrl = new wxTextCtrl();
    
    //! Combo box used to select the conductor associated with the selected node(s)
    /*!
        This combo box is only avaiable for electrical simulations
        For documentation on the wxTextCtrl class, refer to
        the following link:
        http://docs.wxwidgets.org/trunk/classwx_text_ctrl.html
    */
    wxComboBox *_conductorsComboBox = new wxComboBox();
public:

    //! This is the constructor for the class
    /*!
        This constructor is called if the problem is electro-statics
        The constructor will setup the dialog and place all of 
        the widgets in their correct places
        \param par Pointer to the parent window
        \param nodePropertyList Pointer to the global nodal property list
        \param nodeSettings Property of a selected node
        \param conductorPropertyList Pointer to the global conductor property list
    */ 
    setNodalPropertyDialog(wxWindow *par, std::vector<nodalProperty> *nodePropertyList, nodeSetting nodeSettings, std::vector<conductorProperty> *conductorPropertyList);
    
    //! This is the constructor for the class
    /*!
        This constructor is called if the problem is magnetics
        The constructor will setup the dialog and place all of 
        the widgets in their correct places
        \param par Pointer to the parent window
        \param nodePropertyList Pointer to the global nodal property list
        \param nodeSettings Property of a selected node
    */
    setNodalPropertyDialog(wxWindow *par, std::vector<nodalProperty> *nodePropertyList, nodeSetting nodeSettings);
    
    //! Function used to retrieve the nodal settings set by the user
    /*!
        This function will take an object and set the properties of the
        object to be that of the user selection
        \param settigns The object that the program will use to store the user selected nodal properties
    */ 
    void getNodalSettings(nodeSetting &settings);
    
    //! The destructor for the class
    ~setNodalPropertyDialog();
};



#endif