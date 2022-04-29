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

int indeks = 0;
bool found = false;

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

bool bst_isEmpty(BST *bst) {
    return bst->_root == NULL;
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

void bst_insert(BST *bst, int value) {
    if (!bst_find(bst, value)) {
        bst->_root = __bst__insert(bst->_root, value);
        bst->_size++;
    }
}

/**
 * searchParent function is function to determine the parent of a node, 
 * print the parent->data
 */
void searchParent(BST *bst, int value){
    if(!bst_find(bst, value)){ // if value not found, print certain message
        printf("ini anak siapa dah\n");
        return;
    }
    if(bst->_root->key == value){ // if value is root, print certain message
        printf("ini anak siapa dah\n");
        return;
    }

    BSTNode *temp = bst->_root;
    while(temp != NULL){
        if(temp->right != NULL && value == temp->right->key){
            printf("%d\n", temp->key);
            break;
        }
        else if(temp->left != NULL && value == temp->left->key){
            printf("%d\n", temp->key);
            break;
        }

        if(value > temp->key)
            temp = temp->right;
        else if(value < temp->key)
            temp = temp->left;
        
    }
}

void __bst__inorder(BSTNode *root, int value) {
    if (root && !found) {
    	__bst__inorder(root->left, value);
        if (!found) indeks++;
        if (root->key == value)
	        found = true;
        __bst__inorder(root->right, value);
    }
}

int bst_inorder(BST *bst, int value) {
    __bst__inorder(bst->_root, value);
    return indeks;
}

int main(){
    BST set;
    bst_init(&set);

    char cmd[15];
    int n, nilai, count = 0;
    scanf("%d", &n);
    
    while(n--) {
        scanf("%s", cmd);
        if(!strcmp(cmd, "masukin")){ // insert the value to avl tree
            scanf("%d", &nilai);
            bst_insert(&set, nilai);
        }
        else if(!strcmp(cmd, "anaksiapa")){ // searchParent
            scanf("%d", &nilai);
            searchParent(&set, nilai);
        }
        else{ // berapa
        // search the index of value in avl tree by ascending 
            scanf("%d", &nilai);
            indeks = 0;
			count = bst_inorder(&set, nilai);
			printf("%d\n", count);
			found = false;	
        }
    }
}