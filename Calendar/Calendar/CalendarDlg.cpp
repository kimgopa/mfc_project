
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

#define THIS_LISTBOX_ID 10001
#define BEFORE_LISTBOX_ID 11001
#define NEXT_LISTBOX_ID 12001
#define WEEK_STATIC_ID 13001

#define DAY_LIST_START_X 0
#define DAY_LIST_START_Y 70
#define DAY_LIST_WIDTH 100
#define DAY_LIST_HEIGHT 100

// CCalendarDlg dialog



CCalendarDlg::CCalendarDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_CALENDAR_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_listbox_cnt = 0;
	m_today_year = -1;
	m_today_month = -1;
	m_today_day = -1;
	m_today_week = -1;
	m_firstday_week = -1;
	m_lastday_day = -1;
	m_lastday_week = -1;

	m_pMonthStatic = NULL;

	m_pBeforeDayListBox = NULL;
	m_pDayListBox = NULL;
	m_pNextDayListBox = NULL;

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
	//MoveWindow(0, 0, DAY_LIST_WIDTH * 7 + 50, DAY_LIST_START_Y + DAY_LIST_HEIGHT * 6 + 70);
	MoveWindow(0, 0, 1024, 768);

	GetDate();
	DrawMonthlyCalendar();

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

void CCalendarDlg::GetDate()
{
	//현재 날짜 구하기 
	CTime time = CTime::GetTickCount();
	m_today_year = time.GetYear();
	m_today_month = time.GetMonth();
	m_today_day = time.GetDay();
	m_today_week = time.GetDayOfWeek();//요일반환 1 = 일요일, 2 = 월요일, 7 = 토요일

	/* 현재달 시작일 구하기 */
	//CTime(년, 월, 일, 시, 분, 초);
	CTime firstDay = CTime(m_today_year, m_today_month, 1, 9, 0, 0);
	m_firstday_week = firstDay.GetDayOfWeek();

	/* 이전 마지막 일자 구하기 */
	//하루 24시간의 tick값 CTimeSpan(일, 시간, 분, 초);  
	CTimeSpan span(1, 0, 0, 0);

	//그냥 86400초 빼도 된다.  
	//int oneDay = 24 * 60 * 60;   

	//시작일에서 하루 빼기  
	firstDay -= span;

	int beforeYear = firstDay.GetYear();
	int beforeMonth = firstDay.GetMonth();
	int beforeDay = firstDay.GetDay();
	int beforeWeek = firstDay.GetDayOfWeek();

	/* 현재달 마지막일 구하기 */
	//다음달 시작일 구함  
	CTime cTimelastDay = CTime(m_today_year, m_today_month + 1, 1, 9, 0, 0);
	cTimelastDay -= span;

	int lastYear = cTimelastDay.GetYear();
	int lastMonth = cTimelastDay.GetMonth();
	m_lastday_day = cTimelastDay.GetDay();
	m_lastday_week = cTimelastDay.GetDayOfWeek();
}

