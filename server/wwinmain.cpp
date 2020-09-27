/*

(c) 2020 by dbj@dbj.org -- LICENSE_DBJ -- https://dbj.org/license_dbj/

To build this with /kernel make sure _CPPUNWIND is undefined

citation: "..._CPPUNWIND Defined as 1 if one or more of the / GX(Enable Exception Handling),
/ clr(Common Language Runtime Compilation),
or /EH(Exception Handling Model)
compiler options are set. Otherwise, undefined..."

For me, removing any /EH was enough. Just then this will work: /kernel  /D_ATL_NO_EXCEPTIONS

*/

#include "stdafx.h"
#include "resource.h"
#include "initguid.h"
#include "dbjlogsvr.h"

#include "dbjlogsvr_i.c"
#include "thelog.h"


LONG CExeModule::Unlock() noexcept
{
	LONG l = CComModule::Unlock();
	if (l == 0)
	{
#if _WIN32_WINNT >= 0x0400
		if (CoSuspendClassObjects() == S_OK)
			PostThreadMessage(dwThreadID, WM_QUIT, 0, 0);
#else
		PostThreadMessage(dwThreadID, WM_QUIT, 0, 0);
#endif
	}
	return l;
}

CExeModule _Module;

BEGIN_OBJECT_MAP(ObjectMap)
	OBJECT_ENTRY(CLSID_thelog, Cthelog)
END_OBJECT_MAP()

/////////////////////////////////////////////////////////////////////////////
enum
{ 
	UnregServer_arg = 0, RegServer_arg = 1, cli_arguments_max_count = 2 
};

static const wchar_t* 
cli_arguments[cli_arguments_max_count] 
= { L"UnregServer", L"RegServer" };
/////////////////////////////////////////////////////////////////////////////

namespace {

	static void* log_start(void*)
	{
		dbj_simple_log_startup(this_app_full_path_a()); return 0;
	}
	static void* log_end(void*)
	{
		dbj_log_finalize(); return 0;
	}

	static dbj::start_stop<log_start, log_end > dbj_simple_log_start_stop_;	
	
	static void* com_start(void*)
	{
#if ( defined(_WIN32_DCOM)  || defined(_ATL_FREE_THREADED))
		HRESULT result = ::CoInitializeEx(NULL, COINIT_MULTITHREADED);
#else
		HRESULT result = ::CoInitialize(NULL);
#endif
		DBJ_ASSERT( S_OK == result );

		return 0;
	}
	static void* com_finish(void*)
	{
		::CoUninitialize(); return 0;
	}

	static dbj::start_stop<com_start, com_finish > dbj_com_start_stop_;
}

/////////////////////////////////////////////////////////////////////////////
extern "C" int WINAPI wWinMain(HINSTANCE hInstance,
	HINSTANCE /*hPrevInstance*/, LPWSTR lpCmdLine, int /*nShowCmd*/)
{
	// WARNING: if lpCmdLine is not NULL it will NOT contain the app name
	if (!lpCmdLine)
		// taken from here lpCmdLine  **might** contain the app name
		lpCmdLine = GetCommandLineW();

	if (lpCmdLine) dbj_log_info("%S", lpCmdLine);

	_Module.Init(ObjectMap, hInstance);
	_Module.dwThreadID = GetCurrentThreadId();

	int int_result_ = 0;
	BOOL proceed_ = TRUE;

	if (wcsstr(lpCmdLine, cli_arguments[UnregServer_arg]) != NULL)
	{
		VERIFY_HRESULT( _Module.UpdateRegistryFromResource(IDR_Bteclog, FALSE) ) ;
		int_result_ = _Module.UnregisterServer();
		proceed_ = FALSE;
		dbj_log_info("%s","UNRegistered OK");
	}

	if (wcsstr(lpCmdLine, cli_arguments[RegServer_arg]) != NULL)
	{
		VERIFY_HRESULT( _Module.UpdateRegistryFromResource(IDR_Bteclog, TRUE) ) ;

		int_result_ = _Module.RegisterServer(TRUE);
		proceed_ = FALSE; 
		dbj_log_info("%s","Registered OK");
	}

	if (proceed_)
	{
		HRESULT hr_ = _Module.RegisterClassObjects(CLSCTX_LOCAL_SERVER,	REGCLS_MULTIPLEUSE) ;

		if (SUCCEEDED(hr_))
			dbj_log_info("%s","Server is running. Before stoping it call it from a command line with the 'UnregServer' single argument.");
		else
			dbj_log_info("%s", "For some reason RegisterClassObjects() on module has failed? Still I will attempt to run. ");

		MSG msg;
		while (GetMessage(&msg, 0, 0, 0))
			DispatchMessage(&msg);

		_Module.RevokeClassObjects();
	}
	else {
		dbj_log_info("%s","Control mesagess where handled. To run the server repeat the command without arguments. ");
	}

	return int_result_;
}
