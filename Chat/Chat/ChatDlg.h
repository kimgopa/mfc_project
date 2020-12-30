
// ChatDlg.h: 헤더 파일
//

#pragma once
#include "CEnterNotifyEdit.h"


// CChatDlg 대화 상자
class CChatDlg : public CDialogEx
{
// 생성입니다.
public:
	CChatDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CHAT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CListBox m_ctrlListBox;
	CString m_strEdit;
	virtual void OnOK();

	CServerSocket m_ServerSocket;
	CDataSocket m_DataSocket;
	afx_msg LRESULT OnAccept(WPARAM wParam, LPARAM lParam);
	afx_msg void OnBnClickedConnectButton();
	CEnterNotifyEdit m_ctrlEdit;
	afx_msg void OnEnterKey();
	afx_msg LRESULT OnReceive(WPARAM wParam, LPARAM lParam);
};
