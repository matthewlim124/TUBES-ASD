#include "console.h"
#include <stdio.h>

//Global Variable 
Queue QueueLagu; 
SetOfWord SetDaftarAlbum, SetDaftarPenyanyi, SetDaftarUser;
ListLagu DaftarLagu; 
Stack StackLagu; 
Lagu currentPlaying; 
Map MapAlbum, MapLagu; 
Playlist MapPlaylist;

// For User
Stack arrOfStack[MaxUser];
Playlist arrOfPlaylist[MaxUser];
Queue arrOfQueue[MaxUser];
Lagu arrOfLagu[MaxUser];

int statusRun = 0; 
int idxLagu = 0;
int userId = 0; 
boolean statusLoad, userLogin = false; 
void readCommand(int status){
  statusRun = status;
  // Construct Set 
  CreateSet(&SetDaftarAlbum);
  CreateSet(&SetDaftarPenyanyi);
  CreateSet(&SetDaftarUser);

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
  
  boolean masukSesi = false; 
  int stopStatus =0;
  int cnt =0;
  boolean statusEnter = false; 
  while(!stopStatus){
    if(cnt != 0 && !statusEnter)START();
    statusEnter = false;
    printf(">> ");
    STARTWORD();
    cnt++;
    if(compareString(currentWord.TabWord, "START")){
      if(masukSesi){
        printf("Sesi sudah berjalan \n");
        continue;
      }
      char path[120] = "../save/defSave.txt";
      boolean success = loadSave(path);
      if(success){
        printf("START berhasil dijalankan\n");
        masukSesi = true; 
        statusEnter = true;
      }
      else{
        printf("Start gagal dijalankan\n");
        return; 
      }
    }

    else if(compareString(currentWord.TabWord, "LOAD")){
      ADVWORD();
      if(masukSesi){
        printf("Sesi sudah berjalan \n");
        continue;
      }
      char path[120] = "../save/";
      for(int i =0; i< currentWord.Length; i++){
        path[i + 8] = currentWord.TabWord[i]; 
      }
      boolean success = loadSave(path);
      if (success){
        printf("File konfigurasi '%s' aplikasi berhasil dibaca. Wayangwave berhasil dijalankan\n", path);
        masukSesi = true;
        statusEnter = true; 
      }
      else printf("File konfigurasi aplikasi gagal dibaca.\n");
    }

    else if(compareString("HELP", currentWord.TabWord)){
      if(!masukSesi){
        printf("=====[ Menu Help WayangWave ]=====\n");
        printf("1. START -> Untuk masuk sesi baru\n");
        printf("2. LOAD -> Untuk memulai sesi berdasarkan file konfigurasi\n");
      } else {
        printf("=====[ Menu Help WayangWave ]=====\n");
        printf("1. LIST -> Untuk menampilkan daftar lagu, playlist, album, dan lagu\n");
        printf("2. PLAY -> Untuk memulai suatu lagu\n");
        printf("3. QUEUE -> Untuk mengatur antrian lagu\n");
        printf("4. SONG -> Untuk mengatur lagu yang sedang diputar\n");
        printf("5. PLAYLIST -> Untuk mengatur playlist\n");
        printf("6. STATUS -> Untuk menampilkan status lagu yang sedang diputar dan antrian lagu\n");
        printf("7. HELP -> Untuk menampilkan menu help\n");
        printf("8. SAVE -> Untuk menyimpan state ke dalam file\n");
        printf("9. QUIT -> Untuk keluar dari sesi\n");
      }
    }

    else if(!masukSesi){
      printf("Silahkan jalankan perintah \e[1;32mSTART\e[m atau \e[1;32mLOAD nama_save.txt;\e[m \n");
    }

    else if(compareString("LOGIN", currentWord.TabWord)){
      if(userLogin){
        printf("User sudah login dengan username %s\n",SetDaftarUser.buffer[userId-1].TabWord);
        
      }
      else{
        START();
        printf("Masukkan username user Wayangwave : ");
        Word inputUser = takeInput();
        currentWord = inputUser; 
        if(IsIn(SetDaftarUser, currentWord)){
          for(int i =0; i< SetDaftarUser.Count; i++){
            if(CompareWord(SetDaftarUser.buffer[i], currentWord)){
              userLogin = true; 
              userId = i+1; 
              printf("Welcome \e[1;32m%s\e[m\n",currentWord.TabWord);
              LoginCommand();
              break;
            }
          }
        }
        else{
          printf("Tidak ada user dengan username \e[1;31m%s\e[m\nPlease \e[1;32mRegister\e[m or \e[1;32mLogin\e[m\n", currentWord.TabWord);
        }
      }
    }
    else if(compareString("REGISTER", currentWord.TabWord)){
      START();
      if(!userLogin)registerCommand();
      else{
        printf("Sudah melakukan login dengan username %s \n", SetDaftarUser.buffer[userId-1].TabWord);
      }
    }
    else if(!userLogin && userId == 0){
      printf("Silahkan \e[1;32mLOGIN\e[m atau \e[1;32mREGISTER\e[m terlebih dahulu.\n");
      while(!endWord){
        ADVWORD();
      }
    }
    else if(compareString("LOGOUT", currentWord.TabWord)){
      updateSaveUser();
      cleanUser();
      printf("Logout dari akun %s\n",SetDaftarUser.buffer[userId-1].TabWord);
      userLogin = false; 
      userId = 0; 
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
      saveCommand(false);
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
    else{
      printf("Perintah tidak valid silahkan jalankan \e[1;32mHELP\e[m untuk melihat daftar perintah\n");
      while(!endWord){
        ADVWORD();
      }
    }
  }
}

void cleanUser(){
  currentPlaying = MakeLagu();
  CreateEmpty(&StackLagu);
  CreateQueue(&QueueLagu);
  CreateEmptyPlaylist(&MapPlaylist);
}

void registerCommand(){
  printf("Masukkan username yang mau didaftarkan : "); 
  Word userInput = takeInput();
  if(IsIn(SetDaftarUser, userInput)){
    printf("User sudah terdaftar, silahkan login\n");
  }
  else{
    AddSet(&SetDaftarUser, userInput);
    printf("User %s berhasil terdaftar..\nLogin sebagai %s..\n",userInput.TabWord, userInput.TabWord);
    printf("Welcome \e[1;32m%s\e[m \n", userInput.TabWord);
    cleanUser();
    userLogin =true; 
    userId = SetDaftarUser.Count; 
    arrOfLagu[userId] = currentPlaying;
    arrOfPlaylist[userId] = MapPlaylist; 
    arrOfStack[userId] = StackLagu;
    arrOfQueue[userId] = QueueLagu;
  }
}

void LoginCommand(){
  currentPlaying = MakeLagu();
  currentPlaying = arrOfLagu[userId];

  StackLagu = arrOfStack[userId];
  QueueLagu = arrOfQueue[userId];
  MapPlaylist = arrOfPlaylist[userId];

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
  if(Key.Length == 0){
    printf("Tidak ada playlist dengan ID \e[1;31m%d\e[m dalam daftar playlist pengguna. Silakan coba lagi.\n", Index + 1);
  }
  else{
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
  }
  /* printf("Memutar playlist \"\e[1;32m%s\e[m\".\n",Key.TabWord);
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
  } */
  
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
    else {  
      printf("Album \e[1;31m%s\e[m tidak ada dalam daftar. Silakan coba lagi.\n", inputUser2.TabWord);

    }
  }
  else {
    printf("Penyanyi \e[1;31m%s\e[m tidak ada dalam daftar. Silakan coba lagi.\n", inputUser.TabWord);
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
    else {  
      printf("Album \e[1;31m%s\e[m tidak ada dalam daftar. Silakan coba lagi.\n", inputUser2.TabWord);
    }
  }
  else {
    printf("Penyanyi \e[1;31m%s\e[m tidak ada dalam daftar. Silakan coba lagi.\n", inputUser.TabWord);
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
    START();
    Word inputUser2 = takeInput();
    if(IsMember(MapLagu, inputUser2)){
      printf("Daftar Lagu Album \e[1;32m%s\e[m oleh \e[1;32m%s\e[m :\n",inputUser.TabWord, inputUser2.TabWord);
      SetOfWord tempJudul = Value(MapLagu, inputUser2);
      for(int j = 0; j < tempJudul.Count; j++){
        printf("%d. %s\n",j+1,tempJudul.buffer[j].TabWord);
      }

      printf("Pilih ID Lagu yang dipilih : ");
      START();
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
      START();
      STARTWORD();
      printf("\n");
      int Index = WordToInt(currentWord) -1;
      if(MapPlaylist.Elements[Index].Key.Length == 0){
        printf("Tidak ada playlist dengan ID %d dalam daftar playlist pengguna. Silakan coba lagi.", Index);
      }else{
        if(Search(MapPlaylist.Elements[Index].Value, newLagu) == Nil_LL){
          InsVLast(&MapPlaylist.Elements[Index].Value, newLagu);
          printf("Lagu dengan judul \"%s\" pada album %s oleh penyanyi %s berhasil ditambahkan ke dalam playlist %s.\n",tempJudul.buffer[indexLagu].TabWord,inputUser2.TabWord, inputUser.TabWord, MapPlaylist.Elements[Index].Key.TabWord);
        }else{
          printf("\nLagu dengan judul \"%s\" pada album %s oleh penyanyi %s sudah terdapat di dalam playlist %s.\n",tempJudul.buffer[indexLagu].TabWord,inputUser2.TabWord, inputUser.TabWord, MapPlaylist.Elements[Index].Key.TabWord);
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
  Word terminal;
  if(statusRun == 1){
    SetWord(&terminal, "/dev/tty");
  }
  else if(statusRun == 2){
    SetWord(&terminal, "CONIN$");
  }
  // If save file not exists
  if (file == NULL) {
    printf("file can't be opened \n");
    freopen(terminal.TabWord, "r", stdin);
    return false; 
  }
  
  // If save file exists
  else{
    defaultSave();
    for(int abcd = 0 ; abcd < SetDaftarUser.Count; abcd++){
      CreateQueue(&QueueLagu);
      CreateEmpty(&StackLagu);
      CreateEmptyPlaylist(&MapPlaylist);
      currentPlaying = MakeLagu();

      Word inputCurrent= takeInput();
      if(!compareString(inputCurrent.TabWord, "-")){
        currentPlaying.Penyanyi = inputCurrent;

        inputCurrent = takeInput();
        currentPlaying.Album = inputCurrent;

        inputCurrent = takeInput();
        currentPlaying.Judul = inputCurrent;
      }
      else{
        currentPlaying = MakeLagu();
      }
      arrOfLagu[abcd+1] = currentPlaying; 

      STARTWORD();
      int index = WordToInt(currentWord); 

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
        //printf("Penyanyi : %s\n",tempLagu.Penyanyi.TabWord);
        //printf("Album : %s\n",tempLagu.Album.TabWord);
        //printf("Judul : %s\n", tempLagu.Judul.TabWord);
        //DaftarLagu.A[i] = tempLagu;
        //AddSet(&SetDaftarAlbum, tempLagu.Album);
        //AddSet(&SetDaftarPenyanyi, tempLagu.Penyanyi);
        //printf("Panjang Set : %d\n", SetDaftarPenyanyi.Count);
        //
        enqueue(&QueueLagu, tempLagu);
        idxLagu++;
        

      } //End For
      arrOfQueue[abcd+1] = QueueLagu; 
      
      //End of First Part
         
      //Taking for Input (Stack - History Song)
      STARTWORD();
      int idxStack = WordToInt(currentWord) ;
      //printf("\nInput Stack\n========================================\n\n");
      //printf("Second Input : %d\n", idxStack);
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
        //printf("Penyanyi : %s\nAlbum : %s\nJudul : %s\n\n", testLagu.Penyanyi.TabWord, testLagu.Album.TabWord, testLagu.Judul.TabWord);
      }
      arrOfStack[abcd + 1] = StackLagu; 

      // End of Taking input for Stack
      
      // Start Taking input for PLAYLIST

      STARTWORD();
      int jumlahPlaylist=WordToInt(currentWord);
      //printf("Jumlah Playlist : %d\n", jumlahPlaylist);
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
        //printf("Name of Playlist: %s\n",tempPlaylist.TabWord);
        //printf("Banyak Lagu dalam Album %s : %d\n",tempPlaylist.TabWord,jumlahLagu);

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

          //printf("Judul Lagu ke-%d : %s\n",j+1, tempJudul.TabWord );

          // Using Map of LinkedList as Playlist   
          
          addressLinkedList t = Alokasi(tempLagu);
          InsertLast(&temp, t);
          //printf("Dalam LinkedList : %s, %s, %s\n",t->info.Penyanyi.TabWord, t->info.Album.TabWord, t->info.Judul.TabWord);
        }
        InsertPlaylist(&MapPlaylist, tempPlaylist, temp);
      }
      //End of taking input for playlist
      arrOfPlaylist[abcd+1]= MapPlaylist;
      
      // Checking for Map playlist; 
      //printf("\nTesting for Playlist\n");
      //Word newW;
      //SetWord(&newW,"BLACKPINK My Top Three");
      //LinkedList testing = ValuePlaylist(MapPlaylist, newW);
      //addressLinkedList P; 
      //P = First(testing);
      //while(P != Nil_LL){
      //  printf("%s, %s, %s\n",P->info.Album.TabWord, P->info.Judul.TabWord, P->info.Penyanyi.TabWord);
      //  P = P->next;
      //}
    }
  }
  freopen(terminal.TabWord, "r", stdin);
  return true; 
}

