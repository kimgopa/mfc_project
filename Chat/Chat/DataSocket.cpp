// DataSocket.cpp : implementation file
//
/*
	CSocket 클래스에서 상속 받은 클래스
	CArchive, CSocketFile 클래스와 함께 실제 데이터(CData 클래스에 저장되어 있는 데이터)를 주고 받는데 관련된 기능 수행
	클라이언트 소켓으로 서버에 접속 요청을 할 수 있음
*/

#include "pch.h"
#include "DataSocket.h"
#include "Data.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDataSocket

CDataSocket::CDataSocket()
{
}

CDataSocket::~CDataSocket()
{
}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CDataSocket, CSocket)
	//{{AFX_MSG_MAP(CDataSocket)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CDataSocket member functions

// 데이터 소켓 초기화 : 새로운 데이터가 수신되었을 때 메시지를 전송 받을 윈도우의 포인터를 인자로 받음
// CSocket, CSocketFile, CArchive 클래스가 맞물리도록 함
void CDataSocket::Init(CWnd *pWnd)
{
	m_pWnd = pWnd;
	m_pFile = new CSocketFile(this);
	m_pArchiveIn = new CArchive(m_pFile, CArchive::load);
	m_pArchiveOut = new CArchive(m_pFile, CArchive::store);
}

// ============================ 데이터 수신 ============================
void CDataSocket::Receive(CData * pData)
{
	if(m_pArchiveIn != NULL)
		pData->Serialize(*m_pArchiveIn);
}

// Receive 함수 호출
void CDataSocket::operator >>(CData & data)
{
	Receive (&data);
}

// ============================ 데이터 송신 ============================
void CDataSocket::Send(CData * pData)
{
	if(m_pArchiveOut != NULL)
		pData->Serialize(*m_pArchiveOut);
}

// Send 함수를 이용하여 데이터를 송신한다고 해서 이 데이터가 바로 네트워크를 통해 전송되는 것은 아니고, 단지 소켓이 관리하는 송신용 버퍼에 저장되기만 한다.
// 데이터가 실제 네트워크를 통해 전송될 때는 여러 오버헤드가 붙게 되는데 너무 작은 양의 데이터를 보내게 되면 실제 데이터보다 오버헤드가 더 커져서 배보다 배꼽이 더 커지는 꼴이 된다.
// 따라서 전송 효율을 높이기 위해서, 데이터가 어느 정도 길이 이하일 때는 전송하지 않고, 저장해 두었다가 어느 정도 길이 이상 되면 전송을 한다.
// 현재 통신 버퍼에 저장되어 있는 데이터를 바로 네트워크를 통해 전송하고자 하는 Flush 함수를 호출한다.

// 현재 통신 버퍼에 저장되어 있는 내용이 바로 네트워크를 통해 전송된다.
void CDataSocket::Flush()
{
	if(m_pArchiveOut != NULL)
		m_pArchiveOut->Flush();
}

// Send 함수 호출
void CDataSocket::operator <<(CData & data)
{
	Send (&data);
	Flush();
}
// =====================================================================

// 범용적인 클래스를 만들기 위해 새로운 데이터가 수신되었을 때 OnReceive 함수에서 직접 데이터를 수신하지 않고, UM_DATARECEIVE 메시지를 메인 윈도우에 보냄으로써 메인 윈도우에서 데이터를 수신할 수 있도록 함
void CDataSocket::OnReceive(int nErrorCode) 
{
	m_pWnd->SendMessage(UM_DATARECEIVE);	// 메인 윈도우에 메시지를 보냄
	CSocket::OnReceive(nErrorCode);
}

// 연결된 소켓의 접속이 끊어지면 호출
// 동적으로 할당했던 CArchive 클래스와 CSocketFile 오브젝트 삭제
void CDataSocket::OnClose(int nErrorCode) 
{
	if(m_pFile != NULL) {
		delete m_pFile;
		m_pFile = NULL;
	}
	if(m_pArchiveIn != NULL) {
		m_pArchiveIn->Abort();
		delete m_pArchiveIn;
		m_pArchiveIn = NULL;
	}
	if(m_pArchiveOut != NULL) {
		m_pArchiveOut->Abort();
		delete m_pArchiveOut;
		m_pArchiveOut = NULL;
	}	
	
	CSocket::OnClose(nErrorCode);
}
