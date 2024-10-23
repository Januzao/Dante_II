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

void clear_buff() {
    while (getchar() != '\n');
}

int **create_array_2d(int width, int height) {
    if (width <= 0 || height <= 0) {
        return NULL;
    }
    int **array;
    array = (calloc(height, sizeof(int *)));
    if (array == NULL) {
        return NULL;
    }
    for (int i = 0; i < height; i++) {
        *(array + i) = (malloc(width * sizeof(int)));
        if (*(array + i) == NULL) {
            for (int j = 0; j < i; j++) {
                free(*(array + j));
            }
            free(array);
            return NULL;
        }
    }
    return array;
}

int matrix_create(struct matrix_t *m, int width, int height) {
    if (m == NULL || width <= 0 || height <= 0) {
        return 1;
    }
    m->ptr = create_array_2d(width, height);

    if (m->ptr == NULL) {
        return 2;
    }

    m->height = height;
    m->width = width;

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
    if (m != NULL && m->height > 0) {
        int **vacban;
        vacban = m->ptr;
        for (int i = 0; i < m->height; ++i) {
            if (*(vacban + i) != NULL)
                free(*(vacban + i));
        }
        free(vacban);
    }
}

struct matrix_t *matrix_create_struct(int width, int height) {
    int temp;
    if (width <= 0 || height <= 0) {
        return NULL;
    }

    struct matrix_t *memory = (struct matrix_t *) calloc(1, sizeof(struct matrix_t));
    if (memory == NULL) {
        return NULL;
    }

    temp = matrix_create(memory, width, height);
    if (temp != 0) {
        free(memory);
        return NULL;
    }
    return memory;
}


void matrix_destroy_struct(struct matrix_t **m) {
    if (m && *m) {
        for (int i = 0; i < (*m)->height; i++) {
            free(*((*m)->ptr + i));
        }
        free((*m)->ptr);
        free(*m);
        *m = NULL;
    }
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


struct matrix_t *matrix_copy(const struct matrix_t *copy) {
    if (!copy) {
        return NULL;
    }
    if (copy->height <= 0 || copy->width <= 0 || !copy->ptr) {
        return NULL;
    }

    struct matrix_t *aStruct = matrix_create_struct(copy->width, copy->height);
    if (aStruct == NULL) {
        return NULL;
    }
    for (int i = 0; i < copy->height; ++i) {
        for (int j = 0; j < copy->width; ++j) {
            *(*(aStruct->ptr + i) + j) = *(*(copy->ptr + i) + j);
        }
    }
    return aStruct;
}

struct matrix_t *matrix_load_b(const char *filename, int *err_code) {
    int width, height;
    FILE *file;
    if (err_code != NULL) {
        *err_code = 0;
    }
    if (filename == NULL) {
        if (err_code != NULL) {
            *err_code = 1;
        }
        return NULL;
    }

    file = fopen(filename, "rb");
    if (file == NULL) {
        if (err_code != NULL)
            *err_code = 2;
        return NULL;
    }
    int read_result = fread(&width, sizeof(int), 1, file);
    if (read_result != 1) {
        if (err_code != NULL) {
            *err_code = 3;
        }
        fclose(file);
        return NULL;
    }
    read_result = fread(&height, sizeof(int), 1, file);
    if (read_result != 1) {
        if (err_code != NULL) {
            *err_code = 3;
        }
        fclose(file);
        return NULL;
    }
    if (width <= 0 || height <= 0) {
        if (err_code != NULL) {
            *err_code = 3;
        }
        fclose(file);
        return NULL;
    }
    struct matrix_t *matrix = matrix_create_struct(width, height);
    if (matrix == NULL) {
        if (err_code != NULL) {
            *err_code = 4;
        }
        fclose(file);
        return NULL;
    }

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            read_result = fread((*(matrix->ptr + i) + j), sizeof(int), 1, file);
            if (read_result != 1) {
                if (err_code != NULL)
                    *err_code = 3;
                matrix_destroy_struct(&matrix);
                fclose(file);
                return NULL;
            }
        }
    }
    fclose(file);
    return matrix;
}


