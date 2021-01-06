
// ODBCTestView.cpp : CODBCTestView Ŭ������ ����
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

// CODBCTestView ����/�Ҹ�

CODBCTestView::CODBCTestView()
	: CFormView(CODBCTestView::IDD)
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.

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
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CFormView::PreCreateWindow(cs);
}

void CODBCTestView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

	// add list column
	m_ctrlList.InsertColumn(0, "�̸�", LVCFMT_LEFT, 80);
	m_ctrlList.InsertColumn(1, "��ȭ��ȣ", LVCFMT_LEFT, 150);
	m_ctrlList.InsertColumn(2, "����", LVCFMT_LEFT, 150);
	m_ctrlList.InsertColumn(3, "����", LVCFMT_LEFT, 80);

	SelectData();	// db ��ȸ�Ͽ� list�� ������
}


// CODBCTestView ����

#ifdef _DEBUG
void CODBCTestView::AssertValid() const
{
	CFormView::AssertValid();
}

void CODBCTestView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CODBCTestDoc* CODBCTestView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CODBCTestDoc)));
	return (CODBCTestDoc*)m_pDocument;
}
#endif //_DEBUG


void CODBCTestView::SelectData()
{
	try
	{
		// DSN ������ �̿��Ͽ� DB open
		BOOL bOpen = m_db.OpenEx("DSN=DBTest;SERVER=localhost\\sqlexpress01;PORT=1433;UID=sa;PWD=kimgopa;DATABASE=Test;");

		if ( bOpen )
		{
			// recordset�� �޾ƿ� CRecordset ��ü
			m_pRs = new CRecordset( &m_db );

			// query�� ���� recordset�� �޾ƿ�
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
					// MoveFirst() : ù ��° row�� �̵�
					// IsEOF() : ���簡 �������̸� 1 ����
					// MoveNext() : ���� row�� �̵�
					for ( m_pRs->MoveFirst(); !m_pRs->IsEOF(); m_pRs->MoveNext() )
					{
						// ��ȸ�� ���̺��� Į�� ��
						int iFieldCnt = m_pRs->GetODBCFieldCount();

						for ( int iCol = 0; iCol < iFieldCnt; iCol++ )
						{
							//m_pRs->SetAbsolutePosition( iRow );
							// iCol��°�� �ʵ� ���� �о� strData�� �־���
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

	// ��� �� CRecordset, CDatabase ������ ����
	if ( m_pRs->IsOpen() )
		m_pRs->Close();
	if ( m_db.IsOpen() )
		m_db.Close();
}

void CODBCTestView::InsertData()
{
	try
	{
		// DSN ������ �̿��Ͽ� DB open
		BOOL bOpen = m_db.OpenEx("DSN=DBTest;SERVER=localhost\\sqlexpress01;PORT=1433;UID=sa;PWD=kimgopa;DATABASE=Test;");

		if ( bOpen )
		{
			//m_db.BeginTrans();

			try
			{
				m_db.ExecuteSQL("INSERT INTO [User] (Name, Mobile, Birthday, Gender) VALUES ('�����', '010-2222-3333', '2020-12-03', 'f')");
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

	// ��� �� CRecordset, CDatabase ������ ����
	if ( m_pRs->IsOpen() )
		m_pRs->Close();
	if ( m_db.IsOpen() )
		m_db.Close();
}

void CODBCTestView::UpdateData()
{
	try
	{
		// DSN ������ �̿��Ͽ� DB open
		BOOL bOpen = m_db.OpenEx("DSN=DBTest;SERVER=localhost\\sqlexpress01;PORT=1433;UID=sa;PWD=kimgopa;DATABASE=Test;");

		if ( bOpen )
		{
			//m_db.BeginTrans();

			try
			{
				m_db.ExecuteSQL("UPDATE [User] SET Mobile='010-8888-8888' WHERE Name='�����'");
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

	// ��� �� CRecordset, CDatabase ������ ����
	if ( m_pRs->IsOpen() )
		m_pRs->Close();
	if ( m_db.IsOpen() )
		m_db.Close();
}

void CODBCTestView::DeleteData()
{
	try
	{
		// DSN ������ �̿��Ͽ� DB open
		BOOL bOpen = m_db.OpenEx("DSN=DBTest;SERVER=localhost\\sqlexpress01;PORT=1433;UID=sa;PWD=kimgopa;DATABASE=Test;");

		if ( bOpen )
		{
			//m_db.BeginTrans();

			try
			{
				m_db.ExecuteSQL("DELETE FROM [User] WHERE Name='�����'");
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

	// ��� �� CRecordset, CDatabase ������ ����
	if ( m_pRs->IsOpen() )
		m_pRs->Close();
	if ( m_db.IsOpen() )
		m_db.Close();
}


// CODBCTestView �޽��� ó����

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
