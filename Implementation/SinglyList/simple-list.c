/**
 * @date 2022-04-24
 * 
 * another Singly Linked List Implementation
 * For C
 * 
 * !! NOTE !!
 * see how it is used in the main() function
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct node{
    int nim;
    struct Mahasiswa *next;
}Mahasiswa;

void init(Mahasiswa **p){
    *p = NULL;
}

Mahasiswa *alokasi(int nim){
    Mahasiswa *P;
    P = (Mahasiswa*) malloc(sizeof(Mahasiswa));
    if(P!=NULL){
        P->next = NULL;
        P->nim = nim;
    }
    return (P);
}

void Add(Mahasiswa **p, int nim){
    *p = alokasi(nim);
    printf("%d\n", (*p)->nim);
}

int main(){
    Mahasiswa *head;
    init(&head);
    Add(&head, 20);
}