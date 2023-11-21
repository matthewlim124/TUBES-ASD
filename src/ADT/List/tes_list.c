#include <stdio.h>
#include "list.h"

int main() {
    // Membuat list baru
    List newList;
    newList = MakeList(newList);

    // Memeriksa apakah list kosong
    printf("Apakah list kosong? %s\n", IsEmpty(newList) ? "Ya" : "Tidak");
    
    // Menambahkan elemen ke list
    InsertLast(&newList, 5);
    InsertLast(&newList, 10);
    InsertLast(&newList, 15);
    InsertLast(&newList, 20);
    
    // Menampilkan panjang list
    printf("Panjang list adalah: %d\n", Length(newList));
    
    // Menampilkan isi dari list
    printf("Elements dari list: ");
    for (int i = 0; i <= LastIdx(newList); i++) {
        printf("%d ", Get(newList, i));
    }
    printf("\n");
    
    // Menghapus elemen pertama dari list
    DeleteFirst(&newList);
    
    // Menampilkan isi dari list setelah penghapusan elemen pertama
    printf("Element dari list setelah penghapusan elemen pertama: ");
    for (int i = 0; i <= LastIdx(newList); i++) {
        printf("%d ", Get(newList, i));
    }
    printf("\n");
    
    // Menambahkan elemen ke-25 ke dalam list (contoh penggunaan InsertAt)
    InsertAt(&newList, 25, 2);
    
    // Menampilkan isi dari list setelah penambahan elemen ke-25
    printf("Element dari list setelah menambahkan 25 di index 2: ");
    for (int i = 0; i <= LastIdx(newList); i++) {
        printf("%d ", Get(newList, i));
    }
    printf("\n");
    
    // Menghapus elemen terakhir dari list
    DeleteLast(&newList);
    
    // Menampilkan isi dari list setelah penghapusan elemen terakhir
    printf("Elements dari list setelah menghapus elemen terakhir: ");
    for (int i = 0; i <= LastIdx(newList); i++) {
        printf("%d ", Get(newList, i));
    }
    printf("\n");
    
    // Mencari elemen dalam list
    int searchElement = 10;
    printf("%d is%s in the list.\n", searchElement, Search(newList, searchElement) ? "" : " not");
    
    // Mengecek validitas indeks
    IdxType indexToCheck = 3;
    printf("Apakah index %d valid? %s\n", indexToCheck, IsIdxValid(newList, indexToCheck) ? "Ya" : "Tidak");

    // ...
    printf("Program selesai. Tekan tombol apapun untuk keluar.\n");
    getchar(); // Tahan tampilan konsol
    return 0;

    
    return 0;
}
