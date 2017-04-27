#include <UI/GeometryDialog/EditGroupDialog.h>


editGroupNumberDialog::editGroupNumberDialog(wxWindow *par, unsigned int groupNumber) : wxDialog(par, wxID_ANY, "Group Number")
{
    wxIntegerValidator<unsigned int> groupNumberValidator;
    groupNumberValidator.SetRange(0, 65535);
    
    wxFont *font = new wxFont(8.5, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
    
    wxBoxSizer *lineSizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *footerSizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *topSizer = new wxBoxSizer(wxVERTICAL);
    
    wxStaticText *groupText = new wxStaticText(this, wxID_ANY, "In Group:");
    groupText->SetFont(*font);
    _groupNumberTextCtrl->Create(this, wxID_ANY, std::to_string(groupNumber), wxDefaultPosition, wxSize(96, 20), 0, groupNumberValidator);
    _groupNumberTextCtrl->SetFont(*font);
    
    lineSizer->Add(groupText, 0, wxCENTER | wxALL, 6);
    lineSizer->Add(_groupNumberTextCtrl, 0, wxCENTER | wxTOP | wxBOTTOM | wxRIGHT, 6);
    
    wxButton *okButton = new wxButton(this, wxID_OK, "Ok", wxPoint(48, 64), wxSize(75, 23));
    okButton->SetFont(*font);
    
    wxButton *cancelButton = new wxButton(this, wxID_CANCEL, "Cancel", wxPoint(129, 64), wxSize(75, 23));
    cancelButton->SetFont(*font);
    
    footerSizer->Add(okButton, 0, wxCenter | wxLEFT | wxRIGHT | wxBOTTOM, 6);
    footerSizer->Add(cancelButton, 0, wxCENTER | wxRIGHT | wxBOTTOM, 6);
    
    topSizer->Add(lineSizer, 0, wxALIGN_RIGHT);
    topSizer->Add(footerSizer, 0, wxALIGN_RIGHT);
    
    SetSizerAndFit(topSizer);
}

unsigned int editGroupNumberDialog::getGroupNumber()
{
    long value;
    _groupNumberTextCtrl->GetValue().ToLong(&value);
    return (unsigned int)value;
}