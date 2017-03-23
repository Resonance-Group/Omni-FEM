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

class segmentPropertyDialog : public wxDialog
{
private:
    physicProblems _problem;
    
    std::vector<magneticBoundary> _magneticBoundayList;
    
    std::vector<electricalBoundary> _electricalBoundaryList;
    
    std::vector<conductorProperty> _conductorList;

    wxTextCtrl *_elementSizeTextCtrl = new wxTextCtrl();
    
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
    segmentPropertyDialog(wxWindow *par, std::vector<magneticBoundary> magneticBoundayList, segmentProperty property);
    
    segmentPropertyDialog(wxWindow *par, std::vector<electricalBoundary> electricalBoundaryList, std::vector<conductorProperty> conductorList, segmentProperty property);
    
    void getSegmentProperty(segmentProperty &property);
    
    ~segmentPropertyDialog();

private:
    wxDECLARE_EVENT_TABLE();
};

#endif