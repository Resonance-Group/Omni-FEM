#ifndef COMMON_H_
#define COMMON_H_

//! Enum for the menus of the menu bar
enum menubarID
{
    ID_menubarNew = 1,
    ID_menubarSave = 2,
    ID_menubarSaveAs = 3,
    ID_menubarPreferences = 4,
    ID_menubarManual = 5,
    ID_menubarLicense = 6,
	ID_menubarViewResults = 7,
	ID_menubarCreateMesh = 9,
	ID_menubarShowMesh = 10,
	ID_menubarDeleteMesh = 11,
	ID_menubarPrecision = 12,
	ID_menubarOpen = 13,
	ID_menubarLUASCRIPT = 14
};



//! Enum for the tool bar
enum toolbarID
{
	ID_ToolBarNew = 1,
	ID_ToolBarOpen = 2,
	ID_ToolBarSave = 3
};



//! Enum for the buttons
enum buttonID
{
	ID_buttonTwoDim = 1,
	ID_buttonBack = 2,
	ID_buttonNew = 3,
	ID_buttonOpen = 4,
	ID_buttonFinish = 5
};



//! Enums for comboboxs
enum comboListBoxID
{
	ID_physicsProblems = 1
};



//! These enums are for the different panels
enum panelID
{
	ID_initialCreation = 0,
	ID_dimSelectFrame = 1,
	ID_probSelectPanel = 2,
	ID_probDefiningPanel = 3,
	ID_viewResultsPanel = 4,
	ID_geometryBuilder = 5,
	ID_settings = 6,
	ID_modelBuilderTree = 7,
	ID_status = 8
};

#endif