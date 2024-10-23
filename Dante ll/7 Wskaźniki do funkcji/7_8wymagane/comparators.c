#include "comparators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tested_declarations.h"
#include "rdebug.h"

int sort(void* base, size_t num, size_t size, int (*comparator)(const void*, const void*)) {
    if (!base || !comparator || size == 0) return 1;

    char* array = (char*)base;
    for (size_t i = 0; i < num - 1; ++i) {
        for (size_t j = 0; j < num - 1 - i; ++j) {
            char* elem1 = array + j * size;
            char* elem2 = array + (j + 1) * size;
            if (comparator(elem1, elem2) > 0) {
                char* temp = (char*)malloc(size);
                if (!temp) {
                    return 1;
                }
                memcpy(temp, elem1, size);
                memcpy(elem1, elem2, size);
                memcpy(elem2, temp, size);
                free(temp);
            }
        }
    }
    return 0;
}


int comp_int(const void* a, const void* b){
    if (!a || !b){
        return 1;
    }
    int int_a = *((int *)a);
    int int_b = *((int *)b);

    return (int_a > int_b) - (int_a < int_b);

}
int comp_double(const void* a, const void* b){
    if (!a || !b){
        return 1;
    }
    double double_a = *((double*)a);
    double double_b = *((double*)b);

    return (double_a > double_b) - (double_a < double_b);
}
int comp_point(const void* a, const void* b) {
    if (!a || !b){
        return 1;
    }
    struct point_t* point_a = (struct point_t*)a;
    struct point_t* point_b = (struct point_t*)b;
    if (point_a->x != point_b->x) {
        return (point_a->x > point_b->x) - (point_a->x < point_b->x);
    } else {
        return (point_a->y > point_b->y) - (point_a->y < point_b->y);
    }
}

int main(void) {
    int data_type;
    int size;

    printf("Enter data type: ");
    if (scanf("%d", &data_type) != 1 || (data_type < 0 || data_type > 2)) {
        printf("Incorrect input\n");
        return 1;
    }

    printf("Enter array size: ");
    if (scanf("%d", &size) != 1){
        printf("Incorrect input\n");
        return 1;
    } else if (size <= 0){
        printf("Incorrect input data\n");
        return 2;
    }

    void* array = NULL;
    size_t elem_size = 0;
    int (*comparator)(const void*, const void*) = NULL;

    switch (data_type) {
        case 0: // int
            elem_size = sizeof(int);
            array = malloc(size * elem_size);
            comparator = comp_int;
            if (!array) {
                printf("Failed to allocate memory\n");
                return 8;
            }
            printf("Enter ints: ");
            for (int i = 0; i < size; ++i) {
                if (scanf("%d", (int*)array + i) != 1) {
                    printf("Incorrect input\n");
                    free(array);
                    return 1;
                }
            }
            break;
        case 1: // double
            elem_size = sizeof(double);
            array = malloc(size * elem_size);
            comparator = comp_double;
            if (!array) {
                printf("Failed to allocate memory\n");
                return 8;
            }
            printf("Enter doubles: ");
            for (int i = 0; i < size; ++i) {
                if (scanf("%lf", (double*)array + i) != 1) {
                    printf("Incorrect input\n");
                    free(array);
                    return 1;
                }
            }
            break;
        case 2: // point_t
            elem_size = sizeof(struct point_t);
            array = malloc(size * elem_size);
            comparator = comp_point;
            if (!array) {
                printf("Failed to allocate memory\n");
                return 8;
            }
            printf("Enter points: ");
            for (int i = 0; i < size; ++i) {
                if (scanf("%lf %lf", &((struct point_t*)array + i)->x, &((struct point_t*)array + i)->y) != 2) {
                    printf("Incorrect input\n");
                    free(array);
                    return 1;
                }
            }
            break;
    }

    if (sort(array, size, elem_size, comparator) != 0) {
        printf("Failed to sort array\n");
        free(array);
        return 1;
    }

    switch (data_type) {
        case 0:
            for (int i = 0; i < size; ++i) {
                printf("%d ", *(((int*)array) + i));
            }
            printf("\n");
            break;
        case 1:
            for (int i = 0; i < size; ++i) {
                printf("%lf ",*(((double *)array) + i));
            }
            printf("\n");
            break;
        case 2:
            for (int i = 0; i < size; ++i) {
                printf("%lf %lf\n", (((struct point_t*)array) + i)->x, (((struct point_t*)array) + i)->y);
            }
            break;
    }

    free(array);
    return 0;
}

