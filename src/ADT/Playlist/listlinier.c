/* File : listlinier.C */
/* contoh ADT list berkait dengan representasi fisik pointer  */
/* Representasi addressLinkedList dengan pointer */
/* infotype adalah integer */

#include "stdio.h"
#include "stdlib.h"
#include "listlinier.h"

/* PROTOTYPE */
/****************** TEST LIST KOSONG ******************/
boolean IsEmptyLL (LinkedList L)
/* Mengirim true jika list kosong */
{
  return First(L) == Nil_LL;
}

/****************** PEMBUATAN LIST KOSONG ******************/
void CreateEmptyLL (LinkedList *L)
/* I.S. sembarang             */
/* F.S. Terbentuk list kosong */
{
  First(*L) = Nil_LL;
}

/****************** Manajemen Memori ******************/
addressLinkedList Alokasi (infotype X)
/* Mengirimkan addressLinkedList hasil alokasi sebuah elemen */
/* Jika alokasi berhasil, maka addressLinkedList tidak nil, dan misalnya */
/* menghasilkan P, maka Info(P)=X, Next(P)=Nil_LL */
/* Jika alokasi gagal, mengirimkan Nil_LL */
{
  addressLinkedList P = (addressLinkedList) malloc(1 * sizeof (ElmtLinkedList));
  if (P != Nil_LL) {
    Info(P) = X;
    Next(P) = Nil_LL;
    return P;
  } {
    return Nil_LL;
  }
}

void Dealokasi (addressLinkedList *P)
/* I.S. P terdefinisi */
/* F.S. P dikembalikan ke sistem */
/* Melakukan dealokasi/pengembalian addressLinkedList P */
{
  free(*P);
}

/****************** PENCARIAN SEBUAH ELEMEN LIST ******************/
addressLinkedList Search (LinkedList L, infotype X)
/* Mencari apakah ada elemen list dengan Info(P)= X */
/* Jika ada, mengirimkan addressLinkedList elemen tersebut. */
/* Jika tidak ada, mengirimkan Nil_LL */
{
  addressLinkedList P;
  boolean bFound = false;

  if (!IsEmptyLL(L)) {
    P = First(L);
    while (!bFound && P != Nil_LL) {
      if (CompareLagu(X, Info(P))) {
        bFound = true;
      } else {
        P = Next(P);
      }
    }

    if (bFound) {
      return P;
    } else {
      return Nil_LL;
    }

  } else {
    return Nil_LL;
  }
}

/****************** PRIMITIF BERDASARKAN NILAI ******************/
/*** PENAMBAHAN ELEMEN ***/
void InsVFirst (LinkedList *L, infotype X)
/* I.S. L mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen pertama dengan nilai X jika alokasi berhasil */
{
  addressLinkedList P = Alokasi(X);
  if (P != Nil_LL) {
    InsertFirst(L, P);
  }
}

void InsVLast (LinkedList *L, infotype X)
/* I.S. L mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen list di akhir: elemen terakhir yang baru */
/* bernilai X jika alokasi berhasil. Jika alokasi gagal: I.S.= F.S. */
{
  addressLinkedList P = Alokasi(X);
  if (P != Nil_LL) {
    InsertLast(L, P);
  }
}

/*** PENGHAPUSAN ELEMEN ***/
void DelVFirst (LinkedList *L, infotype *X)
/* I.S. LinkedList L tidak kosong  */
/* F.S. Elemen pertama list dihapus: nilai info disimpan pada X */
/*      dan alamat elemen pertama di-dtpealokasi */
{
  addressLinkedList P = First(*L);
  *X = Info(P);
  First(*L) = Next(P);
  Dealokasi(&P);
}

void DelVLast (LinkedList *L, infotype *X)
/* I.S. list tidak kosong */
/* F.S. Elemen terakhir list dihapus: nilai info disimpan pada X */
/*      dan alamat elemen terakhir di-dealokasi */
{
  addressLinkedList P = First(*L);
  addressLinkedList Prec = Nil_LL;

  while (Next(P) != Nil_LL) {
    Prec = P;
    P = Next(P);
  }

  *X = Info(P);
  if (Prec != Nil_LL) {
    Next(Prec) = Nil_LL;
  } else {
    First(*L) = Nil_LL;
  }
  Dealokasi(&P);

}

/****************** PRIMITIF BERDASARKAN ALAMAT ******************/
/*** PENAMBAHAN ELEMEN BERDASARKAN ALAMAT ***/
void InsertFirst (LinkedList *L, addressLinkedList P)
/* I.S. Sembarang, P sudah dialokasi  */
/* F.S. Menambahkan elemen ber-addressLinkedList P sebagai elemen pertama */
{
  Next(P) = First(*L);
  First(*L) = P;
}

void InsertAfter (LinkedList *L, addressLinkedList P, addressLinkedList Prec)
/* I.S. Prec pastilah elemen list dan bukan elemen terakhir, */
/*      P sudah dialokasi  */
/* F.S. Insert P sebagai elemen sesudah elemen beralamat Prec */
{
  Next(P) = Next(Prec);
  Next(Prec) = P;
}

void InsertLast (LinkedList *L, addressLinkedList P)
/* I.S. Sembarang, P sudah dialokasi  */
/* F.S. P ditambahkan sebagai elemen terakhir yang baru */
{
  addressLinkedList Last;

  if (IsEmptyLL(*L)) {
    InsertFirst(L, P);
  } else {
    Last = First(*L);
    while (Next(Last) != Nil_LL) {
      Last = Next(Last);
    }
    InsertAfter(L, P, Last);
  }
}

