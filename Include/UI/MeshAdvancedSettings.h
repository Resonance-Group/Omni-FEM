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