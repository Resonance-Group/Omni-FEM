#ifndef OMNIFEMProblemDefinition_H_
#define OMNIFEMProblemDefininition_H_

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
	
	
	/**********************
	* Function Prototypes *
	***********************/
public:
	//! Function used to query the current dimesion of the problem
	problemDimension getCurrentDimension();
	//! Function used to set the current dimension of the problem
	void setProblemDimension(problemDimension dim);
	
};



#endif