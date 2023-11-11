#ifndef SETLAGU_H
#define SETLAGU_H

#include "../../ADT/Word/word.h"
#define MAX_SET 100

typedef int address; 

typedef struct{
  Word buffer[MAX_SET];
  address Count; 
}SetOfWord;

void CreateSet(SetOfWord *s);

boolean IsEmpty(SetOfWord s); 

int LengthSet(SetOfWord s);

void AddSet(SetOfWord *s, Word l); 

void RemoveSet(SetOfWord *s, Word l); 

boolean IsIn(SetOfWord s, Word l); 

boolean IsEqual(SetOfWord s1, SetOfWord s2);

SetOfWord UnionSet(SetOfWord s1, SetOfWord s2);

SetOfWord IntersectSet(SetOfWord s1, SetOfWord s2);

SetOfWord SetDifference(SetOfWord s1, SetOfWord s2);

SetOfWord CopySet(SetOfWord s);

boolean IsSubset(SetOfWord s1, SetOfWord s2);

#endif
