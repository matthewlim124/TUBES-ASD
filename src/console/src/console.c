#include "console.h"
#include <stdio.h>

//Global Variable 
Queue QueueLagu; 
SetOfWord SetDaftarAlbum, SetDaftarPenyanyi;
ListLagu DaftarLagu; 
Stack StackLagu; 
Lagu currentPlaying; 
Map MapAlbum, MapLagu; 
DaftarPlaylist MapPlaylist;
int idxLagu =0;
boolean statusLoad= false; 
void readCommand(){
  // Construct Set 
  CreateSet(&SetDaftarAlbum);
  CreateSet(&SetDaftarPenyanyi);

  // Construct ListLagu
  MakeListLagu(&DaftarLagu);
  
  // Consturct QueueLagu
  CreateQueue(&QueueLagu);
  
  // Consturct StackLagu 
  CreateEmpty(&StackLagu);

  // Consturct MapLagu
  CreateEmptyMap(&MapLagu);
  
  // Construct MapPlaylist
  CreateEmptyPlaylist(&MapPlaylist);
  
  int i =0; 
  int stopStatus =0;
   while(!stopStatus){
    printf(">> ");
    STARTWORD();
    printf("Iterasi Ke - %d \n",i);
    printf("=================================================\n \n");
    i++;
    if(compareString(currentWord.TabWord, "START")){
      char path[120] = "../../../save/testFile.txt";
      boolean success = loadSave(path);
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
    else if(compareString("LIST", currentWord.TabWord)){
      listCommand();
    }
    else if(compareString("QUEUE", currentWord.TabWord)){
      ADVWORD();
      if(compareString("SONG", currentWord.TabWord)){
        queueSong();
      }
      else if(compareString("PLAYLIST", currentWord.TabWord)){
        queuePlaylist();
      }
      else if(compareString("CLEAR", currentWord.TabWord)){
        queueClear();
        printf("Queue berhasil dikosongkan.\n");
      }
      else if(compareString("SWAP", currentWord.TabWord)){
        queueSwap();
      }
      else if(compareString("REMOVE", currentWord.TabWord)){
        queueRemove();
      }
    }
    else if(compareString("PLAYLIST", currentWord.TabWord)){
      ADVWORD();
      if(compareString(currentWord.TabWord, "CREATE")){
        playlistCreate();
      }
      else if(compareString(currentWord.TabWord, "ADD")){
        ADVWORD();
        if(compareString(currentWord.TabWord, "SONG")){
          playlistAddSong();
        }
        else if(compareString(currentWord.TabWord, "ALBUM")){
          playlistAddAlbum();
        }
      }
      else if(compareString(currentWord.TabWord, "SWAP")){
        playlistSwap();
      }
      else if(compareString(currentWord.TabWord, "DELETE")){
        playlistDelete();
      }
      else if(compareString(currentWord.TabWord, "REMOVE")){
        playlistRemove();
      }
    }
    else if(compareString("PLAY", currentWord.TabWord)){
      ADVWORD();
      if(compareString(currentWord.TabWord, "SONG")){
        playSong(); 
      }
      else if(compareString(currentWord.TabWord, "PLAYLIST")){
        playPlaylist();
      }
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

void playPlaylist(){
  printf("Daftar Playlist : \n");
  for(int i =0; i<MapPlaylist.Count; i++){
    printf("%d. %s\n",i+1, MapPlaylist.Elements[i].Key.TabWord);
  }

  historyClear();
  queueClear();
  START(); //read \n
  printf("Masukkan ID Playlist : ");
  STARTWORD();
  printf("\n");
  int Index = WordToInt(currentWord) -1;
  Word Key = MapPlaylist.Elements[Index].Key;
  printf("Memutar playlist \"\e[1;32m%s\e[m\".\n",Key.TabWord);
  LinkedList PlaylistTerpilih = ValuePlaylist(MapPlaylist, Key);
  addressLinkedList P = First(PlaylistTerpilih); 
  if(P == Nil_LL){
    currentPlaying = MakeLagu();
  }
  else{
    currentPlaying = Info(P);
    Push(&StackLagu, P->info);
    P=Next(P);
  }
  while(P != Nil_LL){
    enqueue(&QueueLagu, P->info);
    Push(&StackLagu, P->info);
    P= Next(P);
  }
  
  //Stack temp; 
  //CreateEmpty(&temp);
  //while(!IsEmptyStack(StackLagu)){
  //  Lagu ta; 
  //  Pop(&StackLagu, &ta);
  //  Push(&temp,ta);
  //}
  //StackLagu = temp; 
  printf("\n");
}

void playSong(){
  printf("Daftar Penyanyi : \n");
  for(int i =0; i< SetDaftarPenyanyi.Count; i++){
    printf("%d. %s\n", i+1, SetDaftarPenyanyi.buffer[i].TabWord);
  }
  printf("\n");
  printf("Masukkan nama penyanyi : "); 
  START(); //Reading \n;
  Word inputUser = takeInput();
  printf("\n");

  if(IsMember(MapAlbum, inputUser)){
    printf("Daftar Album oleh \e[1;32m%s\e[m : \n",inputUser.TabWord);
    SetOfWord temp = Value(MapAlbum, inputUser);
    for(int j = 0; j< temp.Count; j++){
      printf("%d. %s\n",j+1,temp.buffer[j].TabWord);
    }
    

    printf("\nMasukkan Nama Album yang dipilih : ");
    START(); //Reading \n;
    Word inputUser2 = takeInput();
    if(IsMember(MapLagu, inputUser2)){
      printf("Daftar Lagu Album \e[1;32m%s\e[m oleh \e[1;32m%s\e[m :\n",inputUser.TabWord, inputUser2.TabWord);
      SetOfWord tempJudul = Value(MapLagu, inputUser2);
      for(int j = 0; j < tempJudul.Count; j++){
        printf("%d. %s\n",j+1,tempJudul.buffer[j].TabWord);
      }

      printf("Pilih ID Lagu yang dipilih : ");
      START();//Reading \n
      STARTWORD();
      int indexLagu = WordToInt(currentWord) -1 ;
      Lagu newLagu; 
      newLagu.Album = inputUser2; 
      newLagu.Judul = tempJudul.buffer[indexLagu];
      newLagu.Penyanyi = inputUser;

      currentPlaying = newLagu; 
      printf("Memutar lagu \"%s\" oleh \"%s\".\n",currentPlaying.Judul.TabWord, currentPlaying.Penyanyi.TabWord);
      queueClear();
      historyClear();
    }
  }
}

void queueRemove(){
  ADVWORD();
  int IndexTarget = WordToInt(currentWord);
  if(IndexTarget > QueueLagu.idxTail || IndexTarget < QueueLagu.idxHead){
    printf("Lagu dengan urutan ke %d tidak ada.\n", IndexTarget);
  }
  else{
    Queue newQueue; 
    CreateQueue(&newQueue);
    while(!isEmpty(QueueLagu)){
      Lagu temp; 
      int indexQ = QueueLagu.idxHead; 
      dequeue(&QueueLagu, &temp);
      if(indexQ != (IndexTarget-1) )
        enqueue(&newQueue,temp);
    }

    QueueLagu = newQueue;
  }
  printf("\n");
}

void queueSwap(){
  ADVWORD();
  int IndexAwal = WordToInt(currentWord) - 1, IndexAkhir;
  ADVWORD();
  IndexAkhir = WordToInt(currentWord) -1 ;
  if(IndexAwal > QueueLagu.idxTail || IndexAwal< QueueLagu.idxHead){
    printf("Lagu dengan urutan ke %d tidak terdapat dalam queue.\n\n", IndexAwal + 1);
    return; 
  }
  if(IndexAkhir > QueueLagu.idxTail || IndexAkhir <QueueLagu.idxHead){
    printf("Lagu dengan urutan ke %d tidak teradapat dalam queue.\n\n", IndexAkhir + 1);
    return; 
  }
  Lagu akhir, awal; 
  Queue newLagu = QueueLagu; 
  while (!isEmpty(newLagu)){
    Lagu temp;
    int index = newLagu.idxHead; 
    dequeue(&newLagu, &temp);
    if(IndexAkhir == index){
      akhir = temp; 
    }
    else if(IndexAwal == index){
      awal = temp; 
    }
  }
  Queue akhirLagu;
  CreateQueue(&akhirLagu);
  while(!isEmpty(QueueLagu)){
    Lagu temp;
    int index = QueueLagu.idxHead; 
    dequeue(&QueueLagu, &temp);
    if(index == IndexAkhir){
      enqueue(&akhirLagu, awal); 
    }
    else if(index == IndexAwal){
      enqueue(&akhirLagu, akhir);
    }
    else{
    enqueue(&akhirLagu, temp);
    }
  }
  QueueLagu = akhirLagu;
  printf("Lagu \e[1;32m%s\e[m berhasil ditukar dengan \e[1;32m%s\e[m.\n\n",awal.Judul.TabWord, akhir.Judul.TabWord);
}
void queuePlaylist(){
  printf("Daftar Playlist : \n");
  for(int i =0; i<MapPlaylist.Count; i++){
    printf("%d. %s\n",i+1,MapPlaylist.Elements[i].Key.TabWord);
  }
  START(); //Reading \n
  printf("Masukkan ID Playlist : ");
  STARTWORD();
  int Index = WordToInt(currentWord) -1;
  Word Key = MapPlaylist.Elements[Index].Key;
  LinkedList L = ValuePlaylist(MapPlaylist, Key);
  addressLinkedList P = First(L);
  while(P != Nil_LL){
    enqueue(&QueueLagu, Info(P));
    P = P->next;
  }
  printf("Berhasil menambahkan playlist \e[1;32m%s\e[m ke queue.\n\n",Key.TabWord);
}
void historyClear(){
  CreateEmpty(&StackLagu);
}
void queueClear(){
  CreateQueue(&QueueLagu);
}
void queueSong(){
  printf("Daftar Penyanyi : \n");
  for(int i =0; i< SetDaftarPenyanyi.Count; i++){
    printf("%d. %s\n", i+1, SetDaftarPenyanyi.buffer[i].TabWord);
  }
  printf("\n");
  printf("Masukkan nama penyanyi : "); 
  START(); //Reading \n;
  Word inputUser = takeInput();
  printf("\n");

  if(IsMember(MapAlbum, inputUser)){
    printf("Daftar Album oleh \e[1;32m%s\e[m : \n",inputUser.TabWord);
    SetOfWord temp = Value(MapAlbum, inputUser);
    for(int j = 0; j< temp.Count; j++){
      printf("%d. %s\n",j+1,temp.buffer[j].TabWord);
    }
    

    printf("\nMasukkan Nama Album yang dipilih : ");
    START(); //Reading \n;
    Word inputUser2 = takeInput();
    if(IsMember(MapLagu, inputUser2)){
      printf("Daftar Lagu Album \e[1;32m%s\e[m oleh \e[1;32m%s\e[m :\n",inputUser.TabWord, inputUser2.TabWord);
      SetOfWord tempJudul = Value(MapLagu, inputUser2);
      for(int j = 0; j < tempJudul.Count; j++){
        printf("%d. %s\n",j+1,tempJudul.buffer[j].TabWord);
      }

      printf("Pilih ID Lagu yang dipilih : ");
      START();//Reading \n
      STARTWORD();
      int indexLagu = WordToInt(currentWord) -1 ;
      Lagu newLagu; 
      newLagu.Album = inputUser2; 
      newLagu.Judul = tempJudul.buffer[indexLagu];
      newLagu.Penyanyi = inputUser;
      enqueue(&QueueLagu, newLagu);
      printf("\nBerhasil menambahkan Lagu \"%s\" oleh \"%s\" ke queue.",tempJudul.buffer[indexLagu].TabWord,inputUser.TabWord);
    }

  }
  printf("\n");
}
void playlistCreate(){
  STARTWORD();//Reading \n
  printf("Masukkan nama playlist yang ingin dibuat : ");
  Word namaPlaylist= takeInput();
  boolean valid = false; 
  if(!compareString("", namaPlaylist.TabWord)){
    LinkedList emptyList;
    CreateEmptyLL(&emptyList);
    InsertPlaylist(&MapPlaylist, namaPlaylist, emptyList);
    printf("Playlist \e[1;32m%s\e[m berhasil dibuat\n",namaPlaylist.TabWord);
  }
  else{
    printf("Minimal terdapat 3 karakter selain whitespace dalam nama playlist. Silakan coba lagi.\n");
  }
}


void playlistAddSong(){
  printf("Daftar Penyanyi : \n");
  for(int i =0; i< SetDaftarPenyanyi.Count; i++){
    printf("%d. %s\n", i+1, SetDaftarPenyanyi.buffer[i].TabWord);
  }
  printf("\n");
  printf("Masukkan nama penyanyi : "); 
  START(); //Reading \n;
  Word inputUser = takeInput();
  printf("\n");
  
  if(IsMember(MapAlbum, inputUser)){
    printf("Daftar Album oleh \e[1;32m%s\e[m : \n",inputUser.TabWord);
    SetOfWord temp = Value(MapAlbum, inputUser);
    for(int j = 0; j< temp.Count; j++){
      printf("%d. %s\n",j+1,temp.buffer[j].TabWord);
    }


    printf("\nMasukkan Nama Album yang dipilih : ");
    START(); //Reading \n;
    Word inputUser2 = takeInput();
    if(IsMember(MapLagu, inputUser2)){
      printf("Daftar Lagu Album \e[1;32m%s\e[m oleh \e[1;32m%s\e[m :\n",inputUser.TabWord, inputUser2.TabWord);
      SetOfWord tempJudul = Value(MapLagu, inputUser2);
      for(int j = 0; j < tempJudul.Count; j++){
        printf("%d. %s\n",j+1,tempJudul.buffer[j].TabWord);
      }

      printf("Pilih ID Lagu yang dipilih : ");
      START();//Reading \n
      STARTWORD();
      int indexLagu = WordToInt(currentWord) -1 ;
      Lagu newLagu; 
      newLagu.Album = inputUser2; 
      newLagu.Judul = tempJudul.buffer[indexLagu];
      newLagu.Penyanyi = inputUser;
      
      printf("\nDaftar Playlist Pengguna :\n");
      for(int j =0; j<MapPlaylist.Count; j++){
        printf("%d. %s\n",j+1, MapPlaylist.Elements[j].Key.TabWord);
      }

      printf("Masukkan ID Playlist : ");
      STARTWORD();
      printf("\n");
      int Index = WordToInt(currentWord) -1;
      if(MapPlaylist.Elements[Index].Key.Length == 0){
        printf("Tidak ada playlist dengan ID %d dalam daftar playlist pengguna. Silakan coba lagi.", Index);
      }else{
        if(Search(MapPlaylist.Elements[Index].Value, newLagu) == Nil_LL){
          InsVLast(&MapPlaylist.Elements[Index].Value, newLagu);
          printf("\nLagu dengan judul \"%s\" pada album %s oleh penyanyi %s berhasil ditambahkan ke dalam playlist %s.",tempJudul.buffer[indexLagu].TabWord,inputUser2.TabWord, inputUser.TabWord, MapPlaylist.Elements[Index].Key.TabWord);
        }else{
          printf("\nLagu dengan judul \"%s\" pada album %s oleh penyanyi %s sudah terdapat di dalam playlist %s.",tempJudul.buffer[indexLagu].TabWord,inputUser2.TabWord, inputUser.TabWord, MapPlaylist.Elements[Index].Key.TabWord);
        }
      
      } 
    }
    else{
      printf("Album %s tidak ada dalam daftar. Silakan coba lagi.\n",inputUser2.TabWord);
    }
  }
  else{
    printf("Penyanyi %s tidak ada dalam daftar. Silakan coba lagi.\n",inputUser.TabWord);
  }

}

void playlistAddAlbum(){
  printf("Daftar Penyanyi : \n");
  for(int i =0; i< SetDaftarPenyanyi.Count; i++){
    printf("%d. %s\n", i+1, SetDaftarPenyanyi.buffer[i].TabWord);
  }
  printf("\n");
  printf("Masukkan nama penyanyi : "); 
  START(); //Reading \n;
  Word inputUser = takeInput();
  printf("\n");

  if(IsMember(MapAlbum, inputUser)){
    printf("Daftar Album oleh \e[1;32m%s\e[m : \n",inputUser.TabWord);
    SetOfWord temp = Value(MapAlbum, inputUser);
    for(int j = 0; j< temp.Count; j++){
      printf("%d. %s\n",j+1,temp.buffer[j].TabWord);
    }

    printf("\nMasukkan Nama Album yang dipilih : ");
    START(); //Reading \n;
    Word inputUser2 = takeInput();
    printf("\n");
    if(IsMember(MapLagu, inputUser2)){
      
      printf("Daftar Playlist Pengguna :\n");
      
      for(int j =0; j<MapPlaylist.Count; j++){
        printf("%d. %s\n",j+1, MapPlaylist.Elements[j].Key.TabWord);
      }

      printf("\nMasukkan ID Playlist : ");
      START();// Reading \n
      STARTWORD();
      printf("\n");
      int Index = WordToInt(currentWord) -1;
      Word Key = MapPlaylist.Elements[Index].Key; 
      if(IsEmptyWord(Key)){
        printf("Tidak ada playlist dengan ID %d dalam daftar playlist pengguna. Silakan coba lagi.\n", Index+1);
      }else{
        SetOfWord tempJudul = Value(MapLagu, inputUser2);

        Lagu newLagu;
        newLagu.Album = inputUser2;
        newLagu.Penyanyi = inputUser;
        for(int j = 0; j < tempJudul.Count; j++){
          newLagu.Judul = tempJudul.buffer[j];
          if(Search(MapPlaylist.Elements[Index].Value, newLagu) == Nil_LL){
            InsVLast(&MapPlaylist.Elements[Index].Value, newLagu);
            
          }

        }
        printf("Album dengan judul \e[1;32m%s\e[m berhasil ditambahkan ke dalam playlist pengguna \e[1;32m%s\e[m.\n",inputUser2.TabWord, MapPlaylist.Elements[Index].Key.TabWord);

      }
      
    }else{
      printf("Album %s tidak ada dalam daftar. Silakan coba lagi.\n",inputUser2.TabWord);
    }


  }else{
    printf("Penyanyi %s tidak ada dalam daftar. Silakan coba lagi.\n",inputUser.TabWord);
  }
  printf("\n");
}

void playlistSwap(){
  ADVWORD();
  int playlist_idx = WordToInt(currentWord) - 1;
  ADVWORD();
  int idx1 = WordToInt(currentWord) - 1;
  ADVWORD();
  int idx2 = WordToInt(currentWord) - 1;

  if(MapPlaylist.Elements[playlist_idx].Key.Length == 0){
    printf("Tidak ada playlist dengan playlist ID %d\n", playlist_idx + 1);
  }else{
    if(idx1 < 0 || idx1 > NbElmt(MapPlaylist.Elements[playlist_idx].Value) - 1){
      printf("Tidak ada lagu dengan urutan %d di playlist \"%s\"\n", idx1 + 1, MapPlaylist.Elements[playlist_idx].Key.TabWord);
      return;
    }
    if(idx2 < 0 || idx2 > NbElmt(MapPlaylist.Elements[playlist_idx].Value) - 1){
      printf("Tidak ada lagu dengan urutan %d di playlist \"%s\"\n", idx2 + 1, MapPlaylist.Elements[playlist_idx].Key.TabWord);
      return;
    }
    addressLinkedList p1 = MapPlaylist.Elements[playlist_idx].Value.First;
    addressLinkedList p2 = MapPlaylist.Elements[playlist_idx].Value.First;
    Lagu temp;
    
    for(int j = 0; j < idx1; j++){
      p1 = Next(p1);
    }
    temp = Info(p1);

    for(int j = 0; j < idx2; j++){
      p2 = Next(p2);
    }
    
    Info(p1) = Info(p2);
    Info(p2) = temp;

    printf("Berhasil menukar lagu dengan nama \e[1;32m%s\e[m dengan \e[1;32m%s\e[m di playlist \e[1;32m%s\e[m\n", temp.Judul.TabWord , Info(p1).Judul.TabWord , MapPlaylist.Elements[playlist_idx].Key.TabWord);
  }
 
}

void playlistRemove(){
  ADVWORD();
  int playlist_idx = WordToInt(currentWord) - 1;
  ADVWORD();
  int idx = WordToInt(currentWord) - 1;

  if(MapPlaylist.Elements[playlist_idx].Key.Length == 0){
    printf("Tidak ada playlist dengan ID %d\n", playlist_idx + 1);
  }else{
    if(idx < 0 || idx > NbElmt(MapPlaylist.Elements[playlist_idx].Value) - 1){
      printf("Tidak ada lagu dengan urutan %d di playlist \"%s\" \n", idx + 1, MapPlaylist.Elements[playlist_idx].Key.TabWord);
      
    }else{
      Word Key = MapPlaylist.Elements[playlist_idx].Key; 
      LinkedList t = ValuePlaylist(MapPlaylist, Key);
      addressLinkedList p = t.First;
      for(int j = 0; j < idx; j++){
        p = Next(p);
      }
      Lagu temp= p->info;
      DelP(&t, temp);
      MapPlaylist.Elements[playlist_idx].Value = t;
      printf("Lagu \e[1;32m%s\e[m oleh \e[1;32m%s\e[m telah dihapus dari playlist \e[1;32m%s\e[m!\n", temp.Judul.TabWord, temp.Penyanyi.TabWord, MapPlaylist.Elements[playlist_idx].Key.TabWord);
    }
  }
}

void playlistDelete(){
  printf("Daftar Playlist Pengguna :\n");
      
  for(int j =0; j<MapPlaylist.Count; j++){
    printf("%d. %s\n",j+1, MapPlaylist.Elements[j].Key.TabWord);
  }

  printf("Masukkan ID Playlist : ");
  START();// Reading \n
  STARTWORD();
  printf("\n");
  int Index = WordToInt(currentWord) -1;
  
  if(MapPlaylist.Elements[Index].Key.Length == 0){
    printf("Tidak ada playlist dengan ID %d dalam daftar playlist pengguna. Silakan coba lagi.", Index);
  }else{
    printf("Playlist ID %d dengan judul \e[1;32m%s\e[m berhasil dihapus.", Index+1, MapPlaylist.Elements[Index].Key.TabWord);
    DeletePlaylist(&MapPlaylist, MapPlaylist.Elements[Index].Key);
  }
  printf("\n");
}


void statusCommand(){
  Lagu tempLagu = currentPlaying; 
  if(IsEmptyLagu(currentPlaying)){
    printf("Now Playing :\nNo songs have been played yet. Please search for a song to begin playback.\n\n");
  }
  else printf("Now Playing :\n%s - %s - %s\n\n", tempLagu.Penyanyi.TabWord, tempLagu.Judul.TabWord, tempLagu.Album.TabWord);
  int idx =1; 
  printf("Queue : \n");
  Queue newLagu = QueueLagu;
  while(!isEmpty(newLagu) && !isEmpty(QueueLagu)){
    dequeue(&newLagu,&tempLagu);
    printf("%d. %s - %s - %s\n",idx,tempLagu.Penyanyi.TabWord, tempLagu.Judul.TabWord, tempLagu.Album.TabWord);
    idx++;
  }
  if(isEmpty(QueueLagu)){
    printf("Your queue is empty.\n");
  }
  printf("\n");
}

void songPrev(){
  Lagu tempLagu; 
  if(!IsEmptyStack(StackLagu)){
    Pop(&StackLagu,&tempLagu);
    printf("Memutar lagu sebelumnya\n\"%s\" oleh \"%s\"\n",tempLagu.Judul.TabWord, tempLagu.Penyanyi.TabWord);
    currentPlaying = tempLagu;
  }
  else{
    if(!IsEmptyLagu(currentPlaying))printf("Riwayat lagu kosong, memutar kembali lagu\n\"%s\" oleh \"%s\"\n",currentPlaying.Judul.TabWord, currentPlaying.Penyanyi.TabWord);
    else{
      printf("Riwayat lagu kosong, sedang tidak memutar lagu\nTidak memutar lagu apapun.\n");
    }
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
    if(!IsEmptyLagu(currentPlaying))printf("Queue kosong, memutar kembali lagu\n\"%s\" oleh \"%s\"\n",tempLagu.Judul.TabWord, tempLagu.Penyanyi.TabWord);
  }

  if(IsEmptyLagu(currentPlaying)) printf("Tidak ada lagu yang sedang diputar\nTidak memutar lagu apapun.\n");

}
boolean loadSave(char *filePath){
  printf("Lokasi File : %s\n",filePath);
  FILE *file = freopen(filePath, "r",stdin);

  // If save file not exists
  if (file == NULL) {
    printf("file can't be opened \n");
    freopen("CONIN$", "r", stdin);
    return false; 
  }
  
  // If save file exists
  else{
    defaultSave();
    Word inputCurrent= takeInput();
    currentPlaying.Penyanyi = inputCurrent;

    inputCurrent = takeInput();
    currentPlaying.Album = inputCurrent;

    inputCurrent = takeInput();
    currentPlaying.Judul = inputCurrent;
    printf("Current Playing : %s - %s - %s\n", currentPlaying.Penyanyi.TabWord, currentPlaying.Album.TabWord, currentPlaying.Judul.TabWord);

    STARTWORD();
    int index = WordToInt(currentWord); 

    printf("\nInput Queue\n================================\n\n");
    for(int i =0 ;i < index; i++){
      Lagu tempLagu = MakeLagu();
      // Input dari save, Penyanyi ke ADT Lagu
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

      // Input dari save, Album ke ADT Lagu
      STARTWORD();
      Word tempAlbum = currentWord;
      while(!isEndWord() && !EOP){
        ADVWORD();
        SetWord(&space, " ");
        ConcatWord(currentWord, &space);
        ConcatWord(space, &tempAlbum);
      }
      // Input dari save, Judul ke ADT Lagu 
      STARTWORD();
      Word tempJudul = currentWord; 
      while(!isEndWord()  && !EOP){
        ADVWORD();
        SetWord(&space, " ");
        ConcatWord(currentWord, &space);
        ConcatWord(space, &tempJudul);
      }

      // Output Lagu dari file Save untuk testing
      tempLagu.Judul = tempJudul;
      tempLagu.Album = tempAlbum; 
      printf("Penyanyi : %s\n",tempLagu.Penyanyi.TabWord);
      printf("Album : %s\n",tempLagu.Album.TabWord);
      printf("Judul : %s\n", tempLagu.Judul.TabWord);
      DaftarLagu.A[i] = tempLagu;
      AddSet(&SetDaftarAlbum, tempLagu.Album);
      AddSet(&SetDaftarPenyanyi, tempLagu.Penyanyi);
      printf("Panjang Set : %d\n", SetDaftarPenyanyi.Count);

      //printf("Penyanyi : %s\n",SetDaftarLagu.buffer[idxLagu].Penyanyi.TabWord);
      //printf("Album : %s\n",SetDaftarLagu.buffer[idxLagu].Album.TabWord);
      //printf("Judul : %s\n", SetDaftarLagu.buffer[idxLagu].Judul.TabWord);
      
      idxLagu++;
      printf("\n");

    } //End For
    
    //End of First Part
    
    //Taking input from save file to map album and Songs
    printf("Mapping...%d\n", SetDaftarPenyanyi.Count);
    for(int i = 0; i<SetDaftarPenyanyi.Count; i++){
      SetOfWord newSetA; 
      CreateSet(&newSetA);
      for(int j = 0; j< idxLagu; j++){
        if(CompareWord(DaftarLagu.A[j].Penyanyi, SetDaftarPenyanyi.buffer[i])){
          AddSet(&newSetA, DaftarLagu.A[j].Album); 
        }
      }
      Insert(&MapAlbum, SetDaftarPenyanyi.buffer[i], newSetA);
    }


    for(int i = 0; i<SetDaftarAlbum.Count; i++){
      SetOfWord newSetJ; 
      CreateSet(&newSetJ);
      for(int j = 0; j< idxLagu; j++){
        if(CompareWord(DaftarLagu.A[j].Album, SetDaftarAlbum.buffer[i])){
          AddSet(&newSetJ, DaftarLagu.A[j].Judul); 
        }
      }
      Insert(&MapLagu, SetDaftarAlbum.buffer[i], newSetJ);
    }
    printf("Printing Map...\n");
    printf("Count Num of Map : %d\n", MapAlbum.Count);
    for(int i= 0; i<MapAlbum.Count; i++){
      printf("Key : %s\n", MapAlbum.Elements[i].Key.TabWord); 
      for(int j =0 ;j< LengthSet(MapAlbum.Elements[i].Value) ; j++){
        printf("Elemen ke - %d : %s\n",j+1,MapAlbum.Elements[i].Value.buffer[j].TabWord);
      }
    }

    //End map input 
      
    
    //Taking for Input (Stack - History Song)
    STARTWORD();
    int idxStack = WordToInt(currentWord) ;
    printf("\nInput Stack\n========================================\n\n");
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

    // End of Taking input for Stack
    
    // Start Taking input for PLAYLIST

    STARTWORD();
    int jumlahPlaylist=WordToInt(currentWord);
    printf("Jumlah Playlist : %d\n", jumlahPlaylist);
    for(int i =0; i< jumlahPlaylist; i++){
      LinkedList temp; 
      CreateEmptyLL(&temp);
      START();
      int jumlahLagu = currentChar -'0';
      //Start Reading input for name of playlist
      STARTWORD();
      Word tempPlaylist = currentWord;
      Word space;
      while(!isEndWord() && !EOP){
        ADVWORD();
        SetWord(&space, " ");
        ConcatWord(currentWord, &space);
        ConcatWord(space, &tempPlaylist);
      }
      printf("Name of Playlist: %s\n",tempPlaylist.TabWord);
      printf("Banyak Lagu dalam Album %s : %d\n",tempPlaylist.TabWord,jumlahLagu);

      for(int j =0; j< jumlahLagu; j++){
        Lagu tempLagu = MakeLagu();
        // Input dari save, Penyanyi ke ADT Lagu
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

        // Input dari save, Album ke ADT Lagu
        STARTWORD();
        Word tempAlbum = currentWord;
        while(!isEndWord() && !EOP){
          ADVWORD();
          SetWord(&space, " ");
          ConcatWord(currentWord, &space);
          ConcatWord(space, &tempAlbum);
        }

        tempLagu.Album = tempAlbum;

        // Input dari save, Judul ke ADT Lagu 
        STARTWORD();
        Word tempJudul = currentWord; 
        while(!isEndWord()  && !EOP){
          ADVWORD();
          SetWord(&space, " ");
          ConcatWord(currentWord, &space);
          ConcatWord(space, &tempJudul);
        }
        tempLagu.Judul = tempJudul;

        printf("Judul Lagu ke-%d : %s\n",j+1, tempJudul.TabWord );

        // Using Map of LinkedList as Playlist   
        
        addressLinkedList t = Alokasi(tempLagu);
        InsertLast(&temp, t);
        printf("Dalam LinkedList : %s, %s, %s\n",t->info.Penyanyi.TabWord, t->info.Album.TabWord, t->info.Judul.TabWord);
      }
      InsertPlaylist(&MapPlaylist, tempPlaylist, temp);
    }
    //End of taking input for playlist
    
    // Checking for Map playlist; 
    printf("\nTesting for MAP\n");
    Word newW;
    SetWord(&newW,"BLACKPINK My Top Three");
    LinkedList testing = ValuePlaylist(MapPlaylist, newW);
    addressLinkedList P; 
    P = First(testing);
    while(P != Nil_LL){
      printf("%s, %s, %s\n",P->info.Album.TabWord, P->info.Judul.TabWord, P->info.Penyanyi.TabWord);
      P = P->next;
    }

  }
  freopen("CONIN$", "r", stdin);
  return true; 
}

boolean defaultSave(){
  printf("Default Save\n|=======================|\n");
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
  return true; 
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
  if(compareString(currentWord.TabWord, "DEFAULT")){
    printf("Daftar Penyanyi : \n");
    for(int i =0; i<SetDaftarPenyanyi.Count; i++){
      printf("%d. %s\n",i+1, SetDaftarPenyanyi.buffer[i].TabWord);
    }
    
    printf("Ingin melihat album yang ada? (Y/N) : ");
    STARTWORD();//Reading Empty Spaces
    STARTWORD();
    
    if(compareString(currentWord.TabWord, "Y")){

      printf("Pilih penyanyi untuk melihat album mereka : ");
      STARTWORD();//Reading Empty Spaces
      Word newWord = takeInput();
      printf("Daftar Album oleh %s :\n", newWord.TabWord);
      if(IsMember(MapLagu, newWord)){
        for(int i =0; i< Value(MapLagu, newWord).Count; i++){
          printf("%d. %s\n",i+1, Value(MapLagu, newWord).buffer[i].TabWord);
        }
      }

      printf("Pilih album untuk melihat lagu di dalam album : ");
      STARTWORD();
      newWord = takeInput();
      printf("Daftar lagu di %s : \n", newWord.TabWord);
      if(IsMember(MapAlbum, newWord)){
        for(int i = 0; i<Value(MapAlbum, newWord).Count; i++){
          printf("%d. %s\n", i+1, Value(MapAlbum, newWord).buffer[i].TabWord); 
        }
      }
    }
    else{
      return; 
    }
    printf("\n");
   
  }
  else if(compareString(currentWord.TabWord, "PLAYLIST")){
    printf("Daftar playlist yang kamu miliki : \n");
 
    for(int i =0; i< MapPlaylist.Count; i++){
      printf("%d. %s\n",i+1,MapPlaylist.Elements[i].Key.TabWord);
    }
    
    START(); //Reading \n
    printf("Pilih ID Playlist : ");
    STARTWORD();
    int index = WordToInt(currentWord) - 1;
    printf("\n");
    if(MapPlaylist.Elements[index].Key.Length == 0){
      printf("ID tidak terdaftar\n");
    }
    else{
      Word Key = MapPlaylist.Elements[index].Key; 
      LinkedList t = ValuePlaylist(MapPlaylist, Key);
      printf("Daftar Lagu dalam \e[1;32m%s\e[m :\n", Key.TabWord);
      addressLinkedList P = t.First; 
      int cnt = 1;
      while(P!=Nil_LL){
        printf("%d. %s\n",cnt,Info(P).Judul.TabWord);
        cnt++;
        P = Next(P);
      }
    }

    if(MapPlaylist.Count == 0){
      printf("Kamu tidak memiliki playlist\n");
    }
  }
  else{
    printf("Command tidak bisa dieksekusi!\n");
  }
  printf("\n");
  START(); //Reading \n
}

void quitCommand(int *stopStatus){
  printf("Apakah kamu ingin menyimpan data sesi sekarang? "); 
  STARTWORD();// Reading Empty Space
  STARTWORD();
  printf("\n");
  if(compareString(currentWord.TabWord,"Y")){
    printf("Saving....\n");
    printf("Selesai SAVE\n\n");
  }
  *stopStatus= 1;   
  printf("Kamu keluar dari WayangWave.\nDadah ^_^/");
  }


/*================ Extra Features ================*/

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

boolean compareString(char *a, char *b){
  int i =0;
  while(a[i] != '\0' && b[i] != '\0'){
    if(a[i]!=b[i]) return false;
    i++;
  }
  if(a[i] != b[i]) return false; 
  return true; 
}

