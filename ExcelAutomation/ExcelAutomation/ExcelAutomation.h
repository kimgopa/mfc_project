
// ExcelAutomation.h : ExcelAutomation ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.


// CExcelAutomationApp:
// �� Ŭ������ ������ ���ؼ��� ExcelAutomation.cpp�� �����Ͻʽÿ�.
//

class CExcelAutomationApp : public CWinApp
{
public:
	CExcelAutomationApp();


// �������Դϴ�.
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// �����Դϴ�.
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CExcelAutomationApp theApp;
