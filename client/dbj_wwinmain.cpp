#pragma once
#ifndef DBJ_WWIN_MAIN_INC_
#define DBJ_WWIN_MAIN_INC_

/* (c) 2020 by dbj@dbj.org -- LICENSE_DBJ -- https://dbj.org/license_dbj/ */


#include "framework.h"


//----------------------------------------------------------------------------------------------------
// users need to deliver implmentaion of this function
int APIENTRY program (
     HINSTANCE /*hInstance*/,
     HINSTANCE /*hPrevInstance*/,
     LPWSTR    /*lpCmdLine*/,
     int       /*nCmdShow*/);

//----------------------------------------------------------------------------------------------------


extern "C" int APIENTRY wWinMain(
    HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow
)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    __try
    {
        __try {
            // in this frist fw release we force users to stat/stop dbj simple log
            // and COM, always
            dbj_simple_log_startup(this_app_full_path_a());
            HRESULT result = ::CoInitializeEx(NULL, COINIT_MULTITHREADED);
            program(hInstance, hPrevInstance, lpCmdLine, nCmdShow);
        }
        __finally {
            // REMEMBER: this is /kernel build, SEH is thrown but destructors are not called
            // this one has to do it here
            dbj_log_finalize();
            ::CoUninitialize();
        }
    }
    __except (
        GenerateDump(GetExceptionInformation())
        /* returns 1 aka EXCEPTION_EXECUTE_HANDLER */
        )
    {
        // MS STL "throws" are caught here
        // as now they are SEH
        dbj_log_error("SEH Exception caught");

        dbj_log_error(dump_last_run.finished_ok == TRUE
            ? "minidump creation succeeded"
            : "minidump creation failed"
        );

        if (dump_last_run.finished_ok) {
            puts(dump_last_run.dump_folder_name);
            puts(dump_last_run.dump_file_name);
        }
    }

    return EXIT_FAILURE;
} // wWinMain


#endif // DBJ_WWIN_MAIN_INC_
