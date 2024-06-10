#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#define MAX 100
#define MAX_HEAP_SIZE 100

typedef struct Graph {
    int numVertices;
    int adjMatrix[MAX][MAX];  
    char**cityArr ; 
} Graph;

typedef struct {
   
    int *arr;
    int size;
    int capacity;
} MinHeap;

typedef struct {

    int *edgeTo ; 
    int *distanceTo ; 
    
} MST ; 


Graph* createGraph(int vertices, char** cityArr) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->numVertices = vertices;
    graph->cityArr= cityArr; 
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            graph->adjMatrix[i][j] = 0;  
        }
    }
    return graph;
}


void addEdgeAndDistance(Graph* graph, int src, int dest, int dist) {
    graph->adjMatrix[src][dest] = dist ;  
    graph->adjMatrix[dest][src] = dist ;  
}


void printGraph(Graph* graph) {
    for (int i = 0; i < graph->numVertices; i++) {
        for (int j = 0; j < graph->numVertices; j++) {
            printf("%d ", graph->adjMatrix[i][j]);
        }
        printf("\n");
    }
}

MinHeap* createMinHeap(int capacity) {
    MinHeap* heap = (MinHeap*)malloc(sizeof(MinHeap));
    heap->arr = malloc(capacity * sizeof(int));

    heap->size = 0;
    heap->capacity = capacity;
    return heap;
}

void percolateUp(MinHeap* heap, int index,MST* mst ) {
    int parent = (index - 1) / 2;
    int temp;
    
    while (index > 0 && mst->distanceTo[heap->arr[parent]]  > mst->distanceTo[heap->arr[index]]) {
        
        temp = heap->arr[parent];
        heap->arr[parent] = heap->arr[index];
        heap->arr[index] = temp;
    
        index = parent;
        parent = (index - 1) / 2;
    }
}

void percolateDown(MinHeap* heap, int index, MST * mst ) {
    int leftChild, rightChild, minChild, temp;
    while (1) {
        leftChild = 2 * index + 1;
        rightChild = 2 * index + 2;
        minChild = index;

        if (leftChild < heap->size 
        && mst->distanceTo[heap->arr[leftChild] ]< mst->distanceTo[ heap->arr[minChild] ] )
            minChild = leftChild;
        if (rightChild < heap->size 
        && mst->distanceTo[heap->arr[rightChild]] < mst->distanceTo[heap->arr[minChild]])
            minChild = rightChild;

        if (minChild != index) {
            
            temp = heap->arr[index];
            heap->arr[index] = heap->arr[minChild];
            heap->arr[minChild] = temp;
            
            index = minChild;
        } 
        
        else {
            break;
        }
    }
}

void push(MinHeap* heap, int value, MST* mst ) {
    if (heap->size == heap->capacity) {
        printf("Heap Overflow\n");
        return;
    }
    heap->arr[heap->size++] = value;
    
    percolateUp(heap, heap->size - 1,mst);
}

int pop(MinHeap* heap,MST* mst ) {
    if (heap->size == 0) {
        printf("Heap Underflow\n");
        return -1;
    }
    int minVal = heap->arr[0];
    
    heap->arr[0] = heap->arr[((heap->size)--) - 1];
    
    percolateDown(heap, 0,mst);
    return minVal;
}



MST * optimalPrimAlgorithmForMST(Graph *graph , int startVertex ) {
    MST *newMST = malloc(sizeof(MST)); 
    newMST->edgeTo = malloc(sizeof(int) *graph->numVertices); 
    newMST-> distanceTo= malloc(sizeof(int)* graph->numVertices) ; 
     
    for(int i = 0 ; i < graph->numVertices ; i++) {
        newMST->distanceTo[i] =  INT_MAX ; 
        
    } 
    
    newMST->distanceTo[startVertex]= 0 ; 
    newMST->edgeTo[startVertex] = -1  ; 
    
    
    MinHeap *heap= malloc(sizeof(MinHeap)); 
    
    heap= createMinHeap(graph->numVertices) ; 
    
    for(int i = 0 ; i < graph->numVertices; i++ ){ 
        push(heap, i , newMST) ; 
        
    }
    
    int currVisited ; 
    
    
    for (int j =0 ; j < graph->numVertices ; j++ ){ 
        
        currVisited = pop(heap , newMST);  
        for(int i = 0 ; i < heap ->size ; i++) {
            
            if(graph->adjMatrix[currVisited][heap->arr[i]] 
                && graph->adjMatrix[currVisited][heap->arr[i]]<newMST->distanceTo[heap->arr[i]] ){
                    
                newMST->distanceTo[heap->arr[i]] = graph->adjMatrix[currVisited][heap->arr[i]] ; 
                newMST->edgeTo[heap->arr[i]] = currVisited ;  
                
                percolateUp(heap,i,newMST )  ; 
                
            }
        }
       
    }
    return newMST ; 
    
} 



int main() {
    int vertices = 7;  
    
    char* cityArr[7] = {"A","B","C","D","E","F","G"} ;
    Graph* graph = createGraph(vertices,cityArr); 
    addEdgeAndDistance(graph,0,1,2); 
    addEdgeAndDistance(graph,0,2,1);
    
    addEdgeAndDistance(graph,1,2,5);
    addEdgeAndDistance(graph,1,3,11); 
    addEdgeAndDistance(graph,1,4,3);
    addEdgeAndDistance(graph,2,4,1);
    addEdgeAndDistance(graph,2,5,15);
    
    addEdgeAndDistance(graph,3,4,2);
    addEdgeAndDistance(graph,3,6,1);
    addEdgeAndDistance(graph,4,5,4);
    addEdgeAndDistance(graph,4,6,3);
    addEdgeAndDistance(graph,5,6,1); 
    
    printGraph(graph);  
    MST* mst= optimalPrimAlgorithmForMST(graph,0);  
    
    printf("Cities:\n") ;
    for(int i = 0 ; i <  graph->numVertices ; i++ )  {  
        printf("%s ", graph->cityArr[i] ) ;  
    }
    printf("\n");
    printf("Edge To:\n") ; 
    for(int i = 0 ; i <  graph->numVertices ; i++ )  {  
        if(mst->edgeTo[i] != -1 ) printf("%s ", graph->cityArr[mst->edgeTo[i]] ) ;
        else printf("- ");
        
    }
    
    free(mst ); 
    free(graph);
    
    return 0;
}

