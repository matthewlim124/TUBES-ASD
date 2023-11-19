#include "set.h"
#include <stdio.h>
int main(){
  SetOfWord sebuahSet; 
  printf("Creating Empty Set\n"); 
  CreateSet(&sebuahSet);
  if(IsEmpty(sebuahSet))printf("Set Kosong\n"); 
  else{
    printf("Set Tidak Kosong, %d \n",sebuahSet.Count);
  }

  Word sWord; 
  MakeWord(&sWord);
  SetWord(&sWord, "Word");
  
  AddSet(&sebuahSet, sWord);

  printf("Masukkan value ke set \n");
  if(IsEmpty(sebuahSet))printf("Set Kosong\n"); 
  else{
    printf("Set Tidak Kosong, %d \n",sebuahSet.Count);
  }

  if(IsIn(sebuahSet, sWord)){
    printf("Value in set\n");
  }
  printf("SWord : %s\n",sebuahSet.buffer[0].TabWord);

}
