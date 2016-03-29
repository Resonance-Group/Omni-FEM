#ifndef OMNIFEMProblemDefinition_H_
#define OMNIFEMProblemDefininition_H_

#include <wx/wx.h>

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
	
	//! A string containing the name of the problem
	wxString name = "untitiled";
	
	//! The data type to store what physics problem the simulation is
	physicProblems desginatedProblem;
	
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
	
};



#endif