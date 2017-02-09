#include <UI/NodalProperty/NodalPropertyDialog.h>

nodalPropertyDialog::nodalPropertyDialog() : wxDialog(NULL, wxID_ANY, "Nodal Property", wxDefaultPosition)
{
    wxFont *font = new wxFont(8.5, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
    wxBoxSizer *topSizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *headerSizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *radioSizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *valueSizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *footerSizer = new wxBoxSizer(wxHORIZONTAL);
    
    _nodalProperty.setName("New Point Property");
    _nodalProperty.setValue(0);
    
    /* This first part is for the header */
    wxStaticText *name = new wxStaticText(this, wxID_ANY, "Name:", wxPoint(12, 9), wxSize(38, 13));
    name->SetFont(*font);
    nameTextCtrl->Create(this, wxID_ANY, _nodalProperty.getName(), wxPoint(50, 6), wxSize(175, 20));
    nameTextCtrl->SetFont(*font);
    
    headerSizer->Add(name, 0, wxALIGN_CENTER);
    headerSizer->Add(nameTextCtrl, 0, wxSHAPED);
    
    /* Adding in the radio buttons */
    radioButton1->Create(this, generalFrameButton::ID_RadioButton1, "Specified Potential Property", wxPoint(50, 32), wxSize(176, 19));
    radioButton1->SetFont(*font);
    radioButton1->SetValue(true);
    radioButton2->Create(this, generalFrameButton::ID_RadioButton2, "Point Current Property", wxPoint(50, 55), wxSize(144, 19));
    radioButton2->SetFont(*font);
    radioButton2->SetValue(false);
    
    radioSizer->Add(radioButton1);
    radioSizer->Add(radioButton2);
    
    /*Creating the group boxes */
    groupBox1->Create(this, wxID_ANY, "Specified Vector Potential (Wb/m)", wxPoint(15, 78), wxSize(210, 49));
    groupBox1->SetFont(*font);
    textCtrl1->Create(groupBox1, wxID_ANY, std::to_string(0.0), wxPoint(6, 5), wxSize(198, 20));
    textCtrl1->SetFont(*font);
    textCtrl1->Enable(true);
    groupBox2->Create(this, wxID_ANY, "Point Current (Amps)", wxPoint(15, 133), wxSize(210, 49));
    groupBox2->SetFont(*font);
    textCtrl2->Create(groupBox2, wxID_ANY, std::to_string(0.0), wxPoint(6, 5), wxSize(198, 20));
    textCtrl2->SetFont(*font);
    textCtrl2->Enable(false);
    
    valueSizer->Add(groupBox1);
    valueSizer->Add(groupBox2);
    
    /* The buttons */
    wxButton *okButton = new wxButton(this, wxID_OK, "Ok", wxPoint(69, 188), wxSize(75, 23));
    okButton->SetFont(*font);
    wxButton *cancelButton = new wxButton(this, wxID_CANCEL, "Cancel", wxPoint(150, 188), wxSize(75, 23));
    cancelButton->SetFont(*font);
    
    footerSizer->Add(okButton);
    footerSizer->Add(cancelButton);
    
    topSizer->Add(headerSizer, 0, wxALIGN_CENTER_VERTICAL);
    topSizer->Add(radioSizer, 0, wxALIGN_CENTER);
    topSizer->Add(valueSizer, 0, wxALIGN_CENTER);
    topSizer->Add(footerSizer, 0, wxALIGN_RIGHT);
    
    SetSizerAndFit(topSizer);
    
    /*
    this->SetInitialSize(wxSize(238, 220));
    this->Fit();
    this->SetMaxSize(wxSize(238, 220));
     */
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
    
    nameTextCtrl->SetValue(_nodalProperty.getName());
    radioButton1->SetValue(_nodalProperty.getState());
    radioButton2->SetValue(!_nodalProperty.getState());
    
    if(_nodalProperty.getState())
    {
        textCtrl1->Enable(true);
        textCtrl1->SetValue(std::to_string(_nodalProperty.getValue()));
        textCtrl2->SetValue(std::to_string(0.0));
        textCtrl2->Enable(false);
    }
    else
    {
        textCtrl2->Enable(true);
        textCtrl2->SetValue(std::to_string(_nodalProperty.getValue()));
        textCtrl1->SetValue(std::to_string(0.0));
        textCtrl1->Enable(false);
    }
}



void nodalPropertyDialog::clearNodalProperty()
{
    _nodalProperty.setName("New Point Property");
    _nodalProperty.setValue(0);
    _nodalProperty.setState(true);
    
    nameTextCtrl->SetValue(_nodalProperty.getName());
    radioButton1->SetValue(_nodalProperty.getState());
    radioButton2->SetValue(!_nodalProperty.getState());
    
    textCtrl2->SetValue(std::to_string(0.0));
    textCtrl1->SetValue(std::to_string(0.0));
    
    if(_nodalProperty.getState())
    {
        textCtrl1->Enable(true);
        textCtrl2->Enable(false);
    }
    else
    {
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