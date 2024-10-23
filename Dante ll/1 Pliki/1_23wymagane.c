#include <stdio.h>
#include <string.h>
#include "tested_declarations.h"
#include "rdebug.h"


int read_file(const char *filename) {
    if (filename == NULL) {
        return -1;
    }

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        return 0;
    }

    char buffer[31];
    int liczba_plikow = 0;
    while(fgets(buffer, sizeof(buffer), file) != NULL){
        printf("%s", buffer);
        *(buffer + strcspn(buffer, "\n")) = '\0';

        FILE *finner_file = fopen(buffer, "r");
        if(finner_file != NULL){
            fclose(finner_file);
            liczba_plikow += read_file(buffer);
        }
    }
    fclose(file);
    return liczba_plikow + 1;
}


int main() {
    char nazwa_sciezki[31];
    printf("Podaj sciezke do pliku:");
    scanf("%30s", nazwa_sciezki);

    FILE *file = fopen(nazwa_sciezki, "r");
    if (file == NULL) {
        printf("Couldn't open file");
        return 4;
    }

    int opened_file = read_file(nazwa_sciezki);
    printf("%d", opened_file);
    fclose(file);
    return 0;
}

