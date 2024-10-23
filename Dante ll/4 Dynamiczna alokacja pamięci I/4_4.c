#include <stdio.h>
#include <stdlib.h>
#include "tested_declarations.h"
#include "rdebug.h"

int create_array_int(int **ptr, int N) {
    if (N <= 0 || ptr == NULL) {
        return 1;
    }

    *ptr = (int *)calloc(N, sizeof(int));
    if (*ptr == NULL) {
        return 2;
    }

    return 0;
}

void destroy_array_int(int **ptr) {
    if (ptr != NULL) {
        free(*ptr);
        *ptr = NULL;
    }
}

void clear_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main() {
    int size;
    printf("Podaj rozmiar tablicy:");
    if (scanf("%d", &size) != 1) {
        printf("Incorrect input\n");
        return 1;
    }
    if (size <= 0){
        printf("Incorrect input data\n");
        return 2;
    }
    clear_buffer();

    int *arr = NULL;
    int create_result = create_array_int(&arr, size);
    if (create_result == 1) {
        printf("Incorrect input data\n");
        return 2;
    } else if (create_result == 2) {
        printf("Failed to allocate memory\n");
        return 8;
    }

    printf("Podaj liczby:");
    for (int i = 0; i < size; ++i) {
        if (scanf("%d", arr+i) != 1) {
            printf("Incorrect input\n");
            destroy_array_int(&arr);
            return 1;
        }
    }
    clear_buffer();

    for (int i = size - 1; i >= 0; --i) {
        printf("%d ", *(arr+i));
    }
    printf("\n");

    destroy_array_int(&arr);

    return 0;
}

