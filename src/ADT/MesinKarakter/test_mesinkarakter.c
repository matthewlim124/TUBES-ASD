#include <stdio.h>
#include "mesinkarakter.h"

int main() {
    START(); // Memulai mesin karakter
    
    // Membaca karakter per karakter sampai mencapai MARK atau akhir dari input
    while (!EOP) {
        if (currentChar != MARK) {
            printf("Karakter: %c\n", currentChar);
        } else {
            printf("MARK ditemukan.\n");
        }
        ADV(); // Maju ke karakter berikutnya
    }
    
    return 0;
}
