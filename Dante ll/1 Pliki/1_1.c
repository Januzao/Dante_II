#include <stdio.h>
#include "tested_declarations.h"
#include "rdebug.h"

int main() {
    char napisy[31];

    printf("Podaj sciezke do pliku:");
    scanf("%30s", napisy);

    FILE *file = fopen(napisy, "r");

    if (file == NULL) {
        printf("Couldn't open file\n");
        return 4;
    }

    int c;
    int Empty = 1;

    while ((c = fgetc(file)) != EOF) {
        putchar(c);
        Empty = 0;
    }

    fclose(file);

    if (Empty) {
        printf("Nothing to show\n");
        return 0;
    }

    return 0;
}

