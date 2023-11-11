#include "word.h"
#include <stdio.h>
int main(){
  Word nWord; 
  MakeWord(&nWord);
  SetWord(&nWord, "Sebuah Word");
  printf("Isi : %s\n",nWord.TabWord);
}
