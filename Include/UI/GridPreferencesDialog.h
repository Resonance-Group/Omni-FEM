#ifndef GRIDPREFERENCES_H_
#define GRIDPREFERENCES_H_

#include <wx/wx.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/checkbox.h>
#include <wx/combobox.h>
#include <wx/sizer.h>
#include <wx/arrstr.h>


class gridPreferences : public wxDialog
{
private:
    wxTextCtrl *_ppuTextCtrl = new wxTextCtrl();
    
    wxTextCtrl *_gridSizeTextCtrl = new wxTextCtrl();
    
    wxCheckBox *_showGridCheckBox = new wxCheckBox();

    wxCheckBox *_snapGridCheckBox = new wxCheckBox(); 
    
    wxCheckBox *_showOriginCheckBox = new wxCheckBox(); 
    
    wxCheckBox *_showBlockNameCheckBox = new wxCheckBox();

    wxComboBox *_coordinateComboBox = new wxComboBox();
    
    void updateInterface();
public:

    gridPreferences();
    
    ~gridPreferences();
    
    void getParameters();
    
    void setParameters();
};

#endif