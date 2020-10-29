#pragma once

#include "windows_includer.h"
#include "dbj_start_stop.h"

namespace dbj::win {

    extern "C" {

    struct app_args_ final {
        int argc;
        wchar_t** argv;
    };

     inline __declspec(thread) struct app_args_ app_cli_args;

    } // "C"

    namespace {
        
        extern "C" {

        static inline void* harvest_app_args_ (void*) noexcept { 
            app_cli_args.argv =
                ::CommandLineToArgvW(
                    ::GetCommandLineW(), &app_cli_args.argc
                );
            return 0; 
        }
        static inline void* free_app_args_(void*) noexcept 
        {
            if (app_cli_args.argc > 0) {
                ::LocalFree(app_cli_args.argv);
                app_cli_args.argc = 0;
            }
            return 0; 
        }

    } // "C"

        //	In anonymous namespace hide the auto-initializer instance
        inline const dbj::start_stop< harvest_app_args_, free_app_args_> 
            dbj_app_cli_harvester_autoinit__{};
    } // anonspace

#if 0
    // wide char is default
    // C++17 or better is required
    // caution: each instance will make a copy of cli args
    struct cli_args final
    {
        int argc{};
        wchar_t** argv{};

        ~cli_args() { if ( argv != 0) { ::LocalFree(argv); } }

        // NOTE: rezult of GetCommandLineW() must NOT be free
        // NOTE: rezult of CommandLineToArgvW() must be freed
        cli_args() : argv (
            ::CommandLineToArgvW(
                ::GetCommandLineW(), &argc
            )
        ) 
        {
        }
    };
#endif // 0

} // dbj::win
