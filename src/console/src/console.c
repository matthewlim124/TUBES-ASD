#include "console.h"
#include <stdio.h>

 ListLagu DaftarLagu; 
 int idxLagu =0;
void readCommand(){
  // Construct List 
  MakeListLagu(&DaftarLagu);

  int i =0; 
  int stopStatus =0;
   while(!stopStatus){
    printf(">> ");
    STARTWORD();
    printf("Iterasi Ke - %d \n",i);
    printf("=================================================\n \n");
    i++;
    if(compareString(currentWord.TabWord, "START")){
      boolean success = defaultSave();
      if(success){
        printf("START berhasil dijalankan\n");
      }
      else{
        printf("Start gagal dijalankan");
        return; 
      }
    }
    else if(compareString("SAVE", currentWord.TabWord)){
      saveCommand();
    }
    else if(compareString("QUIT", currentWord.TabWord)){
      quitCommand(&stopStatus);
    }
    else if(compareString(currentWord.TabWord, "LOAD")){
      ADVWORD();
      char path[120] = "../../../save/";
      for(int i =0; i< currentWord.Length; i++){
        path[i + 14] = currentWord.TabWord[i]; 
      }
      boolean success = loadSave(path);
      if (success)printf("File konfigurasi '%s' aplikasi berhasil dibaca. Wayangwave berhasil dijalankan\n", path);
      else printf("File konfiguras aplikasi gagal dibaca.\n");
    }
  }
}

boolean compareString(char *a, char *b){
  int i =0;
  while(a[i] != '\0' && b[i] != '\0'){
    if(a[i]!=b[i]) return false;
    i++;
  }
  if(a[i] != b[i]) return false; 
  return true; 
}

boolean loadSave(char *filePath){
  printf("Lokasi File : %s\n",filePath);
  FILE *file = freopen(filePath, "r",stdin);
  if (NULL == file) {
   printf("file can't be opened \n");
    return false; 
  }
  
  else{
    START();
    int index = currentChar - '0'; 
    STARTWORD(); // Rading Empty Line 
    for(int i =0 ;i < index; i++){
      Lagu tempLagu = MakeLagu();
      // Memasukkan save Penyanyi ke list Penyanyi
      Word space;
      STARTWORD();
      Word tempPenyanyi = currentWord;
      while(!isEndWord() && !EOP){
        ADVWORD();
        SetWord(&space, " ");
        ConcatWord(currentWord, &space);
        ConcatWord(space, &tempPenyanyi);
      }
      tempLagu.Penyanyi = tempPenyanyi;
      // Memasukkan save Album ke list Album
      STARTWORD();
      Word tempAlbum = currentWord;
      while(!isEndWord() && !EOP){
        ADVWORD();
        SetWord(&space, " ");
        ConcatWord(currentWord, &space);
        ConcatWord(space, &tempAlbum);
      }
      //Memasukkan Judul 
      STARTWORD();
      Word tempJudul = currentWord; 
      while(!isEndWord()  && !EOP){
        ADVWORD();
        SetWord(&space, " ");
        ConcatWord(currentWord, &space);
        ConcatWord(space, &tempJudul);
      }

      tempLagu.Judul = tempJudul;
      tempLagu.Album = tempAlbum; 
      printf("Penyanyi : %s\n",tempLagu.Penyanyi.TabWord);
      printf("Album : %s\n",tempLagu.Album.TabWord);
      printf("Judul : %s\n", tempLagu.Judul.TabWord);
      DaftarLagu.A[idxLagu] = tempLagu; 
      idxLagu++;
  }  
  freopen("CONIN$", "r", stdin);
  return true; 

  }
}

boolean defaultSave(){
  printf("Default Save\n|=======================|\n");
  FILE *file = freopen("../../../save/DefSave.txt", "r", stdin);
  if(NULL == file){
    printf("Default save missing\n");
    return false; 
  }
  else{
    START();
    int idxP = currentChar - '0';
    printf("Jumlah Penyanyi : %c\n", currentChar);
    STARTWORD();
    for(int k = 0; k < idxP; k++){
      START(); // Reading num of albums
      printf("Jumlah Album : %c\n", currentChar);
      int idxA = currentChar -'0';
      // Reading Penyanyi
      Word space;
      STARTWORD();
      Word tempPenyanyi = currentWord;
      while(!isEndWord() && !EOP){
        ADVWORD();
        SetWord(&space, " ");
        ConcatWord(currentWord, &space);
        ConcatWord(space, &tempPenyanyi);
      }
      printf("Penyanyi : %s\n", tempPenyanyi.TabWord);

      for(int j = 0; j < idxA; j++){
        START(); // Reading num of titles
        printf("Jumlah Judul : %c\n", currentChar);
        int idxJ = currentChar - '0'; 

        // Membaca Album 
        STARTWORD();
        Word tempAlbum = currentWord;
        Word space; 
        while(!isEndWord() && !EOP){
          ADVWORD();
          SetWord(&space, " ");
          ConcatWord(currentWord, &space);
          ConcatWord(space, &tempAlbum);
        }
        printf("Album : %s\n", tempAlbum.TabWord);

        //Reading titles 
        for(int i =0; i< idxJ; i++){ 
          STARTWORD(); // Reading empty space
          Word tempJudul = currentWord;
          Word space;
          while(!isEndWord() && !EOP){
            ADVWORD();
            SetWord(&space, " ");
            ConcatWord(currentWord, &space);
            ConcatWord(space, &tempJudul);
          }
          printf("Judul : %s\n", tempJudul.TabWord);  
        }
      }
    }
  /*Notes program akan error (inifinite loop) 
   * apabila pada save default tidak diakhiri \n
  */ 
  freopen("CONIN$", "r", stdin);
  return true; 
  }
}
void saveCommand(){
  ADVWORD();
  printf("File berhasl disimpan\n");
}

void listCommand(){
  ADVWORD();
  Word sebuahWord; 
  SetWord(&sebuahWord, "PLAYLIST");
  if(CompareWord(currentWord, sebuahWord)){

  }

}

void quitCommand(int *stopStatus){
  printf("Apakah kamu ingin menyimpan data sesi sekarang? "); 
  STARTWORD();
  char masukan[50] = {0}; //Memastikan array berisi NULL 
  CopyLetter(masukan); 
  if(compareString(masukan,"Y")){
    printf("Saving....\n");
    printf("Selesai SAVE\n");
  }
  *stopStatus= 1;   
  printf("Kamu keluar dari WayangWave.\nDadah ^_^/");
  }


