#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#define MAX 100
#define MAX_HEAP_SIZE 100

typedef struct AdjcencyList{
    int vertex; 
    int distance ; 
    struct AdjcencyList* next ; 
    
}AdjcencyList ; 

typedef struct {
    int numVertices;
    AdjcencyList **adjcencyList ; 
    char**cityArr ; 
} Graph;

typedef struct {
   
    int *arr;
    int *posArr; 
    int size;
    int capacity;
} MinHeap;



typedef struct {

    int *edgeTo ; 
    int *distanceTo ; 
    
} Dijkstra ; 


Graph* createGraph(int vertices, char** cityArr) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->numVertices = vertices;
    graph->adjcencyList = malloc(sizeof(AdjcencyList*)*vertices ); 
    graph->cityArr= cityArr; 
    
    for(int i = 0 ; i < vertices ; i ++ ){
        graph->adjcencyList[i] = NULL; 
    }
    
    return graph;
}

AdjcencyList *createAdjcencyNode(int dest, int dist){
    
    AdjcencyList * newNode = malloc(sizeof(AdjcencyList)) ;
    newNode-> vertex = dest ; 
    newNode->distance = dist ;
    newNode->next = NULL ; 
    
    return newNode ; 
    
} 

void addEdgeAndDistance(Graph* graph, int src, int dest, int dist) {
    AdjcencyList *temp ; 
    if(!graph->adjcencyList[src]) {
        graph->adjcencyList[src] = createAdjcencyNode(dest,dist); 
        
    }
    else { 
        temp = graph->adjcencyList[src]; 
        
        while(temp->next !=NULL ) temp = temp->next; 
    
        temp-> next = createAdjcencyNode(dest,dist); 
    }
    
    if(!graph->adjcencyList[dest]) {
        graph->adjcencyList[dest] = createAdjcencyNode(src,dist); 
        
    }
    else {
        temp = graph->adjcencyList[dest]; 
        
        while(temp->next !=NULL ) temp = temp->next; 
    
        temp-> next = createAdjcencyNode(src,dist); 
    }
}


void printGraph(Graph* graph) {
    
        for (int j = 0; j < graph->numVertices; j++) {
            printf("%d: ",j); 
            AdjcencyList* temp = graph->adjcencyList[j]; 
            while(temp !=NULL) {
                printf("%d, ",temp->vertex) ; 
                temp = temp->next ; 
            } 
            printf("\n");
        }
        
    
}

MinHeap* createMinHeap(int capacity) {
    MinHeap* heap = (MinHeap*)malloc(sizeof(MinHeap));
    heap->arr = malloc(capacity * sizeof(int));
    heap->posArr = malloc(capacity * sizeof(int)); ; 
    heap->size = 0;
    heap->capacity = capacity;
    return heap;
}

void percolateUp(MinHeap* heap, int index,Dijkstra* dijkstra ) {
    int parent = (index - 1) / 2;
    int temp;
    
    while (index > 0 && dijkstra->distanceTo[heap->arr[parent]]  > dijkstra->distanceTo[heap->arr[index]]) {
        heap->posArr[heap->arr[parent]] =  index ;
        heap->posArr[heap->arr[index]] = parent ; 
        temp = heap->arr[parent];
        heap->arr[parent] = heap->arr[index];
        heap->arr[index] = temp;
    
        index = parent;
        parent = (index - 1) / 2;
    }
}

