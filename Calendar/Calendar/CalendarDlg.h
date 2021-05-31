
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
	int m_listbox_cnt;
	int m_today_year;
	int m_today_month;
	int m_today_day;
	int m_today_week;
	int m_firstday_week;
	int m_lastday_day;
	int m_lastday_week;
	CBrush m_today_hbr;
protected:
	CStatic *m_pMonthStatic;
	CStatic *m_pWeekStatic[7];
	CListBox **m_pBeforeDayListBox, **m_pDayListBox, **m_pNextDayListBox;
protected:
	void GetDate();
	void DrawMonthlyCalendar();
public:
	afx_msg void OnDestroy();
	afx_msg HBRUSH OnCtlColor(CDC *pDC, CWnd *pWnd, UINT nCtlColor);
};
