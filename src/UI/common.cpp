/*
	This file will contain any code that is common across the UI. Specifically for the main frame
*/
#include "UI/OmniFEM.h"

wxBEGIN_EVENT_TABLE(OmniFEMMainFrame, wxFrame)
    /* This section is for the file menu */
    EVT_MENU(ID_New,   OmniFEMMainFrame::onNewFile)
    EVT_MENU(ID_Save, OmniFEMMainFrame::OnSave)
    EVT_MENU(ID_SaveAs, OmniFEMMainFrame::onSaveAs)
    
    /* This section is for the Edit menu */
    EVT_MENU(ID_Preferences, OmniFEMMainFrame::onPreferences)
	
	/* This section is for the View menu */
	EVT_MENU(ID_ViewResults, OmniFEMMainFrame::onViewResults)
	
	/* This section is for the Problem menu */
	EVT_MENU(ID_Precision, OmniFEMMainFrame::onPrecision)
	
	/*This section is for the mesh menu */
    EVT_MENU(ID_CreateMesh, OmniFEMMainFrame::onCreateMesh)
	EVT_MENU(ID_ShowMesh, OmniFEMMainFrame::onShowMesh)
	EVT_MENU(ID_DeleteMesh, OmniFEMMainFrame::onDeleteMesh)
	
    /* This section is for the Help menu */
	EVT_MENU(ID_Manual, OmniFEMMainFrame::onManual)
    EVT_MENU(ID_License, OmniFEMMainFrame::onLicense)
    EVT_MENU(wxID_ABOUT, OmniFEMMainFrame::OnAbout)
    
    /* Everything Else */
    EVT_MENU(wxID_EXIT,  OmniFEMMainFrame::OnExit)
    
wxEND_EVENT_TABLE()

wxIMPLEMENT_APP(OmniFEMApp);