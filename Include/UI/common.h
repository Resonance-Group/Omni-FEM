#ifndef COMMON_H_
#define COMMON_H_

#define LETTER_A 0x41
#define LETTER_B 0x42
#define LETTER_C 0x43
#define LETTER_D 0x44
#define LETTER_E 0x45
#define LETTER_e 0x65
#define LETTER_F 0x46
#define LETTER_G 0x47
#define LETTER_H 0x48
#define LETTER_I 0x49
#define LETTER_J 0x4A
#define LETTER_K 0x4B
#define LETTER_L 0x4C
#define LETTER_M 0x4D
#define LETTER_N 0x4E
#define LETTER_O 0x4F
#define LETTER_P 0x50
#define LETTER_Q 0x51
#define LETTER_R 0x52
#define LETTER_S 0x53
#define LETTER_T 0x54
#define LETTER_U 0x55
#define LETTER_V 0x56
#define LETTER_W 0x57
#define LETTER_X 0x58
#define LETTER_Y 0x59
#define LETTER_Z 0x5A


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