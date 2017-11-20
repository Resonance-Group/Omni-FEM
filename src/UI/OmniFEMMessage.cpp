#include "common/OmniFEMMessage.h"

OmniFEMMsg *OmniFEMMsg::p_instance = 0;

void OmniFEMMsg::MsgFatal(std::string message)
{
	for(int i = 0; i < instance()->getStatusWindows().size(); i++)
	{
		statusWindow *test = instance()->getStatusWindows()[i];
		if(test->getDisplayState())
		{
			test->outputMessage(wxString("Fatal Error: ") + wxString(message));
		}
	}
	
	// Then log the message if needed
}



void OmniFEMMsg::wxMsgFatal(wxString message)
{
	for(int i = 0; i < instance()->getStatusWindows().size(); i++)
	{
		statusWindow *test = instance()->getStatusWindows()[i];
		if(test->getDisplayState())
		{
			test->outputMessage(wxString("Fatal Error: ") + message);
		}
	}
	
	// Then log the message if needed
}



void OmniFEMMsg::MsgError(std::string message)
{
	for(int i = 0; i < instance()->getStatusWindows().size(); i++)
	{
		statusWindow *test = instance()->getStatusWindows()[i];
		if(test->getDisplayState())
		{
			test->outputMessage(wxString("Error: ") + wxString(message));
		}
	}
	
	// Then log the message if needed
}




void OmniFEMMsg::wxMsgError(wxString message)
{
	for(int i = 0; i < instance()->getStatusWindows().size(); i++)
	{
		statusWindow *test = instance()->getStatusWindows()[i];
		if(test->getDisplayState())
		{
			test->outputMessage(wxString("Error: ") + message);
		}
	}
	
	// Then log the message if needed
}



void OmniFEMMsg::MsgWarning(std::string message)
{
	for(int i = 0; i < instance()->getStatusWindows().size(); i++)
	{
		statusWindow *test = instance()->getStatusWindows()[i];
		if(test->getDisplayState())
		{
			test->outputMessage(wxString("Warning: ") + wxString(message));
		}
	}
	
	// Then log the message if needed
}



void OmniFEMMsg::wxMsgWarning(wxString message)
{
	for(int i = 0; i < instance()->getStatusWindows().size(); i++)
	{
		statusWindow *test = instance()->getStatusWindows()[i];
		if(test->getDisplayState())
		{
			test->outputMessage(wxString("Warning: ") + message);
		}
	}
	
	// Then log the message if needed
}



void OmniFEMMsg::MsgInfo(std::string message)
{
	for(int i = 0; i < instance()->getStatusWindows().size(); i++)
	{
		statusWindow *test = instance()->getStatusWindows()[i];
		if(test->getDisplayState())
		{
			test->outputMessage(wxString("Info: ") + wxString(message));
		}
	}
	
	// Then log the message if needed
}



void OmniFEMMsg::wxMsgInfo(wxString message)
{
	for(int i = 0; i < instance()->getStatusWindows().size(); i++)
	{
		statusWindow *test = instance()->getStatusWindows()[i];
		if(test->getDisplayState())
		{
			test->outputMessage(wxString("Info: ") + message);
		}
	}
	
	// Then log the message if needed
}



void OmniFEMMsg::MsgStatus(std::string message)
{
	wxString finalMessage = wxString("Status: ") + wxString(message);
	for(int i = 0; i < instance()->getStatusWindows().size(); i++)
	{
		statusWindow *test = instance()->getStatusWindows()[i];
		if(test->getDisplayState())
		{
			test->outputMessage(finalMessage);
		}
	}
	
	if(getLoggedState())
	{
		instance()->logMessage(finalMessage);
	}
	// Then log the message if needed
}
  



void OmniFEMMsg::wxMsgStatus(wxString message)
{
	for(int i = 0; i < instance()->getStatusWindows().size(); i++)
	{
		statusWindow *test = instance()->getStatusWindows()[i];
		if(test->getDisplayState())
		{
			test->outputMessage(wxString("Status: ") + message);
		}
	}
	
	// Then log the message if needed
}