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

long y1 = 0, y2 = 0; // to count the 2 deepest depth
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

bool bst_find(BST *bst, long value) {
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

BSTNode* __bst__insert(BSTNode *root, int value, int *flag) {
    if (root == NULL) 
        return __bst__createNode(value);

    /**
     * everytime the node is moving to left or right, increase the flag value,
     * that mean the node is go deeper form the root
     */
    if (value < root->key){ 
        root->left = __bst__insert(root->left, value, flag);
        *flag+=1;
    }
    else if (value > root->key){
        root->right = __bst__insert(root->right, value, flag);
        *flag+=1;
    }
    return root;
}

void bst_insert(BST *bst, int value) {
    long flag = 0;
    if (!bst_find(bst, value)) {
        bst->_root = __bst__insert(bst->_root, value, &flag);
        bst->_size++;
    }

    if(flag==0){ // if depth is still 0, print certain message
        printf("Mulai!\n");
        return;
    }
    // store the flag value that obtained while inserting the value to bst
    else if(flag > y1)
        y1 = flag;
    else if(flag > y2)
        y2 = flag;

    if((y1+y2)%2==0) // if the sum of 2 deepest depth is even, print certain message
        printf("IKKI!!! :(\n");
    // if the sum is odd, print the sum
    else printf("%ld\n", y1 + y2);
}

int main(){
    BST set;
    bst_init(&set);

    int n;
    long x;
    scanf("%d", &n);
    while(n--){
        scanf("%ld", &x);
        bst_insert(&set, x);
    }
    return 0;
}