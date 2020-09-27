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
// NOTE: this is wide string version
#ifndef DBJ_VERIFY
#define DBJ_VERIFY(expr, msg) \
(void)(                                                                                     \
    (!!(expr)) ||                                                                           \
    (1 != _CrtDbgReportW(_CRT_ASSERT, _CRT_WIDE(__FILE__), __LINE__, NULL, L"%ls", msg)) || \
    (_CrtDbgBreak(), 0)                                                                     \
)
#endif

#ifndef DBJ_VERIFYX
#define DBJ_VERIFYX(x) DBJ_VERIFY((x), _CRT_WIDE(#x) )
#endif //! DBJ_VERIFYX

// Here's a better C version (from Google's Chromium project):
#define DBJ_COUNT_OF(x) ((sizeof(x)/sizeof(0[x])) / ((size_t)(!(sizeof(x) % sizeof(0[x])))))

static inline const wchar_t* this_app_full_path_w()
{
	static wchar_t full_path[1024] = { L'\0' };
	if (full_path[0] == L'\0') {
		int rez = GetModuleFileNameW(
			(HMODULE)NULL, full_path, 1024
		);
	}
	return full_path;
}

static inline const char * this_app_full_path_a()
{
	static char full_path[1024] = { '\0' };
	if (full_path[0] == '\0') {
		int rez = GetModuleFileNameA(
			(HMODULE)NULL, full_path, 1024
		);
	}
	return full_path;
}

	// with no extension
static inline const wchar_t* this_base_namew()
{
	static wchar_t this_base_name[0xFF] = { L'\0' };

	if (this_base_name[0] == L'\0') {

		wchar_t this_file[1024] = { L'\0' };

		int rez = GetModuleFileNameW(
			(HMODULE)NULL, this_file, 1024
		);

		wchar_t* last_slash = wcsrchr(this_file, L'\\');
		wchar_t* last_dot = wcsrchr(this_file, L'.');
		wchar_t* walker = last_slash + 1;

		DBJ_ASSERT(last_slash);
		DBJ_ASSERT(last_dot);
		DBJ_ASSERT(walker);

		int this_base_name_idx = 0;
		while (walker != last_dot) {
			this_base_name[this_base_name_idx++] = *walker;
			walker++;
		}
		this_base_name[this_base_name_idx] = L'\0';

		return this_base_name;
	}

	return this_base_name;
}

static inline const char* this_base_namea()
{
	static char this_base_name[0xFF] = { '\0' };

	if (this_base_name[0] == '\0') {

		char this_file[1024] = { '\0' };

		int rez = GetModuleFileNameA(
			(HMODULE)NULL, this_file, 1024
		);

		char* last_slash = strchr(this_file, L'\\');
		char* last_dot = strchr(this_file, L'.');
		char* walker = last_slash + 1;

		DBJ_ASSERT(last_slash);
		DBJ_ASSERT(last_dot);
		DBJ_ASSERT(walker);

		int this_base_name_idx = 0;
		while (walker != last_dot) {
			this_base_name[this_base_name_idx++] = *walker;
			walker++;
		}
		this_base_name[this_base_name_idx] = '\0';

		return this_base_name;
	}

	return this_base_name;
}


#endif // DBJ_WINDOWS_INCLUDE_INC_
