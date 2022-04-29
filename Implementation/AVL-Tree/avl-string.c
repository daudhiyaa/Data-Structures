/**
 * @author ABDUR ROCHMAN
 * @date 2020-03-28
 * 
 * AVL-Tree Implementation
 * -- with unique data in string data-type
 * For C
 * 
 * @editor Daud Dhiya' Rozaan
 * @date 2022-04-23
 * 
 * !! NOTE !!
 * see how it is used in the main() function
 */

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#define ll long long
#define MAX 100

typedef struct AVLNode_t{
    char data[MAX];
    int height;
    struct AVLNode_t *left,*right;
}AVLNode;

typedef struct AVL_t{
    AVLNode *_root;
    unsigned int _size;
}AVL;

void avl_init(AVL *avl) {
    avl->_root = NULL;
    avl->_size = 0u;
}

bool avl_isEmpty(AVL *avl) {
    return avl->_root == NULL;
}

AVLNode* _search(AVLNode *root, char value[]) {
    while (root != NULL) {
        if (strcmp(value, root->data) < 0) root = root->left;
        else if (strcmp(value, root->data) > 0) root = root->right;
        else return root;
    }
    return root;
}

bool avl_find(AVL *avl, char value[]) {
    AVLNode *temp = _search(avl->_root, value);
    if (temp == NULL) return false;
    
    if (strcmp(value, temp->data) == 0) return true;
    else return false;
}

/* uses of "another_avl_find" function is like "avl_find" but without using "_search" function */
bool another_avl_find(AVL *avl, char value[]) {
    AVLNode *temp = avl->_root;
    while (temp != NULL) {
        if (strcmp(value, temp->data) < 0)
            temp = temp->left;
        else if (strcmp(value, temp->data) > 0)
            temp = temp->right;
        else if (strcmp(value, temp->data) == 0) return true;
    }
    return false;
}

int _getHeight(AVLNode* node){
    if(node==NULL) return 0; 
    return node->height;
}

int _getBalanceFactor(AVLNode* node){
    if(node==NULL) return 0;
    return _getHeight(node->left)-_getHeight(node->right);
}

int _max(int a, int b){
    return (a > b)? a : b;
}

AVLNode* _rightRotate(AVLNode* pivotNode) {
    AVLNode* newParrent=pivotNode->left;
    pivotNode->left=newParrent->right;
    newParrent->right=pivotNode;

    pivotNode->height=_max(_getHeight(pivotNode->left),
                      _getHeight(pivotNode->right))+1;
    newParrent->height=_max(_getHeight(newParrent->left),
                       _getHeight(newParrent->right))+1;
    
    return newParrent;
}

AVLNode* _leftRotate(AVLNode* pivotNode) {
    AVLNode* newParrent=pivotNode->right;
    pivotNode->right=newParrent->left;
    newParrent->left=pivotNode;

    pivotNode->height=_max(_getHeight(pivotNode->left),
                      _getHeight(pivotNode->right))+1;
    newParrent->height=_max(_getHeight(newParrent->left),
                       _getHeight(newParrent->right))+1;
    
    return newParrent;
}

AVLNode* _leftCaseRotate(AVLNode* node){
    return _rightRotate(node);
}

AVLNode* _rightCaseRotate(AVLNode* node){
    return _leftRotate(node);
}

AVLNode* _leftRightCaseRotate(AVLNode* node){
    node->left=_leftRotate(node->left);
    return _rightRotate(node);
}

AVLNode* _rightLeftCaseRotate(AVLNode* node){
    node->right=_rightRotate(node->right);
    return _leftRotate(node);
}

AVLNode* _avl_createNode(char value[]) {
    AVLNode *newNode = (AVLNode*) malloc(sizeof(AVLNode));
    strcpy(newNode->data, value);
    newNode->height=1;
    newNode->left = newNode->right = NULL;
    return newNode;
}

