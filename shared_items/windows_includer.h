#pragma once
#ifndef DBJ_WINDOWS_INCLUDE_INC_
#define DBJ_WINDOWS_INCLUDE_INC_
/*
(c) 2019-2020 by dbj.org   -- LICENSE DBJ -- https://dbj.org/license_dbj/
*/
#ifdef __STDC_ALLOC_LIB__
#define __STDC_WANT_LIB_EXT2__ 1
#else
#define _POSIX_C_SOURCE 200809L
#endif

#define NOMINMAX

#ifdef DBJ_MINIMAX
#undef  min
#define min(x, y) ((x) < (y) ? (x) : (y))

#undef  max
#define max(x, y) ((x) > (y) ? (x) : (y))
#endif // DBJ_MINIMAX

#define STRICT 1
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#ifdef DBJ_VERSION_CHECKS
/*
rudimentary runtime version checks
https://docs.microsoft.com/en-us/windows/desktop/sysinfo/getting-the-system-version
*/
#include <VersionHelpers.h>
#endif // DBJ_VERSION_CHECKS

#include <crtdbg.h>

#undef DBJ_ASSERT
#define DBJ_ASSERT _ASSERTE

// ALWAYS WORKS!!! in release builds too, be carefull!
#ifndef DBJ_VERIFY
#define DBJ_VERIFY(expr, msg) \
(void)(                                                                                     \
    (!!(expr)) ||                                                                           \
    (1 != _CrtDbgReportW(_CRT_ASSERT, _CRT_WIDE(__FILE__), __LINE__, NULL, L"%ls", msg)) || \
    (_CrtDbgBreak(), 0)                                                                     \
)
#endif

// Here's a better C version (from Google's Chromium project):
#define DBJ_COUNT_OF(x) ((sizeof(x)/sizeof(0[x])) / ((size_t)(!(sizeof(x) % sizeof(0[x])))))

#endif // DBJ_WINDOWS_INCLUDE_INC_
