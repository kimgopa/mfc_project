
// ODBCTestDoc.h : CODBCTestDoc Ŭ������ �������̽�
//


#pragma once


class CODBCTestDoc : public CDocument
{
protected: // serialization������ ��������ϴ�.
	CODBCTestDoc();
	DECLARE_DYNCREATE(CODBCTestDoc)

// Ư���Դϴ�.
public:

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// �����Դϴ�.
public:
	virtual ~CODBCTestDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()
};


