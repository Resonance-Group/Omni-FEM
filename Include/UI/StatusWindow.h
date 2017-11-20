#ifndef STATUSWINDOW_H_
#define STATUSWINDOW_H_

#include <string>

#include <wx/wx.h>
#include <wx/gauge.h>
#include <wx/textctrl.h>
#include <wx/sizer.h>

class statusWindow : public wxDialog
{
private:
	bool p_isDisplayed = false;
	
	bool p_progressBarOneDisplayed = false;
	
	bool p_progressBarTwoDisplayed = false;
	
	wxGauge *p_gaugeOne;
	
	wxGauge *p_gaugeTwo;
	
	wxTextCtrl *p_messageOutput;
	
	wxStaticBoxSizer *p_progressBarOneSizer;
	
	wxStaticBoxSizer *p_progressBarTwoSizer;
	
	void onClose(wxCloseEvent &event)
	{
		this->Show(false);
		p_isDisplayed = false;
	}
	
	void onOk(wxCommandEvent &event)
	{
		this->Show(false);
		p_isDisplayed = false;
	}
public:

	statusWindow(std::string windowName, bool drawProgressBar1 = false, bool drawProgresssBar2 = false);
	
	/**
	 * @brief 	Function that is called in order to add a message to the messaga box on the form
	 * 			Note that this function will append a new line character and a line feed to the message
	 * @param message The message that is to be displayed
	 */
	void outputMessage(std::string message)
	{
		p_messageOutput->AppendText(wxString(message) + wxString("\r\n"));
	}
	
	/**
	 * @brief 	Function that is called in order to add a message to the messaga box on the form
	 * 			Note that this function will append a new line character and a line feed to the message
	 * @param message The message that is to be displayed
	 */
	void outputMessage(wxString message)
	{
		p_messageOutput->AppendText(message + wxString("\r\n"));
	}
	
	void updateProgressBarOne(unsigned int value)
	{
		if(p_gaugeOne && value < p_gaugeOne->GetRange())
		{
			p_gaugeOne->SetValue(value);
		}
	}
	
	void incrementProgressBarOne(unsigned int incrementValue)
	{
		if(p_gaugeOne)
		{
			if(p_gaugeOne->GetValue() + incrementValue < p_gaugeOne->GetRange())
				p_gaugeOne->SetValue(p_gaugeOne->GetValue() + incrementValue);
			else
				p_gaugeOne->SetValue(p_gaugeOne->GetRange());
		}
	}
	
	void resetProgressBars()
	{
		if(p_gaugeOne)
			p_gaugeOne->SetValue(0);
		
		if(p_gaugeTwo)
			p_gaugeTwo->SetValue(0);
	}
	
	void updateProgressBarTwo(unsigned int value)
	{
		if(p_gaugeTwo && value < p_gaugeTwo->GetRange())
		{
			p_gaugeTwo->SetValue(value);
		}
	}
	
	void incrementProgressBarTwo(unsigned int incrementValue)
	{
		if(p_gaugeTwo)
		{
			if(p_gaugeTwo->GetValue() + incrementValue < p_gaugeTwo->GetRange())
				p_gaugeTwo->SetValue(p_gaugeTwo->GetValue() + incrementValue);
			else
				p_gaugeTwo->SetValue(p_gaugeTwo->GetRange());
		}
	}
	
	void displayWindow()
	{
		this->Show(true);
		p_messageOutput->SetValue(wxEmptyString);
		p_isDisplayed = true;
	}
	
	bool getDisplayState()
	{
		return p_isDisplayed;
	}
	
private:
	//! This macro is required for event procedure
    wxDECLARE_EVENT_TABLE();
	
};
#endif