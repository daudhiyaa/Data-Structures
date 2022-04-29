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
    if (temp == NULL) return false;

    if (strcmp(value, temp->data)==0) return true;
    else return false;
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

int main(int argc, char const *argv[]){
    PriorityQueue myPque;
    pqueue_init(&myPque);

    int j=0;
    char temp[2000005], nama[100000];
    while(scanf(" %[^\n]", temp)!=EOF){
        int len = strlen(temp);
        for(int i=0;i<len;i++){
            if(i == len-1 && temp[i] != ' '){
                nama[j] = temp[i];
                j++;
            }

            if(temp[i] == ' '|| i == len-1){
                if(j){
                    pqueue_push(&myPque, nama);
                    j=0;
                    memset(nama, 0, strlen(nama));
                }
            }
            else if(temp[i] > 64){
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
        if(idx<myPque._size) printf("--<3--");
        idx++;
        temporary = temporary->next;
    }
    return 0;
}