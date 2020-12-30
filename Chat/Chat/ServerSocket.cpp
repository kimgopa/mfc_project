// ServerSocket.cpp : implementation file
//
/*
	CSocket Ŭ�������� ��� ���� Ŭ����
	�������� Ŭ���̾�Ʈ�� ���� ��û�� �޾Ƶ鿩 Ŭ���̾�Ʈ�� ������ ������ ������ ��������ִ� ����
	���� �����͸� �ְ� �޴� ���� �������� ����
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

// ���� ��û�� ������ ��, � �����쿡 �޽����� ���� �� ������, ���� ��û�� ���ؼ� � ��Ʈ ��ȣ�� ����� �������� ���ڷ� ����
void CServerSocket::Init(CWnd *pWnd, int nPortNum)
{
	m_pWnd = pWnd;
	Create(nPortNum);	// ���� ���� �ʱ�ȭ
	Listen();			// ���� ��û ���� ����
}

// Ŭ���̾�Ʈ�κ��� ���� ��û�� ������ ȣ���
void CServerSocket::OnAccept(int nErrorCode) 
{
	m_pWnd->SendMessage(UM_ACCEPT);	// ���� �����쿡 UM_ACCEPT �޽����� ���� -> ������ �޾Ƶ��̴� ���� ���� �����쿡�� �����ϰ� ��
	CSocket::OnAccept(nErrorCode);
}
