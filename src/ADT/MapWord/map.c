#include "map.h"


void CreateEmptyMap(Map *M){
  M->Count = NilMap; 
}

boolean IsEmptyMap(Map M){
  return M.Count == NilMap;
}
boolean IsFullMap(Map M){
  return M.Count == MaxElMap;
}

wordvaluetype Value(Map M, wordkeytype k){
  SetOfWord tempLagu; 
  CreateSet(&tempLagu);
  for(int i =0; i< M.Count; i++){
    if(CompareWord(M.Elements[i].Key, k)){
      tempLagu = M.Elements[i].Value;
    }
  }
  return tempLagu;
}

boolean IsMember(Map M, wordkeytype k){
  for(int i =0; i< M.Count; i++){
    if(CompareWord(k, M.Elements[i].Key)){
      return true; 
    }
  }
  return false; 
}

void Insert(Map *M, wordkeytype k, wordvaluetype v){
  if(!IsFullMap(*M) && !IsMember(*M,k)){
    M->Elements[M->Count].Key = k; 
    M->Elements[M->Count].Value = v;
    M->Count++;
  }
}

void Delete(Map *M, wordkeytype k){
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
