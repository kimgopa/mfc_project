
// SquareExplicitDlg.h : header file
//

#pragma once


// CSquareExplicitDlg dialog
class CSquareExplicitDlg : public CDialogEx
{
// Construction
public:
	CSquareExplicitDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SQUAREEXPLICIT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	HINSTANCE m_hDll;

	double m_dInput;
	double m_dOutput;
	afx_msg void OnDestroy();
	afx_msg void OnEnChangeEditInput();
};
