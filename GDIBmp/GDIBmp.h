
// GDIBmp.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols

#include <GdiPlus.h>
using namespace Gdiplus;
// CGDIBmpApp:
// See GDIBmp.cpp for the implementation of this class
//

class CGDIBmpApp : public CWinAppEx
{
public:
	CGDIBmpApp();

// Overrides
	public:
	virtual BOOL InitInstance();

// Implementation
	virtual int ExitInstance();
	DECLARE_MESSAGE_MAP()
	ULONG_PTR m_gdiplusToken;
};

extern CGDIBmpApp theApp;