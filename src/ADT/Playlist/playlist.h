#ifndef playlist_H
#define playlist_H
#include <stdio.h>

#include "../boolean.h"
#include "listlinier.h"

/* MODUL Map
Deklarasi stack yang dengan implementasi array eksplisit-statik rata kiri
*/

// #define false 0
// #define true 1
#define NilMap 0 
#define MaxElMapPlaylist 100

// typedef int bool;
typedef LinkedList IsiPlaylist;
typedef Word JudulPlaylist;

typedef struct {
	JudulPlaylist Key;
  IsiPlaylist Value;
} LinkedListPlaylist;

typedef struct {
	LinkedListPlaylist Elements[MaxElMapPlaylist];
	int Count;
} Playlist;

/* Definisi Map M kosong : M.Count = Nil */
/* M.Count = jumlah element Map */
/* M.Elements = tempat penyimpanan element Map */

/* ********* Prototype ********* */

/* *** Konstruktor/Kreator *** */
void CreateEmptyPlaylist(Playlist *M);
/* I.S. Sembarang */
/* F.S. Membuat sebuah Map M kosong berkapasitas MaxEl */
/* Ciri Map kosong : count bernilai Nil */

/* ********* Predikat Untuk test keadaan KOLEKSI ********* */
boolean IsEmptyPlaylist(Playlist M);
/* Mengirim true jika Map M kosong*/
/* Ciri Map kosong : count bernilai Nil */

boolean IsFullPlaylist(Playlist M);
/* Mengirim true jika Map M penuh */
/* Ciri Map penuh : count bernilai MaxEl */

/* ********** Operator Dasar Map ********* */
IsiPlaylist ValuePlaylist(Playlist M, JudulPlaylist k);
/* Mengembalikan nilai value dengan key k dari M */
/* Jika tidak ada key k pada M, akan mengembalikan Undefined */

void InsertPlaylist(Playlist *M, JudulPlaylist k, IsiPlaylist v);
/* Menambahkan Elmt sebagai elemen Map M. */
/* I.S. M mungkin kosong, M tidak penuh
        M mungkin sudah beranggotakan v dengan key k */
/* F.S. v menjadi anggota dari M dengan key k. Jika k sudah ada, operasi tidak dilakukan */

void DeletePlaylist(Playlist *M, JudulPlaylist k);
/* Menghapus Elmt dari Map M. */
/* I.S. M tidak kosong
        element dengan key k mungkin anggota / bukan anggota dari M */
/* F.S. element dengan key k bukan anggota dari M */

boolean IsMemberPlaylist(Playlist M, JudulPlaylist k);
/* Mengembalikan true jika k adalah member dari M */

#endif
