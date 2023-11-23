#include <stdio.h>
#include "playlist.h"

int main() {
    Playlist myPlaylist;
    JudulPlaylist key;
    IsiPlaylist value;
    LinkedList tempLagu;
    CreateEmptyLL(&tempLagu);

    Lagu tempLagu0 = MakeLagu();
    
    Word tAlbum, tPenyanyi, tJudul;
    SetWord(&tJudul, "Pink Venom");
    SetWord(&tPenyanyi, "Blackpink");
    SetWord(&tAlbum, "Born Pink");
    tempLagu0.Judul = tJudul; 
    tempLagu0.Album = tAlbum;
    tempLagu0.Penyanyi = tPenyanyi; 
    
    Lagu tempLagu2= MakeLagu();
    
    SetWord(&tJudul, "Shut Down");
    SetWord(&tPenyanyi, "Blackpink");
    SetWord(&tAlbum, "Born Pink");
    tempLagu2.Judul = tJudul; 
    tempLagu2.Album = tAlbum;
    tempLagu2.Penyanyi = tPenyanyi;

    InsVLast(&tempLagu, tempLagu0);
    InsVLast(&tempLagu, tempLagu2);

    CreateEmptyPlaylist(&myPlaylist);

    // Inserting playlists
    InsertPlaylist(&myPlaylist, (Word){"Playlist1", 8}, tempLagu);
    InsertPlaylist(&myPlaylist, (Word){"Playlist2", 5}, tempLagu);
    InsertPlaylist(&myPlaylist, (Word){"Playlist3", 10}, tempLagu);

    // Checking if playlist is empty
    if (IsEmptyPlaylist(myPlaylist))
        printf("Playlist kosong.\n");
    else
        printf("Playlist tidak kosong.\n");

    // Checking if playlist is full
    if (IsFullPlaylist(myPlaylist))
        printf("Playlist penuh.\n");
    else
        printf("Playlist tidak penuh.\n");

    // Checking playlist membership
    if (IsMemberPlaylist(myPlaylist, (Word){"Playlist2", 5}))
        printf("Playlist ada.\n");
    else
        printf("Playlist tidak ada.\n");

    // Getting playlist value
    value = ValuePlaylist(myPlaylist, (Word){"Playlist1", 8});
    printf("Mengembalikan nilai.\n");

    // Deleting a playlist
    DeletePlaylist(&myPlaylist, (Word){"Playlist2", 5});
    printf("Menghapus Playlist.\n");

    return 0;
}
