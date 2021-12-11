@echo off
setlocal

rem Use dynamic shaders to build .inc files only
rem set dynamic_shaders=1
rem == Setup path to nmake.exe, from vc 2005 common tools directory ==
call "C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\vcvarsall.bat" x86


set TTEXE=..\..\devtools\bin\timeprecise.exe
if not exist %TTEXE% goto no_ttexe
goto no_ttexe_end

:no_ttexe
set TTEXE=time /t
:no_ttexe_end


rem echo.
rem echo ~~~~~~ buildsdkshaders %* ~~~~~~
%TTEXE% -cur-Q
set tt_all_start=%ERRORLEVEL%
set tt_all_chkpt=%tt_start%

set BUILD_SHADER=call buildshaders.bat
set ARG_EXTRA=

if not "%shaders_lite%" == "1" (
%BUILD_SHADER% pp_shaders				-game %GAMEDIR% -source %SOURCEDIR%
%BUILD_SHADER% pp_shaders_lite			-game %GAMEDIR% -source %SOURCEDIR%
%BUILD_SHADER% pp_shaders_sm3			-game %GAMEDIR% -source %SOURCEDIR% -dx9_30	-force30 
%BUILD_SHADER% pp_shaders_lite_sm3		-game %GAMEDIR% -source %SOURCEDIR% -dx9_30	-force30 
) else (
%BUILD_SHADER% pp_shaders_lite			-game %GAMEDIR% -source %SOURCEDIR%
%BUILD_SHADER% pp_shaders_lite_sm3		-game %GAMEDIR% -source %SOURCEDIR% -dx9_30	-force30 
)


rem echo.
if not "%dynamic_shaders%" == "1" (
  rem echo Finished full buildallshaders %*
) else (
  rem echo Finished dynamic buildallshaders %*
)

rem %TTEXE% -diff %tt_all_start% -cur
rem echo.
