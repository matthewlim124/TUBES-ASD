#include "map.h"

int main(){
  printf("Creating Empty Map...\n");
  Map sebuahMap; 
  CreateEmptyMap(&sebuahMap);
  printf("Count Map : %d\n", sebuahMap.Count);
  if(IsEmptyMap(sebuahMap)){
    printf("Map is Empty \n");
  }
  else{
    printf("Map isn't Empty \n"); 
  }

  printf("Inserting data into map\n"); 
  
  Word kW, vW; 
  SetWord(&kW, "key Test");
  SetWord(&vW, "value Test");
  
  SetOfWord setW; 
  AddSet(&setW, vW);
  Insert(&sebuahMap, kW, setW);

  printf("Checking if Empty \n"); 

  if(IsEmptyMap(sebuahMap)){
    printf("Map is Empty \n");
  }
  else{
    printf("Map isn't Empty \n"); 
    printf("Map Count : %d\n",sebuahMap.Count);
  }

  if(IsMember(sebuahMap, kW)){
    printf("Keyword ada\n");
  }

  printf("Value : %s, Key : %s\n",Value(sebuahMap, kW).buffer[0].TabWord, kW.TabWord);

}
