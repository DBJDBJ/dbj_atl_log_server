@echo off
@cls

if [%1] == [] (
@echo.
@echo WARNING
@echo '%0' removes ALL the things built but only from this root folder
@echo To make it do that install it again with one argument
@echo.
goto exit
)

if [%1] NEQ [] (
@echo removing folder x64
@rd /S /Q x64 > NUL
@echo removing folder Release
@rd /S /Q Release > NUL
@echo removing folder Debug
@rd /S /Q Debug > NUL
)

:exit

