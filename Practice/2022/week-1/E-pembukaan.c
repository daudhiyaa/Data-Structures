/**
 * fundamental code written by : Bayu Laksana
 * @date 2019-02-29
 * 
 * @editor Daud Dhiya' Rozaan
 * @date 2022-03-12
 * 
 * note : I set the stack in the problem as deque in my solution,
 * cause in deque we can do pushBack and popBack, and there is tail and prev in deque
 */

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

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
    newNode->next = NULL;
    newNode->prev = NULL;
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
    // create (and init it) the deque object for every queue/stack
    Deque myQueue1, myQueue2, myQueue3;
    deq_init(&myQueue1);
    deq_init(&myQueue2);
    deq_init(&myQueue3);

    unsigned short q, i, j, 
                kode1 = 0, kode2 = 0, kode3 = 0; // this is the book code for every stack
    scanf("%hu", &q);
    char perintah[10];
    for(i=0;i<q;i++){
        scanf("%s", perintah);
        if(strcmp(perintah,"CETAK")==0){
            unsigned short n;
            scanf("%hu", &n);
            for(j=0;j<n;j++){
                kode1++;
                deq_pushFront(&myQueue1, kode1); // for 1st stack, push it from front
            }
            kode2 = kode1; // set the code 2 as code 1 at the last
        }
        else if(strcmp(perintah,"TTD")==0){
            unsigned short n;
            scanf("%hu", &n);
            for(j=0;j<n;j++){
                deq_pushBack(&myQueue2, kode2); // for 2nd stack, push it from back
                kode2--;
                deq_popFront(&myQueue1); // delete the data in 1st stack from the top
            }
            kode3 = kode2; // set the code 3 as code 2 at the last
        }
        else{ //SAMPUL
            unsigned short n;
            scanf("%hu", &n);
            for(j=0;j<n;j++){
                kode3++;
                deq_pushFront(&myQueue3, kode3); // for 3rd stack, push it from front
                deq_popBack(&myQueue2); // delete the data in 2nd stack from the top
            }
        }
    }

    // print every stack data until empty
    printf("tumpukan 1:");
    while (!deq_isEmpty(&myQueue1)) { 
        printf(" %hu", deq_back(&myQueue1)); // print 1st stack from the back
        deq_popBack(&myQueue1);
    }
    printf("\ntumpukan 2:");
    while (!deq_isEmpty(&myQueue2)) {
        printf(" %hu", deq_front(&myQueue2)); // print 2nd stack from the front
        deq_popFront(&myQueue2);
    }
    printf("\ntumpukan 3:");
    while (!deq_isEmpty(&myQueue3)) {
        printf(" %hu", deq_back(&myQueue3)); // print 3rd stack from the back
        deq_popBack(&myQueue3);
    }
    return 0;
}