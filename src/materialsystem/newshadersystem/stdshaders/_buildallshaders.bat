@echo off
setlocal enabledelayedexpansion

:start
set TTEXE=..\..\..\devtools\bin\timeprecise.exe
if not exist %TTEXE% goto no_ttexe
goto no_ttexe_end

:no_ttexe
set TTEXE=time /t
:no_ttexe_end

rem ===================================
rem ====== LAUNCH CONFIGURATIONS ======

set "GAMEDIR=%cd%\..\..\..\..\game\VANCE"

@REM this will vary for people here, maybe use the appid finder i have in quiver in this
@REM Totterynine : oh god
set "ENGINEDIR=E:\Projects\TymetaWorks\Tymeta\game\"

set "SOURCEDIR=..\..\.."
set "BUILD_SHADER=call _buildshaders.bat"

@REM dynamic shaders only builds the required files (inc) to build stdshader_*.dll
set dynamic_shaders=0

rem ==== LAUNCH CONFIGURATIONS END ====
rem ===================================

echo ==============================================================================
echo.
echo Building All Shaders
echo.

%TTEXE% -cur-Q
set tt_all_start=%ERRORLEVEL%
set tt_all_chkpt=%tt_start%

REM ---------------------
REM BUILD SHADERS
REM ---------------------
echo --------------------------------------------------------------------------------------------
%BUILD_SHADER% _shaderlist_dx9_20b				-game %GAMEDIR% -source %SOURCEDIR% %dynamic_shaders%
echo --------------------------------------------------------------------------------------------
%BUILD_SHADER% _shaderlist_dx9_30				-game %GAMEDIR% -source %SOURCEDIR% %dynamic_shaders% -dx9_30 -force30
echo --------------------------------------------------------------------------------------------
echo.

REM ---------------------
REM END
REM ---------------------
:end

rem echo.
if not "%dynamic_shaders%" == "1" (
  echo Finished Building All Shaders %*
) else (
  echo Finished Building All Shaders - Dynamic %*
)

%TTEXE% -diff %tt_all_start% -cur

echo.
echo ==============================================================================
echo.
%TTEXE% -diff %tt_all_start% -cur
echo.
echo Press any key to rebuild game shader project and exit . . .
pause >nul
