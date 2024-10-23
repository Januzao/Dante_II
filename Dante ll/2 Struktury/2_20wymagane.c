#include <stdio.h>
#include "tested_declarations.h"
#include "rdebug.h"

struct message_t
{
    char a;
    double b;
    int c;
};

int load_data(struct message_t *cp, int size, const char *filename) {
    FILE *file;
    if (size <= 0 || cp == NULL || filename == NULL){
        return -1;
    }
    file = fopen(filename, "rb");
    if (file == NULL) {
        return -2;
    }

    unsigned int n;
    int element = 0;

    for (int i = 0; i < size; ++i) {
        fread(&n, sizeof(unsigned int), 1, file);
        n *= 8;
        if (n % 24 != 0) {
            fclose(file);
            return -3;
        } else if (n < 24){
            fclose(file);
            return -3;
        }
        for (int j = 0; j < (int)(n / 24); ++j) {
            if (element >= size) break;
            if (fread((cp + i++), sizeof(struct message_t), 1, file) != 1) {
                if (feof(file) != 0) {
                    fclose(file);
                    return element;
                }
                fclose(file);
                return -3;
            } else {
                element++;
            }
        }
    }
    fclose(file);
    return element;
}
int decode_message(const struct message_t *cp, int size, char *msg, int text_size) {
    if(cp == NULL || size <= 0 || msg == NULL || text_size <= 0) return 1;

    const char *ptr = (const char *)cp;
    int msg_index = 0;

    for (int i = 0; i < size; ++i) {
        ptr += 1;

        for (int j = 0; j < 7; ++j) {
            if (msg_index >= text_size - 1) {
                *(msg + msg_index) = '\0';
                return 0;
            }
            *(msg + msg_index++) = *ptr++;
        }

        ptr += 12;

        for (int k = 0; k < 4; ++k) {
            if (msg_index >= text_size - 1) {
                *(msg + msg_index) = '\0';
                return 0;
            }
            *(msg + msg_index++) = *ptr++;
        }
    }

    *(msg + msg_index) = '\0';
    return 0;
}

int main(){
    struct message_t ukrytawiadomosc[100];
    char filename[31];

    printf("Enter file name:");
    char text[1101];
    scanf("%30s", filename);

    int result = load_data(ukrytawiadomosc, 100, filename);
    switch (result) {
        case -2:
            printf("Couldn't open file");
            return 4;
        case -3:
            printf("File corrupted");
            return 6;
    }

    decode_message(ukrytawiadomosc, result, text, 1101);
    printf("%s", text);

    return 0;
}
