#include "listlagu.h"
#include <stdio.h>

int main(){
  ListLagu new; 
  MakeListLagu(&new);
  Lagu A = MakeLagu();
  Lagu B = MakeLagu();
  SetWord(&A.Album, "b");
  SetWord(&A.Judul, "b");
  SetWord(&A.Penyanyi, "b");

  SetWord(&B.Penyanyi, "b");
  SetWord(&B.Album, "b");
  SetWord(&B.Judul, "b");

  if(CompareWord(A.Penyanyi, B.Penyanyi))printf("Compare Word True\n");
  if(CompareLagu(A, B))printf("Compare Lagu True\n");
}
