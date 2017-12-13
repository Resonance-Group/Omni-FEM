#ifndef MESH_ADVANCED_SETTINGS_H_
#define MESH_ADVANCED_SETTINGS_H_

#include <string>

#include <wx/wx.h>
#include <wx/checkbox.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/valnum.h>

#include <common/MeshSettings.h>

class meshAdvanced : public wxDialog
{
private:
	meshSettings *p_meshSettings;
	
	void onResetDefault(wxCommandEvent &event);
public:
	meshAdvanced(wxWindow *par, meshSettings &settings);
	
	void setSettings();
};




#endif