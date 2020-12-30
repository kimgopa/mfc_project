
// ChatDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "Chat.h"
#include "ChatDlg.h"
#include "afxdialogex.h"
#include "ConnectDlg.h"
#include "Data.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CChatDlg 대화 상자



CChatDlg::CChatDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CHAT_DIALOG, pParent)
	, m_strEdit(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CChatDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST, m_ctrlListBox);
	DDX_Text(pDX, IDC_EDIT, m_strEdit);
	DDX_Control(pDX, IDC_EDIT, m_ctrlEdit);
}

BEGIN_MESSAGE_MAP(CChatDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(UM_ACCEPT, OnAccept)
	ON_BN_CLICKED(IDC_CONNECT_BUTTON, &CChatDlg::OnBnClickedConnectButton)
	ON_COMMAND(ID_ENTERKEY, OnEnterKey)
	ON_MESSAGE(UM_DATARECEIVE, OnReceive)
END_MESSAGE_MAP()


// CChatDlg 메시지 처리기

BOOL CChatDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	m_ServerSocket.Init(this, 2000);	// 서버 소켓 초기화

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CChatDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CChatDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CChatDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

LRESULT CChatDlg::OnAccept(WPARAM wParam, LPARAM lParam)
{
	// 연결을 받아들이고, 클라이언트와 m_DataSocket을 연결시켜 줌
	if (!m_ServerSocket.Accept(m_DataSocket))
	{
		AfxMessageBox("Accept 실패");
		return 0;
	}

	// 데이터 소켓 초기화
	m_DataSocket.Init(this);

	m_ctrlListBox.AddString("*** 연결되었습니다. ***");
	return 0L;
}



void CChatDlg::OnOK()
{
	// 엔터키를 누르면 IDOK 이벤트가 발생하여 대화상자가 종료되는데, 이를 막기 위해 OnOK 함수 재정의
	//CDialogEx::OnOK();
}


void CChatDlg::OnBnClickedConnectButton()
{
	// IP 주소를 입력 받는 대화상자 출력
	CConnectDlg dlg;
	if (dlg.DoModal() != IDOK) return;

	// 클라이언트 소켓 생성
	if (!m_DataSocket.Create())
	{
		AfxMessageBox("클라이언트 소켓 생성 실패");
		return;
	}

	// 접속 요청
	if (!m_DataSocket.Connect(dlg.m_strAddress, 2000))
	{
		AfxMessageBox("서버 접속 실패");
		return;
	}

	// 클라이언트 소켓 초기화
	m_DataSocket.Init(this);

	m_ctrlListBox.AddString("*** 연결되었습니다. ***");
}

void CChatDlg::OnEnterKey()
{
	UpdateData();

	// 데이터 전송
	CData data;
	data.m_strData = m_strEdit;
	m_DataSocket << data;
	
	// 전송된 문자열을 상단 윈도우에도 표시
	m_ctrlListBox.AddString(m_strEdit);
	m_ctrlListBox.SetCurSel(m_ctrlListBox.GetCount() - 1);
	m_ctrlListBox.SetCurSel(-1);

	// Edit 컨트롤 초기화
	m_strEdit.Empty();
	UpdateData(FALSE);
}

LRESULT CChatDlg::OnReceive(WPARAM wParam, LPARAM lParam)
{
	// 통신 버퍼에 있는 데이터를 전부 수신할 때까지...
	do {
		// 데이터 수신
		CData data;
		m_DataSocket >> data;

		// 수신된 데이터 표시
		m_ctrlListBox.AddString(data.m_strData);
		m_ctrlListBox.SetCurSel(m_ctrlListBox.GetCount() - 1);
		m_ctrlListBox.SetCurSel(-1);
	} while (!m_DataSocket.m_pArchiveIn->IsBufferEmpty());
	return 0L;
}