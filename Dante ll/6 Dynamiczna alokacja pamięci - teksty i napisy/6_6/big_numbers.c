#include "big_numbers.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "tested_declarations.h"
#include "rdebug.h"

#define Z 0
#define TEN 10


int create(struct big_numbers_t *bn, int capacity) {
    if (!bn || capacity <= Z) {
        return 1;
    }
    bn->big_number = malloc(capacity * sizeof(char *));
    if (!bn->big_number) {
        return 2;
    }

    bn->size = Z;
    bn->capacity = capacity;
    return 0;
}

int create_big_numbers(struct big_numbers_t **bn, int capacity) {
    if (!bn || capacity <= Z) {
        return 1;
    }

    *bn = (struct big_numbers_t *) malloc(sizeof(struct big_numbers_t));
    if (!*bn) {
        return 2;
    }

    int result = create(*bn, capacity);
    if (result != Z) {
        free(*bn);
        *bn = NULL;
    }
    return result;
}

void destroy(struct big_numbers_t *bn) {
    if (bn != NULL && bn->big_number != NULL && bn->capacity > Z && bn->size >= Z && bn->size <= bn->capacity) {
        for (; bn->size > Z; --bn->size) {
            free(*(bn->big_number + bn->size - 1));
        }
        free(bn->big_number);
    }
}

void destroy_big_numbers(struct big_numbers_t **bn) {
    if (bn != NULL && *bn != NULL && (*bn)->big_number != NULL &&
        (*bn)->capacity > Z && (*bn)->size >= 0 && (*bn)->size <= (*bn)->capacity) {
        destroy(*bn);
        free(*bn);
        *bn = NULL;
    }
}


void display(const struct big_numbers_t *bn) {
    if (bn != NULL && bn->big_number != NULL && bn->capacity > Z && bn->size >= Z && bn->size <= bn->capacity) {
        for (int i = Z; i < bn->size; ++i) {
            printf("%s\n", *(bn->big_number + i));
        }
    }
}

int check_if_is_correct(const char *number) {
    if (!number) {
        return -1;
    }

    int length = (int) strlen(number);
    if (length == Z) {
        return 2;
    }

    if (*(number + (length - 1)) == '\n') {
        return 2;
    }

    if (length < 2 && *number == '0') {
        return Z;
    }

    if (length < 5 && atol(number) == 0) {
        return 2;
    }

    int i = (*number == '-') ? 1 : Z;
    int leadingZero = (*number == '0');

    for (; *(number + i); i++) {
        if (!isdigit(*(number + i))) {
            return 2;
        }
    }

    if (leadingZero && i > 1) {
        return 2;
    }

    return Z;
}


int add_big_number(struct big_numbers_t *bn, const char *big_number) {
    if (bn == NULL || big_number == NULL || bn->big_number == NULL || bn->capacity <= Z || bn->size < Z ||
        bn->size > bn->capacity || check_if_is_correct(big_number) != 0)
    {
        return 1;
    }
    if (bn->size == bn->capacity) return 3;

    int result = (int )strlen(big_number);
    *(bn->big_number + bn->size) = calloc(result + 1, sizeof(char));
    if (*(bn->big_number + bn->size) == NULL){
        return 2;
    }

    for (int i = Z; i < result; ++i) *(*(bn->big_number + bn->size) + i) = *(big_number + i);


    bn->size++;

    return 0;
}


void hooo_mukatta_kuruno_ka_Nigetsu_ni_kono_DIO_ni_chikazuite_kuruno_ka_Sekkaku_no_Jesefu_ga_watashi_no_Za_Warudo_no_shotai_wo() {
    while (getchar() != '\n');
}

int main() {
    struct big_numbers_t *structbigNumbers;

    char *string = malloc(201 * sizeof(char));
    if (!string) {
        printf("Failed to allocate memory\n");
        return 8;
    }

    int result = create_big_numbers(&structbigNumbers, TEN);
    if (result != Z) {
        printf("Failed to allocate memory\n");
        return 8;
    }

    printf("Podaj liczby:");
    for (;;) {
        for (int i = 0; i < 200; ++i) {
            *(string + i) = '\0';
        }
        scanf("%200[^\n]", string);
        if (*string == '\0' || *string == '\n' || (int) strlen(string) < 1)
            break;
        if (check_if_is_correct(string) != Z) {
            printf("Incorrect input\n");
            hooo_mukatta_kuruno_ka_Nigetsu_ni_kono_DIO_ni_chikazuite_kuruno_ka_Sekkaku_no_Jesefu_ga_watashi_no_Za_Warudo_no_shotai_wo();
            continue;
        }
        result = add_big_number(structbigNumbers, string);

        switch (result) {
            case 1:
                printf("Incorrect input\n");
                hooo_mukatta_kuruno_ka_Nigetsu_ni_kono_DIO_ni_chikazuite_kuruno_ka_Sekkaku_no_Jesefu_ga_watashi_no_Za_Warudo_no_shotai_wo();
                continue;
            case 2:
                printf("Failed to allocate memory\n");
                break;
            case 3:
                printf("Buffer is full\n");
                break;
        }
        hooo_mukatta_kuruno_ka_Nigetsu_ni_kono_DIO_ni_chikazuite_kuruno_ka_Sekkaku_no_Jesefu_ga_watashi_no_Za_Warudo_no_shotai_wo();
    }
    if (structbigNumbers->size == Z) {
        printf("Buffer is empty\n");
        destroy_big_numbers(&structbigNumbers);
        free(string);
        return Z;
    }
    display(structbigNumbers);
    destroy_big_numbers(&structbigNumbers);
    free(string);

    return Z;
}
