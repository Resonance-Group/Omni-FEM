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
	meshSettings *p_meshSettings;
	
	wxTextCtrl *p_passesTextCtrl = new wxTextCtrl();

	wxTextCtrl *p_llyodTextCtrl = new wxTextCtrl();

	wxTextCtrl *p_factorTextCtrl = new wxTextCtrl();
	
	wxTextCtrl *p_meshFileDirectory = new wxTextCtrl();
	
	wxCheckBox *p_saveAsVTK = new wxCheckBox();
	
	wxCheckBox *p_saveAsBDF = new wxCheckBox();
	
	wxCheckBox *p_saveAsCELUM = new wxCheckBox();
	
	wxCheckBox *p_saveAsCGNS = new wxCheckBox();
	
	wxCheckBox *p_saveAsDIFFPACK = new wxCheckBox();
	
	wxCheckBox *p_saveAsFourier = new wxCheckBox();
	
	wxCheckBox *p_saveAsGEO = new wxCheckBox();
	
	wxCheckBox *p_SaveAsINP = new wxCheckBox();
	
	wxCheckBox *p_saveAsIR3 = new wxCheckBox();
	
	wxCheckBox *p_saveAsMAIL = new wxCheckBox();
	
	wxCheckBox *p_saveAsMESH = new wxCheckBox();
	
	wxCheckBox *p_saveAsP3D = new wxCheckBox();
	
	wxCheckBox *p_saveAsPatitionedMesh = new wxCheckBox();
	
	wxCheckBox *p_saveAsPLY2 = new wxCheckBox();
	
	wxCheckBox *p_saveAsSTL = new wxCheckBox();
	
	wxCheckBox *p_saveAsSU2 = new wxCheckBox();
	
	wxCheckBox *p_saveAsTochnog = new wxCheckBox();
	
	wxCheckBox *p_saveAsUNV = new wxCheckBox();
	
	wxCheckBox *p_saveAsVRML = new wxCheckBox();
	
	void onResetDefault(wxCommandEvent &event);
	
	void onBrowse(wxCommandEvent &event);
	
	void onTextEdit(wxCommandEvent &event);
public:
	meshAdvanced(wxWindow *par, meshSettings &settings);
	
	void setSettings();

private:
	wxDECLARE_EVENT_TABLE();
};




#endif