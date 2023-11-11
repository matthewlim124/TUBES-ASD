#include "playlist.h"

void CreateEmptyPlaylist(DaftarPlaylist *M){
  M->Count = NilMap; 
}

boolean IsEmptyPlaylist(DaftarPlaylist M){
  return M.Count == NilMap;
}
boolean IsFullPlaylist(DaftarPlaylist M){
  return M.Count == MaxElMap;
}

IsiPlaylist ValuePlaylist (DaftarPlaylist M, Word k){
  LinkedList tempLagu; 
  CreateEmptyLL(&tempLagu);
  for(int i =0; i< M.Count; i++){
    if(CompareWord(M.Elements[i].Key, k)){
      tempLagu = M.Elements[i].Value;
    }
  }
  return tempLagu;
}

boolean IsMemberPlaylist(DaftarPlaylist M, JudulPlaylist k){
  for(int i =0; i< M.Count; i++){
    if(CompareWord(k, M.Elements[i].Key)){
      return true; 
    }
  }
  return false; 
}

void InsertPlaylist(DaftarPlaylist *M, JudulPlaylist k, IsiPlaylist v){
  if(!IsFullPlaylist(*M) && !IsMemberPlaylist(*M,k)){
    M->Elements[M->Count].Key = k; 
    M->Elements[M->Count].Value = v;
    M->Count++;
  }
}

void DeletePlaylist (DaftarPlaylist *M, JudulPlaylist k){
  boolean found = false;
  for(int i =0; i< M->Count; i++){
    if(CompareWord(M->Elements[i].Key, k)){
      found = true; 
    }

    if(found && i<M->Count-1){
      M->Elements[i] = M->Elements[i+1];
    }
  }
  if(found)M->Count--;
}
