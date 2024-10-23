#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define DEFINE_ARRAY(TYPE) \
typedef struct array_##TYPE##_t { \
    int size; \
    int capacity; \
    TYPE *data; \
} array_##TYPE##_t;

#define CREATE_ARRAY(TYPE) \
array_##TYPE##_t *create_array_##TYPE(int size) { \
    if (size <=0)          \
        return NULL;\
    array_##TYPE##_t *array = (array_##TYPE##_t *)calloc(1, sizeof(array_##TYPE##_t)); \
    if (!array) return NULL;                      \
    array->size = 0;       \
    array->capacity = size;\
    array->data = (TYPE *)calloc(size, sizeof(TYPE)); \
    if (!array->data) { \
        free(array); \
        return NULL; \
    } \
    return array; \
}

#define FREE_ARRAY(TYPE) \
void free_array_##TYPE(array_##TYPE##_t *array) { \
    if (array) { \
        free(array->data); \
        free(array); \
    } \
}

#define SAVE_ARRAY(TYPE) \
int save_array_##TYPE(const array_##TYPE##_t *array, const char *filename) { \
    if(array==NULL||filename==NULL||array->data==NULL||array->capacity<=0||array->size<=0||array->size>array->capacity) { \
    return 1;} \
    FILE *file = fopen(filename, "wb"); \
    if (!file) return 2; \
    if (fwrite(&array->size, sizeof(int), 1, file) != 1) { \
        fclose(file); \
        return 2; \
    } \
    if (fwrite(array->data, sizeof(TYPE), array->size, file) != (size_t)array->size) { \
        fclose(file); \
        return 2; \
    } \
    fclose(file); \
    return 0; \
}

#define LOAD_ARRAY(TYPE) \
int load_array_##TYPE(array_##TYPE##_t **array, const char *filename) { \
    if (!array || !filename) return 1; \
    FILE *file = fopen(filename, "rb"); \
    if (!file) {         \
    return 2;} \
    int size; \
    if (fread(&size, sizeof(int), 1, file) != 1) { \
        fclose(file); \
        return 3; \
    } else if (size <= 0){                                              \
        fclose(file);    \
        return 3;        \
        }\
    array_##TYPE##_t *new_array = (array_##TYPE##_t *)calloc(1, sizeof(array_##TYPE##_t)); \
    if (!new_array) { \
        fclose(file); \
        return 4; \
    } \
    new_array->data = (TYPE *)calloc(size, sizeof(TYPE)); \
    if (!new_array->data) { \
        free(new_array); \
        fclose(file); \
        return 4; \
    } \
    new_array->size = size; \
    new_array->capacity = size; \
    if (fread(new_array->data, sizeof(TYPE), size, file) != (size_t)size) { \
        free(new_array->data); \
        free(new_array); \
        fclose(file); \
        return 3; \
    } \
    fclose(file); \
    *array = new_array; \
    return 0; \
}

#define SORT_ARRAY(TYPE) \
int sort_array_##TYPE(array_##TYPE##_t *array) { \
    if(!array||!array->data||array->capacity<=0||array->size<=0||array->size>array->capacity) \
        return 1;\
    for (int i = 0; i < array->size - 1; ++i) { \
        for (int j = 0; j < array->size - i - 1; ++j) { \
            if (*(array->data + j) > *(array->data + j + 1)) { \
                TYPE temp = *(array->data + j); \
                *(array->data + j) = *(array->data + j + 1); \
                *(array->data + j + 1) = temp; \
            } \
        } \
    } \
    return 0; \
}

#endif // FUNCTIONS_H
