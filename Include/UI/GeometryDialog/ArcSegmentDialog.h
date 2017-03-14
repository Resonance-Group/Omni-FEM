#ifndef ARC_SEGMENT_DIALOG_H_
#define ARC_SEGMENT_DIALOG_H_

#include <vector>
#include <string>
#include <iostream>
#include <iomanip>

#include <wx/wx.h>
#include <wx/textctrl.h>
#include <wx/stattext.h>
#include <wx/sizer.h>
#include <wx/combobox.h>
#include <wx/arrstr.h>
#include <wx/valnum.h>

#include <common/enums.h>
#include <common/ElectricalBoundary.h>
#include <common/MagneticBoundary.h>

#include <UI/geometryShapes.h>


class arcSegmentDialog : public wxDialog
{
private:
    physicProblems _problem = physicProblems::NO_PHYSICS_DEFINED;

    std::vector<electricalBoundary> _localElectricalBoundaryList;
    
    std::vector<magneticBoundary> _localMagneticBoundaryList;
    
    wxArrayString _nameArray;

    wxTextCtrl *_arcAngleTextCtrl = new wxTextCtrl();
    
    wxTextCtrl *_segmentTextCtrl = new wxTextCtrl();
    
    wxComboBox *_boundaryComboBox = new wxComboBox();
    
    arcShape _localArcShape;
    
    void updateInterface();
    
    void createDialog();
    
public:
    arcSegmentDialog(wxWindow *par, std::vector<electricalBoundary> list);
    
    arcSegmentDialog(wxWindow *par, std::vector<magneticBoundary> list);
    
    void clearParameter();
    
    void setArcParameter(arcShape shape);
    
    void getArcParameter(arcShape &shape);
};

#endif