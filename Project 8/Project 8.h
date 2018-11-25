
// Project 8.h : main header file for the Project 8 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CProject8App:
// See Project 8.cpp for the implementation of this class
//

class CProject8App : public CWinApp
{
public:
	CProject8App() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CProject8App theApp;
