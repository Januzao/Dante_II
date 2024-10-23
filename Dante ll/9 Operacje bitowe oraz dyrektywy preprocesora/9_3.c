#include <stdio.h>
#include <string.h>
#include "tested_declarations.h"
#include "rdebug.h"

void show(const void* ptr, size_t count) {
    const unsigned char* bytes = (const unsigned char*) ptr;
    for (size_t i = 0; i < count; ++i) {
        printf("%02x ", bytes[i]);
    }
    printf("\n");
}

void inverse_bits(void* ptr, size_t offset, size_t count) {
    if (!ptr || offset + count > 100) {
        return;
    }
    unsigned char* bytes = (unsigned char*) ptr;
    for (size_t i = offset; i < offset + count; ++i) {
        bytes[i] = ~bytes[i];
    }
}

int main() {
    char input[101];

    printf("Podaj tekst: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        printf("Incorrect input\n");
        return 1;
    }

    size_t len = strlen(input);
    if (input[len - 1] == '\n') {
        input[len - 1] = '\0';
        len--;
    }

    len++;

    show(input, len);
    inverse_bits(input, 0, len);
    show(input, len);

    return 0;
}

