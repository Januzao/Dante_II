#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "tested_declarations.h"
#include "rdebug.h"


int fsize(FILE *fp) {
    if (!fp) { return 0; }
    int size = 0;
    fseek(fp, 0, SEEK_END);
    size = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    return size;
}
int check_digit(FILE *fp) {
    int c;
    while ((c = fgetc(fp)) != EOF){
        if (!isdigit(c) && c != '\n' && c != ' '){
            return 3;
        }
    }
    fseek(fp, 0, SEEK_SET);
    return 0;
}

int encode(const char *input, char *txt, const char *output) {
    if (input == NULL || txt == NULL || output == NULL) {
        return 1;
    }

    FILE *fp_in = fopen(input, "r");
    if (fp_in == NULL) {
        return 2;
    }
    if (check_digit(fp_in)){
        fclose(fp_in);
        return 3;
    }
    int asd = fsize(fp_in);
    if (strlen(txt) > (size_t)asd / 8) {
        fclose(fp_in);
        return 3;
    }

    FILE *fp_out = fopen(output, "w");
    if (fp_out == NULL) {
        fclose(fp_in);
        return 4;
    }

    int c;
    size_t bitIndex = 0;
    size_t textBits = strlen(txt) * 8;
    char buffer[20];
    int bufferIndex = 0;

    while ((c = fgetc(fp_in)) != EOF) {
        if (c == ' ' || c == '\n') {
            if (bufferIndex > 0) {
                *(buffer + bufferIndex) = '\0';
                long pixelValue = strtol(buffer, NULL, 10);

                if (bitIndex < textBits + 8) {
                    if ((*(txt + bitIndex / 8) >> (7 - bitIndex % 8)) & 1) {
                        pixelValue |= 1;
                    } else {
                        pixelValue &= ~1;
                    }
                    bitIndex++;
                } else {
                    pixelValue &= ~1;
                    bitIndex++;
                }

                fprintf(fp_out, "%ld", pixelValue);
                bufferIndex = 0;

                int oldc = c;
                c = fgetc(fp_in);
                if (isdigit(c)) {
                    ungetc(c, fp_in);
                    c = oldc;
                }

                if (c == '\n') {
                    fputc(oldc, fp_out);
                    fputc('\n', fp_out);
                } else {
                    fputc(' ', fp_out);
                }
            }
        } else if (c >= '0' && c <= '9') {
            *(buffer + bufferIndex++) = c;
        } else {
            fclose(fp_in);
            fclose(fp_out);
            return 3;
        }
    }

    if (bitIndex < textBits) {
        fclose(fp_in);
        fclose(fp_out);
        return 3;
    }

    fclose(fp_in);
    fclose(fp_out);
    return 0;
}


int decode(const char *filename, char *txt, int size) {
    if (filename == NULL || txt == NULL || size <= 0) {
        return 1;
    }

    FILE *file = fopen(filename, "r");
    if (!file) return 2;

    int pixelValue;
    int bitCounter = 0;
    char currentChar = 0;
    int txtIndex = 0;
    int valueRead;

    while ((valueRead = fscanf(file, "%d", &pixelValue)) == 1 && txtIndex < size - 1) {
        currentChar = (currentChar << 1) | (pixelValue & 1);
        bitCounter++;

        if (bitCounter == 8) {
            *(txt + txtIndex++) = currentChar;
            bitCounter = 0;
            currentChar = 0;
        }
    }

    *(txt + txtIndex) = '\0';
    fclose(file);

    if (valueRead != 1 || bitCounter > 0) {
        return 3;
    }

    return txtIndex > 0 ? 0 : 3;
}


int main() {
    char action;
    printf("Enter 'e' to encode or 'd' to decode:");
    scanf(" %c", &action);

    if (action == 'e' || action == 'E') {
        char txt[1000];
        char input[30], output[30];

        printf("Enter the text to hide (max 1000 characters):");
        scanf(" %999[^\n]", txt);

        printf("Enter the source image file name (max 29 characters):");
        scanf(" %29s", input);

        printf("Enter the output file name (max 29 characters):");
        scanf(" %29s", output);

        int result = encode(input, txt, output);
        switch (result) {
            case 0:
                printf("File saved");
                return 0;
            case 2:
                printf("Couldn't open file");
                return 4;
            case 3:
                printf("File corrupted");
                return 6;
            case 4:
                printf("Couldn't create file");
                return 5;
        }
    } else if (action == 'd' || action == 'D') {
        char filename[30];
        char txt[1000];

        printf("Enter the source image file name (max 29 characters): ");
        scanf(" %29s", filename);

        int result = decode(filename, txt, sizeof(txt));
        if (result == 0) {
            printf("%s", txt);
        } else {
            switch (result) {
                case 2:
                    printf("Couldn't open file");
                    return 4;
                case 3:
                    printf("File corrupted");
                    return 6;
            }
        }
    } else {
        printf("Incorrect input data");
        return 1;
    }

    return 0;
}

