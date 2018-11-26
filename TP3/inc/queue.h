#ifndef QUEUE_H
#define QUEUE_H

#include <stddef.h>

struct _queue {
    size_t front, rear;
    size_t capacity, size;
    int array[];
};

typedef struct _queue *Queue;

Queue createQueue(size_t capacity);

char isFull(Queue queue);
char isEmpty(Queue queue);

void enqueue(Queue queue, int item);

int dequeue(Queue queue);

void freeQueue(Queue queue);

#endif // QUEUE_H
