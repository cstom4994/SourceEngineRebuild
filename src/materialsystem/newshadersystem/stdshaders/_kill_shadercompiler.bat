@echo off

tasklist /FI "IMAGENAME eq shadercompile_standalone.exe" 2>NUL | find /I /N "shadercompile_standalone.exe">NUL

if "%ERRORLEVEL%"=="0" (
	echo Shadercompile is running still, killing
	taskkill /f /im shadercompile_standalone.exe >nul
)