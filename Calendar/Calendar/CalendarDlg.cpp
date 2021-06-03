
// CalendarDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "Calendar.h"
#include "CalendarDlg.h"
#include "afxdialogex.h"

#include <atltime.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define THIS_LISTBOX_ID			10001
#define BEFORE_LISTBOX_ID		11001
#define NEXT_LISTBOX_ID			12001
#define WEEK_STATIC_ID			13001

#define DAY_LIST_START_X		0
#define DAY_LIST_START_Y		70
#define DAY_LIST_WIDTH			100
#define DAY_LIST_HEIGHT			100

#define IDC_MONTH_STATIC		1001
#define IDC_TODAY_BTN			1002
#define IDC_MONTH_BEFORE_BTN	1003
#define IDC_MONTH_NEXT_BTN		1004

// CCalendarDlg dialog



CCalendarDlg::CCalendarDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_CALENDAR_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_bInit = FALSE;

	m_nBeforeDayListBox = 0;
	m_nDayListBox = 0;
	m_nNextDayListBox = 0;

	m_today_hbr.CreateSolidBrush(RGB(246, 246, 246));
}

void CCalendarDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CCalendarDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	ON_WM_CTLCOLOR()
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_TODAY_BTN, &CCalendarDlg::OnBnClickedTodayButton)
	ON_BN_CLICKED(IDC_MONTH_BEFORE_BTN, &CCalendarDlg::OnBnClickedBeforeMonthButton)
	ON_BN_CLICKED(IDC_MONTH_NEXT_BTN, &CCalendarDlg::OnBnClickedNextMonthButton)
END_MESSAGE_MAP()


// CCalendarDlg message handlers

BOOL CCalendarDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	MoveWindow(0, 0, 1024, 768);
	GetToday();
	InitMonthlyCalendar();
	DrawMonthlyCalendar();

	m_bInit = TRUE;

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CCalendarDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CCalendarDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CCalendarDlg::GetToday()
{
	//현재 날짜 구하기 
	CTime time = CTime::GetTickCount();
	calendarDate.year = time.GetYear();
	calendarDate.month = time.GetMonth();
	calendarDate.day = time.GetDay();
	calendarDate.week = time.GetDayOfWeek();//요일반환 1 = 일요일, 2 = 월요일, 7 = 토요일

	/* 현재달 시작일 구하기 */
	//CTime(년, 월, 일, 시, 분, 초);
	CTime firstDay = CTime(calendarDate.year, calendarDate.month, 1, 9, 0, 0);
	calendarDate.firstday_week = firstDay.GetDayOfWeek();

	/* 이전 마지막 일자 구하기 */
	//하루 24시간의 tick값 CTimeSpan(일, 시간, 분, 초);  
	CTimeSpan span(1, 0, 0, 0);

	//그냥 86400초 빼도 된다.  
	//int oneDay = 24 * 60 * 60;   

	//시작일에서 하루 빼기  
	firstDay -= span;

	calendarDate.beforelast_year = firstDay.GetYear();
	calendarDate.beforelast_month = firstDay.GetMonth();
	calendarDate.beforelast_day = firstDay.GetDay();

	/* 현재달 마지막일 구하기 */
	//다음달 시작일 구함  
	CTime cTimelastDay = CTime(calendarDate.year, calendarDate.month + 1, 1, 9, 0, 0);
	calendarDate.nextfirst_year = cTimelastDay.GetYear();
	calendarDate.nextfirst_month = cTimelastDay.GetMonth();

	cTimelastDay -= span;

	calendarDate.lastday_day = cTimelastDay.GetDay();
	calendarDate.lastday_week = cTimelastDay.GetDayOfWeek();

	todayDate = calendarDate;
}

