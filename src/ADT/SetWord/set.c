#include "set.h"
#include <stdio.h>

void CreateSet(SetOfWord *s){
  for(int i =0; i< MAX_SET; i++){
    MakeWord(&s->buffer[i]);
  }
  
  s->Count = 0;
}

boolean IsEmpty(SetOfWord s){
  return s.Count ==0;
}

int LengthSet(SetOfWord s){
  return s.Count; 
}

boolean IsIn(SetOfWord s, Word l){
  int index = LengthSet(s);
  for(int i =0; i< index; i++){
    if(CompareWord(s.buffer[i],l))return true; 
  }
  return false; 
}

void AddSet(SetOfWord *s, Word l){
   //if(IsIn(*s, l)){
   //  printf("Test");
   //}
   //else{
   //  printf("Not test"); 

   //}

   //printf("%s\n", l.TabWord);
  if( !IsIn(*s,l)){
    s->buffer[LengthSet(*s)] = l;
    s->Count++; 
  }
}
//Belum Semua baru yang diperlukan

