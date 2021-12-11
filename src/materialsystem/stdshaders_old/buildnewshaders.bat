@echo off
setlocal

set TTEXE=..\..\devtools\bin\timeprecise.exe
if not exist %TTEXE% goto no_ttexe
goto no_ttexe_end

:no_ttexe
set TTEXE=time /t
:no_ttexe_end


rem echo.
rem echo ~~~~~~ buildallshaders %* ~~~~~~
%TTEXE% -cur-Q
set tt_all_start=%ERRORLEVEL%
set tt_all_chkpt=%tt_start%



set sourcedir="shaders"
set targetdir="..\..\..\game\hl2\shaders"

set BUILD_SHADER=call buildshaders_new.bat

set ARG_X360=-x360
set ARG_EXTRA=



REM ****************
REM usage: buildallshaders [-pc | -x360]
REM ****************
set ALLSHADERS_CONFIG=pc
if /i "%1" == "-x360" goto shcfg_x360
goto shcfg_end
:shcfg_x360
           set ALLSHADERS_CONFIG=x360
:shcfg_end


REM ****************
REM PC SHADERS
REM ****************
if /i "%ALLSHADERS_CONFIG%" == "pc" (
%BUILD_SHADER% tymeta_dx9_20b
%BUILD_SHADER% tymeta_dx9_30
)


:end



rem echo.
if not "%dynamic_shaders%" == "1" (
  rem echo Finished full buildallshaders %*
) else (
  rem echo Finished dynamic buildallshaders %*
)

rem %TTEXE% -diff %tt_all_start% -cur
rem echo.
