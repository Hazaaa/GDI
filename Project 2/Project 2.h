
// Project 2.h : main header file for the Project 2 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CProject2App:
// See Project 2.cpp for the implementation of this class
//

class CProject2App : public CWinApp
{
public:
	CProject2App();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CProject2App theApp;
