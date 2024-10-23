#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "tested_declarations.h"
#include "rdebug.h"

int stats(int *sum, float *avg, int num, ...) {
    if (num <= 0 || !sum || !avg) {
        return 1;
    }

    va_list args;
    va_start(args, num);

    int total_sum = 0;

    for (int i = 0; i < num; i++) {
        int value = va_arg(args, int);
        total_sum += value;
    }

    va_end(args);

    *sum = total_sum;
    *avg = (float)total_sum / num;

    return 0;
}

int main(void) {
    int num;
    printf("Enter number of elements: ");
    if (scanf("%d", &num) != 1) {
        printf("Incorrect input\n");
        return 1;
    }

    if (num < 1 || num > 3) {
        printf("Incorrect input data\n");
        return 2;
    }

    int *numbers = malloc(num * sizeof(int));
    if (numbers == NULL) {
        printf("Failed to allocate memory\n");
        return 1;
    }

    printf("Enter numbers: ");
    for (int i = 0; i < num; i++) {
        if (scanf("%d", numbers + i) != 1) {
            printf("Incorrect input\n");
            free(numbers);
            return 1;
        }
    }

    int sum;
    float avg;

    if (stats(&sum, &avg, num, *numbers, (num > 1 ? *(numbers + 1) : 0), (num > 2 ? *(numbers + 2)  : 0)) == 0) {
        printf("%d %.6f\n", sum, avg);
    } else {
        printf("Error calculating stats.\n");
    }

    free(numbers);
    return 0;
}

