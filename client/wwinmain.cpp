/* (c) 2020 by dbj@dbj.org -- LICENSE_DBJ -- https://dbj.org/license_dbj/ */
#include "framework.h"

//----------------------------------------------------------------------------------------------------
    HRESULT log(const char* txt_);

int APIENTRY program(/*_In_*/ HINSTANCE /*hInstance*/,
    /*_In_opt_*/ HINSTANCE /*hPrevInstance*/,
    /*_In_*/ LPWSTR    /*lpCmdLine*/,
    /*_In_*/ int       /*nCmdShow*/);

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

            VERIFY_HRESULT(log("diving into the program now!"));

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