boolean defaultSave(){
  STARTWORD();
  int idxP = WordToInt(currentWord);
  //printf("Jumlah Penyanyi : %d\n", idxP);
  for(int k = 0; k < idxP; k++){
    STARTWORD();
    int idxA = WordToInt(currentWord);
    //printf("Jumlah Album : %d\n", idxA);
    
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
    //printf("Penyanyi : %s\n", tempPenyanyi.TabWord);
    AddSet(&SetDaftarPenyanyi, tempPenyanyi);
    SetOfWord newSet; 
    CreateSet(&newSet);

    for(int j = 0; j < idxA; j++){
      STARTWORD();
      int idxJ = WordToInt(currentWord); 
      //printf("Jumlah Judul : %d\n", idxJ);
      
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
      //printf("Album : %s\n", tempAlbum.TabWord);
      AddSet(&newSet, tempAlbum);

      SetOfWord setJudul; 
      CreateSet(&setJudul);

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

        AddSet(&setJudul, tempJudul);
        
        //printf("Judul : %s\n", tempJudul.TabWord);  
      }

      Insert(&MapLagu, tempAlbum, setJudul);
    }
      Insert(&MapAlbum, tempPenyanyi, newSet);
  }

  // Read Users Username
  
  STARTWORD();
  int JumlahInput = WordToInt(currentWord);
  int numOfUser = JumlahInput;
  for(int i = 0 ; i < JumlahInput; i++){
    STARTWORD();
    Word tempInput = currentWord;
    Word space;
    while(!isEndWord() && !EOP){
      ADVWORD();
      SetWord(&space, " ");
      ConcatWord(currentWord, &space);
      ConcatWord(space, &tempInput);
    }

    AddSet(&SetDaftarUser, tempInput);  
    //printf("User : %s\n", SetDaftarUser.buffer[i].TabWord);  
  }
  
  /*Notes program akan error (infinite loop) 
   * apabila pada save default tidak diakhiri \n
  */ 
  return true; 
}
void updateSaveUser(){
  arrOfPlaylist[userId] = MapPlaylist;
  arrOfLagu[userId] = currentPlaying;
  arrOfStack[userId] = StackLagu;
  arrOfQueue[userId] = QueueLagu;
}

