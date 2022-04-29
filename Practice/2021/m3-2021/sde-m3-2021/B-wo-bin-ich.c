/**
 * fundamental code written by : ABDUR ROCHMAN
 * @date 2020-03-28
 * 
 * @editor Daud Dhiya' Rozaan
 * @date 2022-04-19
 */

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#define ll long long
#define ull unsigned long long
#define MOD 1000000007

typedef struct AVLNode_t{
    ll data, height,
        leftChild, rightChild;
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
    AVLNode* newParrent = pivotNode->left;
    pivotNode->left = newParrent->right;
    pivotNode->leftChild = newParrent->rightChild;
    newParrent->right = pivotNode;

    if(newParrent->right)
        newParrent->rightChild = pivotNode->leftChild + pivotNode->rightChild + 1;
    else newParrent->rightChild = 0;

    pivotNode->height=_max(_getHeight(pivotNode->left),
                      _getHeight(pivotNode->right))+1;
    newParrent->height=_max(_getHeight(newParrent->left),
                       _getHeight(newParrent->right))+1;
    
    return newParrent;
}

AVLNode* _leftRotate(AVLNode* pivotNode) {
    AVLNode* newParrent=pivotNode->right;
    pivotNode->right=newParrent->left;
    pivotNode->rightChild = newParrent->leftChild;
    newParrent->left=pivotNode;

    if(newParrent->left)
        newParrent->leftChild = pivotNode->leftChild + pivotNode->rightChild + 1;
    else newParrent->leftChild = 0;

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
    newNode->height=1;
    newNode->left = newNode->right = NULL;
    newNode->leftChild = 0;
    newNode->rightChild = 0;
    return newNode;
}

AVLNode* _insert_AVL(AVL *avl,AVLNode* node, ll value) {
    if(node==NULL)
        return _avl_createNode(value);
    if(value < node->data)
        node->left = _insert_AVL(avl,node->left,value), node->leftChild++;
    else if(value > node->data)
        node->right = _insert_AVL(avl,node->right,value), node->rightChild++;
    
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

void avl_insert(AVL *avl, ll value){
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

AVLNode* _remove_AVL(AVLNode* node, ll value){
    if(node==NULL)
        return node;
    if(value > node->data)
        node->right=_remove_AVL(node->right,value), node->rightChild--;
    else if(value < node->data)
        node->left=_remove_AVL(node->left,value), node->leftChild--;
    else{
        AVLNode *temp;
        if((node->left==NULL)||(node->right==NULL)){
            temp=NULL;
            if(node->left==NULL) temp=node->right;  
            else if(node->right==NULL) temp=node->left;
            
            if(temp==NULL){
                temp=node;
                node=NULL;
            }
            else *node=*temp;   
            
            free(temp);
        }
        else{
            temp = _findMinNode(node->right);
            node->data=temp->data;
            node->rightChild--;
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

void avl_remove(AVL *avl, ll value){
    if(avl_find(avl,value)){
        avl->_root=_remove_AVL(avl->_root,value);
        avl->_size--;
    }
}

int indeks(AVLNode *root, ll value){
    AVLNode *temp = root;
    int idx = 0;
    while(temp != NULL)
        if(value < temp->data) 
            temp = temp->left;
        else if(value > temp->data)
            idx += temp->leftChild + 1, temp = temp->right;
        else return idx + temp->leftChild;
    return -1;
}

ll arr_permutasi[100001];
void permutasi(){
    ll multiply = 1;
    arr_permutasi[0] = 1;
    for (int i = 1; i <= 100000; i++) {
        multiply = (multiply * i) % MOD;
        arr_permutasi[i] = multiply;
    }
}

int main(){
    AVL avlku;
    avl_init(&avlku);
    permutasi();
    
    int n;
    scanf("%d", &n);
    while(n--){
        int num;
        scanf("%d", &num);

        ll bil[num];
        for(int i=0;i<num;i++){
            scanf("%lld", &bil[i]);
            avl_insert(&avlku, bil[i]);
        }

        ll index = 0;
        for(int i=0;i<num;i++){
            int idx_bilangan = indeks(avlku._root, bil[i]);
            int permutate = num - i; 

            index = (index + ((arr_permutasi[permutate - 1] * idx_bilangan) % MOD))%MOD;
            avl_remove(&avlku, bil[i]);
        }
        printf("%lld\n", index+1);
    }
}