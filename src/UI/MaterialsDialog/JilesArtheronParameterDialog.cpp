#include <UI/MaterialsDialog/JilesAthertonParametersDialog.h>


jilesAthertonParameterDialog::jilesAthertonParameterDialog(wxWindow *par) : wxDialog(par, wxID_ANY, "Jiles Atheron ")
{
    wxFont *font = new wxFont(8.5, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
    
    wxBoxSizer *headerSizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *line1Sizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *line2Sizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *line3Sizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *line4Sizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *line5Sizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *line6Sizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *line7Sizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *line8Sizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *footerSizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *topSizer = new wxBoxSizer(wxVERTICAL);
    
    // THis section of the code is for the Y parameters of the JA model. Which for now, we are only using the X until further notice
    /*
    wxStaticBoxSizer *JAXparametersSizer = new wxStaticBoxSizer(wxVERTICAL, this, "X Parameters");
    JAXparametersSizer->GetStaticBox()->SetFont(*font);
    
    wxBoxSizer *YLine1 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *YLine2 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *YLine3 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *YLine4 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *YLine5 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *YLine6 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *YLine7 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *YLine8 = new wxBoxSizer(wxHORIZONTAL);
    
    wxStaticBoxSizer *JAYparametersSizer = new wxStaticBoxSizer(wxVERTICAL, this, "Y Parameters");
    JAYparametersSizer->GetStaticBox()->SetFont(*font);
    */
    
    wxStaticText *unit1 = new wxStaticText(this, wxID_ANY, "A/m", wxPoint(156, 88), wxSize(27, 13));
    unit1->SetFont(*font);
    wxStaticText *unit2 = new wxStaticText(this, wxID_ANY, "A/m", wxPoint(156, 113), wxSize(27, 13));
    unit2->SetFont(*font);
    wxStaticText *unit3 = new wxStaticText(this, wxID_ANY, "A/m", wxPoint(156, 139), wxSize(27, 13));
    unit3->SetFont(*font);
    wxStaticText *unit4 = new wxStaticText(this, wxID_ANY, "J/m^3", wxPoint(156, 191), wxSize(37, 13));
    unit4->SetFont(*font);
    wxStaticText *unit5 = new wxStaticText(this, wxID_ANY, "deg", wxPoint(156, 217), wxSize(27, 13));
    unit5->SetFont(*font);
    
    _isAnisotropyCheckBox->Create(this, generalFrameButton::ID_CHECKBOX1, "Anisotropy Material", wxPoint(47, 19), wxSize(135, 17));
    _isAnisotropyCheckBox->SetFont(*font);
    _isAnisotropyCheckBox->SetValue(false);
    
    headerSizer->Add(_isAnisotropyCheckBox, 0, wxALL, 6);
    
    wxStaticText *alphaText = new wxStaticText(this, wxID_ANY, wxT("α:"), wxPoint(15, 61), wxSize(16, 13));
    alphaText->SetFont(*font);
    _alphaParamTextCtrl->Create(this, wxID_ANY, wxEmptyString, wxPoint(50, 58), wxSize(100, 20));
    _alphaParamTextCtrl->SetFont(*font);
    line1Sizer->Add(alphaText, 0, wxCENTER | wxALL, 6);
    line1Sizer->Add(19, 0, 0);
    line1Sizer->Add(_alphaParamTextCtrl, 0, wxCENTER | wxTOP | wxBOTTOM | wxRIGHT, 6);
    
    wxStaticText *aText = new wxStaticText(this, wxID_ANY, "a:", wxPoint(15, 88), wxSize(22, 13));
    aText->SetFont(*font);
    _aParamTextCtrl->Create(this, wxID_ANY, wxEmptyString, wxPoint(50, 84), wxSize(100, 20));
    _aParamTextCtrl->SetFont(*font);
    line2Sizer->Add(aText, 0, wxCENTER | wxBOTTOM | wxRIGHT | wxLEFT, 6);
    line2Sizer->Add(13, 0, 0);
    line2Sizer->Add(_aParamTextCtrl, 0, wxCENTER | wxBOTTOM | wxRIGHT, 6);
    line2Sizer->Add(unit1, 0, wxCENTER | wxBOTTOM | wxRIGHT, 6);
    
    wxStaticText *magnetizationText = new wxStaticText(this, wxID_ANY, "Ms:", wxPoint(15, 113), wxSize(24, 13));
    magnetizationText->SetFont(*font);
    _satMagnetizationParamTextCtrl->Create(this, wxID_ANY, wxEmptyString, wxPoint(50, 110), wxSize(100, 20));
    _satMagnetizationParamTextCtrl->SetFont(*font);
    line3Sizer->Add(magnetizationText, 0, wxCENTER | wxBOTTOM | wxRIGHT | wxLEFT, 6);
    line3Sizer->Add(11, 0, 0);
    line3Sizer->Add(_satMagnetizationParamTextCtrl, 0, wxCENTER | wxBOTTOM | wxRIGHT, 6);
    line3Sizer->Add(unit2, 0, wxCENTER | wxBOTTOM | wxRIGHT, 6);
    
    wxStaticText *kText = new wxStaticText(this, wxID_ANY, "k:", wxPoint(15, 139), wxSize(16, 13));
    kText->SetFont(*font);
    _kParamTextCtrl->Create(this, wxID_ANY, wxEmptyString, wxPoint(50, 136), wxSize(100, 20));
    _kParamTextCtrl->SetFont(*font);
    line4Sizer->Add(kText, 0, wxCENTER | wxBOTTOM | wxRIGHT | wxLEFT, 6);
    line4Sizer->Add(19, 0, 0);
    line4Sizer->Add(_kParamTextCtrl, 0, wxCENTER | wxBOTTOM | wxRIGHT, 6);
    line4Sizer->Add(unit3, 0, wxCENTER | wxBOTTOM | wxRIGHT, 6);
    
    wxStaticText *cText = new wxStaticText(this, wxID_ANY, "c:", wxPoint(15, 165), wxSize(16, 13));
    cText->SetFont(*font);
    _cParamTextCtrl->Create(this, wxID_ANY, wxEmptyString, wxPoint(50, 162), wxSize(100, 20));
    _cParamTextCtrl->SetFont(*font);
    line5Sizer->Add(cText, 0, wxCENTER | wxBOTTOM | wxRIGHT | wxLEFT, 6);
    line5Sizer->Add(19, 0, 0);
    line5Sizer->Add(_cParamTextCtrl, 0, wxCENTER | wxBOTTOM | wxRIGHT, 6);
    
    wxStaticText *kanText = new wxStaticText(this, wxID_ANY, "Kan:", wxPoint(15, 165), wxSize(25, 13));
    kanText->SetFont(*font);
    _KanParamTextCtrl->Create(this, wxID_ANY, wxEmptyString, wxPoint(50, 188), wxSize(100, 20));
    _KanParamTextCtrl->SetFont(*font);
    line6Sizer->Add(kanText, 0, wxCENTER | wxBOTTOM | wxRIGHT | wxLEFT, 6);
    line6Sizer->Add(10, 0, 0);
    line6Sizer->Add(_KanParamTextCtrl, 0, wxCENTER | wxBOTTOM | wxRIGHT, 6);
    line6Sizer->Add(unit4, 0, wxCENTER | wxBOTTOM | wxRIGHT, 6);
    
    wxStaticText *psiText = new wxStaticText(this, wxID_ANY, wxT("ψ:"), wxPoint(15, 217), wxSize(24, 13));
    psiText->SetFont(*font);
    _psiParamTextCtrl->Create(this, wxID_ANY, wxEmptyString, wxPoint(50, 214), wxSize(100, 20));
    _psiParamTextCtrl->SetFont(*font);
    line7Sizer->Add(psiText, 0, wxCENTER | wxBOTTOM | wxRIGHT | wxLEFT, 6);
    line7Sizer->Add(11, 0, 0);
    line7Sizer->Add(_psiParamTextCtrl, 0, wxCENTER | wxBOTTOM | wxRIGHT, 6);
    line7Sizer->Add(unit5, 0, wxCENTER | wxBOTTOM | wxRIGHT, 6);
        
    wxStaticText *tText = new wxStaticText(this, wxID_ANY, "t:", wxPoint(15, 243), wxSize(13, 13));
    tText->SetFont(*font);
    _tParamTextCtrl->Create(this, wxID_ANY, wxEmptyString, wxPoint(50, 240), wxSize(100, 20));
    _tParamTextCtrl->SetFont(*font);
    line8Sizer->Add(tText, 0, wxCENTER | wxBOTTOM | wxRIGHT | wxLEFT, 6);
    line8Sizer->Add(22, 0, 0);
    line8Sizer->Add(_tParamTextCtrl, 0, wxCENTER | wxBOTTOM | wxRIGHT, 6);
    
    wxButton *okButton = new wxButton(this, wxID_OK, "Ok", wxPoint(62, 303), wxSize(75, 23));
    okButton->SetFont(*font);
    wxButton *cancelButton = new wxButton(this, wxID_CANCEL, "Cancel", wxPoint(143, 303), wxSize(75, 23));
    cancelButton->SetFont(*font);
    footerSizer->Add(okButton, 0, wxBOTTOM | wxRIGHT | wxLEFT, 6);
    footerSizer->Add(cancelButton, 0, wxBOTTOM | wxRIGHT, 6);
    
    topSizer->Add(headerSizer, 0, wxCENTER);
    topSizer->Add(line1Sizer);
    topSizer->Add(line2Sizer);
    topSizer->Add(line3Sizer);
    topSizer->Add(line4Sizer);
    topSizer->Add(line5Sizer);
    topSizer->Add(line6Sizer);
    topSizer->Add(line7Sizer);
    topSizer->Add(line8Sizer);
    topSizer->Add(footerSizer, 0, wxALIGN_RIGHT);
    
    updateInterface();
    
    SetSizerAndFit(topSizer);
}


void jilesAthertonParameterDialog::setJilesAthertonParameter(jilesAthertonParameters param)
{
    _parameter = param;
    updateInterface();
}



void jilesAthertonParameterDialog::getJilesAthertonParameter(jilesAthertonParameters &param)
{
    double value;
    
    param.setIsAnisotropyMaterial(_isAnisotropyCheckBox->GetValue());
    
    _alphaParamTextCtrl->GetValue().ToDouble(&value);
    param.setAlpha(value);
    
    _aParamTextCtrl->GetValue().ToDouble(&value);
    param.setAParam(value);
    
    _satMagnetizationParamTextCtrl->GetValue().ToDouble(&value);
    param.setSaturationMagnetization(value);
    
    _kParamTextCtrl->GetValue().ToDouble(&value);
    param.setKParam(value);
    
    _cParamTextCtrl->GetValue().ToDouble(&value);
    param.setMagnetizationReversibility(value);
    
    _KanParamTextCtrl->GetValue().ToDouble(&value);
    param.setEnergyDensity(value);
    
    _psiParamTextCtrl->GetValue().ToDouble(&value);
    param.setPsi(value);
    
    _tParamTextCtrl->GetValue().ToDouble(&value);
    param.setTParameter(value);
}


void jilesAthertonParameterDialog::onCheckBox(wxCommandEvent &event)
{
    if(_isAnisotropyCheckBox->GetValue())
    {
        _KanParamTextCtrl->Enable(true);
        _psiParamTextCtrl->Enable(true);
        _tParamTextCtrl->Enable(true);
    }
    else
    {
        _KanParamTextCtrl->Enable(false);
        _psiParamTextCtrl->Enable(false);
        _tParamTextCtrl->Enable(false); 
    }
}



void jilesAthertonParameterDialog::updateInterface()
{
    std::ostream alphaStream(_alphaParamTextCtrl);
    std::ostream aStream(_aParamTextCtrl);
    std::ostream satMagnetizationStream(_satMagnetizationParamTextCtrl);
    std::ostream kStream(_kParamTextCtrl);
    std::ostream cStream(_cParamTextCtrl);
    std::ostream kanStream(_KanParamTextCtrl);
    std::ostream psiStream(_psiParamTextCtrl);
    std::ostream tStream(_tParamTextCtrl);
    
    _alphaParamTextCtrl->SetValue(wxEmptyString);
    alphaStream << std::setprecision(3);
    alphaStream << _parameter.getAlpha();
    
    _aParamTextCtrl->SetValue(wxEmptyString);
    aStream << std::setprecision(3);
    aStream << _parameter.getAParam();
    
    _satMagnetizationParamTextCtrl->SetValue(wxEmptyString);
    satMagnetizationStream << std::setprecision(3);
    satMagnetizationStream << _parameter.getSaturationMagnetization();
    
    _kParamTextCtrl->SetValue(wxEmptyString);
    kStream << std::setprecision(3);
    kStream << _parameter.getKParam();
    
    _cParamTextCtrl->SetValue(wxEmptyString);
    cStream << std::setprecision(3);
    cStream << _parameter.getMagnetizationReversibility();
    
    _KanParamTextCtrl->SetValue(wxEmptyString);
    kanStream << std::setprecision(3);
    kanStream << _parameter.getEnergyDensity();
    
    _psiParamTextCtrl->SetValue(wxEmptyString);
    psiStream << std::setprecision(3);
    psiStream << _parameter.getPsi();
    
    _tParamTextCtrl->SetValue(wxEmptyString);
    tStream << std::setprecision(3);
    tStream << _parameter.getTParameter();
    
    _isAnisotropyCheckBox->SetValue(_parameter.getIsAnisotropyMaterial());
    
    if(_parameter.getIsAnisotropyMaterial())
    {
        _KanParamTextCtrl->Enable(true);
        _psiParamTextCtrl->Enable(true);
        _tParamTextCtrl->Enable(true);
    }
    else
    {
        _KanParamTextCtrl->Enable(false);
        _psiParamTextCtrl->Enable(false);
        _tParamTextCtrl->Enable(false); 
    }
}



jilesAthertonParameterDialog::~jilesAthertonParameterDialog()
{
    
}


wxBEGIN_EVENT_TABLE(jilesAthertonParameterDialog, wxDialog)
    EVT_CHECKBOX(generalFrameButton::ID_CHECKBOX1, jilesAthertonParameterDialog::onCheckBox)
wxEND_EVENT_TABLE()