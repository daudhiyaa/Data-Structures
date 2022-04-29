/**
 * fundamental code written by : ABDUR ROCHMAN
 * @date 2020-03-28
 * 
 * @editor Keyisa Raihan & Daud Dhiya' Rozaan
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

int _getHeight(AVLNode* node){
    if(node==NULL)
        return 0; 
    return node->height;
}

int _max(int a,int b){
    return (a > b)? a : b;
}

AVLNode* _avl_createNode(int value) {
    AVLNode *newNode = (AVLNode*) malloc(sizeof(AVLNode));
    newNode->data = value;
    newNode->height=1;
    newNode->left = newNode->right = NULL;
    return newNode;
}

AVLNode* _search(AVLNode *root, int value) {
    while (root != NULL) {
        if (value < root->data)
            root = root->left;
        else if (value > root->data)
            root = root->right;
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

int _getBalanceFactor(AVLNode* node){
    if(node==NULL)
        return 0;
    return _getHeight(node->left)-_getHeight(node->right);
}

AVLNode* _insert_AVL(AVL *avl,AVLNode* node,int value) {
    
    if(node==NULL)
        return _avl_createNode(value);
    if(value < node->data)
        node->left = _insert_AVL(avl,node->left,value);
    else if(value > node->data)
        node->right = _insert_AVL(avl,node->right,value);
    
    node->height= 1 + _max(_getHeight(node->left),_getHeight(node->right)); 

    int balanceFactor=_getBalanceFactor(node);
    
    if(balanceFactor > 1 && value < node->left->data)
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
 * !! GENERAL EXPLANATION !!
 * in this problem, I use nested travers.
 * every time doing distance calculation, 2 node parameters are used, root and pivotNode. 
 * 
 * root and pivotNode are mutable. 
 * in the __avl__preorder function, it is the root that changes, 
 * while in the preoder function, it is the pivotNode that changes.
 * 
 * from the two nodes, look for LCA (Lowest common ancestor) 
 * and then determine the distance using the findjrk function.
 * -- distance = pivotNode to LCA + LCA to root 
 * 
 * findjrk function is only called when it satisfies the condition 
 * i.e. when root and pivotNode is not a leaf at all,
 * if one of them is leaf it still doesn't matter
 */

int x;
bool flag = false;

AVLNode *lca(AVLNode* root, int n1, int n2){
    while (root != NULL){
        if (root->data > n1 && root->data > n2)
            root = root->left;
        else if (root->data < n1 && root->data < n2)
            root = root->right;
        else break;
    }
    return root;
}

int findjrk(AVLNode *root, int value) {
    int jrk=0;
    while (root != NULL) {
        jrk += root->data;
        if (value < root->data)
            root = root->left;
        else if (value > root->data)
            root = root->right;
        else return jrk;
    }
    return jrk;
}

void __avl__preorder(AVL *avl, AVLNode *root, AVLNode *pivot) {
    if (root) {
        AVLNode *temp = lca(avl->_root, root->data, pivot->data);
        if((root->left!=NULL && root->right!=NULL) || (pivot->right!=NULL && pivot->left!=NULL))
        { // if pivotNode & root is not a leaf at all, if one of them is leaf it still doesn't matter
            int now = findjrk(temp, pivot->data) + findjrk(temp, root->data);
            now -= temp->data;
            if(now == x){
                flag = true;
                return;
            }
        }
        __avl__preorder(avl, root->left, pivot);
        __avl__preorder(avl, root->right, pivot);
    }
}


void preorder(AVL *avl, AVLNode *root) {
    if (root) {
        __avl__preorder(avl, avl->_root, root);
        preorder(avl, root->left);
        preorder(avl, root->right);
    }
}

int main(){
    AVL avlku;
    avl_init(&avlku);
    int n, cmd;
    scanf("%d",&n);
    while(n--){
        scanf("%d%d", &cmd, &x);
        if(cmd==1) avl_insert(&avlku, x);
        else{
            if (avlku._size <= 1) flag = false;
            else if (avl_find(&avlku, x)) flag = true;
            else preorder(&avlku, avlku._root);

            if(flag && avlku._size>1)printf("Aaa udh lama bgt ga diboongin:)\n");
            else printf("Apasi, ngajak berantem mulu dah kerjaannya:(\n");
            flag = false;
        }
    }
    return 0;
}