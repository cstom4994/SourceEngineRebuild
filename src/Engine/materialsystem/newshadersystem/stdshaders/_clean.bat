@echo off
setlocal

if /i "%1" == "-game" goto CleanGameDir
goto CleanINCFiles

:CleanGameDir
set __GameDir=%~2
if not exist "%__GameDir%\gameinfo.txt" goto MissingGameInfo
if exist "%__GameDir%\shaders" rd /s /q "%2\shaders"
goto CleanINCFiles

:CleanINCFiles
if exist fxctmp9 rd /s /q fxctmp9
if exist fxctmp9_tmp rd /s /q fxctmp9_tmp
goto CleanOtherStuff

:CleanOtherStuff
@REM if exist debug_dx9 rd /s /q debug_dx9
if exist shaders rd /s /q shaders
goto end

:MissingGameInfo
echo Invalid -game parameter specified (no "%__GameDir%\gameinfo.txt" exists).
goto end

:end
pause