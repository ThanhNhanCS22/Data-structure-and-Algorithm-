
#include <stdio.h>
#include <stdlib.h>

#define MAX_HEAP_SIZE 100

typedef struct {
    int *arr;
    int size;
    int capacity;
} MinHeap;

MinHeap* createMinHeap(int capacity) {
    MinHeap* heap = (MinHeap*)malloc(sizeof(MinHeap));
    heap->arr = (int*)malloc(capacity * sizeof(int));
    heap->size = 0;
    heap->capacity = capacity;
    return heap;
}

void percolateUp(MinHeap* heap, int index) {
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

void percolateDown(MinHeap* heap, int index) {
    int leftChild, rightChild, minChild, temp;
    while (1) {
        leftChild = 2 * index + 1;
        rightChild = 2 * index + 2;
        minChild = index;

        if (leftChild < heap->size && heap->arr[leftChild] < heap->arr[minChild])
            minChild = leftChild;
        if (rightChild < heap->size && heap->arr[rightChild] < heap->arr[minChild])
            minChild = rightChild;

        if (minChild != index) {
            temp = heap->arr[index];
            heap->arr[index] = heap->arr[minChild];
            heap->arr[minChild] = temp;
            index = minChild;
        } else {
            break;
        }
    }
}

void push(MinHeap* heap, int value) {
    if (heap->size == heap->capacity) {
        printf("Heap Overflow\n");
        return;
    }
    heap->arr[heap->size++] = value;
   
    percolateUp(heap, heap->size - 1);
}

int deleteMin(MinHeap* heap) {
    if (heap->size == 0) {
        printf("Heap Underflow\n");
        return -1;
    }
    int minVal = heap->arr[0];
    heap->arr[0] = heap->arr[((heap->size)--) - 1];
    //heap->size--;
    percolateDown(heap, 0);
    return minVal;
}
void DeleteArbitrary(MinHeap* heap, int arbitraryValue) { 
    int index = -1 ;
    for(int i = 0 ; i < heap->size ; i ++) { 
        if(heap->arr[i] == arbitraryValue) {
            index = i ; 
            break ; 
        }
    }
    if(index!= -1 ){ 
        heap->arr[index] = heap->arr[((heap->size)--) - 1];
        percolateDown(heap, index); 
        
        
    }
    
}
void printHeap(MinHeap* heap) {
    printf("Heap: ");
    for (int i = 0; i < heap->size; i++) {
        printf("%d ", heap->arr[i]);
    }
    printf("\n");
}

int main() {
    MinHeap* heap = createMinHeap(MAX_HEAP_SIZE);

    push(heap, 5);
    push(heap, 3);
    push(heap, 8);
    push(heap, 1);
    push(heap, 9);

    printHeap(heap);
    DeleteArbitrary(heap, 10) ; 
    printHeap(heap) ; 
    /*printf("Deleting min: %d\n", deleteMin(heap));

    printHeap(heap);*/
    
    
    free(heap->arr);
    free(heap);

    return 0;
}


