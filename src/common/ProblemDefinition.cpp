/* This file will contain the class implementation of the problemDefinition class */
#include "UI/problemDefinition.h"
#include <common/ProblemDefinition.h>

// This is the old stuff that needs to be intergrated in the new problem definition class
problemDimension problemDef::getCurrentDimension()
{
	return dimension;
}




void problemDef::setProblemDimension(problemDimension dim)
{
	dimension = dim;
}




void problemDef::setPhysicsProblem(physicProblems phy)
{
	desginatedProblem = phy;
}



physicProblems problemDef::getPhysicProblem()
{
	return desginatedProblem;
}



void problemDef::setProblemName(wxString problemName)
{
	name = problemName;
}



wxString problemDef::getProblemName()
{
	return name;
}



void problemDef::setProblemID(wxTreeItemId treeItemID)
{
	problemID = treeItemID;
}




wxTreeItemId problemDef::getProblemID()
{
	return problemID;
}



void problemDef::setGeometryID(wxTreeItemId treeItemID)
{
	geometryID = treeItemID;
}




wxTreeItemId problemDef::getGeometryID()
{
	return geometryID;
}



void problemDef::setMaterialsID(wxTreeItemId treeItemID)
{
	materialsID = treeItemID;
}




wxTreeItemId problemDef::getMaterialsID()
{
	return materialsID;
}



void problemDef::setMeshID(wxTreeItemId treeItemID)
{
	meshID = treeItemID;
}



wxTreeItemId problemDef::getMeshID()
{
	return meshID;
}



void problemDef::setResultsID(wxTreeItemId treeItemID)
{
	resultsID = treeItemID;
}



wxTreeItemId problemDef::getResultsID()
{
	return resultsID;
}

//-------------------The new stuff------------------------

