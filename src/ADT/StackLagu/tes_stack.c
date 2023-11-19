#include <stdio.h>
#include "stack.h"

#define STRING_MAX 100 // Anda perlu menentukan nilai STRING_MAX yang sesuai

int main() {
    Stack S;
    infotype item;

    CreateEmpty(&S);

    printf("Apakah stack kosong? %s\n", IsEmptyStack(S) ? "Ya" : "Tidak");

    printf("Menambahkan elemen ke dalam stack...\n");
    for (int i = 1; i <= 5; ++i) {
        infotype newItem;
        Word penyanyi, album, judul;

        // Inisialisasi struktur Word
        penyanyi.Length = album.Length = judul.Length = STRING_MAX;

        // Contoh pengisian nilai pada struktur Lagu (infotype)
        newItem.Penyanyi = penyanyi;
        newItem.Album = album;
        newItem.Judul = judul;

        if (!IsFull(S)) {
            Push(&S, newItem);
            printf("Menambahkan item dengan ID %d ke dalam stack\n", i);
        } else {
            printf("Stack penuh. Tidak bisa menambahkan item lagi.\n");
            break;
        }
    }

    printf("Apakah stack penuh? %s\n", IsFull(S) ? "Ya" : "Tidak");

    printf("Mengeluarkan item dari stack.\n");
    while (!IsEmptyStack(S)) {
        Pop(&S, &item);
        printf("Mengeluarkan item dari stack\n");
        // Lakukan operasi atau manipulasi sesuai kebutuhan dengan item yang di-pop
    }

    printf("Apakah stack kosong? %s\n", IsEmptyStack(S) ? "Ya" : "Tidak");

    return 0;
}
