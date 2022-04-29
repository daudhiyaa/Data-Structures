#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

typedef struct bstnode_t {
    int key;
    char nama[50000];
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

BSTNode* __bst__createNode(char* nama) {
    BSTNode *newNode = (BSTNode*) malloc(sizeof(BSTNode));
    strcpy(newNode->nama, nama);
    newNode->left = newNode->right = NULL;
    return newNode;
}

BSTNode* __bst__insert(BSTNode *root, char *value) {
    if (root == NULL) 
        return __bst__createNode(value);

    if (strcmp(root->nama, value) < 0)
        root->left = __bst__insert(root->left, value);
    else if (strcmp(root->nama, value) > 0)
        root->right = __bst__insert(root->right, value);
    return root;
}

BSTNode* __bst__search(BSTNode *root, char *value) {
    while (root != NULL) {
        if (strcmp(root->nama, value) < 0)
            root = root->left;
        else if (strcmp(root->nama, value) > 0)
            root = root->right;
        else return root;
    }
    return root;
}

bool bst_find(BST *bst, char *value) {
    BSTNode *temp = __bst__search(bst->_root, value);
    if (temp == NULL)
        return false;
    
    if (temp->nama == value)
        return true;
    else return false;
}

void bst_insert(BST *bst, char *value) {
    if (!bst_find(bst, value)) {
        bst->_root = __bst__insert(bst->_root, value);
        bst->_size++;
    }
}

void searchChild(BST *bst, char *value){
    BSTNode *temp = __bst__search(bst->_root, value);
    if(temp != NULL) {
        if(temp->left != NULL && temp->right != NULL)
            printf("%s %s", temp->left->nama, temp->right->nama);
        else if(temp->left != NULL && temp->right == NULL)
            printf("%s -", temp->left->nama);
        else if(temp->left == NULL && temp->right != NULL)
            printf("- %s", temp->right->nama);
        else printf("diManakah Anak-aNakkuu ;(");
    }
}

void searchParent(BST *bst, char *value){
    BSTNode *temp = bst->_root;
    if(!strcmp(temp->nama, value)) {
        printf("Aku adalah sesepuh keluarga Santoso");
        return;
    }
    while(temp != NULL) {
        if(temp->right != NULL&& !strcmp(temp->right->nama, value)) {
            printf("%s", temp->nama);
            return;
        }
        if(temp->left != NULL && !strcmp(temp->left->nama, value)) {
            printf("%s", temp->nama);
            return;
        }

        if(strcmp(temp->nama, value) > 0)
            temp = temp->right;
        else if(strcmp(temp->nama, value) < 0)
            temp = temp->left;  
    }
}

int main(){
    BST set;
    bst_init(&set);
    char nama[50000], cmd[50000], cek[50000];
    int t, n;
    scanf("%d %d", &t, &n);
    while(t--) {
        scanf("%s", nama);
        bst_insert(&set, nama);
    }
    while(n--) {
        scanf("%s", cmd);
        if(!strcmp(cmd, "anak")){
            scanf("%s", cek);
            searchChild(&set, cek);
            puts("");
        }
        else if(!strcmp(cmd, "ibu")){
            scanf("%s", cek);
            searchParent(&set, cek);
            puts("");
        }
    }
}