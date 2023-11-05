#include "map.h"
#include <stdio.h>

//PENJELASAN ADT MAP UNTUK TUBES INI
/*
    //REPRESENTASI VISUAL MAP
    MAP Playlist = {(["Key"],[["Value1"],["Value2"],["Value3"]])}

    //TIPE DATA MAPENTRY
    Key pada map berupa array of character sebesar name_length 
    Value pada map berupa  array 2 dimensi (matrix) of character sebesar MaxEl,name_length

    //MAP
    Elements merupakan array of MAPENTRY sebesar MaxEl
    Count merupakan jumlah elemen di Elements
*/


/* Definisi Map M kosong : M.Count = Nil */
/* M.Count = jumlah element Map */
/* M.Elements = tempat penyimpanan element Map */


/* *** Konstruktor/Kreator *** */
void CreateEmptyMap(Map *M){
    (*M).Count = Nil;


    
}
/* I.S. Sembarang */
/* F.S. Membuat sebuah Map M kosong berkapasitas MaxEl */
/* Ciri Map kosong : count bernilai Nil */

/* ********* Predikat Untuk test keadaan KOLEKSI ********* */
boolean IsEmptyMap(Map M){
    return (M.Count == Nil );
}
/* Mengirim true jika Map M kosong*/
/* Ciri Map kosong : count bernilai Nil */

boolean IsFullMap(Map M){
    return (M.Count == MaxEl);
}

boolean isElEmpty(Map M, int idx){

    
    return (M.Elements[idx].Key[0] == Undefined);
       
    
}
/* Mengirim true jika Map M penuh */
/* Ciri Map penuh : count bernilai MaxEl */
int length_name(char *str){
    
    int i = 0;
    
    while(str[i] != Undefined){
        

        i++;
    }
    return i;
}

int value_count(Map M, keytype*k){

    int i = 0;
    int counter = 0;
    while(i < MaxEl){
        if(M.Elements[find_key_idx(M,k)].Value[i][0] != '\0'){
            counter++;
        }
        i++;
    }

    return counter;
}

int find_key_idx(Map M, keytype *k){
    /*I.S key ada di Map*/

    int char_counter = 0;
    for(int i = 0; i < M.Count; i++){
        for(int j = 0; j < length_name(k); j++){
            if(M.Elements[i].Key[j] == k[j]){
                char_counter++;
            }
        }

        if(char_counter == length_name(k)){
            return i;
        }
    }

    
    
}

int find_empty_map_idx(Map M){
    
    /*I.S MAP TIDAK PENUH*/
   
    
    for(int i = 0; i < M.Count; i++){

        if(M.Elements[i].Key[0] == Undefined){
            return i;
        }
    
    }
 
    
}



int find_value_idx(Map M, keytype* k, valuetype* value){
    for(int i = 0; i < MaxEl; i++){
        int counter = 0;
        int j = 0;
        while(M.Elements[find_key_idx(M,k)].Value[i][j] != '\0'){
            if(M.Elements[find_key_idx(M,k)].Value[i][j] == value[j]){
                counter++;
            }
            j++;
        }
        if(counter == length_name(value)){
            return i;
        }
    }

    return idx_undef;
}

int find_empty_value_idx(Map M, keytype* k){
    /*I.S Value Tidak penuh*/

    /*Mencari index yang kosong di M.Elements[].Value[][]*/
    
    for(int i = 0; i < M.Count; i++){

        if(M.Elements[find_key_idx(M,k)].Value[i][0] == '\0'){
            return i;
        }
    
    }
 
    
}

/* ********** Operator Dasar Map ********* */


void Insert(Map *M, keytype *k, valuetype *v){

    if(IsEmptyMap(*M)){
        for(int i = 0; i < length_name(k); i++){
            (*M).Elements[0].Key[i] = k[i]; 
        }
        for(int i = 0; i < length_name(v); i++){
            (*M).Elements[0].Value[0][i] = v[i];
        }
        (*M).Count++;
        
    }else{

        if(IsMemberMap(*M,k,length_name(k))){
            if(find_value_idx(*M, k, v) == idx_undef){
                for(int i = 0; i < length_name(v); i++){
                
                    (*M).Elements[find_key_idx(*M,k)].Value[find_empty_value_idx(*M,k)][i] = v[i];
                }
            }
            
        }else{
            for(int i = 0; i < length_name(k); i++){
                (*M).Elements[find_empty_map_idx(*M)].Key[i] = k[i]; 
            }
            for(int i = 0; i < length_name(v); i++){
                (*M).Elements[find_empty_map_idx(*M)].Value[0][i] = v[i];
            }
            (*M).Count++;
        }

        
    }

   
}
/* Menambahkan Elmt sebagai elemen Map M. */
/* I.S. M mungkin kosong, M tidak penuh
        M mungkin sudah beranggotakan v dengan key k */
/* F.S. v menjadi anggota dari M dengan key k. Jika k sudah ada, operasi tidak dilakukan */

void Delete(Map *M, keytype* k, valuetype* value){
    
    //Key yang ingin dihapus
    if(value == NULL){
        (*M).Elements[find_key_idx(*M,k)].Key[0] = Undefined;
            
        (*M).Count--;
    }else{
        //Value di key yang ingin dihaapus
        (*M).Elements[find_key_idx(*M,k)].Value[find_value_idx(*M,k,value)][0] = Undefined;
    }
    
    
    //Apakah ada di map
    
}

/* Menghapus Elmt dari Map M. */
/* I.S. M tidak kosong
        element dengan key k mungkin anggota / bukan anggota dari M */
/* F.S. element dengan key k bukan anggota dari M */

boolean IsMemberMap(Map M, keytype *k){
    if(!(IsEmptyMap(M))){
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
            if(char_counter == length_name(k)){
                return true;
            }
        }
    }
        
    
    
    return false;
    
}
/* Mengembalikan true jika k adalah member dari M */

