#if !defined(AFX_DATASOCKET_H__DD8B4738_C2F2_4A7D_BA47_F43AA0571A53__INCLUDED_)
#define AFX_DATASOCKET_H__DD8B4738_C2F2_4A7D_BA47_F43AA0571A53__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DataSocket.h : header file
//


#define UM_DATARECEIVE (WM_USER+11)
class CData;

/////////////////////////////////////////////////////////////////////////////
// CDataSocket command target

class CDataSocket : public CSocket
{
// Attributes
public:
	void Init(CWnd *pWnd);
	void Send(CData *pData);
	void Receive(CData *pData);
	void operator << (CData &data);
	void operator >> (CData &data);
	void Flush();

	CArchive	*m_pArchiveIn;
	CArchive	*m_pArchiveOut;

// Operations
public:
	CDataSocket();
	virtual ~CDataSocket();

// Overrides
public:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDataSocket)
	public:
	virtual void OnReceive(int nErrorCode);
	virtual void OnClose(int nErrorCode);
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CDataSocket)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
	CWnd		*m_pWnd;
	CSocketFile *m_pFile;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DATASOCKET_H__DD8B4738_C2F2_4A7D_BA47_F43AA0571A53__INCLUDED_)
