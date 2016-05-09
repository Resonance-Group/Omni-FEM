#ifndef COMMON_H_
#define COMMON_H_

/*	These defines are for the keyboard press event. These were obtained from the ASCII chart 
	at http://www.bibase.com/images/ascii.gif */
#define LETTER_A 0x41
#define LETTER_B 0x42
#define LETTER_C 0x43
#define LETTER_D 0x44
#define LETTER_E 0x45
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

#define LETTER_a 0x61
#define LETTER_b 0x62
#define LETTER_c 0x63
#define LETTER_d 0x64
#define LETTER_e 0x65
#define LETTER_f 0x66
#define LETTER_g 0x67
#define LETTER_h 0x68
#define LETTER_i 0x69
#define LETTER_j 0x6A
#define LETTER_k 0x6B
#define LETTER_l 0x6C
#define LETTER_m 0x6D
#define LETTER_n 0x6E
#define LETTER_o 0x6F
#define LETTER_p 0x70
#define LETTER_q 0x71
#define LETTER_r 0x72
#define LETTER_s 0x73
#define LETTER_t 0x74
#define LETTER_u 0x75
#define LETTER_v 0x76
#define LETTER_w 0x77
#define LETTER_x 0x78
#define LETTER_y 0x79
#define LETTER_z 0x7A

#define DEL_KEY 0x7F

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