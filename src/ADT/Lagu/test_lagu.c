#include "lagu.h"
#include <stdio.h>

int main(){
  Lagu tempLagu = MakeLagu();
  printf("Inisiasi Lagu Kosong..\n"); 
  printf("Isi Lagu : %s, %s, %s \n",tempLagu.Album.TabWord,tempLagu.Judul.TabWord,tempLagu.Penyanyi.TabWord);
  
  Word tAlbum, tPenyanyi, tJudul;
  SetWord(&tJudul, "Pink Venom");
  SetWord(&tPenyanyi, "Blackpink");
  SetWord(&tAlbum, "Born Pink");
  tempLagu.Album = tAlbum;
  tempLagu.Judul = tJudul;
  tempLagu.Penyanyi = tPenyanyi; 
  
  printf("Isi Lagu 1 (Penyanyi, Album, Judul) : %s, %s, %s\n", tempLagu.Penyanyi.TabWord, tempLagu.Album.TabWord, tempLagu.Judul.TabWord);
  Lagu tempLagu2= MakeLagu();
  
  SetWord(&tJudul, "Shut Down");
  SetWord(&tPenyanyi, "Blackpink");
  SetWord(&tAlbum, "Born Pink");
  tempLagu2.Judul = tJudul; 
  tempLagu2.Album = tAlbum;
  tempLagu2.Penyanyi = tPenyanyi;
  printf("Isi Lagu 2 (Penyanyi,Album,Judul) : %s, %s, %s\n", tempLagu2.Penyanyi.TabWord, tempLagu2.Album.TabWord, tempLagu2.Judul.TabWord);
  
  if(CompareLagu(tempLagu, tempLagu2)){
    printf("Lagu Sama\n");
  }
  else{
    printf("Lagu Tidak Sama\n");
  }

  printf("Semisal Lagu diubah menjadi sama \n"); 

  tempLagu.Judul = tempLagu2.Judul; 
  
  
  if(CompareLagu(tempLagu, tempLagu2)){
    printf("Lagu Sama\n");
  }
  else{
    printf("Lagu Tidak Sama\n");
  }

}
