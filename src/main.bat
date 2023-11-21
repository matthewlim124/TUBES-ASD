@echo off
gcc ADT/StackLagu/stack.c ADT/Queue/queue.c ADT/SetWord/set.c ADT/Word/word.c ADT/ListLagu/listlagu.c ADT/MesinKarakter/mesinkarakter.c ADT/MesinKata/mesinkata.c main.c console/src/console.c ADT/Lagu/lagu.c ADT/MapWord/map.c ADT/Playlist/playlist.c ADT/Playlist/listlinier.c -o main

if errorlevel 1 (
    echo Compilation failed.
    pause
    exit /b 1
)

echo Compilation successful.
pause
