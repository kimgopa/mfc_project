// ServerSocket.cpp : implementation file
//
/*
	CSocket 클래스에서 상속 받은 클래스
	서버에서 클라이언트의 접속 요청을 받아들여 클라이언트와 서버의 데이터 소켓을 연결시켜주는 역할
	실제 데이터를 주고 받는 데는 관여하지 않음
*/

#include "pch.h"
#include "ServerSocket.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CServerSocket

CServerSocket::CServerSocket()
{
}

CServerSocket::~CServerSocket()
{
}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CServerSocket, CSocket)
	//{{AFX_MSG_MAP(CServerSocket)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CServerSocket member functions

// 접속 요청이 들어왔을 때, 어떤 윈도우에 메시지를 보내 줄 것인지, 접속 요청을 위해서 어떤 포트 번호를 사용할 것인지를 인자로 받음
void CServerSocket::Init(CWnd *pWnd, int nPortNum)
{
	m_pWnd = pWnd;
	Create(nPortNum);	// 서버 소켓 초기화
	Listen();			// 접속 요청 감지 시작
}

// 클라이언트로부터 접속 요청이 들어오면 호출됨
void CServerSocket::OnAccept(int nErrorCode) 
{
	m_pWnd->SendMessage(UM_ACCEPT);	// 메인 윈도우에 UM_ACCEPT 메시지를 보냄 -> 접속을 받아들이는 일을 메인 윈도우에서 가능하게 함
	CSocket::OnAccept(nErrorCode);
}
