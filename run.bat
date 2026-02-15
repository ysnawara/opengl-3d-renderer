@echo off
cd /d "%~dp0"
if not exist "build\Release\renderer.exe" (
    echo Building first...
    cmake -B build -G "Visual Studio 17 2022" -A x64
    cmake --build build --config Release
)
build\Release\renderer.exe
pause
