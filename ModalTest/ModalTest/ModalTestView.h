
// ModalTestView.h : interface of the CModalTestView class
//

#pragma once

class CModelessDlg;
class CModalTestView : public CFormView
{
protected: // create from serialization only
	CModalTestView() noexcept;
	DECLARE_DYNCREATE(CModalTestView)

public:
#ifdef AFX_DESIGN_TIME
	enum{ IDD = IDD_MODALTEST_FORM };
#endif

// Attributes
public:
	CModalTestDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct

// Implementation
public:
	virtual ~CModalTestView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

public:
	CModelessDlg *m_pModelessDlg;

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonModal();
	afx_msg void OnBnClickedButtonModeless();
};

#ifndef _DEBUG  // debug version in ModalTestView.cpp
inline CModalTestDoc* CModalTestView::GetDocument() const
   { return reinterpret_cast<CModalTestDoc*>(m_pDocument); }
#endif

