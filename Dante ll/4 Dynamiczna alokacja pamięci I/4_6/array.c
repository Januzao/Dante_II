#include "array.h"
#include <stdio.h>
#include <stdlib.h>
#include "tested_declarations.h"
#include "rdebug.h"


int array_create(struct array_t *a, int N) {
    if (N <= 0 || a == NULL) {
        return 1;
    }

    a->ptr = (int *)malloc(N * sizeof(int));
    if (a->ptr == NULL) {
        return 2;
    }

    a->size = 0;
    a->capacity = N;

    return 0;
}

int array_push_back(struct array_t *a, int value) {
    if (a == NULL || a->ptr == NULL || a->capacity <= 0 || a->size < 0 || a->size > a->capacity) {
        return 1;
    }

    if (a->size == a->capacity) {
        return 2;
    }

    *(a->ptr + a->size) = value;
    a->size += 1;
    return 0;
}


void array_display(const struct array_t *a) {
    if (a == NULL || a->ptr == NULL || a->size <= 0 || a->capacity <= 0 || a->size > a->capacity) {
        return;
    }

    for (int i = 0; i < a->size; i++) {
        printf("%d ", *(a->ptr + i));
    }
    printf("\n");
}


void array_destroy(struct array_t *a) {
    if (a != NULL) {
        free(a->ptr);
        a->ptr = NULL;
    }
}

int main()
{
    int size_input, input_value, scanf_result;
    struct array_t arr;

    printf("Podaj rozmiar tablicy:");
    scanf_result = scanf("%d", &size_input);
    switch (scanf_result) {
        case 1:
            break;
        default:
            printf("Incorrect input");
            return 1;
    }

    if (size_input <= 0) {
        printf("Incorrect input data");
        return 2;
    }
    scanf_result = array_create(&arr, size_input);
    switch (scanf_result) {
        case 1:
        case 2:
            printf("Failed to allocate memory");
            return 8;
    }

    printf("Podaj liczby do zapisania:");
    do {
        scanf_result = scanf("%d", &input_value);
        switch (scanf_result) {
            case 1:
                if (input_value != 0) {
                    array_push_back(&arr, input_value);
                }
                break;
            default:
                printf("Incorrect input");
                array_destroy(&arr);
                return 1;
        }
    } while (input_value != 0);

    if (arr.size == arr.capacity) {
        printf("Buffer is full\n");
    }

    if (arr.size == 0) {
        printf("Buffer is empty");
    } else {
        array_display(&arr);
    }

    array_destroy(&arr);
    return 0;
}

