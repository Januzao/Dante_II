#include <stdio.h>
#include "tested_declarations.h"
#include "rdebug.h"

int is_equal(int a, int b) {
    return !(a ^ b);
}

int is_negative(int value) {
    unsigned int mask = 1u << 31;
    return (value & mask) >> 31;
}


int main(void) {
    int a, b;

    printf("Podaj dwie liczby: ");
    int result = scanf("%d %d", &a, &b);
    if (!result) {
        printf("Incorrect input");
        return 1;
    }

    if (is_equal(a, b)) {
        printf("rowne\n");
    } else {
        printf("nierowne\n");
    }

    if (is_negative(a)) {
        printf("ujemna ");
    } else {
        printf("nieujemna ");
    }

    if (is_negative(b)) {
        printf("ujemna\n");
    } else {
        printf("nieujemna\n");
    }

    return 0;
}

