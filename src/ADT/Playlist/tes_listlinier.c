#include <stdio.h>
#include <string.h>
#include "listlinier.h"

// Fungsi untuk menampilkan isi dari linked list
void displayList(LinkedList L) {
    addressLinkedList P = First(L);
    printf("Isi linked list:\n");
    while (P != NULL) {
        printf("Penyanyi: %s\n", P->info.Penyanyi.TabWord);
        printf("Album: %s\n", P->info.Album.TabWord);
        printf("Judul: %s\n\n", P->info.Judul.TabWord);
        P = Next(P);
    }
}


int main() {
    // Buat linked list baru
    LinkedList list;
    CreateEmptyLL(&list);

    // Tambahkan beberapa lagu ke linked list
    Lagu lagu1 = {{"Penyanyi1", 9}, {"Album1", 6}, {"Judul1", 6}};
    Lagu lagu2 = {{"Penyanyi2", 9}, {"Album2", 6}, {"Judul2", 6}};
    Lagu lagu3 = {{"Penyanyi3", 9}, {"Album3", 6}, {"Judul3", 6}};

    InsVFirst(&list, lagu1);
    InsVLast(&list, lagu2);
    InsVLast(&list, lagu3);

    // Tampilkan isi linked list
    displayList(list);

    // Uji penghapusan elemen
    Lagu deletedValue;
    DelVLast(&list, &deletedValue);
    printf("\nElemen terakhir yang dihapus:\n");
    printf("Penyanyi: %s\n", deletedValue.Penyanyi.TabWord);
    printf("Album: %s\n", deletedValue.Album.TabWord);
    printf("Judul: %s\n\n", deletedValue.Judul.TabWord);

    displayList(list);

    // Uji pembalikan linked list
    InversLinkedList(&list);
    printf("Setelah pembalikan:\n");
    displayList(list);

    return 0;
}
