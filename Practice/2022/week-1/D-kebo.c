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
 
typedef struct stackNode_t {
    short data;
    struct stackNode_t *next;
} StackNode;
 
typedef struct stack_t {
    StackNode *_top;
    unsigned _size;
} Stack;
 
void stack_init(Stack *stack) {
    stack->_size = 0;
    stack->_top = NULL;
}
 
bool stack_isEmpty(Stack *stack) {
    return (stack->_top == NULL);
}
 
void stack_push(Stack *stack, short value) {
    StackNode *newNode = (StackNode *) malloc(sizeof(StackNode));
    if (newNode) {
        stack->_size++;
        newNode->data = value;
 
        if (stack_isEmpty(stack)) newNode->next = NULL;
        else newNode->next = stack->_top;
 
        stack->_top = newNode;
    }
}
 
void stack_pop(Stack *stack) {
    if (!stack_isEmpty(stack)) {
        StackNode *temp = stack->_top;
        stack->_top = stack->_top->next;
        free(temp);
        stack->_size--;
    }
}
 
short stack_top(Stack *stack) {
    if (!stack_isEmpty(stack))
        return stack->_top->data;
    return 0;
}
 
unsigned stack_size(Stack *stack) {
    return stack->_size;
}
 
int main(int argc, char const *argv[]){
    Stack myStack;
    
    short masuk[2][1001], keluar[1001];
    short kebo, lahan, i, j;
    
    for(j=0;j>=0;j++){
        scanf("%hi%hi", &kebo, &lahan);
        // if kebo = 0 and laha = 0, exit program
        if(kebo==0 && lahan==0) break;
        
        stack_init(&myStack);
        // set the memory of array
        memset(masuk, 0, sizeof(masuk[0]));
        memset(masuk, 0, sizeof(masuk[1]));
        memset(keluar, 0, sizeof(keluar));
        
        bool flag = true;
        for(i=0;i<kebo;i++){
            short datang, pergi;
            scanf("%hi%hi", &datang, &pergi);
            // if the arrival time exceeds the departure time
            if (datang >= pergi){
                flag = false;
                break;
            }

            masuk[0][datang]++;
            masuk[1][datang] = pergi;
            keluar[pergi]++;

            // if there is more than 1 buffalo
            if (masuk[0][datang] > 1 || keluar[pergi] > 1){
                flag = false;
                break;
            }
        }
 
        for (i=1;i<1001;i++) {
            // if land area is less than number of buffalo
            if (stack_size(&myStack) > lahan){
                flag = false;
                break;
            }
                
            if (stack_top(&myStack) == i)
                stack_pop(&myStack);
            
            if (masuk[0][i] == 1)
                stack_push(&myStack, masuk[1][i]);
        }

        // if in the end there are still buffalo left (that mean the stack isn't empty)
        if (!stack_isEmpty(&myStack)) 
            flag = false;

        if(flag) printf("Bagusla\n");
        else printf("Dah lah\n");
    }
    return 0;
}