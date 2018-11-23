
// Project 6.h : main header file for the Project 6 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CProject6App:
// See Project 6.cpp for the implementation of this class
//

class CProject6App : public CWinApp
{
public:
	CProject6App() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CProject6App theApp;
