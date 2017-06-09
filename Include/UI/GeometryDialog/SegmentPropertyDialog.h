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
    
    wxComboBox *_boundaryListCombo = new wxComboBox();
    
    wxComboBox *_conductorListCombobox = new wxComboBox();
    
    wxCheckBox *_meshSpacingAutoCheckbox = new wxCheckBox();
    
    wxCheckBox *_hideSegmentCheckbox = new wxCheckBox();
    
    void onMeshCheckBox(wxCommandEvent &event);
    
public:
    /* The magnetic boundary list is the global boundary list.
     * The property is the segmentProperty for the line 
     */
    segmentPropertyDialog(wxWindow *par, std::vector<magneticBoundary> *magneticBoundayList, segmentProperty property, bool isArc);
    
    segmentPropertyDialog(wxWindow *par, std::vector<electricalBoundary> *electricalBoundaryList, std::vector<conductorProperty> *conductorList, segmentProperty property, bool _isArc);
    
    void getSegmentProperty(segmentProperty &property);
    
    ~segmentPropertyDialog();

private:
    wxDECLARE_EVENT_TABLE();
};

#endif