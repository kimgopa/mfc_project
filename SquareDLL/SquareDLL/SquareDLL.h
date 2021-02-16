// SquareDLL.h : main header file for the SquareDLL DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CSquareDLLApp
// See SquareDLL.cpp for the implementation of this class
//

class CSquareDLLApp : public CWinApp
{
public:
	CSquareDLLApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
