
// Project 7.h : main header file for the Project 7 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CProject7App:
// See Project 7.cpp for the implementation of this class
//

class CProject7App : public CWinApp
{
public:
	CProject7App() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CProject7App theApp;
