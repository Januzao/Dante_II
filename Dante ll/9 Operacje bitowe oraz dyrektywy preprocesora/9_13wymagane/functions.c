#include <stdio.h>
#include "functions.h"
#include "tested_declarations.h"
#include "rdebug.h"

int main() {
    int type;
    printf("Enter data type: ");
    if (scanf("%d", &type) != 1) {
        printf("Incorrect input\n");
        return 1;
    } else if (type < 0 || type > 2){
        printf("Incorrect input data\n");
        return 2;
    }

    if (type == 0) {
        unsigned int value;
        printf("Enter an integer number: ");
        if (scanf("%u", &value) != 1) {
            printf("Incorrect input\n");
            return 1;
        }
        unsigned int set_bits, cleared_bits;
        COUNT_BITS(value, &set_bits, &cleared_bits);
        printf("%u\n", set_bits);
        printf("%u\n", cleared_bits);
        DISPLAY_BITS(value);
        REVERSE_BITS(&value);
        DISPLAY_BITS(value);
    } else if (type == 1) {
        unsigned short value;
        printf("Enter an integer number: ");
        if (scanf("%hu", &value) != 1) {
            printf("Incorrect input\n");
            return 1;
        }
        unsigned int set_bits, cleared_bits;
        COUNT_BITS(value, &set_bits, &cleared_bits);
        printf("%u\n", set_bits);
        printf("%u\n", cleared_bits);
        DISPLAY_BITS(value);
        REVERSE_BITS(&value);
        DISPLAY_BITS(value);
    } else if (type == 2) {
        unsigned long long value;
        printf("Enter an integer number: ");
        if (scanf("%llu", &value) != 1) {
            printf("Incorrect input\n");
            return 1;
        }
        unsigned int set_bits, cleared_bits;
        COUNT_BITS(value, &set_bits, &cleared_bits);
        printf("%u\n", set_bits);
        printf("%u\n", cleared_bits);
        DISPLAY_BITS(value);
        REVERSE_BITS(&value);
        DISPLAY_BITS(value);
    }

    return 0;
}

