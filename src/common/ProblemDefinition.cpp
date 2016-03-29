/* This file will contain the class implementation of the problemDefinition class */
#include "UI/problemDefinition.h"


problemDimension problemDefinition::getCurrentDimension()
{
	return dimension;
}




void problemDefinition::setProblemDimension(problemDimension dim)
{
	dimension = dim;
}




void problemDefinition::setPhysicsProblem(physicProblems phy)
{
	desginatedProblem = phy;
}



physicProblems problemDefinition::getPhysicProblem()
{
	return desginatedProblem;
}



void problemDefinition::setProblemName(wxString problemName)
{
	name = problemName;
}



wxString problemDefinition::getProblemName()
{
	return name;
}