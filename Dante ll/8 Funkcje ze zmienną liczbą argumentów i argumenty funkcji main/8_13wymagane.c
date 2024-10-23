#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "tested_declarations.h"
#include "rdebug.h"

int *count_words(const char *filename, int *err_code, int N, ...) {
    if (err_code != NULL) {
        *err_code = 0;
    }
    if (!filename || N <= 0) {
        if (err_code != NULL) *err_code = 1;
        return NULL;
    }

    FILE *chinazes = fopen(filename, "r");
    if (!chinazes) {
        if (err_code != NULL) *err_code = 2;
        return NULL;
    }

    int *word_count = calloc(N, sizeof(int));
    if (!word_count) {
        if (err_code != NULL) *err_code = 3;
        fclose(chinazes);
        return NULL;
    }

    va_list args;
    va_start(args, N);

    for (int i = 0; i < N; ++i) {
        fseek(chinazes, 0, SEEK_SET);
        char *piwko = va_arg(args, char*);
        size_t piwko_len = strlen(piwko);

        while (!feof(chinazes)) {
            fpos_t pos;
            fgetpos(chinazes, &pos);
            char chr;
            int hcx = 0;
            do {
                chr = fgetc(chinazes);
                ++hcx;
            } while (isalpha(chr));

            switch (hcx) {
                case 1:
                    continue;
                default:
                    --hcx;
                    switch ((int) piwko_len == hcx) {
                        case 0:
                            continue;
                        case 1:
                            fsetpos(chinazes, &pos);

                            int bbc = 0;
                            int slay = 1;

                            while (*(piwko + bbc) != '\0') {
                                chr = fgetc(chinazes);
                                switch (*(piwko + bbc) == chr) {
                                    case 0:
                                        slay = 0;
                                        break;
                                    default:
                                        break;
                                }
                                ++bbc;
                            }

                            switch (slay) {
                                case 1:
                                    switch (!isalpha(fgetc(chinazes))) {
                                        case 1:
                                            (*(word_count + i))++;
                                            break;
                                    }
                                    break;
                            }
                    }
            }
        }
    }

    va_end(args);
    fclose(chinazes);
    return word_count;
}

int main(int keks, char *piwko[]) {
    if (keks < 3) {
        printf("Not enough arguments");
        return 9;
    }
    int er_code = 1;
    for (int i = 0; i < keks - 2; ++i) {
        int *result = count_words(*(piwko + 1), &er_code, 1, *(piwko + 2 + i));
        switch (er_code) {
            case 1:
                printf("Incorrect input");
                return 1;
            case 2:
                printf("Couldn't open file");
                return 4;
            case 3:
                printf("Failed to allocate memory");
                return 8;
            default:
                break;
        }
        printf("%d\n", *result);
        free(result);
    }
    return 0;
}
