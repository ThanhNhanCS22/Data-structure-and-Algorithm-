
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
    int entry = value%(table->size) ; 
    int otherEntry ; 
    for(int i = 0 ; i <table->size;i++) {
        otherEntry = (entry + i ) % (table->size) ;  
        if(!table->checkArr[otherEntry]){
            table->arr[otherEntry] = value ; 
            table->checkArr[otherEntry] = 1; 
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

void realDelete(HashTable * table, int value ){
    int entry = value%(table->size); 
    int otherEntry = entry  ; 
    while(table->checkArr[otherEntry] ) { 
        
        if(table->arr[otherEntry]!= value) {
            otherEntry = (++entry)%(table->size) ; 
            
        }
        else break ; 
        
        if(otherEntry == value%(table->size) ) return;  
        
        
    }
    if( table->checkArr[otherEntry]  ){  
        while(table->checkArr[(++entry)%( table->size)] ){ 
             
                if(otherEntry>= ( table->arr[(entry)%( table->size) ] ) %(table ->size) 
                ||( table->arr[(entry)%( table->size) ] ) %(table ->size) > (entry)%( table->size) ) 
                { 
                    table->arr[otherEntry] = table->arr[entry%(table->size)] ; 
                    otherEntry= entry%(table->size) ; 
                    
                }
        }
    }
    else return;  
    table->checkArr[otherEntry] = 0 ; 
    

     
}
int main()
{  
    HashTable* table= initializeHashTable() ; 
    insert(table, 8);  
    insert(table, 88); 
    insert(table, 1); 
    insert(table, 2);
    insert(table, 5); 
    insert (table, 7 ); 
    insert (table, 17 ); 
    insert(table, 27 ) ;
   
    insert(table,9)  ; 
    
    realDelete(table,8);   
    
    
    
    printTable(table );  
    
    
    
    return 0;
}

