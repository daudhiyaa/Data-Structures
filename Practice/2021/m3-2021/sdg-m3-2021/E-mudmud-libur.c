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

struct Data{
    char str[30];
};

typedef struct pqueueNode_t {
    char data[30];
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

    int n;
    scanf("%d", &n);
    struct Data inp[n];
    for(int i=0;i<n;i++){
        scanf("%s", inp[i].str);
    }

    int t, flag = 0, sum = 0;
    scanf("%d", &t);
    char tes[30];
    bool gagal = true;
    for(int k=1;k<=t;k++){
        scanf("%s", tes);
        int len = strlen(tes);
        for(int j=0;j<n;j++){
            for (int i=0;i<len;i++) {
                if(tes[i] == inp[j].str[i]){
                    flag++;
                    gagal = false;
                }
            }
            if(flag==len){
                pqueue_push(&myPque, inp[j].str);
                sum++;
            }
            flag = 0;
        }
        printf("Kasus #%d: ", k);
        if(gagal)
            printf("Tidak ada hasil\n");
        else{
            printf("%d\n", sum);
            PQueueNode *temporary = myPque._top;
            while(temporary != NULL){
                printf("%s\n", temporary->data);
                temporary = temporary->next;
            }
        }
        pqueue_init(&myPque);
        sum = 0; gagal= true;
    }
    return 0;
}