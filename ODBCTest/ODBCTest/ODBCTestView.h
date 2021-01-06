
// ODBCTestView.h : CODBCTestView 클래스의 인터페이스
//


#pragma once
#include "afxcmn.h"


class CODBCTestView : public CFormView
{
protected: // serialization에서만 만들어집니다.
	CODBCTestView();
	DECLARE_DYNCREATE(CODBCTestView)

public:
	enum{ IDD = IDD_ODBCTEST_FORM };

// 특성입니다.
public:
	CODBCTestDoc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual void OnInitialUpdate(); // 생성 후 처음 호출되었습니다.

// 구현입니다.
public:
	virtual ~CODBCTestView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
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

#ifndef _DEBUG  // ODBCTestView.cpp의 디버그 버전
inline CODBCTestDoc* CODBCTestView::GetDocument() const
   { return reinterpret_cast<CODBCTestDoc*>(m_pDocument); }
#endif

