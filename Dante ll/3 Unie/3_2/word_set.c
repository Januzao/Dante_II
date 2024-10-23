#include <stdio.h>
#include "word_set.h"
#include "tested_declarations.h"
#include "rdebug.h"

int main() {
    union word_set ws;

    printf("Podaj liczbe:");
    if (scanf("%d", &ws.value) != 1){
        printf("Incorrect input");
        return 1;
    }

    printf("%u %u\n", *ws.words, *(ws.words + 1));

    return 0;
}

