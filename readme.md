# [ATL](https://docs.microsoft.com/en-us/cpp/atl/active-template-library-atl-concepts?view=vs-2019) Server 2020?!

Yes this is ATL indeed. It all started very innocently. I was experimenting with [cl /kernel](https://docs.microsoft.com/en-us/cpp/build/reference/kernel-create-kernel-mode-binary?view=vs-2019) switch. Trying all sorts of projects, from modern MS STL code, back to Win32. And then I wondered into my own code from pre 1998 (gasp!). Little I know it never worketh...

That was 24 hours ago. Which I spent refactoring, and making it work. It *seems* to work now. There is also a cpp client. `comdef.h` and the rest. 

Both server and the client are [/kernel](https://docs.microsoft.com/en-us/cpp/build/reference/kernel-create-kernel-mode-binary?view=vs-2019) build.

Client server communication over COM is working. Server is mainly without functionality of the logging. That is next.

## Usage

1. make sure you start the cmd.exe in admin mode and Visual Studio in admin mode too
2. debug build of the server has a lot of message box popup's so you can see what is going on
3. You need to start `dbjatllog RegServer` first
    1. then you need to restart it with no arguments, now server runs
4. then start the client VStudio debugging session and follow that `log()` call
   1. it all works, but nothing is logged :)
   2. you can open another VStudio session (as admin again!) and attach the debugger to the `dbjatllog` process. Please the break points inside methods to catch the COM message arrivals.
5. to stop the server you need to do `dbjatllog UnregServer` 



&copy; 2020 by dbj@dbj.org -- LICENSE_DBJ -- https://dbj.org/license_dbj/