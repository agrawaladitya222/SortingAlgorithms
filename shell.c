#include "shell.h"

#include "gaps.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>

int shell_moves = 0;
int shell_comparisons = 0;

bool shell_compare(uint32_t one, uint32_t two) { //returns true if one<two
    shell_comparisons += 1;
    return one < two;
}

void shell_sort(uint32_t *A, uint32_t n) {
    for (uint32_t gapi = 0; gapi < GAPS; gapi += 1) { //gapi is the index for array gaps
        for (uint32_t i = gaps[gapi]; i < n; i += 1) { //GAPS is a constant for length of gaps
            uint32_t j = i;
            uint32_t temp = *(A + i);
            shell_moves += 1;
            while (
                (j >= gaps[gapi])
                && /* (temp < *(A + j - gaps[gapi]))*/ shell_compare(temp, *(A + j - gaps[gapi]))) {
                //shell_comparisons += 1;
                shell_moves += 1;
                *(A + j) = *(A + j - gaps[gapi]);
                j -= gaps[gapi];
            }
            *(A + j) = temp;
            shell_moves += 1;
        }
    }
}
