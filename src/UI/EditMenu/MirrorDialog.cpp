#include <UI/EditMenu/MirrorDialog.h>

mirrorDialog::mirrorDialog(wxWindow *par) : wxDialog(par, wxID_ANY, "Mirror")
{
    wxFont *font = new wxFont(8.5, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
    
    wxStaticBoxSizer *firstSizer = new wxStaticBoxSizer(wxHORIZONTAL, this, "First Point on Line of Symmetry");
    firstSizer->GetStaticBox()->SetFont(*font);
    wxStaticBoxSizer *secondSizer = new wxStaticBoxSizer(wxHORIZONTAL, this, "Second Point on Line of Symmetry");
    secondSizer->GetStaticBox()->SetFont(*font);
    wxBoxSizer *footerSizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *topSizer = new wxBoxSizer(wxVERTICAL);
    
    _firstPointXTextCtrl->Create(firstSizer->GetStaticBox(), wxID_ANY, "0", wxPoint(6, 19), wxSize(100, 20));
    _firstPointXTextCtrl->SetFont(*font);
    
    _firstPointYTextCtrl->Create(firstSizer->GetStaticBox(), wxID_ANY, "0", wxPoint(112, 19), wxSize(100, 20));
    _firstPointYTextCtrl->SetFont(*font);
    
    firstSizer->Add(_firstPointXTextCtrl, 0, wxCENTER | wxALL, 6);
    firstSizer->Add(_firstPointYTextCtrl, 0, wxCENTER | wxTOP | wxBOTTOM | wxRIGHT, 6);
    
    _secondPointXTextCtrl->Create(secondSizer->GetStaticBox(), wxID_ANY, "0", wxPoint(6, 19), wxSize(100, 20));
    _secondPointXTextCtrl->SetFont(*font);
    
    _secondPointYTextCtrl->Create(secondSizer->GetStaticBox(), wxID_ANY, "0", wxPoint(112, 19), wxSize(100, 20));
    _secondPointYTextCtrl->SetFont(*font);
    
    secondSizer->Add(_secondPointXTextCtrl, 0, wxCENTER | wxALL, 6);
    secondSizer->Add(_secondPointYTextCtrl, 0, wxCENTER | wxTOP | wxBOTTOM | wxRIGHT, 6);
    
    wxButton *okButton = new wxButton(this, wxID_OK, "Ok", wxPoint(76, 135), wxSize(75, 23));
    okButton->SetFont(*font);
    
    wxButton *cancelButton = new wxButton(this, wxID_CANCEL, "Cancel", wxPoint(76, 135), wxSize(75, 23));
    cancelButton->SetFont(*font);
    
    footerSizer->Add(okButton, 0, wxCENTER | wxBOTTOM | wxRIGHT, 6);
    footerSizer->Add(cancelButton, 0, wxCENTER | wxBOTTOM | wxRIGHT, 6);
    
    topSizer->Add(firstSizer, 0, wxLEFT | wxRIGHT | wxTOP, 6);
    topSizer->Add(secondSizer, 0, wxALL , 6);
    topSizer->Add(footerSizer, 0, wxALIGN_RIGHT);
    
    SetSizerAndFit(topSizer);
}



void mirrorDialog::getPoints(wxRealPoint &firstPoint, wxRealPoint &secondPoint)
{
    double value1, value2;
    
    _firstPointXTextCtrl->GetValue().ToDouble(&value1);
    _firstPointYTextCtrl->GetValue().ToDouble(&value2);
    firstPoint = wxRealPoint(value1, value2);
    
    _secondPointXTextCtrl->GetValue().ToDouble(&value1);
    _secondPointYTextCtrl->GetValue().ToDouble(&value2);
    secondPoint = wxRealPoint(value1, value2);
}



mirrorDialog::~mirrorDialog()
{
    
}