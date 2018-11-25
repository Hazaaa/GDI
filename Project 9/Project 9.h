
// Project 9.h : main header file for the Project 9 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CProject9App:
// See Project 9.cpp for the implementation of this class
//

class CProject9App : public CWinApp
{
public:
	CProject9App() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CProject9App theApp;
