/**
 * fundamental code written by : ABDUR ROCHMAN
 * @date 2020-03-28
 * 
 * @editor Keyisa Raihan
 * @date 2022-04-11
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

bool avl_isEmpty(AVL *avl) {
    return avl->_root == NULL;
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
        else
            return root;
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
    if(balanceFactor > 1 && value > node->left->data) // 
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

int x;
bool flag=false;

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
        else{
            // printf("%d\n",jrk);
            return jrk;
        }
    }
    return jrk;
}

void __avl__preorder(AVL *avl, AVLNode *root,int cari) {
    if (root) {
        AVLNode *temp = lca(avl->_root, root->data, cari);
        if(root->left!=NULL || root->right!=NULL || _search(avl->_root, cari)->right!=NULL || 
           _search(avl->_root, cari)->left!=NULL || root->data == _search(avl->_root,cari)->data){
            int now = findjrk(temp,cari) + findjrk(temp,root->data);
            now -= temp->data;
            // printf("x = %d , now %d\n", x, now);
            if(now==x)flag=true;
        }
        __avl__preorder(avl,root->left,cari);
        __avl__preorder(avl,root->right,cari);
    }
}


void inorder(AVL *avl, AVLNode *root, int value) {
    if (root) {
        __avl__preorder(avl,avl->_root,root->data);
        inorder(avl,root->left,value);
        inorder(avl,root->right,value);
    }
}

int main(){
    AVL avlku;
    avl_init(&avlku);
    int n, cmd;
    scanf("%d",&n);
    while(n--){
        scanf("%d %d",&cmd,&x);
        if(cmd==1)
            avl_insert(&avlku,x);
        else{
            inorder(&avlku,avlku._root,x);
            if(flag)printf("HehE Boy, AkAn KutemUkan kaU Petot\n");
            else printf("Yahh Petot kAbur :(\n");
            flag=false;
        }
    }
    return 0;
}