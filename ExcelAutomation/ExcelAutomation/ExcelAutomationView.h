
// ExcelAutomationView.h : CExcelAutomationView Ŭ������ �������̽�
//

#pragma once


class CExcelAutomationView : public CFormView
{
protected: // serialization������ ��������ϴ�.
	CExcelAutomationView();
	DECLARE_DYNCREATE(CExcelAutomationView)

public:
#ifdef AFX_DESIGN_TIME
	enum{ IDD = IDD_EXCELAUTOMATION_FORM };
#endif

// Ư���Դϴ�.
public:
	CExcelAutomationDoc* GetDocument() const;

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
	virtual ~CExcelAutomationView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()
public:
	CString m_strProgramDir;

	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
};

#ifndef _DEBUG  // ExcelAutomationView.cpp�� ����� ����
inline CExcelAutomationDoc* CExcelAutomationView::GetDocument() const
   { return reinterpret_cast<CExcelAutomationDoc*>(m_pDocument); }
#endif

