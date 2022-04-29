/**
 * @author Bayu Laksana
 * @date 2019-01-22
 * 
 * ADT Implementation (Queue)
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

typedef struct queueNode_t {
    char data[MAX];
    struct queueNode_t *next;
} QueueNode;

typedef struct queue_t {
    QueueNode *_front, *_rear;
    unsigned _size;
} Queue;

void queue_init(Queue *queue){
    queue->_size = 0;
    queue->_front = NULL;
    queue->_rear = NULL;
}

bool queue_isEmpty(Queue *queue) {
    return (queue->_front == NULL && queue->_rear == NULL);
}

void queue_push(Queue *queue, char value[MAX]){
    QueueNode *newNode = (QueueNode*) malloc(sizeof(QueueNode));
    if (newNode) {
        queue->_size++;
        strcpy(newNode->data,value);
        newNode->next = NULL;
        
        if (queue_isEmpty(queue))                 
            queue->_front = queue->_rear = newNode;
        else {
            queue->_rear->next = newNode;
            queue->_rear = newNode;
        }
    }
}

void queue_pop(Queue *queue){
    if (!queue_isEmpty(queue)) {
        QueueNode *temp = queue->_front;
        queue->_front = queue->_front->next;
        free(temp);
        
        if (queue->_front == NULL)
            queue->_rear = NULL;
        queue->_size--;
    }
}

void queue_front(Queue *queue){
    if (!queue_isEmpty(queue))
        printf("%s\n", queue->_front->data);
    return;
}

int main(int argc, char const *argv[]){
    Queue myQueue;
    queue_init(&myQueue);

    char temp[MAX];
    int n;
    scanf("%d", &n);
    for(int i=0;i<n;i++){      
        getchar();
        scanf("%[^\n]", temp);
        queue_push(&myQueue, temp);
    }

    while (!queue_isEmpty(&myQueue)) {
        queue_front(&myQueue);
        queue_pop(&myQueue);
    }

    return 0;
}