#include <UI/EditMenu/CreateFilletDialog.h>


createFilletDialog::createFilletDialog(wxWindow *par) : wxDialog(par, wxID_ANY, "Fillet Radius")
{
    wxFloatingPointValidator<double> radiusValidator;
    radiusValidator.SetMin(0);
    
    wxFont *font = new wxFont(8.5, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
    
    wxBoxSizer *textCtrlSizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *footerSizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *topSizer = new wxBoxSizer(wxVERTICAL);
    
    _radiusTextCtrl->Create(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(156, 20), 0, radiusValidator);
    _radiusTextCtrl->SetFont(*font);
    
    textCtrlSizer->Add(_radiusTextCtrl, 0, wxCENTER | wxALL, 6);
    
    wxButton *okButton = new wxButton(this, wxID_OK, "Ok", wxDefaultPosition, wxSize(75, 23));
    okButton->SetFont(*font);
    
    wxButton *cancelButton = new wxButton(this, wxID_CANCEL, "Cancel", wxDefaultPosition, wxSize(75, 23));
    cancelButton->SetFont(*font);
    
    footerSizer->Add(okButton, 0, wxCENTER | wxBOTTOM | wxLEFT | wxRIGHT, 6);
    footerSizer->Add(cancelButton, 0, wxCENTER | wxBOTTOM | wxRIGHT, 6);
    
    topSizer->Add(textCtrlSizer, 0, wxALIGN_CENTER);
    topSizer->Add(footerSizer, 0, wxALIGN_RIGHT);
    
    SetSizerAndFit(topSizer);
}



double createFilletDialog::getRadius()
{
    double value;
    _radiusTextCtrl->GetValue().ToDouble(&value);
    return value;
}