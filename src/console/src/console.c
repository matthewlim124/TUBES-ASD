#include "console.h"
#include <stdio.h>

//Global Variable 
Queue QueueLagu; 
SetLagu SetDaftarLagu;
ListLagu DaftarLagu; 
Stack StackLagu; 
Lagu currentPlaying; 

int idxLagu =0;
boolean statusLoad= false; 
void readCommand(){
  // Construct Set 
  CreateSet(&SetDaftarLagu);

  // Construct ListLagu
  MakeListLagu(&DaftarLagu);
  
  // Consturct QueueLagu
  CreateQueue(&QueueLagu);
  
  // Consturct StackLagu 
  CreateEmpty(&StackLagu);

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
    else if(compareString("SONG", currentWord.TabWord)){
      ADVWORD();
      if(compareString("NEXT", currentWord.TabWord)){
        songNext();
      }
      else if(compareString("PREVIOUS", currentWord.TabWord)){
        songPrev();
      }
    }
    else if(compareString("STATUS", currentWord.TabWord)){
      statusCommand();
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

void statusCommand(){
  Lagu tempLagu; 
  Queue newLagu = QueueLagu; 
  dequeue(&newLagu, &tempLagu);
  printf("\n\nNow Playing :\n %s - %s - %s\n", tempLagu.Penyanyi.TabWord, tempLagu.Judul.TabWord, tempLagu.Album.TabWord);
  int idx =1; 
  printf("Queue : \n");
  while(!isEmpty(newLagu)){
    dequeue(&newLagu,&tempLagu);
    printf("%d. %s - %s - %s\n",idx,tempLagu.Penyanyi.TabWord, tempLagu.Judul.TabWord, tempLagu.Album.TabWord);
    idx++;
  }
}

void songPrev(){
  Lagu tempLagu; 
  if(!IsEmptyStack(StackLagu)){
    Pop(&StackLagu,&tempLagu);
    printf("Memutar lagu sebelumnya\n\"%s\" oleh \"%s\"\n",tempLagu.Judul.TabWord, tempLagu.Penyanyi.TabWord);
    currentPlaying = tempLagu;
  }
  else{
    printf("Riwayat lagu kosong, memutar kembali lagu\n\"%s\" oleh \"%s\"\n",currentPlaying.Judul.TabWord, currentPlaying.Penyanyi.TabWord);
  }
}
void songNext(){
  Lagu tempLagu; 
  dequeue(&QueueLagu,&tempLagu);
  if(!isEmpty(QueueLagu)){
    currentPlaying = tempLagu; 
    printf("Memutar lagu selanjutnya\n\"%s \" oleh \"%s\"\n",tempLagu.Judul.TabWord, tempLagu.Penyanyi.TabWord);
    
  }
  else{
    enqueue(&QueueLagu, tempLagu);
    printf("Queue kosong, memutar kembali lagu\n\"%s\" oleh \"%s\"\n",tempLagu.Judul.TabWord, tempLagu.Penyanyi.TabWord);
  }

}
boolean loadSave(char *filePath){
  printf("Lokasi File : %s\n",filePath);
  FILE *file = freopen(filePath, "r",stdin);
  if (file == NULL) {
    printf("file can't be opened \n");
    freopen("CONIN$", "r", stdin);
    return false; 
  }
  
  else{
    START();
    int index = currentChar - '0'; 
    printf("\nInput Queue\n================================\n\n");
    STARTWORD(); // Reading Empty Line 
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
      enqueue(&QueueLagu, tempLagu); 
      //printf("Penyanyi : %s\n",SetDaftarLagu.buffer[idxLagu].Penyanyi.TabWord);
      //printf("Album : %s\n",SetDaftarLagu.buffer[idxLagu].Album.TabWord);
      //printf("Judul : %s\n", SetDaftarLagu.buffer[idxLagu].Judul.TabWord);
      idxLagu++;
      currentPlaying = tempLagu;
      printf("\n");

    } //End For
      
    
    //Taking for Input (Stack - History Song)
    START(); 
    int idxStack = currentChar - '0';
    printf("Input Stack\n========================================\n\n");
    printf("Second Input : %d\n", idxStack);
    STARTWORD();
    for(int i =0; i< idxStack; i++){
      Lagu newLagu = MakeLagu();
      Word Penyanyi = takeInput();
      Word Album = takeInput();
      Word Judul = takeInput();
      newLagu.Album = Album; 
      newLagu.Penyanyi = Penyanyi; 
      newLagu.Judul = Judul; 
      Push(&StackLagu, newLagu);
      Lagu testLagu; 
      Pop(&StackLagu, &testLagu);
      Push(&StackLagu, newLagu);
      printf("Penyanyi : %s\nAlbum : %s\nJudul : %s\n\n", testLagu.Penyanyi.TabWord, testLagu.Album.TabWord, testLagu.Judul.TabWord);
    }
    printf("Total Lagu : %d\nTotal Lagu dalam Set : %d\n", idxLagu, LengthSet(SetDaftarLagu));
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
  /*Notes program akan error (infinite loop) 
   * apabila pada save default tidak diakhiri \n
  */ 
  freopen("CONIN$", "r", stdin);
  return true; 
  }
}
void saveCommand(){
  ADVWORD();
  Word filePath; 
  SetWord(&filePath, "../../../save/");
  ConcatWord(currentWord,&filePath);
  printf("%s\n",filePath.TabWord);
  FILE *file = fopen(filePath.TabWord, "w");
  fprintf(file, "something");
  fclose(file);
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
  STARTWORD();// Reading Empty Space
  STARTWORD();
  if(compareString(currentWord.TabWord,"Y")){
    printf("Saving....\n");
    printf("Selesai SAVE\n");
  }
  *stopStatus= 1;   
  printf("Kamu keluar dari WayangWave.\nDadah ^_^/");
  }

Word takeInput(){
  STARTWORD();
  Word tempWord = currentWord;
  Word space; 
  while(!isEndWord() && !EOP){
    ADVWORD();
    SetWord(&space, " ");
    ConcatWord(currentWord, &space);
    ConcatWord(space, &tempWord);
  }
  return tempWord; 
}
