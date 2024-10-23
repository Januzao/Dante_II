#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>

#define CREATE_READ_FUNCTIONS(TYPE, FORMAT)                        \
    int read_##TYPE(TYPE *data, int size) {                        \
        if (!data || size <= 0) return 1;                          \
        for (int i = 0; i < size; ++i) {                           \
            if (scanf(FORMAT, data + i) != 1) {                    \
                return 2;                                          \
            }                                                      \
        }                                                          \
        return 0;                                                  \
    }

#define CREATE_SORT_FUNCTIONS(TYPE)                                \
    int sort_##TYPE(TYPE *data, int size) {                        \
        if (!data || size <= 0) return 1;                          \
        for (int i = 0; i < size - 1; ++i) {                       \
            for (int j = i + 1; j < size; ++j) {                   \
                if (*(data + i) > *(data + j)) {                   \
                    TYPE temp = *(data + i);                       \
                    *(data + i) = *(data + j);                     \
                    *(data + j) = temp;                            \
                }                                                  \
            }                                                      \
        }                                                          \
        return 0;                                                  \
    }

#define CREATE_DISPLAY_FUNCTIONS(TYPE, FORMAT)                     \
    void display_##TYPE(const TYPE *data, int size) {              \
        if (!data || size <= 0) return;                            \
        for (int i = 0; i < size; ++i) {                           \
            printf(FORMAT " ", *(data + i));                       \
        }                                                          \
        printf("\n");                                              \
    }

#endif // FUNCTIONS_H
