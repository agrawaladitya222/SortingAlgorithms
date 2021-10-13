#include "quick.h"

#include "queue.h"
#include "stack.h"

#include <inttypes.h>
#include <stdio.h>

int qss_comparisons = 0;
int qss_moves = 0;
int qsq_comparisons = 0;
int qsq_moves = 0;

bool qss_compare(int64_t one, int64_t two) { //returns true if one<two
    qss_comparisons += 1;
    return one < two;
}

bool qsq_compare(int64_t one, int64_t two) { //returns true if one<two
    qsq_comparisons += 1;
    return one < two;
}

int64_t qsq_partition(uint32_t *A, int64_t lo, int64_t hi) {
    uint32_t pivot = A[lo + ((hi - lo) / 2)];
    int64_t i = lo - 1;
    int64_t j = hi + 1;
    while (i < j) {
        i += 1;
        //while (A[i] < pivot){
        while (qsq_compare(A[i], pivot)) {
            i += 1;
        }
        j -= 1;
        //while (A[j] > pivot) {
        while (qsq_compare(pivot, A[j])) {
            j -= 1;
        }
        if (i < j) {
            uint32_t temp = A[i];
            A[i] = A[j];
            A[j] = temp;
            qsq_moves += 3;
        }
    }
    return j;
}

int64_t qss_partition(uint32_t *A, int64_t lo, int64_t hi) {
    uint32_t pivot = A[lo + ((hi - lo) / 2)];
    int64_t i = lo - 1;
    int64_t j = hi + 1;
    while (i < j) {
        i += 1;
        //while (A[i] < pivot){
        while (qss_compare(A[i], pivot)) {
            i += 1;
        }
        j -= 1;
        //while (A[j] > pivot) {
        while (qss_compare(pivot, A[j])) {
            j -= 1;
        }
        if (i < j) {
            uint32_t temp = A[i];
            A[i] = A[j];
            A[j] = temp;
            qss_moves += 3;
        }
    }
    return j;
}

void quick_sort_stack(uint32_t *A, uint32_t n) {
    int64_t lo = 0;
    int64_t hi = n - 1;
    Stack *s = stack_create(n);
    stack_push(s, lo);
    stack_push(s, hi);
    while (stack_size(s) != 0) {
        stack_pop(s, &hi);
        stack_pop(s, &lo);
        int64_t p = qss_partition(A, lo, hi); //maybe add * before A
        if (lo < p) {
            stack_push(s, lo);
            stack_push(s, p);
        }
        if (hi > (p + 1)) {
            stack_push(s, (p + 1));
            stack_push(s, hi);
        }
    }
}

void quick_sort_queue(uint32_t *A, uint32_t n) {
    int64_t lo = 0;
    int64_t hi = n - 1;
    Queue *q = queue_create(n);
    enqueue(q, lo);
    enqueue(q, hi);
    while (queue_size(q) != 0) {
        dequeue(q, &lo);
        dequeue(q, &hi);
        int64_t p = qsq_partition(A, lo, hi); //maybe add * before A
        if (lo < p) {
            enqueue(q, lo);
            enqueue(q, p);
        }
        if (hi > (p + 1)) {
            enqueue(q, (p + 1));
            enqueue(q, hi);
        }
    }
}
