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
    // A comment
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
    
    wxBoxSizer *documentSettingsSizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *gridSettingsSizer = new wxBoxSizer(wxVERTICAL);
    
    wxBoxSizer *documentSettingLine1 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *documentSettingLine2 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *documentSettingLine3 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *documentSettingLine4 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *documentSettingLine5 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *documentSettingLine6 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *documentSettingLine7 = new wxBoxSizer(wxHORIZONTAL);
    
    wxBoxSizer *gridSettingLine1 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *gridSettingLine2 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *gridSettingLine3 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *gridSettingLine4 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *gridSettingLine5 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *gridSettingLine6 = new wxBoxSizer(wxHORIZONTAL);
    
    wxFloatingPointValidator<double> greaterThenZero(15, NULL, wxNUM_VAL_NO_TRAILING_ZEROES);
    greaterThenZero.SetMin(0);
    
    wxFloatingPointValidator<double> angleValidator(15);
    angleValidator.SetRange(0, 360);

    /* The frist section will be creating everything for the grid preferences */
    wxStaticText *gridText = new wxStaticText(gridSettingPanel, wxID_ANY, "Grid Step:");
    gridText->SetFont(*font);
    _gridStepTextCtrl->Create(gridSettingPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(121, 20), 0, greaterThenZero);
    _gridStepTextCtrl->SetFont(*font);
    std::ostream gridSizeStream(_gridStepTextCtrl);
    gridSizeStream << std::setprecision(15);
    gridSizeStream << _preferences->getGridStep();
    
    gridSettingLine1->Add(gridText, 0, wxCENTER | wxALL, 6);
    gridSettingLine1->Add(12, 0, 0);
    gridSettingLine1->Add(_gridStepTextCtrl, 0, wxCENTER | wxBOTTOM | wxRIGHT | wxTOP, 6);
    
    wxStaticText *coordianteText = new wxStaticText(gridSettingPanel, wxID_ANY, "Coordinate:");
    coordianteText->SetFont(*font);
    _coordinateComboBox->Create(gridSettingPanel, wxID_ANY, wxEmptyString, wxPoint(79, 64), wxSize(121, 21), coordianteNameArray);
    _coordinateComboBox->SetFont(*font);
    _coordinateComboBox->SetSelection((int)_preferences->getCoordinateSystem());
    
    gridSettingLine2->Add(coordianteText, 0, wxCENTER | wxBOTTOM | wxLEFT | wxRIGHT, 6);
    gridSettingLine2->Add(_coordinateComboBox, 0, wxCENTER | wxBOTTOM | wxRIGHT, 6);
    
    _showGridCheckBox->Create(gridSettingPanel, wxID_ANY, "Show Grid");
    _showGridCheckBox->SetValue(_preferences->getShowGridState());
    _showGridCheckBox->SetFont(*font);
    _showOriginCheckBox->Create(gridSettingPanel, wxID_ANY, "Show Origin");
    _showOriginCheckBox->SetFont(*font);
    _showOriginCheckBox->SetValue(_preferences->getShowOriginState());
    
    gridSettingLine3->Add(_showGridCheckBox, 0, wxCENTER | wxBOTTOM | wxRIGHT | wxLEFT, 6);
    gridSettingLine3->Add(_showOriginCheckBox, 0, wxCENTER | wxBOTTOM | wxRIGHT, 6);
    
    _snapGridCheckBox->Create(gridSettingPanel, wxID_ANY, "Snap Grid");
    _snapGridCheckBox->SetFont(*font);
    _snapGridCheckBox->SetValue(_preferences->getSnapGridState());
    _showGridAxisCheckBox->Create(gridSettingPanel, wxID_ANY, "Show Grid Axis");
    _showGridAxisCheckBox->SetFont(*font);
    _showGridAxisCheckBox->SetValue(_preferences->getShowAxisState());
    
    gridSettingLine4->Add(_snapGridCheckBox, 0, wxCENTER | wxBOTTOM | wxRIGHT | wxLEFT, 6);
    gridSettingLine4->Add(_showGridAxisCheckBox, 0, wxCENTER | wxBOTTOM | wxRIGHT, 6);
    
    _showBlockNameCheckBox->Create(gridSettingPanel, wxID_ANY, "Show Block Names");
    _showBlockNameCheckBox->SetValue(_preferences->getShowBlockNameState());
    _showBlockNameCheckBox->SetFont(*font);
    
    gridSettingLine5->Add(_showBlockNameCheckBox, 0, wxCENTER | wxBOTTOM | wxRIGHT | wxLEFT, 6);
    
    _reverseMouseZoomCheckBox->Create(gridSettingPanel, wxID_ANY, "Reverse Mouse Zoom Direction");
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
    
    /* This next section is for the preferences related to the settings */
    wxStaticText *probTypeText = new wxStaticText(physicsProblemPreferencesPanel, wxID_ANY, "Problem Type:");
    probTypeText->SetFont(*font);
    _problemTypeComboBox->Create(physicsProblemPreferencesPanel, generalFrameButton::ID_ComboBox1, wxEmptyString, wxPoint(98, 12), wxSize(121, 21), problemTypeNameArray);
    _problemTypeComboBox->SetFont(*font);
    documentSettingLine1->Add(probTypeText, 0, wxCENTER | wxTOP | wxBOTTOM | wxLEFT, 6);
    documentSettingLine1->Add(20, 0, 0);
    documentSettingLine1->Add(_problemTypeComboBox, 0, wxCENTER | wxTOP | wxBOTTOM | wxRIGHT, 6);
   
    wxStaticText *lengthUnitsText = new wxStaticText(physicsProblemPreferencesPanel, wxID_ANY, "Length Units:");
    lengthUnitsText->SetFont(*font);
    _lengthComboBox->Create(physicsProblemPreferencesPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(121, 21), lengthName);
    _lengthComboBox->SetFont(*font);
    documentSettingLine2->Add(lengthUnitsText, 0, wxCENTER | wxBOTTOM | wxLEFT, 6);
    documentSettingLine2->Add(23, 0, 0);
    documentSettingLine2->Add(_lengthComboBox, 0, wxCENTER | wxBOTTOM | wxRIGHT, 6);
    
    if(_problem == physicProblems::PROB_MAGNETICS)
    {
        wxStaticText *acSolverText = new wxStaticText(physicsProblemPreferencesPanel, wxID_ANY, "AC Solver:");
        acSolverText->SetFont(*font);
        _acSolverComboBox->Create(physicsProblemPreferencesPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(121, 21), acSovlerNameArray);
        _acSolverComboBox->SetFont(*font);
        _acSolverComboBox->SetSelection((int)_magneticPreference.getACSolver());
        documentSettingLine3->Add(acSolverText, 0, wxCENTER | wxBOTTOM | wxLEFT, 6);
        documentSettingLine3->Add(41, 0, 0);
        documentSettingLine3->Add(_acSolverComboBox, 0, wxCENTER | wxBOTTOM | wxRIGHT, 6);

        wxStaticText *freqText = new wxStaticText(physicsProblemPreferencesPanel, wxID_ANY, "Frequency (Hz):");
        freqText->SetFont(*font);
        _frequencyTextCtrl->Create(physicsProblemPreferencesPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(121, 20), 0, greaterThenZero);
        std::ostream freqStream(_frequencyTextCtrl);
        freqStream << std::setprecision(3);
        freqStream << _magneticPreference.getFrequency();
        _frequencyTextCtrl->SetFont(*font);
        documentSettingLine4->Add(freqText, 0, wxCENTER | wxBOTTOM | wxLEFT, 6);
        documentSettingLine4->Add(11, 0, 0);
        documentSettingLine4->Add(_frequencyTextCtrl, 0, wxCENTER | wxBOTTOM | wxRIGHT, 6);
    }
   
    wxStaticText *depthText = new wxStaticText(physicsProblemPreferencesPanel, wxID_ANY, "Depth:");
    depthText->SetFont(*font);
    _depthTextCtrl->Create(physicsProblemPreferencesPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(121, 20), 0, greaterThenZero);
    std::ostream dStream(_depthTextCtrl);
    dStream << std::setprecision(4);
    _depthTextCtrl->SetFont(*font);
    documentSettingLine5->Add(depthText, 0, wxCENTER | wxBOTTOM | wxLEFT, 6);
    documentSettingLine5->Add(59, 0, 0);
    documentSettingLine5->Add(_depthTextCtrl, 0, wxCENTER | wxBOTTOM | wxRIGHT, 6);
   
    wxStaticText *solverPrecisionText = new wxStaticText(physicsProblemPreferencesPanel, wxID_ANY, "Solver Precision:");
    solverPrecisionText->SetFont(*font);
    _precisionTextCtrl->Create(physicsProblemPreferencesPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(121, 20), 0, greaterThenZero);
    std::ostream spStream(_precisionTextCtrl);
    spStream << std::setprecision(4);
    _precisionTextCtrl->SetFont(*font);
    documentSettingLine6->Add(solverPrecisionText, 0, wxCENTER | wxBOTTOM | wxLEFT, 6);
    documentSettingLine6->Add(6, 0, 0);
    documentSettingLine6->Add(_precisionTextCtrl, 0, wxCENTER | wxBOTTOM | wxRIGHT, 6);
   
    wxStaticText *minAngleText = new wxStaticText(physicsProblemPreferencesPanel, wxID_ANY, "Min Angle (deg):");
    minAngleText->SetFont(*font);
    _minAngleTextCtrl->Create(physicsProblemPreferencesPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(121, 20), 0, angleValidator);
    std::ostream minAngleStream(_minAngleTextCtrl);
    minAngleStream << std::setprecision(4);
    _minAngleTextCtrl->SetFont(*font);
    documentSettingLine7->Add(minAngleText, 0, wxCENTER | wxBOTTOM | wxLEFT, 6);
    documentSettingLine7->Add(7, 0, 0);
    documentSettingLine7->Add(_minAngleTextCtrl, 0, wxCENTER | wxBOTTOM | wxRIGHT, 6);
    
    wxStaticBoxSizer *commentSizer = new wxStaticBoxSizer(wxVERTICAL, physicsProblemPreferencesPanel, "Comments");
    commentSizer->GetStaticBox()->SetFont(*font);
    _commentsTextCtrl->Create(commentSizer->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(192, 87), wxTE_MULTILINE);
    _commentsTextCtrl->SetFont(*font);
    commentSizer->Add(_commentsTextCtrl, 0, wxALL, 6);

    documentSettingsSizer->Add(documentSettingLine1);
    documentSettingsSizer->Add(documentSettingLine2);
    
    if(_problem == physicProblems::PROB_MAGNETICS)
    {
        documentSettingsSizer->Add(documentSettingLine3);
        documentSettingsSizer->Add(documentSettingLine4);
    }
    
    documentSettingsSizer->Add(documentSettingLine5);
    documentSettingsSizer->Add(documentSettingLine6);
    documentSettingsSizer->Add(documentSettingLine7);
    documentSettingsSizer->Add(commentSizer, 0, wxLEFT | wxRIGHT | wxCENTER, 6);
  //  topSizer->Add(commentSizer, 0, wxLEFT | wxRIGHT | wxCENTER, 6);
    
    if(_problem == physicProblems::PROB_ELECTROSTATIC)
    {
        _problemTypeComboBox->SetSelection((int)_electricalPreference.getProblemType());
        _lengthComboBox->SetSelection((int)_electricalPreference.getUnitLength());
        dStream << _electricalPreference.getDepth();
        spStream << _electricalPreference.getPrecision();
        minAngleStream << _electricalPreference.getMinAngle();
        _commentsTextCtrl->SetValue(_electricalPreference.getComments());
    }
    else if(_problem == physicProblems::PROB_MAGNETICS)
    {
        _problemTypeComboBox->SetSelection((int)_magneticPreference.getProblemType());
        _lengthComboBox->SetSelection((int)_magneticPreference.getUnitLength());
        dStream << _magneticPreference.getDepth();
        spStream << _magneticPreference.getPrecision();
        minAngleStream << _magneticPreference.getMinAngle();
        _commentsTextCtrl->SetValue(_magneticPreference.getComments());
    }
    
    if(_problemTypeComboBox->GetSelection() == 1)
    {
        _depthTextCtrl->Enable(false);
    }
    
    gridSettingPanel->SetSizerAndFit(gridSettingsSizer);
    physicsProblemPreferencesPanel->SetSizerAndFit(documentSettingsSizer);
    
    base->AddPage(gridSettingPanel, "Grid Settings");
    base->AddPage(physicsProblemPreferencesPanel, "Problem Settings");
    
    LayoutDialog();
}




