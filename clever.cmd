@echo off&title %~n0
@cls
@echo.
for %%a in ("%~dp0\.") do echo This folder basename: "%%~nxa"

@echo.
for %%a in ("%~dp0\.") do for %%b in ("%%~dpa\.") do echo Parent basename: "%%~nxb"

@echo.
@echo This folder full path: "%~dp0"