#include <stdio.h> 
#include "queue.h"

void CreateQueue(Queue *q){
  q->idxHead = IDX_UNDEF; 
  q->idxTail = IDX_UNDEF; 
}

boolean isEmpty(Queue q){
  return (q.idxHead == IDX_UNDEF && q.idxTail == IDX_UNDEF);
}

boolean isFull(Queue q){
  return (q.idxHead == 0 && q.idxTail == CAPACITY -1); 
}

int length(Queue q){
  return q.idxTail - q.idxHead + 1; 
}

void enqueue(Queue *q, ElType val){
  if(isEmpty(*q)){ 
    q->idxHead = 0; 
    q->idxTail = 0; 
  }
  else{
      if(q->idxTail == CAPACITY - 1){
        for(int i =q->idxHead; i<=q->idxTail;i++){
          q->buffer[i-q->idxHead] = q->buffer[i]; 
        }
        q->idxTail-=q->idxHead;
        q->idxHead = 0;
      }
      q->idxTail++; 
  }
  q-> buffer[q->idxTail] = val; 

}

void dequeue(Queue *q, ElType *val){
  *val = q->buffer[q->idxHead]; 
  if(q->idxHead == q->idxTail){
    q->idxHead = IDX_UNDEF;
    q->idxTail = IDX_UNDEF; 
  }
  else{
    q->idxHead ++; 
  }
}
void displayQueue(Queue q){
  printf("["); 
  int index= q.idxHead; 
  if(!isEmpty(q)){
    while(index != q.idxTail){
      printf("%d,", q.buffer[index]); 
      index++;
    }
    printf("%d",q.buffer[index]);
  }
  printf("]\n");
}
