#include <stdio.h>
#include <stdlib.h> 

#define MAX_SIZE_HEAP 1000  
typedef struct {
    int *arr ; 
    int capacity; 
    int size  ; 
} MinMaxHeap; 

MinMaxHeap* createMinMaxHeap(int capacity) {
    MinMaxHeap* heap = malloc(sizeof(MinMaxHeap) )  ; 
    heap->arr= malloc(sizeof(int)*capacity )  ; 
    heap->size = 0 ; 
    heap->capacity = capacity ; 
    return heap ; 
}

int minimumElement(MinMaxHeap* heap ){
    if (!heap || !heap->arr || heap ->size<1) {
        printf("your heap does not have any minimum elements!") ; 
        exit(0); 
        
    } 
    return heap->arr[0];
    
} 

int maximumElement(MinMaxHeap * heap) { 
    if (!heap || !heap->arr || heap->size < 1 ) {
        printf("your heap does not have any maximum element!") ; 
        exit(0); 
    } 
    if(heap->size == 1 ) return heap->arr[0] ;  
    if(heap ->size == 2 ) return heap->arr[1] ; 
    return heap->arr[1]>heap->arr[2] ? heap->arr[1] : heap->arr[2] ; 
    
}

void swap(int * a, int *b ) {
    int temp = *a ; 
    *a = * b ;
    *b = temp ; 
}

void percolateUpForMinHeap(MinMaxHeap* heap, int index) {
    int parent = (index - 1) / 2;
    int temp;
    while (index > 0 && heap->arr[parent] > heap->arr[index]) {
        temp = heap->arr[parent];
        heap->arr[parent] = heap->arr[index];
        heap->arr[index] = temp;
        index = parent;
        parent = (index - 1) / 2;
    }
}

void percolateUp(MinMaxHeap* heap, int index, int MinOrMaxHeap) { 
    int ancestorIndex= (index - 3 )/4 ; 
    
    if (MinOrMaxHeap == 1 ) { 
        while(ancestorIndex > 0 &&  heap->arr[index] > heap->arr[ancestorIndex])  {
            swap(&(heap->arr[index]),  &(heap->arr[ancestorIndex]) );
            index = ancestorIndex ; 
            ancestorIndex = (index - 3 )/4 ; 
            
        }
    }
    else {
        while (index > 0 && heap->arr[index] < heap->arr[ancestorIndex]) {
            swap(&(heap->arr[index]),  &(heap->arr[ancestorIndex])) ;
            index = ancestorIndex ; 
            ancestorIndex = (index - 3 )/4 ; 
        }
    }
        
}

void push(MinMaxHeap* heap, int value)  {
    if(heap->size == heap->capacity) {
        printf("heap overflow!!!\n" ); 
        return;   
    } 
    heap->arr[heap->size++] = value ;  
    if(heap->size < 3 ){
     
        percolateUpForMinHeap(heap,heap->size -1 ) ;
    }
    else{ 
       
        int MinOrMaxValue; 
        if(heap->arr[(heap->size-2)/2 ]< heap->arr[(heap->size-4)/4]  ){
            MinOrMaxValue = 1 ; 
        else {
            MinOrMaxValue = 0 ; 
        }
        int currIndex = heap->size -1 ; 
        if( MinOrMaxValue == 1 && heap->arr[heap-> size -1] < heap->arr[(heap->size-2)/2 ] ) { 
            swap( &(heap->arr[heap-> size -1]),&(heap->arr[(heap->size-2)/2 ]) ) ; 
            currIndex =  (heap->size-2)/2 ; 
            MinOrMaxValue = 0 ; 
        }    
        
        else if( MinOrMaxValue == 0 && heap->arr[heap-> size -1] > heap->arr[(heap->size-2)/2 ] ) { 
            swap( &(heap->arr[heap-> size -1]),&(heap->arr[(heap->size-2)/2 ]) ) ; 
            currIndex =  (heap->size-2)/2 ; 
            MinOrMaxValue = 1 ; 
        }
        percolateUp(heap, currIndex, MinOrMaxValue ); 
    }
 }

void printHeap(MinMaxHeap* heap) {
    printf("Heap: ");
    for (int i = 0; i < heap->size; i++) {
        printf("%d ", heap->arr[i]);
    }
    printf("\n");
}

int main()
{
    
    MinMaxHeap * heap = createMinMaxHeap(MAX_SIZE_HEAP); 
    
    push(heap,81);  
    push(heap,17);
    push(heap,87);  
    push(heap,14);  
      
    push(heap,12);  
    push(heap,28); 
    push(heap,6); 
    push(heap, 24); 
    push(heap, 5);  
 
    printHeap(heap); 

    return 0;
}
