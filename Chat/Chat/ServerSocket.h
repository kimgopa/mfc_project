#if !defined(AFX_SERVERSOCKET_H__C33E76A0_1957_42F1_8202_3B5DD3C9C380__INCLUDED_)
#define AFX_SERVERSOCKET_H__C33E76A0_1957_42F1_8202_3B5DD3C9C380__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ServerSocket.h : header file
//


#define UM_ACCEPT (WM_USER+10)

/////////////////////////////////////////////////////////////////////////////
// CServerSocket command target

class CServerSocket : public CSocket
{
// Attributes
public:
	void Init(CWnd *pWnd, int nPortNum);

// Operations
public:
	CServerSocket();
	virtual ~CServerSocket();

// Overrides
public:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CServerSocket)
	public:
	virtual void OnAccept(int nErrorCode);
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CServerSocket)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
	CWnd *m_pWnd;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SERVERSOCKET_H__C33E76A0_1957_42F1_8202_3B5DD3C9C380__INCLUDED_)