AVLNode* _insert_AVL(AVL *avl,AVLNode* node, char value[]) {
    if(node==NULL) // leaf
        return _avl_createNode(value);

    if(strcmp(value, node->data)<0)
        node->left = _insert_AVL(avl,node->left,value);
    else if(strcmp(value, node->data)>0)
    	node->right = _insert_AVL(avl,node->right,value);
    
    node->height= 1 + _max(_getHeight(node->left),_getHeight(node->right)); 

    int balanceFactor=_getBalanceFactor(node);
    
    if(balanceFactor > 1 && value < node->left->data) // skewed kiri (left-left case)
        return _leftCaseRotate(node);
    if(balanceFactor > 1 && value > node->left->data) 
		return _leftRightCaseRotate(node);
    if(balanceFactor < -1 && value > node->right->data)
        return _rightCaseRotate(node);
    if(balanceFactor < -1 && value < node->right->data)
        return _rightLeftCaseRotate(node);
    
    return node;
}

void avl_insert(AVL *avl, char value[]){
    if(!avl_find(avl,value)){
        avl->_root=_insert_AVL(avl,avl->_root,value);
        avl->_size++;
    }
}

AVLNode* _findMinNode(AVLNode *node) {
    AVLNode *currNode = node;
    while (currNode && currNode->left != NULL)
        currNode = currNode->left;
    return currNode;
}

AVLNode* _remove_AVL(AVLNode* node,int value){
    if(node==NULL)
        return node;

    if(strcmp(value, node->data)>0)
    	node->right=_remove_AVL(node->right,value);
    else if(strcmp(value, node->data)<0)
    	node->left=_remove_AVL(node->left,value);
    else{
        AVLNode *temp;
        if(node->left==NULL || node->right==NULL){
            temp = NULL;
            if(node->left == NULL) temp = node->right;  
            else if(node->right == NULL) temp=node->left;
            
            if(temp == NULL){
                temp=node;
                node=NULL;
            }
            else *node=*temp;   
            
            free(temp);
        }
        else{
            temp = _findMinNode(node->right);
            strcpy(node->data,temp->data);
            node->right=_remove_AVL(node->right,temp->data);
        }    
    }

	if(node==NULL) return node;
    
    node->height=_max(_getHeight(node->left),_getHeight(node->right))+1;

    int balanceFactor= _getBalanceFactor(node);
    
    if(balanceFactor>1 && _getBalanceFactor(node->left)>=0) 
        return _leftCaseRotate(node);

    if(balanceFactor>1 && _getBalanceFactor(node->left)<0) 
        return _leftRightCaseRotate(node);
  
    if(balanceFactor < -1 && _getBalanceFactor(node->right)<=0) 
        return _rightCaseRotate(node);

    if(balanceFactor < -1 && _getBalanceFactor(node->right)>0) 
        return _rightLeftCaseRotate(node);
    
    return node;
}

void avl_remove(AVL *avl, char value[]){
    if(avl_find(avl,value)){
        avl->_root=_remove_AVL(avl->_root,value);
        avl->_size--;
    }
}

void avl_postorder(AVLNode *root) {
    if (root) {
        avl_postorder(root->left);
        avl_postorder(root->right);
        printf("%s\n", root->data);
    }
}

void avl_inorder(AVLNode *root) {
    if (root) {
        avl_inorder(root->left);
        printf("%s\n", root->data);
        avl_inorder(root->right);
    }
}

void avl_preorder(AVLNode *root) {
    if (root) {
        printf("%s\n", root->data);
        avl_preorder(root->left);
        avl_preorder(root->right);
    }
}

int main(){
    AVL avlku;
    avl_init(&avlku);
    
    int n;
    scanf("%d", &n);
    char str[MAX];
    for(int i=0;i<n;i++){
        scanf("%[^\n]s", str);
        avl_insert(&avlku, str);
    }
    avl_inorder(avlku._root);
}