/**
 * @author Bayu Laksana
 * @date 2019-01-22
 * 
 * ADT List Implementation (Doubly Linked List)
 * -- with string data-type
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

typedef struct dnode_t {
    char data[MAX];
    struct dnode_t *next, *prev;
} DListNode;

typedef struct dlist_t {
    DListNode *_head, *_tail;
    unsigned _size;
} List;

DListNode* __dlist_createNode(char value[]){
    DListNode *newNode = (DListNode*) malloc (sizeof(DListNode));
    if (!newNode) return NULL;
    strcpy(newNode->data,value);
    newNode->next = newNode->prev = NULL;
    return (DListNode*) newNode;
}

void dlist_init(List *list){
    list->_head = list->_tail = NULL;
    list->_size = (unsigned) 0;
}

bool dlist_isEmpty(List *list) {
    return (list->_head == NULL && list->_tail == NULL);
}

void dlist_pushFront(List *list, char value[]){
    DListNode *newNode = __dlist_createNode(value);
    if (newNode) {
        list->_size++;
        if (dlist_isEmpty(list)) {
            list->_head = list->_tail = newNode;
            return;
        }

        newNode->next = list->_head;
        list->_head->prev = newNode;
        list->_head = newNode;
    }
}

void dlist_pushBack(List *list, char value[]){
    DListNode *newNode = __dlist_createNode(value);
    if (newNode) {
        list->_size++;
        if (dlist_isEmpty(list)) {
            list->_head = newNode;
            list->_tail = newNode;
            return;
        }

        list->_tail->next = newNode;
        newNode->prev = list->_tail;
        list->_tail = newNode;
    }
}

void dlist_insertAt(List *list, unsigned index, char value[]){
    if (index <= 0) { 
        dlist_pushFront(list, value);
        return;
    }
    else if (index >= list->_size) {
        dlist_pushBack(list, value);
        return;
    }

    DListNode *newNode = __dlist_createNode(value);
    if (newNode) {
        if (dlist_isEmpty(list)) {
            list->_head = newNode;
            list->_tail = newNode;
            return;
        }

        DListNode *temp = list->_head;

        unsigned _i = 0;
        while (_i < index - 1 && temp->next != NULL) {
            temp = temp->next;
            _i++;
        }
        newNode->next = temp->next;
        newNode->prev = temp;

        if (temp->next)
            temp->next->prev = newNode;
        temp->next = newNode;
        list->_size++;
    }
}

void dlist_front(List *list) {
    if (!dlist_isEmpty(list))
        printf("%s\n", list->_head->data);
    return;
}

void dlist_back(List *list) {
    if (!dlist_isEmpty(list))
        printf("%s\n", list->_tail->data);
    return;
}

void dlist_popFront(List *list){
    if (!dlist_isEmpty(list)) {
        DListNode *temp = list->_head;
        if (list->_head == list->_tail) {
            list->_head = list->_tail = NULL;
            free(temp);
        }
        else {
            list->_head = list->_head->next;
            list->_head->prev = NULL;
            free(temp);
        }
        list->_size--;
    }
}

void dlist_popBack(List *list){
    if (!dlist_isEmpty(list)) {
        DListNode *temp;
        if (list->_head == list->_tail) {
            temp = list->_head;
            list->_head = list->_tail = NULL;
            free(temp);
        }
        else {
            temp = list->_tail;
            list->_tail = list->_tail->prev;
            list->_tail->next = NULL;
            free(temp);
        }
        list->_size--;
    }
}

int main(int argc, char const *argv[]){
    List myList;
    dlist_init(&myList);

    char temp[MAX];
    int n;
    scanf("%d", &n);
    while(n--){
        getchar();
        scanf("%[^\n]", temp);
        dlist_pushFront(&myList, temp);
    }
    
    while (!dlist_isEmpty(&myList)) {
        dlist_back(&myList);
        dlist_popBack(&myList);
    }
    return 0;
}