/*** PENGHAPUSAN SEBUAH ELEMEN ***/
void DelFirst (LinkedList *L, addressLinkedList *P)
/* I.S. LinkedList tidak kosong */
/* F.S. P adalah alamat elemen pertama list sebelum penghapusan */
/*      Elemen list berkurang satu (mungkin menjadi kosong) */
/* First element yg baru adalah suksesor elemen pertama yang lama */
{
  *P = First(*L);
  L->First = L->First->next;
  Next(*P) = Nil_LL;
}

void DelP (LinkedList *L, infotype X)
/* I.S. Sembarang */
/* F.S. Jika ada elemen list beraddressLinkedList P, dengan Info(P)=X  */
/* Maka P dihapus dari list dan di-dealokasi */
/* Jika tidak ada elemen list dengan Info(P)=X, maka list tetap */
/* LinkedList mungkin menjadi kosong karena penghapusan */
{
  addressLinkedList Prec;
  addressLinkedList P;
  boolean bFound = false;

  if (!IsEmptyLL(*L)) {
    if (CompareLagu(X, Info(First(*L)))){
      DelFirst(L, &P);
      Dealokasi(&P);
    } else {
      P = First(*L);
      while (!bFound && P != Nil_LL) {
        if (CompareLagu(X, Info(P))) {
          bFound = true;
        } else {
          Prec = P;
          P = Next(P);
        }
      }

      if (bFound) {
        DelAfter(L, &P, Prec);
        Dealokasi(&P);
      }
    }
  }
}

void DelLast (LinkedList *L, addressLinkedList *P)
/* I.S. LinkedList tidak kosong */
/* F.S. P adalah alamat elemen terakhir list sebelum penghapusan  */
/*      Elemen list berkurang satu (mungkin menjadi kosong) */
/* Last element baru adalah predesesor elemen pertama yg lama, */
/* jika ada */
{
  addressLinkedList Last = First(*L);
  addressLinkedList PrecLast = Nil_LL;

  while (Next(Last) != Nil_LL) {
    PrecLast = Last;
    Last = Next(Last);
  }

  *P = Last;
  if (PrecLast == Nil_LL) {
    First(*L) = Nil_LL;
  } else {
    Next(PrecLast) = Nil_LL;
  }
}

void DelAfter (LinkedList *L, addressLinkedList *Pdel, addressLinkedList Prec)
/* I.S. LinkedList tidak kosong. Prec adalah anggota list  */
/* F.S. Menghapus Next(Prec): */
/*      Pdel adalah alamat elemen list yang dihapus  */
{
  *Pdel = Next(Prec);
  Next(Prec) = Next(Next(Prec));
  Next(*Pdel) = Nil_LL;
}

/****************** PROSES SEMUA ELEMEN LIST ******************/
void PrintInfo (LinkedList L)
/* I.S. LinkedList mungkin kosong */
/* F.S. Jika list tidak kosong, isi list dicetak ke kanan: [e1,e2,...,en] */
/* Contoh : jika ada tiga elemen bernilai 1, 20, 30 akan dicetak: [1,20,30] */
/* Jika list kosong : menulis [] */
/* Tidak ada tambahan karakter apa pun di awal, akhir, atau di tengah terkecuali untuk newline di akhir output */
{
  //addressLinkedList P;
  //boolean isFirst = true;

  //printf("[");
  //if (!IsEmptyLL(L)) {
  //  P = First(L);
  //  while (P != Nil_LL) {
  //    if (!isFirst) {
  //      printf(",");
  //    }
  //    printf("%d", Info(P));
  //    isFirst = false;

  //    P = Next(P);
  //  }
  //}
  //printf("]\n");


}
int NbElmt (LinkedList L)
/* Mengirimkan banyaknya elemen list; mengirimkan 0 jika list kosong */
{
  int cnt = 0;
  addressLinkedList P;

  if (!IsEmptyLL(L)) {
    P = First(L);
    while (P != Nil_LL) {
      cnt++;
      P = Next(P);
    }
  }

  return cnt;
}



/****************** PROSES TERHADAP LIST ******************/
void InversLinkedList (LinkedList *L)
/* I.S. sembarang. */
/* F.S. elemen list dibalik : */
/* Elemen terakhir menjadi elemen pertama, dan seterusnya. */
/* Membalik elemen list, tanpa melakukan alokasi/dealokasi. */
{
	addressLinkedList P;
	addressLinkedList Prec = Nil_LL;
	addressLinkedList Succ;
	
	if (!IsEmptyLL(*L)) {
		P = First(*L);
		while (P != Nil_LL) {
			Succ = Next(P);
			Next(P) = Prec;
			Prec = P;
			P = Succ;
		}
		First(*L) = Prec;
	}
}


void Konkat1 (LinkedList *L1, LinkedList *L2, LinkedList *L3)
/* I.S. L1 dan L2 sembarang */
/* F.S. L1 dan L2 kosong, L3 adalah hasil konkatenasi L1 & L2 */
/* Konkatenasi dua buah list : L1 dan L2    */
/* menghasilkan L3 yang baru (dengan elemen list L1 dan L2) */
/* dan L1 serta L2 menjadi list kosong.*/
/* Tidak ada alokasi/dealokasi pada prosedur ini */
{
  addressLinkedList Last1;

  CreateEmptyLL(L3);
  if (IsEmptyLL(*L1)) {
    First(*L3) = First(*L2);
  } else {
    First(*L3) = First(*L1);
    Last1 = First(*L1);
    while (Next(Last1) != Nil_LL) {
      Last1 = Next(Last1);
    }
    Next(Last1) = First(*L2);
  }

  First(*L1) = Nil_LL;
  First(*L2) = Nil_LL;
}
