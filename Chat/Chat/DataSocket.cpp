// DataSocket.cpp : implementation file
//
/*
	CSocket Ŭ�������� ��� ���� Ŭ����
	CArchive, CSocketFile Ŭ������ �Բ� ���� ������(CData Ŭ������ ����Ǿ� �ִ� ������)�� �ְ� �޴µ� ���õ� ��� ����
	Ŭ���̾�Ʈ �������� ������ ���� ��û�� �� �� ����
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

// ������ ���� �ʱ�ȭ : ���ο� �����Ͱ� ���ŵǾ��� �� �޽����� ���� ���� �������� �����͸� ���ڷ� ����
// CSocket, CSocketFile, CArchive Ŭ������ �¹������� ��
void CDataSocket::Init(CWnd *pWnd)
{
	m_pWnd = pWnd;
	m_pFile = new CSocketFile(this);
	m_pArchiveIn = new CArchive(m_pFile, CArchive::load);
	m_pArchiveOut = new CArchive(m_pFile, CArchive::store);
}

// ============================ ������ ���� ============================
void CDataSocket::Receive(CData * pData)
{
	if(m_pArchiveIn != NULL)
		pData->Serialize(*m_pArchiveIn);
}

// Receive �Լ� ȣ��
void CDataSocket::operator >>(CData & data)
{
	Receive (&data);
}

// ============================ ������ �۽� ============================
void CDataSocket::Send(CData * pData)
{
	if(m_pArchiveOut != NULL)
		pData->Serialize(*m_pArchiveOut);
}

// Send �Լ��� �̿��Ͽ� �����͸� �۽��Ѵٰ� �ؼ� �� �����Ͱ� �ٷ� ��Ʈ��ũ�� ���� ���۵Ǵ� ���� �ƴϰ�, ���� ������ �����ϴ� �۽ſ� ���ۿ� ����Ǳ⸸ �Ѵ�.
// �����Ͱ� ���� ��Ʈ��ũ�� ���� ���۵� ���� ���� ������尡 �ٰ� �Ǵµ� �ʹ� ���� ���� �����͸� ������ �Ǹ� ���� �����ͺ��� ������尡 �� Ŀ���� �躸�� ����� �� Ŀ���� ���� �ȴ�.
// ���� ���� ȿ���� ���̱� ���ؼ�, �����Ͱ� ��� ���� ���� ������ ���� �������� �ʰ�, ������ �ξ��ٰ� ��� ���� ���� �̻� �Ǹ� ������ �Ѵ�.
// ���� ��� ���ۿ� ����Ǿ� �ִ� �����͸� �ٷ� ��Ʈ��ũ�� ���� �����ϰ��� �ϴ� Flush �Լ��� ȣ���Ѵ�.

// ���� ��� ���ۿ� ����Ǿ� �ִ� ������ �ٷ� ��Ʈ��ũ�� ���� ���۵ȴ�.
void CDataSocket::Flush()
{
	if(m_pArchiveOut != NULL)
		m_pArchiveOut->Flush();
}

// Send �Լ� ȣ��
void CDataSocket::operator <<(CData & data)
{
	Send (&data);
	Flush();
}
// =====================================================================

// �������� Ŭ������ ����� ���� ���ο� �����Ͱ� ���ŵǾ��� �� OnReceive �Լ����� ���� �����͸� �������� �ʰ�, UM_DATARECEIVE �޽����� ���� �����쿡 �������ν� ���� �����쿡�� �����͸� ������ �� �ֵ��� ��
void CDataSocket::OnReceive(int nErrorCode) 
{
	m_pWnd->SendMessage(UM_DATARECEIVE);	// ���� �����쿡 �޽����� ����
	CSocket::OnReceive(nErrorCode);
}

// ����� ������ ������ �������� ȣ��
// �������� �Ҵ��ߴ� CArchive Ŭ������ CSocketFile ������Ʈ ����
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
