/*
	This file will contain any code that is common across the UI. Specifically for the main frame
*/
#include "UI/OmniFEMFrame.h"

wxBEGIN_EVENT_TABLE(OmniFEMMainFrame, wxFrame)
	/**********************
	* Menu event Handling *
	***********************/
	
    /* This section is for the file menu */
    EVT_MENU(menubarID::ID_menubarNew,   OmniFEMMainFrame::onNewFile)
    EVT_MENU(menubarID::ID_menubarSave, OmniFEMMainFrame::OnSave)
    EVT_MENU(menubarID::ID_menubarSaveAs, OmniFEMMainFrame::onSaveAs)
	EVT_MENU(menubarID::ID_menubarOpen, OmniFEMMainFrame::onOpenFile)
    
    /* This section is for the Edit menu */
	EVT_MENU(menubarID::ID_menubarLUASCRIPT, OmniFEMMainFrame::onLuaRun)
    EVT_MENU(menubarID::ID_menubarPreferences, OmniFEMMainFrame::onPreferences)
	
	/* This section is for the View menu */
	EVT_MENU(menubarID::ID_menubarViewResults, OmniFEMMainFrame::onViewResults)
	
	/* This section is for the Problem menu */
	EVT_MENU(menubarID::ID_menubarPrecision, OmniFEMMainFrame::onPrecision)
	
	/*This section is for the mesh menu */
    EVT_MENU(menubarID::ID_menubarCreateMesh, OmniFEMMainFrame::onCreateMesh)
	EVT_MENU(menubarID::ID_menubarShowMesh, OmniFEMMainFrame::onShowMesh)
	EVT_MENU(menubarID::ID_menubarDeleteMesh, OmniFEMMainFrame::onDeleteMesh)
	
    /* This section is for the Help menu */
	EVT_MENU(menubarID::ID_menubarManual, OmniFEMMainFrame::onManual)
    EVT_MENU(menubarID::ID_menubarLicense, OmniFEMMainFrame::onLicense)
    EVT_MENU(wxID_ABOUT, OmniFEMMainFrame::OnAbout)
    
    /* Everything Else */
    EVT_MENU(wxID_EXIT,  OmniFEMMainFrame::OnExit)
	EVT_SIZE(OmniFEMMainFrame::onResize)
	
	/************************
	* Button Event Handling *
	*************************/
	
	EVT_BUTTON(buttonID::ID_buttonNew, OmniFEMMainFrame::onNewFile)
	EVT_BUTTON(buttonID::ID_buttonOpen, OmniFEMMainFrame::onOpenFile)
    EVT_BUTTON(buttonID::ID_buttonTwoDim, OmniFEMMainFrame::onTwoDimButton)
	EVT_BUTTON(buttonID::ID_buttonBack, OmniFEMMainFrame::onBackButton)
	EVT_BUTTON(buttonID::ID_buttonFinish, OmniFEMMainFrame::onFinishButton)
	
	/*************************
	* ToolBar Event Handling *
	**************************/	
	
	EVT_TOOL(toolbarID::ID_ToolBarNew, OmniFEMMainFrame::onNewFile)
	EVT_TOOL(toolbarID::ID_ToolBarOpen, OmniFEMMainFrame::onOpenFile)
	EVT_TOOL(toolbarID::ID_ToolBarSave, OmniFEMMainFrame::OnSave)
	
	/********
	* Other *
	*********/

	EVT_LISTBOX(comboListBoxID::ID_physicsProblems, OmniFEMMainFrame::physicsProblemComboBox)
    
wxEND_EVENT_TABLE()

wxIMPLEMENT_APP(OmniFEMApp);// This is where int main is located inside of