#include <stdio.h>
#include <stdlib.h>
#include "tested_declarations.h"
#include "rdebug.h"

int* create_array_int(int N) {
    if (N <= 0) {
        return NULL;
    }

    int* arr = (int*)calloc(N, sizeof(int));
    if (arr == NULL){
        return NULL;
    }
    return arr;
}

int* copy_array_int(const int* ptr, int N) {
    if (N <= 0 || ptr == NULL) {
        return NULL;
    }

    int* copy_arr = (int*)calloc(N, sizeof(int));
    if (copy_arr == NULL) {
        return NULL;
    }

    for (int i = 0; i < N; ++i) {
        *(copy_arr+i) = *(ptr+i);
    }

    return copy_arr;
}

void display_array_int(const int* ptr, int N) {
    if (N <= 0 || ptr == NULL) {
        return;
    }

    for (int i = 0; i < N; ++i) {
        printf("%d ", *(ptr+i));
    }
    printf("\n");
}


int main() {
    int size, input_result;
    int* array_ptr;
    int* copied_array_ptr;

    printf("Podaj rozmiar tablicy:");
    input_result = scanf("%d", &size);

    switch(input_result) {
        case 1:
            break;
        default:
            printf("Incorrect input");
            return 1;
    }

    if (size <= 0) {
        printf("Incorrect input data");
        return 2;
    }

    array_ptr = create_array_int(size);

    switch(array_ptr != NULL) {
        case 1:
            break;
        default:
            printf("Failed to allocate memory");
            return 8;
    }

    printf("Podaj liczby:");
    for (int i = 0; i < size; i++) {
        input_result = scanf("%d", (array_ptr + i));
        switch(input_result) {
            case 1:
                break;
            default:
                printf("Incorrect input");
                free(array_ptr);
                return 1;
        }
    }

    copied_array_ptr = copy_array_int(array_ptr, size);

    switch(copied_array_ptr != NULL) {
        case 1:
            break;
        default:
            printf("Failed to allocate memory");
            free(array_ptr);
            return 8;
    }

    display_array_int(array_ptr, size);
    display_array_int(copied_array_ptr, size);

    free(array_ptr);
    free(copied_array_ptr);

    return 0;
}