void globalPreferencesDialog::onProblemTypeComboBox(wxCommandEvent &event)
{
    switch(_problemTypeComboBox->GetSelection())
    {
        case 0:// This first case is if the user selected the problem type to be planar
            _depthTextCtrl->Enable(true);
            break;
        case 1:// This second case is if the user selected the problem type to be axisymmetric
            _depthTextCtrl->Enable(false);
            break;
        default:// Everything else
            break;
    }
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
    
    /* THis section will get the preferences for the physics problem */
    electricPref.setProblemType((problemTypeEnum)_problemTypeComboBox->GetSelection());
    electricPref.setUnitLength((unitLengthEnum)_lengthComboBox->GetSelection());
    _depthTextCtrl->GetValue().ToDouble(&value);
    electricPref.setDepth(value);
    _precisionTextCtrl->GetValue().ToDouble(&value);
    electricPref.setPrecision(value);
    _minAngleTextCtrl->GetValue().ToDouble(&value);
    electricPref.setMinAngle(value);
    electricPref.setComments(_commentsTextCtrl->GetValue());
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
    
    /* THis section will get the preferences for the physics problem */
    magneticPref.setProblemType((problemTypeEnum)_problemTypeComboBox->GetSelection());
    magneticPref.setUnitLength((unitLengthEnum)_lengthComboBox->GetSelection());
    _depthTextCtrl->GetValue().ToDouble(&value);
    magneticPref.setDepth(value);
    _precisionTextCtrl->GetValue().ToDouble(&value);
    magneticPref.setPrecision(value);
    _minAngleTextCtrl->GetValue().ToDouble(&value);
    magneticPref.setMinAngle(value);
    magneticPref.setComments(_commentsTextCtrl->GetValue());
    magneticPref.setACSolver((acSolverEnum)_acSolverComboBox->GetSelection());
    _frequencyTextCtrl->GetValue().ToDouble(&value);
    magneticPref.setFrequency(value);
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



wxBEGIN_EVENT_TABLE(globalPreferencesDialog, wxPropertySheetDialog)
    EVT_COMBOBOX(generalFrameButton::ID_ComboBox1, globalPreferencesDialog::onProblemTypeComboBox)
wxEND_EVENT_TABLE()