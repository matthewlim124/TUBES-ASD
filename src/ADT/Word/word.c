#include "word.h"
#include <stdio.h>

void MakeWord(Word *s){
  for(int i =0; i< STRING_MAX; i++){
    s->TabWord[i] = '\0';
  }
  s->Length =0;
}

void ConcatWord(Word dest, Word *target){
  for(int i =0; i< dest.Length; i++){
    target -> TabWord[i + target->Length] = dest.TabWord[i]; 
  }
  target->Length = dest.Length + target->Length;
}

boolean CompareWord(Word a, Word b){
  int idx = 0; 
  if(a.Length> b.Length) idx = a.Length; 
  else idx = b.Length; 
  for(int i =0; i< idx; i++){
    if(a.TabWord[i]!=b.TabWord[i]) return false;
  }
  return true; 
}

void CleanWord(Word *w){
  for(int i =0; i< STRING_MAX; i++){
    w->TabWord[i] = '\0';
  }
}
void SetWord(Word *w, char *s){
  CleanWord(w);
  int i =0;
  while(s[i] != '\0'){
    w->TabWord[i] = s[i];
    i++;
  }
  w->Length = i;
}


