@echo off

cd /d %~dp0

echo Compiling shaders
for /r %%i in (*.frag, *.vert) do "%VULKAN_SDK%/Bin/glslangValidator.exe" -V %%i

echo Moving shaders
ROBOCOPY %~dp0 %~dp0../../../../game/bin/shaders *.spv /MOV

exit 0