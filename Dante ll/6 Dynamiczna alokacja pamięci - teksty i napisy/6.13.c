#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "tested_declarations.h"
#include "rdebug.h"

#define TYS 1000

int function_word_count(const char* word) {
    int length = 0;
    for (; isalpha((unsigned char)*(word + length)); ++length);
    return length;
}

int function_count_sen(const char *text) {
    if (text == NULL)
        return -1;
    if (*text == '\0')
        return 0;

    int count = 0;
    for (int i = 0; *(text + i) != '\0'; ++i) {
        switch (*(text + i)) {
            case '\0':
                return count;
            default:
                if (isalpha(*(text + i)) && !isalpha(*(text + i + 1))) {
                    ++count;
                }
        }
    }
    return count;
}

void destr(int count, char **text){
    for (int j = 0; j < count; ++j) {
        free(*(text + j));
    }
}
char **split_words(const char *text) {
    int count = 0;
    int xount;
    int kount = 0;
    int func_res = function_count_sen(text);
    if (func_res <= 0) return NULL;

    char **tempText = malloc((func_res + 1) * sizeof(char*));
    if (tempText == NULL) return NULL;

    *(tempText + func_res) = NULL;

    while (count < func_res) {
        while (*(text + kount) && !isalpha(*(text + kount))) kount++;

        xount = function_word_count(text + kount);
        if (xount == 0) {
            kount++;
            continue;
        }

        *(tempText + count) = malloc((xount + 1) * sizeof(char));
        if (*(tempText + count) == NULL) {
            destr(count, tempText);
            free(tempText);
            return NULL;
        }
        strncpy(*(tempText + count), text + kount, xount);
        *((*(tempText + count)) + xount) = '\0';

        kount += xount;
        ++count;
    }

    return tempText;
}


int sort_words(char **words) {
    if (words == NULL || *words == NULL) {
        return 1;
    }

    for (char **i = words; *i != NULL; i++) {
        for (char **j = words; *(j + 1) != NULL; j++) {
            if (strcmp(*j, *(j + 1)) > 0) {
                char *temp = *j;
                *j = *(j + 1);
                *(j + 1) = temp;
            }
        }
    }

    return 0;
}

void destroy(char **words) {
    if (!words) {
        return;
    }
    char **p = words;
    while (*p != NULL) {
        free(*p);
        p++;
    }
    free(words);
}

int main() {
    char *input = malloc(TYS * sizeof(char));
    if (input == NULL) {
        printf("Failed to allocate memory");
        return 8;
    }
    printf("Enter text:");
    if (fgets(input, TYS, stdin) == NULL) {
        printf("Error reading input");
        free(input);
        return 1;
    }

    *(input + strcspn(input, "\n")) = '\0';

    if (function_word_count(input) == 0){
        free(input);
        printf("Nothing to show");
        return 0;
    }

    char **words = split_words(input);
    if (words == NULL) {
        printf("Failed to allocate memory");
        free(input);
        return 8;
    }

    if (*words == NULL) {
        printf("Nothing to show");
        free(input);
        free(words);
        return 0;
    }

    if (sort_words(words) != 0) {
        destroy(words);
        free(input);
        printf("Failed to sort words");
        return 2;
    }

    for (char **p = words; *p != NULL; p++) {
        printf("%s\n", *p);
    }

    destroy(words);
    free(input);
    return 0;
}

