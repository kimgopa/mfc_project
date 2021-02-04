// CModalDlg.cpp : implementation file
//

#include "pch.h"
#include "ModalTest.h"
#include "CModalDlg.h"
#include "afxdialogex.h"


// CModalDlg dialog

IMPLEMENT_DYNAMIC(CModalDlg, CDialogEx)

CModalDlg::CModalDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_MODAL, pParent)
{

}

CModalDlg::~CModalDlg()
{
}

void CModalDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CModalDlg, CDialogEx)
END_MESSAGE_MAP()


// CModalDlg message handlers
