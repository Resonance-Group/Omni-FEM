#include <UI/NodalProperty/NodalPropertyDialog.h>



nodalPropertyDialog::nodalPropertyDialog(physicProblems problem) : wxDialog(NULL, wxID_ANY, "Nodal Property")
{
    createDialog(problem);
}



nodalPropertyDialog::nodalPropertyDialog() : wxDialog(NULL, wxID_ANY, "Nodal Property")
{
    
}


void nodalPropertyDialog::createDialog(physicProblems problem)
{
    wxFont *font = new wxFont(8.5, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
    
    _problem = problem;
    
    wxBoxSizer *headerSizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *radioSizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *valueSizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *footerSizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *topSizer = new wxBoxSizer(wxVERTICAL);
    
    _nodalProperty.setName("New Point Property");
    _nodalProperty.setValue(0);
    
    /* This first part is for the header */
    wxStaticText *name = new wxStaticText(this, wxID_ANY, "Name:", wxPoint(12, 9), wxSize(38, 13));
    name->SetFont(*font);
    nameTextCtrl->Create(this, wxID_ANY, _nodalProperty.getName(), wxPoint(50, 6), wxSize(165, 20));
    nameTextCtrl->SetFont(*font);
    
    headerSizer->Add(name, 0, wxCENTER | wxALL , 6);
    headerSizer->Add(nameTextCtrl, 0, wxCenter | wxTOP | wxBOTTOM | wxRIGHT, 6);
    
    /* Adding in the radio buttons */
    radioButton1->Create(this, generalFrameButton::ID_RadioButton1, "Specified Potential Property", wxPoint(50, 32), wxSize(176, 19));
    radioButton1->SetFont(*font);
    radioButton1->SetValue(true);
    if(_problem == physicProblems::PROB_MAGNETICS)
        radioButton2->Create(this, generalFrameButton::ID_RadioButton2, "Point Current Property", wxPoint(50, 55), wxSize(144, 19));
    else
        radioButton2->Create(this, generalFrameButton::ID_RadioButton2, "Point Charge Density Property", wxPoint(50, 55), wxSize(190, 19));
    radioButton2->SetFont(*font);
    radioButton2->SetValue(false);
    
    radioSizer->Add(radioButton1, 0, wxLEFT | wxRIGHT | wxBOTTOM, 6);
    radioSizer->Add(radioButton2, 0, wxLEFT | wxRIGHT, 6);
    
    /*Creating the group boxes */
    if(_problem == physicProblems::PROB_MAGNETICS)
        groupBox1->Create(this, wxID_ANY, "Specified Vector Potential (Wb/m)", wxPoint(15, 78), wxSize(210, 49));
    else
        groupBox1->Create(this, wxID_ANY, "Specified Vector Potential (V)", wxPoint(15, 78), wxSize(210, 49));
    groupBox1->SetFont(*font);
    textCtrl1->Create(groupBox1, wxID_ANY, std::to_string(0.0), wxPoint(6, 5), wxSize(198, 20));
    textCtrl1->SetFont(*font);
    textCtrl1->Enable(true);
    if(_problem == physicProblems::PROB_MAGNETICS)
        groupBox2->Create(this, wxID_ANY, "Point Current (Amps)", wxPoint(15, 133), wxSize(210, 49));
    else
        groupBox2->Create(this, wxID_ANY, "Point Charge Density (C/m)", wxPoint(15, 133), wxSize(210, 49));
    groupBox2->SetFont(*font);
    textCtrl2->Create(groupBox2, wxID_ANY, std::to_string(0.0), wxPoint(6, 5), wxSize(198, 20));
    textCtrl2->SetFont(*font);
    textCtrl2->Enable(false);
    
    valueSizer->Add(groupBox1, 0, wxALL, 6);
    valueSizer->Add(groupBox2, 0, wxLEFT | wxRIGHT | wxBOTTOM, 6);
    
    /* The buttons */
    wxButton *okButton = new wxButton(this, wxID_OK, "Ok", wxPoint(69, 188), wxSize(75, 23));
    okButton->SetFont(*font);
    wxButton *cancelButton = new wxButton(this, wxID_CANCEL, "Cancel", wxPoint(150, 188), wxSize(75, 23));
    cancelButton->SetFont(*font);
    
    footerSizer->Add(okButton, 0, wxLEFT | wxRIGHT | wxBOTTOM, 6);
    footerSizer->Add(cancelButton, 0, wxRIGHT | wxBOTTOM, 6);
    
    topSizer->Add(headerSizer);
    topSizer->Add(radioSizer);
    topSizer->Add(valueSizer);
    topSizer->Add(footerSizer, 0, wxALIGN_RIGHT);
    
    updateInterface();
    
    SetSizerAndFit(topSizer);
}


void nodalPropertyDialog::onRadioButton1Cllick(wxCommandEvent &event)
{
    radioButton1->SetValue(true);
    radioButton2->SetValue(false);
    textCtrl1->Enable(true);
    textCtrl2->Enable(false);
}



void nodalPropertyDialog::onRadioButton2Cllick(wxCommandEvent &event)
{
    radioButton1->SetValue(false);
    radioButton2->SetValue(true);
    textCtrl1->Enable(false);
    textCtrl2->Enable(true);
}



void nodalPropertyDialog::getNodalProperty(nodalProperty &nodalProp)
{
    double value;
    nodalProp.setName(nameTextCtrl->GetValue().ToStdString());
    
    nodalProp.setState(radioButton1->GetValue());
    
    if(radioButton1->GetValue())
    {
        textCtrl1->GetValue().ToDouble(&value);
        nodalProp.setValue(value);
    }
    else
    {
        textCtrl2->GetValue().ToDouble(&value);
        nodalProp.setValue(value);
    }
        
}



void nodalPropertyDialog::setNodalProperty(nodalProperty &nodalProp)
{
    _nodalProperty = nodalProp;
    
    updateInterface();
}



void nodalPropertyDialog::clearNodalProperty()
{
    _nodalProperty.setName("New Point Property");
    _nodalProperty.setValue(0);
    _nodalProperty.setState(true);
    
    updateInterface();
}



void nodalPropertyDialog::updateInterface()
{
    std::ostream textCtrl1Stream(textCtrl1);
    std::ostream textCtrl2Stream(textCtrl2);
    
    nameTextCtrl->SetValue(_nodalProperty.getName());
    
    radioButton1->SetValue(_nodalProperty.getState());
    radioButton2->SetValue(!_nodalProperty.getState());
    
    textCtrl1->SetValue(wxEmptyString);
    textCtrl2->SetValue(wxEmptyString);
    
    textCtrl1Stream << setprecision(7);
    textCtrl2Stream << setprecision(7);
    
    if(_nodalProperty.getState())
    {
        textCtrl1Stream << _nodalProperty.getValue();
        textCtrl2Stream << 0;
        textCtrl1->Enable(true);
        textCtrl2->Enable(false);
    }
    else
    {
        textCtrl2Stream << _nodalProperty.getValue();
        textCtrl1Stream << 0;
        textCtrl2->Enable(true);
        textCtrl1->Enable(false);
    }
}



nodalPropertyDialog::~nodalPropertyDialog()
{
    
}



wxBEGIN_EVENT_TABLE(nodalPropertyDialog, wxDialog)
    EVT_RADIOBUTTON(generalFrameButton::ID_RadioButton1, nodalPropertyDialog::onRadioButton1Cllick)
    EVT_RADIOBUTTON(generalFrameButton::ID_RadioButton2, nodalPropertyDialog::onRadioButton2Cllick)
wxEND_EVENT_TABLE()