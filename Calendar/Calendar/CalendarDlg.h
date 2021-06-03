
// CalendarDlg.h : header file
//

#pragma once


// CCalendarDlg dialog
class CCalendarDlg : public CDialog
{
// Construction
public:
	CCalendarDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CALENDAR_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

protected:
	struct CalendarDate
	{
		int year = 0;
		int month = 0;
		int day = 0;
		int week = 0;

		int firstday_week = 0;
		int lastday_day = 0;
		int lastday_week = 0;

		int beforelast_year = 0;
		int beforelast_month = 0;
		int beforelast_day = 0;

		int nextfirst_year = 0;
		int nextfirst_month = 0;
	};

	CalendarDate calendarDate, todayDate;
protected:
	BOOL m_bInit;

	int m_nBeforeDayListBox;
	int m_nDayListBox;
	int m_nNextDayListBox;

	CStatic *m_pMonthStatic;
	CStatic *m_pWeekStatic[7];
	CListBox **m_pBeforeDayListBox, **m_pDayListBox, **m_pNextDayListBox;
	CButton *m_pTodayBtn;
	CButton *m_pBeforeMonthBtn, *m_pNextMonthBtn;

	CBrush m_today_hbr;

	void GetToday();
	void GetDate();
	void GetDate(int nYear, int nMonth);
	void InitMonthlyCalendar();
	void DrawMonthlyCalendar();
	void ResizeCalendar(int cx, int cy);
	void DeleteDayListBox();
public:
	afx_msg void OnDestroy();
	afx_msg HBRUSH OnCtlColor(CDC *pDC, CWnd *pWnd, UINT nCtlColor);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBnClickedTodayButton();
	afx_msg void OnBnClickedBeforeMonthButton();
	afx_msg void OnBnClickedNextMonthButton();
};
