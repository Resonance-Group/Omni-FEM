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

	unsigned char p_loopNumber = 0;
	
	bool p_isDisplayed = false;
	
	bool p_progressBarOneDisplayed = false;
	
	bool p_progressBarTwoDisplayed = false;
	
	wxGauge *p_gaugeOne = nullptr;
	
	wxGauge *p_gaugeTwo = nullptr;
	
	wxTextCtrl *p_messageOutput = nullptr;
	
	wxStaticBoxSizer *p_progressBarOneSizer = nullptr;
	
	wxStaticBoxSizer *p_progressBarTwoSizer = nullptr;
	
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
		if(p_loopNumber == 10)
		{
			this->Refresh();
			this->Update();
			p_loopNumber = 0;
		}
		else
			p_loopNumber++;
	}
	
	/**
	 * @brief 	Function that is called in order to add a message to the messaga box on the form
	 * 			Note that this function will append a new line character and a line feed to the message
	 * @param message The message that is to be displayed
	 */
	void outputMessage(wxString message)
	{
		p_messageOutput->AppendText(message + wxString("\r\n"));
		if(p_loopNumber == 10)
		{
			this->Refresh();
			this->Update();
			p_loopNumber = 0;
		}
		else
			p_loopNumber++;
	}
	
	void updateProgressBarOne(unsigned int value)
	{
		if(p_gaugeOne && value <= p_gaugeOne->GetRange())
		{
			p_gaugeOne->SetValue(value);
		}
		this->Refresh();
		this->Update();
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
		this->Refresh();
		this->Update();
	}
	
	void resetProgressBars()
	{
		resetProgressBarOne();
		resetProgressBarTwo();
	}
	
	void resetProgressBarOne()
	{
		if(p_gaugeOne)
			p_gaugeOne->SetValue(0);
		this->Refresh();
		this->Update();
	}
	
	void resetProgressBarTwo()
	{
		if(p_gaugeTwo)
			p_gaugeTwo->SetValue(0);
		this->Refresh();
		this->Update();
	}
	
	void updateProgressBarTwo(unsigned int value)
	{
		if(p_gaugeTwo && value <= p_gaugeTwo->GetRange())
		{
			p_gaugeTwo->SetValue(value);
		}
		this->Refresh();
		this->Update();
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
		this->Refresh();
		this->Update();
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
	
	void setProgressBarOneTitle(std::string title)
	{
		p_progressBarOneSizer->GetStaticBox()->SetLabel(wxString(title));
	}
	
	void setProgressBarTwoTitle(std::string title)
	{
		p_progressBarTwoSizer->GetStaticBox()->SetLabel(wxString(title));
	}
	
private:
	//! This macro is required for event procedure
    wxDECLARE_EVENT_TABLE();
	
};
#endif