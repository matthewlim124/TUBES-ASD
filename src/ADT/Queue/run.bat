@echo off
:loop
gcc -o tes_queue tes_queue.c queue.c ..\..\ADT\Lagu\lagu.c ..\..\ADT\Word\word.c
if %errorlevel% neq 0 (
    echo Compilation failed
    pause
    exit /b 1
) else (
    echo Compilation successful
    tes_queue.exe
)
pause
goto loop
