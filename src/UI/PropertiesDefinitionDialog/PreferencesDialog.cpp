#include <UI/PreferencesDialog.h>
#include <iostream>
#include <iomanip>

preferencesDialog::preferencesDialog(magneticPreference pref, physicProblems problem) : wxDialog(NULL, wxID_ANY, "Problem Preferences")
{
    _magPreference = pref;
    _problem = problem;

    _acSolverNameArray->Add("Succ. Approx");
    _acSolverNameArray->Add("Newton");
   
    createDialog();
}



preferencesDialog::preferencesDialog(electroStaticPreference pref, physicProblems problem) : wxDialog(NULL, wxID_ANY, "Problem Definition")
{
    _electrPreference = pref;
    _problem = problem;
    
    createDialog();
}



void preferencesDialog::createDialog()
{
    wxFont *font = new wxFont(8.5, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
    
    wxBoxSizer *probTypeSizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *lengthSizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *freqSizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *depthSizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *solverPreSizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *minAngleSizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *acSolverSizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *topSizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *footerSizer = new wxBoxSizer(wxHORIZONTAL);
    
    _probTypeNameArray->Add("Planar");
    _probTypeNameArray->Add("Axisymmetric");
   
    _lengthUnitsNameArray->Add("Inches");
    _lengthUnitsNameArray->Add("Millimeters");
    _lengthUnitsNameArray->Add("Centimeters");
    _lengthUnitsNameArray->Add("Meters");
    _lengthUnitsNameArray->Add("Mils");
    _lengthUnitsNameArray->Add("Micrometers");
    
    wxStaticText *probTypeText = new wxStaticText(this, wxID_ANY, "Problem Type:", wxPoint(12, 15), wxSize(90, 13));
    probTypeText->SetFont(*font);
    _problemTypeComboBox->Create(this, wxID_ANY, wxEmptyString, wxPoint(98, 12), wxSize(121, 21), *_probTypeNameArray);
    _problemTypeComboBox->SetFont(*font);
    probTypeSizer->Add(probTypeText, 0, wxCENTER | wxTOP | wxBOTTOM | wxLEFT, 6);
    probTypeSizer->Add(7, 0, 0);
    probTypeSizer->Add(_problemTypeComboBox, 0, wxCENTER | wxTOP | wxBOTTOM | wxRIGHT, 6);
   
    wxStaticText *lengthUnitsText = new wxStaticText(this, wxID_ANY, "Length Units:", wxPoint(12, 42), wxSize(90, 13));
    lengthUnitsText->SetFont(*font);
    _lengthUnitsComboBox->Create(this, wxID_ANY, wxEmptyString, wxPoint(98, 39), wxSize(121, 21), *_lengthUnitsNameArray);
    _lengthUnitsComboBox->SetFont(*font);
    lengthSizer->Add(lengthUnitsText, 0, wxCENTER | wxBOTTOM | wxLEFT, 6);
    lengthSizer->Add(7, 0, 0);
    lengthSizer->Add(_lengthUnitsComboBox, 0, wxCENTER | wxBOTTOM | wxRIGHT, 6);
    if(_problem == physicProblems::PROB_MAGNETICS)
    {
        wxStaticText *acSolverText = new wxStaticText(this, wxID_ANY, "AC Solver:", wxPoint(12, 69), wxSize(60, 13));
        acSolverText->SetFont(*font);
        _acSolverComboBox->Create(this, wxID_ANY, wxEmptyString, wxPoint(98, 65), wxSize(121, 21), *_acSolverNameArray);
        _acSolverComboBox->SetFont(*font);
        _acSolverComboBox->SetSelection((int)_magPreference.getACSolver());
        acSolverSizer->Add(acSolverText, 0, wxCENTER | wxBOTTOM | wxLEFT, 6);
        acSolverSizer->Add(37, 0, 0);
        acSolverSizer->Add(_acSolverComboBox, 0, wxCENTER | wxBOTTOM | wxRIGHT, 6);

        wxStaticText *freqText = new wxStaticText(this, wxID_ANY, "Frequency (Hz):", wxPoint(12, 95), wxSize(90, 13));
        freqText->SetFont(*font);
        _frequencyTextCtrl->Create(this, wxID_ANY, wxEmptyString, wxPoint(98, 92), wxSize(121, 20));
        std::ostream freqStream(_frequencyTextCtrl);
        freqStream << std::setprecision(3);
        freqStream << _magPreference.getFrequency();
        _frequencyTextCtrl->SetFont(*font);
        freqSizer->Add(freqText, 0, wxCENTER | wxBOTTOM | wxLEFT, 6);
        freqSizer->Add(7, 0, 0);
        freqSizer->Add(_frequencyTextCtrl, 0, wxCENTER | wxBOTTOM | wxRIGHT, 6);
    }
   
    wxStaticText *depthText = new wxStaticText(this, wxID_ANY, "Depth:");
    depthText->SetFont(*font);
    _depthTextCtrl->Create(this, wxID_ANY, wxEmptyString, wxPoint(98, 118), wxSize(121, 20));
    std::ostream dStream(_depthTextCtrl);
    dStream << std::setprecision(4);
    _depthTextCtrl->SetFont(*font);
    depthSizer->Add(depthText, 0, wxCENTER | wxBOTTOM | wxLEFT, 6);
    depthSizer->Add(59, 0, 0);
    depthSizer->Add(_depthTextCtrl, 0, wxCENTER | wxBOTTOM | wxRIGHT, 6);
   
    wxStaticText *solverPrecisionText = new wxStaticText(this, wxID_ANY, "Solver Precision:");
    solverPrecisionText->SetFont(*font);
    _solverPrecisionTextCtrl->Create(this, wxID_ANY, wxEmptyString, wxPoint(98, 144), wxSize(121, 20));
    std::ostream spStream(_solverPrecisionTextCtrl);
    spStream << std::setprecision(4);
    _solverPrecisionTextCtrl->SetFont(*font);
    solverPreSizer->Add(solverPrecisionText, 0, wxCENTER | wxBOTTOM | wxLEFT, 6);
    solverPreSizer->Add(6, 0, 0);
    solverPreSizer->Add(_solverPrecisionTextCtrl, 0, wxCENTER | wxBOTTOM | wxRIGHT, 6);
   
    wxStaticText *minAngleText = new wxStaticText(this, wxID_ANY, "Min Angle (deg):");
    minAngleText->SetFont(*font);
    _minAngleTextCtrl->Create(this, wxID_ANY, wxEmptyString, wxPoint(98, 170), wxSize(121, 20));
    std::ostream minAngleStream(_minAngleTextCtrl);
    minAngleStream << std::setprecision(4);
    _minAngleTextCtrl->SetFont(*font);
    minAngleSizer->Add(minAngleText, 0, wxCENTER | wxBOTTOM | wxLEFT, 6);
    minAngleSizer->Add(7, 0, 0);
    minAngleSizer->Add(_minAngleTextCtrl, 0, wxCENTER | wxBOTTOM | wxRIGHT, 6);
    
    wxStaticBoxSizer *commentSizer = new wxStaticBoxSizer(wxVERTICAL, this, "Comments");
    commentSizer->GetStaticBox()->SetFont(*font);
    _commentsTextCtrl->Create(commentSizer->GetStaticBox(), wxID_ANY, wxEmptyString, wxPoint(6, 19), wxSize(192, 87), wxTE_MULTILINE);
    _commentsTextCtrl->SetFont(*font);
    commentSizer->Add(_commentsTextCtrl);
    
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
    
    SetSizerAndFit(topSizer);
    
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