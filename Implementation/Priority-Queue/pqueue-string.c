/**
 * @author Bayu Laksana
 * @date 2019-01-22
 * 
 * ADT Implementation (PriorityQueue using Linked List)
 * -- default: minimum priority
 * For C
 * 
 * PriorityQueue for string data-type
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
#define MAX 100

typedef struct pqueueNode_t {
    char data[MAX];
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

void pqueue_push(PriorityQueue *pqueue, char value[]){
    PQueueNode *temp = pqueue->_top;
    PQueueNode *newNode = (PQueueNode*) malloc (sizeof(PQueueNode));
    strcpy(newNode->data,value);
    newNode->next = NULL;

    if (pqueue_isEmpty(pqueue)) {
        pqueue->_top = newNode;
        return;
    }

    if (strcmp(value, pqueue->_top->data)<0) {
        newNode->next = pqueue->_top;
        pqueue->_top = newNode;
    }
    else {
        while(temp->next != NULL && strcmp(value, pqueue->_top->data)<0)
            temp = temp->next;
        newNode->next = temp->next;
        temp->next = newNode;
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

    char temp[MAX];
    int n;
    scanf("%d", &n);
    for(int i=0;i<n;i++){
        getchar();
        scanf("%[^\n]", temp);
        pqueue_push(&myPque, temp);
    }
    
    while (!pqueue_isEmpty(&myPque)) {
        pqueue_top(&myPque);
        pqueue_pop(&myPque);
    }

    return 0;
}