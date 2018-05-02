#ifndef MESH_ADVANCED_SETTINGS_H_
#define MESH_ADVANCED_SETTINGS_H_

#include <string>

#include <wx/wx.h>
#include <wx/checkbox.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/valnum.h>
#include <wx/dirdlg.h>

#include <common/MeshSettings.h>
#include <common/OmniFEMMessage.h>


/**
 * @class meshAdvanced
 * @author Phillip
 * @date 16/04/18
 * @file MeshAdvancedSettings.h
 * @brief This class handles all of the additional settings that the user can select or edit that should be
 * 			more hidden from the the main view. These settings apply directly to the mesh settings. This
 * 			class handles the selection of the different file formats to save the mesh in, the directory
 * 			location of the mesh saved files, the number of mesh passes, the llyod smoothing steps, and
 * 			the global mesh size factor setting.
 */
class meshAdvanced : public wxDialog
{
private:
	//! Pointer to the meshSettings. This is a local copy for ease of access
	meshSettings *p_meshSettings;
	
	//! Text control that is associated with the number of passes. THis would be the number of times GMSH re-meshes the geometry
	wxTextCtrl *p_passesTextCtrl = new wxTextCtrl();

	//! Text Box used to input the number of smoothing steps for the Blossom algorithm
	wxTextCtrl *p_llyodTextCtrl = new wxTextCtrl();

	//! Text box that is used to set the Global Mesh Factor Scaling number
	wxTextCtrl *p_factorTextCtrl = new wxTextCtrl();
	
	//! Text box used to indicate the local of the directory to save the mesh file to
	wxTextCtrl *p_meshFileDirectory = new wxTextCtrl();
	
	//! Check box used to indicate that the user wants to save the mesh as VTK file
	wxCheckBox *p_saveAsVTK = new wxCheckBox();
	
	//! Check box used to indicate that the user wants to save the mesh as BDF file
	wxCheckBox *p_saveAsBDF = new wxCheckBox();
	
	//! Check box used to indicate that the user wants to save the mesh as CELUM file
	wxCheckBox *p_saveAsCELUM = new wxCheckBox();
	
	//! Check box used to indicate that the user wants to save the mesh as CGNS file
	wxCheckBox *p_saveAsCGNS = new wxCheckBox();
	
	//! Check box used to indicate that the user wants to save the mesh as DIFFPACK file
	wxCheckBox *p_saveAsDIFFPACK = new wxCheckBox();
	
	//! Check box used to indicate that the user wants to save the mesh as Fourier file
	wxCheckBox *p_saveAsFourier = new wxCheckBox();
	
	//! Check box used to indicate that the user wants to save the mesh as GEO file
	wxCheckBox *p_saveAsGEO = new wxCheckBox();
	
	//! Check box used to indicate that the user wants to save the mesh as INP file
	wxCheckBox *p_SaveAsINP = new wxCheckBox();
	
	//! Check box used to indicate that the user wants to save the mesh as IR3 file
	wxCheckBox *p_saveAsIR3 = new wxCheckBox();
	
	//! Check box used to indicate that the user wants to save the mesh as MAIL file
	wxCheckBox *p_saveAsMAIL = new wxCheckBox();
	
	//! Check box used to indicate that the user wants to save the mesh as MESH file
	wxCheckBox *p_saveAsMESH = new wxCheckBox();
	
	//! Check box used to indicate that the user wants to save the mesh as P3D file
	wxCheckBox *p_saveAsP3D = new wxCheckBox();
	
	//! Check box used to indicate that the user wants to save the mesh as Patitioned Mesh file
	wxCheckBox *p_saveAsPatitionedMesh = new wxCheckBox();
	
	//! Check box used to indicate that the user wants to save the mesh as PLY2 file
	wxCheckBox *p_saveAsPLY2 = new wxCheckBox();
	
	//! Check box used to indicate that the user wants to save the mesh as STL file
	wxCheckBox *p_saveAsSTL = new wxCheckBox();
	
	//! Check box used to indicate that the user wants to save the mesh as SU2 file
	wxCheckBox *p_saveAsSU2 = new wxCheckBox();
	
	//! Check box used to indicate that the user wants to save the mesh as Tochnog file
	wxCheckBox *p_saveAsTochnog = new wxCheckBox();
	
	//! Check box used to indicate that the user wants to save the mesh as UNV file
	wxCheckBox *p_saveAsUNV = new wxCheckBox();
	
	//! Check box used to indicate that the user wants to save the mesh as VRML file
	wxCheckBox *p_saveAsVRML = new wxCheckBox();
	
	/**
	 * @brief Event procedure that is fired when the user needs to reset to default settings
	 * @param event Required arguement for event procedure functionality
	 */
	void onResetDefault(wxCommandEvent &event);
	
	/**
	 * @brief Event procedure that is fired when the user clicks the Browse button
	 * 			This will create a new window which allows the user to select the 
	 * 			directory to save the mesh files to
	 * @param event Required arguement for event procedure functionality
	 */
	void onBrowse(wxCommandEvent &event);
	
	/**
	 * @brief Event procedure that is fired when the user edits the mesh file directory text box
	 * 			This function will check to make sure that what the user inputs is a valid dir.
	 * 			If not, the simulator will display a message alerting the user. This event is only fired
	 * 			when the user presses Enter.
	 * @param event Required arguement for event procedure functionality
	 */
	void onTextEdit(wxCommandEvent &event);
public:

	/**
	 * @brief The construtor for the class
	 * @param par The parent window for the advanced setting window
	 * @param settings The mesh settings that will be edited
	 */
	meshAdvanced(wxWindow *par, meshSettings &settings);
	
	/**
	 * @brief Function that is called in order to "save" the settings that user
	 * 			has specified.
	 */
	void setSettings();

private:
	wxDECLARE_EVENT_TABLE();
};




#endif