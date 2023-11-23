#include "listlagu.h"
#include <stdio.h>

int main(){
  ListLagu new; 
  MakeListLagu(&new);
  Lagu A = MakeLagu();
  Lagu B = MakeLagu();
  SetWord(&A.Album, "a");
  SetWord(&A.Judul, "a");
  SetWord(&A.Penyanyi, "a");

  SetWord(&B.Penyanyi, "b");
  SetWord(&B.Album, "b");
  SetWord(&B.Judul, "b");
  if(CompareWord(A.Penyanyi, B.Penyanyi))printf("Compare Word True\n");
  if(CompareLagu(A, B))printf("Compare Lagu True\n");
  Set(&new, Length(new), A);
  
  Set(&new, Length(new), B);

  printf("Panjang List Lagu : %d\n", Length(new));
  printf("Element ke 1 : %s - %s - %s\n", new.A[0].Judul.TabWord, new.A[0].Album.TabWord, new.A[0].Penyanyi.TabWord);

}
