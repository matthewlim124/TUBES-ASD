#ifndef CONSOLE_H
#define CONSOLE_H
#include "../../ADT/MesinKata/mesinkata.h"
#include "../../ADT/boolean.h"
#include "../../ADT/Word/word.h"
#include "../../ADT/ListLagu/listlagu.h"
#include "../../ADT/SetLagu/set.h"
#include "../../ADT/Queue/queue.h"
#include "../../ADT/StackLagu/stack.h"
#include "../../ADT/MapLagu/map.h"

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
void createPlaylist();
void addPlaylist();
void playSong();
void playPlaylist();
void queueSong();
void queuePlaylist();
void queueSwap();
void queueRemove();
void queueClear();
/*Command PLAY PLAYLIST digunakan untuk memainkan lagu berdasarkan id playlist. Ketika command ini berhasil dieksekusi, queue akan berisi semua lagu yang ada dalam playlist yang dimainkan dan isi riwayat lagu sama dengan queue, tetapi dengan urutan yang di-reverse.

>> PLAY PLAYLIST;

Masukkan ID Playlist: 2;

Memutar playlist “K-pop Enjoyer”.

*/

#endif
