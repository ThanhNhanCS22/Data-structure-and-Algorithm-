
#include <stdio.h>
#include <stdlib.h>


typedef struct HashNode { 
    int key ; 
    struct HashNode *next ; 
    
    
} HashNode ; 

typedef struct  {
    int hashSize ; 
    HashNode ** hashTable ; 
    
}HashTable ; 



HashNode * createHashNode(int value ) {
    HashNode *newNode = malloc(sizeof(HashNode) ) ; 
    newNode ->key = value ; 
    newNode-> next = NULL; 
    return newNode ; 
    
}
HashTable * createHashTable(){
    
     
    HashTable * newTable = malloc(sizeof(HashTable) ) ; 
    printf("Let's enter the size of hash table: "); 
    scanf("%d",&(newTable-> hashSize)); 
    newTable->hashTable = malloc(newTable->hashSize*sizeof(HashNode*) ) ; 
    
    return newTable ; 
    
} 
void insert(HashTable* table, int value) { 
    
    int entry = value%(table->hashSize) ; 
    HashNode * tempNode = table->hashTable[entry]; 
    if(tempNode == NULL ){
        table->hashTable[entry] = createHashNode(value); 
    } 
    else {
        while(tempNode -> next != NULL ) tempNode = tempNode ->next ;  
        tempNode->next = createHashNode(value ); 
        
        
    }
    
}

HashNode *search(HashTable* table, int value) {
    int entry = value%(table->hashSize) ;   
    HashNode* tempNode = table->hashTable[entry]; 
    
    while( tempNode != NULL ){
        if(tempNode ->key == value) return tempNode ; 
        tempNode= tempNode->next ; 
    }
    return NULL; 
}

void delete(HashTable* table, int value) {
    int entry = value%(table->hashSize) ; 
    HashNode* currNode = table->hashTable[entry];  
    
    while (currNode != NULL && currNode->key == value ){
        table->hashTable[entry] = table->hashTable[entry]->next;  
        free(currNode);  
        currNode = table->hashTable[entry];  
        
    } 
    
    
    if(currNode!= NULL) currNode = currNode->next ; 
    HashNode* prevNode = currNode;  
    
    
    while( currNode != NULL ){
        if(currNode ->key == value) {
            
            prevNode->next=currNode->next; 
            free(currNode);  
            currNode = prevNode->next ;  
        }
        else { 
            prevNode = currNode ; 
            currNode = currNode->next ; 
    
        }    
    }
}

void printTable(HashTable * table){
    HashNode *tempNode ; 
    for(int i = 0 ; i < table->hashSize ; i++) { 
        tempNode = table->hashTable[i] ; 
        printf("%d: ",i) ;  
        while(tempNode!= NULL) {
            printf("%d->",tempNode->key) ; 
            tempNode =tempNode->next ; 
            
        } 
        printf("NULL\n") ; 
        
    }
    
} 


int main()
{
    HashTable * table = createHashTable();  
    insert(table, 8)  ; 
    insert(table, 6)  ;
    insert(table, 5)  ;
    insert(table, 1)  ; 
    insert(table, 88) ; 
    // delete( table, 8) ;
    // delete(table, 89 ) ; 
    printTable(table); 
    if(search(table, 9 )  ) printf("True")   ;
    else printf("false") ; 
    return 0;
}
