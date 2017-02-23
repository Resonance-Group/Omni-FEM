#ifndef GRIDPREFERENCES_H_
#define GRIDPREFERENCES_H_

#include <wx/wx.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/checkbox.h>
#include <wx/sizers.h>


class gridPreferences : wxDialog
{
private:
    wxTextCtrl *_ppuTextCtrl = new wxTextCtrl();
    
    wxTextCtrl *_gridSizeTextCtrl = new wxTextCtrl();
    
    wxCheckBox *_showGridCheckBox = new wxCheckBox();

    wxCheckBox *_snapGridCheckBox = new wxCheckBox(); 
    
    wxCheckBox *_showOriginCheckBox = new wxCheckBox(); 
    
    wxCheckBox *_showBlockNameCheckBox = new wxCheckBox(); 
    
    void updateInterface();
public:

    gridPreferences();
    
    ~gridPreferences();
    
    void getParameters();
    
    void setParameters();
};

#endif