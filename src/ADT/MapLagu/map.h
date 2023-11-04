#ifndef map_H
#define map_H
#include <stdio.h>
#include "../boolean.h"


//PENJELASAN ADT MAP UNTUK TUBES INI
/*
    //REPRESENTASI VISUAL MAP
    MAP Playlist = { (["Key1"],[["Value1"],["Value2"],["Value3"]]), (["Key2"],[["Value1"],["Value2"],["Value3"]]), dst }

    //TIPE DATA MAPENTRY
    Key pada map berupa array of character sebesar name_length 
    Value pada map berupa  array 2 dimensi (matrix) of character sebesar MaxEl,name_length

    //MAP
    Elements merupakan array of MAPENTRY sebesar MaxEl
    Count merupakan jumlah elemen di Elements
*/



// #define false 0
// #define true 1
#define Nil 0
#define idx_undef -1
#define MaxEl 100
#define Undefined '\0'

#define name_length 51

// typedef int bool;
typedef char keytype;
typedef char valuetype;


typedef struct {
	keytype Key[name_length];
	
	valuetype Value[MaxEl][name_length];
} MapEntry;

typedef struct {
	MapEntry Elements[MaxEl];
	int Count;
} Map;

/* Definisi Map M kosong : M.Count = Nil */
/* M.Count = jumlah element Map */
/* M.Elements = tempat penyimpanan element Map */

/* ********* Prototype ********* */

/* *** Konstruktor/Kreator *** */
void CreateEmptyMap(Map *M);
/* I.S. Sembarang */
/* F.S. Membuat sebuah Map M kosong berkapasitas MaxEl */
/* Ciri Map kosong : count bernilai Nil */

/* ********* Predikat Untuk test keadaan KOLEKSI ********* */
boolean IsEmptyMap(Map M);
/* Mengirim true jika Map M kosong*/
/* Ciri Map kosong : count bernilai Nil */

boolean IsFullMap(Map M);
/* Mengirim true jika Map M penuh */
/* Ciri Map penuh : count bernilai MaxEl */

boolean isElEmpty(Map M, int idx);

int length_name(char *str);

int find_value_idx(Map M, keytype* k, valuetype* value);

int find_empty_value_idx(Map M, keytype* k);

int find_key_idx(Map M, keytype *k);

int find_empty_map_idx(Map M);

/* ********** Operator Dasar Map ********* */


void Insert(Map *M, keytype *k, valuetype *v);
/* Menambahkan Elmt sebagai elemen Map M. */
/* I.S. M mungkin kosong, M tidak penuh
        M mungkin sudah beranggotakan v dengan key k */
/* F.S. v menjadi anggota dari M dengan key k. Jika k sudah ada, operasi tidak dilakukan */

void Delete(Map *M, keytype *k, valuetype* value);
/* Menghapus Elmt dari Map M. */
/* I.S. M tidak kosong
        element dengan key k mungkin anggota / bukan anggota dari M */
/* F.S. element dengan key k bukan anggota dari M */

boolean IsMemberMap(Map M, keytype* k, int length);
/* Mengembalikan true jika k adalah member dari M */




#endif