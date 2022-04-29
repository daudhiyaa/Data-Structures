/**
 * @author Bayu Laksana
 * @date 2019-01-22
 * 
 * ADT Implementation (PriorityQueue using Linked List)
 * -- default: minimum priority
 * For C
 * 
 * PriorityQueue with unique string data-type
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

typedef struct pqueueNode_t {
    char data[100000];
    struct pqueueNode_t *next;
} PQueueNode;

typedef struct pqueue_t {
    PQueueNode *_top;
    unsigned _size;
} PriorityQueue;

void pqueue_init(PriorityQueue *pqueue){
    pqueue->_top = NULL;
    pqueue->_size = 0;
}

bool pqueue_isEmpty(PriorityQueue *pqueue) {
    return (pqueue->_top == NULL);
}

bool pqueue_find(PriorityQueue *pqueue, char value[]) {
    PQueueNode *temp = pqueue->_top;
    while (temp != NULL) {
        if (strcmp(value, temp->data)!=0)
            temp = temp->next;
        else if (strcmp(value, temp->data)==0) return true;
    }
    return false;
}

void pqueue_push(PriorityQueue *pqueue, char value[]){
    if(!pqueue_find(pqueue, value)){
        PQueueNode *temp = pqueue->_top;
        PQueueNode *newNode =  (PQueueNode*) malloc (sizeof(PQueueNode));
        strcpy(newNode->data, value);
        pqueue->_size++;
        newNode->next = NULL;

        if (pqueue_isEmpty(pqueue)){
            pqueue->_top = newNode;
            return;
        }

        if (strcmp(value, pqueue->_top->data)<0) {
            newNode->next = pqueue->_top;
            pqueue->_top = newNode;
        }
        else {
            while(temp->next != NULL && strcmp(temp->next->data,value)<0)
                temp = temp->next;
            newNode->next = temp->next;
            temp->next = newNode;
        }
    }
}

void pqueue_pop(PriorityQueue *pqueue){
    if (!pqueue_isEmpty(pqueue)) {
        PQueueNode *temp = pqueue->_top;
        pqueue->_top = pqueue->_top->next;
        free(temp);
    }
}

void pqueue_top(PriorityQueue *pqueue) {
    if (!pqueue_isEmpty(pqueue))
        printf("%s\n", pqueue->_top->data);
    return;
}

int main(int argc, char const *argv[]){
    PriorityQueue myPque;
    pqueue_init(&myPque);

    return 0;
}