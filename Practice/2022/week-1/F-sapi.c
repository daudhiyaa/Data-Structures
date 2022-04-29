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
#include <string.h>

typedef struct pqueueNode_t {
    unsigned short no, data, kg;
    struct pqueueNode_t *next;
} PQueueNode;

typedef struct pqueue_t {
    PQueueNode *_top;
    unsigned _size;
}PriorityQueue;

void pqueue_init(PriorityQueue *pqueue)
{
    pqueue->_top = NULL;
    pqueue->_size = 0;
}

bool pqueue_isEmpty(PriorityQueue *pqueue) {
    return (pqueue->_top == NULL);
}

/**
 * as described in the problem,
 * Priority is determined by the cow's age, 
 * if the age is same, Priority is determined by the cow's weight
 * 
 * @param num is cow's id
 * @param value is cow's age
 * @param berat is cow's weight
 */

void pqueue_push(PriorityQueue *pqueue, unsigned short num, unsigned short value, unsigned short berat){
    PQueueNode *temp = pqueue->_top;
    PQueueNode *newNode = (PQueueNode*) malloc (sizeof(PQueueNode));
    newNode->no = num;
    newNode->data = value;
    newNode->kg = berat;
    newNode->next = NULL;

    if(pqueue_isEmpty(pqueue)){
        pqueue->_top = newNode;
        return;
    }

    // if cow's age is more than cow's age in the top of pqueue
    if(value > pqueue->_top->data){
        newNode->next = pqueue->_top;
        pqueue->_top = newNode;
    }
    /**
     * if cow's age is same as cow's age in the top of pqueue,
     * but cow's weight is more than cow's weight in the top of pqueue
     */
    else if(value == pqueue->_top->data && berat > pqueue->_top->kg){
        newNode->next = pqueue->_top;
        pqueue->_top = newNode;
    }
    else{
        // while cow's age is still less than cow's age in the pqueue, do the loop until meet another condition
        while(temp->next != NULL && temp->next->data > value){
            temp = temp->next;
        }
        /**
         * if cow's age is same as cow's age in the some node in pqueue,
         * but cow's weight is more than cow's weight in the some node in pqueue
         */
        if(temp->next != NULL && value == temp->next->data && berat > temp->next->kg){
            newNode->next = temp->next;
            temp->next = newNode;
        }
        /**
         * if cow's age is same as cow's age in the some node in pqueue,
         * but cow's weight is still less than cow's weight in the some node in pqueue,
         * do next one more time
         */
        else if(temp->next != NULL && value == temp->next->data && berat < temp->next->kg){
            temp = temp->next;
            newNode->next = temp->next;
            temp->next = newNode;
        }
        else{
            newNode->next = temp->next;
            temp->next = newNode;
        }
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

int pqueue_top(PriorityQueue *pqueue) {
    if (!pqueue_isEmpty(pqueue))
        return pqueue->_top->no;
    else return 0;
}

int main(int argc, char const *argv[])
{
    PriorityQueue myPque;
    pqueue_init(&myPque);

    unsigned short n, i, id, umur, mass, beli;
    scanf("%hu", &n);
    char perintah[10];
    for(i=0;i<n;i++){
        scanf("%s", perintah);
        if(strcmp(perintah, "DAFTAR")==0){ // enter the cow's data to pqueue
            scanf("%hu%hu%hu", &id, &umur, &mass);
            pqueue_push(&myPque, id, umur, mass);
        }
        else{ // BELI 
            unsigned short j = 0;
            scanf("%hu", &beli);
            // looping until pqueue is empty or or until the number of cows purchased
            while (!pqueue_isEmpty(&myPque) && j!=beli){
                pqueue_pop(&myPque);
                j++;
            }
        }
    }
    if(pqueue_isEmpty(&myPque)) // if pqueue is empty, print 0
        printf("0");

    // else, print the data in pqueue until pqueue is empty
    while (!pqueue_isEmpty(&myPque)) {
        printf("%hu ", pqueue_top(&myPque));
        pqueue_pop(&myPque);
    }
    return 0;
}