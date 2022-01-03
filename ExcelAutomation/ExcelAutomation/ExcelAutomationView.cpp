
// ExcelAutomationView.cpp : CExcelAutomationView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
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

// CExcelAutomationView 생성/소멸

CExcelAutomationView::CExcelAutomationView()
	: CFormView(IDD_EXCELAUTOMATION_FORM)
{
	// TODO: 여기에 생성 코드를 추가합니다.

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
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CFormView::PreCreateWindow(cs);
}

void CExcelAutomationView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

	// 실행 파일 경로 얻기
	TCHAR szPath[_MAX_PATH + 1];
	GetModuleFileName(AfxGetApp()->m_hInstance, szPath, _MAX_PATH);
	CString strProgramDir = szPath;
	int nLen = strProgramDir.ReverseFind('\\');
	if (nLen > 0)
		m_strProgramDir = strProgramDir.Left(nLen);
}


// CExcelAutomationView 진단

#ifdef _DEBUG
void CExcelAutomationView::AssertValid() const
{
	CFormView::AssertValid();
}

void CExcelAutomationView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CExcelAutomationDoc* CExcelAutomationView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CExcelAutomationDoc)));
	return (CExcelAutomationDoc*)m_pDocument;
}
#endif //_DEBUG


// CExcelAutomationView 메시지 처리기


