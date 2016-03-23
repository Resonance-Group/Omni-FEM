#include "UI/OmniFEMFrame.h"


OmniFEMMainFrameController::OmniFEMMainFrameController()
{
	
}



void OmniFEMMainFrameController::updateOmniFEMState(systemState omniFEMState)
{
	abstractionLayer.setOmniFEMState(omniFEMState);
}