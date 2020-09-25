// thelog.cpp : Implementation of Cthelog
#include "stdafx.h"
#include "bteclog.h"
#include "thelog.h"

/////////////////////////////////////////////////////////////////////////////
// Cthelog

STDMETHODIMP Cthelog::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_Ithelog,
	};

	 for (int i=0;i<sizeof(arr)/sizeof(arr[0]);i++)
	//for (int i=0; i < DBJ_COUNT_OF(arr) ; i++)
	{
		if ( dbj::win::equal_guids(*arr[i], riid) )
		// if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
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

	DBGW(__FUNCSIG__);

	return S_OK;
}

STDMETHODIMP Cthelog::put_logfilename(BSTR newVal)
{
	DBGW(__FUNCSIG__);

	return S_OK;
}

STDMETHODIMP Cthelog::get_doelapsedtime(BOOL * pVal)
{
	DBGW(__FUNCSIG__);

	return S_OK;
}

STDMETHODIMP Cthelog::put_doelapsedtime(BOOL newVal)
{
	DBGW(__FUNCSIG__);

	return S_OK;
}

STDMETHODIMP Cthelog::get_status(BSTR * pVal)
{
	DBGW(__FUNCSIG__);

	return S_OK;
}

// hmm .. argument is not a pointer here?
STDMETHODIMP Cthelog::log(BSTR logtext_)
{
	DBGW(__FUNCSIG__);

	return S_OK;
}
