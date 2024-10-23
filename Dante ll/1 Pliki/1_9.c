#include <stdio.h>
#include "tested_declarations.h"
#include "rdebug.h"

int main() {
    char nazwa_sciezki[31];
    printf("Podaj nazwe pliku:");
    scanf("%30s", nazwa_sciezki);

    FILE *file = fopen(nazwa_sciezki, "r");
    if (file == NULL) {
        printf("Couldn't open file\n");
        return 4;
    }

    int num_count;
    if (fscanf(file, "%d", &num_count) != 1) {
        printf("File corrupted\n");
        fclose(file);
        return 6;
    }

    if (num_count <= 0) {
        printf("File corrupted\n");
        fclose(file);
        return 6;
    }

    int suma = 0;
    int liczba;
    for (int i = 0; i < num_count; ++i) {
        if (fscanf(file, "%d", &liczba) != 1) {
            printf("File corrupted\n");
            fclose(file);
            return 6;
        }
        suma += liczba;
    }

    double average = (double)suma / num_count;

    printf("%d\n", suma);
    printf("%.6f\n", average);

    fclose(file);
    return 0;
}

