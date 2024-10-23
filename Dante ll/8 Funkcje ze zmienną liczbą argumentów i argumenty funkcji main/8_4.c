#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "tested_declarations.h"
#include "rdebug.h"

void clean_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

char* concatenate(int num, ...) {
    if (num <= 0) {
        return NULL;
    }

    va_list args;
    va_start(args, num);

    int total_len = 0;
    for (int i = 0; i < num; ++i) {
        char* text = va_arg(args, char*);
        total_len += (int)strlen(text);
    }
    total_len += (num - 1);

    char* result = (char*)malloc((total_len + 1) * sizeof(char));
    if (result == NULL) {
        va_end(args);
        return NULL;
    }

    va_end(args);
    va_start(args, num);

    *result = '\0';
    for (int i = 0; i < num; ++i) {
        char* text = va_arg(args, char*);
        strcat(result, text);
        if (i < num - 1) {
            strcat(result, " ");
        }
    }

    va_end(args);
    return result;
}

int main(void) {
    int n;
    char **texts = (char **)calloc(4, sizeof(char *));
    if (texts == NULL) {
        printf("Failed to allocate memory\n");
        return 8;
    }

    for (int i = 0; i < 4; ++i) {
        *(texts + i) = (char *)calloc(1001, sizeof(char));
        if (*(texts + i) == NULL) {
            for (int k = 0; k < 4; ++k) {
                if (*(texts + k) != NULL) {
                    free(*(texts + k));
                }
            }
            free(texts);
            printf("Failed to allocate memory\n");
            return 8;
        }
    }

    printf("Podaj liczbe tekstow do wprowadzenia: ");
    if (scanf("%d", &n) != 1) {
        printf("Incorrect input\n");
        for (int k = 0; k < 4; ++k) {
            free(*(texts + k));
        }
        free(texts);
        return 1;
    }

    if (n < 2 || n > 4) {
        printf("Incorrect input data\n");
        for (int k = 0; k < 4; ++k) {
            free(*(texts + k));
        }
        free(texts);
        return 2;
    }

    getchar();
    printf("Podaj teksty: ");
    for (int i = 0; i < n; ++i) {
        if (fgets(*(texts + i), 1001, stdin) == NULL) {
            printf("Incorrect input data\n");
            for (int k = 0; k < 4; ++k) {
                free(*(texts + k));
            }
            free(texts);
            return 2;
        }

        size_t len = strnlen(*(texts + i), 1001);
        if (len > 0 && *(*(texts + i) + len - 1) == '\n') {
            *(*(texts + i) + len - 1) = '\0';
        } else {
            clean_buffer();
        }
    }

    char* result = concatenate(n, *(texts + 0), *(texts + 1), *(texts + 2), *(texts + 3));
    if (result == NULL) {
        printf("Failed to allocate memory\n");
        for (int i = 0; i < 4; ++i) {
            free(*(texts + i));
        }
        free(texts);
        return 8;
    }

    printf("%s", result);

    free(result);
    for (int i = 0; i < 4; ++i) {
        free(*(texts + i));
    }
    free(texts);

    return 0;
}

