/**
 * this sourcecode taken from : 
 * https://www.sanfoundry.com/c-program-implement-hash-tables-with-double-hashing/
 * 
 * Hash Table Implementation (Double Hashing)
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
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
int max = 11, size = 0, prime = 3;

struct data {
    int key, value;
};

struct hashtable_item {
    int flag; 
    struct data *item;
}*array;

/* returns largest prime number less than size of array */
int get_prime() {
    for (int i = max - 1; i >= 1; i--) {
        bool flag = true;
        int akar = sqrt(i);
        for (int j = 2; j <= akar; j++) {
            if (i % j == 0){
                flag = false;
                break;
            }
        }
        if (flag) return i;
    }
    return 3;
}

int hashcode1(int key) {
    return (key % max);
}

int hashcode2(int key) {
    return (prime - (key % prime));
}

void insert(int key, int value) {
    int hash1 = hashcode1(key);   
    int hash2 = hashcode2(key);
    int index = hash1;

    struct data *new_item = (struct data*) malloc(sizeof(struct data));
    new_item->key = key;
    new_item->value = value;

    if (size == max){
        printf("\nHash Table is full, cannot insert more items \n");
        return;
    }

    /* probing through other array elements */
    while (array[index].flag == 1) {
        if (array[index].item->key == key) {
            printf("\nKey already present, hence updating its value");
            array[index].item->value = value;
            return;
        }

    	index = (index + hash2) % max; 
        if (index == hash1){
            printf("\nAdd is failed");
            return;
        }
        printf("\nprobing\n");
    }
    array[index].item = new_item;
    array[index].flag = 1;
    size++;
    printf("\nKey (%d) has been inserted", key);
}

void remove_element(int key) {
    int hash1 = hashcode1(key);
    int hash2 = hashcode2(key);
    int index = hash1;
    
    if (size == 0) {
        printf("\nHash Table is empty");
        return;
    }

    while (array[index].flag != 0) {
        if (array[index].flag == 1  &&  array[index].item->key == key){
            array[index].item = NULL;
            array[index].flag = 2;
            size--;
            printf("\nKey (%d) has been removed", key);
            return;
        }

    	index = (index + hash2) % max;
        if (index == hash1)break;
    }
    printf("\nKey (%d) does not exist", key);
}

void init_array() {
    for(int i = 0; i < max; i++) {
        array[i].item = NULL;
        array[i].flag = 0;
    }
    prime = get_prime();
}

void display() {
    for (int i = 0; i < max; i++){
        if (array[i].flag != 1)
            printf("\nArray[%d] has no elements", i);
        else
            printf("\nArray[%d] has elements -> Key (%d) and Value (%d)", i, array[i].item->key, array[i].item->value);
    }
}

int main() {
    int choice, key, value, n, c;
    array = (struct hashtable_item*) malloc(max * sizeof(struct hashtable_item));
    init_array();
    printf("Implementation of Hash Table in C with Double Hashing.\n");
    do {
        printf("\nMENU-:"
                "\n1.Inserting item in the Hash Table" 
                "\n2.Removing item from the Hash Table" 
                "\n3.Check the size of Hash Table" 
                "\n4.Display Hash Table"
                "\n\nPlease enter your choice : ");
        scanf("%d", &choice);
        switch(choice) {
            case 1:
                printf("\nEnter key and value : ");
                scanf("%d %d", &key, &value);
                insert(key, value);
                break;
            case 2:
                printf("\nEnter the key to delete :");
                scanf("%d", &key);
                remove_element(key);
                break;
            case 3:
                printf("Size of Hash Table is : %d", size);
                break;
            case 4: display(); break;
            default: return 0; break;
        }
        printf("\n\nDo you want to continue (press 1 for yes) : ");
        scanf("%d", &c);
    }while(c == 1);
}