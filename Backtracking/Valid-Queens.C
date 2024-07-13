

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define Size 10

void findCorrectColumn(int **Board, int *col, int size, int row,  int *colArr, int *leftDiagArr, int * rightDiagArr){
    while(*col < size){
        if(!colArr[*col] && !leftDiagArr[row +  (*col)] &&  !rightDiagArr[row - (*col)+ size - 1 ]  ){
            
            Board[row][*col]  = 1 ; 
            colArr[*col] = 1 ; 
            leftDiagArr[row+(*col)] = 1 ; 
            rightDiagArr[row - (*col) + size - 1 ]  = 1 ; 
            return  ;   
        } 
        (*col)++ ; 
    }
    return ; 

}
int PutQueen(int **Board,int size,  int row, int *colArr, int *leftDiagArr, int * rightDiagArr) {
    if(row==size ) return 1 ; 
    int i = 0 ; 
    
    findCorrectColumn(Board, &i , size,row, colArr, leftDiagArr, rightDiagArr) ;
    
    if (i == size) return 0 ; 
    while( !PutQueen(Board,size, row + 1 , colArr, leftDiagArr, rightDiagArr) ) {
        
        Board[row][i]  = 0 ; 
        colArr[i] = 0 ; 
        leftDiagArr[row+i] = 0 ; 
        rightDiagArr[row - i + size - 1 ]  = 0 ;
        i++ ; 
        
        findCorrectColumn(Board, &i , size,row, colArr, leftDiagArr, rightDiagArr) ;
        
        if (i == size) return 0 ; 
    }
    return 1 ; 
     
} 
void ValidOfPuttingQueens( int **Board, int size ) { 
    
    int columnArr[size];  
    int leftDiagonalArr[size+size]; 
    int rightDiagonalArr[size+size];  
    
    memset(columnArr, 0, sizeof(int) * size ); 
    memset (leftDiagonalArr, 0 ,sizeof(int) * (size + size) ) ; 
    memset (rightDiagonalArr, 0 , sizeof(int) * (size + size) ) ; 
    
    PutQueen(Board,size, 0 , columnArr , leftDiagonalArr , rightDiagonalArr);  
}

int main()
{
   
    int **Board = malloc(Size*sizeof(int*) ); 
    
    for(int i = 0 ; i < Size ; i ++) {
        Board[i] = calloc(Size, sizeof(int) );   
    }
    
    ValidOfPuttingQueens( Board, Size )  ; 
    for(int i = 0 ; i < Size; i++) {
        for(int j = 0 ; j < Size; j++){
            printf("%d ",Board[i][j] );  
        }
        printf("\n") ; 
    } 
    

    return 0;
}
