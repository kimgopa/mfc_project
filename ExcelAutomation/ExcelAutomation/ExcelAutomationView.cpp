
// ExcelAutomationView.cpp : CExcelAutomationView Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "ExcelAutomation.h"
#endif

// ======= excel automation class =======
#include "CApplication.h"
#include "CRange.h"
#include "CWorkbook.h"
#include "CWorkbooks.h"
#include "CWorksheet.h"
#include "CWorksheets.h"
// ======================================

#include "ExcelAutomationDoc.h"
#include "ExcelAutomationView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CExcelAutomationView

IMPLEMENT_DYNCREATE(CExcelAutomationView, CFormView)

BEGIN_MESSAGE_MAP(CExcelAutomationView, CFormView)
	ON_BN_CLICKED(IDC_BUTTON1, &CExcelAutomationView::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CExcelAutomationView::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CExcelAutomationView::OnBnClickedButton3)
END_MESSAGE_MAP()

// CExcelAutomationView ����/�Ҹ�

CExcelAutomationView::CExcelAutomationView()
	: CFormView(IDD_EXCELAUTOMATION_FORM)
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.

}

CExcelAutomationView::~CExcelAutomationView()
{
}

void CExcelAutomationView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BOOL CExcelAutomationView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CFormView::PreCreateWindow(cs);
}

void CExcelAutomationView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

	// ���� ���� ��� ���
	TCHAR szPath[_MAX_PATH + 1];
	GetModuleFileName(AfxGetApp()->m_hInstance, szPath, _MAX_PATH);
	CString strProgramDir = szPath;
	int nLen = strProgramDir.ReverseFind('\\');
	if (nLen > 0)
		m_strProgramDir = strProgramDir.Left(nLen);
}


// CExcelAutomationView ����

#ifdef _DEBUG
void CExcelAutomationView::AssertValid() const
{
	CFormView::AssertValid();
}

void CExcelAutomationView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CExcelAutomationDoc* CExcelAutomationView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CExcelAutomationDoc)));
	return (CExcelAutomationDoc*)m_pDocument;
}
#endif //_DEBUG


// CExcelAutomationView �޽��� ó����


