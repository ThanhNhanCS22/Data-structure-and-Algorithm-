
#include <stdio.h>
#include <stdlib.h> 

int max(int a , int b) { 

    return a>b ? a : b ; 

    
}
struct TreeNode { 
    int data ; 
    struct TreeNode *left; 
    struct TreeNode *right; 
    int height ; 
    
};


int getHeight(struct TreeNode* root ) { 
    if(root == NULL ) return  0 ; 
    
    return root->height ;
    
}

struct TreeNode* createNode(int data) {
    struct TreeNode * newNode = malloc(sizeof(struct TreeNode)) ;
    newNode-> data = data ; 
    newNode -> left = NULL ;
    newNode ->right = NULL ;
    newNode-> height = 1 ; 
    return newNode ; 
}


int getBalanceFactor(struct TreeNode* root) { 
    
    if(root == NULL) return 0 ; 
    return getHeight(root->left) - getHeight(root->right)    ;
    
}



struct TreeNode * singleLeftRotate(struct TreeNode* x ) { 
    struct TreeNode* y = x-> right ; 
    struct TreeNode* T2  = y -> left ; 
    
    y->left = x ; 
    x->right = T2 ; 
    
    x->height= max(getHeight(x->right), getHeight(x->left)  ) + 1 ;  
    y->height= max(getHeight(y->right), getHeight(y->left)  ) + 1 ;  
     
    
    return y ; 
}



struct TreeNode * singleRightRotate(struct TreeNode* y ) { 
    
    struct TreeNode * x = y-> left; 
    struct TreeNode * T2 = x->right; 
    
    x->right = y ; 
    y->left = T2 ; 
    
    
    y->height= max(getHeight(y->right), getHeight(y->left)  ) + 1 ;  
    x->height= max(getHeight(x->right), getHeight(x->left)  ) + 1 ;  
    
    return x ; 
} 

struct TreeNode* doubleLeftRightRotate(struct TreeNode* node) {
    node->left = singleLeftRotate(node->left);
    return singleRightRotate(node);
}

// Function to perform double rotation - first right then left
struct TreeNode* doubleRightLeftRotate(struct TreeNode* node) {
    node->right = singleRightRotate(node->right);
    return singleLeftRotate(node);
}


struct TreeNode* insert (struct TreeNode * root, int data ) { 
    if(root == NULL) return createNode(data); 
    
    if(data < root -> data) root->left= insert(root-> left, data ); 
    
    else if (data> root->data ) root ->right = insert(root->right, data);   
    
    else return root ; // dupdicated values are not allwed !!! 
    
    root-> height = 1 + max(getHeight(root->right), getHeight(root->left)  )  ; 
    int bf = getBalanceFactor(root); 
    
    
    // left left case  
    if (bf > 1 && data < root->left-> data ){
        return singleRightRotate(root);  
    } 
    
    
    //right right case
    else if(bf < -1 && data > root-> right -> data) {
        return singleLeftRotate(root);  
        
    } 
    //left right case 
    else if(bf >1  && data > root-> left -> data) {
        return doubleLeftRightRotate(root); 
        
    } 
    
    //right left case 
    
    else if (bf < -1 && data <root ->right ->data ) {
        return  doubleRightLeftRotate(root);
        
    }
    return root ; 
}


struct TreeNode* createEmptyAVLTree() {
    return NULL; 
} 

int main()
{
    struct TreeNode *root= createEmptyAVLTree() ; 
    root = insert(root, 45) ; 
    root = insert(root, 46) ; 
    root = insert(root, 47) ; 
    root = insert(root, 50) ; 
    root = insert(root, 48) ; 
    
    printf("%d",root->data) ;  
    
    
    

    return 0;
}
