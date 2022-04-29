/**
 * fundamental code written by : Bayu Laksana
 * @date 2019-02-29
 * 
 * @editor Daud Dhiya' Rozaan
 * @date 2022-03-22
 */

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

typedef struct bstnode_t {
    int key;
    struct bstnode_t *left, *right;
} BSTNode;

typedef struct bst_t {
    unsigned int _size;
    BSTNode *_root;
} BST;

void bst_init(BST *bst) {
    bst->_root = NULL;
    bst->_size = 0u;
}

bool bst_isEmpty(BST *bst) {
    return bst->_root == NULL;
}

/* find & search */
BSTNode* __bst__search(BSTNode *root, int value) {
    while (root != NULL) {
        if (value < root->key)
            root = root->left;
        else if (value > root->key)
            root = root->right;
        else return root;
    }
    return root;
}

bool bst_find(BST *bst, int value) {
    BSTNode *temp = __bst__search(bst->_root, value);
    if (temp == NULL)
        return false;
    
    if (temp->key == value)
        return true;
    else return false;
}

/* insert */
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

/* remove */
BSTNode* __bst__findMinNode(BSTNode *node) {
    BSTNode *currNode = node;
    while (currNode && currNode->left != NULL)
        currNode = currNode->left;
    
    return currNode;
}

BSTNode* __bst__remove(BSTNode *root, int value) {
    if (root == NULL) return NULL;

    if (value > root->key) 
        root->right = __bst__remove(root->right, value);
    else if (value < root->key) 
        root->left = __bst__remove(root->left, value);
    else {
        
        if (root->left == NULL) {
            BSTNode *rightChild = root->right;
            free(root);
            return rightChild;
        }
        else if (root->right == NULL) {
            BSTNode *leftChild = root->left;
            free(root);
            return leftChild;
        }

        BSTNode *temp = __bst__findMinNode(root->right);
        root->key     = temp->key;
        root->right   = __bst__remove(root->right, temp->key);
    }
    return root;
}

void bst_remove(BST *bst, int value) {
    if (bst_find(bst, value)) {
        bst->_root = __bst__remove(bst->_root, value);
        bst->_size--;
    }
}

// inorder
/* prime */
void __bst__inorder_prima(BSTNode *root) {
    if (root) {
        __bst__inorder_prima(root->left);
        int stat = 1;
        int sq = sqrt(root->key);
        if(root->key < 2)
            stat = 0;
        else if(root->key > 2){
            for(int j=2; j<=sq; j++){
                if(root->key%j == 0){
                    stat = 0;
                    break;
                }
            }
        }
        if(stat == 1)
            printf("%d\n", root->key);
        __bst__inorder_prima(root->right);
    }
}

void bst_inorder_prima(BST *bst) {
    __bst__inorder_prima(bst->_root);
}

/* odd */
void __bst__inorder_ganjil(BSTNode *root) {
    if (root) {
        __bst__inorder_ganjil(root->left);
        if(root->key%2!=0)
            printf("%d\n", root->key);
        __bst__inorder_ganjil(root->right);
    }
}

void bst_inorder_ganjil(BST *bst) {
    __bst__inorder_ganjil(bst->_root);
}

/* genap */
void __bst__inorder_genap(BSTNode *root) {
    if (root) {
        __bst__inorder_genap(root->left);
        if(root->key%2==0)
            printf("%d\n", root->key);
        __bst__inorder_genap(root->right);
    }
}

void bst_inorder_genap(BST *bst) {
    __bst__inorder_genap(bst->_root);
}

/* semua */
void __bst__inorder_semua(BSTNode *root) {
    if (root) {
        __bst__inorder_semua(root->left);
        printf("%d\n", root->key);
        __bst__inorder_semua(root->right);
    }
}

void bst_inorder_semua(BST *bst) {
    __bst__inorder_semua(bst->_root);
}

//postorder 
/* prima */
void __bst__postorder_prima(BSTNode *root) {
    if (root) {
        __bst__postorder_prima(root->left);
        __bst__postorder_prima(root->right);
        int stat = 1;
        int sq = sqrt(root->key);
        if(root->key < 2)
            stat = 0;
        else if(root->key > 2){
            for(int j=2; j<=sq; j++){
                if(root->key%j == 0){
                    stat = 0;
                    break;
                }
            }
        }
        if(stat == 1)
            printf("%d\n", root->key);
    }
}

void bst_postorder_prima(BST *bst) {
    __bst__postorder_prima(bst->_root);
}

/* ganjil */
void __bst__postorder_ganjil(BSTNode *root) {
    if (root) {
        __bst__postorder_ganjil(root->left);
        __bst__postorder_ganjil(root->right);
        if(root->key%2!=0)
            printf("%d\n", root->key);
    }
}

void bst_postorder_ganjil(BST *bst) {
    __bst__postorder_ganjil(bst->_root);
}

/* genap */
void __bst__postorder_genap(BSTNode *root) {
    if (root) {
        __bst__postorder_genap(root->left);
        __bst__postorder_genap(root->right);
        if(root->key%2==0)
            printf("%d\n", root->key);
    }
}

void bst_postorder_genap(BST *bst) {
    __bst__postorder_genap(bst->_root);
}

