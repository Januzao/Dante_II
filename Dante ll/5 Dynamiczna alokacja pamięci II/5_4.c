#include <stdlib.h>
#include <stdio.h>
#include "tested_declarations.h"
#include "rdebug.h"

struct matrix_t{
    int **ptr;
    int width;
    int height;
};
void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}

int matrix_create(struct matrix_t *m, int width, int height){
    if (m == NULL || width <= 0 || height <= 0){
        return 1;
    }
    m->width = width;
    m->height = height;

    m->ptr = (int **)malloc(height * sizeof(int *));
    if (m->ptr == NULL) {
        return 2;
    }

    for (int i = 0; i < height; ++i) {
        *(m->ptr+i) = (int *)malloc(width * sizeof(int));
        if (*(m->ptr+i) == NULL) {
            for (int j = 0; j < i; ++j) {
                free(*(m->ptr+j));
            }
            free(m->ptr);
            return 2;
        }
    }

    return 0;
}
int matrix_read(struct matrix_t *m){
    if (m == NULL || m->ptr == NULL || m->width <= 0 || m->height <= 0){
        return 1;
    }

    for (int i = 0; i < m->height; ++i) {
        for (int j = 0; j < m->width; ++j) {
            if (scanf("%d", (*(m->ptr + i) + j)) != 1){
                clear_input_buffer();
                return 2;
            }
        }
    }
    return 0;
}
void matrix_display(const struct matrix_t *m){
    if (m == NULL || m->ptr == NULL || m->width <= 0 || m->height <= 0) {
        return;
    }
    for (int i = 0; i < m->height; ++i) {
        int *row = *(m->ptr + i);
        for (int j = 0; j < m->width; ++j) {
            printf("%d ", *(row + j));
        }
        printf("\n");
    }
}
void matrix_destroy(struct matrix_t *m){
    if (m != NULL && m->ptr != NULL && m->height > 0){
        for (int i = 0; i < m->height; ++i) {
            free(*(m->ptr + i));
        }
        free(m->ptr);
    }
}

int main() {
    struct matrix_t gg;
    int width, height;
    printf("Podaj szerokosc i wysokosc:");
    if (scanf("%d %d", &width, &height) != 2) {
        printf("Incorrect input");
        clear_input_buffer();
        return 1;
    }
    clear_input_buffer();

    if (width <= 0 || height <= 0) {
        printf("Incorrect input data");
        return 2;
    }
    int result = matrix_create(&gg, width, height);
    if (result == 1){
        printf("incorrect input data");
        return 2;
    } else if (result == 2){
        printf("Failed to allocate memory");
        return 8;
    }

    printf("Podaj liczby:");
    result = matrix_read(&gg);
    if (result == 2){
        printf("incorrect input\n");
        matrix_destroy(&gg);
        return 1;
    }
    clear_input_buffer();


    matrix_display(&gg);
    matrix_destroy(&gg);

    return 0;
}
