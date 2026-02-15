@echo off
cd /d "%~dp0"
if not exist "build\Release\renderer.exe" (
    cmake -B build -G "Visual Studio 17 2022" -A x64
    cmake --build build --config Release
)
xcopy /E /I /Y "assets" "build\Release\assets" >nul 2>&1
xcopy /E /I /Y "shaders" "build\Release\shaders" >nul 2>&1
build\Release\renderer.exe
