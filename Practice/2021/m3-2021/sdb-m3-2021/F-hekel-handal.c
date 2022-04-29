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

#define MAX 100005
int arr[MAX];

void preorder(AVLNode *root, int lvl) {
    if(root) {
        arr[lvl] += root->data;
        preorder(root->left, lvl - 1);
        preorder(root->right, lvl + 1);
    }
}

int main(){
    AVL avlku;
    avl_init(&avlku);
    int t, nilai;
    long sum = 0;
    scanf("%d", &t);
    while(t--){
        int com;
        scanf("%d", &com);
        switch (com){
        case 1:
            scanf("%d", &nilai);
            avl_insert(&avlku, nilai);
            break;
        default:
            preorder(avlku._root, (avlku._size + 1) / 2);
            for(int i = 0; i < avlku._size + 1; i++) {
                if(arr[i] != 0) {
                    printf("%d ", arr[i]);
                    sum += arr[i];
                }
            }
            printf("\ntotal : %ld\n", sum);
            memset(arr, 0, sizeof(arr));
            sum = 0;
            break;
        }
    }
}