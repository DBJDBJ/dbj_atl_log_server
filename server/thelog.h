// thelog.h : Declaration of the Cthelog

#ifndef __THELOG_H_
#define __THELOG_H_

#include "resource.h"       // main symbols


/////////////////////////////////////////////////////////////////////////////
// Cthelog
class ATL_NO_VTABLE Cthelog : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<Cthelog, &CLSID_thelog>,
	public CComControl<Cthelog>,
	public IDispatchImpl<Ithelog, &IID_Ithelog, &LIBID_BTECLOGLib>,
	/* DBJ: had to change from NULL to (IID*)0 */
	public IProvideClassInfo2Impl<&CLSID_thelog, (IID*)0, &LIBID_BTECLOGLib>,
	public IPersistStreamInitImpl<Cthelog>,
	public IPersistStorageImpl<Cthelog>,
	public IQuickActivateImpl<Cthelog>,
	public IOleControlImpl<Cthelog>,
	public IOleObjectImpl<Cthelog>,
	public IOleInPlaceActiveObjectImpl<Cthelog>,
	public IViewObjectExImpl<Cthelog>,
	public IOleInPlaceObjectWindowlessImpl<Cthelog>,
	public IDataObjectImpl<Cthelog>,
	public ISupportErrorInfo,
	public ISpecifyPropertyPagesImpl<Cthelog>
{
public:
	Cthelog()
	{
 
	}

DECLARE_REGISTRY_RESOURCEID(IDR_THELOG)

BEGIN_COM_MAP(Cthelog)
	COM_INTERFACE_ENTRY(Ithelog)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY_IMPL(IViewObjectEx)
	COM_INTERFACE_ENTRY_IMPL_IID(IID_IViewObject2, IViewObjectEx)
	COM_INTERFACE_ENTRY_IMPL_IID(IID_IViewObject, IViewObjectEx)
	COM_INTERFACE_ENTRY_IMPL(IOleInPlaceObjectWindowless)
	COM_INTERFACE_ENTRY_IMPL_IID(IID_IOleInPlaceObject, IOleInPlaceObjectWindowless)
	COM_INTERFACE_ENTRY_IMPL_IID(IID_IOleWindow, IOleInPlaceObjectWindowless)
	COM_INTERFACE_ENTRY_IMPL(IOleInPlaceActiveObject)
	COM_INTERFACE_ENTRY_IMPL(IOleControl)
	COM_INTERFACE_ENTRY_IMPL(IOleObject)
	COM_INTERFACE_ENTRY_IMPL(IQuickActivate)
	COM_INTERFACE_ENTRY_IMPL(IPersistStorage)
	COM_INTERFACE_ENTRY_IMPL(IPersistStreamInit)
	COM_INTERFACE_ENTRY_IMPL(ISpecifyPropertyPages)
	COM_INTERFACE_ENTRY_IMPL(IDataObject)
	COM_INTERFACE_ENTRY(IProvideClassInfo)
	COM_INTERFACE_ENTRY(IProvideClassInfo2)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()

BEGIN_PROPERTY_MAP(Cthelog)
	// Example entries
	// PROP_ENTRY("Property Description", dispid, clsid)
	PROP_PAGE(CLSID_StockColorPage)
END_PROPERTY_MAP()


BEGIN_MSG_MAP(Cthelog)
	MESSAGE_HANDLER(WM_PAINT, OnPaint)
	MESSAGE_HANDLER(WM_SETFOCUS, OnSetFocus)
	MESSAGE_HANDLER(WM_KILLFOCUS, OnKillFocus)
END_MSG_MAP()


// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IViewObjectEx
	STDMETHOD(GetViewStatus)(DWORD* pdwStatus)
	{
		ATLTRACE(_T("IViewObjectExImpl::GetViewStatus\n"));
		*pdwStatus = VIEWSTATUS_SOLIDBKGND | VIEWSTATUS_OPAQUE;
		return S_OK;
	}

// Ithelog
public:
	STDMETHOD(log)(/*[in]*/ BSTR logtext_);
	STDMETHOD(get_status)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(get_doelapsedtime)(/*[out, retval]*/ BOOL *pVal);
	STDMETHOD(put_doelapsedtime)(/*[in]*/ BOOL newVal);
	STDMETHOD(get_logfilename)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_logfilename)(/*[in]*/ BSTR newVal);
	HRESULT OnDraw(ATL_DRAWINFO& di);

};

#endif //__THELOG_H_
