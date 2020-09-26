<h1> ATL COM Server 2020?! </h1>

- [1.1. Modus Operandi](#11-modus-operandi)
  - [1.1.1. Knowledge Rules](#111-knowledge-rules)
  - [1.1.2. How COM/RPC works](#112-how-comrpc-works)
- [1.2. Usage](#12-usage)

Yes this is [ATL](https://docs.microsoft.com/en-us/cpp/atl/active-template-library-atl-concepts?view=vs-2019) indeed. It all started very innocently. I was experimenting with [cl /kernel](https://docs.microsoft.com/en-us/cpp/build/reference/kernel-create-kernel-mode-binary?view=vs-2019) switch. Trying all sorts of projects, from modern MS STL code, back to Win32. And then I wondered into my own code from pre 1998 (gasp!). Little I know it never worketh...

That was 24 hours ago. Which I spent refactoring, and making it work. It *seems* to work now. There is also a cpp client. Using `comdef.h` and the rest. 

Both server and the client are [/kernel](https://docs.microsoft.com/en-us/cpp/build/reference/kernel-create-kernel-mode-binary?view=vs-2019) build.

Client server communication over COM is working. Server is mainly without functionality of the logging. That is next.

## 1.1. Modus Operandi

[COM](https://en.wikipedia.org/wiki/Component_Object_Model) is based on [MSRPC](https://en.wikipedia.org/wiki/Microsoft_RPC). 

### 1.1.1. Knowledge Rules

It is critical you read those two Wikipedia articles first. Just after that take any direction you choose in gaining more knowledge about COM: paper books, ancient PDF's or whatever.

Advice: [MS DOCS](https://docs.microsoft.com/en-us/) (what was MSDN) is vast. It is actually much bigger and deeper than you think. It is also (more or less well) organized. But. There is no chronological ordering. You will never know are you diving into some 30 years old C++ or you are following (for example) Windows 10 RT (Run Time) library. Thing are all in there clumped together. And historical perspective is extremely important as most of still available technologies are deprecated or superseded. 

So you better know are you barking to the wrong tree before you invest into climbing it. And for that I find Wikipedia priceless. Usually Wikipedia IT articles are written by very good people. With a lot of important historical perspective. Do understand we are here investigating complex technology pre dating StackOverflow escape hatch. Always start from WikiPedia.

### 1.1.2. How COM/RPC works

<h2>&nbsp;</h2>

![rpc architecture diagram](https://docs.microsoft.com/en-us/windows/win32/rpc/images/prog-a11.png)

<h2>&nbsp;</h2>

Looks rather over elaborated. But that works and it works well. Local RPC calls are instantaneous. The whole Windows OS level, inter component communication layer (since NT) is based on MS RPC. 

[UNIX/Linux have nothing like RPC or COM](https://stackoverflow.com/a/3063712/10870835). There are disparate and competing solutions but it seems [D-Bus](https://en.wikipedia.org/wiki/D-Bus) has won.

[Here is an "better than average" text](https://docs.microsoft.com/en-us/windows/win32/rpc/how-rpc-works) on MS DOCS about RPC architecture.

COM is an "modern" Object Oriented Architecture based on RPC.

<h3>&nbsp;</h3>

## 1.2. Usage

<h3>&nbsp;</h3>

<h3>WARNING! Do EVERYTHING as administrator</h3>

<h3>&nbsp;</h3>

> For client / server connection to be established the windows security is the roadblock. Please be sure both are running the administrator context. Including the VStudio sessions you use.

> From VStudio, before the client debugging session use "Debug --> Attach to process" to check if `dbjatllog` is running.

<h2>&nbsp;</h2>

**Build and test**

Two separate solutions are provided, one for sever and one for client. You need to open two Visual Studio sessions. One with `server.sln` and the other with `client.sln`. Even better if you have two (or more) monitors. you keep them completely separate. Make sure you start the cmd.exe in admin mode.

1. build the server
   1. Debug build of the server has a lot of message box popup's.
2. build the client
3. start the server
   1. On cmd line execute
   2. `dbjatllog UnregServer RegServer` first, then
       `dbjatllog` with no arguments.
   5. Now server runs. 
   6. to stop the server you need to do `dbjatllog UnregServer` 
      1. Remember: Visual Studio Debug --> Attach to process dialogue, will tell you if `dbjatllog` is running.
4. start the client by starting the VS debug session. Follow that `log()` call
   1. Remember: COM is based on RPC and calls are almost instantaneous. Just as if you are calling methods locally. Which means you need to implement asynchronous operation or locking on the server side, if required. 
   2. This is unlike sockets where things are inherently asynchronous. And slower.  Local COM (RPC) calls do not use networking at all. By 2020, AFAIK, local COM calls are all shared memory based.
   
You can open another VStudio session and attach the debugger to the `dbjatllog` process. Place the break points inside methods to catch the COM message arrivals.


---

&copy; 2020 by dbj@dbj.org -- LICENSE_DBJ -- https://dbj.org/license_dbj/