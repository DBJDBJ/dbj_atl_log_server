#pragma once

#include <stdbool.h>
#include <strsafe.h>
#include <crtdbg.h>

//    StringCchPrintfA( szFileName, MAX_PATH, "%s%s", ... );
#undef  win32_sprintfa
#define win32_sprintfa StringCchPrintfA

#undef  win32_sprintfw
#define win32_sprintfw StringCchPrintfW

#include "windows_includer.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

	// with no extension
	static inline const wchar_t* this_base_namew()
	{
		static wchar_t this_base_name[0xFF] = {'\0'};

		if (this_base_name[0] == '\0') {
			
			wchar_t this_file[1024] = { '\0' };

			int rez = GetModuleFileNameW( 
				(HMODULE)NULL ,	this_file,1024
			);

			wchar_t* last_slash = wcsrchr(this_file, L'\\');
			wchar_t* last_dot   = wcsrchr(this_file, L'.');
			wchar_t* walker = last_slash + 1 ;

			_ASSERTE(last_slash);
			_ASSERTE(last_dot);
			_ASSERTE(walker);

			int this_base_name_idx = 0;
			while (walker != last_dot ) {
				this_base_name[this_base_name_idx++] = *walker;
				walker++;
			}
			this_base_name[this_base_name_idx] = L'\0';

			return this_base_name;
		}

		return this_base_name;
	}


	//  msg box no exit
	static inline void win32_msg_boxA
	(const char msg[], const char* file_, const long line_)
	{
		char buff[1024] = { 0 };
		win32_sprintfa(buff, 1024, "\n%s\n\nFile: %s\nLine: %d", msg, file_, line_);

		MessageBoxA(NULL, (LPCSTR)buff, "Message", MB_OK);
	}

#undef MSGBOXA
#ifdef _DEBUG
#define MSGBOXA(m_) win32_msg_boxA(m_ , __FILE__, __LINE__)
#else // ! _DEBUG
#define MSGBOXA(m_) 
#endif // ! _DEBUG

	static inline void win32_msg_boxW
	(const wchar_t msg[], const wchar_t* file_, const long line_)
	{
		wchar_t buff[1024] = { L'\0' };
		win32_sprintfw(buff, 1024, L"\n%s\n\nFile: %s\nLine: %d", msg, file_, line_);

		MessageBoxW(NULL, (LPCWSTR)buff, this_base_namew(), MB_OK);
	}

#undef MSGBOXW
#ifdef _DEBUG
#define MSGBOXW(m_) win32_msg_boxW(m_, __FILEW__, __LINE__ )
#else // ! _DEBUG
#define MSGBOXW(m_) 
#endif // ! _DEBUG

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
		_ASSERTE(format_rezult > 0);
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

#ifdef __cplusplus
} // "C"
#endif // __cplusplus
