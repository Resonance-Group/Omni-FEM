/*
	This file will contain any code that is common across the UI. Specifically for the main frame
*/
#include "UI/OmniFEMFrame.h"

wxBEGIN_EVENT_TABLE(OmniFEMMainFrame, wxFrame)
	/**********************
	* Menu event Handling *
	***********************/
	
    /* This section is for the file menu */
    EVT_MENU(ID_New,   OmniFEMMainFrame::onNewFile)
    EVT_MENU(ID_Save, OmniFEMMainFrame::OnSave)
    EVT_MENU(ID_SaveAs, OmniFEMMainFrame::onSaveAs)
	EVT_MENU(ID_Open, OmniFEMMainFrame::onOpenFile)
    
    /* This section is for the Edit menu */
	EVT_MENU(ID_LUASCRIPT, OmniFEMMainFrame::onLuaRun)
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
	
	EVT_SIZE(OmniFEMMainFrame::onResize)
	
	/************************
	* Button Event Handling *
	*************************/
	EVT_BUTTON(ID_New, OmniFEMMainFrame::onNewFile)
	EVT_BUTTON(ID_Open, OmniFEMMainFrame::onOpenFile)
    EVT_BUTTON(ID_TwoDim, OmniFEMMainFrame::onTwoDimButton)
	EVT_BUTTON(ID_BACK, OmniFEMMainFrame::onBackButton)
    
wxEND_EVENT_TABLE()

wxIMPLEMENT_APP(OmniFEMApp);// This is where int main is located inside of