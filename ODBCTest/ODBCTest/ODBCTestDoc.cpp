
// ODBCTestDoc.cpp : CODBCTestDoc Ŭ������ ����
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


// CODBCTestDoc ����/�Ҹ�

CODBCTestDoc::CODBCTestDoc()
{
	// TODO: ���⿡ ��ȸ�� ���� �ڵ带 �߰��մϴ�.

}

CODBCTestDoc::~CODBCTestDoc()
{
}

BOOL CODBCTestDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: ���⿡ ���ʱ�ȭ �ڵ带 �߰��մϴ�.
	// SDI ������ �� ������ �ٽ� ����մϴ�.

	return TRUE;
}




// CODBCTestDoc serialization

void CODBCTestDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	}
	else
	{
		// TODO: ���⿡ �ε� �ڵ带 �߰��մϴ�.
	}
}


// CODBCTestDoc ����

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


// CODBCTestDoc ���
