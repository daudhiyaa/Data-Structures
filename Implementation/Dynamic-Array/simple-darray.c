/**
 * @date 2022-04-24
 * 
 * another Dynamic Array Implementation
 * For C
 * 
 * !! NOTE !!
 * see how it is used in the main() function
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    char *name;
    int age;
}object;

typedef struct {
    object *arr;
    int size, capacity;
}d_array;

void init(d_array *darray){
    darray->capacity = 2;
    darray->size = 0u;
    darray->arr = (object*) malloc(sizeof(sizeof(object) * darray->capacity));
}

void add(d_array *darray, char *name, int value){
    if(darray->size == darray->capacity){
        darray->capacity <<=1;
        darray->arr = (object*) realloc(darray->arr, sizeof(sizeof(object) * darray->capacity));
    }
    darray->arr[darray->size].name = name;
    darray->arr[darray->size].age = value;
    darray->size++;
}

int main(){
    d_array tes;
    init(&tes);
    add(&tes, "Aku", 21);
    printf("%s %d\n", tes.arr[0].name, tes.arr[0].age);
}