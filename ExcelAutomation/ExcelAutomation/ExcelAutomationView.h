
// ExcelAutomationView.h : CExcelAutomationView 클래스의 인터페이스
//

#pragma once


class CExcelAutomationView : public CFormView
{
protected: // serialization에서만 만들어집니다.
	CExcelAutomationView();
	DECLARE_DYNCREATE(CExcelAutomationView)

public:
#ifdef AFX_DESIGN_TIME
	enum{ IDD = IDD_EXCELAUTOMATION_FORM };
#endif

// 특성입니다.
public:
	CExcelAutomationDoc* GetDocument() const;

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
	virtual ~CExcelAutomationView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	CString m_strProgramDir;

	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
};

#ifndef _DEBUG  // ExcelAutomationView.cpp의 디버그 버전
inline CExcelAutomationDoc* CExcelAutomationView::GetDocument() const
   { return reinterpret_cast<CExcelAutomationDoc*>(m_pDocument); }
#endif

