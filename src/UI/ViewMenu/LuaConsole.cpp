#include <UI/ViewMenu/LuaConsole.h>

luaConsole::luaConsole() : wxDialog(NULL, wxID_ANY, "Lua Console")
{
    wxFont *font = new wxFont(8.5, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
    
    wxBoxSizer *topSizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *intermediateSizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *footerSizer1 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *footerSizer2 = new wxBoxSizer(wxHORIZONTAL);
    
    _outputConsole->Create(this, wxID_ANY, wxEmptyString, wxPoint(12, 12), wxSize(373, 98), wxTE_MULTILINE);
    _outputConsole->SetFont(*font);
    _outputConsole->Enable(false);
    
    _inputConsole->Create(this, wxID_ANY, wxEmptyString, wxPoint(12, 116), wxSize(373, 98), wxTE_MULTILINE);
    _inputConsole->SetFont(*font);
    
    wxButton *clearInputButton = new wxButton(this, generalFrameButton::ID_BUTTON1, "Clear Input", wxPoint(12, 242), wxSize(75, 23));
    clearInputButton->SetFont(*font);
    
    wxButton *clearOutputButton = new wxButton(this, generalFrameButton::ID_BUTTON2, "Clear Output", wxPoint(93, 242), wxSize(75, 25));
    clearOutputButton->SetFont(*font);
    
    wxButton *evaluateButton = new wxButton(this, wxID_OK, "Evaluate", wxPoint(310, 242), wxSize(75, 23));
    evaluateButton->SetFont(*font);
    
    footerSizer2->Add(evaluateButton, 0, wxCENTER | wxALL, 6);
    
    footerSizer1->Add(clearInputButton, 0, wxCENTER | wxALL, 6);
    footerSizer1->Add(clearOutputButton, 0, wxCENTER | wxTOP | wxBOTTOM | wxRIGHT, 6);
    
    intermediateSizer->Add(footerSizer1, 0, wxALIGN_LEFT);
    intermediateSizer->Add(137, 0, 0);
    intermediateSizer->Add(evaluateButton, 0, wxALIGN_RIGHT | wxCENTER);
    
    topSizer->Add(_outputConsole, 0, wxALL, 6);
    topSizer->Add(_inputConsole, 0, wxLEFT | wxRIGHT | wxBOTTOM, 6);
    topSizer->Add(0, 20, 0);
    topSizer->Add(intermediateSizer);
    
    SetSizerAndFit(topSizer);
}



void luaConsole::onClearOutput(wxCommandEvent &event)
{
    _outputConsole->SetValue(wxEmptyString);
}



void luaConsole::onClearInput(wxCommandEvent &event)
{
    _inputConsole->SetValue(wxEmptyString);
}



void luaConsole::appendOutput(wxString &outputText)
{
    _outputConsole->AppendText(outputText);
}



void luaConsole::getInput(wxString &inputText)
{
    inputText = _inputConsole->GetValue();
}



luaConsole::~luaConsole()
{
    
}



wxBEGIN_EVENT_TABLE(luaConsole, wxDialog)
    EVT_BUTTON(generalFrameButton::ID_BUTTON1, luaConsole::onClearInput)
    EVT_BUTTON(generalFrameButton::ID_BUTTON2, luaConsole::onClearOutput)
wxEND_EVENT_TABLE()