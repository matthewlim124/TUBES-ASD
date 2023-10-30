#include "../boolean.h"

#ifndef STRING_H
#define STRING_H
#define STRING_MAX 100 

typedef struct{
  char TabWord[STRING_MAX];
  int Length;
}Word;

void MakeWord(Word *s); 
/*Melakukan awal string dengan string kosong, yaitu {0} dalam array string atau 
 * bisa hanya berisis '\0' */

void ConcatWord(Word dest, Word *target); 
/*Mengabungkan 2 kata menjadi satu string */

boolean CompareWord(Word a, Word b);

void CleanWord(Word *w); 

void SetWord(Word *w, char *s);
#endif
