// wintriangleDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CWintriangleDlg dialog

class CWintriangleDlg : public CDialog
{
// Construction
public:
	CWintriangleDlg(CWnd* pParent = NULL);	// standard constructor
	void dlgprintf(PSTR sz,...);

// Dialog Data
	//{{AFX_DATA(CWintriangleDlg)
	enum { IDD = IDD_WINTRIANGLE_DIALOG };
	CRichEditCtrl	m_infowindow;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWintriangleDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CWintriangleDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
