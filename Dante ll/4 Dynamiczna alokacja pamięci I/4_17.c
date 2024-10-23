#include <stdio.h>
#include <stdlib.h>
#include "tested_declarations.h"
#include "rdebug.h"

#define ALLOCATION_STEP 10

void display_vector(const int *vector, int size) {
    if (vector == NULL || size <= 0) {
        return;
    }
    for (int i = 0; i < size; i++, vector++) {
        printf("%d ", *vector);
    }
    printf("\n");
}

int sort(int *vector, int size) {
    if (vector == NULL || size <= 0) {
        return 1;
    }
    for (int i = 0; i < size - 1; i++) {
        int *ptr = vector;
        for (int j = 0; j < size - i - 1; j++, ptr++) {
            if (*ptr > *(ptr + 1)) {
                int temp = *ptr;
                *ptr = *(ptr + 1);
                *(ptr + 1) = temp;
            }
        }
    }
    return 0;
}


int main() {
    int *numbers = NULL;
    int num;
    int size = 0;
    int capacity = 0;

    numbers = realloc(numbers, ALLOCATION_STEP * sizeof(int));
    if (numbers == NULL) {
        printf("Failed to allocate memory\n");
        return 8;
    }
    capacity = ALLOCATION_STEP;

    printf("Podaj liczby:");
    while (1) {
        int result = scanf("%d", &num);
        if (result == EOF) {
            if (feof(stdin) || ferror(stdin)) {
                printf("Incorrect input\n");
                free(numbers);
                return 1;
            }
            break;
        }
        if (result != 1) {
            printf("Incorrect input\n");
            while (fgetc(stdin) != '\n');
            free(numbers);
            return 1;
        }

        if (num == 0) break;

        if (size >= capacity) {
            int newCapacity = capacity + ALLOCATION_STEP;
            int *temp = realloc(numbers, newCapacity * sizeof(int));
            if (temp == NULL) {
                printf("Failed to allocate memory\n");
                sort(numbers, size);
                display_vector(numbers, size);
                free(numbers);
                return 0;
            }
            numbers = temp;
            capacity = newCapacity;
        }
        *(numbers + size++) = num;
    }

    if (size == 0) {
        printf("Nothing to show\n");
    } else {
        sort(numbers, size);
        display_vector(numbers, size);
    }

    free(numbers);
    return 0;
}
