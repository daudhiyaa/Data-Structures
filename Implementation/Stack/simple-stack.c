/**
 * @date 2022-04-24
 * 
 * another Stack Implementation
 * For C
 * 
 * !! NOTE !!
 * see how it is used in the main() function
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX 10

typedef struct _STACK{
    int top;
    int data[MAX];
}STACK;

STACK tumpuk;

void inisialisasi(){
    tumpuk.top = -1;
}

int isFull(){
    return(tumpuk.top==MAX-1) ? 1 : 0;
}

int isEmpty(){
    return(tumpuk.top==-1) ? 1 : 0;
}

void Push(int value){
    tumpuk.data[++tumpuk.top]=value;
}

void Pop(){
    printf("Data ter-ambil %d\n", tumpuk.data[tumpuk.top]);
    tumpuk.top--;
}

void tampilStack(){
    for(int i = tumpuk.top;i>=0;i--){
        printf("Data stack ke-%d adalah %d\n", i, tumpuk.data[i]);
    }
}

void masukkanData(){
    int value;
    while (!isFull()){
        scanf("%d", &value);
        Push(value);
    }
}

void ambilData(){
    while (!isEmpty())
        Pop();
}

int main(){
    inisialisasi();
    masukkanData();
    tampilStack();
    ambilData();

    return 0;
}