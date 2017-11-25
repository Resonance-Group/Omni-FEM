#include <UI/StatusWindow.h>

statusWindow::statusWindow(std::string windowName, bool drawProgressBar1, bool drawProgresssBar2) : wxDialog(NULL, wxID_ANY, windowName)
{
	wxFont font(8.5, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
	wxBoxSizer *footerSizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *topSizer = new wxBoxSizer(wxVERTICAL);
	wxStaticBoxSizer *logSizer = new wxStaticBoxSizer(wxVERTICAL, this, "Log");
	logSizer->GetStaticBox()->SetFont(font);
	// Progress Bars should be initilizied to 270 px length, 20 width
	if(drawProgressBar1 || drawProgresssBar2)
	{
		if(drawProgressBar1)
		{
			p_progressBarOneSizer = new wxStaticBoxSizer(wxVERTICAL, this, "Progress Bar 1");
			p_progressBarOneSizer->GetStaticBox()->SetFont(font);
			
			p_gaugeOne = new wxGauge(p_progressBarOneSizer->GetStaticBox(), wxID_ANY, 100, wxDefaultPosition, wxSize(320, 20));
			p_progressBarOneSizer->Add(p_gaugeOne, 0, wxCENTER | wxALL, 6);
		}
		
		if(drawProgresssBar2)
		{
			p_progressBarTwoSizer = new wxStaticBoxSizer(wxVERTICAL, this, "Progress Bar 2");
			p_progressBarTwoSizer->GetStaticBox()->SetFont(font);
			
			p_gaugeTwo = new wxGauge(p_progressBarTwoSizer->GetStaticBox(), wxID_ANY, 100, wxDefaultPosition, wxSize(320, 20));
			p_progressBarTwoSizer->Add(p_gaugeTwo, 0, wxCENTER | wxALL, 6);
		}
	}
	
	p_messageOutput = new wxTextCtrl(logSizer->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(320, 140), wxTE_MULTILINE | wxTE_READONLY  | wxHSCROLL);
	p_messageOutput->SetFont(font);
	logSizer->Add(p_messageOutput, 0, wxCENTER | wxALL, 6);
	
	wxButton *okButton  = new wxButton(this, wxID_OK, "Ok", wxDefaultPosition, wxSize(75, 23));
    okButton->SetFont(font);
	footerSizer->Add(okButton, 0, wxALL, 6);
	
	if(drawProgressBar1)
		topSizer->Add(p_progressBarOneSizer, 0, wxALL, 6);
	
	if(drawProgresssBar2)
	{
		if(drawProgressBar1)
			topSizer->Add(p_progressBarTwoSizer, 0, wxLEFT | wxRIGHT | wxBOTTOM, 6);
		else
			topSizer->Add(p_progressBarTwoSizer, 0, wxALL, 6);
	}
	
	if(drawProgressBar1 || drawProgresssBar2)
		topSizer->Add(logSizer, 0, wxLEFT | wxRIGHT, 6);
	else
		topSizer->Add(logSizer, 0, wxALL, 6);
		
	topSizer->Add(footerSizer, 0, wxALIGN_RIGHT);
	
	SetSizerAndFit(topSizer);
}

wxBEGIN_EVENT_TABLE(statusWindow, wxDialog)
	EVT_CLOSE(statusWindow::onClose)
	EVT_BUTTON(wxID_OK, statusWindow::onOk)
wxEND_EVENT_TABLE()