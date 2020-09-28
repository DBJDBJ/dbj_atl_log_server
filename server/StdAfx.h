#pragma once

// NOTE! This is server side exe , thus any gui popin out fo here 
// it will be invisible to humans
// thus logging it is, no GUI or MessageBox-es please
//
// also since this is windows app there is no std streams 
// thus there is no point of printf-ing from here

#include "../dbj--simplelog/dbj_simple_log.h"

#include "../shared_items/windows_includer.h"
#include "../shared_items/hresult_verify.h" // VERIFY_HRESULT
// #include "../shared_items/win_msg_box.h"
#include "../shared_items/win_guid_compare.h"
#include "../shared_items/dbj_start_stop.h"

#ifndef STRICT
#define STRICT
#endif // STRICT

// #define _WIN32_WINNT 0x0400
#define _ATL_APARTMENT_THREADED
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