struct matrix_t *matrix_load_t(const char *filename, int *err_code) {
    int width, height;
    FILE *fileout;
    if (err_code != NULL) {
        *err_code = 0;
    }
    if (filename == NULL) {
        if (err_code != NULL) {
            *err_code = 1;
        }
        return NULL;
    }

    fileout = fopen(filename, "r");
    if (fileout == NULL) {
        if (err_code != NULL) {
            *err_code = 2;
        }
        return NULL;
    }

    if (fscanf(fileout, "%d %d", &width, &height) != 2) {
        if (err_code != NULL) {
            *err_code = 3;
        }
        fclose(fileout);
        return NULL;
    }
    if (width <= 0 || height <= 0) {
        if (err_code != NULL) {
            *err_code = 3;
        }
        fclose(fileout);
        return NULL;
    }

    struct matrix_t *matrix = matrix_create_struct(width, height);
    if (!matrix) {
        if (err_code != NULL) {
            *err_code = 4;
        }
        fclose(fileout);
        return NULL;
    }

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            if (fscanf(fileout, "%d ", (*(matrix->ptr + i) + j)) != 1) {
                if (err_code != NULL) {
                    *err_code = 3;
                }
                matrix_destroy_struct(&matrix);
                fclose(fileout);
                return NULL;
            }
        }
    }
    fclose(fileout);
    return matrix;
}

struct matrix_t *matrix_add(const struct matrix_t *m1, const struct matrix_t *m2) {
    if (!m1 || !m2) {
        return NULL;
    }
    if (m1->height <= 0 || m1->width <= 0 || m1->ptr == NULL || m2->height <= 0 || m2->width <= 0 || m2->ptr == NULL ||
        m1->height != m2->height || m1->width != m2->width) {
        return NULL;
    }

    struct matrix_t *matrix_add = matrix_create_struct(m1->width, m2->height);
    if (!matrix_add) {
        return NULL;
    }

    for (int i = 0; i < m1->height; ++i) {
        for (int j = 0; j < m2->width; ++j) {
            *(*(matrix_add->ptr + i) + j) = *(*(m1->ptr + i) + j) + *(*(m2->ptr + i) + j);
        }
    }
    return matrix_add;
}

struct matrix_t *matrix_subtract(const struct matrix_t *m1, const struct matrix_t *m2) {
    if (!m1 || !m2) {
        return NULL;
    }
    if (m1->height <= 0 || m1->width <= 0 || m1->ptr == NULL || m2->height <= 0 || m2->width <= 0 || m2->ptr == NULL ||
        m1->height != m2->height || m1->width != m2->width) {
        return NULL;
    }

    struct matrix_t *matrix_subtract = matrix_create_struct(m1->width, m2->height);
    if (!matrix_subtract) {
        return NULL;
    }

    for (int i = 0; i < m1->height; ++i) {
        for (int j = 0; j < m2->width; ++j) {
            *(*(matrix_subtract->ptr + i) + j) = *(*(m1->ptr + i) + j) - *(*(m2->ptr + i) + j);
        }
    }
    return matrix_subtract;
}

struct matrix_t *matrix_multiply(const struct matrix_t *m1, const struct matrix_t *m2) {
    if (!m1 || !m2 || m1->height <= 0 || m1->width <= 0 || m1->ptr == NULL ||
        m2->height <= 0 || m2->width <= 0 || m2->ptr == NULL || m1->width != m2->height) {
        return NULL;
    }
    struct matrix_t *result = matrix_create_struct(m2->width, m1->height);
    if (!result) {
        return NULL;
    }

    for (int i = 0; i < m1->height; ++i) {
        for (int j = 0; j < m2->width; ++j) {
            *(*(result->ptr + i) + j) = 0;
        }
    }
    for (int i = 0; i < m1->height; ++i) {
        for (int j = 0; j < m2->width; ++j) {
            for (int k = 0; k < m1->width; ++k) {
                *(*(result->ptr + i) + j) += (*(*(m1->ptr + i) + k)) * (*(*(m2->ptr + k) + j));
            }
        }
    }

