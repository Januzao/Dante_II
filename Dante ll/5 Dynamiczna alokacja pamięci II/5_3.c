#include <stdlib.h>
#include <stdio.h>
#include "tested_declarations.h"
#include "rdebug.h"


int create_array_2d_2(int ***ptr, int width, int height){
    if (width <= 0 || height <= 0  || ptr == NULL){
        return 1;
    }
    int **gg;

    gg = (int**) malloc(height * sizeof(int*));
    if (gg == NULL){
        return 2;
    }
    for (int i = 0; i < height; ++i) {
        *(gg + i) = (int *)malloc(width * sizeof(int));
        if (*(gg + i)  == NULL) {
            for (int j = 0; j < i; ++j) {
                free(*(gg + j));
            }
            free(gg);
            return 2;
        }
    }
    *ptr = gg;
    return 0;
}

int sum_array_2d(int **ptr, int width, int height){
    if (width <= 0 || height <= 0 || ptr == NULL){
        return -1;
    }

    int cala_suma = 0;

    for (int i = 0; i < height; ++i) {
        if (*(ptr + i) == NULL){
            return -1;
        }

        for (int j = 0; j < width; ++j) {
            cala_suma += *(*(ptr + i) + j);
        }
    }
    return cala_suma;
}

int sum_row(int *ptr, int width){
    if (ptr == NULL || width <= 0){
        return -1;
    }

    int suma = 0;

    for (int i = 0; i < width; ++i) {
        suma += *(ptr + i);
    }

    return suma;
}


void display_array_2d(int **ptr, int width, int height) {
    if (ptr != NULL && width > 0 && height > 0) {
        for (int i = 0; i < height; i++) {
            for (int k = 0; k < width; k++) {
                printf("%d ", *(*(ptr + i) + k));
            }
            printf("\n");
        }
    }
}

void destroy_array_2d(int ***ptr, int height) {
    if (ptr == NULL || height <= 0) {
        return;
    }
    for (int i = 0; i < height; ++i) {
        free(*((*ptr) + i));
    }
    free(*ptr);
    *ptr = NULL;
}

void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}


int main() {
    int **gg;
    int width, height;
    printf("Podaj szerokosc i wysokosc:");
    if (scanf("%d %d", &width, &height) != 2) {
        printf("Incorrect input");
        clear_input_buffer();
        return 1;
    }

    if (width <= 0 || height <= 0) {
        printf("Incorrect input data");
        return 2;
    }

    if(create_array_2d_2(&gg, width, height) != 0){
        printf("Failed to allocate memory");
        return 8;
    }

    printf("Podaj liczby:");
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            if (scanf("%d", *(gg + i) + j) != 1) {
                destroy_array_2d(&gg, height);
                printf("incorrect input\n");
                clear_input_buffer();
                return 1;
            }
        }
        clear_input_buffer();
    }


    display_array_2d(gg, width, height);

    for (int i = 0; i < height; ++i) {
        printf("%d\n", sum_row(*(gg + i), width));
    }
    printf("%d\n", sum_array_2d(gg, width, height));

    destroy_array_2d(&gg, height);
    return 0;
}
