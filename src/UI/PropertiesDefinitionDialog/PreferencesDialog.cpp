#include <UI/PreferencesDialog.h>
#include <iostream>
#include <iomanip>

preferencesDialog::preferencesDialog(wxWindow *par, magneticPreference pref) : wxDialog(par, wxID_ANY, "Problem Preferences")
{
    _magPreference = pref;
    _problem = physicProblems::PROB_MAGNETICS;

    
   
    createDialog();
}



preferencesDialog::preferencesDialog(wxWindow *par, electroStaticPreference pref) : wxDialog(par, wxID_ANY, "Problem Definition")
{
    _electrPreference = pref;
    _problem = physicProblems::PROB_ELECTROSTATIC;
    
    createDialog();
}



void preferencesDialog::createDialog()
{
    wxFont *font = new wxFont(8.5, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
    
    wxFloatingPointValidator<double> greaterThenZero(15, NULL, wxNUM_VAL_NO_TRAILING_ZEROES);
    greaterThenZero.SetMin(0);
    
    wxFloatingPointValidator<double> angleValidator(15, NULL, wxNUM_VAL_NO_TRAILING_ZEROES);
    angleValidator.SetRange(0, 360);
    
    wxBoxSizer *probTypeSizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *lengthSizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *freqSizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *depthSizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *solverPreSizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *minAngleSizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *acSolverSizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *topSizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *footerSizer = new wxBoxSizer(wxHORIZONTAL);
    
    wxArrayString probTypeNameArray;
    wxArrayString lengthUnitsNameArray;
    wxArrayString acSolverNameArray;
    
    probTypeNameArray.Add("Planar");
    probTypeNameArray.Add("Axisymmetric");
   
    lengthUnitsNameArray.Add("Inches");
    lengthUnitsNameArray.Add("Millimeters");
    lengthUnitsNameArray.Add("Centimeters");
    lengthUnitsNameArray.Add("Meters");
    lengthUnitsNameArray.Add("Mils");
    lengthUnitsNameArray.Add("Micrometers");
    
    acSolverNameArray.Add("Succ. Approx");
    acSolverNameArray.Add("Newton");
    
    wxStaticText *probTypeText = new wxStaticText(this, wxID_ANY, "Problem Type:");
    probTypeText->SetFont(*font);
    _problemTypeComboBox->Create(this, generalFrameButton::ID_ComboBox1, wxEmptyString, wxDefaultPosition, wxSize(121, 21), probTypeNameArray);
    _problemTypeComboBox->SetFont(*font);
    probTypeSizer->Add(probTypeText, 0, wxCENTER | wxTOP | wxBOTTOM | wxLEFT, 6);
    probTypeSizer->Add(20, 0, 0);
    probTypeSizer->Add(_problemTypeComboBox, 0, wxCENTER | wxTOP | wxBOTTOM | wxRIGHT, 6);
   
    wxStaticText *lengthUnitsText = new wxStaticText(this, wxID_ANY, "Length Units:");
    lengthUnitsText->SetFont(*font);
    _lengthUnitsComboBox->Create(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(121, 21), lengthUnitsNameArray);
    _lengthUnitsComboBox->SetFont(*font);
    lengthSizer->Add(lengthUnitsText, 0, wxCENTER | wxBOTTOM | wxLEFT, 6);
    lengthSizer->Add(23, 0, 0);
    lengthSizer->Add(_lengthUnitsComboBox, 0, wxCENTER | wxBOTTOM | wxRIGHT, 6);
    
    if(_problem == physicProblems::PROB_MAGNETICS)
    {
        wxStaticText *acSolverText = new wxStaticText(this, wxID_ANY, "AC Solver:");
        acSolverText->SetFont(*font);
        _acSolverComboBox->Create(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(121, 21), acSolverNameArray);
        _acSolverComboBox->SetFont(*font);
        _acSolverComboBox->SetSelection((int)_magPreference.getACSolver());
        acSolverSizer->Add(acSolverText, 0, wxCENTER | wxBOTTOM | wxLEFT, 6);
        acSolverSizer->Add(41, 0, 0);
        acSolverSizer->Add(_acSolverComboBox, 0, wxCENTER | wxBOTTOM | wxRIGHT, 6);

        wxStaticText *freqText = new wxStaticText(this, wxID_ANY, "Frequency (Hz):");
        freqText->SetFont(*font);
        _frequencyTextCtrl->Create(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(121, 20), 0, greaterThenZero);
        std::ostream freqStream(_frequencyTextCtrl);
        freqStream << std::setprecision(4);
        freqStream << _magPreference.getFrequency();
        _frequencyTextCtrl->SetFont(*font);
        freqSizer->Add(freqText, 0, wxCENTER | wxBOTTOM | wxLEFT, 6);
        freqSizer->Add(11, 0, 0);
        freqSizer->Add(_frequencyTextCtrl, 0, wxCENTER | wxBOTTOM | wxRIGHT, 6);
    }
   
    wxStaticText *depthText = new wxStaticText(this, wxID_ANY, "Depth:");
    depthText->SetFont(*font);
    _depthTextCtrl->Create(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(121, 20), 0, greaterThenZero);
    std::ostream dStream(_depthTextCtrl);
    dStream << std::setprecision(4);
    _depthTextCtrl->SetFont(*font);
    depthSizer->Add(depthText, 0, wxCENTER | wxBOTTOM | wxLEFT, 6);
    depthSizer->Add(59, 0, 0);
    depthSizer->Add(_depthTextCtrl, 0, wxCENTER | wxBOTTOM | wxRIGHT, 6);
    
    wxStaticText *solverPrecisionText = new wxStaticText(this, wxID_ANY, "Solver Precision:");
    solverPrecisionText->SetFont(*font);
    _solverPrecisionTextCtrl->Create(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(121, 20), 0, greaterThenZero);
    std::ostream spStream(_solverPrecisionTextCtrl);
    spStream << std::setprecision(4);
    _solverPrecisionTextCtrl->SetFont(*font);
    solverPreSizer->Add(solverPrecisionText, 0, wxCENTER | wxBOTTOM | wxLEFT, 6);
    solverPreSizer->Add(6, 0, 0);
    solverPreSizer->Add(_solverPrecisionTextCtrl, 0, wxCENTER | wxBOTTOM | wxRIGHT, 6);
   
    wxStaticText *minAngleText = new wxStaticText(this, wxID_ANY, "Min Angle (deg):");
    minAngleText->SetFont(*font);
    _minAngleTextCtrl->Create(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(121, 20), 0, angleValidator);
    std::ostream minAngleStream(_minAngleTextCtrl);
    minAngleStream << std::setprecision(15);
    _minAngleTextCtrl->SetFont(*font);
    minAngleSizer->Add(minAngleText, 0, wxCENTER | wxBOTTOM | wxLEFT, 6);
    minAngleSizer->Add(7, 0, 0);
    minAngleSizer->Add(_minAngleTextCtrl, 0, wxCENTER | wxBOTTOM | wxRIGHT, 6);
    
    wxStaticBoxSizer *commentSizer = new wxStaticBoxSizer(wxVERTICAL, this, "Comments");
    commentSizer->GetStaticBox()->SetFont(*font);
    _commentsTextCtrl->Create(commentSizer->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(192, 87), wxTE_MULTILINE);
    _commentsTextCtrl->SetFont(*font);
    commentSizer->Add(_commentsTextCtrl, 0, wxALL, 6);
    
    wxButton *okButton = new wxButton(this, wxID_OK, "Ok", wxDefaultPosition, wxSize(75, 23));
    okButton->SetFont(*font);
    wxButton *cancelButton = new wxButton(this, wxID_CANCEL, "Cancel", wxDefaultPosition, wxSize(75, 23));
    cancelButton->SetFont(*font);
    footerSizer->Add(okButton, 0, wxTOP | wxBOTTOM | wxRIGHT, 6);
    footerSizer->Add(cancelButton, 0, wxRIGHT | wxBOTTOM | wxTOP, 6);
    
    topSizer->Add(probTypeSizer);
    topSizer->Add(lengthSizer);
    
    if(_problem == physicProblems::PROB_MAGNETICS)
    {
        topSizer->Add(acSolverSizer);
        topSizer->Add(freqSizer);
    }
    
    topSizer->Add(depthSizer);
    topSizer->Add(solverPreSizer);
    topSizer->Add(minAngleSizer);
    topSizer->Add(commentSizer, 0, wxLEFT | wxRIGHT | wxCENTER, 6);
    
    topSizer->Add(footerSizer, 0, wxALIGN_RIGHT);
    
    if(_problem == physicProblems::PROB_ELECTROSTATIC)
    {
        _problemTypeComboBox->SetSelection((int)_electrPreference.getProblemType());
        _lengthUnitsComboBox->SetSelection((int)_electrPreference.getUnitLength());
        dStream << _electrPreference.getDepth();
        spStream << _electrPreference.getPrecision();
        minAngleStream << _electrPreference.getMinAngle();
        _commentsTextCtrl->SetValue(_electrPreference.getComments());
    }
    else if(_problem == physicProblems::PROB_MAGNETICS)
    {
        _problemTypeComboBox->SetSelection((int)_magPreference.getProblemType());
        _lengthUnitsComboBox->SetSelection((int)_magPreference.getUnitLength());
        dStream << _magPreference.getDepth();
        spStream << _magPreference.getPrecision();
        minAngleStream << _magPreference.getMinAngle();
        _commentsTextCtrl->SetValue(_magPreference.getComments());
    }
    
    if(_problemTypeComboBox->GetSelection() == 1)
    {
        _depthTextCtrl->Enable(false);
    }
    
    SetSizerAndFit(topSizer);
    
}

void preferencesDialog::onComboBox(wxCommandEvent &event)
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


void preferencesDialog::getPreferences(magneticPreference &settings)
{
    double value;
    
    settings.setProblemType((problemTypeEnum)_problemTypeComboBox->GetSelection());
    settings.setUnitLength((unitLengthEnum)_lengthUnitsComboBox->GetSelection());
    settings.setACSolver((acSolverEnum)_acSolverComboBox->GetSelection());
    
    _frequencyTextCtrl->GetValue().ToDouble(&value);
    settings.setFrequency(value);
    
    _depthTextCtrl->GetValue().ToDouble(&value);
    settings.setDepth(value);
    
    _solverPrecisionTextCtrl->GetValue().ToDouble(&value);
    settings.setPrecision(value);
    
    _minAngleTextCtrl->GetValue().ToDouble(&value);
    settings.setMinAngle(value);
    
    settings.setComments(_commentsTextCtrl->GetValue());
}



void preferencesDialog::getPreferences(electroStaticPreference &settings)
{
    double value;
    
    settings.setProblemType((problemTypeEnum)_problemTypeComboBox->GetSelection());
    settings.setUnitLength((unitLengthEnum)_lengthUnitsComboBox->GetSelection());
    
    _depthTextCtrl->GetValue().ToDouble(&value);
    settings.setDepth(value);
    
    _solverPrecisionTextCtrl->GetValue().ToDouble(&value);
    settings.setPrecision(value);
    
    _minAngleTextCtrl->GetValue().ToDouble(&value);
    settings.setMinAngle(value);
    
    settings.setComments(_commentsTextCtrl->GetValue());
}



preferencesDialog::~preferencesDialog()
{
    
}


wxBEGIN_EVENT_TABLE(preferencesDialog, wxDialog)
    EVT_COMBOBOX(generalFrameButton::ID_ComboBox1, preferencesDialog::onComboBox)
wxEND_EVENT_TABLE()