void CExcelAutomationView::OnBnClickedButton1()	// ���� ���� ����, ����, ����
{
	CString strPath = m_strProgramDir + "\\test1.xlsx";

	CApplication excel_app;

	// ���� ����
	if ( !excel_app.CreateDispatch(_T("Excel.Application")) )
	{
		AfxMessageBox(_T("Couldn't start Excel."));
		return;
	}
	else
	{
		excel_app.put_Visible(TRUE);
	}

	// workbook ����
	excel_app.put_SheetsInNewWorkbook(1);

	CWorkbooks wbs;
	CWorkbook wb;

	COleVariant covTrue((short)TRUE);
	COleVariant covFlase((short)FALSE);
	COleVariant covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);

	// books ����
	wbs.AttachDispatch(excel_app.get_Workbooks());
	// book ����
	wb.AttachDispatch(wbs.Add(covOptional));

	// sheet ����, ����
	CWorksheets wss;
	wss = wb.get_Sheets();

	// sheet ����, ���� (1�� ��Ʈ)
	CWorksheet ws;
	ws = wss.get_Item(COleVariant((short)1));

	// sheet �̸� ����
	ws.put_Name(_T("test sheet 1"));

	// range ����, ����
	CRange range;
	range.AttachDispatch(ws.get_Cells(), TRUE);

	// range �� ����
	for (int i = 1; i < 11; i++)
	{
		CString strColumn;
		strColumn.Format(_T("COLUMN %d"), i);
		range.put_Item(COleVariant((long)1), COleVariant(long(i)), COleVariant(strColumn));
	}

	// ���� ����
	COleVariant vtOpt((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
	wb.SaveAs(COleVariant(strPath), vtOpt, vtOpt, vtOpt, vtOpt, vtOpt, 0, vtOpt, vtOpt, vtOpt, vtOpt, vtOpt);

	// ���� ����
	range.ReleaseDispatch();
	ws.ReleaseDispatch();
	wss.ReleaseDispatch();
	wb.ReleaseDispatch();
	wbs.ReleaseDispatch();
	excel_app.Quit();
	excel_app.ReleaseDispatch();
}


void CExcelAutomationView::OnBnClickedButton2() // ���� ���� ����, ����
{
	CString strPath = m_strProgramDir + "\\test2.xlsx";

	CApplication excel_app;

	// ���� ����
	if (!excel_app.CreateDispatch(_T("Excel.Application")))
	{
		AfxMessageBox(_T("Couldn't start Excel."));
		return;
	}

	// workbook ����
	excel_app.put_SheetsInNewWorkbook(1);

	CWorkbooks wbs;
	CWorkbook wb;

	COleVariant covTrue((short)TRUE);
	COleVariant covFlase((short)FALSE);
	COleVariant covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);

	// books ����
	wbs.AttachDispatch(excel_app.get_Workbooks());
	// book ����
	wb.AttachDispatch(wbs.Add(covOptional));

	// sheet ����, ����
	CWorksheets wss;
	wss = wb.get_Sheets();

	// sheet ����, ���� (1�� ��Ʈ)
	CWorksheet ws;
	ws = wss.get_Item(COleVariant((short)1));

	// sheet �̸� ����
	ws.put_Name(_T("test sheet 1"));

	// range ����, ����
	CRange range;
	range.AttachDispatch(ws.get_Cells(), TRUE);

	// range �� ����
	for (int i = 1; i < 11; i++)
	{
		CString strRow;
		strRow.Format(_T("ROW %d"), i);
		range.put_Item(COleVariant((long)i), COleVariant(long(1)), COleVariant(strRow));
	}

	// ���� ����
	COleVariant vtOpt((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
	wb.SaveAs(COleVariant(strPath), vtOpt, vtOpt, vtOpt, vtOpt, vtOpt, 0, vtOpt, vtOpt, vtOpt, vtOpt, vtOpt);

	// ���� ����
	range.ReleaseDispatch();
	ws.ReleaseDispatch();
	wss.ReleaseDispatch();
	wb.ReleaseDispatch();
	wbs.ReleaseDispatch();
	excel_app.Quit();
	excel_app.ReleaseDispatch();
}


void CExcelAutomationView::OnBnClickedButton3() // ���� ���� ��й�ȣ ����
{
	CString strPath = m_strProgramDir + "\\test3.xlsx";

	CApplication excel_app;

	// ���� ����
	if (!excel_app.CreateDispatch(_T("Excel.Application")))
	{
		AfxMessageBox(_T("Couldn't start Excel."));
		return;
	}
	else
	{
		excel_app.put_Visible(FALSE);
	}

	// workbook ����
	excel_app.put_SheetsInNewWorkbook(1);

	CWorkbooks wbs;
	CWorkbook wb;

	COleVariant covTrue((short)TRUE);
	COleVariant covFlase((short)FALSE);
	COleVariant covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);

	// books ����
	wbs.AttachDispatch(excel_app.get_Workbooks());
	// book ����
	wb.AttachDispatch(wbs.Add(covOptional));

	// sheet ����, ����
	CWorksheets wss;
	wss = wb.get_Sheets();

	// sheet ����, ���� (1�� ��Ʈ)
	CWorksheet ws;
	ws = wss.get_Item(COleVariant((short)1));

	// sheet �̸� ����
	ws.put_Name(_T("test sheet 1"));

	// range ����, ����
	CRange range;
	range.AttachDispatch(ws.get_Cells(), TRUE);

	// range �� ����
	for (int i = 1; i < 11; i++)
	{
		CString strRow;
		strRow.Format(_T("ROW %d"), i);
		range.put_Item(COleVariant((long)i), COleVariant(long(1)), COleVariant(strRow));
	}

	// ���� ����
	COleVariant vtOpt((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
	wb.SaveAs(COleVariant(strPath), vtOpt, COleVariant(_T("1234")), vtOpt, vtOpt, vtOpt, 0, vtOpt, vtOpt, vtOpt, vtOpt, vtOpt);

	// ���� ����
	range.ReleaseDispatch();
	ws.ReleaseDispatch();
	wss.ReleaseDispatch();
	wb.ReleaseDispatch();
	wbs.ReleaseDispatch();
	excel_app.Quit();
	excel_app.ReleaseDispatch();
}
