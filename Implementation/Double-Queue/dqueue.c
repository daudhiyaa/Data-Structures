/**
 * @author Bayu Laksana
 * @date 2019-01-22
 * 
 * ADT List Implementation (Double-ended Queue)
 * -- with int data-type
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

typedef struct dnode_t {
    int data;
    struct dnode_t *next, *prev;
} DListNode;

typedef struct deque_t {
    DListNode *_head, *_tail;
    unsigned _size;
} Deque;

DListNode* __dlist_createNode(int value){
    DListNode *newNode = (DListNode*) malloc (sizeof(DListNode));
    if (!newNode) return NULL;
    newNode->data = value;
    newNode->next = newNode->prev = NULL;
    return (DListNode*) newNode;
}

void deq_init(Deque *deque){
    deque->_head = deque->_tail = NULL;
    deque->_size = (unsigned) 0;
}

bool deq_isEmpty(Deque *deque) {
    return (deque->_head == NULL && deque->_tail == NULL);
}

void deq_pushFront(Deque *deque, int value){
    DListNode *newNode = __dlist_createNode(value);
    if (newNode) {
        deque->_size++;
        if (deq_isEmpty(deque)) {
            deque->_head = newNode;
            deque->_tail = newNode;
            return;
        }

        newNode->next = deque->_head;
        deque->_head->prev = newNode;
        deque->_head = newNode;
    }
}

void deq_pushBack(Deque *deque, int value){
    DListNode *newNode = __dlist_createNode(value);
    if (newNode) {
        deque->_size++;
        if (deq_isEmpty(deque)) {
            deque->_head = newNode;
            deque->_tail = newNode;
            return;
        }

        deque->_tail->next = newNode;
        newNode->prev = deque->_tail;
        deque->_tail = newNode;
    }
}

int deq_front(Deque *deque) {
    if (!deq_isEmpty(deque))
        return (deque->_head->data);
    return 0;
}

int deq_back(Deque *deque) {
    if (!deq_isEmpty(deque)) 
        return (deque->_tail->data);
    return 0;
}

void deq_popFront(Deque *deque){
    if (!deq_isEmpty(deque)) {
        DListNode *temp = deque->_head;
        if (deque->_head == deque->_tail) {
            deque->_head = deque->_tail = NULL;
            free(temp);
        }
        else {
            deque->_head = deque->_head->next;
            deque->_head->prev = NULL;
            free(temp);
        }
        deque->_size--;
    }
}

void deq_popBack(Deque *deque){
    if (!deq_isEmpty(deque)) {
        DListNode *temp;
        if (deque->_head == deque->_tail) {
            temp = deque->_head;
            deque->_head = deque->_tail = NULL;
            free(temp);
        }
        else {
            temp = deque->_tail;
            deque->_tail = deque->_tail->prev;
            deque->_tail->next = NULL;
            free(temp);
        }
        deque->_size--;
    }
}

int main(int argc, char const *argv[]){
    Deque mydeq;
    deq_init(&mydeq);

    deq_pushBack(&mydeq, 1);
    deq_pushBack(&mydeq, 12);
    deq_pushBack(&mydeq, 6);
    deq_pushBack(&mydeq, 7);
    deq_pushBack(&mydeq, 2);

    deq_pushFront(&mydeq, 11);
    deq_pushFront(&mydeq, 8);
    deq_pushFront(&mydeq, 0);

    deq_popBack(&mydeq);
    deq_popFront(&mydeq);

    while (!deq_isEmpty(&mydeq)) {
        printf("%d ", deq_front(&mydeq));
        deq_popFront(&mydeq);
    }
    puts("");
    return 0;
}