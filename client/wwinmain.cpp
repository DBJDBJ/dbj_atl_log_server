/* (c) 2020 by dbj@dbj.org -- LICENSE_DBJ -- https://dbj.org/license_dbj/ */
#include "framework.h"

//----------------------------------------------------------------------------------------------------
/////////////////////////////////////////////////////////////////////////////
/// automagicaly start stop dbj simple log and com init/uninit

namespace {

    static void* log_start(void*)
    {
        dbj_simple_log_startup(this_app_full_path_a()); return 0;
    }
    static void* log_end(void*)
    {
        dbj_log_finalize(); return 0;
    }

    static dbj::start_stop<log_start, log_end > dbj_simple_log_start_stop_;

    static void* com_start(void*)
    {
#if ( defined(_WIN32_DCOM)  || defined(_ATL_FREE_THREADED))
        HRESULT result = ::CoInitializeEx(NULL, COINIT_MULTITHREADED);
#else
        HRESULT result = ::CoInitialize(NULL);
#endif
        DBJ_ASSERT(S_OK == result);

        return 0;
    }
    static void* com_finish(void*)
    {
        ::CoUninitialize(); return 0;
    }

    static dbj::start_stop<com_start, com_finish > dbj_com_start_stop_;
}

//----------------------------------------------------------------------------------------------------
HRESULT log_client(const char* txt_);
//----------------------------------------------------------------------------------------------------

int APIENTRY program(/*_In_*/ HINSTANCE /*hInstance*/,
    /*_In_opt_*/ HINSTANCE /*hPrevInstance*/,
    /*_In_*/ LPWSTR    /*lpCmdLine*/,
    /*_In_*/ int       /*nCmdShow*/);

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

            VERIFY_HRESULT(log_client("diving into the program now!"));

            program(hInstance, hPrevInstance, lpCmdLine, nCmdShow);
        }
        __finally {
        }
    }
    __except (
       GenerateDump(GetExceptionInformation())
        /* returns 1 aka EXCEPTION_EXECUTE_HANDLER */
        )
    {
        // MS STL "throws" are caught here
        // as now they are SEH
        perror(APP_NAME "SEH Exception caught");

        puts(dump_last_run.finished_ok == TRUE
            ? "minidump creation succeeded"
            : "minidump creation failed"
        );

        if (dump_last_run.finished_ok) {
            puts(dump_last_run.dump_folder_name);
            puts(dump_last_run.dump_file_name);
        }
    }
  
        return EXIT_FAILURE;
}

