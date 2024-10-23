#include <stdio.h>
#include <stdlib.h>
#include "tested_declarations.h"
#include "rdebug.h"


int main() {
    char filename[31];
    char index[31] = {'\0'};
    FILE *file;

    printf("Podaj sciezke do pliku:\n");
    scanf("%30s", filename);

    file = fopen(filename, "r");
    if (file == NULL) {
        printf("Couldn't open file\n");
        return 4;
    }
    int kaunt = 0;
    for (;;) {
        char i = fgetc(file);
        if (i == EOF) break;
        kaunt++;
    }
    if (kaunt == 0){
        printf("File corrupted");
        fclose(file);
        return 6;
    }
    fseek(file, 0, SEEK_SET);


    int kursor = 0;
    char c;
    int i = 0;
    while ((c = fgetc(file)) != EOF) {
        if (c == '\n') break;
        if (c != ' ' && (c < '0' || c > '9')) {
            printf("File corrupted");
            fclose(file);
            return 6;
        }
        if (c >= '0' && c <= '9') {
            *(index + i) = c;
            i++;
            kursor++;
        }
        if (c == ' ') {
            kursor++;
            int temp;
            temp = atoi(index);
            fseek(file, 0, SEEK_SET);
            if (kaunt <= temp) {
                printf("File corrupted");
                fclose(file);
                return 6;
            }
            fseek(file, kursor, SEEK_SET);
            for (int j = 0; j < i; ++j) {
                *(index + j) = '\0';
            }
            i = 0;
        }
    }
    int last_index;
    last_index = atoi(index);

    if (last_index > kaunt) {
        printf("File corrupted");
        fclose(file);
        return 6;
    }

    fseek(file, 0, SEEK_SET);
    for (int j = 0; j < i; ++j) {
        *(index + j) = '\0';
    }
    kursor = 0;
    i = 0;
    while ((c = fgetc(file)) != EOF) {
        if (c == '\n') break;
        if (c >= '0' && c <= '9') {
            *(index + i) = c;
            i++;
            kursor++;
        }
        if (c == ' ') {
            kursor++;
            int temp;
            temp = atoi(index);
            int kount = 0;
            fseek(file, 0, SEEK_SET);
            for (;;) {
                char o = fgetc(file);
                if (kount == temp) {
                    printf("%c", o);
                    break;
                }
                kount++;
            }

            fseek(file, kursor, SEEK_SET);

            for (int j = 0; j < i; ++j) {
                *(index + j) = '\0';
            }
            i = 0;
        }
    }
    int text;
    int count = 0;
    text = atoi(index);
    fseek(file, 0, SEEK_SET);
    for (;;) {
        char o = fgetc(file);
        if (count == text) {
            printf("%c", o);
            break;
        }
        count++;
    }
    fclose(file);
    return 0;
}
