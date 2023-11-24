#include <stdio.h>
#include "ADT/boolean.h"
#include "console/src/console.h"

int main(){
  boolean sEnd = false, A = false; 
  int stat =0; 

  printBanner();
  while(!stat){
    printf("Pilih dimana program dijalankan : \n    1.Linux\n    2.Windows\n >> "); 
    STARTWORD();

    if(WordToInt(currentWord)== 1){
      printf("Pilihan 1, program dijalankan di \e[1;32mLinux\e[m\n");
      stat = 1; 
    }
    else if(WordToInt(currentWord)== 2){
      printf("Pilihan 2, program dijalankan di \e[1;32mWindows\e[m\n");
      stat = 2;
    }
    else{
      printf("Pilihan tidak valid, silahkan mengulang\n \n");
    }
    START();
  }
  while(!sEnd){
    readCommand(stat); 
  }
}