    return result;
}


void egg(char *name, int i) {
    if (fgets(name, i + 1, stdin)) {
        int len = strlen(name);
        if (*(name + len - 1) == '\n') {
            *(name + len - 1) = '\0';

        } else {
            clear_buff();
        }
    }
}


int func(const char *text_str, const char *string) {
    if (text_str == NULL || string == NULL) {
        return 0;
    }

    int lenght = strlen(text_str);
    int lenght2 = strlen(string);

    if (lenght < lenght2) {
        return 0;
    }
    int count = 0;
    for (int i = lenght - lenght2; i < lenght; ++i) {
        if (*(text_str + i) != *(string + count)) {
            return 0;
        }
        ++count;
    }

    return 1;
}

int main() {
    struct matrix_t *matrix1 = NULL;
    struct matrix_t *matrix2 = NULL;
    struct matrix_t *matrix3 = NULL;

    char *memory = (char *) malloc(20 * sizeof(char));
    if (memory == NULL) {
        printf("Failed to allocate memory");
        return 8;
    }
    printf("Podaj nazwe pierwszego pliku:");
    egg(memory, 19);

    if (!func(memory, ".bin") && !func(memory, ".txt")) {
        printf("Unsupported file format");
        free(memory);
        return 7;
    }

    int error_code;

    if (func(memory, ".bin")) {
        matrix1 = matrix_load_b(memory, &error_code);
    } else if (func(memory, ".txt")) {
        matrix1 = matrix_load_t(memory, &error_code);
    }

    if (matrix1 == NULL) {
        if (error_code == 1) {
            printf("Incorrect input");
            free(memory);
            return 1;
        } else if (error_code == 2) {
            printf("Couldn't open file");
            free(memory);
            return 4;
        } else if (error_code == 3) {
            printf("File corrupted");
            free(memory);
            return 6;
        } else if (error_code == 4) {
            printf("Failed to allocate memory");
            free(memory);
            return 8;
        }
        free(memory);
        return error_code;
    }

    printf("Podaj nazwe drugiego pliku:");
    egg(memory, 19);

    if (!func(memory, ".bin") && !func(memory, ".txt")) {
        matrix_destroy_struct(&matrix1);
        free(memory);
        printf("Unsupported file format");
        return 7;
    }

    if (func(memory, ".bin")) {
        matrix2 = matrix_load_b(memory, &error_code);
    } else if (func(memory, ".txt")) {
        matrix2 = matrix_load_t(memory, &error_code);
    }

    if (matrix2 == NULL) {
        if (error_code == 1) {
            printf("Incorrect input");
            matrix_destroy_struct(&matrix1);
            free(memory);
            return 1;
        } else if (error_code == 2) {
            printf("Couldn't open file");
            matrix_destroy_struct(&matrix1);
            free(memory);
            return 4;
        } else if (error_code == 3) {
            printf("File corrupted");
            matrix_destroy_struct(&matrix1);
            free(memory);
            return 6;
        } else if (error_code == 4) {
            printf("Failed to allocate memory");
            matrix_destroy_struct(&matrix1);
            free(memory);
            return 8;
        }
        matrix_destroy_struct(&matrix1);
        free(memory);
        return error_code;
    }

    matrix3 = matrix_add(matrix1, matrix2);
    if (matrix3 == NULL) {
        printf("Error\n");
    } else {
        matrix_display(matrix3);
    }
    matrix_destroy_struct(&matrix3);
    matrix3 = matrix_subtract(matrix1, matrix2);
    if (matrix3 == NULL) {
        printf("Error\n");
    } else {
        matrix_display(matrix3);
    }
    matrix_destroy_struct(&matrix3);
    matrix3 = matrix_multiply(matrix1, matrix2);
    if (matrix3 == NULL) {
        printf("Error\n");
    } else {
        matrix_display(matrix3);
    }
    matrix_destroy_struct(&matrix1);
    matrix_destroy_struct(&matrix2);
    matrix_destroy_struct(&matrix3);
    free(memory);
    return 0;
}

