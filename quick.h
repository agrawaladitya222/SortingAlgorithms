#ifndef __QUICK_H__
#define __QUICK_H__

#include <stdint.h>

extern uint32_t max_stack_size;
extern uint32_t max_queue_size;
extern int qss_comparisons;
extern int qss_moves;
extern int qsq_comparisons;
extern int qsq_moves;

void quick_sort_stack(uint32_t *A, uint32_t n);

void quick_sort_queue(uint32_t *A, uint32_t n);

#endif