void CExcelAutomationView::OnBnClickedButton1()	// 엑셀 파일 열기, 쓰기, 저장
{
	CString strPath = m_strProgramDir + "\\test1.xlsx";

	CApplication excel_app;

	// 엑셀 시작
	if ( !excel_app.CreateDispatch(_T("Excel.Application")) )
	{
		AfxMessageBox(_T("Couldn't start Excel."));
		return;
	}
	else
	{
		excel_app.put_Visible(TRUE);
	}

	// workbook 생성
	excel_app.put_SheetsInNewWorkbook(1);

	CWorkbooks wbs;
	CWorkbook wb;

	COleVariant covTrue((short)TRUE);
	COleVariant covFlase((short)FALSE);
	COleVariant covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);

	// books 연결
	wbs.AttachDispatch(excel_app.get_Workbooks());
	// book 연결
	wb.AttachDispatch(wbs.Add(covOptional));

	// sheet 생성, 연결
	CWorksheets wss;
	wss = wb.get_Sheets();

	// sheet 생성, 연결 (1번 시트)
	CWorksheet ws;
	ws = wss.get_Item(COleVariant((short)1));

	// sheet 이름 변경
	ws.put_Name(_T("test sheet 1"));

	// range 생성, 연결
	CRange range;
	range.AttachDispatch(ws.get_Cells(), TRUE);

	// range 값 쓰기
	for (int i = 1; i < 11; i++)
	{
		CString strColumn;
		strColumn.Format(_T("COLUMN %d"), i);
		range.put_Item(COleVariant((long)1), COleVariant(long(i)), COleVariant(strColumn));
	}

	// 파일 저장
	COleVariant vtOpt((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
	wb.SaveAs(COleVariant(strPath), vtOpt, vtOpt, vtOpt, vtOpt, vtOpt, 0, vtOpt, vtOpt, vtOpt, vtOpt, vtOpt);

	// 연결 끊기
	range.ReleaseDispatch();
	ws.ReleaseDispatch();
	wss.ReleaseDispatch();
	wb.ReleaseDispatch();
	wbs.ReleaseDispatch();
	excel_app.Quit();
	excel_app.ReleaseDispatch();
}


void CExcelAutomationView::OnBnClickedButton2() // 엑셀 파일 쓰기, 저장
{
	CString strPath = m_strProgramDir + "\\test2.xlsx";

	CApplication excel_app;

	// 엑셀 시작
	if (!excel_app.CreateDispatch(_T("Excel.Application")))
	{
		AfxMessageBox(_T("Couldn't start Excel."));
		return;
	}

	// workbook 생성
	excel_app.put_SheetsInNewWorkbook(1);

	CWorkbooks wbs;
	CWorkbook wb;

	COleVariant covTrue((short)TRUE);
	COleVariant covFlase((short)FALSE);
	COleVariant covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);

	// books 연결
	wbs.AttachDispatch(excel_app.get_Workbooks());
	// book 연결
	wb.AttachDispatch(wbs.Add(covOptional));

	// sheet 생성, 연결
	CWorksheets wss;
	wss = wb.get_Sheets();

	// sheet 생성, 연결 (1번 시트)
	CWorksheet ws;
	ws = wss.get_Item(COleVariant((short)1));

	// sheet 이름 변경
	ws.put_Name(_T("test sheet 1"));

	// range 생성, 연결
	CRange range;
	range.AttachDispatch(ws.get_Cells(), TRUE);

	// range 값 쓰기
	for (int i = 1; i < 11; i++)
	{
		CString strRow;
		strRow.Format(_T("ROW %d"), i);
		range.put_Item(COleVariant((long)i), COleVariant(long(1)), COleVariant(strRow));
	}

	// 파일 저장
	COleVariant vtOpt((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
	wb.SaveAs(COleVariant(strPath), vtOpt, vtOpt, vtOpt, vtOpt, vtOpt, 0, vtOpt, vtOpt, vtOpt, vtOpt, vtOpt);

	// 연결 끊기
	range.ReleaseDispatch();
	ws.ReleaseDispatch();
	wss.ReleaseDispatch();
	wb.ReleaseDispatch();
	wbs.ReleaseDispatch();
	excel_app.Quit();
	excel_app.ReleaseDispatch();
}


void CExcelAutomationView::OnBnClickedButton3() // 엑셀 파일 비밀번호 저장
{
	CString strPath = m_strProgramDir + "\\test3.xlsx";

	CApplication excel_app;

	// 엑셀 시작
	if (!excel_app.CreateDispatch(_T("Excel.Application")))
	{
		AfxMessageBox(_T("Couldn't start Excel."));
		return;
	}
	else
	{
		excel_app.put_Visible(FALSE);
	}

	// workbook 생성
	excel_app.put_SheetsInNewWorkbook(1);

	CWorkbooks wbs;
	CWorkbook wb;

	COleVariant covTrue((short)TRUE);
	COleVariant covFlase((short)FALSE);
	COleVariant covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);

	// books 연결
	wbs.AttachDispatch(excel_app.get_Workbooks());
	// book 연결
	wb.AttachDispatch(wbs.Add(covOptional));

	// sheet 생성, 연결
	CWorksheets wss;
	wss = wb.get_Sheets();

	// sheet 생성, 연결 (1번 시트)
	CWorksheet ws;
	ws = wss.get_Item(COleVariant((short)1));

	// sheet 이름 변경
	ws.put_Name(_T("test sheet 1"));

	// range 생성, 연결
	CRange range;
	range.AttachDispatch(ws.get_Cells(), TRUE);

	// range 값 쓰기
	for (int i = 1; i < 11; i++)
	{
		CString strRow;
		strRow.Format(_T("ROW %d"), i);
		range.put_Item(COleVariant((long)i), COleVariant(long(1)), COleVariant(strRow));
	}

	// 파일 저장
	COleVariant vtOpt((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
	wb.SaveAs(COleVariant(strPath), vtOpt, COleVariant(_T("1234")), vtOpt, vtOpt, vtOpt, 0, vtOpt, vtOpt, vtOpt, vtOpt, vtOpt);

	// 연결 끊기
	range.ReleaseDispatch();
	ws.ReleaseDispatch();
	wss.ReleaseDispatch();
	wb.ReleaseDispatch();
	wbs.ReleaseDispatch();
	excel_app.Quit();
	excel_app.ReleaseDispatch();
}
