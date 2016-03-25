// This file will contain all of the function definitons for the different buttons on the main UI
#include "UI/OmniFEMFrame.h"


void OmniFEMMainFrame::onTwoDimButton(wxCommandEvent &event)
{
    createProblemChoosingClient();
}



void OmniFEMMainFrame::onBackButton(wxCommandEvent &event)
{
	systemState currentState = controller.getOmniFEMState();
	
	if(currentState == systemState::dimensionChoosing)
	{
		createInitialStartup();
	}
	else if(currentState == systemState::problemChooseing)
	{
		createDimensionClient();
	}
}