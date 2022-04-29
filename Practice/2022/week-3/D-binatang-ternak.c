/**
 * fundamental code written by : ABDUR ROCHMAN
 * @date 2020-03-28
 * 
 * @editor Daud Dhiya' Rozaan
 * @date 2022-04-18
 */

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

typedef struct AVLNode_t{
    int data, height;
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

AVLNode* _search(AVLNode *root, int value) {
    while (root != NULL) {
        if (value < root->data) root = root->left;
        else if (value > root->data) root = root->right;
        else return root;
    }
    return root;
}

bool avl_find(AVL *avl, int value) {
    AVLNode *temp = _search(avl->_root, value);
    if (temp == NULL) return false;
    
    if (temp->data == value) return true;
    else return false;
}

int _getHeight(AVLNode* node){
    if(node==NULL) return 0; 
    return node->height;
}

int _getBalanceFactor(AVLNode* node){
    if(node==NULL) return 0;
    return _getHeight(node->left)-_getHeight(node->right);
}

int _max(int a,int b){
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

AVLNode* _avl_createNode(int value) {
    AVLNode *newNode = (AVLNode*) malloc(sizeof(AVLNode));
    newNode->data = value;
    newNode->height=1;
    newNode->left = newNode->right = NULL;
    return newNode;
}

AVLNode* _insert_AVL(AVL *avl,AVLNode* node,int value) {
    if(node==NULL) // udah mencapai leaf
        return _avl_createNode(value);
    if(value < node->data)
        node->left = _insert_AVL(avl,node->left,value);
    else if(value > node->data)
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

void avl_insert(AVL *avl,int value){
    if(!avl_find(avl,value)){
        avl->_root=_insert_AVL(avl,avl->_root,value);
        avl->_size++;
    }
}

/**
 * searchParent function is function to determine the parent of a node, 
 * return the parent->data as int data-type
 */
int searchParent(AVL *avl, int value){
    if(!avl_find(avl, value)) return (0); // if test (a.k.a value) is not found, return 0
    if(avl->_root->data == value) return (0); // if test (a.k.a value) equal to root->data, return 0

    AVLNode *temp = avl->_root;
    while(temp != NULL) {
        if(temp->right != NULL && temp->right->data == value){
            return temp->data; break;
        }
        else if(temp->left != NULL && temp->left->data == value){
            return temp->data; break;
        }

        if(value > temp->data)
            temp = temp->right;
        else if(value < temp->data)
            temp = temp->left;
    }
    return 0;
}

/**
 * searchSibling function is function to determine the sibling of a node,
 * (in this problem, it's used to determine the sibling of a parent's node), 
 * return the sibling->data as int data-type
 */
int searchSibling(AVL *avl, int value){
    if(!avl_find(avl, value)) return (0); // if parent (a.k.a value) is not found, return 0
    if(avl->_root->data == value) return (0); // if parent (a.k.a value) equal to root->data, return 0
    AVLNode *temp = avl->_root;
    while(temp != NULL) {
        if(temp->right != NULL && temp->right->data == value){
            if(temp->left != NULL) return temp->left->data;
            else return 0;
            break;
        }
        else if(temp->left != NULL && temp->left->data == value){
            if(temp->right != NULL) return temp->right->data;
            else return 0;
            break;
        }

        if(value > temp->data)
            temp = temp->right;
        else if(value < temp->data)
            temp = temp->left;
    }
    return 0;
}


int main(){
    AVL avlku;
    avl_init(&avlku);
    int n, t, nilai, test;
    scanf("%d%d", &n, &t);
    while(n--){
        scanf("%d", &nilai);
        avl_insert(&avlku, nilai);
    }
    while(t--){
        scanf("%d", &test);

        /* search the parent of "test" */
        int parent = searchParent(&avlku, test);

        /* search the sibling of "parent" */
        int sibling = searchSibling(&avlku, parent);

        int hasil = sibling - parent; // result formula = sibling(data) - parent(data)
        if(hasil<0) hasil *= -1; // if result is smaller than 0, multiply by -1
        printf("%d\n", hasil);
    }
    return 0;
}