/* semua */
void __bst__postorder_semua(BSTNode *root) {
    if (root) {
        __bst__postorder_semua(root->left);
        __bst__postorder_semua(root->right);
        printf("%d\n", root->key);
    }
}

void bst_postorder_semua(BST *bst) {
    __bst__postorder_semua(bst->_root);
}

//preorder
/* prima */
void __bst__preorder_prima(BSTNode *root) {
    if (root) {
        int stat = 1;
        int sq = sqrt(root->key);
        if(root->key < 2)
            stat = 0;
        else if(root->key > 2){
            for(int j=2; j<=sq; j++){
                if(root->key%j == 0){
                    stat = 0;
                    break;
                }
            }
        }
        if(stat == 1)
            printf("%d\n", root->key);
        __bst__preorder_prima(root->left);
        __bst__preorder_prima(root->right);
    }
}

void bst_preorder_prima(BST *bst) {
    __bst__preorder_prima(bst->_root);
}

/* ganjil */
void __bst__preorder_ganjil(BSTNode *root) {
    if (root) {
        if(root->key%2!=0)
            printf("%d\n", root->key);
        __bst__preorder_ganjil(root->left);
        __bst__preorder_ganjil(root->right);
    }
}

void bst_preorder_ganjil(BST *bst) {
    __bst__preorder_ganjil(bst->_root);
}

/* genap */
void __bst__preorder_genap(BSTNode *root) {
    if (root) {
        if(root->key%2==0)
            printf("%d\n", root->key);
        __bst__preorder_genap(root->left);
        __bst__preorder_genap(root->right);
    }
}

void bst_preorder_genap(BST *bst) {
    __bst__preorder_genap(bst->_root);
}

/* semua */
void __bst__preorder_semua(BSTNode *root) {
    if (root) {
        printf("%d\n", root->key);
        __bst__preorder_semua(root->left);
        __bst__preorder_semua(root->right);
    }
}

void bst_preorder_semua(BST *bst) {
    __bst__preorder_semua(bst->_root);
}

/* print ancestor of node until root */
bool printAncestorsOfNode(BSTNode* root, int num) {
    if (root == NULL) return false;
    if (root->key == num) return true;
    
    if (printAncestorsOfNode(root->left, num) || printAncestorsOfNode(root->right, num)) {
        printf("%d\n", root->key);
        return true;
    } 
    else return false;
}

/**
 * function to get the leaf, 
 * if node is leaf, return true, otherwise return false 
 */
bool searchNoChild(BST *bst, int j){
    BSTNode *temp = __bst__search(bst->_root, j);
    if(temp != NULL) {
        if(temp->left == NULL && temp->right == NULL)
            return true;
        else return false;
    }
    else return false;
}

int main(){
    BST set;
    bst_init(&set);
    for(int i=0;i>=0;i++){ // infinite loop until value of "fruit" is -1 
        int fruit;
        scanf("%d", &fruit);
        if(fruit==-1) break;
        bst_insert(&set, fruit);
    }

    int n;
    scanf("%d", &n);
    for(int i=1;i<=n;i++){
        char cmd[30], cmd1[30];
        getchar();
        scanf("%s", cmd);
        printf("Command : #%d\n",i);
        if(strcmp(cmd, "inorder")==0){ // do inorder traversal
            getchar();
            scanf("%s", cmd1);
            if(strcmp(cmd1, "prima")==0) // do it just for prime number
                bst_inorder_prima(&set);
            else if(strcmp(cmd1, "semua")==0) // do it just for all data in bst
                bst_inorder_semua(&set);
            else if(strcmp(cmd1, "ganjil")==0) // do it just for odd number
                bst_inorder_ganjil(&set);
            else if(strcmp(cmd1, "genap")==0) // do it just for even number
                bst_inorder_genap(&set);
        }
        // else, is like inorder but just in different traversal
        else if(strcmp(cmd, "postorder")==0){
            getchar();
            scanf("%s", cmd1);
            if(strcmp(cmd1, "prima")==0)
                bst_postorder_prima(&set);
            else if(strcmp(cmd1, "semua")==0)
                bst_postorder_semua(&set);
            else if(strcmp(cmd1, "ganjil")==0)
                bst_postorder_ganjil(&set);
            else if(strcmp(cmd1, "genap")==0)
                bst_postorder_genap(&set);
        }
        else if(strcmp(cmd, "preorder")==0){
            getchar();
            scanf("%s", cmd1);
            if(strcmp(cmd1, "prima")==0)
                bst_preorder_prima(&set);
            else if(strcmp(cmd1, "semua")==0)
                bst_preorder_semua(&set);
            else if(strcmp(cmd1, "ganjil")==0)
                bst_preorder_ganjil(&set);
            else if(strcmp(cmd1, "genap")==0)
                bst_preorder_genap(&set);
        }
        else{ // panjat
            int dicari;
            scanf("%d", &dicari);
            /**
             * if value not found, or value = root, or value is leaf, 
             * print certain message, and continue loop 
             */
            if(!bst_find(&set, dicari) || set._root->key == dicari || !searchNoChild(&set, dicari)){
                printf("Gabisa, dasar setan!\n");
                continue;
            }
            else{
                printf("%d\n", dicari); // print itself 
                printAncestorsOfNode(set._root, dicari);
                bst_remove(&set, dicari); // remove the value
            }
        }
    }
}