
// ModalTest.h : main header file for the ModalTest application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CModalTestApp:
// See ModalTest.cpp for the implementation of this class
//

class CModalTestApp : public CWinApp
{
public:
	CModalTestApp() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CModalTestApp theApp;
