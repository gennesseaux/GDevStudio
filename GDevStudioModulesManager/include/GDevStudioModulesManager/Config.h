///////////////////////////////////////////////////////////////////////////////
// GDEVSTUDIOMM Config file                                                 //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
#ifndef GDEVSTUDIOMM_CONFIG_H
#define GDEVSTUDIOMM_CONFIG_H



// ------------------------------------------------------------------------- //
// Platform utilisée
// ------------------------------------------------------------------------- //
#if defined(WINAPI_FAMILY) && (WINAPI_FAMILY == WINAPI_FAMILY_APP)
  #define GDEVSTUDIOMM_WINRT 1
#elif defined(WIN32) || defined(_WIN32)
  #define GDEVSTUDIOMM_WIN32 1
#else
  #define GDEVSTUDIOMM_LINUX 1
#endif


// ------------------------------------------------------------------------- //
// Decides whether symbols are imported from a dll (client app) or exported to
// a dll (GDEVSTUDIOMM library). The GDEVSTUDIOMM_SOURCE symbol is defined by
// all source files of the library, so you don't have to worry about a thing.
// ------------------------------------------------------------------------- //
#if defined(_MSC_VER)

  #if defined(GDEVSTUDIOMM_STATICLIB)
    #define GDEVSTUDIOMM_API
  #else
    #if defined(GDEVSTUDIOMM_SOURCE)
      // If we are building the DLL, export the symbols tagged like this
      #define GDEVSTUDIOMM_API __declspec(dllexport)
    #else
      // If we are consuming the DLL, import the symbols tagged like this
      #define GDEVSTUDIOMM_API __declspec(dllimport)
    #endif
  #endif

#else

  #error Unknown compiler, please implement shared library macros

#endif


// ------------------------------------------------------------------------- //
// Ensure that when building an application (or another DLL) using this DLL,
// the appropriate .LIB file will automatically be used when linking.
// ------------------------------------------------------------------------- //
#ifndef GDEVSTUDIOMM_SOURCE
	#ifdef _DEBUG
		#pragma comment(lib, "GDevStudioModulesManager.lib")
	#else
		#pragma comment(lib, "GDevStudioModulesManager.lib")
	#endif
#endif

#endif // GDEVSTUDIOMM_CONFIG_H
