#include <stdio.h>
#include "tested_declarations.h"
#include "rdebug.h"

int main() {
    char nazwa_sciezki[31];
    printf("Podaj sciezke do pliku:\n");
    scanf("%30s", nazwa_sciezki);

    FILE *f = fopen(nazwa_sciezki, "r");
    if (f == NULL) {
        printf("Couldn't open file\n");
        return 4;
    }

    int suma = 0;
    int number;
    while (fscanf(f, "%d", &number) == 1) {
        suma += number;
    }

    if (!feof(f)) {
        printf("File corrupted\n");
        fclose(f);
        return 6;
    }

    printf("%d\n", suma);
    fclose(f);
    return 0;
}

