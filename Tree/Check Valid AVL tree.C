
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
struct TreeNode {
    int data; 
    struct TreeNode* left; 
    struct TreeNode* right; 
    
    
} ; 


struct TreeNode* createNode(int data ) {
    struct TreeNode* newNode =malloc(sizeof(struct TreeNode)) ;  
    newNode->data = data ; 
    newNode-> left =  newNode-> right = NULL; 
    return newNode; 
        
} 



void checkHeight(int level, int * height, struct TreeNode* root ) {
    if(root == NULL) return; 
    if (*height < level   ) *height = level ;   
    checkHeight(level + 1 , height, root->left ) ; 
    checkHeight(level + 1 , height, root->right ) ; 
}  


void  checkValidAVLTree(struct TreeNode* root, int *checkVar ) { 
    if (*checkVar == 0) return ; 
    if(root == NULL ) return ; 
    int leftHeight = 0 ; 
    int rightHeight = 0 ; 
    checkHeight(1, &leftHeight, root->left  ); 
    checkHeight(1, &rightHeight, root->right  ); 
    if (abs(leftHeight - rightHeight ) > 1 ){
       *checkVar = 0 ;  
       return ; 
    }   
    checkValidAVLTree(root-> left, checkVar )  ; 
    checkValidAVLTree(root-> right, checkVar )  ; 
}


bool validAVLTree(struct TreeNode* root ){
    int checkVar = 1 ; 
    checkValidAVLTree(root, &checkVar ) ; 
    return checkVar ; 
}


int main()
{
    struct TreeNode *root = createNode(5) ; 
  
    root->left = createNode(3) ; 
    root->left->left = createNode(3) ; 
    root->right = createNode(3); 
    root->right->left  = createNode(3); 
    root->right->right  = createNode(3); 
    root->right->right->left = createNode(3); 
    
    if( validAVLTree(root )) {
        
        printf("this is valid AVL tree") ; 
        
    } 
    else{
        printf("not valid") ; 
    }
    
    return 0;
}
