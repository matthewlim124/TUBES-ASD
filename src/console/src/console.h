#ifndef CONSOLE_H
#define CONSOLE_H
#include "../../ADT/MesinKata/mesinkata.h"
#include "../../ADT/boolean.h"
#include "../../ADT/Word/word.h"
#include "../../ADT/ListLagu/listlagu.h"
#include "../../ADT/SetWord/set.h"
#include "../../ADT/Queue/queue.h"
#include "../../ADT/StackLagu/stack.h"
#include "../../ADT/MapWord/map.h"
#include "../../ADT/Playlist/playlist.h"

void queueSong();
void playlistCreate();
void readCommand(); // Membaca Command dari User
boolean defaultSave(); // Meload file save default
boolean loadSave(char *filePath); // Meload file save 
boolean compareString(char *a, char *b);
void quitCommand(int *stopStatus);
void saveCommand();
void statusCommand();
Word takeInput();
void songNext();
void songPrev();
void listCommand();
#endif
