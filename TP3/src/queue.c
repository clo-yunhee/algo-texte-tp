#include <stdlib.h>

#include "queue.h"

Queue createQueue(size_t capacity) {
    Queue queue = malloc(sizeof(Queue));
    
    queue->capacity = capacity;
    queue->front = queue->size = 0;
    queue->rear = capacity - 1;
    queue->array = malloc(capacity * sizeof(int));

    return queue;
}

void enqueue(Queue queue, int item) {
    if (isFull(queue))
        return;
    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->array[queue->rear] = item;
    queue->size++;
}

int dequeue(Queue queue) {
    if (isEmpty(queue))
        return -1;
    int item = queue->array[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size--;
    return item;
}

char isFull(Queue queue) {
    return (queue->size == queue->capacity);
}

char isEmpty(Queue queue) {
    return (queue->size == 0);
}

void freeQueue(Queue queue) {
    if (queue != NULL) {
        free(queue->array);
        free(queue);
    }
}
