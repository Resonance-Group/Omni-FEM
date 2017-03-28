#include <UI/ExteriorRegion.h>


exteriorRegionDialog::exteriorRegionDialog(wxWindow *par) : wxDialog(par, wxID_ANY, "Exterior Region")
{
    wxFont *font = new wxFont(8.5, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
    
    wxBoxSizer *line1Sizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *line2Sizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *line3Sizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *footerSizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *topSizer = new wxBoxSizer(wxVERTICAL);
    
    wxStaticText *centerText = new wxStaticText(this, wxID_ANY, "Center of the Exterior:");
    centerText->SetFont(*font);
    _centerExteriorTextCtrl->Create(this, wxID_ANY, "0", wxDefaultPosition, wxSize(80, 20));
    _centerExteriorTextCtrl->SetFont(*font);
    line1Sizer->Add(centerText, 0, wxCENTER | wxALL, 6);
    line1Sizer->Add(1, 0, 0);
    line1Sizer->Add(_centerExteriorTextCtrl, 0, wxCENTER | wxTOP | wxBOTTOM | wxRIGHT, 6);
    
    wxStaticText *radiusExteriorText = new wxStaticText(this, wxID_ANY, "Radius of the Exterior:");
    radiusExteriorText->SetFont(*font);
    _radiusExteriorTextCtrl->Create(this, wxID_ANY, "0", wxDefaultPosition, wxSize(80, 20));
    _radiusExteriorTextCtrl->SetFont(*font);
    line2Sizer->Add(radiusExteriorText, 0, wxCENTER | wxBOTTOM | wxLEFT | wxRIGHT, 6);
    line2Sizer->Add(_radiusExteriorTextCtrl, 0, wxCENTER | wxBOTTOM | wxRIGHT, 6);
    
    wxStaticText *radiusInteriorText = new wxStaticText(this, wxID_ANY, "Radius of the Interior:");
    radiusInteriorText->SetFont(*font);
    _radiusInteriorTextCtrl->Create(this, wxID_ANY, "0", wxDefaultPosition, wxSize(80, 20));
    _radiusInteriorTextCtrl->SetFont(*font);
    line3Sizer->Add(radiusInteriorText, 0, wxCENTER | wxBOTTOM | wxLEFT | wxRIGHT, 6);
    line3Sizer->Add(3, 0, 0);
    line3Sizer->Add(_radiusInteriorTextCtrl, 0, wxCENTER | wxBOTTOM | wxRIGHT, 6);
    
    wxButton *okButton = new wxButton(this, wxID_OK, "Ok", wxDefaultPosition, wxSize(75, 23));
    okButton->SetFont(*font);
    
    wxButton *cancelButton = new wxButton(this, wxID_CANCEL, "Cancel", wxDefaultPosition, wxSize(75, 23));
    cancelButton->SetFont(*font);
    
    footerSizer->Add(okButton, 0, wxCENTER | wxBOTTOM | wxRIGHT, 6);
    footerSizer->Add(cancelButton, 0, wxCENTER | wxBOTTOM | wxRIGHT, 6);
    
    topSizer->Add(line1Sizer);
    topSizer->Add(line2Sizer);
    topSizer->Add(line3Sizer);
    topSizer->Add(footerSizer, 0, wxALIGN_RIGHT);
    
    SetSizerAndFit(topSizer);
}


void exteriorRegionDialog::setParameters(double &centerOfExterior, double &radiusExterior, double &radiusInterior)
{
    std::ostream centerExteriorStream(_centerExteriorTextCtrl);
    std::ostream radiusExteriorStream(_radiusExteriorTextCtrl);
    std::ostream radiusInteriorStream(_radiusInteriorTextCtrl);
    
    _centerExteriorTextCtrl->SetValue(wxEmptyString);
    centerExteriorStream << std::setprecision(4);
    centerExteriorStream << centerOfExterior;
    
    _radiusExteriorTextCtrl->SetValue(wxEmptyString);
    radiusExteriorStream << std::setprecision(4);
    radiusExteriorStream << radiusExterior;
    
    _radiusInteriorTextCtrl->SetValue(wxEmptyString);
    radiusInteriorStream << std::setprecision(4);
    radiusInteriorStream << radiusInterior;
}



void exteriorRegionDialog::getParameters(double &centerOfExterior, double &radiusExterior, double &radiusInterior)
{
    double value;
    
    _centerExteriorTextCtrl->GetValue().ToDouble(&value);
    centerOfExterior = value;
    
    _radiusExteriorTextCtrl->GetValue().ToDouble(&value);
    radiusExterior = value;
    
    _radiusInteriorTextCtrl->GetValue().ToDouble(&value);
    radiusInterior = value;
}



exteriorRegionDialog::~exteriorRegionDialog()
{
    
}