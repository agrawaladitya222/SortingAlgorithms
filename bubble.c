#include "bubble.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>

int bubble_moves = 0;
int bubble_comparisons = 0;

bool compare(uint32_t one, uint32_t two) { //returns true if one<two
    bubble_comparisons += 1;
    return one < two;
}

void bubble_sort(uint32_t *A, uint32_t n) {
    bool swapped = true;
    while (swapped) {
        swapped = false;
        for (uint32_t i = 1; i < n; i += 1) {
            if (compare(*(A + i), *(A + i - 1))) {
                uint32_t temp = *(A + i);
                *(A + i) = *(A + i - 1);
                *(A + i - 1) = temp;
                swapped = true;
                bubble_moves += 3;
            }
        }
        n -= 1;
    }
}
