#ifndef SETLAGU_H
#define SETLAGU_H

#include "../../ADT/Lagu/lagu.h"
#define MAX_SET 100

typedef struct{
  Lagu buffer[MAX_SET];
  int Length; 
}SetLagu;

void CreateSet(SetLagu *s);

boolean IsEmpty(SetLagu s); 

int LengthSet(SetLagu s);

void AddSet(SetLagu *s, Lagu l); 

void RemoveSet(SetLagu *s, Lagu l); 

boolean IsIn(SetLagu s, Lagu l); 

boolean IsEqual(SetLagu s1, SetLagu s2);

SetLagu UnionSet(SetLagu s1, SetLagu s2);

SetLagu IntersectSet(SetLagu s1, SetLagu s2);

SetLagu SetDifference(SetLagu s1, SetLagu s2);

SetLagu CopySet(SetLagu s);

boolean IsSubset(SetLagu s1, SetLagu s2);

#endif
