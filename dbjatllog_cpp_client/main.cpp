
#include "framework.h"

#define APP_NAME "bteclog_cpp_client"
#define APP_VERSION "0.0.1"

//----------------------------------------------------------------------------------------------------
/*

Insired by: https://docs.microsoft.com/en-us/windows/win32/dxtecharts/crash-dump-analysis

Extensions to that (c) 2020 by dbj.org -- LICENSE_DBJ

NOTE: SEH routines are intrinsic to the cl.exe

Usage:

inline void SomeFunction() {    __try    {
        int *pBadPtr = NULL;      *pBadPtr = 0;
    }    __except(GenerateDump(GetExceptionInformation()))    {    }
}
*/

#include <assert.h>
#include <dbghelp.h>
#include <shellapi.h>
#include <shlobj.h>
#include <strsafe.h>

//    StringCchPrintfA( szFileName, MAX_PATH, "%s%s", szPath, szAppName );
#undef  win32_sprintf
#define win32_sprintf StringCchPrintfA

#pragma comment(lib, "Dbghelp.lib")

    typedef struct generate_dump_last_run {
        char  dump_folder_name[MAX_PATH];
        char  dump_file_name[MAX_PATH];
        BOOL finished_ok;
    } generate_dump_last_run;

    static generate_dump_last_run dump_last_run;
    static generate_dump_last_run dump_last_run_clean = { 0, 0, FALSE };

    /*
    DBJ: warning, currently this is a blocking call to an expensive function
    */
    static inline int GenerateDump(EXCEPTION_POINTERS* pExceptionPointers)
    {
        dump_last_run = dump_last_run_clean;

        char  szPath[MAX_PATH] = { 0 };
        char  szFileName[MAX_PATH] = { 0 };
        const char* szAppName = APP_NAME ;
        const char* szVersion = APP_VERSION ;
        DWORD dwBufferSize = MAX_PATH;
        HANDLE hDumpFile = 0;
        SYSTEMTIME stLocalTime;
        MINIDUMP_EXCEPTION_INFORMATION ExpParam;

        GetLocalTime(&stLocalTime);
        GetTempPathA(dwBufferSize, szPath);

        win32_sprintf(szFileName, MAX_PATH, "%s%s", szPath, szAppName);
        CreateDirectoryA(szFileName, NULL);

        win32_sprintf(dump_last_run.dump_folder_name, MAX_PATH, "%s", szFileName);

        win32_sprintf(szFileName, MAX_PATH, "%s%s\\%s-%04d%02d%02d-%02d%02d%02d-%ld-%ld.dmp",
            szPath, szAppName, szVersion,
            stLocalTime.wYear, stLocalTime.wMonth, stLocalTime.wDay,
            stLocalTime.wHour, stLocalTime.wMinute, stLocalTime.wSecond,
            GetCurrentProcessId(), GetCurrentThreadId());

        hDumpFile = CreateFileA(szFileName, GENERIC_READ | GENERIC_WRITE,
            FILE_SHARE_WRITE | FILE_SHARE_READ, 0, CREATE_ALWAYS, 0, 0);

        win32_sprintf(dump_last_run.dump_file_name, MAX_PATH, "%s", szFileName);

        ExpParam.ThreadId = GetCurrentThreadId();
        ExpParam.ExceptionPointers = pExceptionPointers;
        ExpParam.ClientPointers = TRUE;

        BOOL bMiniDumpSuccessful = MiniDumpWriteDump(GetCurrentProcess(), GetCurrentProcessId(),
            hDumpFile, MiniDumpWithDataSegs, &ExpParam, NULL, NULL);

        dump_last_run.finished_ok = bMiniDumpSuccessful;
        return EXCEPTION_EXECUTE_HANDLER;
    }

//----------------------------------------------------------------------------------------------------
    HRESULT log(const char* txt_);

int APIENTRY program(/*_In_*/ HINSTANCE /*hInstance*/,
    /*_In_opt_*/ HINSTANCE /*hPrevInstance*/,
    /*_In_*/ LPWSTR    /*lpCmdLine*/,
    /*_In_*/ int       /*nCmdShow*/);

//----------------------------------------------------------------------------------------------------
int APIENTRY wWinMain(/*_In_*/ HINSTANCE hInstance,
    /*_In_opt_*/ HINSTANCE hPrevInstance,
    /*_In_*/ LPWSTR    lpCmdLine,
    /*_In_*/ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    __try
    {
        HRESULT hRes = CoInitializeEx(NULL, COINIT_MULTITHREADED);
        _ASSERTE(SUCCEEDED(hRes));

        HRESULT logrez = log("diving into the program now!");

        if (FAILED(logrez))
        {
            char msg[win32_errormsg_size] = { 0 };

            win32_errormsg(HRESULT_CODE(logrez), & msg );

            // for to be seen in the debbuger; at this point
            const char* see_mee = msg;
            UNREFERENCED_PARAMETER( see_mee );

        }
        return program(hInstance, hPrevInstance, lpCmdLine, nCmdShow);
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

