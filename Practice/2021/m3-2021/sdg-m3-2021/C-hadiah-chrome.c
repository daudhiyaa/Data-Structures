#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>

typedef struct AVLNode_t{
    unsigned long long data, number;
    struct AVLNode_t *left,*right;
    int height;
}AVLNode;

typedef struct AVL_t{
    AVLNode *_root;
    unsigned int _size;
}AVL;

AVLNode* _avl_createNode(unsigned long long value, unsigned long long number) {
    AVLNode *newNode = (AVLNode*) malloc(sizeof(AVLNode));
    newNode->data = value;
    newNode->number = number;
    newNode->height=1;
    newNode->left = newNode->right = NULL;
    return newNode;
}

AVLNode* _search(AVLNode *root, unsigned long long value) {
    while (root != NULL) {
        if (value < root->data)
            root = root->left;
        else if (value > root->data)
            root = root->right;
        else return root;
    }
    return root;
}

int _getHeight(AVLNode* node){
    if(node==NULL) return 0;
    return node->height;
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

int _getBalanceFactor(AVLNode* node){
    if(node==NULL) return 0;
    return _getHeight(node->left)-_getHeight(node->right);
}

AVLNode* _insert_AVL(AVL *avl,AVLNode* node,unsigned long long value, unsigned long long number) {
    if(node==NULL)
        return _avl_createNode(value, number);
    if(value < node->data)
        node->left = _insert_AVL(avl,node->left,value,number);
    else if(value > node->data)
        node->right = _insert_AVL(avl,node->right,value,number);

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

void avl_init(AVL *avl) {
    avl->_root = NULL;
    avl->_size = 0u;
}

bool avl_find(AVL *avl, unsigned long long value) {
    AVLNode *temp = _search(avl->_root, value);
    if (temp == NULL) return false;

    if (temp->data == value) return true;
    else return false;
}

void avl_insert(AVL *avl, unsigned long long value, unsigned long long number){
    if(!avl_find(avl,value)){
        avl->_root=_insert_AVL(avl,avl->_root,value,number);
        avl->_size++;
    }
}

void preorder(AVLNode *root) {
    if (root){
        printf("%llu %llu\n", root->number, root->data);
        preorder(root->left);
        preorder(root->right);
    }
}

unsigned long long cek_prima(unsigned long long number){
    if(number == 2)
        return number;
    unsigned long long i, akar = sqrt(number);
    for (i=3; i<=akar; i+=2){
        if (number%i == 0)
            return cek_prima(number-2);
    }
    return number;
}

unsigned long long cek_prima_2(unsigned long long number){
    if(number == 2)
        return number;
    unsigned long long i, akar = sqrt(number);
    for (i=3; i<=akar; i+=2){
        if (number%i == 0)
            return cek_prima_2(number+2);
    }
    return number;
}

int main(){
    AVL num, code;
    avl_init(&num);
    avl_init(&code);

    unsigned long long Z, num_root, prima_1, prima_2, prima_3, i, N, hasil_1, hasil_2;
    scanf("%llu", &N);

    for(i=1; i<=N; i++){
        scanf("%llu", &Z);
        avl_insert(&num, Z, i);
        num_root = sqrt(Z);
        if(num_root%2 == 0)
            num_root++;
        prima_1 = cek_prima(num_root);
        if(prima_1 == 3)
            prima_2 = 2;
        else
            prima_2 = cek_prima(prima_1-2);
        prima_3 = cek_prima_2(prima_1+2);

        hasil_1 = prima_1*prima_2;
        hasil_2 = prima_1*prima_3;
        if(hasil_2 <= Z){
            if(!avl_find(&code, hasil_2))
                avl_insert(&code, hasil_2, i);
        }
        else{
            if(!avl_find(&code, hasil_1))
                avl_insert(&code, hasil_1, i);
        }
    }
    printf("Hint :\n");
    preorder(num._root);
    printf("Kode Rahasia :\n");
    preorder(code._root);

    return 0;
}