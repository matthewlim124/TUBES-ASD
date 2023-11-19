#include <stdio.h>
#include "list.h"

int main() {
    // Membuat list baru
    List newList = MakeList();
    
    // Memeriksa apakah list kosong
    printf("Is the list empty? %s\n", IsEmpty(newList) ? "Yes" : "No");
    
    // Menambahkan elemen ke list
    InsertLast(&newList, 5);
    InsertLast(&newList, 10);
    InsertLast(&newList, 15);
    InsertLast(&newList, 20);
    
    // Menampilkan panjang list
    printf("Length of the list: %d\n", Length(newList));
    
    // Menampilkan isi dari list
    printf("Elements of the list: ");
    for (int i = 0; i <= LastIdx(newList); i++) {
        printf("%d ", Get(newList, i));
    }
    printf("\n");
    
    // Menghapus elemen pertama dari list
    DeleteFirst(&newList);
    
    // Menampilkan isi dari list setelah penghapusan elemen pertama
    printf("Elements of the list after deleting first element: ");
    for (int i = 0; i <= LastIdx(newList); i++) {
        printf("%d ", Get(newList, i));
    }
    printf("\n");
    
    // Menambahkan elemen ke-25 ke dalam list (contoh penggunaan InsertAt)
    InsertAt(&newList, 25, 2);
    
    // Menampilkan isi dari list setelah penambahan elemen ke-25
    printf("Elements of the list after inserting 25 at index 2: ");
    for (int i = 0; i <= LastIdx(newList); i++) {
        printf("%d ", Get(newList, i));
    }
    printf("\n");
    
    // Menghapus elemen terakhir dari list
    DeleteLast(&newList);
    
    // Menampilkan isi dari list setelah penghapusan elemen terakhir
    printf("Elements of the list after deleting last element: ");
    for (int i = 0; i <= LastIdx(newList); i++) {
        printf("%d ", Get(newList, i));
    }
    printf("\n");
    
    // Mencari elemen dalam list
    int searchElement = 10;
    printf("%d is%s in the list.\n", searchElement, Search(newList, searchElement) ? "" : " not");
    
    // Mengecek validitas indeks
    IdxType indexToCheck = 3;
    printf("Is index %d valid? %s\n", indexToCheck, IsIdxValid(newList, indexToCheck) ? "Yes" : "No");
    
    return 0;
}
