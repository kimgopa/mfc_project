
// ODBCTest.h : ODBCTest ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.


// CODBCTestApp:
// �� Ŭ������ ������ ���ؼ��� ODBCTest.cpp�� �����Ͻʽÿ�.
//

class CODBCTestApp : public CWinApp
{
public:
	CODBCTestApp();


// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CODBCTestApp theApp;
