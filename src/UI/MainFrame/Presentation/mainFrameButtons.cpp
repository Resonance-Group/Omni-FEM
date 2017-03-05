// This file will contain all of the function definitons for the different buttons on the main UI
#include "UI/OmniFEMFrame.h"


void OmniFEMMainFrame::onTwoDimButton(wxCommandEvent &event)
{
    createProblemChoosingClient();
	
//	controller.setAbstractProblemDim(problemDimension::two_dimension);
}



void OmniFEMMainFrame::onBackButton(wxCommandEvent &event)
{
    /*
	systemState currentState = controller.getOmniFEMState();
	
	if(currentState == systemState::dimensionChoosing)
	{
		createInitialStartupClient();
	}
	else if(currentState == systemState::problemChooseing)
	{
		createDimensionClient();
	}
     */ 
}



void OmniFEMMainFrame::onFinishButton(wxCommandEvent &event)
{
    int temp = _physicsProblemsListBox->GetSelection() + 1;
    _model.getProblemParameters()->setPhysicsProblem((physicProblems)temp);
//	createModelDefiningClient();
}