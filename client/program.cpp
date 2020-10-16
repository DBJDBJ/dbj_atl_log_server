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
    UNREFERENCED_PARAMETER(lpCmdLine);


    // VERIFY_HRESULT(mshtml_client("https://bing.com"));
    
    VERIFY_HRESULT(log_client("diving into the com log server client test now!"));


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