void saveCommand(boolean Quit){
  updateSaveUser();

  Word filePath; 
  if(!Quit){
    ADVWORD();
    SetWord(&filePath, "../save/");
    ConcatWord(currentWord,&filePath);
  }
  else{
    SetWord(&filePath, "../save/defSave.txt");
  }
  printf("%s\n",filePath.TabWord);
  FILE *file = fopen(filePath.TabWord, "w");
  
  //BAGIAN MAP LAGU dan ALBUM 
  //Print Jumlah Penyanyi
  int numOfSinger = SetDaftarPenyanyi.Count;
  fprintf(file, "%d\n", numOfSinger);
  
  //Nama Penyanyi dan Jumlah Album dari Penyanyi
  for(int i = 0; i < numOfSinger; i++){
    //Banyak Album 
    SetOfWord newSet = Value(MapAlbum, SetDaftarPenyanyi.buffer[i]);
    int numOfAlbum = newSet.Count;
    fprintf(file, "%d %s\n", numOfAlbum, SetDaftarPenyanyi.buffer[i].TabWord); //Menulis Penyanyi
    
    for(int j = 0; j < numOfAlbum; j++){
      SetOfWord setLagu = Value(MapLagu, newSet.buffer[j]);
      int numOfSongs = setLagu.Count;
      fprintf(file, "%d %s\n",numOfSongs, newSet.buffer[j].TabWord);
      for(int k = 0;k < numOfSongs; k++){
        fprintf(file, "%s\n",setLagu.buffer[k].TabWord);
      }
    }
  }
  //Bagian Daftar User 
  fprintf(file, "%d\n",numOfSinger);
  for(int ac = 0; ac<SetDaftarUser.Count; ac++){
    fprintf(file, "%s\n",SetDaftarUser.buffer[ac].TabWord);
  }
  
  for(int n = 0 ; n < SetDaftarUser.Count; n++){
    currentPlaying = arrOfLagu[n+1];
    StackLagu = arrOfStack[n+1];
    MapPlaylist = arrOfPlaylist[n+1];
    QueueLagu = arrOfQueue[n+1];

    //Bagian CurrentPlaying
    if(IsEmptyLagu(currentPlaying)){
      fprintf(file,"-\n");
    }
    else fprintf(file, "%s;%s;%s\n", currentPlaying.Penyanyi.TabWord, currentPlaying.Album.TabWord, currentPlaying.Judul.TabWord);
    //BAGIAN QUEUE 
    int numOfQ = QueueLagu.idxTail+1;
    fprintf(file,"%d\n",numOfQ);
    Queue newQueue = QueueLagu; 
    for(int i =0; i< numOfQ; i++){
      Lagu temp; 
      dequeue(&newQueue, &temp);
      fprintf(file,"%s;%s;%s\n",temp.Penyanyi.TabWord, temp.Album.TabWord, temp.Judul.TabWord);
    }

    //BAGIAN STACK 
    Stack newStack;
    CreateEmpty(&newStack);
    int cnt =0; 
    while(!IsEmptyStack(StackLagu)){
      Lagu temp; 
      Pop(&StackLagu, &temp);
      Push(&newStack, temp);
      cnt++; 
    }
    fprintf(file, "%d\n",cnt);
    while(cnt){
      Lagu temp; 
      Pop(&newStack, &temp);
      fprintf(file, "%s;%s;%s\n",temp.Penyanyi.TabWord, temp.Album.TabWord, temp.Judul.TabWord);
      Push(&StackLagu,temp);
      cnt--;
    }

    //BAGIAN PLAYLIST
    int numOfPlaylist = MapPlaylist.Count; 
    fprintf(file, "%d\n",numOfPlaylist);
    for(int i =0; i<numOfPlaylist; i++){
      Word Key = MapPlaylist.Elements[i].Key; 
      LinkedList l = MapPlaylist.Elements[i].Value;
      int numOfSong = NbElmt(l);
      fprintf(file, "%d %s\n",numOfSong,Key.TabWord);
      addressLinkedList p = l.First; 
      while(p != Nil_LL){
        fprintf(file, "%s;%s;%s\n",p->info.Penyanyi.TabWord, p->info.Album.TabWord, p->info.Judul.TabWord);
        p = p->next;
      }
    }
  }

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
    
    STARTWORD();//Reading Empty Spaces
    printf("Ingin melihat album yang ada? (Y/N) : ");
    STARTWORD();
    
    if(compareString(currentWord.TabWord, "Y")){

      printf("Pilih penyanyi untuk melihat album mereka : ");
      STARTWORD();//Reading Empty Spaces
      Word newWord = takeInput();
      printf("Daftar Album oleh %s :\n", newWord.TabWord);
      if(IsMember(MapAlbum, newWord)){
        for(int i =0; i< Value(MapAlbum, newWord).Count; i++){
          printf("%d. %s\n",i+1, Value(MapAlbum, newWord).buffer[i].TabWord);
        }
      }

      printf("Pilih album untuk melihat lagu di dalam album : ");
      STARTWORD();
      newWord = takeInput();
      printf("Daftar lagu di %s : \n", newWord.TabWord);
      if(IsMember(MapLagu, newWord)){
        for(int i = 0; i<Value(MapLagu, newWord).Count; i++){
          printf("%d. %s\n", i+1, Value(MapLagu, newWord).buffer[i].TabWord); 
        }
      }
    }
    else{
      return; 
    }
  }
  else if(compareString(currentWord.TabWord, "PLAYLIST")){
    if(MapPlaylist.Count == 0){
      printf("Kamu tidak memiliki Playlist\n");
      return; 
    }

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
}

void quitCommand(int *stopStatus){
  printf("Apakah kamu ingin menyimpan data sesi sekarang? "); 
  STARTWORD();// Reading Empty Space
  STARTWORD();
  printf("\n");
  if(compareString(currentWord.TabWord,"Y")){
    saveCommand(true);
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

