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

#define DBJ_SHORT_LIVED_SERVER ;

LONG CExeModule::Unlock() noexcept
{
	LONG l = CComModule::Unlock();
	if (l == 0)
	{
#ifdef DBJ_SHORT_LIVED_SERVER
		if (CoSuspendClassObjects() == S_OK)
		{
			dbj_log_info("Stopping. WM_QUIT passed.");
			PostThreadMessage(dwThreadID, WM_QUIT, 0, 0);
	     }
#else  // ! DBJ_SHORT_LIVED_SERVER
		dbj_log_info("Proceeding. WM_QUIT *not* passed.");
#endif // ! DBJ_SHORT_LIVED_SERVER
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
extern "C" int WINAPI program (HINSTANCE hInstance,
	HINSTANCE /*hPrevInstance*/, LPWSTR lpCmdLine, int /*nShowCmd*/)
{
	// WARNING: if lpCmdLine is not NULL it will NOT contain the app name
	if (!lpCmdLine)
		// taken from here lpCmdLine  **might** contain the app name
		lpCmdLine = GetCommandLineW();

	if (lpCmdLine) dbj_log_info("Command line arguments are: %S", lpCmdLine);

	_Module.Init(ObjectMap, hInstance);
	_Module.dwThreadID = GetCurrentThreadId();

	int int_result_ = 0;
	BOOL proceed_ = TRUE;

	if (wcsstr(lpCmdLine, cli_arguments[UnregServer_arg]) != NULL)
	{
		VERIFY_HRESULT( _Module.UpdateRegistryFromResource(IDR_Bteclog, FALSE) ) ;
		int_result_ = _Module.UnregisterServer();
		proceed_ = FALSE; // after de registration we will exit
		dbj_log_info("%s","UNRegistered OK");
	}

	if (wcsstr(lpCmdLine, cli_arguments[RegServer_arg]) != NULL)
	{
		VERIFY_HRESULT( _Module.UpdateRegistryFromResource(IDR_Bteclog, TRUE) ) ;

		int_result_ = _Module.RegisterServer(TRUE);
		proceed_ = TRUE;  // after registration we proceed to server running state
		dbj_log_info("%s","Registered OK");
	}

	// what happens if we run from the command line server exe to which we have given UnregServer
	// in the previous run?
	// peraps we should read the registry to find out if server is registered?
	// or the RegisterClassObjects bellow will fail in server is not registered?

	if (! proceed_){
		dbj_log_info("%s", "Server is un registered. Exiting...");
		return EXIT_SUCCESS;
	}
		HRESULT hr_ = _Module.RegisterClassObjects(CLSCTX_LOCAL_SERVER,	REGCLS_MULTIPLEUSE) ;

		if (SUCCEEDED(hr_))
			dbj_log_info("%s","Server is running. Before stoping it call it from a command line with the 'UnregServer' single argument.");
		else
			dbj_log_info("%s", "For some reason RegisterClassObjects() on module has failed? Still I will attempt to run. ");

		MSG msg;
		BOOL bRet;

		while (1)
		{
			bRet = GetMessage(&msg, NULL, 0, 0);

			if (bRet > 0)  // (bRet > 0 indicates a message that must be processed.)
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			else if (bRet < 0)  // (bRet == -1 indicates an error.)
			{
				_com_error cer(_com_error::WCodeToHRESULT( (WORD)GetLastError() ) );

				dbj_log_error("Error in the main message loop -- %S", cer.ErrorMessage() );
			}
			else  // (bRet == 0 indicates "exit program".)
			{
				break;
			}
		}
		return (int)msg.wParam;
}
