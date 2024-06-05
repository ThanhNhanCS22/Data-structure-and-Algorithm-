
#include <stdio.h>
#include <stdlib.h>

#define MAX_HEAP_SIZE 100

typedef struct {
    int *arr;
    int size;
    int capacity;
}  MaxHeap ; 

MaxHeap* createMaxHeap(int capacity) {
    MaxHeap* heap = malloc(sizeof(MaxHeap));
    heap->arr = malloc(capacity * sizeof(int));
    heap->size = 0;
    heap->capacity = capacity;
    return heap;
}

void percolateUp(MaxHeap* heap, int index) {
    int parent = (index - 1) / 2;
    int temp;
    while (index > 0 && heap->arr[parent] < heap->arr[index]) {
        temp = heap->arr[parent];
        heap->arr[parent] = heap->arr[index];
        heap->arr[index] = temp;
        index = parent;
        parent = (index - 1) / 2;
    }
}

void percolateDown(MaxHeap* heap, int index) {
    int leftChild, rightChild, minChild, temp;
    while (1) {
        leftChild = 2 * index + 1;
        rightChild = 2 * index + 2;
        minChild = index;

        if (leftChild < heap->size && heap->arr[leftChild] > heap->arr[minChild])
            minChild = leftChild;
        if (rightChild < heap->size && heap->arr[rightChild] > heap->arr[minChild])
            minChild = rightChild;

        if (minChild != index) {
            temp = heap->arr[index];
            heap->arr[index] = heap->arr[minChild];
            heap->arr[minChild] = temp;
            index = minChild;
        } 
        else break;
    
    }
}
void swap(int * a, int * b){
    int temp =*a ; 
    *a = *b ; 
    *b = temp ; 
} 

void convertToMaxHeap(MaxHeap * heap  ){
    
    int childIndex  ; 
    int parentIndex ;
    if( heap->size  % 2 == 0 ){
        childIndex = heap->size -1 ; 
        parentIndex = (childIndex -1 )/2 ; 
        if(heap->arr[childIndex]>heap->arr[parentIndex]) swap(&(heap->arr[parentIndex]), &(heap->arr[childIndex]) );
        if ( heap->size  == 2 ) return; 
        childIndex = heap->arr[heap->size-2 ] > heap->arr[heap->size-3 ] ? heap->size-2 : heap->size -3 ;  
        parentIndex = (childIndex -1 )/2 ; 
        
    } 
    else {
        childIndex = heap->arr[heap->size-1 ] > heap->arr[heap->size-2 ] ? heap->size-1 : heap->size -2;
        parentIndex = (childIndex -1 )/2 ;
    }
    
    while(1) {
         
        if(heap->arr[childIndex]>heap->arr[parentIndex]) swap(&(heap->arr[parentIndex]), &(heap->arr[childIndex]) );
        if(parentIndex == 0 )  break ; 
        parentIndex-- ; 
        childIndex = heap->arr[2*parentIndex+1] > heap->arr[2*parentIndex+2] 
                                        ? 2*parentIndex+1 : 2*parentIndex+2 ; 
                                        
        
    }
    
    percolateDown(heap, childIndex);  
}


int pop(MaxHeap * heap ) {
    if (heap->size == 0) {
        printf("Heap Underflow\n");
        exit(1); 
    }
    int temp = heap->arr[0] ; 
    heap->size -- ; 
   
    heap->arr[0] = heap->arr[heap->size ]; 
    
   
    percolateDown(heap,0); 
    return temp ; 
     
} 

void HeapSort(int *arr, int length ) {
    if (length <2 ) return ;  
    MaxHeap * heap = createMaxHeap(MAX_HEAP_SIZE) ;
    heap->size = length; 
    heap->arr =arr ; 
    
    convertToMaxHeap(heap) ; 
    while(heap->size!= 0) {
        int temp = pop(heap); 
        arr[heap->size] = temp ; 
        
    } 
    free(heap) ; 
}

MaxHeap* mergedTwoBinaryMaxHeap(MaxHeap* heap1, MaxHeap* heap2) {
    MaxHeap* heap = createMaxHeap(MAX_HEAP_SIZE); 
    heap->size = heap1->size + heap2->size ; 
    for(int i = 0 ; i < heap1->size ; i ++ ){
        heap->arr[i] = heap1->arr[i];  
    } 
    for (int i  = 0  ; i < heap2 ->size ; i ++ ){
        heap->arr[heap1->size+i] = heap2->arr[i]; 
    } 
    convertToMaxHeap(heap); 
    return heap ; 
    
} 


void push(MaxHeap* heap, int value) {
    if (heap->size == heap->capacity) {
        printf("Heap Overflow\n");
        return;
    }
    heap->arr[heap->size++] = value;
   
    percolateUp(heap, heap->size - 1);
}


void printHeap(MaxHeap* heap) {
    printf("Heap: ");
    for (int i = 0; i < heap->size; i++) {
        printf("%d ", heap->arr[i]);
    }
    printf("\n");
}
void findAllKeyGreaterThanValueK(int k, MaxHeap* heap) {
    printf("all values are greater than %d is:\n",k) ;
    for(int i = 0 ; i < heap->size ; i ++ ){ 
        
        if(heap->arr[i]>k) printf("%d ",heap->arr[i]) ;   
    }
    printf("\n");  
} 
int main() {
    MaxHeap* heap = createMaxHeap(MAX_HEAP_SIZE);

    push(heap, 5);
    push(heap, 3);
    push(heap, 8);
    push(heap, 1);
    push(heap, 9);

    printHeap(heap);
    printf("%d\n",heap->size);  
    pop(heap); 
    printHeap(heap);
    printf("%d\n",heap->size);
    findAllKeyGreaterThanValueK(5, heap);
     
    int arr[] = {4,10,1,5,3,}; 
    int length = sizeof(arr)/sizeof(int ); 
    
    
    HeapSort(arr, length); 
    for(int i = 0 ; i < length; i++) {
        printf("%d ",arr[i]) ; 
        
    } 
    int arr1[] ={10,5,6,2}; 
    int arr2[] ={12,7,9} ;
    MaxHeap* heap1 = createMaxHeap(MAX_HEAP_SIZE) ; 
    heap1->arr = arr1 ; 
    heap1->size = 4 ;
    MaxHeap* heap2 = createMaxHeap(MAX_HEAP_SIZE); 
    heap2->arr = arr2 ; 
    heap2->size = 3 ; 
    
    MaxHeap * mergedHeap = mergedTwoBinaryMaxHeap(heap1, heap2) ; 
    printHeap(mergedHeap) ; 
    
    
    
    
    free(heap->arr);
    free(heap);

    return 0;
}



