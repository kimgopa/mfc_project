
// ODBCTestDoc.cpp : CODBCTestDoc 클래스의 구현
//

#include "stdafx.h"
#include "ODBCTest.h"

#include "ODBCTestDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CODBCTestDoc

IMPLEMENT_DYNCREATE(CODBCTestDoc, CDocument)

BEGIN_MESSAGE_MAP(CODBCTestDoc, CDocument)
END_MESSAGE_MAP()


// CODBCTestDoc 생성/소멸

CODBCTestDoc::CODBCTestDoc()
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.

}

CODBCTestDoc::~CODBCTestDoc()
{
}

BOOL CODBCTestDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.

	return TRUE;
}




// CODBCTestDoc serialization

void CODBCTestDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 여기에 저장 코드를 추가합니다.
	}
	else
	{
		// TODO: 여기에 로딩 코드를 추가합니다.
	}
}


// CODBCTestDoc 진단

#ifdef _DEBUG
void CODBCTestDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CODBCTestDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CODBCTestDoc 명령
