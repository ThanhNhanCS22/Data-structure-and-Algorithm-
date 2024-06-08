#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 100


typedef struct Graph {
    int numVertices;
    int adjMatrix[MAX][MAX];  
    char**cityArr ; 
} Graph;


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


void addEdge(Graph* graph, int src, int dest) {
    graph->adjMatrix[src][dest] = 1;  
    graph->adjMatrix[dest][src] = 1;  
}


void printGraph(Graph* graph) {
    for (int i = 0; i < graph->numVertices; i++) {
        for (int j = 0; j < graph->numVertices; j++) {
            printf("%d ", graph->adjMatrix[i][j]);
        }
        printf("\n");
    }
}


typedef struct {
    int size ; 
    int front ; 
    int rear ; 
    int * arr ; 
}Queue ;

Queue *createQueue() {
    Queue* newQueue = malloc(sizeof(Queue)) ; 
    newQueue->size = MAX ; 
    newQueue->front = -1 ; 
    newQueue->rear = -1 ; 
    newQueue->arr = malloc(sizeof(int) * newQueue->size); 
    
}

bool isFull( Queue *q ){
    if(q->rear == q->size-1 )  return 1 ; 
    return  0; 
    
} 
   
bool isEmpty( Queue* q) {
    if(q->rear == q->front ) return 1 ; 
    return 0 ; 
}



void enqueue( Queue *q, int val  ){
    if(isFull(q) ) {
        printf("This queue is full!!!\n"); 
        exit(1) ; 
        
    } 
    else {
        q->arr[++(q->rear)] = val  ; 
    }
} 

int dequeue( Queue *q ){
    
    if(isEmpty(q) ) {
        printf("This queue is empty!!!\n"); 
        exit(1); 
        
    } 
    else {
        return q->arr[++ (q->front )] ; 
    }
} 



void BFS(Graph* graph, int startVertex) {
    int *visited = calloc(MAX,sizeof(int) )  ;  
    Queue* queue = createQueue();

    visited[startVertex] = 1;  
    enqueue(queue, startVertex);
    int countVisited=0 ;
    while (!isEmpty(queue)) {
        int currentVertex = dequeue(queue);
        
        countVisited++ ;
        
        printf("%s", graph->cityArr[currentVertex]);
        if(countVisited < graph->numVertices) {
            printf(" - ") ;  
        }

        
        for (int i = 0; i < graph->numVertices; i++) {
            if (graph->adjMatrix[currentVertex][i] == 1 && !visited[i]) {
                
                visited[i] = 1;
                enqueue(queue, i);
                
            }
        }
    }
    free(visited);  
    free(queue);  
    printf("\n");
}

void DFSoperation(Graph* graph, int startVertex, int* visited ) {
    static int count = 0 ; 
    count++  ;
    printf("%s", graph->cityArr[startVertex]) ;
    if(count < graph->numVertices) {
            printf(" - ") ;  
        }
    visited[startVertex]  = 1 ; 
    
    for(int i  = 0 ; i < graph->numVertices ; i++ ) {
        if(graph ->adjMatrix[startVertex][i] == 1 && !visited[i]){
            DFSoperation(graph,i,visited) ;
        }
    }
}

void DFS(Graph * graph, int startVertex) { 

    int *visited = calloc(MAX,sizeof(int) )  ; 
    DFSoperation(graph, startVertex,visited)  ; 
    
    free(visited); 
    printf("\n") ; 
}





int main() {
    int vertices = 6;  
    
    char* cityArr[6] = {"Tp HCM","Binh Duong","Vung Tau","Binh Phuoc","Phan Thiet","Khanh Hoa"} ;
    Graph* graph = createGraph(vertices,cityArr);
    addEdge(graph, 0, 1);
    addEdge(graph, 0, 2);
    addEdge(graph, 1, 2);
    addEdge(graph, 1, 3);
    addEdge(graph, 2, 4);
    addEdge(graph, 3, 4);
    addEdge(graph, 3, 5);

    printf("Adjacency matrix of the graph:\n");
    printGraph(graph);

    printf("BFS traversal starting from vertex 0:\n");
    BFS(graph, 0);

    printf("DFS traversal starting from vertex 0:\n");
    DFS(graph,0); 
    
    free(graph);
    
    return 0;
}
