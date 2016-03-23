/* This file contains the main data for the OmniFEM.
	For example, this structure s*/
#include "UI/OmniFEMFrame.h"

OmniFEMMainFrameAbstraction::OmniFEMMainFrameAbstraction()
{
	
}
	
	

systemState OmniFEMMainFrameAbstraction::getOmniFEMState()
{
	return omniFEMSystemState;
}



void OmniFEMMainFrameAbstraction::setOmniFEMState(systemState omniFEMState)
{
	omniFEMSystemState = omniFEMState;
}