void CCalendarDlg::GetDate()
{
	//현재 날짜 구하기 
	CTime time = CTime::GetTickCount();
	int year = time.GetYear();
	int month = time.GetMonth();
	int day = time.GetDay();
	int week = time.GetDayOfWeek();//요일반환 1 = 일요일, 2 = 월요일, 7 = 토요일

	/* 현재달 시작일 구하기 */
	//CTime(년, 월, 일, 시, 분, 초);
	CTime firstDay = CTime(year, month, 1, 9, 0, 0);
	int firstday_week = firstDay.GetDayOfWeek();

	/* 이전 마지막 일자 구하기 */
	//하루 24시간의 tick값 CTimeSpan(일, 시간, 분, 초);  
	CTimeSpan span(1, 0, 0, 0);

	//그냥 86400초 빼도 된다.  
	//int oneDay = 24 * 60 * 60;   

	//시작일에서 하루 빼기  
	firstDay -= span;

	int beforeday_year = firstDay.GetYear();
	int beforeday_month = firstDay.GetMonth();
	int beforeday_day = firstDay.GetDay();
	int beforeWeek = firstDay.GetDayOfWeek();

	/* 현재달 마지막일 구하기 */
	//다음달 시작일 구함  
	CTime cTimelastDay = CTime(year, month + 1, 1, 9, 0, 0);
	int next_year = cTimelastDay.GetYear();
	int next_month = cTimelastDay.GetMonth();

	cTimelastDay -= span;

	int lastYear = cTimelastDay.GetYear();
	int lastMonth = cTimelastDay.GetMonth();
	int lastday_day = cTimelastDay.GetDay();
	int lastday_week = cTimelastDay.GetDayOfWeek();
}

void CCalendarDlg::GetDate(int nYear, int nMonth)
{
	calendarDate.year = nYear;
	calendarDate.month = nMonth;
	calendarDate.day = 0;
	calendarDate.week = 0;

	/* 현재달 시작일 구하기 */
	//CTime(년, 월, 일, 시, 분, 초);
	CTime firstDay = CTime(calendarDate.year, calendarDate.month, 1, 9, 0, 0);
	calendarDate.firstday_week = firstDay.GetDayOfWeek();

	/* 이전 마지막 일자 구하기 */
	//하루 24시간의 tick값 CTimeSpan(일, 시간, 분, 초);  
	CTimeSpan span(1, 0, 0, 0);

	//그냥 86400초 빼도 된다.  
	//int oneDay = 24 * 60 * 60;   

	//시작일에서 하루 빼기  
	firstDay -= span;

	calendarDate.beforelast_year = firstDay.GetYear();
	calendarDate.beforelast_month = firstDay.GetMonth();
	calendarDate.beforelast_day = firstDay.GetDay();

	/* 현재달 마지막일 구하기 */
	//다음달 시작일 구함
	CTime cTimelastDay;
	if (calendarDate.month == 12)
		cTimelastDay = CTime(calendarDate.year + 1, 1, 1, 9, 0, 0);
	else
		cTimelastDay = CTime(calendarDate.year, calendarDate.month + 1, 1, 9, 0, 0);
	calendarDate.nextfirst_year = cTimelastDay.GetYear();
	calendarDate.nextfirst_month = cTimelastDay.GetMonth();

	cTimelastDay -= span;

	calendarDate.lastday_day = cTimelastDay.GetDay();
	calendarDate.lastday_week = cTimelastDay.GetDayOfWeek();
}

