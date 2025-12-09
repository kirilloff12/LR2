#include <stdio.h>
#include <time.h>
#include "stack.h"

#define ITERATIONS 1000000

void benchmark_push() {
    Stack stack;
    initStack(&stack);

    clock_t start = clock();

    for (int i = 0; i < ITERATIONS; i++) {
        push(&stack, i);
    }

    clock_t end = clock();
    double elapsed = (double)(end - start) / CLOCKS_PER_SEC;

    printf("push() benchmark: %d iterations in %.4f seconds (%.0f ops/sec)\n",
           ITERATIONS, elapsed, ITERATIONS / elapsed);

    destroyStack(&stack);
}

void benchmark_pop() {
    Stack stack;
    initStack(&stack);

    // Fill stack first
    for (int i = 0; i < ITERATIONS; i++) {
        push(&stack, i);
    }

    clock_t start = clock();

    for (int i = 0; i < ITERATIONS; i++) {
        pop(&stack);
    }

    clock_t end = clock();
    double elapsed = (double)(end - start) / CLOCKS_PER_SEC;

    printf("pop() benchmark: %d iterations in %.4f seconds (%.0f ops/sec)\n",
           ITERATIONS, elapsed, ITERATIONS / elapsed);
}

void benchmark_push_pop_alternating() {
    Stack stack;
    initStack(&stack);

    clock_t start = clock();

    for (int i = 0; i < ITERATIONS / 2; i++) {
        push(&stack, i);
        pop(&stack);
    }

    clock_t end = clock();
    double elapsed = (double)(end - start) / CLOCKS_PER_SEC;

    printf("push/pop alternating benchmark: %d operations in %.4f seconds (%.0f ops/sec)\n",
           ITERATIONS, elapsed, ITERATIONS / elapsed);

    destroyStack(&stack);
}

int main() {
    printf("Running stack benchmarks...\n\n");

    benchmark_push();
    benchmark_pop();
    benchmark_push_pop_alternating();

    return 0;
}
