#include <stdio.h>
#include "tested_declarations.h"
#include "rdebug.h"
int main(int hejka, char* piwko[]) {
    if(hejka < 3) return printf("Not enough arguments\n"), 9;
    FILE *filenamexdlolkek = fopen(*(piwko + 1), "rb");
    if(!filenamexdlolkek) return printf("Couldn't open file\n"), 4;
    FILE *chinazes = fopen(*(piwko + 2), "wb");
    if(!chinazes) {
        printf("Couldn't create file\n");
        fclose(filenamexdlolkek);
        return 5;
    }
    while(!feof(filenamexdlolkek)) {
        char buffer;
        if(fread(&buffer, sizeof(char), 1, filenamexdlolkek) == 1) {
            fwrite(&buffer, sizeof(char), 1, chinazes);
        }
    }
    fclose(chinazes);
    fclose(filenamexdlolkek);
    printf("File copied\n");
    return 0;
}

