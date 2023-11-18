/* File: mesinkarakter.c */
/* Implementasi Mesin Karakter */

#include "mesinkarakter.h"
#include <stdio.h>

char currentChar;
boolean EOP;
boolean fromInput;
static FILE *pita;
static int retval;

void START(){
       /* Mesin siap dioperasikan. Pita disiapkan untuk dibaca.
          Karakter pertama yang ada pada pita posisinya adalah pada jendela.
          I.S. : sembarang
          F.S. : currentChar adalah karakter pertama pada pita. Jika currentChar != MARK maka EOP akan padam (false).
                 Jika currentChar = MARK maka EOP akan menyala (true) */
       /* Algoritma */
       pita = stdin;
       EOP = false;
       ADV();
}

void ADV()
{
       /* Pita dimajukan satu karakter.
          I.S. : Karakter pada jendela =
                 currentChar, currentChar != MARK
          F.S. : currentChar adalah karakter berikutnya dari currentChar yang lama,
                 currentChar mungkin = MARK.
                       Jika  currentChar = MARK maka EOP akan menyala (true) */

       /* Algoritma */
       retval = fscanf(pita, "%c", &currentChar);
       if(currentChar == '\n' || currentChar == ';'){
         EOP = true;
       };
}
