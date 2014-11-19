// GDevStudio.h : main header file for the GDevStudio application
//
#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

// Inclusions
#include "resource.h"       // main symbols

// Inclusions
#include <Poco/Path.h>


class CGDevStudioApp : public CBCGPWinApp
{
public:
	CGDevStudioApp();

	// Override from CBCGPWorkspace
	virtual void PreLoadState ();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

	// Implementation
	void OnAppAbout();
	
	DECLARE_MESSAGE_MAP()

protected:
	// map to the following for file new/open
	void OnFileNew();
	void OnFileOpen();

	void Test();
};

extern CGDevStudioApp theApp;