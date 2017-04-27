// csolv.h : main header file for the BELASOLV application
//

#include "StdAfx.h"

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

void old_main(void *inptr);

/////////////////////////////////////////////////////////////////////////////
// CcsolvApp:
// See csolv.cpp for the implementation of this class
//

// TODO: CWINAPP here.
class CcsolvApp : public CWinApp
{
public:
	/* The constructor and destructor */
	CcsolvApp();
	~CcsolvApp();

	// Overrides
		// ClassWizard generated virtual function overrides
		//{{AFX_VIRTUAL(CcsolvApp)
public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CcsolvApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG

	// TODO: look into removing this
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////
