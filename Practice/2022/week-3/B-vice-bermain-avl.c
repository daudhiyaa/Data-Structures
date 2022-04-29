/**
 * fundamental code written by : ABDUR ROCHMAN
 * @date 2020-03-28
 * 
 * @editor Daud Dhiya' Rozaan
 * @date 2022-04-18
 */

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

typedef struct AVLNode_t{
    int data, height;
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

bool avl_isEmpty(AVL *avl) {
    return avl->_root == NULL;
}

AVLNode* _search(AVLNode *root, int value) {
    while (root != NULL) {
        if (value < root->data) root = root->left;
        else if (value > root->data) root = root->right;
        else return root;
    }
    return root;
}

bool avl_find(AVL *avl, int value) {
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

AVLNode* _avl_createNode(int value) {
    AVLNode *newNode = (AVLNode*) malloc(sizeof(AVLNode));
    newNode->data = value;
    newNode->height=1;
    newNode->left = newNode->right = NULL;
    return newNode;
}

AVLNode* _insert_AVL(AVL *avl,AVLNode* node,int value) {
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

void avl_insert(AVL *avl,int value){
    if(!avl_find(avl,value)){
        avl->_root=_insert_AVL(avl,avl->_root,value);
        avl->_size++;
    }
}

/**
 * searchParent function is function to determine the parent of a node, 
 * return the parent->data as int data-type
 */
int searchParent(AVL *avl, int value){
    AVLNode *temp = avl->_root;
    while(temp != NULL) {
        if(temp->right != NULL && temp->right->data == value){
            return temp->data; break;
        }
        else if(temp->left != NULL && temp->left->data == value){
            return temp->data; break;
        }

        if(value > temp->data)
            temp = temp->right;
        else if(value < temp->data)
            temp = temp->left;
    }
    return 0;
}

int size = 0; // it's just like a flag
void preorder(AVLNode *root, AVL *avl) {
    if (root) {
        printf("%d", root->data);
        size++;
        // if size is still smaller than avl_size, print a certain message
        if(size < avl->_size) printf(":"); 
        preorder(root->left, avl);
        preorder(root->right, avl);
    }
}

int main(){
    AVL avlku;
    avl_init(&avlku);
    int nilai, tes;
    char command[25], cmd[25];
    for(int i=0;i>=0;i++){ // infinite loop, until the "cmd" is finish
        scanf("%s", command);
        if(strcmp(command, "more:")==0){
            scanf("%s", cmd);
            if(strcmp(cmd, "requiem")==0){
                scanf("%d", &tes);
                printf("requiem:\n");
                printf("%d\n", tes);

                int y1, y2;
                /* search the parent of "tes", if "tes" isn't root*/
                if(avlku._root->data != tes){
                    y1 = searchParent(&avlku, tes);
                    printf("%d\n", y1);
                }
                /**
                 * search the parent of "y1" (or we can say it grandparent of "tes"), 
                 * if "y1" isn't root
                 */
                if(avlku._root->data != y1){
                    y2 = searchParent(&avlku, y1);
                    printf("%d\n", y2);
                }
            }
            else{ // finish, print the data in avl by preorder traversal
                printf("list:\n");
                preorder(avlku._root, &avlku);
                break; // finishing the loop & exit program
            }
        }
        else if(strcmp(command, "add")==0){ // add value to avl tree
            scanf("%d", &nilai);
            avl_insert(&avlku, nilai);
        }
    }
}