void CCalendarDlg::InitMonthlyCalendar()
{
	CRect rectDlg;
	this->GetWindowRect(rectDlg);

	// month
	// get system font
//	LOGFONT lf;
//	CFont *pFont = CFont::FromHandle((HFONT)GetStockObject(DEFAULT_GUI_FONT));
//	pFont->GetLogFont(&lf);

	CFont *pMonthFont = new CFont();
	pMonthFont->CreateFont(
		30,						// 글자높이
		10,						// 글자너비
		0,						// 출력각도
		0,						// 기준 선에서의각도
		FW_NORMAL,				// 글자굵기
		FALSE,					// Italic 적용여부
		FALSE,					// 밑줄적용여부
		FALSE,					// 취소선적용여부
		DEFAULT_CHARSET,		// 문자셋종류
		OUT_DEFAULT_PRECIS,		// 출력정밀도
		CLIP_DEFAULT_PRECIS,	// 클리핑정밀도
		DEFAULT_QUALITY,		// 출력문자품질
		DEFAULT_PITCH,			// 글꼴Pitch
		_T("맑은 고딕")			// 글꼴
	);

	m_pMonthStatic = new CStatic();
	m_pMonthStatic->Create(_T(""), WS_CHILD | WS_VISIBLE | SS_NOTIFY | SS_CENTER | SS_CENTERIMAGE, CRect(rectDlg.Width() / 2 - 100, 0, rectDlg.Width() / 2 + 100, 50), this);
	m_pMonthStatic->SetFont(pMonthFont);

	// move to today button
	m_pTodayBtn = new CButton();
	m_pTodayBtn->Create(_T("오늘"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect((rectDlg.Width() - DAY_LIST_WIDTH * 7) / 2, 10, (rectDlg.Width() - DAY_LIST_WIDTH * 7) / 2 + 50, 40), this, IDC_TODAY_BTN);
	m_pTodayBtn->SetFont(GetFont());

	// month button
	m_pBeforeMonthBtn = new CButton();
	m_pBeforeMonthBtn->Create(_T("<<"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(rectDlg.Width() / 2 - 140, 10, rectDlg.Width() / 2 - 110, 40), this, IDC_MONTH_BEFORE_BTN);
	m_pBeforeMonthBtn->SetFont(GetFont());

	m_pNextMonthBtn = new CButton();
	m_pNextMonthBtn->Create(_T(">>"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(rectDlg.Width() / 2 + 110, 10, rectDlg.Width() / 2 + 140, 40), this, IDC_MONTH_NEXT_BTN);
	m_pNextMonthBtn->SetFont(GetFont());

	// week
	CString strWeek[7] = { _T("일"), _T("월"), _T("화"), _T("수"), _T("목"), _T("금"),_T("토") };

	CRect rectStatic;
	rectStatic.SetRect((rectDlg.Width() - DAY_LIST_WIDTH * 7) / 2, 50, (rectDlg.Width() - DAY_LIST_WIDTH * 7) / 2 + DAY_LIST_WIDTH, 70);

	for (int i = 0; i < 7; i++)
	{
		m_pWeekStatic[i] = new CStatic();
		m_pWeekStatic[i]->Create(strWeek[i], WS_CHILD | WS_VISIBLE | SS_NOTIFY | SS_CENTER | SS_CENTERIMAGE, rectStatic, this, WEEK_STATIC_ID + i);
		m_pWeekStatic[i]->SetFont(GetFont());
		rectStatic.MoveToXY((rectDlg.Width() - DAY_LIST_WIDTH * 7) / 2 + (i + 1) * DAY_LIST_WIDTH, 50);
	}
}

void CCalendarDlg::DrawMonthlyCalendar()
{
	CRect rectDlg;
	this->GetWindowRect(rectDlg);

	// month
	CString strMonth;
	strMonth.Format(_T("%d년 %d월"), calendarDate.year, calendarDate.month);
	m_pMonthStatic->SetWindowTextW(strMonth);

	// day
	DeleteDayListBox();

	m_pBeforeDayListBox = new CListBox * [calendarDate.firstday_week - 1];
	m_pDayListBox = new CListBox * [calendarDate.lastday_day];
	m_pNextDayListBox = new CListBox * [8 - calendarDate.lastday_week];

	CRect rectList;
	rectList.SetRect((rectDlg.Width() - DAY_LIST_WIDTH * 7) / 2, DAY_LIST_START_Y, (rectDlg.Width() - DAY_LIST_WIDTH * 7) / 2 + DAY_LIST_WIDTH, DAY_LIST_START_Y + DAY_LIST_HEIGHT);

	CString strDay = _T("");
	int nWeekCnt = 0;
	m_nBeforeDayListBox = 0;
	m_nDayListBox = 0;
	m_nNextDayListBox = 0;

	for (int i = 0; i < calendarDate.firstday_week - 1; i++)
	{
		strDay.Format(_T("%d"), calendarDate.beforelast_day - calendarDate.firstday_week + 2 + i);

		m_pBeforeDayListBox[i] = new CListBox();
		m_pBeforeDayListBox[i]->Create(WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER | WS_DISABLED | LBS_STANDARD | LBS_NOSEL | LBS_NOTIFY | LBS_SORT, rectList, this, BEFORE_LISTBOX_ID + i);
		m_pBeforeDayListBox[i]->SetFont(GetFont());
		m_pBeforeDayListBox[i]->AddString(strDay);

		rectList.MoveToXY((rectDlg.Width() - DAY_LIST_WIDTH * 7) / 2 + (i + 1) * DAY_LIST_WIDTH, DAY_LIST_START_Y);

		m_nBeforeDayListBox += 1;
	}

	for (int i = 0, x = calendarDate.firstday_week - 1; i < calendarDate.lastday_day; i++)
	{
		strDay.Format(_T("%d"), i + 1);

		m_pDayListBox[i] = new CListBox();
		m_pDayListBox[i]->Create(WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER | LBS_STANDARD | LBS_NOSEL | LBS_NOTIFY | LBS_SORT, rectList, this, THIS_LISTBOX_ID + i);
		m_pDayListBox[i]->SetFont(GetFont());
		m_pDayListBox[i]->AddString(strDay);

		if (x == 6)
		{
			x = 0;
			nWeekCnt += 1;
		}
		else
		{
			x += 1;
		}

		rectList.MoveToXY((rectDlg.Width() - DAY_LIST_WIDTH * 7) / 2 + x * DAY_LIST_WIDTH, DAY_LIST_START_Y + nWeekCnt * DAY_LIST_HEIGHT);

		m_nDayListBox += 1;
	}

	for (int i = 0; i < 7 - calendarDate.lastday_week; i++)
	{
		strDay.Format(_T("%d"), 1 + i);
		
		m_pNextDayListBox[i] = new CListBox();
		m_pNextDayListBox[i]->Create(WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER | WS_DISABLED | LBS_STANDARD | LBS_NOSEL | LBS_NOTIFY | LBS_SORT, rectList, this, NEXT_LISTBOX_ID + i);
		m_pNextDayListBox[i]->SetFont(GetFont());
		m_pNextDayListBox[i]->AddString(strDay);

		rectList.MoveToXY((rectDlg.Width() - DAY_LIST_WIDTH * 7) / 2 + (calendarDate.lastday_week + 1 + i) * DAY_LIST_WIDTH, DAY_LIST_START_Y + nWeekCnt * DAY_LIST_HEIGHT);

		m_nNextDayListBox += 1;
	}
}

void CCalendarDlg::ResizeCalendar(int cx, int cy)
{
	if (!m_bInit)
		return;

	m_pMonthStatic->MoveWindow(CRect(cx / 2 - 100, 0, cx / 2 + 100, 50));
	m_pTodayBtn->MoveWindow(CRect((cx - DAY_LIST_WIDTH * 7) / 2, 10, (cx - DAY_LIST_WIDTH * 7) / 2 + 50, 40));
	m_pBeforeMonthBtn->MoveWindow(CRect(cx / 2 - 140, 10, cx / 2 - 110, 40));
	m_pNextMonthBtn->MoveWindow(CRect(cx / 2 + 110, 10, cx / 2 + 140, 40));

	for (int i = 0; i < 7; i++)
	{
		m_pWeekStatic[i]->MoveWindow(CRect((cx - DAY_LIST_WIDTH * 7) / 2 + i * DAY_LIST_WIDTH, 50, (cx - DAY_LIST_WIDTH * 7) / 2 + (i + 1) * DAY_LIST_WIDTH, 70));
	}

	CRect rectList;
	rectList.SetRect((cx - DAY_LIST_WIDTH * 7) / 2, DAY_LIST_START_Y, (cx - DAY_LIST_WIDTH * 7) / 2 + DAY_LIST_WIDTH, DAY_LIST_START_Y + DAY_LIST_HEIGHT);

	for (int i = 0; i < m_nBeforeDayListBox; i++)
	{
		m_pBeforeDayListBox[i]->MoveWindow(rectList);
		rectList.MoveToXY((cx - DAY_LIST_WIDTH * 7) / 2 + (i + 1) * DAY_LIST_WIDTH, DAY_LIST_START_Y);
	}

	int nWeekCnt = 0;
	for (int i = 0, x = calendarDate.firstday_week - 1; i < m_nDayListBox; i++)
	{
		m_pDayListBox[i]->MoveWindow(rectList);

		if (x == 6)
		{
			x = 0;
			nWeekCnt += 1;
		}
		else
		{
			x += 1;
		}

		rectList.MoveToXY((cx - DAY_LIST_WIDTH * 7) / 2 + x * DAY_LIST_WIDTH, DAY_LIST_START_Y + nWeekCnt * DAY_LIST_HEIGHT);
	}

	for (int i = 0; i < m_nNextDayListBox; i++)
	{
		m_pNextDayListBox[i]->MoveWindow(rectList);
		rectList.MoveToXY((cx - DAY_LIST_WIDTH * 7) / 2 + (calendarDate.lastday_week + 1 + i) * DAY_LIST_WIDTH, DAY_LIST_START_Y + nWeekCnt * DAY_LIST_HEIGHT);
	}
}

void CCalendarDlg::DeleteDayListBox()
{
	if (m_pBeforeDayListBox != NULL)
	{
		for (int i = 0; i < m_nBeforeDayListBox; i++)
		{
			delete m_pBeforeDayListBox[i];
			m_pBeforeDayListBox[i] = NULL;
		}
		delete[] m_pBeforeDayListBox;
	}

	if (m_pDayListBox != NULL)
	{
		for (int i = 0; i < m_nDayListBox; i++)
		{
			delete m_pDayListBox[i];
			m_pDayListBox[i] = NULL;
		}
		delete[] m_pDayListBox;
	}

	if (m_pNextDayListBox != NULL)
	{
		for (int i = 0; i < m_nNextDayListBox; i++)
		{
			delete m_pNextDayListBox[i];
			m_pNextDayListBox[i] = NULL;
		}
		delete[] m_pNextDayListBox;
	}
}

void CCalendarDlg::OnDestroy()
{
	CDialog::OnDestroy();

	DeleteDayListBox();
}


HBRUSH CCalendarDlg::OnCtlColor(CDC *pDC, CWnd *pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  Change any attributes of the DC here

	// TODO:  Return a different brush if the default is not desired
	if (pWnd->GetDlgCtrlID() == WEEK_STATIC_ID)
	{
		pDC->SetTextColor(RGB(255, 0, 0));
	}
	else if (pWnd->GetDlgCtrlID() == WEEK_STATIC_ID + 6)
	{
		pDC->SetTextColor(RGB(0, 0, 255));
	}
	else if (pWnd->GetDlgCtrlID() == THIS_LISTBOX_ID + todayDate.day - 1 && calendarDate.year == todayDate.year && calendarDate.month == todayDate.month)	// set today
	{
		return m_today_hbr;
	}

	return hbr;
}


void CCalendarDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	ResizeCalendar(cx, cy);

}


void CCalendarDlg::OnBnClickedTodayButton()
{
	GetToday();
	DrawMonthlyCalendar();
}


void CCalendarDlg::OnBnClickedBeforeMonthButton()
{
	GetDate(calendarDate.beforelast_year, calendarDate.beforelast_month);
	DrawMonthlyCalendar();
}

void CCalendarDlg::OnBnClickedNextMonthButton()
{
	GetDate(calendarDate.nextfirst_year, calendarDate.nextfirst_month);
	DrawMonthlyCalendar();
}