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



void problemDefinition::setProblemID(wxTreeItemId treeItemID)
{
	problemID = treeItemID;
}




wxTreeItemId problemDefinition::getProblemID()
{
	return problemID;
}



void problemDefinition::setGeometryID(wxTreeItemId treeItemID)
{
	geometryID = treeItemID;
}




wxTreeItemId problemDefinition::getGeometryID()
{
	return geometryID;
}



void problemDefinition::setMaterialsID(wxTreeItemId treeItemID)
{
	materialsID = treeItemID;
}




wxTreeItemId problemDefinition::getMaterialsID()
{
	return materialsID;
}



void problemDefinition::setMeshID(wxTreeItemId treeItemID)
{
	meshID = treeItemID;
}



wxTreeItemId problemDefinition::getMeshID()
{
	return meshID;
}



void problemDefinition::setResultsID(wxTreeItemId treeItemID)
{
	resultsID = treeItemID;
}



wxTreeItemId problemDefinition::getResultsID()
{
	return resultsID;
}