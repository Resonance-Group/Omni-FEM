#include <UI/EditMenu/MoveCopyDialog.h>


moveCopyDialog::moveCopyDialog(wxWindow *par, bool isMove) : wxDialog(par, wxID_ANY, "Copy")
{
    _isMove = isMove;
    
    wxIntegerValidator<unsigned int> copiesValidator;
    copiesValidator.SetRange(0, 65535);
    
    wxFloatingPointValidator<double> angleValidator(15);
    angleValidator.SetRange(-360, 360);
    
    if(isMove)
        this->SetTitle("Move");
        
    wxFont *font = new wxFont(8.5, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
    
    wxBoxSizer *headerSizer = new wxBoxSizer(wxHORIZONTAL);
    wxStaticBoxSizer *rotationSizer = new wxStaticBoxSizer(wxVERTICAL, this, "Rotation");
    rotationSizer->GetStaticBox()->SetFont(*font);
    wxBoxSizer *RSLine1 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *RSLine2 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *RSLine3 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *translationCheckBoxSizer = new wxBoxSizer(wxHORIZONTAL);
    wxStaticBoxSizer *translationSizer = new wxStaticBoxSizer(wxVERTICAL, this, "Translation");
    translationSizer->GetStaticBox()->SetFont(*font);
    wxBoxSizer *TSLine1 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *TSLine2 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *numCopiesSizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *footerSizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *topSizer = new wxBoxSizer(wxVERTICAL);
    
    _rotationCheckBox->Create(this, generalFrameButton::ID_RadioButton1, "Rotation");
    _rotationCheckBox->SetFont(*font);
    _rotationCheckBox->SetValue(true);
    headerSizer->Add(_rotationCheckBox, 0, wxALL, 6);
    
    wxStaticText *shiftText = new wxStaticText(rotationSizer->GetStaticBox(), wxID_ANY, "Angular Shift (deg):", wxPoint(6, 22), wxSize(110, 13));
    shiftText->SetFont(*font);
    wxStaticText *aboutPointText = new wxStaticText(rotationSizer->GetStaticBox(), wxID_ANY, "About Point (x, y):", wxPoint(6, 48), wxSize(105, 13));
    aboutPointText->SetFont(*font);
    _angularShiftTextCtrl->Create(rotationSizer->GetStaticBox(), wxID_ANY, "0", wxPoint(107, 19), wxSize(100, 20), 0, angleValidator);
    _angularShiftTextCtrl->SetFont(*font);
    _aboutPointXTextCtrl->Create(rotationSizer->GetStaticBox(), wxID_ANY, "0", wxPoint(107, 45), wxSize(100, 20));
    _aboutPointXTextCtrl->SetFont(*font);
    _aboutPointYTextCtrl->Create(rotationSizer->GetStaticBox(), wxID_ANY, "0", wxPoint(107, 71), wxSize(100, 20));
    _aboutPointYTextCtrl->SetFont(*font);
    
    RSLine1->Add(shiftText, 0, wxALL | wxCENTER, 6);
    RSLine1->Add(_angularShiftTextCtrl, 0, wxCENTER | wxTOP | wxBOTTOM | wxRIGHT, 6);
    RSLine2->Add(aboutPointText, 0, wxCENTER | wxBOTTOM | wxLEFT | wxRIGHT, 6);
    RSLine2->Add(5, 0, 0);
    RSLine2->Add(_aboutPointXTextCtrl, 0, wxCENTER | wxBOTTOM | wxRIGHT, 6);
    
    RSLine3->Add(_aboutPointYTextCtrl, 0, wxBOTTOM | wxRIGHT, 6);
    
    rotationSizer->Add(RSLine1);
    rotationSizer->Add(RSLine2);
    rotationSizer->Add(RSLine3, 0, wxALIGN_RIGHT);
    
    _translationCheckBox->Create(this, generalFrameButton::ID_RadioButton2, "Translation");
    _translationCheckBox->SetFont(*font);
    _translationCheckBox->SetValue(false);
    translationCheckBoxSizer->Add(_translationCheckBox, 0, wxALL, 6);
    
    wxStaticText *horizontalText = new wxStaticText(this, wxID_ANY, "Horizontal Shift:", wxPoint(6, 22), wxSize(100, 13));
    horizontalText->SetFont(*font);
    wxStaticText *verticalText = new wxStaticText(this, wxID_ANY, "Vertical Shift:", wxPoint(6, 48), wxSize(100, 13));
    verticalText->SetFont(*font);
    _horizontalShiftTextCtrl->Create(this, wxID_ANY, "0", wxPoint(107, 19), wxSize(100, 20));
    _horizontalShiftTextCtrl->SetFont(*font);
    _verticalShiftTextCtrl->Create(this, wxID_ANY, "0", wxPoint(107, 45), wxSize(100, 20));
    _verticalShiftTextCtrl->SetFont(*font);
    _horizontalShiftTextCtrl->Enable(false);
    _verticalShiftTextCtrl->Enable(false);
    
    TSLine1->Add(horizontalText, 0, wxCENTER | wxALL, 6);
    TSLine1->Add(10, 0, 0);
    TSLine1->Add(_horizontalShiftTextCtrl, 0, wxCENTER | wxTOP | wxBOTTOM | wxRIGHT, 6);
    
    TSLine2->Add(verticalText, 0, wxCENTER | wxBOTTOM | wxLEFT | wxRIGHT, 6);
    TSLine2->Add(10, 0, 0);
    TSLine2->Add(_verticalShiftTextCtrl, 0, wxCENTER | wxRIGHT | wxBOTTOM, 6);
    
    translationSizer->Add(TSLine1);
    translationSizer->Add(TSLine2);
    
    if(!isMove)
    {
        wxStaticText *copiesText = new wxStaticText(this, wxID_ANY, "Number of Copies:");
        copiesText->SetFont(*font);
        _numberCopiesTextCtrl->Create(this, wxID_ANY, "0", wxPoint(119, 250), wxSize(100, 20), 0, copiesValidator);
        _numberCopiesTextCtrl->SetFont(*font);
    
        numCopiesSizer->Add(copiesText, 0, wxCENTER | wxALL, 6);
        numCopiesSizer->Add(13, 0, 0);
        numCopiesSizer->Add(_numberCopiesTextCtrl, 0, wxCENTER);
    }

    
    wxButton *okButton = new wxButton(this, wxID_OK, "OK", wxPoint(76, 276), wxSize(75, 23));
    okButton->SetFont(*font);
    
    wxButton *cancelButton = new wxButton(this, wxID_CANCEL, "Cancel", wxPoint(157, 276), wxSize(75, 23));
    cancelButton->SetFont(*font);
    
    footerSizer->Add(okButton, 0, wxTOP | wxRIGHT, 6);
    footerSizer->Add(cancelButton, 0, wxTOP | wxRIGHT, 6);
    
    topSizer->Add(headerSizer);
    topSizer->Add(rotationSizer, 0, wxLEFT | wxRIGHT, 6);
    topSizer->Add(translationCheckBoxSizer);
    topSizer->Add(translationSizer, 0, wxLEFT | wxRIGHT, 6);
    
    if(!isMove)
        topSizer->Add(numCopiesSizer, 0, wxTOP | wxRIGHT, 6);
        
    topSizer->Add(footerSizer, 0, wxALIGN_RIGHT);
    
    SetSizerAndFit(topSizer);
}



bool moveCopyDialog::rotationIsSelected()
{
    return _rotationCheckBox->GetValue();
}



void moveCopyDialog::getRotationCopy(wxPoint &aboutPoint, double &angularShift, unsigned int &numberCopies)
{
    double value1, value2;
    long numCopies;
    
    _angularShiftTextCtrl->GetValue().ToDouble(&value1);
    angularShift = value1;
    _aboutPointXTextCtrl->GetValue().ToDouble(&value1);
    _aboutPointYTextCtrl->GetValue().ToDouble(&value2);
    
    if(!_isMove)
    {
        _numberCopiesTextCtrl->GetValue().ToLong(&numCopies);
        numberCopies = (unsigned int)numCopies;
    }
    else
        numberCopies = 0;
    
    aboutPoint = wxPoint(value1, value2);
}



void moveCopyDialog::getTranslationCopy(double &horizontalShift, double &verticalShift, unsigned int &numberCopies)
{
    double value;
    long numCopies;
    
    _horizontalShiftTextCtrl->GetValue().ToDouble(&value);
    horizontalShift = value;
    _verticalShiftTextCtrl->GetValue().ToDouble(&value);
    verticalShift = value;
    
    if(!_isMove)
    {
        _numberCopiesTextCtrl->GetValue().ToLong(&numCopies);
        numberCopies = (unsigned int)numCopies;
    }
    else
        numberCopies = 0;
}



void moveCopyDialog::onRotationCheck(wxCommandEvent &event)
{
    _angularShiftTextCtrl->Enable(true);
    _aboutPointXTextCtrl->Enable(true);
    _aboutPointYTextCtrl->Enable(true);
    
    _horizontalShiftTextCtrl->Enable(false);
    _verticalShiftTextCtrl->Enable(false);
}



void moveCopyDialog::onTranslationCheck(wxCommandEvent &event)
{
    _angularShiftTextCtrl->Enable(false);
    _aboutPointXTextCtrl->Enable(false);
    _aboutPointYTextCtrl->Enable(false);
    
    _horizontalShiftTextCtrl->Enable(true);
    _verticalShiftTextCtrl->Enable(true);
}



moveCopyDialog::~moveCopyDialog()
{
    
}



wxBEGIN_EVENT_TABLE(moveCopyDialog, wxDialog)
    EVT_RADIOBUTTON(generalFrameButton::ID_RadioButton1, moveCopyDialog::onRotationCheck)
    EVT_RADIOBUTTON(generalFrameButton::ID_RadioButton2, moveCopyDialog::onTranslationCheck)
wxEND_EVENT_TABLE()