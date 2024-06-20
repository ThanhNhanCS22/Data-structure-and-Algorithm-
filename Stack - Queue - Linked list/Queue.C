
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
struct Queue {
    int size ; 
    int front ; 
    int rear ; 
    int * arr ; 
};
bool isFull(struct Queue *q ){
    if(q->rear == q->size-1 )  return 1 ; 
    return  0; 
    
} 
   
bool isEmpty(struct Queue* q) {
    if(q->rear == q->front ) return 1 ; 
    return 0 ; 
}



void enqueue(struct Queue *q, int val  ){
    if(isFull(q) ) {
        printf("This queue is full!!!\n"); 
        exit(1) ; 
        
    } 
    else {
        (*q).arr[++((*q).rear)] = val  ; 
    }
} 

int dequeue(struct Queue *q ){
    
    if(isEmpty(q) ) {
        printf("This queue is empty!!!\n"); 
        exit(1); 
        
    } 
    else {
        return q->arr[++ (q->front )] ; 
    }
} 


int main()
{
    struct Queue q ; 
    q.size = 100 ; 
    q.front = q.rear = -1 ; 
    q.arr = malloc(q.size*sizeof(int)) ; 
    enqueue( &q,12); 
    enqueue( &q,18); 
    
    printf("%d\n", dequeue(&q)) ;
    printf("%d\n", dequeue(&q)) ;
    printf("%d\n", dequeue(&q)) ;
    

    return 0;
}
