#include <stdio.h>
#include "queue.h"

int main() {
    Queue q;
    ElType temp;

    CreateQueue(&q);

    printf("Is Queue Empty? %s\n", isEmpty(q) ? "Yes" : "No");

    Lagu lagu1 = { {"Taylor Swift", 13}, {"Album A", 7}, {"Shake it Off", 12} };
    Lagu lagu2 = { {"Zayn", 4}, {"Album BB", 8}, {"Dusk Till Dawn", 14} };
    Lagu lagu3 = { {"Justin Bieber", 14}, {"Album Cc", 8}, {"Baby", 4} };

    enqueue(&q, lagu1);
    enqueue(&q, lagu2);
    enqueue(&q, lagu3);


    printf("Is Queue Empty? %s\n", isEmpty(q) ? "Yes" : "No");
    printf("Is Queue Full? %s\n", isFull(q) ? "Yes" : "No");

    printf("Length of Queue: %d\n", length(q));

    printf("Displaying Queue: ");
    displayQueue(q);

    dequeue(&q, &temp);
    printf("\nDequeued element: "); // Melihat elemen yang di-dequeue
    // Tambahkan kode untuk menampilkan nilai elemen yang di-dequeue sesuai dengan tipe data ElType
    displayQueue(q);

    return 0;
}
