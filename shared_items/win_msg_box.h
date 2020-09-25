#pragma once

#include "win32_strsafe.h"
#include "windows_includer.h"
// #include "dbj_win_buffer.h"

#include <stdbool.h>
#include <strsafe.h>
#include <crtdbg.h>


#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

	// with no extension
	static inline const wchar_t * this_base_namew()
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

	static inline const char * this_base_namea()
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


	//  msg box no exit
	static inline void win32_msg_boxA(const char * fmt_ , ...)
	{
		DBJ_ASSERT(fmt_);
		char buff[1024] = { 0 };
		va_list argptr;
		va_start(argptr, fmt_ );
		HRESULT hr_ = win_vsprintfa(buff, 1024, fmt_, argptr) ;
		DBJ_ASSERT( S_OK == hr_ ) ;
		va_end(argptr);
		MessageBoxA(NULL, (LPCSTR)buff, this_base_namea(), MB_OK);
	}

#undef DBGA
#ifdef _DEBUG
#define DBGA(m_) win32_msg_boxA(("%s\n\n%s\n\n%d", m_, __FILE__, __LINE__)
#else // ! _DEBUG
#define DBGA(m_) 
#endif // ! _DEBUG

	static inline void win32_msg_boxW(const wchar_t * fmt_ , ... )
	{
		DBJ_ASSERT(fmt_);
		WCHAR buff[1024] = { (WCHAR)0 };
		va_list argptr;
		va_start(argptr, fmt_);
		HRESULT hr_ = win_vsprintfw(buff, 1024, fmt_, argptr);
		DBJ_ASSERT(S_OK == hr_);
		va_end(argptr);
		MessageBoxW(NULL, (LPCWSTR)buff, this_base_namew(), MB_OK);
	}

#undef DBGW
#ifdef _DEBUG
#define DBGW(m_) win32_msg_boxW(L"%s\n\n%s\n\n%d", m_, __FILEW__, __LINE__ )
#else // ! _DEBUG
#define DBGW(m_) 
#endif // ! _DEBUG

#undef SXW
#define SXW(f_, x_ ) win32_msg_boxW(L"Expression:\n%s\n\nResult:\n" f_ , #x_, (x_))

#undef SXA
#define SXA(f_, x_ ) win32_msg_boxA("Expression:\n%s\n\nResult:\n" f_ , #x_, (x_))

#if 0
#undef  WIN32_ERROR_MESSAGE_SIZE
#define WIN32_ERROR_MESSAGE_SIZE 0xFF

	typedef struct win32_error_msg_box_arg
	{
		bool display_error_message;
		bool do_process_exit;
		/*DWORD*/ int last_error /* from GetLastError()*/;
		const char* error_source;
	}
	win32_error_msg_box_arg;

	typedef struct win32_error_msg {
		char data[WIN32_ERROR_MESSAGE_SIZE];
	} win32_error_msg;

	win32_error_msg
		win32_error_msg_box_exit(win32_error_msg_box_arg);

	/*
	*/
	static inline win32_error_msg
		win32_error_msg_box_exit(
			win32_error_msg_box_arg  arg_ret_val
		)
	{   // def value is empty string
		win32_error_msg result_err_msg = { (char)'\0' };

		// if last error not given ask for it
		if (arg_ret_val.last_error < 1) arg_ret_val.last_error = GetLastError();

		arg_ret_val.error_source =
			(arg_ret_val.error_source == NULL ? "null" : arg_ret_val.error_source);

		// Retrieve the system error message for the last-error code
		LPVOID lpMsgBuf = { 0 };
		LPVOID lpDisplayBuf = { 0 };

#ifndef  NDEBUG
		int format_rezult =
#endif // ! NDEBUG
			FormatMessageA(
				FORMAT_MESSAGE_ALLOCATE_BUFFER |
				FORMAT_MESSAGE_FROM_SYSTEM |
				FORMAT_MESSAGE_IGNORE_INSERTS,
				NULL,
				arg_ret_val.last_error,
				MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
				(LPSTR)&lpMsgBuf,
				0, NULL);

#ifndef  NDEBUG
		DBJ_ASSERT(format_rezult > 0);
		if (format_rezult < 1) {
			LocalFree(lpMsgBuf);
			return result_err_msg; // empty msg
		}
#endif // ! NDEBUG

		// Display the error message
		if (arg_ret_val.display_error_message) {

			lpDisplayBuf =
				(LPVOID)LocalAlloc(LMEM_ZEROINIT,
					(strlen((LPCSTR)lpMsgBuf) + strlen((LPCSTR)arg_ret_val.error_source) + 40) * sizeof(char)
				);

			StringCchPrintfA(
				(LPSTR)lpDisplayBuf,
				LocalSize(lpDisplayBuf) / sizeof(char),
				"%s failed\n\nerror code %d\nmessage: %s\n\n%s",
				arg_ret_val.error_source, 
				arg_ret_val.last_error, 
				(LPSTR)lpMsgBuf,
				(arg_ret_val.do_process_exit ? " Module will exit!" : "" )
			);

			MessageBoxA(NULL, (LPCSTR)lpDisplayBuf, "Error", MB_OK);
		}

		strncpy_s(result_err_msg.data, WIN32_ERROR_MESSAGE_SIZE, (LPCSTR)lpMsgBuf, WIN32_ERROR_MESSAGE_SIZE);

		LocalFree(lpMsgBuf);
		LocalFree(lpDisplayBuf);
		SetLastError(0); // yes this helps sometimes

		// caller asked us to exit the process
		if (arg_ret_val.do_process_exit) {
			ExitProcess(arg_ret_val.last_error);
		}
		return result_err_msg;
	} // win32_error_msg
#endif // 0
#ifdef __cplusplus
} // "C"
#endif // __cplusplus
