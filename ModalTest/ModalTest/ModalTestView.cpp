
// ModalTestView.cpp : implementation of the CModalTestView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "ModalTest.h"
#endif

#include "ModalTestDoc.h"
#include "ModalTestView.h"

#include "CModalDlg.h"
#include "CModelessDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CModalTestView

IMPLEMENT_DYNCREATE(CModalTestView, CFormView)

BEGIN_MESSAGE_MAP(CModalTestView, CFormView)
	ON_BN_CLICKED(IDC_BUTTON_MODAL, &CModalTestView::OnBnClickedButtonModal)
	ON_BN_CLICKED(IDC_BUTTON_MODELESS, &CModalTestView::OnBnClickedButtonModeless)
END_MESSAGE_MAP()

// CModalTestView construction/destruction

CModalTestView::CModalTestView() noexcept
	: CFormView(IDD_MODALTEST_FORM)
{
	m_pModelessDlg = NULL;

}

CModalTestView::~CModalTestView()
{
}

void CModalTestView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BOOL CModalTestView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFormView::PreCreateWindow(cs);
}

void CModalTestView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

}


// CModalTestView diagnostics

#ifdef _DEBUG
void CModalTestView::AssertValid() const
{
	CFormView::AssertValid();
}

void CModalTestView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CModalTestDoc* CModalTestView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CModalTestDoc)));
	return (CModalTestDoc*)m_pDocument;
}
#endif //_DEBUG


// CModalTestView message handlers


void CModalTestView::OnBnClickedButtonModal()
{
	CModalDlg dlg;
	dlg.DoModal();
}


void CModalTestView::OnBnClickedButtonModeless()
{
	if (m_pModelessDlg != NULL)
	{
		// 대화상자가 이미 출력되어 있는 경우 - 대화상자에 포커스를 줌
		m_pModelessDlg->SetFocus();
	}
	else
	{
		// 대화상자가 출력되어 있지 않은 경우 - 새로운 인스턴스를 생성 후 ShowWindow
		m_pModelessDlg = new CModelessDlg;
		m_pModelessDlg->Create(IDD_DIALOG_MODELESS, this);
		m_pModelessDlg->ShowWindow(SW_SHOW);
	}
}
