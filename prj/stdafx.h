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

// Modify the following defines if you have to target a platform prior to the ones specified below.
// Refer to MSDN for the latest info on corresponding values for different platforms.
#ifndef WINVER				// Allow use of features specific to Windows XP or later.
#define WINVER 0x0501		// Change this to the appropriate value to target other versions of Windows.
#endif

#ifndef _WIN32_WINNT		// Allow use of features specific to Windows XP or later.                   
#define _WIN32_WINNT 0x0501	// Change this to the appropriate value to target other versions of Windows.
#endif						

#ifndef _WIN32_WINDOWS		// Allow use of features specific to Windows 98 or later.
#define _WIN32_WINDOWS 0x0410 // Change this to the appropriate value to target Windows Me or later.
#endif

#ifndef _WIN32_IE			// Allow use of features specific to IE 6.0 or later.
#define _WIN32_IE 0x0600	// Change this to the appropriate value to target other versions of IE.
#endif

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS	// some CString constructors will be explicit

// turns off MFC's hiding of some common and often safely ignored warning messages
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions





#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

// STL
#include <string>

// BCGPro Control Bar
#define _BCGCBPRO_STATIC_
#include <BCGCBProInc.h>
#include "BCGPDialog.h"
#include <afxcontrolbars.h>

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
inline std::string ToStdString(__in CString cString)
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
inline CString ToString(__in std::string string)
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
