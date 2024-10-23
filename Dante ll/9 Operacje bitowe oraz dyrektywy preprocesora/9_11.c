#include <stdio.h>
#include "tested_declarations.h"
#include "rdebug.h"

unsigned long long add(unsigned long long a, unsigned long long b) {
    while (b != 0) {
        unsigned long long carry = a & b;
        a = a ^ b;
        b = carry << 1;
    }
    return a;
}

int main(void) {
    unsigned long long a, b;

    printf("Enter numbers: ");
    if (scanf("%llu %llu", &a, &b) != 2) {
        printf("Incorrect input\n");
        return 1;
    }

    unsigned long long result = add(a, b);
    printf("%llu\n", result);
    return 0;
}

