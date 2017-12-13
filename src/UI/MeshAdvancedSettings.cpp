#include "UI/MeshAdvancedSettings.h"


meshAdvanced::meshAdvanced(wxWindow *par, meshSettings &settings) : wxDialog(par, wxID_ANY, "Mesh Settings Advnaced")
{
	p_meshSettings = &settings;
	
	wxFont font = wxFont(8.5, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
	
	wxBoxSizer *multiplePassesSizer = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer *smoothingSizer = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer *meshFactorSizer = new wxBoxSizer(wxHORIZONTAL);
	wxStaticBoxSizer *meshFormatsSizer = new wxStaticBoxSizer(wxHORIZONTAL, this, "Mesh File Save Formats");
	wxBoxSizer *topSizer = new wxBoxSizer(wxVERTICAL);
	
	meshFormatsSizer->GetStaticBox()->SetFont(font);
	
	wxIntegerValidator<unsigned int> greaterThenZeroVal;
	greaterThenZeroVal.SetMin(1);
	
	wxStaticText *passesText = new wxStaticText(this, wxID_ANY, "Number of Passes: ");
	passesText->SetFont(font);
	
	wxTextCtrl *passesTextCtrl = new wxTextCtrl(this, wxID_ANY, std::to_string(p_meshSettings->getMultiplePasses()), wxDefaultPosition, wxDefaultSize, 0, greaterThenZeroVal);
	passesTextCtrl->SetFont(font);
	
	multiplePassesSizer->Add(passesText, 0, wxALL, 6);
	multiplePassesSizer->Add(passesTextCtrl, 0, wxTOP | wxBOTTOM | wxRIGHT , 6);
	
	wxStaticText *llyodSmoothingStepsText = new wxStaticText(this, wxID_ANY, "Llyod Smoothing Steps: ");
	llyodSmoothingStepsText->SetFont(font);
	
	wxTextCtrl *llyodTextCtrl = new wxTextCtrl(this, wxID_ANY, std::to_string(p_meshSettings->getLlyodSmoothingSteps()), wxDefaultPosition, wxDefaultSize, 0, greaterThenZeroVal);
	llyodTextCtrl->SetFont(font);
	
	smoothingSizer->Add(llyodSmoothingStepsText, 0, wxLEFT | wxRIGHT | wxBOTTOM, 6);
	smoothingSizer->Add(llyodTextCtrl, 0, wxBOTTOM | wxRIGHT, 6);
	
	
	

}