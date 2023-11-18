#include "word.h"
#include <stdio.h>
int main(){
  Word nWord; 
  MakeWord(&nWord);
  SetWord(&nWord, "Sebuah Word");
  printf("Isi : %s\n",nWord.TabWord); 
  printf("Melakukan testing untuk angka...\n");
  printf("Masukkan Angka : ");
  char s[50]; 
  scanf("%s",s);
  SetWord(&nWord,s );
  printf("Angka : %d \n", WordToInt(nWord));
}
