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

typedef struct snode_t {
    unsigned short data;
    struct snode_t *next;
} SListNode;

typedef struct slist_t {
    unsigned _size;
    SListNode *_head;
} SinglyList;

void slist_init(SinglyList *list){
    list->_head = NULL;
    list->_size = 0;
}

bool slist_isEmpty(SinglyList *list) {
    return (list->_head == NULL);
}

void slist_pushFront(SinglyList *list, unsigned short value) {
    SListNode *newNode = (SListNode*) malloc(sizeof(SListNode));
    if (newNode) {
        list->_size++;
        newNode->data = value;

        if (slist_isEmpty(list)) newNode->next = NULL;
        else newNode->next = list->_head;
        list->_head = newNode;
    }
}

void slist_popFront(SinglyList *list){
    if (!slist_isEmpty(list)) {
        SListNode *temp = list->_head;
        list->_head = list->_head->next;
        free(temp);
        list->_size--;
    }
}

void slist_pushBack(SinglyList *list, int value){
    SListNode *newNode = (SListNode*) malloc(sizeof(SListNode));
    if (newNode) {
        list->_size++;
        newNode->data = value;
        newNode->next = NULL;
        
        if (slist_isEmpty(list)) 
            list->_head = newNode;
        else {
            SListNode *temp = list->_head;
            while (temp->next != NULL) 
                temp = temp->next;
            temp->next = newNode;
        }
    }
}

void slist_popBack(SinglyList *list)
{
    if (!slist_isEmpty(list)) {
        SListNode *nextNode = list->_head->next;
        SListNode *currNode = list->_head;

        if (currNode->next == NULL) {
            free(currNode);
            list->_head = NULL;
            return;
        }

        while (nextNode->next != NULL) {
            currNode = nextNode;
            nextNode = nextNode->next;
        }
        currNode->next = NULL;
        free(nextNode);
        list->_size--;
    }
}

void slist_insertAt(SinglyList *list, unsigned short index, unsigned short value)
{
    if (slist_isEmpty(list) || index >= list->_size) {
        slist_pushBack(list, value);
        return;    
    }
    else if (index <= 0) {
        slist_pushFront(list, value);
        return;
    }
    
    SListNode *newNode = (SListNode*) malloc(sizeof(SListNode));
    if (newNode) {
        SListNode *temp = list->_head;
        int _i = 0;
        while (temp->next != NULL && _i < index-1) {
            temp = temp->next;
            _i++;
        }
        newNode->data = value;
        newNode->next = temp->next;
        temp->next = newNode;
        list->_size++;
    }
}

int slist_front(SinglyList *list){
    if (!slist_isEmpty(list))
        return list->_head->data;
    return 0;
}

int slist_getAt(SinglyList *list, unsigned short index){
    if (!slist_isEmpty(list)) {
        SListNode *temp = list->_head;
        int _i = 0;
        while (temp->next != NULL && _i < index) {
            temp = temp->next;
            _i++;
        }
        return temp->data;
    }
    return 0;
}

int main(int argc, char const *argv[]){
    SinglyList myList;
    slist_init(&myList);

    unsigned short b, n, x, i, flag = 0, temp, berhasil = 0;
    bool gagal = false; // boolean to determine failure, when it's true, then failure occurs

    scanf("%hu", &b);
    for(i=0;i<b;i++){
        scanf("%hu", &x);
        slist_pushBack(&myList, x);
    }
    scanf("%hu", &n); // input the divisor

    for(i=0;i<b-1;i++){
        temp = slist_getAt(&myList, i);
        if(temp%n==0){
            flag++;
            if(temp+flag==slist_getAt(&myList, i+1)){
                // if failure occurs, set the boolean to true, and then stop the loop
                gagal=true;
                break;
            }
            slist_insertAt(&myList, i+1, temp+flag);
            berhasil++;
            b++;
        }
    }

    /* if success happens more than n (many number that IKKI has) */
    if(berhasil>n){
        slist_popFront(&myList);
        slist_popBack(&myList);
        printf("#NICEVICE\n");
        while (myList._head != NULL) {
            printf("%hu ", slist_front(&myList));
            slist_popFront(&myList);
        }
    }
    // if failure occurs
    else if(berhasil==0 || gagal)
        printf("VICE!!!\n");
    /* if success happens less than n (many number that IKKI has) and not fail */
    else if(berhasil<=n && !gagal){
        printf(":(\n");
        while (myList._head != NULL) {
            printf("%hu ", slist_front(&myList));
            slist_popFront(&myList);
        }
    }
    return 0;
}