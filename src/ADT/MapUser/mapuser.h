#ifndef mapuser_H
#define mapuser_H
#include <stdio.h>
#include "../boolean.h"
#include "../Word/word.h"
#include "../SetWord/set.h"
#include "../Queue/queue.h"
#include "../StackLagu/stack.h"
#include "../Playlist/playlist.h"

/* MODUL MapUser
Deklarasi stack yang dengan implementasi array eksplisit-statik rata kiri
*/

// #define false 0
// #define true 1
#define MaxElMapUserUser 100

// typedef int bool;
typedef Word UserName;
typedef int address;

//MapUser memiliki 3 values : Stack - History, Queue, dan Daftar Playlist
typedef struct {
	UserName Key;
  Stack HistoryUser; 
  Queue QueueUser; 
  Playlist PlaylistUser;
} UserInformation;

typedef struct {
	UserInformation Elements[MaxElMapUserUser];
	address Count;
} MapUser;

/* Definisi MapUser M kosong : M.Count = Nil */
/* M.Count = jumlah element MapUser */
/* M.Elements = tempat penyimpanan element MapUser */

/* ********* Prototype ********* */

/* *** Konstruktor/Kreator *** */
void CreateEmptyMapUser(MapUser *M);
/* I.S. Sembarang */
/* F.S. Membuat sebuah MapUser M kosong berkapasitas MaxEl */
/* Ciri MapUser kosong : count bernilai Nil */

/* ********* Predikat Untuk test keadaan KOLEKSI ********* */
boolean IsEmptyMapUser(MapUser M);
/* Mengirim true jika MapUser M kosong*/
/* Ciri MapUser kosong : count bernilai Nil */

boolean IsFullMapUser(MapUser M);
/* Mengirim true jika MapUser M penuh */
/* Ciri MapUser penuh : count bernilai MaxEl */

/* ********** Operator Dasar MapUser ********* */
wordvaluetype Value(MapUser M, wordkeytype k);
/* Mengembalikan nilai value dengan key k dari M */
/* Jika tidak ada key k pada M, akan mengembalikan Undefined */

void Insert(MapUser *M, wordkeytype k, wordvaluetype v);
/* Menambahkan Elmt sebagai elemen MapUser M. */
/* I.S. M mungkin kosong, M tidak penuh
        M mungkin sudah beranggotakan v dengan key k */
/* F.S. v menjadi anggota dari M dengan key k. Jika k sudah ada, operasi tidak dilakukan */

void Delete(MapUser *M, wordkeytype k);
/* Menghapus Elmt dari MapUser M. */
/* I.S. M tidak kosong
        element dengan key k mungkin anggota / bukan anggota dari M */
/* F.S. element dengan key k bukan anggota dari M */

boolean IsMember(MapUser M, wordkeytype k);
/* Mengembalikan true jika k adalah member dari M */

#endif
