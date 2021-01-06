
// ODBCTestView.h : CODBCTestView Ŭ������ �������̽�
//


#pragma once
#include "afxcmn.h"


class CODBCTestView : public CFormView
{
protected: // serialization������ ��������ϴ�.
	CODBCTestView();
	DECLARE_DYNCREATE(CODBCTestView)

public:
	enum{ IDD = IDD_ODBCTEST_FORM };

// Ư���Դϴ�.
public:
	CODBCTestDoc* GetDocument() const;

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.
	virtual void OnInitialUpdate(); // ���� �� ó�� ȣ��Ǿ����ϴ�.

// �����Դϴ�.
public:
	virtual ~CODBCTestView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_ctrlList;

public:
	CDatabase m_db;
	CRecordset *m_pRs;

	void SelectData();
	void InsertData();
	void UpdateData();
	void DeleteData();
	afx_msg void OnBnClickedButtonInsert();
	afx_msg void OnBnClickedButtonUpdate();
	afx_msg void OnBnClickedButtonDelete();
};

#ifndef _DEBUG  // ODBCTestView.cpp�� ����� ����
inline CODBCTestDoc* CODBCTestView::GetDocument() const
   { return reinterpret_cast<CODBCTestDoc*>(m_pDocument); }
#endif

