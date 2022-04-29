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
#define ll long long

typedef struct AVLNode_t{
    ll data, height;
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

AVLNode* _search(AVLNode *root, ll value) {
    while (root != NULL) {
        if (value < root->data) root = root->left;
        else if (value > root->data) root = root->right;
        else return root;
    }
    return root;
}

bool avl_find(AVL *avl, ll value) {
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

AVLNode* _avl_createNode(ll value) {
    AVLNode *newNode = (AVLNode*) malloc(sizeof(AVLNode));
    newNode->data = value;
    newNode->height = 1;
    newNode->left = newNode->right = NULL;
    return newNode;
}

AVLNode* _insert_AVL(AVL *avl, AVLNode* node, ll value) {
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

void avl_insert(AVL *avl, ll value){
    if(!avl_find(avl,value)){
        avl->_root=_insert_AVL(avl,avl->_root,value);
        avl->_size++;
    }
}

typedef struct bstnode_t {
    ll key, high;
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

bool bst_find(BST *bst, ll value) {
    BSTNode *temp = bst->_root;
    while (temp != NULL) {
        if (value < temp->key)
            temp = temp->left;
        else if (value > temp->key)
            temp = temp->right;
        else break;
    }
    if (temp == NULL) return false;

    if (temp->key == value) return true;
    else return false;
}

BSTNode* __bst__createNode(ll value, ll height) {
    BSTNode *newNode = (BSTNode*) malloc(sizeof(BSTNode));
    newNode->key = value;
    newNode->high = height;
    newNode->left = newNode->right = NULL;
    return newNode;
}

BSTNode* __bst__insert(BSTNode *root, ll value, ll height) {
    if (root == NULL) 
        return __bst__createNode(value, height);

    if (value < root->key){
        height++;
        root->left = __bst__insert(root->left, value, height);
    }
    else if (value > root->key){
        height++;
        root->right = __bst__insert(root->right, value, height);
    }
    
    return root;
}

void bst_insert(BST *bst, ll value, ll height) {
    if (!bst_find(bst, value)) {
        bst->_root = __bst__insert(bst->_root, value, height);
        bst->_size++;
    }
}

void preorder_avl(AVLNode *root, BST *set) {
    if (root) {
        ll flag = 1;
        bst_insert(set, root->data, flag);
        preorder_avl(root->left, set);
        preorder_avl(root->right, set);
    }
}

ll tinggi_maks = 0;
void preorder_bst(BSTNode *root, ll tinggi) {
    if (root) {
        if(root->high == ((tinggi-tinggi_maks-1)*-1))
            printf("%lld ", root->key);
        preorder_bst(root->left, tinggi);
        preorder_bst(root->right, tinggi);
    }
}

ll sum = 0;
void preorder_bst_sum(BSTNode *root, ll tinggi) {
    if (root) {
        if(root->high == ((tinggi-tinggi_maks-1)*-1)) 
            sum+=root->key;
        preorder_bst_sum(root->left, tinggi);
        preorder_bst_sum(root->right, tinggi);
    }
}

void inorder(BSTNode *root) {
    if (root) {
        inorder(root->left);
        if(root->left == NULL && root->right ==  NULL){
            if(root->high > tinggi_maks) 
                tinggi_maks = root->high;
        }
        inorder(root->right);
    }
}

int main(){
    AVL avlku;
    avl_init(&avlku);
    BST tree;
    int q;
    scanf("%d", &q);
    while(q--){
        int com;
        ll nilai, tinggi;
        scanf("%d", &com);
        switch (com){
        case 1:
            scanf("%lld", &nilai);
            avl_insert(&avlku, nilai);
            break;
        case 2:
            bst_init(&tree);
            scanf("%lld", &tinggi);
            preorder_avl(avlku._root, &tree);
            inorder(tree._root);
            preorder_bst(tree._root, tinggi);
            puts("");
            break;
        default:
            bst_init(&tree);
            scanf("%lld", &tinggi);
            preorder_avl(avlku._root, &tree);
            inorder(tree._root);
            preorder_bst_sum(tree._root, tinggi);
            printf("%lld\n", sum);
            sum = 0;
            break;
        }
    }
}