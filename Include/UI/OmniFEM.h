#ifndef OMNIFEM_H_
#define OMNIFEM_H_

#pragma once

#include <wx/wx.h>
#include <wx/aboutdlg.h>


class OmniFEMApp : public wxApp
{
    public:
        virtual bool OnInit();
};



class OmniFEMMainFrame : public wxFrame
{
public:
    OmniFEMMainFrame(const wxString &title, const wxPoint &pos, const wxSize &size);
private:
    /* This section is for the File menu */
    void onNewFile(wxCommandEvent &event);
    void OnSave(wxCommandEvent &event);
    void onSaveAs(wxCommandEvent &event);
    
    /* This section is for the Edit menu */
    void onPreferences(wxCommandEvent &event);
	
	/* This section is for the View Menu */
	void onViewResults(wxCommandEvent &event);
	
	/* This section is for the Problem Menu */
	void onPrecision(wxCommandEvent &event);
	
	/* This section is for the Mesh menu */
	void onCreateMesh(wxCommandEvent &event);
	void onShowMesh(wxCommandEvent &event);
	void onDeleteMesh(wxCommandEvent &event);
    
    /* This section is for the Help menu */
    void onManual(wxCommandEvent &event);
    void onLicense(wxCommandEvent &event);
    void OnAbout(wxCommandEvent &event);
    
    void OnExit(wxCommandEvent &event);
    wxDECLARE_EVENT_TABLE();
};


/* Enum for the menus of the menu bar */
enum
{
    ID_New = 1,
    ID_Save = 2,
    ID_SaveAs = 3,
    ID_Preferences = 4,
    ID_Manual = 5,
    ID_License = 6,
	ID_ViewResults = 7,
	ID_CreateMesh = 9,
	ID_ShowMesh = 10,
	ID_DeleteMesh = 11,
	ID_Precision = 12
};






#endif /* OMNIFEM_H_ */
