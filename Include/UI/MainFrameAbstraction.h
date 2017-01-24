#ifndef MAINFRAMEABSTRACTION_H_
#define MAINFRAMEABSTRACTION_H_

#include <wx/wx.h>
#include <wx/aboutdlg.h>
#include <wx/stdpaths.h>
#include <string.h>
#include <wx/textctrl.h>
#include <wx/stattext.h>
#include <UI/problemDefinition.h>
#include <wx/listbox.h>
#include <wx/sizer.h>
#include <wx/treectrl.h>
#include <UI/geometryEditor2D.h>
#include <UI/common.h>
#include <UI/PropertiesDialog.h>
#include <common/BoundaryConditions.h>

/*! \class OmniFEMMainFrameAbstraction
	\brief The class representing the abstraction layer for OmniFEM's main frame
	
	This will contain all of the data that the presentation will need access to.
     * THis will also contain all of the high level data that is needed for the simualtion to run.
     * This includes data of teh boundary condition.
*/
class OmniFEMMainFrameAbstraction
{
	
public:
	//! This is the main constructor for the class
	OmniFEMMainFrameAbstraction();
	
	//! This will return the state of OmniFEM
	/*!
		/return The state of OmniFEM
	*/
	systemState getOmniFEMState();

	//! This function will set the state of OmniFEM.
	/*!
		This function will also call an event in order to update the presentation approiately
		/param omniFEMState The state that OmniFEM will be going into.
	*/
	void setOmniFEMState(systemState omniFEMState);
	
	//! Function to get the current problem dimension
	problemDimension getProblemDimension();
	
	//! Function to set the problem dimension
	void setProblemDimension(problemDimension dimension);
	
	//! Function used to get the current physics of the problem 
	physicProblems getProblemPhysics();
	
	//! Function used to set the current physics problem
	void setProblemPhysics(physicProblems phy);
	
	//! This function will retrive the border width for the box sizer
	int getBorderWidth();
	
	//! This will retrieve the workspace/solution name
	wxString getworkspaceName();
	
	//! This will set the workspace/solution name
	void setWorkspaceName(wxString name);
	
	//! This will set the main tree ID for the tree control
	void setRootTreeID(wxTreeItemId tree);
	
	//! This will return the main tree ID for the tree control
	/* 
		This is not an actual interger ID but rather the whole class
	*/
	wxTreeItemId getRootTreeID();
	
	//! This will retreive the problem IF from the simuation object
	wxTreeItemId getSimProblemID();
	
	//! This will set the problem IF in the simulation object
	void setSimProblemID(wxTreeItemId problemID);
	
	//! This will set the geometry ID of the simulation object
	void setSimGeometryID(wxTreeItemId geometryID);
	
	//! This will get the geometry ID of the simulation object
	wxTreeItemId getSimGeometryID();
	
	//! This will set the Material ID of the simulation object
	void setSimMaterialsID(wxTreeItemId materialsID);
	
	//! This will get the material ID of the simulation object
	wxTreeItemId getSimMaterialsID();
	
	//! This will set the mesh ID of the simulation object
	void setSimMeshID(wxTreeItemId simMeshID);
	
	//! This will get the mesh ID of the simulation object
	wxTreeItemId getSimMeshID();
	
	//! This will set the simulation name
	void setSimulationName(wxString simName);
	
	//! This will retieve the simulation name
	wxString getSimulationName();
	
	/************
	* Variables *
	*************/
private:
	
	//! The state of OmniFEM
	/*!
		This variable holds the current state of OmniFEM
	*/
	systemState omniFEMSystemState = systemState::initialStartUp;
	
	//! This object is created for each physics problem
	/*!
		This is setting up for future additions where the model tree builder
		will be able to display more then one physics problem per solution.
		Each phyics problem will be it's own object in code
	*/
	problemDefinition definition;
	
	//! This variable stores the border size
	int borderSize = 5;
	
	//! The name of the solution/workspace
	wxString workspaceName = "untitled";
	
	//! This variable is used to store the data for the tree control in the model builder window
	wxTreeItemId rootTree;
    
    

};

#endif