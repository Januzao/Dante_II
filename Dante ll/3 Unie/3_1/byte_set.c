#include <stdio.h>
#include "byte_set.h"
#include "tested_declarations.h"
#include "rdebug.h"

int main() {
    union byte_set bs;
    printf("Podaj liczbe:");
    if (scanf("%d", &bs.value) != 1) {
        printf("Incorrect input\n");
        return 1;
    }

    for (long unsigned int i = 0; i < sizeof(int); ++i) {
        printf("%d ", *(bs.bytes+i));
    }
    printf("\n");

    return 0;
}

