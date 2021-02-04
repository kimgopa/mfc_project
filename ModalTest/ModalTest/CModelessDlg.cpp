// CModelessDlg.cpp : implementation file
//

#include "pch.h"
#include "ModalTest.h"
#include "CModelessDlg.h"
#include "afxdialogex.h"

#include "ModalTestDoc.h"
#include "ModalTestView.h"

// CModelessDlg dialog

IMPLEMENT_DYNAMIC(CModelessDlg, CDialogEx)

CModelessDlg::CModelessDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_MODELESS, pParent)
{

}

CModelessDlg::~CModelessDlg()
{
}

void CModelessDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CModelessDlg, CDialogEx)
	ON_BN_CLICKED(IDCANCEL, &CModelessDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CModelessDlg message handlers


void CModelessDlg::OnBnClickedCancel()
{
	DestroyWindow();
}


void CModelessDlg::PostNcDestroy()
{
	((CModalTestView *)AfxGetMainWnd())->m_pModelessDlg = NULL;
	delete this;

	CDialogEx::PostNcDestroy();
}
