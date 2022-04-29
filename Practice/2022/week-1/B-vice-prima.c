/**
 * fundamental code written by : Bayu Laksana
 * @date 2019-02-29
 * 
 * @editor Daud Dhiya' Rozaan
 * @date 2022-03-12
 */

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>

typedef struct dnode_t {
    short data;
    struct dnode_t *next, *prev;
} DListNode;

typedef struct deque_t {
    DListNode *_head, *_tail;
    unsigned _size;
} Deque;

DListNode* __dlist_createNode(short value){
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

void deq_pushFront(Deque *deque, short value){
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

void deq_pushBack(Deque *deque, short value){
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

    short n, bilangan, i, j,  prima = 0;
    bool stat = true;
    scanf("%hi", &n);

    for(i=0;i<n;i++){
        scanf("%hi", &bilangan);
        /**
         * check the number, is it prime or not.
         * when stat is true, the number is prime number,
         * otherwise, it's not
        */
        if(bilangan < 2)
            stat = false;
        else if(bilangan == 2)
            stat = true; 
        else{
            int akar = sqrt(bilangan);
            for(j=2; j<=akar; j++){
                if(bilangan%j == 0){
                    stat = false;
                    break;
                }
            }
        }
        
        /**
         * if number is prime number, push to deque from the front,
         * otherwise, push it from the back
         */
        if(!stat) // not prime number
            deq_pushBack(&mydeq, bilangan);
        else{ // prime number
            deq_pushFront(&mydeq, bilangan);
            prima++; // flag to count how many prime number
        }
    }

    /**
     * print the prime number by looping until how many prime number that found
     * note : print it from the front and than do the popFront
     */
    for(i=0;i<prima;i++){
        printf("%hi\n", deq_front(&mydeq));
        deq_popFront(&mydeq);
    }
    /**
     * after that, print the not prime number by looping until deque is empty
     * note : print it from the back and than do the popBack
     */
    while(!deq_isEmpty(&mydeq)){
        printf("%hi\n", deq_back(&mydeq));
        deq_popBack(&mydeq);
    }
    return 0;
}