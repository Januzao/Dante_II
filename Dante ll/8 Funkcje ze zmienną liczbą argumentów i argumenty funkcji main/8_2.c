#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "tested_declarations.h"
#include "rdebug.h"

int concatenate(char *out, int size, int num, ...) {
    if (out == NULL || size <= 0 || num <= 0) {
        return 1;
    }

    va_list args;
    va_start(args, num);

    int current_len = 0;
    for (int i = 0; i < num; ++i) {
        char *text = va_arg(args, char*);
        int text_len = (int )strnlen(text, 1000);

        if (current_len + text_len + (i > 0 ? 1 : 0) >= size) {
            va_end(args);
            return 2;
        }

        if (i > 0) {
            *(out + current_len) = ' ';
            current_len++;
        }

        strncpy(out + current_len, text, text_len);
        current_len += text_len;
    }

    *(out + current_len) = '\0';
    va_end(args);

    return 0;
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
            for (int k = 0; k < i; ++k) {
                free(*(texts + k));
            }
            free(texts);
            printf("Failed to allocate memory\n");
            return 8;
        }
    }

    char *res = (char *)calloc(4004, sizeof(char));
    if (res == NULL) {
        for (int k = 0; k < 4; ++k) {
            free(*(texts + k));
        }
        free(texts);
        printf("Failed to allocate memory\n");
        return 8;
    }

    printf("Podaj liczbe tekstow do wprowadzenia: ");
    if (scanf("%d", &n) != 1) {
        printf("Incorrect input\n");
        free(res);
        for (int k = 0; k < 4; ++k) {
            free(*(texts + k));
        }
        free(texts);
        return 1;
    }

    if (n < 2 || n > 4) {
        printf("Incorrect input data\n");
        free(res);
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
            free(res);
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
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
        }
    }

    int result = concatenate(res, 4004, n, *texts, *(texts + 1), *(texts + 2), *(texts + 3));
    if (result == 1) {
        printf("Incorrect input\n");
    } else if (result == 2) {
        printf("Failed to allocate memory\n");
    } else {
        printf("%s", res);
    }

    free(res);
    for (int i = 0; i < 4; ++i) {
        free(*(texts + i));
    }
    free(texts);

    return result == 0 ? 0 : (result == 1 ? 1 : 8);
}

