#include "console.h"
#include <stdio.h>

//Global Variable 
Queue QueueLagu; 
SetLagu SetDaftarLagu;
ListLagu DaftarLagu; 
Stack StackLagu; 
Lagu currentPlaying; 
Map Playlist; //Playlist yang dimiliki
Map Penyanyi; // Berisi penyanyi sebagai key dan album-album penyanyi sebagai value
Map Album; //Berisi album sebagai key dan lagu-lagu sebagai value

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

  // Construct Playlist
  CreateEmptyMap(&Playlist);

  // Construct Penyanyi
  CreateEmptyMap(&Penyanyi);

  // Construct Album
  CreateEmptyMap(&Album);

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
    else if(compareString("PLAYLIST", currentWord.TabWord)){
      ADVWORD();
      if(compareString("CREATE", currentWord.TabWord)){
        createPlaylist();
      }
      else if(compareString("ADD", currentWord.TabWord)){
        ADVWORD();
        if(compareString("SONG", currentWord.TabWord)){
          addPlaylist("SONG");
        }
        else{
          addPlaylist("ALBUM");
        }
      }
      else if(compareString("SWAP", currentWord.TabWord)){
        
      }
    }
    else if(compareString("QUEUE", currentWord.TabWord)){
        ADVWORD();
        if(compareString("SONG", currentWord.TabWord)){
          queueSong();
        }else if(compareString("PLAYLIST",currentWord.TabWord)){
          queuePlaylist();
        }else if(compareString("SWAP",currentWord.TabWord)){
          int x,y;
          ADV();
          x = currentChar - '0';
          ADV();
          y = currentChar - '0';
          queueSwap(x,y);
        }else if(compareString("REMOVE",currentWord.TabWord)){
          ADV();
          int x = currentChar -'0';
          queueRemove(x);
        
        }else if(compareString("CLEAR",currentWord.TabWord)){
          queueClear();
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

void createPlaylist(){
  char input[100];
  printf("Masukkan nama playlist yang ingin dibuat : ");
  scanf("%s", input);

  int i = 0;
  while(input[i] != Undefined){
    Playlist.Elements[find_empty_map_idx(Playlist)].Key[i] = input[i];
    i++;
  }

  printf("\n");
  printf("Playlist %s berhasil dibuat! Silakan masukkan lagu - lagu artis terkini kesayangan Anda!", Playlist.Elements[find_empty_map_idx(Playlist)].Key);
}

void playSong()
{
  printf("Daftar Penyanyi: \n");
  displayMap("PENYANYI");
  printf("Masukkan Nama Penyanyi yang dipilih : ");
  char input[name_length];
  scanf("%s", input);

  int i = 0;
  while(input[i] != Undefined){
    Penyanyi.Elements[find_empty_map_idx(Penyanyi)].Key[i] = input[i];
    i++;
  }

  printf("\n");
  printf("Daftar Album oleh %s:\n", Penyanyi.Elements[find_empty_map_idx(Penyanyi)].Key);
  displayMap("ALBUM");
  printf("Masukkan Nama Album yang dipilih : ");
  scanf("%s", input);
  
  printf("\n");
  i = 0;
  while(input[i] != Undefined){
    Album.Elements[find_empty_map_idx(Album)].Key[i] = input[i];
    i++;
  }
  printf("Daftar Lagu Album %s oleh %s : \n", Album.Elements[find_empty_map_idx(Album)].Key, Penyanyi.Elements[find_empty_map_idx(Penyanyi)].Key);
  displayMap("LAGU");
  printf("Masukkan ID Lagu yang dipilih : ");
  int id_lagu;
  scanf("%d", &id_lagu);

  printf("\n");
  printf("Memutar lagu %s oleh %s", Album.Elements[find_empty_map_idx(Album)].Key, Penyanyi.Elements[find_empty_map_idx(Penyanyi)].Key);

  //Empty Queue
  while(!isEmpty(QueueLagu)){
    dequeue(&QueueLagu, &currentPlaying);
  }
  //Empty Stack
  while(!IsEmptyStack(StackLagu)){
    Pop(&StackLagu, &currentPlaying);
  }
}

void playPlaylist()
{
  printf("Masukkan ID Playlist: ");
  int id_playlist;
  scanf("%d", &id_playlist);

  printf("\n");
  printf("Memutar playlist \"%s\".", Playlist.Elements[find_empty_map_idx(Playlist)].Key);

  //Enter reversed queue to stack 
  Stack tempStack;
  while(!isEmpty(QueueLagu)){
    Lagu tempLagu;
    dequeue(&QueueLagu, &tempLagu);
    Push(&tempStack, tempLagu);
  }
  while(!IsEmptyStack(tempStack)){
    Lagu tempLagu;
    Pop(&tempStack, &tempLagu);
    Push(&StackLagu, tempLagu);
  }


  //Enter album song to queue
  int i = 0;
  while(Album.Elements[find_empty_map_idx(Album)].Value[i] != Undefined){
    valuetype currentSong = *(Album.Elements[find_empty_map_idx(Album)].Value[i]);
    ElType song = {currentSong};
    enqueue(&QueueLagu, song);
    i++;
  }

}

void insertMap(Map *M){
  //Insert penyanyi dan album

}

void displayMap(char *type){
  //Display Map
  
}



void addPlaylist(char *type){

  char input[name_length];

  if(compareString("SONG", type)){
    //ADD SONG
    displayMap("PENYANYI");
    printf("Masukkan nama penyanyi yang ingin dipilih: ");
    scanf("%s", input);

    if(IsMemberMap(Penyanyi, input)){
      displayMap("ALBUM");
      printf("Masukkan Judul Album yang dipilih : ");
      scanf("%s", input);

      if(IsMemberMap(Album, input)){
        int id_lagu, id_playlist;
        displayMap("LAGU");
        printf("Masukkan ID Lagu yang dipilih : ");
        scanf("%d", &id_lagu);

        displayMap("PLAYLIST");
        printf("Masukkan ID Playlist yang dipilih : ");
        scanf("%d", &id_playlist);

        printf("Lagu dengan judul “PINK VENOM” pada album BORN PINK oleh penyanyi BLACKPINK berhasil ditambahkan ke dalam playlist K-Pop Enjoyer.");
      }
    }
  }else{
    //ADD ALBUM

  }
  
}


void swapPlaylist(int id_play, int song1, int song2){

}

void deletePlaylist(){

}

void removePlaylist(int id_play, int song_id){

}

void queueSong(){
   int i,j;

  printf("%s","Daftar Penyanyi :\n");
  displayMap("PENYANYI");

  char inputPenyanyi[name_length];
  scanf("Masukkan Nama Penyanyi : %s", inputPenyanyi);

  int keyIdx;
  printf("Daftar Album oleh %s :\n",inputPenyanyi);
  keyIdx = find_key_idx(Penyanyi,inputPenyanyi);
  for(i = 0;i< value_count(Penyanyi,inputPenyanyi);i++){
        printf("%d. ",i+1);
        for(j = 0;j<length_name(Penyanyi.Elements[keyIdx].Value[i]);j++){
            printf("%c",Penyanyi.Elements[keyIdx].Value[i][j]);
        }
        printf("\n");
  }


  char inputAlbum[name_length];
  scanf("Masukkan Nama Album yang dipilih : %s", inputAlbum);

 
  printf("Daftar Lagu Album %s oleh %s :\n",inputAlbum,inputPenyanyi);

  keyIdx = find_key_idx(Album,inputAlbum);
  for(i = 0;i< value_count(Album,inputAlbum);i++){
        printf("%d. ",i+1);
        for(j = 0;j<length_name(Album.Elements[keyIdx].Value[i]);j++){
            printf("%c",Album.Elements[keyIdx].Value[i][j]);
        }
        printf("\n");
  }

  int songID;
  scanf("Masukkan ID Lagu yang dipilih : %d", songID);

  Lagu added = MakeLagu();
  i = 0;
  while(inputAlbum[i] != '\0'){
    added.Album.TabWord[i] = inputAlbum[i];
    i++;
  }
  added.Album.Length = i;
  i = 0;
  while(inputPenyanyi[i] != '\0'){
    added.Penyanyi.TabWord[i] = inputPenyanyi[i];
    i++;
  }
  added.Penyanyi.Length = i;
  i = 0;
  while(Album.Elements[keyIdx].Value[songID -1][i] != '\0'){
    added.Judul.TabWord[i] = Album.Elements[keyIdx].Value[songID -1][i];
    i++;
  }
  added.Judul.Length = i;
  enqueue(&QueueLagu,added);

}


void queuePlaylist(){
   int i,j;

   int playListId;
   scanf("Masukkan ID Playlist: %d",&playListId);

   char playListKey[name_length] ;
   for( i = 0;i<length_name(Playlist.Elements[playListId-1].Key);i++){
      playListKey[i] =  Playlist.Elements[playListId-1].Key[i];
   }

   char song[name_length];
   for(i = 0;i< value_count(Playlist,playListKey);i++){

        Lagu l;
        l = MakeLagu();

        for(j = 0;j<length_name(Playlist.Elements[playListId-1].Value[i]);j++){
            l.Judul.TabWord[j] = Playlist.Elements[playListId-1].Value[i][j];
        }
        
        int albumIdx = find_key_idx(Album,l.Judul.TabWord);
        for(j = 0;j<length_name(Album.Elements[albumIdx].Key);j++){
            l.Album.TabWord[j] = Album.Elements[albumIdx].Key[j];
        }

      
        int penyanyiIDX = find_key_idx(Penyanyi,l.Album.TabWord);
        for(j = 0;j<length_name(Penyanyi.Elements[penyanyiIDX].Key);j++){
            l.Penyanyi.TabWord[j] = Penyanyi.Elements[penyanyiIDX].Key[j];
        }

        enqueue(&QueueLagu,l);
  }
  printf("Berhasil menambahkan Playlist %s ke queue\n", playListKey);
}

void queueSwap(int x, int y){
  if(!isEmpty(QueueLagu)){
     if(x < 1 || x > length(QueueLagu)){
        printf("Lagu dengan urutan ke %d tidak terdapat dalam queue!\n",x);
        return;
     }
     if(y < 1 || y > length(QueueLagu)){
       printf("Lagu dengan urutan ke %d tidak terdapat dalam queue!\n",y);
       return;
     }

     int i,j;

     char keyX[name_length];
     char keyY[name_length];

    for(j = 0;j<length_name((QueueLagu.buffer[x-1].Judul.TabWord));j++){
        keyX[j] = QueueLagu.buffer[x-1].Judul.TabWord[j];
    }

    for(j = 0;j<length_name((QueueLagu.buffer[y-1].Judul.TabWord));j++){
        keyY[j] = QueueLagu.buffer[y-1].Judul.TabWord[j];
    }
     

     Lagu temp;
     temp = MakeLagu();

     for(i =0;i< length_name(QueueLagu.buffer[x-1].Album.TabWord);i++){
        temp.Album.TabWord[i] = QueueLagu.buffer[x-1].Album.TabWord[i];
     }

    for(i =0;i< length_name(QueueLagu.buffer[x-1].Judul.TabWord);i++){
        temp.Judul.TabWord[i] = QueueLagu.buffer[x-1].Judul.TabWord[i];
     }

    for(i =0;i< length_name(QueueLagu.buffer[x-1].Penyanyi.TabWord);i++){
        temp.Penyanyi.TabWord[i] = QueueLagu.buffer[x-1].Penyanyi.TabWord[i];
     }


    for(i =0;i< length_name(QueueLagu.buffer[y-1].Album.TabWord);i++){
        QueueLagu.buffer[x-1].Album.TabWord[i] = QueueLagu.buffer[y-1].Album.TabWord[i];
     }

    for(i =0;i< length_name(QueueLagu.buffer[y-1].Judul.TabWord);i++){
        QueueLagu.buffer[x-1].Judul.TabWord[i] = QueueLagu.buffer[y-1].Judul.TabWord[i];
     }
     for(i =0;i< length_name(QueueLagu.buffer[y-1].Penyanyi.TabWord);i++){
        QueueLagu.buffer[x-1].Penyanyi.TabWord[i] = QueueLagu.buffer[y-1].Penyanyi.TabWord[i];
     }


    for(i =0;i< length_name(temp.Album.TabWord);i++){
        QueueLagu.buffer[y-1].Album.TabWord[i] = temp.Album.TabWord[i];
     }

    for(i =0;i< length_name(temp.Judul.TabWord);i++){
        QueueLagu.buffer[y-1].Judul.TabWord[i] = temp.Judul.TabWord[i];
     }
    for(i =0;i< length_name(temp.Penyanyi.TabWord);i++){
        QueueLagu.buffer[y-1].Penyanyi.TabWord[i] = temp.Penyanyi.TabWord[i];
     }

    printf("Lagu %s Berhasil ditukar dengan %s\n",keyX,keyY);
    
  }
  
}
void queueRemove(int x){
   int i;
   for(i = x-1;i<length(QueueLagu)-1;i++){
     queueSwap(i,i+1);
   }
   QueueLagu.idxTail--;
}
void queueClear(){
  Lagu randomSong;
  while(isEmpty(QueueLagu)){
    dequeue(&QueueLagu,&randomSong);
  }
  printf("Queue berhasil dikosongkan\n");
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