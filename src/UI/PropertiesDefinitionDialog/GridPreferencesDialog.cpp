#include <UI/GridPreferencesDialog.h>

gridPreferencesDialog::gridPreferencesDialog() : wxDialog(NULL, wxID_ANY, "Grid Preferences")
{
    wxFont *font = new wxFont(8.5, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
    
    wxBoxSizer *line1Sizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *line2Sizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *line3Sizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *line4Sizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *line5Sizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *line6Sizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *footerSizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *topSizer = new wxBoxSizer(wxVERTICAL);
    
    wxArrayString *selectionArray = new wxArrayString();
    selectionArray->Add("Cartesian");
    selectionArray->Add("Polar");
    
    wxStaticText *ppuText = new wxStaticText(this, wxID_ANY, "Pixels/Unit:");
    ppuText->SetFont(*font);
    _ppuTextCtrl->Create(this, wxID_ANY, wxEmptyString, wxPoint(79, 12), wxSize(121, 20));
    _ppuTextCtrl->SetFont(*font);
    
    line1Sizer->Add(ppuText, 0, wxCENTER | wxALL, 6);
    line1Sizer->Add(3, 0, 0);
    line1Sizer->Add(_ppuTextCtrl, 0, wxCENTER | wxTOP | wxBOTTOM | wxRIGHT, 6);
    
    wxStaticText *gridText = new wxStaticText(this, wxID_ANY, "Grid Size:");
    gridText->SetFont(*font);
    _gridSizeTextCtrl->Create(this, wxID_ANY, wxEmptyString, wxPoint(79, 38), wxSize(121, 20));
    _gridSizeTextCtrl->SetFont(*font);
    
    line2Sizer->Add(gridText, 0, wxCENTER | wxBOTTOM | wxLEFT | wxRIGHT, 6);
    line2Sizer->Add(12, 0, 0);
    line2Sizer->Add(_gridSizeTextCtrl, 0, wxCENTER | wxBOTTOM | wxRIGHT, 6);
    
    wxStaticText *coordianteText = new wxStaticText(this, wxID_ANY, "Coordinate:");
    coordianteText->SetFont(*font);
    _coordinateComboBox->Create(this, wxID_ANY, wxEmptyString, wxPoint(79, 64), wxSize(121, 21), *selectionArray);
    _coordinateComboBox->SetFont(*font);
    _coordinateComboBox->SetSelection(0);
    
    line3Sizer->Add(coordianteText, 0, wxCENTER | wxBOTTOM | wxLEFT | wxRIGHT, 6);
    line3Sizer->Add(_coordinateComboBox, 0, wxCENTER | wxBOTTOM | wxRIGHT, 6);
    
    _showGridCheckBox->Create(this, wxID_ANY, "Show Grid", wxPoint(15, 64), wxSize(80, 17));
    _showGridCheckBox->SetFont(*font);
    _showOriginCheckBox->Create(this, wxID_ANY, "Show Origin", wxPoint(102, 64), wxSize(90, 17));
    _showOriginCheckBox->SetFont(*font);
    
    line4Sizer->Add(_showGridCheckBox, 0, wxCENTER | wxBOTTOM | wxRIGHT | wxLEFT, 6);
    line4Sizer->Add(_showOriginCheckBox, 0, wxCENTER | wxBOTTOM | wxRIGHT, 6);
    
    _snapGridCheckBox->Create(this, wxID_ANY, "Snap Grid", wxPoint(15, 87), wxSize(80, 17));
    _snapGridCheckBox->SetFont(*font);
    
    line5Sizer->Add(_snapGridCheckBox, 0, wxCENTER | wxBOTTOM | wxRIGHT | wxLEFT, 6);
    
    _showBlockNameCheckBox->Create(this, wxID_ANY, "Show Block Names", wxPoint(15, 110), wxSize(135, 17));
    _showBlockNameCheckBox->SetFont(*font);
    
    line6Sizer->Add(_showBlockNameCheckBox, 0, wxCENTER | wxBOTTOM | wxRIGHT | wxLEFT, 6);
    
    wxButton *okButton = new wxButton(this, wxID_OK, "Ok", wxPoint(23, 133), wxSize(75, 23));
    okButton->SetFont(*font);
    
    wxButton *cancelButton = new wxButton(this, wxID_CANCEL, "Cancel", wxPoint(104, 133), wxSize(75, 23));
    cancelButton->SetFont(*font);
    
    footerSizer->Add(okButton, 0, wxCENTER | wxBOTTOM | wxRIGHT | wxLEFT, 6);
    footerSizer->Add(cancelButton, 0, wxCENTER | wxBOTTOM | wxRIGHT, 6);
    
    topSizer->Add(line1Sizer);
    topSizer->Add(line2Sizer);
    topSizer->Add(line3Sizer);
    topSizer->Add(0, 10, 0);
    topSizer->Add(line4Sizer);
    topSizer->Add(line5Sizer);
    topSizer->Add(line6Sizer);
    topSizer->Add(footerSizer, 0, wxALIGN_RIGHT);
    
    SetSizerAndFit(topSizer);
    
    updateInterface();
}



void gridPreferencesDialog::getParameters(gridPreferences &preferences)
{
    double value;
    int temp;
    
    _ppuTextCtrl->GetValue().ToDouble(&value);
    preferences.setPPU(value);
    
    _gridSizeTextCtrl->GetValue().ToDouble(&value);
    preferences.setGridSize(value);
    
    temp = _coordinateComboBox->GetSelection() + 1;
    preferences.setCoordinateSystem((planarCoordinateEnum)temp);
    
    preferences.setShowGridState(_showGridCheckBox->GetValue());
    preferences.setSnapGridState(_snapGridCheckBox->GetValue());
    preferences.setShowOriginState(_showOriginCheckBox->GetValue());
    preferences.setShowBlockNameState(_showBlockNameCheckBox->GetValue());
}



void gridPreferencesDialog::setParameters(gridPreferences &preferences)
{
    _preferences = preferences;
    updateInterface();
}



void gridPreferencesDialog::updateInterface()
{
    std::ostream ppuStream(_ppuTextCtrl);
    std::ostream gridSizeStream(_gridSizeTextCtrl);
    
    _ppuTextCtrl->SetValue(wxEmptyString);
    ppuStream << std::setprecision(3);
    ppuStream << _preferences.getPPU();
    
    _gridSizeTextCtrl->SetValue(wxEmptyString);
    gridSizeStream << std::setprecision(3);
    gridSizeStream << _preferences.getGridSize();
    
    if(_preferences.getCoordinateSystem() != planarCoordinateEnum::NO_COORDINATE_DEFINED)
        _coordinateComboBox->SetSelection((int)_preferences.getCoordinateSystem() - 1);
    else
        _coordinateComboBox->SetSelection(0);
        
    _showGridCheckBox->SetValue(_preferences.getShowGridState());
    _showOriginCheckBox->SetValue(_preferences.getShowOriginState());
    _snapGridCheckBox->SetValue(_preferences.getSnapGridState());
    _showBlockNameCheckBox->SetValue(_preferences.getShowBlockNameState());
}



gridPreferencesDialog::~gridPreferencesDialog()
{
    
}