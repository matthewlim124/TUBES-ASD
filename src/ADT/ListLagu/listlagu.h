#ifndef LISTLAGU_H
#define LISTLAGU_H

#include "../Lagu/lagu.h"

typedef struct{
  Lagu A[50];
}ListLagu;

void MakeListLagu(ListLagu *l); 

int Length(ListLagu l); 

void Set(ListLagu *l , int idx, Lagu a);

#endif
