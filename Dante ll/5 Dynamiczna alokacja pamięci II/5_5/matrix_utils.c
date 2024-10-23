#include "matrix_utils.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "tested_declarations.h"
#include "rdebug.h"

void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

int matrix_create(struct matrix_t *m, int width, int height) {
    if (m == NULL || width <= 0 || height <= 0) {
        return 1;
    }
    m->width = width;
    m->height = height;

    m->ptr = (int **) malloc(height * sizeof(int *));
    if (m->ptr == NULL) {
        return 2;
    }

    for (int i = 0; i < height; ++i) {
        *(m->ptr + i) = (int *) malloc(width * sizeof(int));
        if (*(m->ptr + i) == NULL) {
            for (int j = 0; j < i; ++j) {
                free(*(m->ptr + j));
            }
            free(m->ptr);
            return 2;
        }
    }

    return 0;
}

int matrix_read(struct matrix_t *m) {
    if (m == NULL || m->ptr == NULL || m->width <= 0 || m->height <= 0) {
        return 1;
    }

    for (int i = 0; i < m->height; ++i) {
        for (int j = 0; j < m->width; ++j) {
            if (scanf("%d", (*(m->ptr + i) + j)) != 1) {
                clear_input_buffer();
                return 2;
            }
        }
    }
    return 0;
}

void matrix_display(const struct matrix_t *m) {
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

void matrix_destroy(struct matrix_t *m) {
    if (m != NULL && m->ptr != NULL && m->height > 0) {
        for (int i = 0; i < m->height; ++i) {
            free(*(m->ptr + i));
        }
        free(m->ptr);
    }
}

struct matrix_t *matrix_create_struct(int width, int height) {
    if (width <= 0 || height <= 0) {
        return NULL;
    }
    int tab;
    struct matrix_t *memory = (struct matrix_t *) malloc(sizeof(struct matrix_t));
    if (memory == NULL) {
        return NULL;
    }
    tab = matrix_create(memory, width, height);
    if (tab != 0) {
        free(memory);
        return NULL;
    }
    return memory;
}

void matrix_destroy_struct(struct matrix_t **m) {
    if (m != NULL) {
        matrix_destroy(*m);
        free(*m);
    }
    *m = NULL;
}

struct matrix_t *matrix_transpose(const struct matrix_t *m) {
    if (m == NULL || m->ptr == NULL || m->width <= 0 || m->height <= 0)
        return NULL;

    struct matrix_t *transposed = matrix_create_struct(m->height, m->width);
    if (transposed == NULL) {
        return NULL;
    }

    for (int i = 0; i < m->height; ++i) {
        for (int j = 0; j < m->width; ++j) {
            *(*(transposed->ptr + j) + i) = *(*(m->ptr + i) + j);
        }
    }

    return transposed;
}

int matrix_save_b(const struct matrix_t *m, const char *filename) {
    if (m == NULL || m->ptr == NULL || m->width <= 0 || m->height <= 0 || filename == NULL)
        return 1;

    FILE *f = fopen(filename, "wb");
    if (f == NULL)
        return 2;

    int status = 0;

    if (fwrite(&m->width, sizeof(int), 1, f) != 1) status = 3;

    if (status == 0 && fwrite(&m->height, sizeof(int), 1, f) != 1) status = 3;

    for (int i = 0; status == 0 && i < m->height; ++i) {
        for (int k = 0; k < m->width; ++k) {
            if (fwrite((*(m->ptr + i) + k), sizeof(int), 1, f) != 1) {
                status = 3;
                break;
            }
        }
    }

    fclose(f);

    switch (status) {
        case 3:
            return 3;
        default:
            return 0;
    }
}

int matrix_save_t(const struct matrix_t *m, const char *filename) {
    if (m == NULL || m->ptr == NULL || m->width <= 0 || m->height <= 0 || filename == NULL)
        return 1;

    FILE *f = fopen(filename, "w");
    if (f == NULL)
        return 2;

    int status = 0;

    if (fprintf(f, "%d %d\n", m->width, m->height) <= 0) status = 3;

    for (int i = 0; status == 0 && i < m->height; ++i) {
        for (int k = 0; k < m->width; ++k) {
            if (fprintf(f, "%d ", *(*(m->ptr + i) + k)) <= 0) {
                status = 3;
                break;
            }
        }
        if (status == 0) fprintf(f, "\n");
    }

    fclose(f);

    switch (status) {
        case 3:
            return 3;
        default:
            return 0;
    }
}


int main() {
    int scanResult, width, height, filenameLength;
    struct matrix_t *originalMatrix;
    char *filename;

    printf("Podaj szerokosc i wysokosc:");
    scanResult = scanf("%d %d", &width, &height);
    if (scanResult != 2) {
        printf("Incorrect input");
        return 1;
    }
    if (width <= 0 || height <= 0) {
        printf("Incorrect input data");
        return 2;
    }
    originalMatrix = matrix_create_struct(width, height);
    if (originalMatrix == NULL) {
        printf("Failed to allocate memory");
        return 8;
    }
    printf("Podaj liczby:");
    scanResult = matrix_read(originalMatrix);
    if (scanResult != 0) {
        matrix_destroy_struct(&originalMatrix);
        printf("Incorrect input");
        return 1;
    }
    filename = (char *) malloc(40 * sizeof(char));
    if (filename == NULL) {
        matrix_destroy_struct(&originalMatrix);
        printf("Failed to allocate memory");
        return 8;
    }
    clear_input_buffer();
    printf("Podaj sciezke do pliku:");
    scanf("%39[^\n]", filename);
    filenameLength = strlen(filename);

    struct matrix_t *transposedMatrix = matrix_transpose(originalMatrix);
    if (transposedMatrix == NULL) {
        free(filename);
        matrix_destroy_struct(&originalMatrix);
        printf("Failed to allocate memory\n");
        return 8;
    }
    matrix_destroy_struct(&originalMatrix);

    if (filenameLength >= 4 && *(filename + filenameLength - 4) == '.' &&
        *(filename + filenameLength - 3) == 'b' && *(filename + filenameLength - 2) == 'i' &&
        *(filename + filenameLength - 1) == 'n') {
        scanResult = matrix_save_b(transposedMatrix, filename);
    } else if (filenameLength >= 4 && *(filename + filenameLength - 4) == '.' &&
               *(filename + filenameLength - 3) == 't' && *(filename + filenameLength - 2) == 'x' &&
               *(filename + filenameLength - 1) == 't') {
        scanResult = matrix_save_t(transposedMatrix, filename);
    } else {
        printf("Unsupported file format\n");
        scanResult = 7;
    }

    if (scanResult != 0 && scanResult != 7) {
        printf("Couldn't create file\n");
        scanResult = 5;
    } else if (scanResult == 0) {
        printf("File saved\n");
    }

    free(filename);
    matrix_destroy_struct(&transposedMatrix);
    return scanResult;
}
