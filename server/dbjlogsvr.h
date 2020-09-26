

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.01.0622 */
/* at Tue Jan 19 04:14:07 2038
 */
/* Compiler settings for dbjlogsvr.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 8.01.0622 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif /* __RPCNDR_H_VERSION__ */

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __dbjlogsvr_h__
#define __dbjlogsvr_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __Ithelog_FWD_DEFINED__
#define __Ithelog_FWD_DEFINED__
typedef interface Ithelog Ithelog;

#endif 	/* __Ithelog_FWD_DEFINED__ */


#ifndef __thelog_FWD_DEFINED__
#define __thelog_FWD_DEFINED__

#ifdef __cplusplus
typedef class thelog thelog;
#else
typedef struct thelog thelog;
#endif /* __cplusplus */

#endif 	/* __thelog_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __Ithelog_INTERFACE_DEFINED__
#define __Ithelog_INTERFACE_DEFINED__

/* interface Ithelog */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_Ithelog;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("CE863F3F-799C-11D2-94EF-000000000000")
    Ithelog : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_logfilename( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_logfilename( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_doelapsedtime( 
            /* [retval][out] */ BOOL *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_doelapsedtime( 
            /* [in] */ BOOL newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_status( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE log( 
            /* [in] */ BSTR logtext_) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IthelogVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            Ithelog * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            Ithelog * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            Ithelog * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            Ithelog * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            Ithelog * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            Ithelog * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            Ithelog * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_logfilename )( 
            Ithelog * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_logfilename )( 
            Ithelog * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_doelapsedtime )( 
            Ithelog * This,
            /* [retval][out] */ BOOL *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_doelapsedtime )( 
            Ithelog * This,
            /* [in] */ BOOL newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_status )( 
            Ithelog * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *log )( 
            Ithelog * This,
            /* [in] */ BSTR logtext_);
        
        END_INTERFACE
    } IthelogVtbl;

    interface Ithelog
    {
        CONST_VTBL struct IthelogVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define Ithelog_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define Ithelog_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define Ithelog_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define Ithelog_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define Ithelog_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define Ithelog_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define Ithelog_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define Ithelog_get_logfilename(This,pVal)	\
    ( (This)->lpVtbl -> get_logfilename(This,pVal) ) 

#define Ithelog_put_logfilename(This,newVal)	\
    ( (This)->lpVtbl -> put_logfilename(This,newVal) ) 

#define Ithelog_get_doelapsedtime(This,pVal)	\
    ( (This)->lpVtbl -> get_doelapsedtime(This,pVal) ) 

#define Ithelog_put_doelapsedtime(This,newVal)	\
    ( (This)->lpVtbl -> put_doelapsedtime(This,newVal) ) 

#define Ithelog_get_status(This,pVal)	\
    ( (This)->lpVtbl -> get_status(This,pVal) ) 

#define Ithelog_log(This,logtext_)	\
    ( (This)->lpVtbl -> log(This,logtext_) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __Ithelog_INTERFACE_DEFINED__ */



#ifndef __BTECLOGLib_LIBRARY_DEFINED__
#define __BTECLOGLib_LIBRARY_DEFINED__

/* library BTECLOGLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_BTECLOGLib;

EXTERN_C const CLSID CLSID_thelog;

#ifdef __cplusplus

class DECLSPEC_UUID("CE863F40-799C-11D2-94EF-000000000000")
thelog;
#endif
#endif /* __BTECLOGLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long *, unsigned long            , BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserMarshal(  unsigned long *, unsigned char *, BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserUnmarshal(unsigned long *, unsigned char *, BSTR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long *, BSTR * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


