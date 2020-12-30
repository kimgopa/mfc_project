#if !defined(AFX_DATA_H__98BA7ABB_2D49_49AA_9F38_6BCB606E3839__INCLUDED_)
#define AFX_DATA_H__98BA7ABB_2D49_49AA_9F38_6BCB606E3839__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Data.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// CData command target

class CData : public CObject
{
// Attributes
public:

// Operations
public:
	CData();
	virtual ~CData();

	virtual void Serialize(CArchive &ar);

	CString m_strData;	// 텍스트 데이터만 전송하므로

// Overrides
public:

// Implementation
protected:
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DATA_H__98BA7ABB_2D49_49AA_9F38_6BCB606E3839__INCLUDED_)
