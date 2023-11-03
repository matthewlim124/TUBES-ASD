#include "map.h"
#include <stdio.h>



/* MODUL Map
Deklarasi stack yang dengan implementasi array eksplisit-statik rata kiri
*/

/* Definisi Map M kosong : M.Count = Nil */
/* M.Count = jumlah element Map */
/* M.Elements = tempat penyimpanan element Map */


/* *** Konstruktor/Kreator *** */
void CreateEmpty(Map *M){
    (*M).Count = Nil;


    
}
/* I.S. Sembarang */
/* F.S. Membuat sebuah Map M kosong berkapasitas MaxEl */
/* Ciri Map kosong : count bernilai Nil */

/* ********* Predikat Untuk test keadaan KOLEKSI ********* */
boolean IsEmpty(Map M){
    return (M.Count == Nil );
}
/* Mengirim true jika Map M kosong*/
/* Ciri Map kosong : count bernilai Nil */

boolean IsFull(Map M){
    return (M.Count == MaxEl);
}
/* Mengirim true jika Map M penuh */
/* Ciri Map penuh : count bernilai MaxEl */
int length(char *str){
    
    int i = 0;
    
    while(str[i] != '\0'){
        

        i++;
    }
    return i;
}

int find_key_idx(Map M, keytype *k){
    /*I.S key ada di Map*/

    int char_counter = 0;
    for(int i = 0; i < M.Count; i++){
        for(int j = 0; j < length(k); j++){
            if(M.Elements[i].Key[j] == k[j]){
                char_counter++;
            }
        }

        if(char_counter == length(k)){
            return i;
        }
    }

    
    
}

int find_empty_value(Map M){
    /*I.S Value Tidak penuh*/

    /*Mencari index yang kosong di M.Elements[].Value[][]*/
    
    for(int i = 0; i < M.Count; i++){

        for(int j = 0; j < MaxEl; j++){
            if(M.Elements[i].Value[j][0] == '\0'){
                return j;
            }
        }
    
    }

    
    
}

/* ********** Operator Dasar Map ********* */


void Insert(Map *M, keytype *k, valuetype *v){

    if(IsEmpty(*M)){
        for(int i = 0; i < length(k); i++){
            (*M).Elements[0].Key[i] = k[i]; 
        }
        for(int i = 0; i < length(v); i++){
            (*M).Elements[0].Value[0][i] = v[i];
        }
        
        
    }else{

        if(IsMember(*M,k,length(k))){
            for(int i = 0; i < length(k); i++){
                (*M).Elements[find_key_idx(*M,k)].Key[i] = k[i]; 
            }
            int idx_value = find_empty_value(*M);
            for(int i = 0; i < length(v); i++){
                
                (*M).Elements[find_key_idx(*M,k)].Value[idx_value][i] = v[i];
            }
        }else{
            for(int i = 0; i < length(k); i++){
                (*M).Elements[(*M).Count].Key[i] = k[i]; 
            }
            for(int i = 0; i < length(v); i++){
                (*M).Elements[(*M).Count].Value[0][i] = v[i];
            }
            
        }

        
    }

    (*M).Count++;
}
/* Menambahkan Elmt sebagai elemen Map M. */
/* I.S. M mungkin kosong, M tidak penuh
        M mungkin sudah beranggotakan v dengan key k */
/* F.S. v menjadi anggota dari M dengan key k. Jika k sudah ada, operasi tidak dilakukan */

void Delete(Map *M, keytype* k){
    if(IsMember(*M,k,length(k))){
        if((*M).Count == 1){
            (*M).Count = Nil;
        }else{
            (*M).Count--;
            
            boolean isFound = false;
            

            for(int i = 0; i < (*M).Count; i++){
                if((*M).Elements[i].Key == k){
                    isFound = true;
                }
                if(isFound){
                    (*M).Elements[i] = (*M).Elements[i+1];
                    
                }
                
            }
        }
    }
    
}

/* Menghapus Elmt dari Map M. */
/* I.S. M tidak kosong
        element dengan key k mungkin anggota / bukan anggota dari M */
/* F.S. element dengan key k bukan anggota dari M */

boolean IsMember(Map M, keytype *k, int length){
    if(!(IsEmpty(M))){
        //Traversal untuk mengecek tiap karakter key di M dengan k
        for(int i = 0; i < M.Count; i++){
            int j = 0;
            int char_counter = 0;
            while(M.Elements[i].Key[j] != Undefined){
                //Jika karakter sama increment counter
                if(M.Elements[i].Key[j] == k[j]){
                    char_counter++;
                }
                j++;
            }
            //Jika length dari char_counter sama dengan length dari key di M
            if(char_counter == length){
                return true;
            }
        }
    }
        
    
    
    return false;
    
}
/* Mengembalikan true jika k adalah member dari M */

