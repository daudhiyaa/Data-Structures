/**
 * @author Bayu Laksana
 * @date 2019-01-22
 * 
 * ADT List Implementation (Dynamic Array)
 * -- with string data-type
 * For C
 * 
 * @editor Zydhan Linnar Putra
 * @date 2022-04-23
 * 
 * !! NOTE !!
 * see how it is used in the main() function
 */

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

typedef struct dynamicarr_t {
    // Dibuat jadi array 2D
    char **_arr;
    unsigned _size, _capacity;
} DynamicArray;

void dArray_init(DynamicArray *darray){
    darray->_capacity = 2u;
    darray->_size = 0u;
    // Alokasi memori buat array 2D dengan ukuran 2
    darray->_arr = (char **) malloc(sizeof(char *) * 2);
    // Di setiap index array 2D, alokasikan memori sebesar 101x ukuran char (1-nya untuk '\0')
    for (int i=0; i<2; i++) {
        darray->_arr[i] = (char *) malloc(sizeof(char) * 101);
    }
}

bool dArray_isEmpty(DynamicArray *darray) {
    return (darray->_size == 0);
}

void dArray_pushBack(DynamicArray *darray, char * value){
    if (darray->_size + 1 > darray->_capacity) {
        unsigned it;
        darray->_capacity *= 2;

        // Mirip seperti yang ada di init
        char **newArr = (char**) malloc(sizeof(char *) * darray->_capacity);

        // Batasi juga 101
        for (it=0; it < darray->_size; ++it)
            newArr[it] = (char *) malloc(sizeof(char) * 101);
        for (it=0; it < darray->_size; ++it)
            // Assignment diganti dengan strcpy
            strcpy(newArr[it], darray->_arr[it]);
        
        char **oldArray = darray->_arr;
        darray->_arr = newArr;
        free(oldArray);
    }
    darray->_arr[darray->_size++] = value;
}

void dArray_popBack(DynamicArray *darray) {
    if (!dArray_isEmpty(darray)) darray->_size--;
    else return;
}

// change the data-type into char *
char * dArray_back(DynamicArray *darray) {
    if (!dArray_isEmpty(darray))
        return darray->_arr[darray->_size-1];
    else return 0;
}

// change the data-type into char *
char * dArray_front(DynamicArray *darray) {
    if (!dArray_isEmpty(darray))
        return darray->_arr[0];
    else return 0;
}

void dArray_setAt(DynamicArray *darray, unsigned index, char * value){
    if (!dArray_isEmpty(darray)) {
        // Assignment changed with strcpy
        if (index >= darray->_size)
            strcpy(darray->_arr[darray->_size-1], value);
        else strcpy(darray->_arr[index], value);
    }
}

// change the data-type into char *
char * dArray_getAt(DynamicArray *darray, unsigned index){
    if (!dArray_isEmpty(darray)) {
        if (index >= darray->_size)
            return darray->_arr[darray->_size-1];
        else return darray->_arr[index];
    }
    return NULL;
}

int main(){
    // Create DynamicArray object
    DynamicArray myArray;
    // init
    dArray_init(&myArray);

    // myArray => [11, 14, 17, 23]
    dArray_pushBack(&myArray, "11");
    dArray_pushBack(&myArray, "14");
    dArray_pushBack(&myArray, "17");
    dArray_pushBack(&myArray, "23");

    // isi myArray => [11, 14, 17]
    dArray_popBack(&myArray);

    for (unsigned i = 0; i < myArray._size; ++i) {
        printf("%s\n", dArray_getAt(&myArray, i));
    }

    while (!dArray_isEmpty(&myArray)) {
        printf("%s\n", dArray_back(&myArray));
        dArray_popBack(&myArray);
    }
    return 0;
}