void CCalendarDlg::DrawMonthlyCalendar()
{
	CRect rectDlg;
	this->GetWindowRect(rectDlg);

	// month
//	_TCHAR month[4];
//	memset(month, 0, sizeof(month));
//	_stprintf_s(month, _countof(month), _T("%d월"), m_today_month);
	CString strMonth;
	strMonth.Format(_T("%d월"), m_today_month);
	
	m_pMonthStatic = new CStatic();
	m_pMonthStatic->Create(strMonth, WS_CHILD | WS_VISIBLE | SS_NOTIFY | SS_CENTER | SS_CENTERIMAGE, CRect(rectDlg.right / 2 - 25, 0, rectDlg.right / 2 + 25, 50), this);
	m_pMonthStatic->SetFont(GetFont());

	// week
	CRect rectStatic;
	rectStatic.SetRect((rectDlg.right - DAY_LIST_WIDTH * 7) / 2, 50, (rectDlg.right - DAY_LIST_WIDTH * 7) / 2 + DAY_LIST_WIDTH, 70);

	m_pWeekStatic[0] = new CStatic();
	m_pWeekStatic[0]->Create(_T("일"), WS_CHILD | WS_VISIBLE | SS_NOTIFY | SS_CENTER | SS_CENTERIMAGE, rectStatic, this, WEEK_STATIC_ID);
	m_pWeekStatic[0]->SetFont(GetFont());
	rectStatic.MoveToXY((rectDlg.right - DAY_LIST_WIDTH * 7) / 2 + DAY_LIST_WIDTH, 50);

	m_pWeekStatic[1] = new CStatic();
	m_pWeekStatic[1]->Create(_T("월"), WS_CHILD | WS_VISIBLE | SS_NOTIFY | SS_CENTER | SS_CENTERIMAGE, rectStatic, this, WEEK_STATIC_ID + 1);
	m_pWeekStatic[1]->SetFont(GetFont());
	rectStatic.MoveToXY((rectDlg.right - DAY_LIST_WIDTH * 7) / 2 + 2 * DAY_LIST_WIDTH, 50);

	m_pWeekStatic[2] = new CStatic();
	m_pWeekStatic[2]->Create(_T("화"), WS_CHILD | WS_VISIBLE | SS_NOTIFY | SS_CENTER | SS_CENTERIMAGE, rectStatic, this, WEEK_STATIC_ID + 2);
	m_pWeekStatic[2]->SetFont(GetFont());
	rectStatic.MoveToXY((rectDlg.right - DAY_LIST_WIDTH * 7) / 2 + 3 * DAY_LIST_WIDTH, 50);

	m_pWeekStatic[3] = new CStatic();
	m_pWeekStatic[3]->Create(_T("수"), WS_CHILD | WS_VISIBLE | SS_NOTIFY | SS_CENTER | SS_CENTERIMAGE, rectStatic, this, WEEK_STATIC_ID + 3);
	m_pWeekStatic[3]->SetFont(GetFont());
	rectStatic.MoveToXY((rectDlg.right - DAY_LIST_WIDTH * 7) / 2 + 4 * DAY_LIST_WIDTH, 50);

	m_pWeekStatic[4] = new CStatic();
	m_pWeekStatic[4]->Create(_T("목"), WS_CHILD | WS_VISIBLE | SS_NOTIFY | SS_CENTER | SS_CENTERIMAGE, rectStatic, this, WEEK_STATIC_ID + 4);
	m_pWeekStatic[4]->SetFont(GetFont());
	rectStatic.MoveToXY((rectDlg.right - DAY_LIST_WIDTH * 7) / 2 + 5 * DAY_LIST_WIDTH, 50);

	m_pWeekStatic[5] = new CStatic();
	m_pWeekStatic[5]->Create(_T("금"), WS_CHILD | WS_VISIBLE | SS_NOTIFY | SS_CENTER | SS_CENTERIMAGE, rectStatic, this, WEEK_STATIC_ID + 5);
	m_pWeekStatic[5]->SetFont(GetFont());
	rectStatic.MoveToXY((rectDlg.right - DAY_LIST_WIDTH * 7) / 2 + 6 * DAY_LIST_WIDTH, 50);

	m_pWeekStatic[6] = new CStatic();
	m_pWeekStatic[6]->Create(_T("토"), WS_CHILD | WS_VISIBLE | SS_NOTIFY | SS_CENTER | SS_CENTERIMAGE, rectStatic, this, WEEK_STATIC_ID + 6);
	m_pWeekStatic[6]->SetFont(GetFont());
	rectStatic.MoveToXY((rectDlg.right - DAY_LIST_WIDTH * 7) / 2 + 2 * DAY_LIST_WIDTH, 50);

	// day
	m_pBeforeDayListBox = new CListBox * [m_firstday_week - 1];
	m_pDayListBox = new CListBox * [m_lastday_day];
	m_pNextDayListBox = new CListBox * [8 - m_lastday_week];

	CRect rectList;
	rectList.SetRect((rectDlg.right - DAY_LIST_WIDTH * 7) / 2, DAY_LIST_START_Y, (rectDlg.right - DAY_LIST_WIDTH * 7) / 2 + DAY_LIST_WIDTH, DAY_LIST_START_Y + DAY_LIST_HEIGHT);

	CString strDay = _T("");
	int nWeekCnt = 0;

	for (int i = 0; i < m_firstday_week - 1; i++)
	{
		m_pBeforeDayListBox[i] = new CListBox();
		m_pBeforeDayListBox[i]->Create(WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER | WS_DISABLED | LBS_STANDARD | LBS_NOSEL | LBS_NOTIFY | LBS_SORT, rectList, this, BEFORE_LISTBOX_ID + i);
		m_pBeforeDayListBox[i]->SetFont(GetFont());

		rectList.MoveToXY((rectDlg.right - DAY_LIST_WIDTH * 7) / 2 + (i + 1) * DAY_LIST_WIDTH, DAY_LIST_START_Y);
	}

	for (int i = 0, x = m_firstday_week - 1; i < m_lastday_day; i++)
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

		rectList.MoveToXY((rectDlg.right - DAY_LIST_WIDTH * 7) / 2 + x * DAY_LIST_WIDTH, DAY_LIST_START_Y + nWeekCnt * DAY_LIST_HEIGHT);
	}

	for (int i = 0; i <= 7 - m_lastday_week; i++)
	{
		m_pNextDayListBox[i] = new CListBox();
		m_pNextDayListBox[i]->Create(WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER | WS_DISABLED | LBS_STANDARD | LBS_NOSEL | LBS_NOTIFY | LBS_SORT, rectList, this, NEXT_LISTBOX_ID + i);
		m_pNextDayListBox[i]->SetFont(GetFont());

		rectList.MoveToXY((rectDlg.right - DAY_LIST_WIDTH * 7) / 2 + (m_lastday_week + i) * DAY_LIST_WIDTH, DAY_LIST_START_Y + nWeekCnt * DAY_LIST_HEIGHT);
	}
}

void CCalendarDlg::OnDestroy()
{
	CDialog::OnDestroy();

	if (m_pBeforeDayListBox != NULL)
	{
		for (int i = 0; i < m_firstday_week - 1; i++)
		{
			delete m_pBeforeDayListBox[i];
			m_pBeforeDayListBox[i] = NULL;
		}
		delete[] m_pBeforeDayListBox;
	}

	if (m_pDayListBox != NULL)
	{
		for (int i = m_lastday_week; i < m_lastday_day; i++)
		{
			delete m_pDayListBox[i];
			m_pDayListBox[i] = NULL;
		}
		delete[] m_pDayListBox;
	}

	if (m_pNextDayListBox != NULL)
	{
		for (int i = 0; i <= 7 - m_lastday_week; i++)
		{
			delete m_pNextDayListBox[i];
			m_pNextDayListBox[i] = NULL;
		}
		delete[] m_pNextDayListBox;
	}
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
	else if (pWnd->GetDlgCtrlID() == THIS_LISTBOX_ID + m_today_day - 1)	// set today
	{
		return m_today_hbr;
	}

	return hbr;
}
