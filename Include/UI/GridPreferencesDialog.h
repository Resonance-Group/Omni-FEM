#ifndef GRIDPREFERENCES_H_
#define GRIDPREFERENCES_H_

#include <string>
#include <iostream>
#include <iomanip>

#include <wx/wx.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/checkbox.h>
#include <wx/combobox.h>
#include <wx/sizer.h>
#include <wx/arrstr.h>

#include <common/GridPreferences.h>


class gridPreferencesDialog : public wxDialog
{
private:
    gridPreferences _preferences;

    wxTextCtrl *_ppuTextCtrl = new wxTextCtrl();
    
    wxTextCtrl *_gridSizeTextCtrl = new wxTextCtrl();
    
    wxCheckBox *_showGridCheckBox = new wxCheckBox();

    wxCheckBox *_snapGridCheckBox = new wxCheckBox(); 
    
    wxCheckBox *_showOriginCheckBox = new wxCheckBox(); 
    
    wxCheckBox *_showBlockNameCheckBox = new wxCheckBox();

    wxComboBox *_coordinateComboBox = new wxComboBox();
    
    void updateInterface();
public:

    gridPreferencesDialog();
    
    ~gridPreferencesDialog();
    
    void getParameters(gridPreferences &preferences);
    
    void setParameters(gridPreferences &preferences);
};

#endif