

/* (c) 2020 by dbj@dbj.org -- LICENSE_DBJ -- https://dbj.org/license_dbj/ */


#include "framework.h"


//----------------------------------------------------------------------------------------------------
// users need to deliver implmentaion of this function
extern "C" int APIENTRY program (
     HINSTANCE /*hInstance*/,
     HINSTANCE /*hPrevInstance*/,
     LPWSTR    /*lpCmdLine*/,
     int       /*nCmdShow*/);

//----------------------------------------------------------------------------------------------------
// we shall use this canary until the moot point with /kernel builds , SEH and destrcutors is resolved
// right now   ~canary() is called
// but /kernel- switch seems to be ominuously preparing its debut
struct canary final {
    canary()
    {
        // in this frist fw release we force users to stat/stop dbj simple log
        // and COM, always
        dbj_simple_log_startup(this_app_full_path_a());
        /*HRESULT result = */::CoInitializeEx(NULL, COINIT_MULTITHREADED);
        dbj_log_info("canary constructor called");
    }
    ~canary()
    {
        // REMEMBER: this is /kernel build, 
        // if destructors are called there are conflicting reports
        dbj_log_info("canary destructor called");
        dbj_log_finalize();
        ::CoUninitialize();
    }
};
static canary in_the_coalmine_;
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
            program(hInstance, hPrevInstance, lpCmdLine, nCmdShow);
        }
        __finally {
            dbj_log_info("main __finally"); 
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
            dbj_log_info("Dump folder name: %s", dump_last_run.dump_folder_name);
            dbj_log_info("Dump file   name: %s", dump_last_run.dump_file_name);
        }
    }

    return EXIT_FAILURE;
} // wWinMain



