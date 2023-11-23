@echo off
gcc mesinkarakter.c test_mesinkarakter.c -o test_mesinkarakter

if errorlevel 1 (
    echo Compilation failed.
    pause
    exit /b 1
)

echo Compilation successful.
pause
