#include <stdio.h>
#include "tested_declarations.h"
#include "rdebug.h"

void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main() {
    char source_filename[31];
    char dest_filename[31];

    printf("Podaj sciezke do pliku:");
    scanf("%30s", source_filename);
    clear_input_buffer();
    FILE *source_file = fopen(source_filename, "r");
    if (source_file == NULL) {
        printf("Couldn't open file\n");
        return 4;
    }

    printf("Podaj sciezke do pliku wyjsciowego:");
    scanf("%30s", dest_filename);
    clear_input_buffer();

    FILE *dest_file = fopen(dest_filename, "w");
    if (dest_file == NULL) {
        printf("Couldn't create file\n");
        fclose(source_file);
        return 5;
    }

    fseek(source_file, 0, SEEK_END);

    long pos = ftell(source_file);

    while (--pos >= 0) {
        fseek(source_file, pos, SEEK_SET);
        int c = fgetc(source_file);
        fputc(c, dest_file);
    }

    printf("File copied\n");

    fclose(source_file);
    fclose(dest_file);

    return 0;
}

