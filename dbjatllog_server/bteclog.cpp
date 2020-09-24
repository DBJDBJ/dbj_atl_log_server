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
#include "bteclog.h"

#include "bteclog_i.c"
#include "thelog.h"


LONG CExeModule::Unlock()
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

/*
*/
enum 
{ 
	UnregServer_arg = 0, RegServer_arg = 1, cli_arguments_max_count = 2 
};

static const wchar_t* 
cli_arguments[cli_arguments_max_count] 
= { L"UnregServer", L"RegServer" };


/////////////////////////////////////////////////////////////////////////////
//
extern "C" int WINAPI wWinMain(HINSTANCE hInstance,
	HINSTANCE /*hPrevInstance*/, LPWSTR lpCmdLine, int /*nShowCmd*/)
{
	// WARNING: lpCmdLine is not NULL will NOT contain the app name
	if (!lpCmdLine)
		// taken from here lpCmdLine  will contain the app name
		lpCmdLine = GetCommandLineW();

	HRESULT hr_esult_ = CoInitializeEx(NULL, COINIT_MULTITHREADED);
	_ASSERTE(SUCCEEDED(hr_esult_));

	_Module.Init(ObjectMap, hInstance);
	_Module.dwThreadID = GetCurrentThreadId();

	int int_result_ = 0;
	BOOL proceed_ = TRUE;

	if (wcsstr(lpCmdLine, cli_arguments[UnregServer_arg]) != NULL)
	{
		__debugbreak();

		hr_esult_ = _Module.UpdateRegistryFromResource(IDR_Bteclog, FALSE);
		_ASSERTE(SUCCEEDED(hr_esult_));
		int_result_ = _Module.UnregisterServer();
		proceed_ = FALSE;
	}

	if (wcsstr(lpCmdLine, cli_arguments[RegServer_arg]) != NULL)
	{
		__debugbreak();

		hr_esult_ = _Module.UpdateRegistryFromResource(IDR_Bteclog, TRUE);
		_ASSERTE(SUCCEEDED(hr_esult_));
		int_result_ = _Module.RegisterServer(TRUE);
		proceed_ = TRUE; // dbj changed to true
	}

	if (proceed_)
	{
		hr_esult_ = _Module.RegisterClassObjects(CLSCTX_LOCAL_SERVER,
			REGCLS_MULTIPLEUSE);

		_ASSERTE(SUCCEEDED(hr_esult_));

		MSG msg;
		while (GetMessage(&msg, 0, 0, 0))
			DispatchMessage(&msg);

		_Module.RevokeClassObjects();
	}

	CoUninitialize();
	return int_result_;
}
