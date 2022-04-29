#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

int id = 0;
typedef struct snode_t {
    int data;
    struct snode_t *next;
} SListNode;

typedef struct slist_t {
    unsigned _size;
    SListNode *_head;
} SinglyList;

void slist_init(SinglyList *list) {
    list->_head = NULL;
    list->_size = 0;
}

bool slist_isEmpty(SinglyList *list) {
    return (list->_head == NULL);
}

void slist_pushFront(SinglyList *list, int value) {
    SListNode *newNode = (SListNode*) malloc(sizeof(SListNode));
    if (newNode) {
        list->_size++;
        newNode->data = value;

        if (slist_isEmpty(list)) newNode->next = NULL;
        else newNode->next = list->_head;
        list->_head = newNode;
    }
}

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

void __bst__inorder(BSTNode *root, int x) {
    if (root) {
        __bst__inorder(root->left, x);

        SinglyList myList;
        slist_init(&myList);
        id++;
        slist_pushFront(&myList, root->key);
        if(id==x)
            printf("%d\n", root->key);

        __bst__inorder(root->right, x);
    }
}

void __bst__postorder(BSTNode *root, int x) {
    if (root) {
        SinglyList myList;
        slist_init(&myList);
        __bst__postorder(root->left, x);
        __bst__postorder(root->right, x);

        id++;
        slist_pushFront(&myList, root->key);
        if(id==x)
            printf("%d\n", root->key);
    }
}

void __bst__preorder(BSTNode *root, int x) {
    if (root) {
        SinglyList myList;
        slist_init(&myList);
        id++;
        slist_pushFront(&myList, root->key);
        if(id==x)
            printf("%d\n", root->key);
        
        __bst__preorder(root->left, x);
        __bst__preorder(root->right, x);
    }
}

void bst_inorder(BST *bst, int x) {
    __bst__inorder(bst->_root, x);
}

void bst_postorder(BST *bst, int x) {
    __bst__postorder(bst->_root, x);
}

void bst_preorder(BST *bst, int x) {
    __bst__preorder(bst->_root, x);
}

int main(){
    BST set;
    bst_init(&set);

    char perintah[20];
    int q, data, x, command;
    scanf("%d", &q);
    while(q--){
        scanf("%d", &command);
        switch (command){
        case 1:
            scanf("%d", &data);
            bst_insert(&set, data);
            break;
        default:
            scanf("%s %d", perintah, &x);
            if(strcmp(perintah, "inorder")==0)
                bst_inorder(&set, x);
            else if(strcmp(perintah, "postorder")==0)
                bst_postorder(&set, x);
            else bst_preorder(&set, x);
            break;
        }
    }
    return 0;
}