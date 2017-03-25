#include <UI/EditMenu/GlobalPreferencesDialog.h>



globalPreferencesDialog::globalPreferencesDialog(wxWindow *par, gridPreferences *gridPref, magneticPreference pref)
{
    _problem = physicProblems::PROB_MAGNETICS;
    _magneticPreference = pref;
    _preferences = gridPref;
    createDialog(par);
}



globalPreferencesDialog::globalPreferencesDialog(wxWindow *par, gridPreferences *gridPref, electroStaticPreference pref)
{
    _problem = physicProblems::PROB_ELECTROSTATIC;
    _electricalPreference = pref;
    _preferences = gridPref;
    createDialog(par);
}



void globalPreferencesDialog::createDialog(wxWindow *par)
{
    this->Create(par, wxID_ANY, "Preferences");
    this->CreateButtons();
    
    wxBookCtrlBase *base = GetBookCtrl();
    
    wxFont *font = new wxFont(8.5, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
    
    this->SetFont(*font);
    base->SetFont(*font);
    
    wxPanel *gridSettingPanel = new wxPanel(base);
    wxPanel *physicsProblemPreferencesPanel = new wxPanel(base);
  //  GetBookCtrl()->AddPage(panel, "Input Settings");
    
    wxArrayString lengthName;
    wxArrayString problemTypeNameArray;
    wxArrayString coordianteNameArray;
    wxArrayString acSovlerNameArray;
    
    lengthName.Add("Inches");
    lengthName.Add("Millimeters");
    lengthName.Add("Centimeters");
    lengthName.Add("Meters");
    lengthName.Add("Mils");
    lengthName.Add("Micrometers");
    
    problemTypeNameArray.Add("Planar");
    problemTypeNameArray.Add("Axisymmetric");
    
    coordianteNameArray.Add("Cartesian");
    coordianteNameArray.Add("Polar");
    
    acSovlerNameArray.Add("Succ. Approx");
    acSovlerNameArray.Add("Newton");
    
    wxStaticBoxSizer *documentSettingsSizer = new wxStaticBoxSizer(wxVERTICAL, physicsProblemPreferencesPanel);
    wxStaticBoxSizer *gridSettingsSizer = new wxStaticBoxSizer(wxVERTICAL, gridSettingPanel);
    
    wxBoxSizer *documentSettingLine1 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *documentSettingLine2 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *documentSettingLine3 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *documentSettingLine4 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *documentSettingLine5 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *documentSettingLine6 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *documentSettingLine7 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *documentSettingLine8 = new wxBoxSizer(wxHORIZONTAL);
    
    wxBoxSizer *gridSettingLine1 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *gridSettingLine2 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *gridSettingLine3 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *gridSettingLine4 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *gridSettingLine5 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *gridSettingLine6 = new wxBoxSizer(wxHORIZONTAL);
    
    wxFloatingPointValidator<double> greaterThenZero(15, NULL, wxNUM_VAL_NO_TRAILING_ZEROES);
    greaterThenZero.SetMin(0);

/* The frist section will be creating everything for the grid preferences */
    wxStaticText *gridText = new wxStaticText(gridSettingsSizer->GetStaticBox(), wxID_ANY, "Grid Step:");
    gridText->SetFont(*font);
    _gridStepTextCtrl->Create(gridSettingsSizer->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(121, 20), 0, greaterThenZero);
    _gridStepTextCtrl->SetFont(*font);
    std::ostream gridSizeStream(_gridStepTextCtrl);
    gridSizeStream << std::setprecision(15);
    gridSizeStream << _preferences->getGridStep();
    
    gridSettingLine1->Add(gridText, 0, wxCENTER | wxALL, 6);
    gridSettingLine1->Add(12, 0, 0);
    gridSettingLine1->Add(_gridStepTextCtrl, 0, wxCENTER | wxBOTTOM | wxRIGHT | wxTOP, 6);
    
    wxStaticText *coordianteText = new wxStaticText(gridSettingsSizer->GetStaticBox(), wxID_ANY, "Coordinate:");
    coordianteText->SetFont(*font);
    _coordinateComboBox->Create(gridSettingsSizer->GetStaticBox(), wxID_ANY, wxEmptyString, wxPoint(79, 64), wxSize(121, 21), coordianteNameArray);
    _coordinateComboBox->SetFont(*font);
    _coordinateComboBox->SetSelection((int)_preferences->getCoordinateSystem());
    
    gridSettingLine2->Add(coordianteText, 0, wxCENTER | wxBOTTOM | wxLEFT | wxRIGHT, 6);
    gridSettingLine2->Add(_coordinateComboBox, 0, wxCENTER | wxBOTTOM | wxRIGHT, 6);
    
    _showGridCheckBox->Create(gridSettingsSizer->GetStaticBox(), wxID_ANY, "Show Grid");
    _showGridCheckBox->SetValue(_preferences->getShowGridState());
    _showGridCheckBox->SetFont(*font);
    _showOriginCheckBox->Create(gridSettingsSizer->GetStaticBox(), wxID_ANY, "Show Origin");
    _showOriginCheckBox->SetFont(*font);
    _showOriginCheckBox->SetValue(_preferences->getShowOriginState());
    
    gridSettingLine3->Add(_showGridCheckBox, 0, wxCENTER | wxBOTTOM | wxRIGHT | wxLEFT, 6);
    gridSettingLine3->Add(_showOriginCheckBox, 0, wxCENTER | wxBOTTOM | wxRIGHT, 6);
    
    _snapGridCheckBox->Create(gridSettingsSizer->GetStaticBox(), wxID_ANY, "Snap Grid");
    _snapGridCheckBox->SetFont(*font);
    _snapGridCheckBox->SetValue(_preferences->getSnapGridState());
    _showGridAxisCheckBox->Create(gridSettingsSizer->GetStaticBox(), wxID_ANY, "Show Grid Axis");
    _showGridAxisCheckBox->SetFont(*font);
    _showGridAxisCheckBox->SetValue(_preferences->getShowAxisState());
    
    gridSettingLine4->Add(_snapGridCheckBox, 0, wxCENTER | wxBOTTOM | wxRIGHT | wxLEFT, 6);
    gridSettingLine4->Add(_showGridAxisCheckBox, 0, wxCENTER | wxBOTTOM | wxRIGHT, 6);
    
    _showBlockNameCheckBox->Create(gridSettingsSizer->GetStaticBox(), wxID_ANY, "Show Block Names");
    _showBlockNameCheckBox->SetValue(_preferences->getShowBlockNameState());
    _showBlockNameCheckBox->SetFont(*font);
    
    gridSettingLine5->Add(_showBlockNameCheckBox, 0, wxCENTER | wxBOTTOM | wxRIGHT | wxLEFT, 6);
    
    _reverseMouseZoomCheckBox->Create(gridSettingsSizer->GetStaticBox(), wxID_ANY, "Reverse Mouse Zoom Direction");
    _reverseMouseZoomCheckBox->SetValue(_preferences->getMouseZoomReverseState());
    _reverseMouseZoomCheckBox->SetFont(*font);
    
    gridSettingLine6->Add(_reverseMouseZoomCheckBox, 0, wxCENTER | wxRIGHT | wxLEFT | wxBOTTOM, 6);
    
    gridSettingsSizer->Add(gridSettingLine1);
    gridSettingsSizer->Add(gridSettingLine2);
    gridSettingsSizer->Add(0, 10, 0);
    gridSettingsSizer->Add(gridSettingLine3);
    gridSettingsSizer->Add(gridSettingLine4);
    gridSettingsSizer->Add(gridSettingLine5);
    gridSettingsSizer->Add(gridSettingLine6);
    
    gridSettingPanel->SetSizerAndFit(gridSettingsSizer);
    
    base->AddPage(gridSettingPanel, "Grid Settings");
    base->AddPage(physicsProblemPreferencesPanel, "Problem Settings");
    
    LayoutDialog();
}



void globalPreferencesDialog::getPreferences(electroStaticPreference &electricPref)
{
    double value;
    
    /* This section will get the values for the grid preferences */
    _gridStepTextCtrl->GetValue().ToDouble(&value);
    _preferences->setGridStep(value);
    
    _preferences->setCoordinateSystem((planarCoordinateEnum)_coordinateComboBox->GetSelection());

    _preferences->setShowGridState(_showGridCheckBox->GetValue());
    _preferences->setShowOriginState(_showOriginCheckBox->GetValue());
    _preferences->setSnapGridState(_snapGridCheckBox->GetValue());
    _preferences->setShowAxisState(_showGridAxisCheckBox->GetValue());
    _preferences->setShowBlockNameState(_showBlockNameCheckBox->GetValue());
    _preferences->setMouseZoomReverseState(_reverseMouseZoomCheckBox->GetValue());
}



void globalPreferencesDialog::getPreferences(magneticPreference &magneticPref)
{
    double value;
    
    /* This section will get the values for the grid preferences */
    _gridStepTextCtrl->GetValue().ToDouble(&value);
    _preferences->setGridStep(value);
    
    _preferences->setCoordinateSystem((planarCoordinateEnum)_coordinateComboBox->GetSelection());

    _preferences->setShowGridState(_showGridCheckBox->GetValue());
    _preferences->setShowOriginState(_showOriginCheckBox->GetValue());
    _preferences->setSnapGridState(_snapGridCheckBox->GetValue());
    _preferences->setShowAxisState(_showGridAxisCheckBox->GetValue());
    _preferences->setShowBlockNameState(_showBlockNameCheckBox->GetValue());
    _preferences->setMouseZoomReverseState(_reverseMouseZoomCheckBox->GetValue());
}      



void globalPreferencesDialog::updateInterface()
{
    if(_problem == physicProblems::PROB_ELECTROSTATIC)
    {
        
    }
    else if(_problem == physicProblems::PROB_MAGNETICS)
    {
        
    }
}