#ifndef LAGU_H
#define LAGU_H

#include "../Word/word.h"

#define NUM_FEATURES 10
typedef struct{
  Word Penyanyi;
  Word Album;
  Word Judul;
  double Features[NUM_FEATURES];
}Lagu;

// Constructor 
Lagu MakeLagu();
boolean IsEmptyLagu(Lagu a);
boolean CompareLagu(Lagu a, Lagu b);

#endif
