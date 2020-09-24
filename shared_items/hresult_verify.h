#pragma once
/*
NOTE: this is C++17 code
*/

#include "win32_error_msg_box_exit.h"
#include <crtdbg.h>
#include <comdef.h>

extern "C" {

	static inline bool verify_hresult ( HRESULT hr_ ) 
	{
		if (SUCCEEDED(hr_)) return true ;

		win32_error_msg_box_arg arg_ 
			= { 
			/*.display_error_message =*/ true, 
			/*.do_process_exit =*/ true, 
			/*.last_error =*/ HRESULT_CODE(hr_) 
		};

		win32_error_msg_box_exit(arg_);

		return false; // will be not reached
	}

} // "C"
