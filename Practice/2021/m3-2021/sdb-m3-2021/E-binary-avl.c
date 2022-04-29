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
#include <ctype.h>

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

void avl_insert(AVL *avl, int value){
    if(!avl_find(avl, value)){
        avl->_root=_insert_AVL(avl,avl->_root,value);
        avl->_size++;
    }
}

int flag = 0, password[105], indeks = 0;
void inorder_avl(AVLNode *root) {
    if (root) {
        inorder_avl(root->left);
        if(root->left == NULL && root->right ==  NULL){
            password[indeks] = root->data;
            flag++; indeks++;
        }
        inorder_avl(root->right);
    }
}

typedef struct bstnode_t {
    int key;
    struct bstnode_t *left, *right;
} BSTNode;

typedef struct bst_t {
    BSTNode *_root;
    unsigned int _size;
} BST;

void bst_init(BST *bst) {
    bst->_root = NULL;
    bst->_size = 0u;
}

bool bst_find(BST *bst, int value) {
    BSTNode *temp = bst->_root;
    while (temp != NULL) {
        if (value < temp->key)
            temp = temp->left;
        else if (value > temp->key)
            temp = temp->right;
        else if (value == temp->key) return true;
    }
    if (temp == NULL) return false;

    if (temp->key == value) return true;
    else return false;
}

BSTNode* __bst__createNode(int value) {
    BSTNode *newNode = (BSTNode*) malloc(sizeof(BSTNode));
    newNode->key = value;
    newNode->left = newNode->right = NULL;
    return newNode;
}

BSTNode* __bst__insert(BSTNode *root, int value) {
    if (root == NULL) 
        return __bst__createNode(value);

    if (value < root->key)
        root->left = __bst__insert(root->left, value);
    else if (value > root->key)
        root->right = __bst__insert(root->right, value);
    
    return root;
}

void bst_insert(BST *bst, int value) {
    if (!bst_find(bst, value)) {
        bst->_root = __bst__insert(bst->_root, value);
        bst->_size++;
    }
}

void inorder_bst(BSTNode *root, int akar, AVL *avl) {
    if (root) {
        inorder_bst(root->left, akar, avl);
        if(root->key != akar && (root->left != NULL || root->right !=  NULL))
            avl_insert(avl, root->key);
        inorder_bst(root->right, akar, avl);
    }
}

int main(){
    AVL avlku;
    avl_init(&avlku);
    BST tree;
    bst_init(&tree);

    int len, t;
    scanf("%d%d", &len, &t);
    while(t--){
        int size = len+1;
        char kode[size];
        getchar();
        scanf("%s", kode);
        int pengali = kode[size-1] - '0';

        int sum = 0, j = 0, arr[26], nilai = 0;
        for(int i=0;i<size-1;i++){
            if(kode[i] >= 'A' && kode[i] <= 'Z' && kode[i]!='X'){
                arr[j] = kode[i] - 'A' + 1;
                sum += arr[j];
                nilai = sum * pengali;
                bst_insert(&tree, nilai);
                j++;
            }
        }
    }

    bool genap = false, ganjil = false;
    int akar = tree._root->key;
    inorder_bst(tree._root, akar, &avlku);
    inorder_avl(avlku._root);
    if(flag==0){
        printf("Input-nya kurang mas/mbak.\n");
        return 0;
    }

    for(int m=0;m<flag;m++){
        if(password[m]%2==0) genap = true;
        else ganjil = true;
        if(ganjil && genap) break;
    }

    if(genap && !ganjil)printf("mantap");
    else if(!genap && ganjil) printf("gokil");
    else printf("goatapkil");
    
    for(int m=0;m<flag;m++) printf("%d", password[m]);
    
    printf(".avl\n");
}