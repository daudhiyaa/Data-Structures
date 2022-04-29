/**
 * fundamental code written by : Bayu Laksana
 * @date 2019-02-29
 * 
 * @editor Daud Dhiya' Rozaan
 * @date 2022-04-11
 */

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#define MAX 15

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
    PQueueNode *newNode =  (PQueueNode*) malloc (sizeof(PQueueNode));
    strcpy(newNode->data,value);
    pqueue->_size++;
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
        while(temp->next != NULL && strcmp(temp->next->data,value)<0)
            temp = temp->next;
        newNode->next = temp->next;
        temp->next = newNode;
    }
}

void pqueue_pop(PriorityQueue *pqueue)
{
    if (!pqueue_isEmpty(pqueue)) {
        PQueueNode *temp = pqueue->_top;
        pqueue->_top = pqueue->_top->next;
        free(temp);
    }
}

void pqueue_top(PriorityQueue *pqueue) {
    if (!pqueue_isEmpty(pqueue))
        printf("%s", pqueue->_top->data);
    else return;
}

int main(int argc, char const *argv[]){
    PriorityQueue myPque;
    pqueue_init(&myPque);

    int j=0;
    char temp[20005], nama[15];
    while(scanf(" %[^\n]", temp)!=EOF){
        int len = strlen(temp);
        for(int i=0;i<len;i++){
            if(i == len-1 && temp[i] > 64){
                nama[j] = temp[i];
                j++;
            }

            if(temp[i] < 64|| i == len-1){
                if(j) pqueue_push(&myPque, nama);
                j=0;
                memset(nama, 0, strlen(nama));
            }
            else{
                nama[j] = temp[i];
                j++;
            }
        }
    }

    PQueueNode *temporary = myPque._top;
    int idx = 1;
    while(temporary != NULL){
        printf("%d. %s\n", idx, temporary->data);
        temporary = temporary->next;
        idx++;
    }
    
    idx = 1;
    temporary = myPque._top;
    while(temporary != NULL){
        printf("%s", temporary->data);
        if(idx<myPque._size) printf("_");
        idx++;
        temporary = temporary->next;
    }
    return 0;
}