#include <stdlib.h>
#include <stdio.h>
#include "tested_declarations.h"
#include "rdebug.h"


int **create_array_2d(int width, int height) {
    if (width <= 0 || height <= 0) {
        return NULL;
    }
    int **tablica = (int **)malloc(height * sizeof(int *));
    if (tablica == NULL) {
        return NULL;
    }
    for (int i = 0; i < height; i++) {
        *(tablica + i) = (int *)malloc(width * sizeof(int));
        if (*(tablica + i) == NULL) {
            for (int j = 0; j < i; j++) {
                free(*(tablica + j));
            }
            free(tablica);
            return NULL;
        }
    }
    return tablica;
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

void destroy_array_2d(int **ptr, int height) {
    if (ptr != NULL && height > 0) {
        for (int i = 0; i < height; i++) {
            free(*(ptr + i));
        }
        free(ptr);
    }
}

void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}


int main() {
    int width, height;
    printf("Podaj szerokosc i wysokosc:");
    if (scanf("%d %d", &width, &height) != 2) {
        printf("Incorrect input");
        return 1;
    }

    if (width <= 0 || height <= 0) {
        printf("Incorrect input data");
        return 2;
    }

    int **tab = create_array_2d(width, height);
    if (tab == NULL) {
        printf("Failed to allocate memory");
        return 8;
    }

    printf("Podaj liczby:");
    clear_input_buffer();

    for (int i = 0; i < height; i++) {
        for (int k = 0; k < width; k++) {
            if (scanf("%d", *(tab + i) + k) != 1) {
                printf("Incorrect input");
                destroy_array_2d(tab, height);
                return 1;
            }
        }
    }

    display_array_2d(tab, width, height);
    destroy_array_2d(tab, height);

    return 0;
}
