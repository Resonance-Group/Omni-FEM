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



problemDimension OmniFEMMainFrameAbstraction::getProblemDimension()
{
	return definition.getCurrentDimension();
}



void OmniFEMMainFrameAbstraction::setProblemDimension(problemDimension dimension)
{
	definition.setProblemDimension(dimension);
}


void OmniFEMMainFrameAbstraction::setProblemPhysics(physicProblems phy)
{
	definition.setPhysicsProblem(phy);
}



physicProblems OmniFEMMainFrameAbstraction::getProblemPhysics()
{
	return definition.getPhysicProblem();
}