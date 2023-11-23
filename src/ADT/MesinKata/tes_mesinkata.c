#include <stdio.h>
#include "mesinkata.h"

int main() {
    // Inisialisasi awal
    STARTWORD();

    // Contoh penggunaan IgnoreBlanks
    IgnoreBlanks();

    // Contoh penggunaan ADVWORD
    ADVWORD();

    // Contoh penggunaan CopyWord
    CopyWord();

    // Contoh penggunaan isEndWord
    if (isEndWord()) {
        printf("Current character is end of word or line.\n");
    } else {
        printf("Current character is not end of word or line.\n");
    }

    // Contoh penggunaan CopyLetter
    char copiedLetters[NMax];
    CopyLetter(copiedLetters);
    printf("Copied letters: %s\n", copiedLetters);

    // Contoh penggunaan checkForEnter
    checkForEnter();
    if (endWord) {
        printf("Found newline character in current word.\n");
    } else {
        printf("Newline character not found in current word.\n");
    }

    return 0;
}
