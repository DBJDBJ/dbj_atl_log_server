#pragma once

#include "../shared_items/hresult_verify.h" // VERIFY_HRESULT
#include "../shared_items/win_msg_box.h"
#include "../shared_items/win_guid_compare.h"

// note: in here is a win syslog also used but just for windows builds
#define CLUE_LOG_TO_SYSLOG

// optional
// otherwise it is empty string
// #define CLUE_LOG_MODULE_NAME __FILE__

#include "../cclue/cclue.h"

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

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

