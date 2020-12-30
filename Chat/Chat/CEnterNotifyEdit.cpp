// CEnterNotifyEdit.cpp: 구현 파일
//

#include "pch.h"
#include "Chat.h"
#include "CEnterNotifyEdit.h"


// CEnterNotifyEdit

IMPLEMENT_DYNAMIC(CEnterNotifyEdit, CEdit)

CEnterNotifyEdit::CEnterNotifyEdit()
{

}

CEnterNotifyEdit::~CEnterNotifyEdit()
{
}


BEGIN_MESSAGE_MAP(CEnterNotifyEdit, CEdit)
	ON_WM_CHAR()
END_MESSAGE_MAP()



// CEnterNotifyEdit 메시지 처리기



void CEnterNotifyEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == VK_RETURN)
		GetParent()->SendMessage(WM_COMMAND, ID_ENTERKEY, 0);

	CEdit::OnChar(nChar, nRepCnt, nFlags);
}
