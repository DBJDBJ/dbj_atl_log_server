/* (c) 2020 by dbj@dbj.org -- LICENSE_DBJ -- https://dbj.org/license_dbj/ */

#include "framework.h"

///KB: http://resources.esri.com/help/9.3/arcgisengine/com_cpp/COM/VCpp/ImportArcGISTypeLibs.htm

#define DBJ_LOG_TYPE_LIB "../server/dbjlogsvr.tlb"
#define DBJ_TYPE_LIB_NAMESPACE "dbjlog"

#import DBJ_LOG_TYPE_LIB          /* Type library to generate C++ wrappers */ \
  raw_interfaces_only,                             /* Don't add raw_ to method names        */ \
  raw_native_types,                                /* Don't map to DTC smart types          */ \
  rename_namespace(DBJ_TYPE_LIB_NAMESPACE),                                                    \
  named_guids,                                     /* Named guids and declspecs             */ \
  exclude("OLE_COLOR", "OLE_HANDLE", "VARTYPE")    /* Exclude conflicting types             */

/// KB: http://resources.esri.com/help/9.3/arcgisengine/com_cpp/COM/VCpp/SmartTypes.htm
/// KB: https://en.wikipedia.org/wiki/HRESULT
/// KB: https://docs.microsoft.com/en-us/windows/win32/com/using-macros-for-error-handling?redirectedfrom=MSDN
HRESULT log(const char* txt_)
{
	//constexpr GUID wotisthis = __uuidof(dbjlog::thelog);
	//constexpr bool b1 = dbj::win::equal_guids(wotisthis, wotisthis);

	dbjlog::IthelogPtr loggy ;

	/*
	if you do not register the server first, you will get
	onecore\com\combase\dcomrem\resolver.cxx(2491)\combase.dll!00007FF99BFA5FF6: (caller: 00007FF99BFA5F05) ReturnHr(2) tid(2d7c) 80040154 Class not registered
	*/

	VERIFY_HRESULT( loggy.CreateInstance(dbjlog::CLSID_thelog) ) ;

	loggy->put_logfilename(_bstr_t(L"logfile.log"));

	_bstr_t log_file_path ;
	VERIFY_HRESULT( loggy->get_logfilename( & log_file_path.GetBSTR() ) ) ;
	
	return S_OK;
}

