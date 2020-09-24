
///KB: http://resources.esri.com/help/9.3/arcgisengine/com_cpp/COM/VCpp/ImportArcGISTypeLibs.htm

#define DBJ_LOG_TYPE_LIB "../dbjatllog_server/bteclog.tlb"
#define DBJ_TYPE_LIB_NAMESPACE "dbjlog"

#import "../dbjatllog_server/bteclog.tlb"          /* Type library to generate C++ wrappers */ \
  raw_interfaces_only,                             /* Don't add raw_ to method names        */ \
  raw_native_types,                                /* Don't map to DTC smart types          */ \
  rename_namespace(DBJ_TYPE_LIB_NAMESPACE),                                                    \
  named_guids,                                     /* Named guids and declspecs             */ \
  exclude("OLE_COLOR", "OLE_HANDLE", "VARTYPE")    /* Exclude conflicting types             */

///  KB: http://resources.esri.com/help/9.3/arcgisengine/com_cpp/COM/VCpp/SmartTypes.htm
/// KB: https://en.wikipedia.org/wiki/HRESULT
/// KB: https://docs.microsoft.com/en-us/windows/win32/com/using-macros-for-error-handling?redirectedfrom=MSDN
HRESULT log(const char* txt_)
{
	dbjlog::IthelogPtr loggy ;

	// WARNING: CoInitialize() must be called before any COM API is used
	// CLSID_thelog
	/*
	if you do not register the server first, you will get
	onecore\com\combase\dcomrem\resolver.cxx(2491)\combase.dll!00007FF99BFA5FF6: (caller: 00007FF99BFA5F05) ReturnHr(2) tid(2d7c) 80040154 Class not registered
	on using the __uuidof() as bellow
	*/
	auto wotisthis = __uuidof(dbjlog::thelog);
	HRESULT hr = loggy.CreateInstance(dbjlog::CLSID_thelog);
	if (FAILED(hr)) return hr;
	// HRESULT_CODE(hr) can turn that into win32 error code

	assert( loggy );

	loggy->put_logfilename(_bstr_t(L"logfile.log"));

	_bstr_t log_file_path ;
	hr = loggy->get_logfilename( & log_file_path.GetBSTR() );
	if (FAILED(hr)) return hr;
	
	return S_OK;
}

