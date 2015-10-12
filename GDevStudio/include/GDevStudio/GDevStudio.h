// GDevStudio.h : main header file for the GDevStudio application
//
#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

// Inclusions
#include "resource.h"       // main symbols

// Inclusions STL
#include <string>
#include <vector>

// Inclusions Poco
#include <Poco/Foundation.h>
#include <Poco/Path.h>

// Inclusions
#include "GDevStudioModulesManager/ModulesManager.h"
#include "GDevStudioModulesManager/ModulesEvents.h"


class CGDevStudioApp : public CBCGPWinApp
{
public:
	CGDevStudioApp();

	// Override from CBCGPWorkspace
	virtual void PreLoadState ();
	
	// Gestionnaire de modules
	GDSMM::CModulesManager* ModulesManager();
	// Gestion des évènements
	GDSMM::CModulesEvents* ModulesEvents();

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

protected:
	// Gestionnaire de modules
	GDSMM::CModulesManager& _ModulesManager = GDSMM::CModulesManager::ModulesManager();
	// Gestion des évènements
	GDSMM::CModulesEvents& _ModulesEvents = GDSMM::CModulesEvents::ModulesEvents();
};

extern CGDevStudioApp theApp;