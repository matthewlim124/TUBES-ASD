#include "lagu.h"
#include <stdio.h>

Lagu MakeLagu(){
    Lagu newLagu; 
    MakeWord(&newLagu.Album);
    MakeWord(&newLagu.Judul);
    MakeWord(&newLagu.Penyanyi);
    return newLagu;
}

boolean CompareLagu(Lagu a, Lagu b){
  if(CompareWord(a.Album, b.Album) && 
      CompareWord(a.Judul, b.Judul) &&
      CompareWord(a.Penyanyi, b.Penyanyi)){
    return true; 
  }

  return false;
}

