#include <stdio.h>
#include "bit_set.h"
#include "tested_declarations.h"
#include "rdebug.h"

int main() {
    union bit_set bs;

    printf("Podaj liczbe:");
    if (scanf("%hhu", &bs.byte) != 1) {
        printf("Incorrect input\n");
        return 1;
    }

    printf("%d %d %d %d %d %d %d %d\n",
           bs.bits.bit7, bs.bits.bit6, bs.bits.bit5, bs.bits.bit4,
           bs.bits.bit3, bs.bits.bit2, bs.bits.bit1, bs.bits.bit0);

    return 0;
}

