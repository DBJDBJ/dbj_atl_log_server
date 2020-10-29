/* (c) 2020 by dbj@dbj.org -- LICENSE_DBJ -- https://dbj.org/license_dbj/ */

#include "framework.h"

///KB: http://resources.esri.com/help/9.3/arcgisengine/com_cpp/COM/VCpp/ImportArcGISTypeLibs.htm

// #define DBJ_MSHTML_TYPE_LIB "mshtml.tlb"
#define DBJ_MSHTML_TYPE_LIB "Shdocvw.dll"
#define DBJ_TYPE_LIB_NAMESPACE "dbj_mshtml"

#if 1
#import DBJ_MSHTML_TYPE_LIB                        /* Type library to generate C++ wrappers */ \
  rename_namespace(DBJ_TYPE_LIB_NAMESPACE),                                                    \
  named_guids                                     /* Named guids and declspecs             */ 
#endif // 1

/// 
/// KB: http://resources.esri.com/help/9.3/arcgisengine/com_cpp/COM/VCpp/SmartTypes.htm
/// KB: https://en.wikipedia.org/wiki/HRESULT
/// KB: https://docs.microsoft.com/en-us/windows/win32/com/using-macros-for-error-handling?redirectedfrom=MSDN
/// 
extern "C" HRESULT mshtml_client(const char* url_ )
{
	dbj_mshtml::IWebBrowser2 * browser_;

	// using namespace MSHTML;
	/*
	we could create the log point in the constructor
	but that is agains the ATL advice and again my advice too
	we have no C++ exception in this /kernel build thus
	we have no error signaling from the constructor
	it is better to use CreateInstance as bellow and check
	for the HRESULT
	*/
#if 0
	dbj_mshtml::IHTMLWindow2Ptr html_window_ptr_;

	VERIFY_S_OK(html_window_ptr_.CreateInstance( __uuidof(dbj_mshtml::HTMLWindow2)) ) ;

	VERIFY_S_OK(html_window_ptr_->navigate(_bstr_t(url_).GetBSTR()));	
#endif // 0
	/*
	if you do not register the server first, you will get
	onecore\com\combase\dcomrem\resolver.cxx(2491)\combase.dll!00007FF99BFA5FF6: (caller: 00007FF99BFA5F05) ReturnHr(2) tid(2d7c) 80040154 Class not registered

	or the server needs restarting ... which is a conceptual problem , why does it stop?
	trhat is not good for unattended long running server side components
	*/

//	VERIFY_S_OK( loggy.CreateInstance(dbj_mshtml::CLSID_thelog) ) ;

	return S_OK;
}

