@echo off&echo directory walker
FOR /F "tokens=*" %%G IN ('dir /s /b .vs') DO echo %%G