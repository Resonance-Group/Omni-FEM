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
    
    wxStaticText *gridText = new wxStaticText(this, wxID_ANY, "Grid Step:");
    gridText->SetFont(*font);
    _gridSizeTextCtrl->Create(this, wxID_ANY, wxEmptyString);
    _gridSizeTextCtrl->SetFont(*font);
    
    line1Sizer->Add(gridText, 0, wxCENTER | wxALL, 6);
    line1Sizer->Add(12, 0, 0);
    line1Sizer->Add(_gridSizeTextCtrl, 0, wxCENTER | wxBOTTOM | wxRIGHT | wxTOP, 6);
    
    wxStaticText *coordianteText = new wxStaticText(this, wxID_ANY, "Coordinate:");
    coordianteText->SetFont(*font);
    _coordinateComboBox->Create(this, wxID_ANY, wxEmptyString, wxPoint(79, 64), wxSize(121, 21), *selectionArray);
    _coordinateComboBox->SetFont(*font);
    _coordinateComboBox->SetSelection(0);
    
    line2Sizer->Add(coordianteText, 0, wxCENTER | wxBOTTOM | wxLEFT | wxRIGHT, 6);
    line2Sizer->Add(_coordinateComboBox, 0, wxCENTER | wxBOTTOM | wxRIGHT, 6);
    
    _showGridCheckBox->Create(this, wxID_ANY, "Show Grid");
    _showGridCheckBox->SetValue(_preferences.getShowGridState());
    _showGridCheckBox->SetFont(*font);
    _showOriginCheckBox->Create(this, wxID_ANY, "Show Origin");
    _showOriginCheckBox->SetFont(*font);
    _showOriginCheckBox->SetValue(_preferences.getShowOriginState());
    
    line3Sizer->Add(_showGridCheckBox, 0, wxCENTER | wxBOTTOM | wxRIGHT | wxLEFT, 6);
    line3Sizer->Add(_showOriginCheckBox, 0, wxCENTER | wxBOTTOM | wxRIGHT, 6);
    
    _snapGridCheckBox->Create(this, wxID_ANY, "Snap Grid");
    _snapGridCheckBox->SetFont(*font);
    _snapGridCheckBox->SetValue(_preferences.getSnapGridState());
    _showGridAxisCheckBox->Create(this, wxID_ANY, "Show Grid Axis");
    _showGridAxisCheckBox->SetFont(*font);
    _showGridAxisCheckBox->SetValue(_preferences.getShowAxisState());
    
    line4Sizer->Add(_snapGridCheckBox, 0, wxCENTER | wxBOTTOM | wxRIGHT | wxLEFT, 6);
    line4Sizer->Add(_showGridAxisCheckBox, 0, wxCENTER | wxBOTTOM | wxRIGHT, 6);
    
    _showBlockNameCheckBox->Create(this, wxID_ANY, "Show Block Names");
    _showBlockNameCheckBox->SetValue(_preferences.getShowBlockNameState());
    _showBlockNameCheckBox->SetFont(*font);
    
    line5Sizer->Add(_showBlockNameCheckBox, 0, wxCENTER | wxBOTTOM | wxRIGHT | wxLEFT, 6);
    
    _reverseMouseZoomCheckBox->Create(this, wxID_ANY, "Reverse Mouse Zoom Direction");
    _reverseMouseZoomCheckBox->SetValue(_preferences.getMouseZoomReverseState());
    _reverseMouseZoomCheckBox->SetFont(*font);
    
    line6Sizer->Add(_reverseMouseZoomCheckBox, 0, wxCENTER | wxRIGHT | wxLEFT | wxBOTTOM, 6);
    
    wxButton *okButton = new wxButton(this, wxID_OK, "Ok", wxDefaultPosition, wxSize(75, 23));
    okButton->SetFont(*font);
    
    wxButton *cancelButton = new wxButton(this, wxID_CANCEL, "Cancel", wxDefaultPosition, wxSize(75, 23));
    cancelButton->SetFont(*font);
    
    footerSizer->Add(okButton, 0, wxCENTER | wxBOTTOM | wxRIGHT | wxLEFT, 6);
    footerSizer->Add(cancelButton, 0, wxCENTER | wxBOTTOM | wxRIGHT, 6);
    
    topSizer->Add(line1Sizer);
    topSizer->Add(line2Sizer);
    topSizer->Add(0, 10, 0);
    topSizer->Add(line3Sizer);
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
    
    _gridSizeTextCtrl->GetValue().ToDouble(&value);
    preferences.setGridStep(value);
    
    temp = _coordinateComboBox->GetSelection() + 1;
    preferences.setCoordinateSystem((planarCoordinateEnum)temp);
    
    preferences.setShowGridState(_showGridCheckBox->GetValue());
    preferences.setSnapGridState(_snapGridCheckBox->GetValue());
    preferences.setShowOriginState(_showOriginCheckBox->GetValue());
    preferences.setShowBlockNameState(_showBlockNameCheckBox->GetValue());
    preferences.setShowAxisState(_showGridAxisCheckBox->GetValue());
    preferences.setMouseZoomReverseState(_reverseMouseZoomCheckBox->GetValue());
}



void gridPreferencesDialog::setParameters(gridPreferences &preferences)
{
    _preferences = preferences;
    updateInterface();
}



void gridPreferencesDialog::updateInterface()
{
    std::ostream gridSizeStream(_gridSizeTextCtrl);
    
    _gridSizeTextCtrl->SetValue(wxEmptyString);
    gridSizeStream << std::setprecision(3);
    gridSizeStream << _preferences.getGridStep();
    
    if(_preferences.getCoordinateSystem() != planarCoordinateEnum::NO_COORDINATE_DEFINED)
        _coordinateComboBox->SetSelection((int)_preferences.getCoordinateSystem() - 1);
    else
        _coordinateComboBox->SetSelection(0);
        
    _showGridCheckBox->SetValue(_preferences.getShowGridState());
    _showOriginCheckBox->SetValue(_preferences.getShowOriginState());
    _snapGridCheckBox->SetValue(_preferences.getSnapGridState());
    _showBlockNameCheckBox->SetValue(_preferences.getShowBlockNameState());
    _showGridAxisCheckBox->SetValue(_preferences.getShowAxisState());
    _reverseMouseZoomCheckBox->SetValue(_preferences.getMouseZoomReverseState());
}



gridPreferencesDialog::~gridPreferencesDialog()
{
    
}