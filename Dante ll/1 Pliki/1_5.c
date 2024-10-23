#include <stdio.h>
#include "tested_declarations.h"
#include "rdebug.h"

int main() {
    char nazwa_sciezki[31];
    printf("Podaj sziezke do pliku:\n");
    scanf("%30s", nazwa_sciezki);
    FILE *f = fopen(nazwa_sciezki, "w");

    if (f == NULL) {
        printf("Couldn't create file\n");
        return 5;
    }

    for (int i = 0; i <= 100; ++i) {
        fprintf(f, "%d\n", i);
    }
    printf("File saved\n");

    fclose(f);
    return 0;
}


