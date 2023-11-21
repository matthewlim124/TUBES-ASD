@echo off
gcc -o tes_list tes_list.c list.c

if errorlevel 1 (
    echo Compilation failed.
    exit /b 1
)

echo Compilation successful.
echo Running tes_list...
tes_list.exe
