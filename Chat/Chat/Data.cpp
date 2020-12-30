// Data.cpp : implementation file
//
/*
	통신 프로그램이 서로간에 데이터를 주고 받으려면 양쪽에서 데이터 포맷이 같아야 함
	통신 프로그램마다 주고 받는 데이터의 포맷은 달라질 것이므로, 프로그램에 따라 이 부분을 변경해주면 됨
	전송될 데이터는 CData 클래스에 캡슐화
*/

#include "pch.h"
#include "Data.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CData

CData::CData()
{
}

CData::~CData()
{
}

/////////////////////////////////////////////////////////////////////////////
// CData member functions

// Serialize 함수를 이용하여 데이터를 전송할 것이므로 반드시 CObject 클래스에서 상속을 받아야 하며 Serialize 함수가 다음과 같이 재정의되어야 한다.
// 프로그램에 따라 전송해야 할 데이터의 포멧이 달라질 것인데, 이때 이 클래스의 멤버 변수의 내용을 바꿔주고 Serialize 함수에서 멤버 변수들을 차례로 송신하고 수신하도록 만들어 주기만 하면 된다.
void CData::Serialize(CArchive &ar)
{
	if(ar.IsStoring())
	{
		// 네트워크로 송신
		ar << m_strData;
	}
	else
	{
		// 네트워크에서 수신
		ar >> m_strData;
	}
}
