#ifndef OPENBOUNDARYDIALOG_H_
#define OPENBOUNDARYDIALOG_H_

#include <wx/wx.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/combobox.h>
#include <wx/string.h>
#include <wx/arrstr.h>

#include <common/enums.h>


class openBoundaryDialog : public wxDialog
{
private:
    wxTextCtrl *_numberLayersTextCtrl = new wxTextCtrl();
    
    wxTextCtrl *_radiusTextCtrl = new wxTextCtrl();
    
    wxTextCtrl *_horizontalCenterTextCtrl = new wxTextCtrl();
    
    wxTextCtrl *_verticalCenterTextCtrl = new wxTextCtrl();
    
    wxComboBox *_edgeTypeComboBox = new wxComboBox();
    
public:
    openBoundaryDialog();
    
    ~openBoundaryDialog();
    
    void getParameters(long &numberLayers, double &radius, double &horizontalCenter, double &verticalCenter, OpenBoundaryEdge &edgeType);
};



#endif