/**
 * @author Bayu Laksana
 * @date 2019-01-22
 * 
 * ADT Implementation (Stack)
 * -- with string data-type
 * For C
 * 
 * @editor Daud Dhiya' Rozaan
 * @date 2022-04-23
 * 
 * !! NOTE !!
 * see how it is used in the main() function 
 */

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#define MAX 100

typedef struct stackNode_t {
    char data[MAX];
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

void stack_push(Stack *stack, char value[MAX]) {
    StackNode *newNode = (StackNode*) malloc(sizeof(StackNode));
    if (newNode) {
        stack->_size++;
        strcpy(newNode->data,value);
        
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

void stack_top(Stack *stack) {
    if (!stack_isEmpty(stack)) 
        printf("%s\n", stack->_top->data);
    return;
}

int main(int argc, char const *argv[]){
    Stack myStack;
    stack_init(&myStack);

    char temp[MAX];
    scanf("%[^\n]", temp);

    stack_push(&myStack, temp);

    while (!stack_isEmpty(&myStack)) {
        stack_top(&myStack);
        stack_pop(&myStack);
    }

    return 0;
}