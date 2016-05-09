#ifndef OMNIFEMProblemDefinition_H_
#define OMNIFEMProblemDefininition_H_

#include <wx/wx.h>
#include <wx/treectrl.h>

//! Enum contianing the dimension of the problem
/*! 
	Please note that Omni-FEM does not support all of these dimensions.
	Some are placed here as a place holder for future releases
*/
enum class problemDimension
{
	zero_Dimension = 0,
	one_dimension = 1,
	two_dimension = 2,
	three_dimension = 3
};



//! Enum containing the different physics problems
/*!
	This is the enum that is used to determine what physics problem 
	will be simulated. This could effect the view of some menus.
	For a later addition of multiphysics, this system will need
	to be revised.
	
	For now, the enum number must correspond to the index number in the wxArrayString object.
*/
enum class physicProblems
{
	electrostatics = 0,
	magnetics = 1
};


//! This class will handle all of the problem definition settings.
/*! 
	This class is designed to contain any specific infomation about a problem.
	For exanple, the results, the geometry, the mesh.
	Bounday condition setting, name, file path.
	This class must be created for eah problem
*/
class problemDefinition
{

	/************
	* Variables *
	*************/
private:
	//! A variable holding the dimension of the problem
	problemDimension dimension = problemDimension::zero_Dimension;
	
	//! A string containing the name of the simulation
	wxString name = "untitiled";
	
	//! The data type to store what physics problem the simulation is
	physicProblems desginatedProblem;
	
	//! This is the tree item id associated with the simuation
	/*
		This will be used in creating the Hieachy Listbox or the tree list
	*/
	wxTreeItemId problemID;
	
	//! This is the tree item id associated with the geometry for the simulation
	/*
		This will be used in creating the Hieachy Listbox or the tree list
	*/
	wxTreeItemId geometryID;
	
	//! This is the tree id associated with the materials for the simulation
	/*
		This will be used in creating the Hieachy Listbox or the tree list
	*/
	wxTreeItemId materialsID;
	
	//! This is the tree id associated with the mesh of the simulation
	/*
		This will be used in creating the Hieachy Listbox or the tree list
	*/
	wxTreeItemId meshID;
	
	//! This is the tree id associated with the results of the simultion
	/*
		This will be used in creating the Hieachy Listbox or the tree list
	*/
	wxTreeItemId resultsID;
	
	/**********************
	* Function Prototypes *
	***********************/
public:

	//! Function used to query the current dimesion of the problem
	problemDimension getCurrentDimension();
	
	//! Function used to set the current dimension of the problem
	void setProblemDimension(problemDimension dim);
	
	//! Function used to set the physics problem
	void setPhysicsProblem(physicProblems phy);
	
	//! Function used to get the current physics problem
	physicProblems getPhysicProblem();
	
	//! Function used to get the name of the problem
	wxString getProblemName();
	
	//! Function used to set the name of the problem
	void setProblemName(wxString problemName);
	
	//! Function used to set the problem tree ID
	/*
		This creates the object. There is no int ID. This function will
		actually set the problemID = the arguement
	*/
	void setProblemID(wxTreeItemId treeItemID);
	
	//! Function used to get the problem tree ID
	wxTreeItemId getProblemID();
	
	//! Function used to set the geometry tree ID
	/*
		This creates the object. There is no int ID. This function will
		actually set the geometryID = the arguement
	*/
	void setGeometryID(wxTreeItemId treeItemID);
	
	//! This function will get the geometry tree ID
	wxTreeItemId getGeometryID();
	
	//! Function used to set the material tree ID
	/*
		This creates the object. There is no int ID. This function will
		actually set the materialID = the arguement
	*/
	void setMaterialsID(wxTreeItemId treeItemID);
	
	//! This function will get the material tree ID
	wxTreeItemId getMaterialsID();
	
	//! Function used to set the mesh tree ID
	/*
		This creates the object. There is no int ID. This function will
		actually set the meshID = the arguement
	*/
	void setMeshID(wxTreeItemId treeItemID);
	
	//! This function will get the mesh Tree ID
	wxTreeItemId getMeshID();
	
	//! Function used to set the results tree ID
	/*
		This creates the object. There is no int ID. This function will
		actually set the resultsID = the arguement
	*/
	void setResultsID(wxTreeItemId treeItemID);
	
	//! This function will be used to get the results Tree ID
	wxTreeItemId getResultsID();
};



#endif