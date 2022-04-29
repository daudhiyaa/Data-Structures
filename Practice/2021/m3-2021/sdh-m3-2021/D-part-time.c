/**
 * fundamental code written by : ABDUR ROCHMAN
 * @date 2020-03-28
 * 
 * @editor Daud Dhiya' Rozaan
 * @date 2022-04-11
 */

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

typedef struct AVLNode_t{
    int data, height, id;
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


AVLNode* _avl_createNode(int id, int value) {
    AVLNode *newNode = (AVLNode*) malloc(sizeof(AVLNode));
    newNode->data = value;
    newNode->id = id;
    newNode->height=1;
    newNode->left = newNode->right = NULL;
    return newNode;
}

AVLNode* _insert_AVL(AVL *avl, AVLNode* node, int id, int value) {
    if(node==NULL) // udah mencapai leaf
        return _avl_createNode(id, value);
    if(id < node->id)
        node->left = _insert_AVL(avl, node->left, id, value);
    else if(id > node->id)
        node->right = _insert_AVL(avl, node->right, id, value);
    
    node->height = 1 + _max(_getHeight(node->left),_getHeight(node->right)); 

    int balanceFactor = _getBalanceFactor(node);
    
    if(balanceFactor > 1 && id < node->left->id) // skewed kiri (left-left case)
        return _leftCaseRotate(node);
    if(balanceFactor > 1 && id > node->left->id) // 
        return _leftRightCaseRotate(node);
    if(balanceFactor < -1 && id > node->right->id)
        return _rightCaseRotate(node);
    if(balanceFactor < -1 && id < node->right->id)
        return _rightLeftCaseRotate(node);
    
    return node;
}

void avl_insert(AVL *avl, int id, int value){
    avl->_root=_insert_AVL(avl, avl->_root, id, value);
    avl->_size++;
}

long long sum = 0;
void inorder(AVLNode *root, int barang, int id){
    if (root) {
        inorder(root->right, barang, id);
        if(root->id == id){
            int temp = barang * root->data;
            sum += temp;
        }
        inorder(root->left, barang, id);
    }
}

int main(){
    AVL avlku;
    avl_init(&avlku);
    int indeks = 0;

    int m, n;
    scanf("%d%d", &m, &n);
    int id, nilai;
    while(m--){
        scanf("%d%d", &id, &nilai);
        indeks++;
        if(id!=indeks){
            printf("ID harus urut\n");
            return 0;
        }
        else avl_insert(&avlku, id, nilai);
        // printf("%d\n", indeks);
    }
    
    int barang_dibeli, id_dibeli;
    while(n--){
        scanf("%d%d", &barang_dibeli, &id_dibeli);
        if(id_dibeli > indeks || id_dibeli < 1)
            printf("Maaf barang tidak tersedia\n");
        else inorder(avlku._root, barang_dibeli, id_dibeli);
    }
    printf("%lld\n", sum);
    return 0;
}