void percolateDown(MinHeap* heap, int index, Dijkstra *dijkstra) {
    int leftChild, rightChild, minChild, temp;
    while (1) {
        leftChild = 2 * index + 1;
        rightChild = 2 * index + 2;
        minChild = index;

        if (leftChild < heap->size 
        && dijkstra->distanceTo[heap->arr[leftChild] ]< dijkstra->distanceTo[ heap->arr[minChild] ] )
            minChild = leftChild;
        if (rightChild < heap->size 
        && dijkstra->distanceTo[heap->arr[rightChild]] < dijkstra->distanceTo[heap->arr[minChild]])
            minChild = rightChild;

        if (minChild != index) {
            
            heap->posArr[heap->arr[minChild]] =  index ;
            heap->posArr[heap->arr[index]] = minChild ; 
            
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

void push(MinHeap* heap, int value, Dijkstra* dijkstra ) {
    if (heap->size == heap->capacity) {
        printf("Heap Overflow\n");
        return;
    }
    heap->arr[heap->size++] = value;
    heap->posArr[value] = heap->size -1  ; 
    
    percolateUp(heap, heap->size - 1,dijkstra);
}

int pop(MinHeap* heap, Dijkstra* dijkstra ) {
    if (heap->size == 0) {
        printf("Heap Underflow\n");
        return -1;
    }
    int minVal = heap->arr[0];
    
    heap->arr[0] = heap->arr[((heap->size)--) - 1];
    heap-> posArr[heap->arr[0]]= 0 ;  
    percolateDown(heap, 0,dijkstra);
    return minVal;
}



Dijkstra* DijkstraToFindShortestPath(Graph *graph , int startVertex ) {
    Dijkstra * dijkstra = malloc(sizeof(Dijkstra)); 
    dijkstra->edgeTo = malloc(sizeof(int) *graph->numVertices); 
    dijkstra-> distanceTo= malloc(sizeof(int)* graph->numVertices) ; 
    int *visited = calloc(sizeof(int), graph->numVertices) ;  
     
    for(int i = 0 ; i < graph->numVertices ; i++) {
        dijkstra->distanceTo[i] =  INT_MAX ; 
        
    } 
    
    
    dijkstra->edgeTo[startVertex] = -1  ; 
    dijkstra->distanceTo[startVertex]= 0 ; 
    
    MinHeap *heap=  createMinHeap(graph->numVertices) ; 
    
    for(int i = 0 ; i < graph->numVertices; i++ ){ 
        push(heap, i , dijkstra) ; 
        
    }
    
    int currVisited ; 
    
    
    for (int j =0 ; j < graph->numVertices -1  ; j++ ){ 
        
        currVisited = pop(heap , dijkstra);  
        visited[currVisited] = 1 ; 
        AdjcencyList* temp = graph->adjcencyList[currVisited]; 
        while(temp!= NULL ){
            
            if( !visited[temp->vertex] 
                && temp->distance+ dijkstra->distanceTo[currVisited] < dijkstra->distanceTo[temp->vertex] ){      
                    
                dijkstra->distanceTo[temp->vertex] = temp->distance + dijkstra->distanceTo[currVisited]  ; 
                dijkstra->edgeTo[temp->vertex] =  currVisited ;  
                
                percolateUp(heap, heap->posArr[temp->vertex] , dijkstra )  ; 
                
                
            }
            temp = temp->next ; 
        }
    }
    free(heap->arr); 
    free(heap->posArr) ;
    free(heap); 
    
    free(visited); 
    return  dijkstra ; 
    
} 



int main() {
    int vertices = 12;  
    
    char* cityArr[12] = {"A","B","C","D","E","F","G","H","I","J","K","L"} ;
    Graph* graph = createGraph(vertices,cityArr); 
    addEdgeAndDistance(graph,0,1,20 ); 
    addEdgeAndDistance(graph,0,3,21);
    addEdgeAndDistance(graph,1,3,13);
    addEdgeAndDistance(graph,1,2,7); 
    addEdgeAndDistance(graph,1,4,5);
    
    addEdgeAndDistance(graph,2,4,1);
    addEdgeAndDistance(graph,3,4,10);
    addEdgeAndDistance(graph,3,5,14);
    addEdgeAndDistance(graph,4,5,22);
    addEdgeAndDistance(graph,4,6,15);
    
    addEdgeAndDistance(graph,4,7,6);
    addEdgeAndDistance(graph,5,6,4); 
    addEdgeAndDistance(graph,6,7,11); 
    addEdgeAndDistance(graph,6,8,3);
    
    addEdgeAndDistance(graph,6,9,19);
    addEdgeAndDistance(graph,7,8,2); 
    addEdgeAndDistance(graph,7,10,8); 
    addEdgeAndDistance(graph,7,11,9); 
    addEdgeAndDistance(graph,8,9,18);
    addEdgeAndDistance(graph,8,10,12); 
    
    addEdgeAndDistance(graph,9,10,17); 
    addEdgeAndDistance(graph,10,11,16); 
    
    printGraph(graph);  
    Dijkstra *dijkstra = DijkstraToFindShortestPath(graph, 10); 
    
    printf("Cities:\n") ;
    for(int i = 0 ; i <  graph->numVertices ; i++ )  {  
        printf("%s ", graph->cityArr[i] ) ;  
    }
    
    printf("\n");
    printf("Edge To:\n") ; 
    for(int i = 0 ; i <  graph->numVertices ; i++ )  {  
        if(dijkstra->edgeTo[i] != -1 ) printf("%s ", graph->cityArr[dijkstra->edgeTo[i]] ) ;
        else printf("- ");
        
    }
    
    free(dijkstra); 
    free(graph);
    
    return 0;
}

