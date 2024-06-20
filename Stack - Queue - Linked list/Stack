
#include <stdio.h>
#include <stdlib.h>
#include<stdbool.h>
struct stack{
    int size ;
    int top; 
    int *arr ; 
};

bool isEmpty(struct stack* ptr ){
    if (ptr->top == -1 ) {
        return 1; 
    }
    return 0; 
    
} 
bool isFull(struct stack* ptr ){
    if (ptr-> top == ptr->size -1 ) {
        return 1; 
    }
    return 0; 
    
} 
void push(struct stack * ptr, int val) {
    if(isFull(ptr)){
        printf("Stack is Overflow!!!\n") ; 
    }
    else  ptr->arr[++(ptr->top)] = val ;
    
}

int pop (struct stack* ptr){
    
    if (isEmpty(ptr) ) {
        printf("Stack is Underflow!!!\n") ; 
        return -1 ; 
        
    }
    else { 
        return ptr->arr[ptr->top--];  
    }
}

int main()
{
    /*struct stack s ; 
    s.size = 80 ; 
    s.top = -1 ;    
    S.arr = malloc(s.size*sizeof(int)) ; */
    
    
    struct stack *s = malloc(sizeof(struct stack)); 
    s->size = 80 ; 
    s->top = -1 ;    
    s->arr = malloc(s->size*sizeof(int)) ;
    s->arr[0]= 8 ; 
    s->top++ ;
    push(s,88); 
    push(s, 100 );  
    printf("top: %d\nvalue at top: %d\n", s->top,s->arr[s->top] );  
    
    
    //if (isEmpty(s)) printf("this stack is empty") ; 
    //else printf("this stack is not empty") ;
    
    printf("value after popping: %d\n",pop(s) ); 
    printf("top after popping: %d",s->top);  
    
    
     return 0;
}


