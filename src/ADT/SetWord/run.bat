@echo off
cls
gcc test_set.c set.c ..\..\ADT\Word\word.c -o test_set.exe

if errorlevel 1 (
    echo Compilation failed.
    pause
    exit /b 1
)

echo Compilation successful.
echo Running test_set...
test_set.exe
pause
