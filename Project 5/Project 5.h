
// Project 5.h : main header file for the Project 5 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CProject5App:
// See Project 5.cpp for the implementation of this class
//

class CProject5App : public CWinApp
{
public:
	CProject5App() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CProject5App theApp;
