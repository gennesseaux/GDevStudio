// GDevStudio.h : main header file for the GDevStudio application
//
#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

// Inclusions
#include "resource.h"       // main symbols

// Inclusions
#include "PluginLoader.h"

// Inclusions STL
#include <string>
#include <vector>

// Inclusions Poco
#include <Poco/Foundation.h>
#include <Poco/Path.h>


class CGDevStudioApp : public CBCGPWinApp
{
public:
	CGDevStudioApp();

	// Override from CBCGPWorkspace
	virtual void PreLoadState ();
	
	// Liste des générateurs de ressources
	std::vector<CPluginLoader::PluginDesc>& GetRessourcePlugins();
	// Liste des générateurs de classe
	std::vector<CPluginLoader::PluginDesc>& GetClassePlugins();
	// Plugin en fonction de son uuid
	CPluginLoader::PluginDesc GetPlugin(Poco::UUID uuid);

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

protected:
	CPluginLoader pluginLoader;
	std::vector<CPluginLoader::PluginDesc> vRessourcePlugins;
	std::vector<CPluginLoader::PluginDesc> vClassePlugins;
};

extern CGDevStudioApp theApp;