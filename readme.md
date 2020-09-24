# [ATL](https://docs.microsoft.com/en-us/cpp/atl/active-template-library-atl-concepts?view=vs-2019) Server 2020?!

Yes this is ATL indeed. It all started very innocently. I was experimenting with [cl /kernel](https://docs.microsoft.com/en-us/cpp/build/reference/kernel-create-kernel-mode-binary?view=vs-2019) switch. Trying all sorts of projects, from modern MS STL code, back to Win32. And then I wondered into my own code from pre 1998 (gasp!). Little I know it never worketh...

That was 24 hours ago. Which I spent refactoring, and making it work. It *seems* to work now. There is also a cpp client. `comdef.h` and the rest. 

Both server and the client are [/kernel](https://docs.microsoft.com/en-us/cpp/build/reference/kernel-create-kernel-mode-binary?view=vs-2019) build.

Still work in progress. But I am hopeful :)

&copy; 2020 by dbj@dbj.org -- LICENSE_DBJ -- https://dbj.org/license_dbj/