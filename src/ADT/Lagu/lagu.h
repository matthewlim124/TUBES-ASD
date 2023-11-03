#ifndef LAGU_H
#define LAGU_H

#include "../Word/word.h"

typedef struct{
  Word Penyanyi;
  Word Album;
  Word Judul;
}Lagu;

// Constructor 
Lagu MakeLagu();

boolean CompareLagu(Lagu a, Lagu b);

#endif
