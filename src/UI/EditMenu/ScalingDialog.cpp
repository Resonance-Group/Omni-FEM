#include <UI/EditMenu/ScalingDialog.h>


scaleDialog::scaleDialog(wxPoint &selectedPoint) : wxDialog(NULL, wxID_ANY, "Scale")
{
    wxFont *font = new wxFont(8.5, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
    
    wxBoxSizer *SFSizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *BPSizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *footerSizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *topSizer = new wxBoxSizer(wxVERTICAL);
    
    wxStaticText *scalingFactorText = new wxStaticText(this, wxID_ANY, "Scaling Factor:", wxPoint(12, 15), wxSize(85, 13));
    scalingFactorText->SetFont(*font);
    _scalingFactorTextCtrl->Create(this, wxID_ANY, "0", wxPoint(104, 12), wxSize(50, 20));
    _scalingFactorTextCtrl->SetFont(*font);
    
    SFSizer->Add(scalingFactorText, 0, wxCENTER | wxALL, 6);
    SFSizer->Add(10, 0, 0);
    SFSizer->Add(_scalingFactorTextCtrl, 0, wxCenter | wxTOP | wxBOTTOM | wxRIGHT, 6);
    
    wxStaticText *BPText = new wxStaticText(this, wxID_ANY, "Base Point (x, y):", wxPoint(12, 41), wxSize(95, 13));
    BPText->SetFont(*font);
    _baseFactorXTextCtrl->Create(this, wxID_ANY, std::to_string(selectedPoint.x), wxPoint(104, 38), wxSize(50, 20));
    _baseFactorXTextCtrl->SetFont(*font);
    _baseFactorYTextCtrl->Create(this, wxID_ANY, std::to_string(selectedPoint.y), wxPoint(158, 38), wxSize(50, 20));
    _baseFactorYTextCtrl->SetFont(*font);
    
    BPSizer->Add(BPText, 0, wxCENTER | wxBOTTOM | wxRIGHT | wxLEFT, 6);
    BPSizer->Add(_baseFactorXTextCtrl, 0, wxCENTER | wxBOTTOM | wxRIGHT, 6);
    BPSizer->Add(_baseFactorYTextCtrl, 0, wxCENTER | wxBOTTOM | wxRIGHT, 6);
    
    wxButton *okButton = new wxButton(this, wxID_OK, "Ok", wxPoint(48, 64), wxSize(75, 23));
    okButton->SetFont(*font);
    
    wxButton *cancelButton = new wxButton(this, wxID_CANCEL, "Cancel", wxPoint(129, 64), wxSize(75, 23));
    cancelButton->SetFont(*font);
    
    footerSizer->Add(okButton, 0, wxCenter | wxLEFT | wxRIGHT | wxBOTTOM, 6);
    footerSizer->Add(cancelButton, 0, wxCENTER | wxRIGHT | wxBOTTOM, 6);
    
    topSizer->Add(SFSizer);
    topSizer->Add(BPSizer);
    topSizer->Add(footerSizer, 0, wxALIGN_RIGHT);
    
    SetSizerAndFit(topSizer);
}


void scaleDialog::getScalingParameters(double &scalingFactor, wxPoint &baseFactor)
{
    double value1, value2;
    
    _scalingFactorTextCtrl->GetValue().ToDouble(&value1);
    scalingFactor = value1;
    
    _baseFactorXTextCtrl->GetValue().ToDouble(&value1);
    _baseFactorYTextCtrl->GetValue().ToDouble(&value2);
    
    baseFactor = wxPoint(value1, value2);
}



scaleDialog::~scaleDialog()
{
    
}