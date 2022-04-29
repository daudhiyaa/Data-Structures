/**
 * @author Bayu Laksana
 * @date 2019-02-29
 * 
 * Binary Search Tree Implementation
 * -- with unique-key in string data-type
 * For C
 * 
 * @editor Daud Dhiya' Rozaan
 * @date 2022-04-23
 * 
 * !! NOTE !!
 * see how it is used in the main() function
 */

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#define ll long long
#define MAX 100

typedef struct bstnode_t {
    char key[MAX];
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

BSTNode* __bst__search(BSTNode *root, char value[]) {
    while (root != NULL) {
        if (strcmp(value, root->key) < 0) 
            root = root->left;
        else if (strcmp(value, root->key) > 0)
            root = root->right;
        else return root;
    }
    return root;
}

bool bst_find(BST *bst, char value[]) {
    BSTNode *temp = __bst__search(bst->_root, value);
    if (temp == NULL) return false;
    
    if (strcmp(temp->key, value)==0) return true;
    else return false;
}

/* uses of "another_bst_find" function is like "bst_find" but without using "__bst__search" function */
bool another_bst_find(BST *bst, char value[]) {
    BSTNode *temp = bst->_root;
    while (temp != NULL) {
        if (strcmp(value, temp->key) < 0)
            temp = temp->left;
        else if (strcmp(value, temp->key) > 0)
            temp = temp->right;
        else if (strcmp(value, temp->key) == 0) return true;
    }
    return false;
}

BSTNode* __bst__createNode(char value[]) {
    BSTNode *newNode = (BSTNode*) malloc(sizeof(BSTNode));
    strcpy(newNode->key, value);
    newNode->left = newNode->right = NULL;
    return newNode;
}

BSTNode* __bst__insert(BSTNode *root, char value[]) {
    if (root == NULL) 
        return __bst__createNode(value);

    if (strcmp(value, root->key) < 0)
        root->left = __bst__insert(root->left, value);
    else if (strcmp(value, root->key) > 0)
        root->right = __bst__insert(root->right, value);
    
    return root;
}

void bst_insert(BST *bst, char value[]) {
    if (!bst_find(bst, value)) {
        bst->_root = __bst__insert(bst->_root, value);
        bst->_size++;
    }
}

BSTNode* __bst__findMinNode(BSTNode *node) {
    BSTNode *currNode = node;
    while (currNode && currNode->left != NULL)
        currNode = currNode->left;
    return currNode;
}

BSTNode* __bst__remove(BSTNode *root, char value[]) {
    if (root == NULL) return NULL;

    if (strcmp(value, root->key) > 0) 
        root->right = __bst__remove(root->right, value);
    else if (strcmp(value, root->key) < 0) 
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
        strcpy(root->key, temp->key);
        root->right   = __bst__remove(root->right, temp->key);
    }
    return root;
}

void bst_remove(BST *bst, char value[]) {
    if (bst_find(bst, value)) {
        bst->_root = __bst__remove(bst->_root, value);
        bst->_size--;
    }
}

void inorder(BSTNode *root) {
    if (root) {
        inorder(root->left);
        printf("%s\n", root->key);
        inorder(root->right);
    }
}

void postorder(BSTNode *root) {
    if (root) {
        postorder(root->left);
        postorder(root->right);
        printf("%s\n", root->key);
    }
}

void preorder(BSTNode *root) {
    if (root) {
        printf("%s\n", root->key);
        preorder(root->left);
        preorder(root->right);
    }
}
 
int main(){
    BST tree;
    bst_init(&tree);

    int n;
    scanf("%d", &n);
    char str[MAX];
    for(int i=0;i<n;i++){
        scanf("%[^\n]s", str);
        bst_insert(&tree, str);
    }
    inorder(tree._root);
    return 0;
}