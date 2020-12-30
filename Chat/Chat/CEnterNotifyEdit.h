#pragma once


// CEnterNotifyEdit

class CEnterNotifyEdit : public CEdit
{
	DECLARE_DYNAMIC(CEnterNotifyEdit)

public:
	CEnterNotifyEdit();
	virtual ~CEnterNotifyEdit();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
};


