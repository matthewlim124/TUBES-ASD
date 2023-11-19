#include <stdio.h>
#include "stack.h"

#define STRING_MAX 100 // Anda perlu menentukan nilai STRING_MAX yang sesuai

int main() {
    Stack S;
    infotype item;

    CreateEmpty(&S);

    printf("Is Stack Empty? %s\n", IsEmptyStack(S) ? "Yes" : "No");

    printf("Pushing elements into the stack...\n");
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
            printf("Pushed item with ID %d into the stack\n", i);
        } else {
            printf("Stack is full. Cannot push more elements.\n");
            break;
        }
    }

    printf("Is Stack Full? %s\n", IsFull(S) ? "Yes" : "No");

    printf("Popping elements from the stack...\n");
    while (!IsEmptyStack(S)) {
        Pop(&S, &item);
        printf("Popped item from the stack\n");
        // Lakukan operasi atau manipulasi sesuai kebutuhan dengan item yang di-pop
    }

    printf("Is Stack Empty? %s\n", IsEmptyStack(S) ? "Yes" : "No");

    return 0;
}
