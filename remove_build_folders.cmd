@REM for %%a in ("%~dp0\.") do echo This folder basename: "%%~nxa"
@REM for %%a in ("%~dp0\.") do for %%b in ("%%~dpa\.") do echo Parent basename: "%%~nxb"
@REM @echo This folder full path: "%~dp0"

:: it is very important you check first your requirements 
:: against DIR command (cap)abilities
::
:: under here show any folder called .vs even it is hidden
:: DIR /B /S /A:H /A:D .vs
::
:: under here show ONLY hidden folder called .vs
:: DIR /B /S /A:HD .vs
::
:: under here show ONLY ALL hidden folders 
:: DIR /B /S /A:HD
::
:: under here show ALL NOT hidden folders 
:: DIR /B /S /A:D
::
:: usefull switch: /A:-S
:: do not show system files or folders

@echo off
@cls
setlocal
set currentLevel=0
set maxLevel=%2
if not defined maxLevel set maxLevel=3

:procFolder
pushd %1 2>nul || exit /b
if %currentLevel% lss %maxLevel% (
  FOR /F "EOL=: DELIMS=" %%F IN ('DIR /B /S /A:HD') DO (
    CALL :remove_folder_if %%~xnF %%~fF
    set /a currentLevel+=1
    call :procFolder "%%F"
    set /a currentLevel-=1
  )
)

goto exit
:: first arg is a basename
:: second arg is a full path
:: no rezult is returned
:remove_folder_if
SETLOCAL
if [%1] == [x64] (
@echo.  
@echo remove folder %1
@echo.  
@rd /s /q %2
goto :end_remove_folder_if
)
if [%1] == [.vs] (
@echo.  
@echo remove folder %1
@echo.  
@rd /s /q "%2"
goto :end_remove_folder_if
) 
if [%1] == [Release] (
@echo.  
@echo remove folder %1
@echo.  
@rd /s /q "%2"
else goto :end_remove_folder_if
) 
if [%1] == [Debug] (
@echo.  
@echo remove folder %1
@echo.  
@rd /s /q "%2"
else goto :end_remove_folder_if
)
::
:end_remove_folder_if
ENDLOCAL 

:exit
popd