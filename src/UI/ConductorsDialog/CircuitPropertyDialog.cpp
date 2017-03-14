
#include <UI/ConductorsDialog/CircuitPropertyDialog.h>

circuitPropertyDialog::circuitPropertyDialog(wxWindow *par) : wxDialog(par, wxID_ANY, "Circuit Property")
{
    wxFont *font = new wxFont(8.5, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
    wxBoxSizer *headerSizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *radioSizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *footerSizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *inputSizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *intermediateSizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *topSizer = new wxBoxSizer(wxVERTICAL);
    
    _circuitProperty.setCurrent(0.0);
    _circuitProperty.setName("New Circuit");
    
    /* Creating the header of the windows */
    wxStaticText *name = new wxStaticText(this, wxID_ANY, "Name: ", wxPoint(12, 15), wxSize(38, 13));
    name->SetFont(*font);
    nameTextCtrl->Create(this, wxID_ANY, _circuitProperty.getName(), wxPoint(56, 12), wxSize(197, 20));
    nameTextCtrl->SetFont(*font);
    
    headerSizer->Add(name, 0, wxALIGN_CENTER | wxTOP | wxLEFT | wxRIGHT, 6);
    headerSizer->Add(nameTextCtrl, 0, wxALIGN_CENTER | wxTOP | wxRIGHT, 6);
    
    /* Creating the radio buttons for the options of the circuit being series or parallel */
    radioButton1->Create(this, generalFrameButton::ID_RadioButton1, "Parallel", wxPoint(12, 52), wxSize(65, 17));
    radioButton1->SetFont(*font);
    radioButton1->SetValue(true);
    radioButton2->Create(this, generalFrameButton::ID_RadioButton2, "Series", wxPoint(12, 75), wxSize(60, 17));
    radioButton2->SetFont(*font);
    radioButton2->SetValue(false);
    
    radioSizer->Add(radioButton1, 0, wxALIGN_TOP | wxLEFT | wxBOTTOM, 6);
    radioSizer->Add(radioButton2, 0, wxLEFT, 6);
    
    /* Creating the section for the input */
    wxStaticText *circuitText = new wxStaticText(this, wxID_ANY, "Circuit Current (A):", wxPoint(94, 47), wxSize(105, 13));
    circuitText->SetFont(*font);
    circuitCurrentTextCtrl->Create(this, wxID_ANY, std::to_string(_circuitProperty.getCurrent()), wxPoint(97, 63), wxSize(156, 20));
    circuitCurrentTextCtrl->SetFont(*font);
    
    inputSizer->Add(0, 2, 0);
    inputSizer->Add(circuitText, 0, wxALIGN_LEFT);
    inputSizer->Add(circuitCurrentTextCtrl, 0, wxRIGHT | wxBOTTOM, 6);
    
    /* The buttons */
    wxButton *okButton = new wxButton(this, wxID_OK, "Ok", wxPoint(97, 97), wxSize(75, 23));
    okButton->SetFont(*font);
    wxButton *cancelButton = new wxButton(this, wxID_CANCEL, "Cancel", wxPoint(178, 97), wxSize(75, 23));
    cancelButton->SetFont(*font);
    
    footerSizer->Add(okButton, 0, wxLEFT | wxRIGHT | wxBOTTOM | wxTOP, 6);
    footerSizer->Add(cancelButton, 0,  wxBOTTOM | wxTOP | wxRIGHT, 6);
    
    intermediateSizer->Add(radioSizer, 0, wxRIGHT, 20);
    intermediateSizer->Add(inputSizer);
    
    topSizer->Add(headerSizer);
    topSizer->Add(0, 15, 0);
    topSizer->Add(intermediateSizer);
    topSizer->Add(footerSizer, 0, wxALIGN_RIGHT);
    
    SetSizerAndFit(topSizer);
}


void circuitPropertyDialog::getNewCircuit(circuitProperty &newCircuit)
{
    double value = 0;
    
    newCircuit.setName(nameTextCtrl->GetValue().ToStdString());
    
    circuitCurrentTextCtrl->GetValue().ToDouble(&value);
    newCircuit.setCurrent(value);
    
    newCircuit.setCircuitSeriesState(!radioButton1->GetValue());
}



void circuitPropertyDialog::setCircuit(circuitProperty &circuit)
{
    _circuitProperty = circuit;
    
    setTextBox();
}



void circuitPropertyDialog::clearCircuit()
{
    _circuitProperty.setName("New Circuit");
    _circuitProperty.setCurrent(0.0);
    _circuitProperty.setCircuitSeriesState(false);
    
    setTextBox();
}



void circuitPropertyDialog::onRadioButton1Click(wxCommandEvent &event)
{
    radioButton1->SetValue(true);
    radioButton2->SetValue(false);    
}



void circuitPropertyDialog::onRadioButton2Click(wxCommandEvent &event)
{
    radioButton1->SetValue(false);
    radioButton2->SetValue(true);    
}



void circuitPropertyDialog::setTextBox()
{
    std::ostream currentStream(circuitCurrentTextCtrl);
    
    nameTextCtrl->SetValue(_circuitProperty.getName());
    
    radioButton1->SetValue(!_circuitProperty.getCircuitSeriesState());
    radioButton2->SetValue(_circuitProperty.getCircuitSeriesState());
    
    circuitCurrentTextCtrl->SetValue(wxEmptyString);
    currentStream << setprecision(7);
    currentStream << _circuitProperty.getCurrent();
}


circuitPropertyDialog::~circuitPropertyDialog()
{
    
}



wxBEGIN_EVENT_TABLE(circuitPropertyDialog, wxDialog)
    EVT_RADIOBUTTON(generalFrameButton::ID_RadioButton1, circuitPropertyDialog::onRadioButton1Click)
    EVT_RADIOBUTTON(generalFrameButton::ID_RadioButton2, circuitPropertyDialog::onRadioButton2Click)
wxEND_EVENT_TABLE()