#include "playlist.h"

void CreateEmptyPlaylist(Playlist *M){
  M->Count = NilMap; 
}

boolean IsEmptyPlaylist(Playlist M){
  return M.Count == NilMap;
}
boolean IsFullPlaylist(Playlist M){
  return M.Count == MaxElMapPlaylist;
}

IsiPlaylist ValuePlaylist (Playlist M, Word k){
  LinkedList tempLagu; 
  CreateEmptyLL(&tempLagu);
  for(int i =0; i< M.Count; i++){
    if(CompareWord(M.Elements[i].Key, k)){
      tempLagu = M.Elements[i].Value;
    }
  }
  return tempLagu;
}

boolean IsMemberPlaylist(Playlist M, JudulPlaylist k){
  for(int i =0; i< M.Count; i++){
    if(CompareWord(k, M.Elements[i].Key)){
      return true; 
    }
  }
  return false; 
}

void InsertPlaylist(Playlist *M, JudulPlaylist k, IsiPlaylist v){
  if(!IsFullPlaylist(*M) && !IsMemberPlaylist(*M,k)){
    M->Elements[M->Count].Key = k; 
    M->Elements[M->Count].Value = v;
    M->Count++;
  }
}

void DeletePlaylist (Playlist *M, JudulPlaylist k){
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
