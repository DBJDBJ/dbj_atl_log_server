#pragma once

// DBJ FW requirement
extern "C" {
	static const char* DBJ_APP_NAME = "DBJ COM LOG Server";
	static const char* DBJ_APP_VERSION = "1.0.0";
}


// remember to link in the library "dbj_simplelog.lib"
// easy way: #pragma comment(lib, "dbj_simplelog.lib")
// where the lib has to be on the path
#include "../dbj--simplelog/dbj_simple_log.h"

#include "../shared_items/win_guid_compare.h"
#include "../shared_items/windows_includer.h"
#include "../shared_items/win_dump_generator.h"

#ifndef _KERNEL_MODE
#include "../shared_items/dbj_start_stop.h"
#endif

#include "../shared_items/hresult_verify.h"

#ifndef STRICT
#define STRICT
#endif // STRICT

// #define _WIN32_WINNT 0x0400
#undef _ATL_APARTMENT_THREADED
#define _ATL_FREE_THREADED 
#include <atlbase.h>

//You may derive a class from CComModule and use it if you want to override
//something, but do not change the name of _Module
class CExeModule : public CComModule
{
public:
	LONG Unlock() noexcept ;
	DWORD dwThreadID;
};
extern CExeModule _Module;

#include <atlcom.h>
#include <atlctl.h>


