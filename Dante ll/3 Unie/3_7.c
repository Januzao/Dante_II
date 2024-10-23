#include <stdio.h>
#include "tested_declarations.h"
#include "rdebug.h"

union double_to_char_t {
    double d;
    char tab[8];
};

void clear_input_buffer() {
    while (getchar() != '\n');
}

int save_double(const union double_to_char_t *dtc, const char *filename) {
    if (dtc == NULL || filename == NULL) return 1;

    FILE *f = fopen(filename, "wb");
    if (f == NULL) return 2;

    int result = fwrite(dtc->tab, sizeof(union double_to_char_t), 1, f) == 1 ? 0 : 3;
    fclose(f);

    return result;
}

int load_double(union double_to_char_t *dtc, const char *filename) {
    if (dtc == NULL || filename == NULL) return 1;

    FILE *f = fopen(filename, "rb");
    if (f == NULL) return 2;

    int result = fread(dtc->tab, sizeof(union double_to_char_t), 1, f) == 1 ? 0 : 3;
    fclose(f);

    return result;
}

int main() {
    double kek;
    union double_to_char_t p;
    char filename[40];
    int input_result, status;

    printf("Input double:");
    input_result = scanf("%lf", &kek);
    clear_input_buffer();

    switch(input_result) {
        case 1:
            p.d = kek;
            break;
        default:
            printf("Incorrect input\n");
            return 1;
    }

    printf("Enter filename to save:");
    scanf("%39[^\n]", filename);
    clear_input_buffer();

    status = save_double(&p, filename);

    switch(status) {
        case 2:
            printf("Couldn't create file\n");
            return 5;
        case 3:
            printf("File corrupted\n");
            return 6;
        default:
            printf("File saved\n");
            break;
    }

    printf("Enter filename to load: ");
    scanf("%39[^\n]", filename);
    clear_input_buffer();

    status = load_double(&p, filename);

    switch(status) {
        case 2:
            printf("Couldn't open file\n");
            return 4;
        case 3:
            printf("File corrupted\n");
            return 6;
        default:
            printf("%lf", p.d);
            break;
    }

    return 0;
}

