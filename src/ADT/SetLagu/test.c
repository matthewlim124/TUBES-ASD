#include "set.h"
#include <stdio.h>

int main(){
  int nTest;
  //Initiate SetLagu 
  SetLagu sLagu; 
  CreateSet(&sLagu);
  
  //Check For Empty
  printf("Checking for Empty List..\n"); 
  if(IsEmpty(sLagu)){
    printf("Set Empty\n");
  }
                                 
  //Fill in Set 
  Lagu temp = MakeLagu();
  SetWord(&temp.Album , "Ini Album" );
  SetWord(&temp.Judul , "Ini Judul" );
  SetWord(&temp.Penyanyi , "Ini Penyanyi" );
  AddSet(&sLagu, temp);

  //Checking Set Length
  printf("Isi Set : %s, %s, %s\n", sLagu.buffer[0].Judul.TabWord, sLagu.buffer[0].Album.TabWord, sLagu.buffer[0].Penyanyi.TabWord);
  printf("Set Length : %d\n", Length(sLagu));

  //Adding 1 More Lagu  with same value
  AddSet(&sLagu, temp);
  printf("Set Length After Added Same Value : %d\n", Length(sLagu));
  
  //Adding 1 More Lagu with unique value
  Lagu temps; 
  SetWord(&temps.Album , "Ini Album" );
  SetWord(&temps.Judul , "Ini Judul" );
  SetWord(&temps.Penyanyi , "Ini Penyanyis");
  printf("Isi Set : %s, %s, %s,\n", temps.Judul.TabWord,temps.Album.TabWord,temps.Penyanyi.TabWord);
  AddSet(&sLagu, temps);
  printf("Set Length after Added Unique Value : %d\n", Length(sLagu));


}
