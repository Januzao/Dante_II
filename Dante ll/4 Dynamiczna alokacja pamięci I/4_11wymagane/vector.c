#include <stdio.h>
#include <stdlib.h>
#include "vector.h"
#include "tested_declarations.h"
#include "rdebug.h"


int vector_create(struct vector_t *a, int N) {
    if (a == NULL || N <= 0) {
        return 1;
    }
    a->ptr = (int *)calloc(N, sizeof(int));
    if (a->ptr == NULL){
        return 2;
    }


    a->size = 0;
    a->capacity = N;

    return 0;
}

void vector_destroy(struct vector_t *a) {
    if (!(a == NULL || a->ptr == NULL))
        free(a->ptr);
}

void vector_display(const struct vector_t *a) {
    if (!(a == NULL || a->ptr == NULL || a->size <= 0 || a->capacity <= 0 || a->size > a->capacity)) {


        for (int i = 0; i < a->size - 1; i++) {
            printf("%d ", *(a->ptr + i));
        }
        printf("%d", *(a->ptr + a->size - 1));
    }
}

int vector_push_back(struct vector_t *a, int value) {
    if (a == NULL || a->ptr == NULL || a->capacity <= 0 || a->size < 0 || a->size > a->capacity) {
        return 1;
    }
    if (a->size >= a->capacity) {
        int *pInt = realloc(a->ptr, (a->capacity * 2) * sizeof(int));
        if (pInt == NULL) {
            return 2;
        }
        a->ptr = pInt;
        a->capacity *= 2;
    }
    *(a->ptr + a->size) = value;
    a->size += 1;
    return 0;
}

int vector_erase(struct vector_t *a, int value) {
    if (a == NULL || a->size < 0 || a->capacity <= 0 || a->ptr == NULL || a->size > a->capacity)
        return -1;
    int count, uont, l = 0, zmienna, size = a->size;
    int *new_capacity;
    int separator, kostyl = 1;
    if (a->size == 0) {
        if (a->capacity > 1)
            a->capacity = a->capacity / 2;
        return l;
    }
    for (count = 0; count < size; count++) {
        if (*(a->ptr + count) == value)
            l++;
    }

    separator = *(a->ptr);
    for (count = 1; count < a->size; count++) {
        if (separator == *(a->ptr + count)) {
            kostyl++;
        }
    }

    zmienna = a->size;
    for(int o=0;o<5;o++)
        for (count = 0; count < a->size; ++count) {
            if (*(a->ptr + count) == value) {
                for (uont = count; uont < zmienna - 1; ++uont) {
                    *(a->ptr + uont) = *(a->ptr + uont + 1);
                }
            }
        }
    a->size= size - l;

    if((kostyl == size) && (separator == value))
    {
        l=kostyl;
        a->size=0;
        if(a->capacity>1)
            a->capacity=a->capacity/2;
        return l;
    }

    if((a->size<a->capacity/4))
    {
        new_capacity=(int*)realloc(a->ptr, (a->capacity / 2) * sizeof(int));
        if(new_capacity == NULL)
        {
            return l;
        }
        a->ptr=new_capacity;
        if(a->capacity>1)
            a->capacity=a->capacity/2;
    }
    return l;
}

int vector_create_struct(struct vector_t **a, int N) {
    if (a == NULL) {
        return 1;
    }
    *a = (struct vector_t *)malloc(sizeof(struct vector_t));
    if (*a == NULL) {
        return 2;
    }
    int result = vector_create(*a, N);
    if (result != 0) {
        free(*a);
        return result;
    }
    return 0;
}


void vector_destroy_struct(struct vector_t **a) {
    if (a != NULL) {
        vector_destroy(*a);
        free(*a);
    }
}

void buffclear() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main() {
    int liczba, result1, result, result2;
    struct vector_t *gg;

    printf("Podaj pojemnosc tablicy:");
    int result_scanf = scanf("%d", &liczba);
    if (result_scanf != 1) {
        printf("Incorrect input");
        return 1;
    }
    if (liczba <= 0) {
        printf("Incorrect input data");
        return 2;
    }
    result_scanf = vector_create_struct(&gg, liczba);
    if (result_scanf == 1 || result_scanf == 2) {
        printf("Failed to allocate memory");
        return 8;
    }

    for (;;) {
        buffclear();
        printf("Co chcesz zrobic:");
        result_scanf = scanf("%d", &result);
        if (result_scanf != 1) {
            printf("incorrect input");
            vector_destroy_struct(&gg);
            return 1;
        }

        switch (result) {
            case 1:
                printf("Podaj kolejne liczby, ktore maja zostac dodane do tablicy:");
                result2 = 0;
                do {
                    result_scanf = scanf("%d", &result1);
                    if (result_scanf != 1) {
                        printf("Incorrect input");
                        vector_destroy_struct(&gg);
                        return 1;
                    }
                    if (result1 == 0)
                        break;

                    result_scanf = vector_push_back(gg, result1);
                    if (result_scanf == 1) {
                        printf("Incorrect input");
                        vector_destroy_struct(&gg);
                        return 1;
                    }
                    if (result_scanf == 2) {
                        printf("Failed to allocate memory\n");
                        break;
                    }
                    result2++;
                } while (1);

                if (gg->size == 0)
                    printf("Buffer is empty\n");
                else {
                    vector_display(gg);
                    printf("\n");
                }
                break;

            case 2:
                result2 = 0;
                printf("Podaj kolejne liczby, które mają zostać usuniete z tablicy:");
                do {
                    result_scanf = scanf("%d", &result1);
                    if (result_scanf != 1) {
                        printf("Incorrect input");
                        vector_destroy_struct(&gg);
                        return 1;
                    }
                    result2++;
                    if (result1 == 0)
                        break;
                    vector_erase(gg, result1);
                } while (1);

                if (gg->size == 0)
                    printf("Buffer is empty\n");
                else {
                    vector_display(gg);
                    printf("\n");
                }
                break;

            case 0:
                vector_destroy_struct(&gg);
                return 0;

            default:
                printf("Incorrect input data\n");
                break;
        }
    }
}
