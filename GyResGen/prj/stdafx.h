// stdafx.h�: fichier Include pour les fichiers Include syst�me standard,
// ou les fichiers Include sp�cifiques aux projets qui sont utilis�s fr�quemment,
// et sont rarement modifi�s

#pragma once

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // Exclure les en-t�tes Windows rarement utilis�s
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // certains constructeurs CString seront explicites

#include <afxwin.h>         // composants MFC principaux et standard
#include <afxext.h>         // extensions MFC

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxole.h>         // classes OLE MFC
#include <afxodlgs.h>       // classes de bo�te de dialogue OLE MFC
#include <afxdisp.h>        // Classes MFC Automation
#endif // _AFX_NO_OLE_SUPPORT

#ifndef _AFX_NO_DB_SUPPORT
#include <afxdb.h>                      // classes de base de donn�es ODBC MFC
#endif // _AFX_NO_DB_SUPPORT

#ifndef _AFX_NO_DAO_SUPPORT
#include <afxdao.h>                     // classes de base de donn�es DAO MFC
#endif // _AFX_NO_DAO_SUPPORT

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>					// Prise en charge MFC pour les contr�les communs Internet Explorer�4
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>                     // Prise en charge des MFC pour les contr�les communs Windows
#endif // _AFX_NO_AFXCMN_SUPPORT

// STL
#include <string>

//
#include <vld.h>

// BCGPro Control Bar
#define _BCGCBPRO_STATIC_
#include <BCGCBProInc.h>
#include <afxcontrolbars.h>

// Linkage automatique avec les lib
#pragma comment(lib, "DObject.lib")
#pragma comment(lib, "Outils.lib")
#pragma comment(lib, "SQLite.lib")
#pragma comment(lib, "RcReader.lib")
#pragma comment(lib, "GDevStudioApi.lib")
#pragma comment(lib, "GDevStudioModulesManager.lib")

// Transforme un CString en std::string
inline std::string ToStdString(__in CString &cString)
{
#ifdef UNICODE
     std::wstring w;
     w = cString;
     return std::string(w.begin(), w.end());
#else
     return cString;
#endif
}
// Transforme un std::string en CString
inline CString ToString(__in std::string &string)
{
	return CString(string.c_str());
}


