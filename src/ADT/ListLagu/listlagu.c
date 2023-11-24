#include "listlagu.h"
#include <stdio.h>
void MakeListLagu(ListLagu *l){
  Lagu newLagu = MakeLagu();
  for(int i =0; i<MAX_ListLagu;i++){
    l->A[i] = newLagu;
  }
}

int Length(ListLagu l){
  Lagu Mark = MakeLagu();
  int i =0;
  while(!CompareLagu(l.A[i], Mark)){
    i++;
  }
  return i;
}

void Set(ListLagu *l, int idx, Lagu a){
  l->A[idx] = a; 
}
