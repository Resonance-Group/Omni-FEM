#ifndef jilesAthertonParametersDIALOG_H_
#define jilesAthertonParametersDIALOG_H_

#include <string>
#include <iostream>
#include <iomanip>

#include <wx/wx.h>
#include <wx/stattext.h>
#include <wx/combobox.h>
#include <wx/arrstr.h>
#include <wx/statbox.h>
#include <wx/sizer.h>
#include <wx/checkbox.h>

#include <common/JilesAthertonParameters.h>
#include <common/enums.h>

class jilesAthertonParameterDialog : public wxDialog
{
private:
    //! This is the class that stores a local copy of the Jiles Artheron parameters
    jilesAthertonParameters _parameter;
    
    wxTextCtrl *_alphaParamTextCtrl = new wxTextCtrl();
    
    wxTextCtrl *_aParamTextCtrl = new wxTextCtrl();
    
    wxTextCtrl *_satMagnetizationParamTextCtrl = new wxTextCtrl();
    
    wxTextCtrl *_kParamTextCtrl = new wxTextCtrl();
    
    wxTextCtrl *_cParamTextCtrl = new wxTextCtrl();
    
    wxTextCtrl *_KanParamTextCtrl = new wxTextCtrl();
    
    wxTextCtrl *_psiParamTextCtrl = new wxTextCtrl();
    
    wxTextCtrl *_tParamTextCtrl = new wxTextCtrl();
    
    wxCheckBox *_isAnisotropyCheckBox = new wxCheckBox();
    
    void onCheckBox(wxCommandEvent &event);
    
    void updateInterface();
    
public:
    jilesAthertonParameterDialog();
    
    ~jilesAthertonParameterDialog();
    
    void setJilesAthertonParameter(jilesAthertonParameters param);
    
    void getJilesAthertonParameter(jilesAthertonParameters &param);
    
private:
    wxDECLARE_EVENT_TABLE();
};


#endif