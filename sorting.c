#include "bubble.h"
#include "queue.h"
#include "quick.h"
#include "set.h"
#include "shell.h"
#include "stack.h"

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define OPTIONS "absqQr:n:p:"

typedef enum options { b, s, q, Q } options;

void print_func(options j, int seed, int size, int elements) {
    srandom(seed); //set seed
    uint32_t arr[size];
    for (int i = 0; i < size; i += 1) { //initialize array
        arr[i] = random();
    }

    if (j == b) { //bubble sort
        bubble_sort(arr, size); //sort the array
        printf("Bubble Sort\n%d elements, %d moves, %d compares\n", size, bubble_moves,
            bubble_comparisons); //print header
        for (int i = 0; i < ((size < elements) ? size : elements);
             i += 1) { //loop thru array size or elements
            printf("%13" PRIu32, arr[i]); //print array element
            if (((i + 1) % 5) == 0) { //if fifth element, new line
                printf("\n");
            }
        }
    }
    if (j == s) { //shell sort
        shell_sort(arr, size); //sort array
        printf("Shell Sort\n%d elements, %d moves, %d compares\n", size, shell_moves,
            shell_comparisons);
        for (int i = 0; i < ((size < elements) ? size : elements);
             i += 1) { //loop thru array size or elements
            printf("%13" PRIu32, arr[i]); //print array element
            if (((i + 1) % 5) == 0) { //if fifth element, new line
                printf("\n");
            }
        }
    }
    if (j == q) { //quick sort stack
        quick_sort_stack(arr, size); //sort array
        printf("Quick Sort (Stack)\n%d elements, %d moves, %d compares\nMax stack size: 0\n", size,
            qss_moves, qss_comparisons);
        for (int i = 0; i < ((size < elements) ? size : elements);
             i += 1) { //loop thru array size or elements
            printf("%13" PRIu32, arr[i]); //print array element
            if (((i + 1) % 5) == 0) { //if fifth element, new line
                printf("\n");
            }
        }
    }
    if (j == Q) { //quick sort queue
        quick_sort_queue(arr, size);
        printf("Quick Sort (Queue)\n%d elements, %d moves, %d compares\nMax stack size: 0\n", size,
            qsq_moves, qsq_comparisons);
        for (int i = 0; i < ((size < elements) ? size : elements);
             i += 1) { //loop thru array size or elements
            printf("%13" PRIu32, arr[i]); //print array element
            if (((i + 1) % 5) == 0) { //if fifth element, new line
                printf("\n");
            }
        }
    }
    if (((size < elements) ? size : elements) % 5 != 0) {
        printf("\n");
    }
}

int main(int argc, char **argv) {
    int opt = 0;
    Set inputs = set_empty();
    int seed = 13371453;
    int size = 100;
    int elements = 100;
    char *end;

    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'a':
            inputs = set_insert(inputs, b);
            inputs = set_insert(inputs, s);
            inputs = set_insert(inputs, q);
            inputs = set_insert(inputs, Q);
            break;
        case 'b': inputs = set_insert(inputs, b); break;
        case 's': inputs = set_insert(inputs, s); break;
        case 'q': inputs = set_insert(inputs, q); break;
        case 'Q': inputs = set_insert(inputs, Q); break;
        case 'r': seed = strtoul(optarg, &end, 10); break;
        case 'n': size = strtoul(optarg, &end, 10); break;
        case 'p': elements = strtoul(optarg, &end, 10); break;
        default: break;
        }
    }

    for (options i = b; i <= Q; i += 1) {
        if (set_member(inputs, i)) {
            print_func(i, seed, size, elements);
        }
    }

    return 0;
}
