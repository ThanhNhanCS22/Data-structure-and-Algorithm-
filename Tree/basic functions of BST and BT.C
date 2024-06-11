
#include <stdio.h>
#include<stdbool.h>
#include<stdlib.h> 
#define MAX_SIZE  1000 
struct Node{ 
    int data ; 
    struct Node * left ; 
    struct Node * right; 
    
    
};
struct stack{
    int size ;
    int top; 
    struct Node *arr[MAX_SIZE] ; 
};

struct stack * createStack() {
    struct stack * newStack = malloc(sizeof(struct stack) ) ; 
    newStack -> size = MAX_SIZE ; 
    newStack-> top = -1 ; 
} 
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
void push(struct stack * ptr, struct Node * node ) {
    if(isFull(ptr)){
        printf("Stack is Overflow!!!\n") ; 
    }
    else  ptr->arr[++(ptr->top)] = node  ;
    
}

struct Node* pop (struct stack* ptr){
    
    if (isEmpty(ptr) ) {
        printf("Stack is Underflow!!!\n") ; 
        return NULL;  
        
    }
    else { 
        return ptr->arr[ptr->top--];  
    }
}

struct Node* createNode(int data){ 

    struct Node * newNode =malloc(sizeof(struct Node) ) ; 
    newNode ->data= data ;
    newNode ->left = newNode->right = NULL; 
    return newNode ; 
}


void preorderTraversal(struct Node* root )  {
    if(root== NULL) return ; 
    printf("%d", root ->data ); 
    preorderTraversal(root->left ); 
    preorderTraversal(root-> right); 
    
}
void postorderTraversal(struct Node* root )  {
    if(root== NULL) return ; 
 
    postorderTraversal(root->left ); 
    postorderTraversal(root-> right); 
    printf("%d", root ->data ); 
    
}
void inorderTraversal(struct Node* root )  {
    if(root== NULL) return ; 
 
    inorderTraversal(root->left ); 
    printf("%d", root ->data ); 
    inorderTraversal(root-> right); 
   
    
}

bool isBST(struct Node* root ){ 
    
    static struct Node* prev= NULL; 
    
    if(root != NULL) { 
    
        if(!isBST(root->left )) { 
            return 0 ; 
        }
        if(prev!= NULL && root->data <= prev ->data )   return 0 ; 
        
        prev = root ; 
        return isBST(root->right);  
        
        
    }
    
    else { 
        return 1 ; 
        
    }
    
    
}

int findMaxBST(struct Node * root ) { 
    if(root == NULL ) return -1; 
    if(root -> right == NULL ) { 
    
        return root -> data ; 
    } 
    return  findMaxBST(root->right ) ; 
    
    
} 



struct Node* search(struct Node* root, int key){ 
    if( root == NULL) return NULL; 
    if(root->data == key ) return root ; 
    else if (root ->data>key ) return  search(root->left,  key) ; 
    else if (root ->data<key ) return  search(root->right,  key) ;
    
}

void getMax(struct Node*root , int *max ){
    if(root == NULL) return ; 
    if (*max < root->data ) *max = root->data ;
    getMax(root->left,max) ; 
    getMax(root->right, max) ; 
    return ; 
} 


int findMaxBT(struct Node* root ){
    int max=  root ->data ; 
    
    getMax(root,&max ) ;
    return max ; 
} 


struct Node* searchIter(struct Node* root, int key ) {
    while(root != NULL ) {
        if(key == root-> data ) {
            return root; 
            
        } 
        else if(key < root->data ) {
            root =root ->left;  
        } 
        
        else  {
            root = root-> right ; 
        }
    }
    return NULL; 
}

struct Node* insert(struct Node* root, int key ) { 
    if( root == NULL )  return createNode(key);  
    struct Node* returnRoot = root ; 
    struct Node* prev; 
    while(root != NULL) {
        prev = root ; 
        if(key == root ->data ) {
            printf("invalid key!!!\n");  
            exit(1)  ; 
        } 
        else if (key < root->data ) {
            root = root -> left ; 
            
        } 
        else {
            root = root-> right ; 
            
        }
        
        
    }
     
    if (key< prev-> data){
        prev->left = createNode(key) ;
            
    } 
        else { 
            prev->right =  createNode(key) ;
        }
    
     
    return returnRoot ;  
    
}

int findHeightOfRootWithOutUsingRecursion( struct Node* root) {
    struct stack *treeStack = createStack() ; 
    
    struct Node* currNode = root ; 
    int height = 0 ; 
    int countNode = 0 ; 
    while(!isEmpty(treeStack)  || currNode != NULL ) {
        if(currNode){
            countNode++ ; 
            if(height< countNode) height = countNode ;  
            push(treeStack,currNode );  
            currNode  = currNode->left ; 
            
        } 
        else {
             
            currNode = pop(treeStack); 
            if(!currNode->right ) countNode--;  
            currNode = currNode -> right ; 
            
        }
        
    }
    free(treeStack);  
    return height -1 ; 
}

int countAllNodesWithoutRecursion(struct Node* root) {
    struct stack *treeStack = createStack() ; 
    
    struct Node* currNode = root ; 
    int count = 0 ; 
    while(!isEmpty(treeStack)  || currNode != NULL ) {
        if(currNode ){
            count ++ ; 
            push(treeStack,currNode );  
            currNode  = currNode->left ; 
            
        } 
        else {
            currNode = pop(treeStack)->right ; 
            
        }
        
    }
    free(treeStack);  
    return count ; 
}


struct Node* lowestCommonAncestor(struct Node* root, struct Node* p, struct Node* q ) {
    if(!(search(root, p-> data) && search(root,q->data))  )  {
        printf("No exist q or p or both!!!") ; 
        return NULL;   
    }
    if (root->data > p->data && root->data > q->data)
        return lowestCommonAncestor(root->left, p, q);
    else if (root->data < p->data && root->data < q->data) 
        return lowestCommonAncestor(root->right, p, q);
    else
        return root;
}
int main()
{
   struct Node* p ; 
   
   p = insert(p, 9); 
   p = insert (p,8); 
   p = insert(p,12) ; 
   p = insert(p,7); 
   p = insert(p,10) ;  
   p = insert(p,13); 
   p = insert(p,11);  
   
   
   printf("%d\n",p->data);
    preorderTraversal(p );
    printf("\n");
    postorderTraversal(p);
    printf("\n");
    inorderTraversal(p);
    
    printf("\n");
    int numNodes= countAllNodesWithoutRecursion(p); 
    printf("%d" , numNodes);  
    
    printf("\n");
    int heightOfRoot = findHeightOfRootWithOutUsingRecursion(p);
    printf("%d" , heightOfRoot) ;  
    // if(isBST(p))  printf ("\ntrue"); 
    // else printf("\nfalse");
    
    
    //int max = findMaxBST(p ) ; 
    //printf("\nmax value: %d", max) ; 
    
    
    // struct Node* p1= search(p, 4 ); 
    // printf("\n%d",p1->data );  
    
    // int max2 = findMaxBT(p); 
    // printf("\n%d",max2); 
    
    
    
    
    return 0;
}

