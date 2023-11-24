#ifndef LISTLAGU_H
#define LISTLAGU_H

#include "../Lagu/lagu.h"
#define MAX_ListLagu 300
typedef struct{
  Lagu A[MAX_ListLagu];
}ListLagu;

void MakeListLagu(ListLagu *l); 

int Length(ListLagu l); 

void Set(ListLagu *l , int idx, Lagu a);

#endif
