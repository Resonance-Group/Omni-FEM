#ifndef OMNIFEMMESSAGE_H_
#define OMNIFEMMESSAGE_H_

#include <vector>

#include <wx/wx.h>
#include <UI/StatusWindow.h>



enum Status_Windows
{
	LOG_STATUS_WINDOW = 0,
	MESH_STATUS_WINDOW,
	SOLVER_STATUS_WINDOW
};

class OmniFEMMsg
{
private:

	static OmniFEMMsg *p_instance;
	
	bool p_logMessage = false;
	
	std::vector<statusWindow*> p_statusWindows;
	
public:
	

	OmniFEMMsg()
	{
		// Create the three different windows
		p_statusWindows.push_back(new statusWindow("Log Status Window", false, false));
		p_statusWindows.push_back(new statusWindow("Mesh Status Window", true, false));
		p_statusWindows[1]->setProgressBarOneTitle("Mesh Progress");
		p_statusWindows.push_back(new statusWindow("Solver Status Window", true, true));
	}
	
	void instanceSetLogStatus(bool state)
	{
		p_logMessage = state;
	}
	
	bool instanceGetLogState()
	{
		return p_logMessage;
	}
	
	
	std::vector<statusWindow*> getStatusWindows()
	{
		return p_statusWindows;
	}
	
	void MsgFatal(std::string message);
	void wxMsgFatal(wxString message);
	
	void MsgError(std::string message);
	void wxMsgError(wxString message);
	
	void MsgWarning(std::string message);
	void wxMsgWarning(wxString message);
	
	void MsgInfo(std::string message);
	void wxMsgInfo(wxString message);
	
	void MsgStatus(std::string message);
	void wxMsgStatus(wxString message);
	
	void displayWindow(Status_Windows displayWindowNum)
	{
		instance()->getStatusWindows()[(int)displayWindowNum]->displayWindow();
	}
	
	void incrementProgressBar(unsigned int value, Status_Windows window, int progressBar)
	{
		if(progressBar == 1)
			instance()->getStatusWindows()[(int)window]->incrementProgressBarOne(value);
		else if(progressBar == 2)
			instance()->getStatusWindows()[(int)window]->incrementProgressBarTwo(value);
	}
	
	void setProgressBarValue(unsigned int value, Status_Windows window, int progressBar)
	{
		if(progressBar == 1)
			instance()->getStatusWindows()[(int)window]->updateProgressBarOne(value);
		else if(progressBar == 2)
			instance()->getStatusWindows()[(int)window]->updateProgressBarTwo(value);
	}
	
	void resetProgressBar(Status_Windows window, bool resetBarOne, bool resetBarTwo = false)
	{
		if(resetBarOne)
			instance()->getStatusWindows()[(int)window]->resetProgressBarOne();
		
		if(resetBarTwo)
			instance()->getStatusWindows()[(int)window]->resetProgressBarTwo();
	}
	
	static OmniFEMMsg *instance()
	{
		if(!p_instance)
		{
			p_instance = new OmniFEMMsg();
		}
		return p_instance;
	}
	
	void setLogMessages(bool state)
	{
		instance()->instanceSetLogStatus(state);
	}
	
	bool getLoggedState()
	{
		return instance()->instanceGetLogState();
	}
	
	void logMessage(wxString message)
	{
		return;
	}
};


#endif