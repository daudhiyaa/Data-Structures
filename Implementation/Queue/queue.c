/**
 * @author Bayu Laksana
 * @date 2019-01-22
 * 
 * ADT Implementation (Queue)
 * -- with int data-type
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
#include <math.h>
#define ll long long

typedef struct queueNode_t {
    int data;
    struct queueNode_t *next;
} QueueNode;

typedef struct queue_t {
    QueueNode *_front, *_rear;
    unsigned _size;
} Queue;

void queue_init(Queue *queue){
    queue->_size = 0;
    queue->_front = queue->_rear = NULL;
}

bool queue_isEmpty(Queue *queue) {
    return (queue->_front == NULL && queue->_rear == NULL);
}

void queue_push(Queue *queue, int value){
    QueueNode *newNode = (QueueNode*) malloc(sizeof(QueueNode));
    if (newNode) {
        queue->_size++;
        newNode->data = value;
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

int queue_front(Queue *queue){
    if (!queue_isEmpty(queue))
        return queue->_front->data;
    return 0;
}

int main(int argc, char const *argv[]){
    Queue myQueue;
    // init
    queue_init(&myQueue);

    queue_push(&myQueue, 1);
    queue_push(&myQueue, 2);
    queue_push(&myQueue, 3);

    // print
    while (!queue_isEmpty(&myQueue)) {
        printf("%d ", queue_front(&myQueue));
        queue_pop(&myQueue);
    }
    puts("");
    return 0;
}