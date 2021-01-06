
// ODBCTestView.cpp : CODBCTestView 클래스의 구현
//

#include "stdafx.h"
#include "ODBCTest.h"

#include "ODBCTestDoc.h"
#include "ODBCTestView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CODBCTestView

IMPLEMENT_DYNCREATE(CODBCTestView, CFormView)

BEGIN_MESSAGE_MAP(CODBCTestView, CFormView)
	ON_BN_CLICKED(IDC_BUTTON_INSERT, &CODBCTestView::OnBnClickedButtonInsert)
	ON_BN_CLICKED(IDC_BUTTON_UPDATE, &CODBCTestView::OnBnClickedButtonUpdate)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, &CODBCTestView::OnBnClickedButtonDelete)
END_MESSAGE_MAP()

// CODBCTestView 생성/소멸

CODBCTestView::CODBCTestView()
	: CFormView(CODBCTestView::IDD)
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CODBCTestView::~CODBCTestView()
{
}

void CODBCTestView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST, m_ctrlList);
}

BOOL CODBCTestView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CFormView::PreCreateWindow(cs);
}

void CODBCTestView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

	// add list column
	m_ctrlList.InsertColumn(0, "이름", LVCFMT_LEFT, 80);
	m_ctrlList.InsertColumn(1, "전화번호", LVCFMT_LEFT, 150);
	m_ctrlList.InsertColumn(2, "생일", LVCFMT_LEFT, 150);
	m_ctrlList.InsertColumn(3, "성별", LVCFMT_LEFT, 80);

	SelectData();	// db 조회하여 list에 보여줌
}


// CODBCTestView 진단

#ifdef _DEBUG
void CODBCTestView::AssertValid() const
{
	CFormView::AssertValid();
}

void CODBCTestView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CODBCTestDoc* CODBCTestView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CODBCTestDoc)));
	return (CODBCTestDoc*)m_pDocument;
}
#endif //_DEBUG


void CODBCTestView::SelectData()
{
	try
	{
		// DSN 정보를 이용하여 DB open
		BOOL bOpen = m_db.OpenEx("DSN=DBTest;SERVER=localhost\\sqlexpress01;PORT=1433;UID=sa;PWD=kimgopa;DATABASE=Test;");

		if ( bOpen )
		{
			// recordset을 받아올 CRecordset 객체
			m_pRs = new CRecordset( &m_db );

			// query를 날려 recordset을 받아옴
			BOOL bOpen = m_pRs->Open( CRecordset::snapshot, "SELECT Name, Mobile, Birthday, Gender FROM [User]" );

			if ( bOpen )
			{
				if ( m_ctrlList.GetItemCount() > 0 )
					m_ctrlList.DeleteAllItems();

				CString strData;
				int iRow = 1;
				BOOL bIsEOF = m_pRs->IsEOF();
				//DWORD dwSize = m_pRs->GetRowsetSize();

				if ( !bIsEOF )
				{
					// MoveFirst() : 첫 번째 row로 이동
					// IsEOF() : 현재가 마지막이면 1 리턴
					// MoveNext() : 다음 row로 이동
					for ( m_pRs->MoveFirst(); !m_pRs->IsEOF(); m_pRs->MoveNext() )
					{
						// 조회한 테이블의 칼럼 수
						int iFieldCnt = m_pRs->GetODBCFieldCount();

						for ( int iCol = 0; iCol < iFieldCnt; iCol++ )
						{
							//m_pRs->SetAbsolutePosition( iRow );
							// iCol번째의 필드 값을 읽어 strData에 넣어줌
							m_pRs->GetFieldValue( iCol, strData );

							// insert list control
							if ( iCol == 0 )
								m_ctrlList.InsertItem( iRow-1, strData );
							else
								m_ctrlList.SetItemText( iRow-1, iCol, strData );
						}

						iRow++;
					}
				}
			}
			else
			{
				AfxMessageBox("Query Fail..");
			}
		}
		else
		{
			AfxMessageBox("DB Open Fail..");
		}
	}
	catch ( CException *e )
	{
		e->ReportError();
	}

	// 사용 후 CRecordset, CDatabase 순으로 종료
	if ( m_pRs->IsOpen() )
		m_pRs->Close();
	if ( m_db.IsOpen() )
		m_db.Close();
}

void CODBCTestView::InsertData()
{
	try
	{
		// DSN 정보를 이용하여 DB open
		BOOL bOpen = m_db.OpenEx("DSN=DBTest;SERVER=localhost\\sqlexpress01;PORT=1433;UID=sa;PWD=kimgopa;DATABASE=Test;");

		if ( bOpen )
		{
			//m_db.BeginTrans();

			try
			{
				m_db.ExecuteSQL("INSERT INTO [User] (Name, Mobile, Birthday, Gender) VALUES ('김고파', '010-2222-3333', '2020-12-03', 'f')");
			}
			catch ( CException *e )
			{
				e->ReportError();
			}
			//m_db.CommitTrans();
		}
		else
		{
			AfxMessageBox("DB Open Fail..");
		}
	}
	catch ( CException *e )
	{
		e->ReportError();
	}

	// 사용 후 CRecordset, CDatabase 순으로 종료
	if ( m_pRs->IsOpen() )
		m_pRs->Close();
	if ( m_db.IsOpen() )
		m_db.Close();
}

void CODBCTestView::UpdateData()
{
	try
	{
		// DSN 정보를 이용하여 DB open
		BOOL bOpen = m_db.OpenEx("DSN=DBTest;SERVER=localhost\\sqlexpress01;PORT=1433;UID=sa;PWD=kimgopa;DATABASE=Test;");

		if ( bOpen )
		{
			//m_db.BeginTrans();

			try
			{
				m_db.ExecuteSQL("UPDATE [User] SET Mobile='010-8888-8888' WHERE Name='김고파'");
			}
			catch ( CException *e )
			{
				e->ReportError();
			}
			//m_db.CommitTrans();
		}
		else
		{
			AfxMessageBox("DB Open Fail..");
		}
	}
	catch ( CException *e )
	{
		e->ReportError();
	}

	// 사용 후 CRecordset, CDatabase 순으로 종료
	if ( m_pRs->IsOpen() )
		m_pRs->Close();
	if ( m_db.IsOpen() )
		m_db.Close();
}

void CODBCTestView::DeleteData()
{
	try
	{
		// DSN 정보를 이용하여 DB open
		BOOL bOpen = m_db.OpenEx("DSN=DBTest;SERVER=localhost\\sqlexpress01;PORT=1433;UID=sa;PWD=kimgopa;DATABASE=Test;");

		if ( bOpen )
		{
			//m_db.BeginTrans();

			try
			{
				m_db.ExecuteSQL("DELETE FROM [User] WHERE Name='김고파'");
			}
			catch ( CException *e )
			{
				e->ReportError();
			}
			//m_db.CommitTrans();
		}
		else
		{
			AfxMessageBox("DB Open Fail..");
		}
	}
	catch ( CException *e )
	{
		e->ReportError();
	}

	// 사용 후 CRecordset, CDatabase 순으로 종료
	if ( m_pRs->IsOpen() )
		m_pRs->Close();
	if ( m_db.IsOpen() )
		m_db.Close();
}


// CODBCTestView 메시지 처리기

void CODBCTestView::OnBnClickedButtonInsert()
{
	InsertData();
	SelectData();
}

void CODBCTestView::OnBnClickedButtonUpdate()
{
	UpdateData();
	SelectData();
}

void CODBCTestView::OnBnClickedButtonDelete()
{
	DeleteData();
	SelectData();
}
