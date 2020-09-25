#pragma once

#include "win_msg_box.h"
#include <crtdbg.h>
#include <comdef.h>

#ifndef _UNICODE
#error Unicode build is required 
#endif // _UNICODE

extern "C" {
	/* NOTE: this is C++ code */
	/* NOTE: process exit on anything but S_OK */
	static inline bool verify_hresult_ ( HRESULT hr_, const wchar_t * file_ = L"", const long line = 0 ) 
	{
		if (S_OK == hr_ ) return true ;

		_com_error  comerr(hr_);

if (line > 0 )  
	win32_msg_boxW(L"IMMEDIATE EXIT !!\n\n'%s'\n\n%s\n# %d", comerr.ErrorMessage(), file_, line);
else
	win32_msg_boxW(L"IMMEDIATE EXIT !!\n\n'%s'", comerr.ErrorMessage() );

		ExitProcess((UINT)hr_);

		return false; // will be not reached
	}

} // "C"

#undef VERIFY_HRESULT

#ifdef _DEBUG
#define VERIFY_HRESULT(HR_) ( verify_hresult_( HR_, __FILEW__, __LINE__) )
#else
#define VERIFY_HRESULT(HR_) ( verify_hresult_( HR_) )
#endif
