// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently,
// but are changed infrequently

#pragma once

#ifndef _SECURE_ATL
#define _SECURE_ATL 1
#endif

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers
#endif

// Si vous incluez SDKDDKVer.h, cela définit la dernière plateforme Windows disponible.
// Si vous souhaitez générer votre application pour une plateforme Windows précédente, incluez WinSDKVer.h et
// définissez la macro _WIN32_WINNT à la plateforme que vous souhaitez prendre en charge avant d'inclure SDKDDKVer.h.
#include <SDKDDKVer.h>

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS	// some CString constructors will be explicit

// turns off MFC's hiding of some common and often safely ignored warning messages
#define _AFX_ALL_WARNINGS

#include <afxwin.h>				// composants MFC principaux et standard
#include <afxext.h>				// extensions MFC

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // Prise en charge MFC pour les contrôles communs Internet Explorer 4
#endif

#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // Prise en charge des MFC pour les contrôles communs Windows
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
#pragma comment(lib, "SQLite.lib")
#pragma comment(lib, "RcReader.lib")
#pragma comment(lib, "GDevStudioApi.lib")
#pragma comment(lib, "GDevStudioModulesManager.lib")

//
inline void SetFontBold(CWnd* pWnd)
{
	CFont* font = pWnd->GetFont();
	LOGFONT logFont;
	font->GetLogFont(&logFont);
	logFont.lfWeight = FW_BOLD;
	HFONT hFontBold = CreateFontIndirect(&logFont);
	pWnd->SendMessage(WM_SETFONT, (int)hFontBold, true);
}
inline void SetFontUnderline(CWnd* pWnd)
{
	CFont* font = pWnd->GetFont();
	LOGFONT logFont;
	font->GetLogFont(&logFont);
	logFont.lfUnderline = TRUE;
	HFONT hFontBold = CreateFontIndirect(&logFont);
	pWnd->SendMessage(WM_SETFONT, (int)hFontBold, true);
}
inline void SetFontBoldUnderline(CWnd* pWnd)
{
	CFont* font = pWnd->GetFont();
	LOGFONT logFont;
	font->GetLogFont(&logFont);
	logFont.lfWeight = FW_BOLD;
	logFont.lfUnderline = TRUE;
	HFONT hFontBold = CreateFontIndirect(&logFont);
	pWnd->SendMessage(WM_SETFONT, (int)hFontBold, true);
}

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
// 
inline void SetCWndWindowText(__in CWnd* pWnd, __in std::string str)
{
	pWnd->SetWindowText(ToString(str));
}
// Retourne le CString obtenu par GetWindowText sur un CWnd*
inline CString GetCWndWindowText(__in CWnd* pWnd)
{
	CString sTexte;
	pWnd->GetWindowText(sTexte);
	return sTexte;
}
// Retourne le CString obtenu par GetWindowText sur un CWnd*
inline std::string GetCWndWindowTextString(__in CWnd* pWnd)
{
	return ToStdString(GetCWndWindowText(pWnd));
}
// Retourne le CString obtenu par GetWindowText su un CWnd*
inline int GetCWndWindowTextLength(__in CWnd* pWnd)
{
	return GetCWndWindowText(pWnd).GetLength();
}








#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_IA64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='ia64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
