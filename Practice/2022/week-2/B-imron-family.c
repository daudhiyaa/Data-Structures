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

typedef struct bstnode_t {
    int key;
    char city[100000]; // string to store the name of city
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

bool bst_isEmpty(BST *bst) {
    return bst->_root == NULL;
}

BSTNode* __bst__createNode(int value, char *kota) {
    BSTNode *newNode = (BSTNode*) malloc(sizeof(BSTNode));
    newNode->key = value;
    strcpy(newNode->city, kota); // assign the "kota" value to newNode->city using strcpy
    newNode->left = newNode->right = NULL;
    return newNode;
}

BSTNode* __bst__insert(BSTNode *root, int value, char *kota) {
    if (root == NULL) 
        return __bst__createNode(value, kota);

    if (value < root->key)
        root->left = __bst__insert(root->left, value, kota);
    else if (value > root->key)
        root->right = __bst__insert(root->right, value, kota);
    
    return root;
}

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

void bst_insert(BST *bst, int value, char *kota) {
    if (!bst_find(bst, value)) {
        bst->_root = __bst__insert(bst->_root, value, kota);
        bst->_size++;
    }
}

/**
 * LCA function to find the lowest common ancestor of 2 node
 */
BSTNode *lca(BSTNode* root, int n1, int n2){
    while (root != NULL){
        if (root->key > n1 && root->key > n2)
            root = root->left;
        else if (root->key < n1 && root->key < n2)
            root = root->right;
        /**
         * if n1 > root->key and n2 < root->key,
         * or n1 < root->key and n2 > root->key,
         * stop the loop and return the root
         */
        else break;
    }
    return root;
}

int main(){
    BST set;
    bst_init(&set);

    int n;
    scanf("%d", &n);
    int id;
    char kota[100000];
    while(n--){
        scanf("%d %s", &id, kota);
        bst_insert(&set, id, kota);
    }

    int t;
    scanf("%d", &t);
    int a, b;
    while(t--){
        scanf("%d%d", &a, &b);
        BSTNode *temp = lca(set._root, a, b);
        printf("%s\n", temp->city);
    }
    return 0;
}