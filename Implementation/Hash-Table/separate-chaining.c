/**
 * this sourcecode taken from : 
 * https://www.log2base2.com/algorithms/searching/open-hashing.html
 * 
 * Hash Table Implementation (Separate Chaining)
 * -- with int data-type
 * For C
 * 
 * @editor Daud Dhiya' Rozaan
 * @date 2022-04-23
 * 
 * !! NOTE !!
 * see how it is used in the main() function
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define size 7

struct node{
    int data;
    struct node *next;
}*chain[size];

void init(){
    for(int i = 0; i < size; i++) 
        chain[i] = NULL;
}

bool ketemu(int value){
    int key = value % size;
    struct node *temp = chain[key];
    while(temp) {
        if(temp->data == value) return true;
        temp = temp->next;
    }
    return false;
}

void insert(int value){ 
    struct node *newNode = malloc(sizeof(struct node));
    newNode->data = value;
    newNode->next = NULL;

    //calculate hash key
    int key = value % size;

    if(chain[key] == NULL) chain[key] = newNode;
    else {
        struct node *temp = chain[key];
        while(temp->next) 
            temp = temp->next;
        temp->next = newNode;
    }
}

void del(int value){
    if(!ketemu(value))
        printf("\nData tidak ditemukan\n");
    else{
        int key = value % size;
        struct node *temp = chain[key], *dealloc;
        while(temp != NULL) {
            if(temp->data == value) {
                dealloc = temp;
                temp = temp->next;
                free(dealloc);
                printf("\nData berhasil dihapus\n");
                break;
            }
            temp = temp->next;
        }
    }
}

void print(){
    for(int i = 0; i < size; i++) {
        struct node *temp = chain[i];
        printf("chain[%d] : ",i);
        while(temp) {
            printf("%d -> ",temp->data);
            temp = temp->next;
        }
        printf("NULL\n");
    }
}

int main(){
    init();

    insert(7);
    insert(0);
    insert(3);
    insert(10);
    insert(4);
    insert(5);
    print();

    del(1);
    del(10);
    puts("");
    print();

    return 0;
}