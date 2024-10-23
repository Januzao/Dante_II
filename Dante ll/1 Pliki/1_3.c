#include <stdio.h>
#include "tested_declarations.h"
#include "rdebug.h"

int main() {
    char source_filename[31];
    char dest_filename[31];

    printf("Podaj sciezke do pliku:");
    scanf("%30s", source_filename);
    FILE *source_file = fopen(source_filename, "r");
    if (source_file == NULL) {
        printf("Couldn't open file\n");
        return 4;
    }

    printf("Podaj sciezke do pliku wyjsciowego:");
    scanf("%30s", dest_filename);



    FILE *dest_file = fopen(dest_filename, "w");
    if (dest_file == NULL) {
        printf("Couldn't create file\n");
        fclose(source_file);
        return 5;
    }

    int c;
    while ((c = fgetc(source_file)) != EOF) {
        fputc(c, dest_file);
    }

    printf("File copied\n");

    fclose(source_file);
    fclose(dest_file);

    return 0;
}

