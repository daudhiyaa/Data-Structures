/**
 * fundamental code written by : ABDUR ROCHMAN
 * @date 2020-03-28
 * 
 * @editor Daud Dhiya' Rozaan
 * @date 2022-04-23
 * 
 * Example (with explanation in Indonesian) by : M Daffa Ashdaqfillah
 * Documentation by : M Daffa Ashdaqfillah 
 * (the documentation has been translated to english) 
 
  Example :
  Permisalan ada 3 bilangan, sehingga kemungkinan permutasi =
    1 2 3
    1 3 2
    2 1 3
    2 3 1
    3 1 2
    3 2 1
  Permisalan pencarian urutan dari 3 2 1
 
 1. avl dan index pertama {1,2,3}
    jumlah bilangan sekarang = 2
 
    di kasus ini pengecekan angka pertama dimulai dari 3
    index 3 = 2 (karena index dimulai dari 0)
    jumlahPermutasi dari [jumlah bilangan - 1] = [3-1] = jumlahPermutasi[2] = 2
    sehingga, index = index + (indexBilangan * jumlahPermutasi[jumlahBilangan-1])
    index = 0 + (2 * 2) = 4
    lalu 3 dihapus dari AVL
 
 2. avl dan index sekarang = {1,2}
    jumlah bilangan sekarang = 2
 
    Pengecekan kedua (angka 2)
    index 2 = 1 (karena index dimulai dari 0)
    jumlahPermutasi dari [jumlah bilangan - 1] = [2-1] = jumlahPermutasi[1] = 1
    sehingga, index = index + (indexBilangan * jumlahPermutasi[jumlahBilangan-1])
    index = 4 + (1 * 1) => 4 + 1 = 5
    lalu 2 dihapus dari AVL
 
 3. avl dan index sekarang = {1,2}
    jumlah bilangan sekarang = 2

    Pengecekan ketiga (angka 1)
    index 1 = 0 (karena index dimulai dari 0)
    jumlahPermutasi dari [jumlah bilangan - 1] = [1-1] = jumlahPermutasi[0] = 1
    sehingga, index = index + (indexBilangan * jumlahPermutasi[jumlahBilangan-1])
    index = 5 + (1 * 0) => 5 + 0 = 5
    lalu 1 dihapus dari AVL
 
  karena perulangan sudah selesai maka,
  urutan 3 2 1 ada di index permutasi ke-5 (index mulai dari nol)
  atau ada di index permutasi ke-6 (index mulai dari 1)
 
  printf 6
*/

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define ll long long
#define ull unsigned long long
#define MOD 1000000007

typedef struct AVLNode_t{
    ll data, height,
        leftChild, rightChild; // leftChild & rightChild to count the many nodeChild
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
    /**
     * cause pivotNode will be rightChild of newParent, 
     * so the rightChild of newParent will become into leftChild of pivotNode
     */
    pivotNode->leftChild = newParrent->rightChild;
    newParrent->right = pivotNode;

    /**
     * if newParent has rightNode, 
     * so the leftChild of pivotNode and rightChild of pivotNode will be rightChild of newParent
     */
    if(newParrent->right) // plus by one because pivotNode become rightChild of newParent
        newParrent->rightChild = pivotNode->leftChild + pivotNode->rightChild + 1;

    /* else, set the rightChild of newParent to 0 */
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
    /**
     * cause pivotNode will be leftChild of newParent, 
     * so the leftChild of newParent will become into rightChild of pivotNode
     */
    pivotNode->rightChild = newParrent->leftChild;
    newParrent->left=pivotNode;

    /**
     * if newParent has leftNode, 
     * so the leftChild of pivotNode and rightChild of pivotNode will be rightChild of newParent
     */
    if(newParrent->left) // plus by one because pivotNode become leftChild of newParent
        newParrent->leftChild = pivotNode->leftChild + pivotNode->rightChild + 1;

    /* else, set the leftChild of newParent to 0 */
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
    newNode->leftChild = 0; // declaration with zero value
    newNode->rightChild = 0; // declaration with zero value
    return newNode;
}

AVLNode* _insert_AVL(AVL *avl,AVLNode* node, ll value) {
    if(node==NULL)
        return _avl_createNode(value);

    /* everytime moving to left, add the value of leftChild*/
    if(value < node->data)
        node->left = _insert_AVL(avl,node->left,value), node->leftChild++;
    /* everytime moving to right, add the value of rightChild*/
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

    /* everytime moving to right, reduce the value of rightChild */
    if(value > node->data)
        node->right=_remove_AVL(node->right,value), node->rightChild--;
    /* everytime moving to left, reduce the value of leftChild */
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
            /* the smallest value of rightChild will be entered into data's node */
            node->data=temp->data;
            /**
             * rightChild's node removed one because deletion will be done
             * with the smallest value of previous rightChild
             */
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
    int idx = 0; // index value start with 0
    while(temp != NULL)
        if(value < temp->data) 
            temp = temp->left;
        /* everytime moving to right, leftChild of previous node will be added to index */
        else if(value > temp->data)
            idx += temp->leftChild + 1, temp = temp->right;
        /**
         * return index that previously accumulated + leftChild of that node
         * (because the value is smaller than the node value and hasn't been added to the index)
         */
        else return idx + temp->leftChild;
    return -1;
}


/**
 * permutation function, it is used to determine the number of permutations of a number.
 * refers to contraints, the size of arr_permutasi is 10^5 + 1
 * 
 * array permutations (arr_permutasi) is an array that store 
 * the value of the number of permutations of some numbers
 */
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
    /* create the AVL object and init it */
    AVL avlku;
    avl_init(&avlku);

    /* call the permutation function */
    permutasi();
    
    int n;
    scanf("%d", &n);
    while(n--){
        int num;
        scanf("%d", &num);
        int jumlahBil = num-1; // current number of numbers

        ll bil[num];
        for(int i=0;i<num;i++){
            scanf("%lld", &bil[i]);
            avl_insert(&avlku, bil[i]);
        }

        ll index = 0; // lexicographic index of the order of permutations
        for(int i=0;i<num;i++){
            int idx_bilangan = indeks(avlku._root, bil[i]); // to get index number

            /**
             * index formula :
             * (index + ((permutation[currentNumberOfNumbers] * indexNumber) % MOD)) % MOD
             */
            index = (index + ((arr_permutasi[jumlahBil] * idx_bilangan) % MOD)) % MOD;
            avl_remove(&avlku, bil[i]);
            jumlahBil--; // decrease the value of current number of numbers
        }
        printf("%lld\n", index+1); // plus by one cause index start from 0
    }
    return 0;
}

/**
 * note : actually you can change index start from 1,
 * so when printf you don't need add the index by 1
 */