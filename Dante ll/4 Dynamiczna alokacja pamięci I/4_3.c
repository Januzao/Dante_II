#include <stdio.h>
#include <stdlib.h>
#include "tested_declarations.h"
#include "rdebug.h"

float* create_array(int N) {
    if (N <= 0) {
        return NULL;
    }

    float *ptr = (float *)malloc(N * sizeof(float));
    return ptr;
}

void clear_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main() {
    int size;
    printf("Podaj rozmiar tablicy:");
    if (scanf("%d", &size) != 1) {
        printf("Incorrect input");
        return 1;
    }
    if (size <= 0) {
        printf("Incorrect input data");
        return 2;
    }

    clear_buffer();

    float *arr = create_array(size);
    if (arr == NULL) {
        printf("Failed to allocate memory");
        return 8;
    }

    printf("Podaj liczby:");
    for (int i = 0; i < size; ++i) {
        if (scanf("%f", (arr+i)) != 1) {
            printf("Incorrect input");
            free(arr);
            return 1;
        }
    }
    clear_buffer();

    for (int i = size - 1; i >= 0; --i) {
        printf("%.4f ", *(arr+i));
    }
    printf("\n");

    free(arr);

    return 0;
}

