#pragma once

#define STRICT
// #define _WIN32_WINNT 0x0400
#define _ATL_APARTMENT_THREADED
#include <atlbase.h>
//You may derive a class from CComModule and use it if you want to override
//something, but do not change the name of _Module
class CExeModule : public CComModule
{
public:
	LONG Unlock();
	DWORD dwThreadID;
};
extern CExeModule _Module;
#include <atlcom.h>
#include <atlctl.h>

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

