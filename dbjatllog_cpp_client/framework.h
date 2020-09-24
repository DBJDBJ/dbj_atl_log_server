// header.h : include file for standard system include files,
// or project specific include files
//

#pragma once

#include "targetver.h"
#define STRICT 1             // DBJ added
#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files
#include <windows.h>
// C RunTime Header Files
#include <assert.h> // DBJ added
#include <crtdbg.h> // DBJ added
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

// (c) 2020 by dbj@dbj.org -- LICENSE_DBJ -- https://dbj.org/license_dbj/
extern "C" {

    enum { win32_errormsg_size = 0xFF } ;

    static inline void win32_errormsg(int error_code_, char(*buffer)[win32_errormsg_size])
    {
        DWORD rez = FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM,
            NULL, error_code_,
            MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
            *buffer,
            win32_errormsg_size,
            NULL);

        assert(rez > 0);

    } // win32_errormsg
}