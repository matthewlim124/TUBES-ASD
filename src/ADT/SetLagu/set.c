#include "set.h"
#include <stdio.h>

void CreateSet(SetLagu *s){
  for(int i =0; i< MAX_SET; i++){
    s->buffer[i] = MakeLagu();
  }
  
  s->Length = 0;
}

boolean IsEmpty(SetLagu s){
  return s.Length ==0;
}

int Length(SetLagu s){
  Lagu MARK = MakeLagu();
  int i =0; 
  while(!CompareLagu(MARK, s.buffer[i])){
    i++;
  }
  return i; 
}

boolean IsIn(SetLagu s, Lagu l){
  int index = Length(s);
  for(int i =0; i< index; i++){
    if(CompareLagu(s.buffer[i],l))return true; 
  }
  return false; 
}

void AddSet(SetLagu *s, Lagu l){
  if( !IsIn(*s,l)){
    s->Length++; 
    s->buffer[Length(*s)] = l;
  }
}
//Belum Semua baru yang diperlukan

