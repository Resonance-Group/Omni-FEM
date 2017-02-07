#ifndef MAINFRAMCONTROLLER_H_
#define MAINFRAMCONTROLLER_H_

#include <string.h>

#include <wx/wx.h>
#include <wx/aboutdlg.h>
#include <wx/stdpaths.h>
#include <wx/listbox.h>
#include <wx/sizer.h>
#include <wx/treectrl.h>

//#include <UI/problemDefinition.h>
#include <UI/geometryEditor2D.h>
#include <UI/common.h>
#include <UI/PropertiesDialog.h>
#include <UI/MainFrameAbstraction.h>

#include <common/BoundaryConditions.h>
#include <common/ElectricalBoundary.h>
#include <common/MagneticBoundary.h>
#include <common/enums.h>

#include <UI/MaterialsDialog/MaterialDialog.h>
#include <UI/BoundaryDialog/BoundaryDialog.h>

/*! \class OmniFEMMainFrameController
 *  \brief The class representing the controller layer for OmniFEM's main frame
 * 
 *  This class contains all of the processing calls in order to manage the OmniFEM MainFrame.
 *	This class handles the presentation of the main frame for Omni-FEM and is thus one of the largest objects in the whole program
 *  
*/
class OmniFEMMainFrameController
{
/* Constructor */
public:
	OmniFEMMainFrameController();
	
	/************
	* Variables *
	*************/
private:
	
	OmniFEMMainFrameAbstraction abstractionLayer;
	
	/**********************
	* Function Prototypes *
	***********************/
public:

	//! This function will update the systemState of OmniFEM in the abstraction layer
	void updateOmniFEMState(systemState omniFEMState);
    
    //! This will get the current state of OmniFEM contained in the abstraction layer
    systemState getOmniFEMState();
	
	//! This function will set the problem dimension in the 
	void setAbstractProblemDim(problemDimension dim);
	
	//! This function will be used to get the problem dimension from the abstraction layer
	problemDimension getAbstractProblemDim();
	
	//! This function will get the physics problem in the abstraction
	physicProblems getAbstractProblemPhysics();
	
	//! This function will set the phycis problem in the abstraction
	void setAbstractProblemPhysics(physicProblems phy);
	
	//! This function will retrieve the border size of the boxSizer.
	int getBorderSize();
	
	//! This will get the workspace/solution name from the abstraction layer
	wxString getWorkspaceNameAbstraction();
	
	//! This will set the workspace name in the abstraction layer
	void setWorkspaceNameAbstraction(wxString name);
	
	//! This will set the root tree ID object in the abstraction layer
	void setRootTreeIDAbstraction(wxTreeItemId tree);
	
	//! This will get the root tree ID object from the abstraction layer
	wxTreeItemId getRootTreeIDAbstraction();
	
	//! This will retreive the problem ID from the abstraction layer
	wxTreeItemId getAbstractProblemID();
	
	//! This will set the problem IF in the simulation object
	void setAbstractProblemID(wxTreeItemId problemID);
	
	//! This will set the geometry ID of the simulation object
	void setAbstractGeometryID(wxTreeItemId geometryID);
	
	//! This will get the geometry ID of the simulation object
	wxTreeItemId getAbstractGeometryID();
	
	//! This will set the Material ID of the simulation object
	void setAbstractMaterialsID(wxTreeItemId materialsID);
	
	//! This will get the material ID of the simulation object
	wxTreeItemId getAbstractMaterialsID();
	
	//! This will set the mesh ID of the simulation object
	void setAbstractMeshID(wxTreeItemId simMeshID);
	
	//! This will get the mesh ID of the simulation object
	wxTreeItemId getAbstractMeshID();

	//! This will retrieve the simulation name from the abstract layer
	wxString getAbstractSimName();
	
	//! This will set the simulation name in the abstraction layer
	void setAbstractSimName(wxString name);
    
    //! This function is called when the user presses CTRL+M or clicks on the materials under the properties pane
    void createMaterialDialog();
    
    void createBoundaryDialog();
	
};

#endif