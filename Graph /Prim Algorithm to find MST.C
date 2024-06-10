#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
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



typedef struct {

    int *edgeTo ; 
    int *distanceTo ; 
    
} MST ; 



MST * basicPrimAlgorithmForMST(Graph *graph , int startVertex ) {
    MST *newMST = malloc(sizeof(MST)); 
    newMST->edgeTo = malloc(sizeof(int) *graph->numVertices); 
    newMST-> distanceTo= malloc(sizeof(int)* graph->numVertices) ; 
     
    for(int i = 0 ; i < graph->numVertices ; i++) {
        newMST->distanceTo[i] =  INT_MAX ; 
        
    } 
    newMST->edgeTo[startVertex] = -1 ; 
    
    int countEdges = 0 ;
    
    int currVisited = startVertex ; 
    
    while(countEdges < graph->numVertices ){ 
        
        newMST->distanceTo[currVisited] = 0 ; 
        for(int i = 0 ; i < graph->numVertices; i++) {
            if(graph->adjMatrix[currVisited][i] 
                && graph->adjMatrix[currVisited][i]<newMST->distanceTo[i] ){
                    
                newMST->distanceTo[i] = graph->adjMatrix[currVisited][i]  ; 
                newMST->edgeTo[i] = currVisited ;  
            }
        }
        
        int minDist = INT_MAX ; 
        
        for (int i = 0 ; i < graph->numVertices ; i++){
            if(newMST->distanceTo[i]  &&  minDist > newMST->distanceTo[i] ) {
                minDist = newMST->distanceTo[i];
                currVisited = i ; 
            }    
        } 
        
        countEdges++ ; 
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
    MST* mst= basicPrimAlgorithmForMST(graph,0);  
    
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

