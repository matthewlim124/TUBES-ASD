#ifndef CONSOLE_H
#define CONSOLE_H
#include "../../ADT/MesinKata/mesinkata.h"
#include "../../ADT/boolean.h"
#include "../../ADT/Word/word.h"
#include "../../ADT/ListLagu/listlagu.h"

void readCommand(); // Membaca Command dari User
void defaultSave(); // Meload file save default
boolean loadSave(char *filePath); // Meload file save 
boolean compareString(char *a, char *b);
void quitCommand(int *stopStatus);
void saveCommand(); 

#endif
