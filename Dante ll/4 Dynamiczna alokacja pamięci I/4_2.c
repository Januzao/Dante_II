#include <stdio.h>
#include <stdlib.h>
#include "tested_declarations.h"
#include "rdebug.h"

int main() {
    float *pi = (float *)malloc(sizeof(float));

    if (pi == NULL) {
        printf("Failed to allocate memory\n");
        return 8;
    }

    *pi = 3.141593;
    printf("%f %p\n", *pi, (void *)pi);

    free(pi);

    return 0;
}

