#include "lagu.h"
#include <stdio.h>

Lagu MakeLagu(){
    Lagu newLagu; 
    MakeWord(&newLagu.Album);
    MakeWord(&newLagu.Judul);
    MakeWord(&newLagu.Penyanyi);
    for(int i =0; i<NUM_FEATURES; i++){
      newLagu.Features[i] = 0; 
    }
    return newLagu;
}
boolean IsEmptyLagu(Lagu a){
  Lagu b  = MakeLagu();
  if(CompareLagu(a, b)){
    return true;
  }
  return false; 
}
boolean CompareLagu(Lagu a, Lagu b){
  if(CompareWord(a.Album, b.Album) && 
      CompareWord(a.Judul, b.Judul) &&
      CompareWord(a.Penyanyi, b.Penyanyi)){
    return true; 
  }

  return false;
}

