///////////////////////////////////////////////////////////////////////////////
// GDevStudioApi Config file                                                 //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
#ifndef GDEVSTUDIOAPI_CONFIG_H
#define GDEVSTUDIOAPI_CONFIG_H



// ------------------------------------------------------------------------- //
// Platform utilisée
// ------------------------------------------------------------------------- //
#if defined(WINAPI_FAMILY) && (WINAPI_FAMILY == WINAPI_FAMILY_APP)
  #define GDEVSTUDIOAPI_WINRT 1
#elif defined(WIN32) || defined(_WIN32)
  #define GDEVSTUDIOAPI_WIN32 1
#else
  #define GDEVSTUDIOAPI_LINUX 1
#endif


// ------------------------------------------------------------------------- //
// Decides whether symbols are imported from a dll (client app) or exported to
// a dll (GDEVSTUDIOAPI library). The GDEVSTUDIOAPI_SOURCE symbol is defined by
// all source files of the library, so you don't have to worry about a thing.
// ------------------------------------------------------------------------- //
#if defined(_MSC_VER)

  #if defined(GDEVSTUDIOAPI_STATICLIB)
    #define GDEVSTUDIOAPI_API
  #else
    #if defined(GDEVSTUDIOAPI_SOURCE)
      // If we are building the DLL, export the symbols tagged like this
      #define GDEVSTUDIOAPI_API __declspec(dllexport)
    #else
      // If we are consuming the DLL, import the symbols tagged like this
      #define GDEVSTUDIOAPI_API __declspec(dllimport)
    #endif
  #endif

#else

  #error Unknown compiler, please implement shared library macros

#endif


// ------------------------------------------------------------------------- //
// Ensure that when building an application (or another DLL) using this DLL,
// the appropriate .LIB file will automatically be used when linking.
// ------------------------------------------------------------------------- //
#ifndef GDEVSTUDIOAPI_SOURCE
	#ifdef _DEBUG
		#pragma comment(lib, "GDevStudioApi.lib")
	#else
		#pragma comment(lib, "GDevStudioApi.lib")
	#endif
#endif


// ------------------------------------------------------------------------- //
// Inclusions utilisées pas la majorité des classes
// ------------------------------------------------------------------------- //
// Inclusions
#include <windows.h>
#include <assert.h>
// Inclusions STL
#include <string>
// Inclusions
#include <GDevStudioApi/SQLiteSource.h>
// Inclusions Outils
#include <Outils/StringTools.h>
// Inclusions Poco
#include <Poco/Foundation.h>
#include <Poco/File.h>
#include <Poco/Logger.h>
#include <Poco/NumberFormatter.h>
#include <Poco/Path.h>
#include <Poco/UUID.h>
// Inclusions SQLite
#include <SQLite/SQLiteSource.h>


#endif // GDEVSTUDIOAPI_CONFIG_H
