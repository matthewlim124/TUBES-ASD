#include <stdio.h>
#include "mesinkata.h"

boolean endWord;
Word currentWord;

void IgnoreBlanks()
{
    /* Mengabaikan satu atau beberapa BLANK
       I.S. : currentChar sembarang
       F.S. : currentChar ≠ BLANK atau currentChar = MARK */
    while (currentChar == BLANK)
    {
        ADV();
    }
}

void cleanWORD(){
  for(int i =0; i<currentWord.Length; i++){
    currentWord.TabWord[i] = '\0'; 
  }
}
void STARTWORD()
{
    /* I.S. : currentChar sembarang
       F.S. : endWord = true, dan currentChar = MARK;
              atau endWord = false, currentWord adalah kata yang sudah diakuisisi,
              currentChar karakter pertama sesudah karakter terakhir kata */
    cleanWORD();
    START();
    IgnoreBlanks();
    if (currentChar == MARK || currentChar == '\r' || currentChar == '\n')
    {
        endWord = true;
    }
    else
    {
        endWord = false;
        CopyWord();
    }
}

void ADVWORD()
{
    /* I.S. : currentChar adalah karakter pertama kata yang akan diakuisisi
       F.S. : currentWord adalah kata terakhir yang sudah diakuisisi,
              currentChar adalah karakter pertama dari kata berikutnya, mungkin MARK
              Jika currentChar = MARK, endWord = true.
       Proses : Akuisisi kata menggunakan procedure CopyWord */
    cleanWORD();
    IgnoreBlanks();
    if(currentChar == MARK || currentChar == '\r' || currentChar == '\n'){
        endWord = true;
    }
    else
    {
        endWord = false;
        CopyWord();
        IgnoreBlanks();
    }
}

void CopyWord()
{
    /* Mengakuisisi kata, menyimpan dalam currentWord
       I.S. : currentChar adalah karakter pertama dari kata
       F.S. : currentWord berisi kata yang sudah diakuisisi;
              currentChar = BLANK atau currentChar = MARK;
              currentChar adalah karakter sesudah karakter terakhir yang diakuisisi.
              Jika panjang kata melebihi CAPACITY, maka sisa kata terpotong */
    currentWord.Length = 0;
    while (currentChar != BLANK && currentChar != MARK && currentChar != '\r' && currentChar != '\n')
    {
        if (currentWord.Length < NMax)
        { // jika lebih akan terpotong
            currentWord.TabWord[currentWord.Length++] = currentChar;
            ADV();
        }
        else
            break;
    }
}

boolean isEndWord() {
    return currentChar == '\n' || currentChar == MARK;
}

void CopyLetter(char *arr){
  for(int i =0; i< currentWord.Length; i++){
    arr[i] = currentWord.TabWord[i]; 
  }
}

void checkForEnter(){
  for(int i =1; i < currentWord.Length; i++){
    if(currentWord.TabWord[i] == '\\' && currentWord.TabWord[i+1]=='r'){
      endWord = true;
    }
  }
}
