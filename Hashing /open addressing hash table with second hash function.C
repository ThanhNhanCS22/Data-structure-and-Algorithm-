#include <stdio.h>
#include <stdlib.h> 
typedef struct {
    int size ; 
    int *arr ; 
    int *checkArr ; 
} HashTable ; 



HashTable* initializeHashTable(){
    HashTable * newTable= malloc(sizeof(HashTable)) ;  
    printf("Let's input the size of hash table: "); 
    scanf("%d",&(newTable ->size) ); 
    newTable-> arr = malloc(newTable-> size* sizeof(int) )  ; 
    newTable-> checkArr = calloc(newTable->size, sizeof(int) ) ; 
    return newTable ; 
}  

void insert(HashTable* table, int value) {
    int firstHashFunction = value%(table->size) ;
    int secondHashFunction= 7-(value %7 ) ;  
    int entry; 
    for(int i = 0 ; i <table->size;i++) {
        entry = (firstHashFunction + i* secondHashFunction) % (table->size) ;  
        if(!table->checkArr[entry]){
            table->arr[entry] = value ; 
            table->checkArr[entry] = 1; 
            return ; 
        } 
    }
    printf("Cannot insert value!!!"); 
    
}

void printTable(HashTable * table ) {
    for(int i = 0 ; i < table->size ; i++) { 
        printf("%d: ",i);  
        if(table->checkArr[i]) {
            printf("%d",table->arr[i] );  
        } 
        printf("\n") ;  
        
    }
} 

void lazyDelete(HashTable * table, int value ){
    int firstHashFunction = value%(table->size); 
    int secondHashFunction= 7-(value %7 ) ;  
    int entry  = firstHashFunction; 
    while(table->checkArr[entry] ) { 
        int i = 0 ; 
        if(table->arr[entry]!= value) {
            entry = (firstHashFunction + (++i)*secondHashFunction  )%(table->size) ; 
            
        }
        else {
            table->checkArr[entry] = 0 ; 
            return; 
        }
        
        if(i == table->size-1  ) return;  
    }
}
int main()
{  
    HashTable* table= initializeHashTable() ; 
    insert(table, 8);  
    insert(table, 88); 
    insert(table, 1); 
    insert(table, 2);
    insert(table, 5); 
    lazyDelete(table, 8 ); 
   
    
    
    
    printTable(table );  
    
    
    
    return 0;
}
