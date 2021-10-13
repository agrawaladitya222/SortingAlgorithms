#include "queue.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Queue {
    uint32_t head; //index of head of queue (next to be dequeue'd)
    uint32_t tail; //index of tail of queue (next available spot to enqueue)
    uint32_t size; // the number of elements in the queue
    uint32_t capacity; // capacity of the queue
    int64_t *items; //holds the items
} Queue;

uint32_t next(uint32_t pos, uint32_t capacity) {
    return ((pos + 1) % capacity);
}

Queue *queue_create(uint32_t capacity) {
    Queue *q = (Queue *) malloc(sizeof(Queue));
    if (q) {
        q->head = 0;
        q->tail = 0;
        q->size = 0;
        q->capacity = capacity;
        q->items = (int64_t *) calloc(capacity, sizeof(int64_t));
        if (!q->items) {
            free(q);
            q = NULL;
        }
    }
    return q;
}

void queue_delete(Queue **q) {
    if (*q && (*q)->items) {
        free((*q)->items);
        free(*q);
        *q = NULL;
    }
    return;
}

bool queue_empty(Queue *q) {
    return (q->size == 0);
}

bool queue_full(Queue *q) {
    return (q->size == q->capacity);
}

uint32_t queue_size(Queue *q) {
    return q->size;
}

bool enqueue(Queue *q, int64_t x) { //set items[tail], then increment tail (use next() function)
    if (queue_full(q)) {
        return false;
    }
    q->items[q->tail] = x;
    q->tail = next(q->tail, q->capacity);
    q->size += 1;
    return true;
}

bool dequeue(Queue *q, int64_t *x) { //return items[head], then increment head
    if (queue_empty(q)) {
        return false;
    }
    *x = q->items[q->head];
    q->head = next(q->head, q->capacity);
    q->size -= 1;
    return true;
}

void queue_print(Queue *q) {
    printf("[");
    uint32_t i = q->head;
    uint32_t j = 0;
    while (j < q->size) {
        printf("%" PRId64, q->items[i]);
        if (next(i, q->capacity) != q->tail) {
            printf(",");
        }
        i = next(i, q->capacity);
        j += 1;
    }
    printf("]\n");
}

//main function only for testing
/*
int main(void){
        Queue *q = queue_create(5);
	enqueue(q, 0);	
        enqueue(q, 1);
	enqueue(q, 2);
	enqueue(q, 3);
	enqueue(q, 4);
        queue_print(q);
        printf("%" PRIu32"\n", queue_size(q));
        int64_t x;
        dequeue(q, &x);
        queue_print(q);
        printf("%" PRIu32"\n", queue_size(q));
        return 0;
}*/
