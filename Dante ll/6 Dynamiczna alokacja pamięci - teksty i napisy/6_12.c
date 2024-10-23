#include <stdio.h>
#include <stdlib.h>
#include "tested_declarations.h"
#include "rdebug.h"

void clear_input_buffer() {
    int ch;
    while ((ch = getchar()) != '\n');
}


int main() {
    const int size = 50;
    char *text = NULL;
    int current_size = 0;
    text = realloc(NULL, sizeof(char) * 50);
    if (!text){
        printf("failed to allocate memory");
        return 8;
    }
    printf("Podaj tekst:");
    int ch;
    int count = 0;


    while ((ch = getchar()) != '\n') {
        if (count >= current_size  - 1) {
            char *new_text = realloc(text, current_size + size);
            if (new_text == NULL) {
                if (text == NULL) {
                    printf("failed to allocate memory");
                    return 8;
                } else {
                    scanf("%s", new_text);
                    clear_input_buffer();
                    *(text + count) = '\0';
                    printf("%s", text);
                    free(text);
                    return 0;
                }
            }
            text = new_text;
            current_size += size;
        }

        *(text + count) = (char)ch;
        count++;

    }

    if (text != NULL) {
        *(text + count) = '\0';
        printf("%s", text);
        free(text);
    }

    return 0;
}
