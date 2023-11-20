# include "list.h"
#include <stdio.h>

List MakeList(){
  List sebuahList;
  for(int i =0; i<=MaxEl; i++){
    sebuahList.A[i] = Mark; 
  } 
  return sebuahList; 
}

boolean IsEmpty(List L){
  return (L.A[0] == Mark);
}

ElType Get(List L, int i){
  return L.A[i];
}

void Set(List *L, int i, int v){
  L->A[i] = v; 
}

int Length(List L){
    int i = 0;
    boolean ketemu = false;
    while (ketemu == false){
        if (L.A[i] == Mark){
            ketemu = true;
        } else {
            i++;
        }
    }
    return i;
}

IdxType FirstIdx(List L){
  return 0; 
}

IdxType LastIdx(List L){
  return Length(L) - 1;
}

boolean IsIdxValid(List L, IdxType i){
  return (i >= FirstIdx(L) && MaxEl >= i);
}

boolean IsIdxEff(List L, IdxType i){
  return (i>= FirstIdx(L) && Length(L)> i);
}

boolean Search(List L, int X){
  for(int i =0; i<= LastIdx(L); i++){
    if(Get(L,i) == X)return true;
  }
  return false; 
}

void InsertAt(List *L, int X, int i){
    for (int j = Length(*L)-1; j >= i; j--){
      Set(L, j+1, Get(*L,j));
    }
    Set(L,i,X);
}
void InsertFirst(List *L, int X){
 for (int i = Length(*L)-1; i >= 0; i--){
        Set(L, i+1, Get(*L,i));
    }
    Set(L,0,X);
}

void InsertLast(List *L, int X){
  Set(L,Length(*L), X);
}

void DeleteAt(List *L, int i){
  for(int k =i; k<Length(*L);k++ ){
    L->A[k]=L->A[k+1]; 
  }
}

void DeleteFirst(List *L){
  DeleteAt(L,0);
}

void DeleteLast(List *L){
  L->A[LastIdx(*L)] = Mark; 
}
List Concat(List L1, List L2){
  for(int i =1; i<=Length(L2); i++){
    L1.A[i+LastIdx(L1)] = L2.A[i-1];
  }
  return L1; 
}
