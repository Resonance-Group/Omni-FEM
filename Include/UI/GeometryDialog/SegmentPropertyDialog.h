#ifndef SEGMENTPROPERTIESDIALOG_H_
#define SEGMENTPROPERTIESDIALOG_H_

#include <vector>
#include <string>
#include <iostream>
#include <iomanip>

#include <wx/wx.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/combobox.h>
#include <wx/sizer.h>
#include <wx/arrstr.h>
#include <wx/checkbox.h>

#include <common/ElectricalBoundary.h>
#include <common/MagneticBoundary.h>
#include <common/enums.h>

#include <common/GeometryProperties/SegmentProperties.h>


//! Dialog used to set the segment properties of a selected segment
/*!
    This class will create a dialog allowing the user to 
    select and edit the segment properties of a selected
    segment. A segment can be either a line or an arc.
    Once the user clicks on the ok button, the class will generate a 
    wxID_OK event.
    For documentation on the wxDialog class, refer to the 
    following link:
    http://docs.wxwidgets.org/3.1.0/classwx_dialog.html
*/ 
class segmentPropertyDialog : public wxDialog
{
private:

	segmentProperty p_property;

    //! The physics problem that the user has selected.
    /*!
        This variable will effect what widgets are drawn on
        the screen and what is returned. This variable is set
        with the constructor and is dependant on which
        constructor is called
    */ 
    physicProblems _problem;
    
	//! Pointer to the global magnetics list
    std::vector<magneticBoundary> *_magneticBoundayList;
    
	//! Pointer to the global electrical boundary list
    std::vector<electricalBoundary> *_electricalBoundaryList;
    
	//! Pointer to the global conductor list
    std::vector<conductorProperty> *_conductorList;
    
	//! Boolean used to indicate if the geometry is an arc
	/*!
		The dialog for a line segment and an arc segment
		contain some different parameters.
		This boolean is used to determine what widgets to place on
		the dialog
	*/ 
    bool _isArc;
	
	//! Text box used to modify the element size
	/*!
		If the auto mesh spacing is not checked, this 
		text box will be enabled allowing the user to manually
		specify the element size along the boundary
		For documentation on the wxTextCtrl class, refer to
        the following link:
        http://docs.wxwidgets.org/trunk/classwx_text_ctrl.html
	*/ 
    wxTextCtrl *_elementSizeTextCtrl = new wxTextCtrl();
    
	//! Text box used to modufy the group number of the segment
	/*!
        For documentation on the wxTextCtrl class, refer to
        the following link:
        http://docs.wxwidgets.org/trunk/classwx_text_ctrl.html
    */ 
    wxTextCtrl *_groupTextCtrl = new wxTextCtrl();
    
    //! Combo box used to select the boundary condition for the segment
    /*!
        For documentation on the wxComboBox class, refer to
        the following link:
        http://docs.wxwidgets.org/trunk/classwx_combo_box.html
    */ 
    wxComboBox *_boundaryListCombo = new wxComboBox();
    
    //! Combo box used to select the conductor associated with the segment
    /*!
        This is only used in electrical simulations
        For documentation on the wxComboBox class, refer to
        the following link:
        http://docs.wxwidgets.org/trunk/classwx_combo_box.html
    */ 
    wxComboBox *_conductorListCombobox = new wxComboBox();
    
    //! Check box used to select if the program should auto mesh along the segment
    /*!
        For documentation on the wxCheckBox class, refer to
        the following link:
        http://docs.wxwidgets.org/3.1.0/classwx_check_box.html
    */ 
    wxCheckBox *_meshSpacingAutoCheckbox = new wxCheckBox();
    
    //! Check box used to select if the segment is a construction line
    /*!
        For documentation on the wxCheckBox class, refer to
        the following link:
        http://docs.wxwidgets.org/3.1.0/classwx_check_box.html
    */
    wxCheckBox *_hideSegmentCheckbox = new wxCheckBox();
    
    //! Event procedure executed when the user clicks on the mesh spacing auto check box
    /*!
        This function will enable to user to edit the mesh size along the line
        \param event A required parameter in order to allow the event procedure to work 
                    properly
    */ 
    void onMeshCheckBox(wxCommandEvent &event);
    
public:
    
    //! The constructor for the class for magnetic simulations
    /*!
        This constructor is used for magnetic simulations.
        This function will create the dialog and display the widgets
        that are relevent to magnetic simulations
        \param par Pointer to the parent window
        \param magneticBoundaryList Pointer to the global magnetic boundary list
        \param property The segment property that is to be edited
        \param isArc Set to true if editing an arc. Otherwise, set to false
    */ 
    segmentPropertyDialog(wxWindow *par, std::vector<magneticBoundary> *magneticBoundayList, segmentProperty property, bool isArc);
    
    //! The constructor for the class for electrical simulations
    /*!
        This constructor is used for electrical simulations.
        This function will create the dialog and display the widgets
        that are relevent to electrical simulations
        \param par Pointer to the parent window
        \param electricalBoundaryList Pointer to the global electrical boundary list
        \param conductorList Pointer to the global conductor list
        \param property The segment property that is to be edited
        \param isArc Set to true if editing an arc. Otherwise, set to false
    */ 
    segmentPropertyDialog(wxWindow *par, std::vector<electricalBoundary> *electricalBoundaryList, std::vector<conductorProperty> *conductorList, segmentProperty property, bool _isArc);
    
    //! Retrieves the properties that the user set
    /*!
        This function depends on the problem type that was set in the 
        constructor. The problem type will determine what widgets this
        function should look at when called. This function
        will retrieve all user set properties and store them 
        in the variable property
        \param property The variable that the program will store the 
                        saved settigns
    */ 
    bool getSegmentProperty(segmentProperty &property);
    
    //! The desctructor of the class
    ~segmentPropertyDialog();

private:
    //! Required function call for event procedure
    wxDECLARE_EVENT_TABLE();
};

#endif