@echo off
gcc -o tes_stack tes_stack.c stack.c "..\..\ADT\Lagu\lagu.c" "..\..\ADT\Word\word.c"

if errorlevel 1 (
    echo Compilation failed.
    exit /b 1
)

echo Compilation successful.
echo Running tes_stack...
tes_stack.exe
