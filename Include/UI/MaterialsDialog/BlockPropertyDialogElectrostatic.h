#ifndef BLOCKPROPERTYELECTROSTATIC_H_
#define BLOCKPROPERTYELECTROSTATIC_H_

#include <string>
#include <iostream>
#include <iomanip>

#include <wx/wx.h>
#include <wx/stattext.h>
#include <wx/arrstr.h>
#include <wx/statbox.h>
#include <wx/sizer.h>

#include <common/enums.h>
#include <common/ElectroStaticMaterial.h>

class blockPropertyDialogElectrostatic : public wxDialog
{
private:
    electrostaticMaterial _material;

    wxTextCtrl *_name = new wxTextCtrl();
    
    wxTextCtrl *_relativeEpiXTextCtrl = new wxTextCtrl();
    
    wxTextCtrl *_relativeEpiYTextCtrl = new wxTextCtrl();
    
    wxTextCtrl *_chargeDensityTextCtrl = new wxTextCtrl();
    
    void setTextBox();

public:
    blockPropertyDialogElectrostatic();
    
    ~blockPropertyDialogElectrostatic();
    
    void getMaterial(electrostaticMaterial &material);
    
    void clearMaterial();
    
    void setMaterial(electrostaticMaterial &material);
};



#endif