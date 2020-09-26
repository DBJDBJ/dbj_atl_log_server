// thelog.cpp : Implementation of Cthelog
#include "stdafx.h"
#include "dbjlogsvr.h"
#include "thelog.h"

/////////////////////////////////////////////////////////////////////////////
// Cthelog

STDMETHODIMP Cthelog::InterfaceSupportsErrorInfo(const IID & riid)
{
	if ( dbj::win::equal_guids(IID_Ithelog, riid) )
		return S_OK;

	return S_FALSE;
}

HRESULT Cthelog::OnDraw(ATL_DRAWINFO& di)
{
	RECT& rc = *(RECT*)di.prcBounds;
	Rectangle(di.hdcDraw, rc.left, rc.top, rc.right, rc.bottom);
	DrawText(di.hdcDraw, _T("DBJ Log Server"), -1, &rc, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	return S_OK;
}

STDMETHODIMP Cthelog::get_logfilename(BSTR * pVal)
{
	// TODO: Add your implementation code here

	CLUE_LOG_NOTICE << "Entered: " __FUNCSIG__ ;

	return S_OK;
}

STDMETHODIMP Cthelog::put_logfilename(BSTR newVal)
{
	CLUE_LOG_NOTICE << "Entered: " __FUNCSIG__;

	return S_OK;
}

STDMETHODIMP Cthelog::get_doelapsedtime(BOOL * pVal)
{
	CLUE_LOG_NOTICE << "Entered: " __FUNCSIG__;

	return S_OK;
}

STDMETHODIMP Cthelog::put_doelapsedtime(BOOL newVal)
{
	CLUE_LOG_NOTICE << "Entered: " __FUNCSIG__;

	return S_OK;
}

STDMETHODIMP Cthelog::get_status(BSTR * pVal)
{
	CLUE_LOG_NOTICE << "Entered: " __FUNCSIG__;

	return S_OK;
}

// hmm .. argument is not a pointer here?
STDMETHODIMP Cthelog::log(BSTR logtext_)
{
	CLUE_LOG_NOTICE << "Entered: " __FUNCSIG__;

	return S_OK;
}
