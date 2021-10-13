#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Stack {
    uint32_t top; //index of next empty slot
    uint32_t capacity; //number of items that can be pushed
    int64_t *items; //array of items, each of type int64_t
} Stack;

Stack *stack_create(uint32_t capacity) { //code from Eugene's section/Prof Long in assignment pdf
    Stack *s = (Stack *) malloc(sizeof(Stack));
    if (s) {
        s->top = 0;
        s->capacity = capacity;
        s->items = (int64_t *) calloc(capacity, sizeof(int64_t));
        if (!s->items) {
            free(s);
            s = NULL;
        }
    }
    return s;
}

void stack_delete(Stack **s) { //code from prof Long in assignment pdf
    if (*s && (*s)->items) {
        free((*s)->items);
        free(*s);
        *s = NULL;
    }
    return;
}

bool stack_empty(Stack *s) {
    return (s->top == 0);
}

bool stack_full(Stack *s) { //code from Eugene's section
    return s->top == s->capacity;
}

uint32_t stack_size(Stack *s) {
    return (s->top);
}

bool stack_push(Stack *s, int64_t x) { //code from Eugene's section
    if (stack_full(s)) {
        return false;
    }
    s->items[s->top] = x;
    s->top += 1;
    return true;
}

bool stack_pop(Stack *s, int64_t *x) { //modified code from Eugene's section
    if (stack_empty(s)) {
        return false;
    }
    s->top -= 1;
    *x = s->items[s->top];
    return true;
}

void stack_print(Stack *s) { //code from Eugene's section
    printf("[");
    for (uint32_t i = 0; i < s->top; i += 1) {
        printf("%" PRId64, s->items[i]);
        if (i + 1 != s->top) {
            printf(",");
        }
    }
    printf("]\n");
}

//main function for testing only
/*
int main(void){
	Stack *s = stack_create(5);
	stack_push(s,0);
	stack_push(s,1);
	stack_push(s,2);
	stack_push(s,3);
	stack_push(s,4);
	stack_print(s);
	printf("%" PRIu32"\n", stack_size(s));
	int64_t x;
	stack_pop(s, &x);
	stack_print(s);
	printf("%" PRIu32"\n", stack_size(s));
	return 0;
}*/
