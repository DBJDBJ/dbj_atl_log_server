//

#include "framework.h"
//----------------------------------------------------------------------------------------------------
extern "C" HRESULT log_client(const char* );
// extern "C" HRESULT mshtml_client(const char* txt_);
//----------------------------------------------------------------------------------------------------
extern "C" int APIENTRY program (_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(hInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
    UNREFERENCED_PARAMETER(nCmdShow);


    LOG_DEBUG("wargv[0] is: %S", dbj::win::app_cli_args.argv[0]);
    LOG_DEBUG("basename is: %s", this_base_namea() );
    
    VERIFY_S_OK(log_client("diving into the com log server client test now!"));

    MSG msg;

    // Main message loop:
    while (GetMessageW(&msg, nullptr, 0, 0))
    {
        if (!TranslateAcceleratorW(msg.hwnd, NULL, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessageW(&msg);
        }
    }

    return (int) msg.wParam;
}



