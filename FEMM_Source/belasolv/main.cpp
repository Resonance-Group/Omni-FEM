//#include <StdAfx.h>
#include "StdAfx.h"
#include<stdio.h>
#include<math.h>
#include<string.h>
#include<afxtempl.h>
#include "belasolv.h"
#include "belasolvDlg.h"
#include "spars.h"
#include "mesh.h"
#include "FemmeDocCore.h"

/*

Belasolv is used to solve problems in the electostatic domain

*/

void old_main(void *inptr)
{
	CbelasolvDlg *TheView;
	CFemmeDocCore Doc;
	char PathName[256];
	CFileDialog *fname_dia, *test;
	char outstr[1024];
	int i;


	TheView = (CbelasolvDlg *)inptr;

	/*
		get the name of the file to be processed,
		either from argv or from the user
		argc indicates that FEMM can be opened from command line.
		If this is the case, then argc > 2
		If not, then execute code for UI
	*/
	if (__argc < 2)
	{
		// This creates a windows File dialog box. Refer to: https://msdn.microsoft.com/en-us/library/wh5hz49d.aspx
		fname_dia = new CFileDialog(
			TRUE,// By setting this to true, this tells the program to create a File Open Dialog
			"fem | * ",// This specifics the default file extension to be associated
			NULL,// Specifies the initial filename that appears in the FileName box, NULL does not create a name
			OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,/*	Flags that are used to customize dialog box: https://msdn.microsoft.com/en-us/library/ms646839.aspx
														These particular flags will Hide the read only check box
														The second will cause the save as dialog box to generate a message box if the file already exists
													*/
			"belaview datafile (*.fee) | *.fee; *.FEE | All Files (*.*) | *.*||",// Applies specific filters that will filter files when the open dialog box appears
			NULL// This line is a pointer to a parent or owner window
			);

		// This line is the function creates the dialog box in order for the user to browse for files and directories and enter a filename
		// The function will return IDCANCEL to indicate if the user clicked the CANCEL button
		if (fname_dia->DoModal() == IDCANCEL)
		{
			delete[] fname_dia;// Deletes the dialog box
			MsgBox("No file name!");
			exit(0);
		}

		/* This block is creating the path name from the filename */
		CString fname = fname_dia->GetPathName();// This function returns the full path of the file 
		fname = fname.Left(fname.GetLength() - 4);// Retunering substring of left most charaters
		strcpy(PathName, fname);

		delete[] fname_dia;
	}
	else
		strcpy(PathName, __argv[1]);

	/* Saves the variables in status variables */
	Doc.PathName = PathName;
	Doc.TheView = TheView;

	// load problem geometry and block labels. Everything in to preprocessor is loaded here 
	if (Doc.OnOpenDocument() != TRUE)
	{
		MsgBox("problem loading .fee file");
		exit(7);
	}

	// load mesh
	if (Doc.LoadMesh() != TRUE)
	{
		MsgBox("problem loading mesh");
		exit(2);
	}

	// label the dialog to report which problem is being solved
	char PaneText[256];
	char *ProbName;
	ProbName = PathName;

	for (i = 0; i < (int)strlen(PathName); i++)
		if (PathName[i] == '\\')
			ProbName = PathName + i;

	if (strlen(PathName) > 0)
	{
		ProbName++;
		sprintf(PaneText, "%s - belasolve", ProbName);// Copies ProbName into PaneText with formatting
	}

	while (!IsWindow(TheView->m_hWnd))
		Sleep(1);

	TheView->SetWindowText(PaneText);

	// renumber using Cuthill-McKee
	TheView->SetDlgItemText(IDC_STATUSWINDOW, "renumbering nodes");
	if (Doc.Cuthill() != TRUE)
	{
		MsgBox("problem renumbering nodes");
		exit(3);
	}

	// display details about the problem to be solved
	TheView->SetDlgItemText(IDC_STATUSWINDOW, "solving...");
	sprintf(outstr, "Problem Statistics:\n%i nodes\n%i elements\nPrecision: %3.2e\n",
		Doc.NumNodes, Doc.NumEls, Doc.Precision);

	TheView->SetDlgItemText(IDC_PROBSTATS, outstr);

	// initialize the problem, allocating the space required to solve it.

	CBigLinProb L;
	L.TheView = TheView;
	L.Precision = Doc.Precision;

	if (L.Create(Doc.NumNodes + Doc.NumCircProps, Doc.BandWidth) == FALSE)
	{
		MsgBox("couldn't allocate enough space for matrices");
		Doc.CleanUp();
		L.~CBigLinProb();
		exit(4);
	}

	// Create element matrices and solve the problem;
	if (Doc.AnalyzeProblem(L) == FALSE)
	{
		MsgBox("Couldn't solve the problem");
		Doc.CleanUp();
		L.~CBigLinProb();
		exit(5);
	}

	TheView->SetDlgItemText(IDC_STATUSWINDOW, "Problem solved");

	// now that we have results, write 'em to dist
	if (Doc.WriteResults(L) == FALSE)
	{
		MsgBox("couldn't write results to disk");
		Doc.CleanUp();
		L.~CBigLinProb();
		exit(6);
	}
	TheView->SetDlgItemText(IDC_STATUSWINDOW, "results written to disk");

	// make sure that everything is freed up to avoid memory leaks
	Doc.CleanUp();
	L.~CBigLinProb();
	exit(0);
}
