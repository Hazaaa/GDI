
// Project 3.h : main header file for the Project 3 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CProject3App:
// See Project 3.cpp for the implementation of this class
//

class CProject3App : public CWinApp
{
public:
	CProject3App() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CProject3App theApp;
