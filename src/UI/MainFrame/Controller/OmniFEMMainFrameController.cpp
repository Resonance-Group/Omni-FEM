#include "UI/OmniFEMFrame.h"


OmniFEMMainFrameController::OmniFEMMainFrameController()
{
	
}



void OmniFEMMainFrameController::updateOmniFEMState(systemState omniFEMState)
{
	abstractionLayer.setOmniFEMState(omniFEMState);
}



systemState OmniFEMMainFrameController::getOmniFEMState()
{
    return abstractionLayer.getOmniFEMState();
}



void OmniFEMMainFrameController::setAbstractProblemDim(problemDimension dim)
{
	abstractionLayer.setProblemDimension(dim);
}



problemDimension OmniFEMMainFrameController::getAbstractProblemDim()
{
	return abstractionLayer.getProblemDimension();
}



physicProblems OmniFEMMainFrameController::getAbstractProblemPhysics()
{
	return abstractionLayer.getProblemPhysics();
}



void OmniFEMMainFrameController::setAbstractProblemPhysics(physicProblems phy)
{
	abstractionLayer.setProblemPhysics(phy);
}