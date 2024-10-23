#include <stdio.h>
#include <math.h>
#include <float.h>
#include <ctype.h>
#include "color.h"
#include "tested_declarations.h"
#include "rdebug.h"


int is_decimal_separator(char ch) {
    return ch == '.' || ch == ',';
}

int validate_file_content(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        return -2;
    }
    int ch;
    while ((ch = fgetc(file)) != EOF) {
        if (!isdigit(ch) && !isspace(ch) && !is_decimal_separator(ch)) {
            fclose(file);
            return -3;
        }
    }

    fclose(file);
    return 0;
}


int load_colors_t(const char *filename, struct color_t *p, int N) {
    if (filename == NULL || p == NULL || N <= 0) {
        return -1;
    }

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        return -2;
    }
    if (validate_file_content(filename) == -3) {
        fclose(file);
        return -3;
    }
    int count = 0;
    while (count < N) {
        int result = fscanf(file, "%f %f %f %d", &(p + count)->r, &(p + count)->g, &(p + count)->b, (int *) &((p + count)->c));
        if (result == 4) {
            count++;
        } else {
            fclose(file);
            return -3;
        }
    }

    fclose(file);

    if (count > 0) {
        return count;
    } else if (count == 0 && !feof(file)) {
        return -3;
    } else {
        return 0;
    }
}

float distance(const struct color_t *p1, const struct color_t *p2, int *err_code) {
    if (p1 == NULL || p2 == NULL) {
        if (err_code != NULL) *err_code = 1;
        return -1;
    }

    float dr = p2->r - p1->r;
    float dg = p2->g - p1->g;
    float db = p2->b - p1->b;
    float dist = sqrt(dr * dr + dg * dg + db * db);

    if (err_code != NULL) *err_code = 0;
    return dist;
}

enum colors find_nearest_neighbour(const struct color_t *database, int size,
                                   const struct color_t *unknown, int *err_code) {
    if (database == NULL || unknown == NULL || size <= 0) {
        if (err_code != NULL) *err_code = 1;
        return UNKNOWN;
    }

    take_this xddddd;
    float* distances = (float*)&xddddd;

    int nearest_index = -1;
    float min_distance = FLT_MAX;

    for (int i = 0; i < size; ++i) {
        int err;
        float dist = distance(database + i, unknown, &err);
        *(distances+i) = dist;
        if (err != 0) {
            if (err_code != NULL) *err_code = 1;
            return UNKNOWN;
        }

    }
    for (int j = 0; j < size; ++j) {
        if (*(distances+j) < min_distance) {
            nearest_index = j;
            min_distance = *(distances+j);
        }
    }
    for (int k = 0; k < size; ++k) {
        for (int i = k+1; i < size; ++i) {
            if (*(distances + i) == *(distances + k)){
                if ((database + i)->c != (database + k)->c){
                    if (err_code != NULL) *err_code = 2;
                    return UNKNOWN;
                }
            }
        }
    }

    if (nearest_index != -1) {
        if (err_code != NULL) *err_code = 0;
        return (database + nearest_index)->c;
    } else {
        if (err_code != NULL) *err_code = 0;
        return UNKNOWN;
    }
}

void clearBuffer() {
    char c;
    do {
        c = getchar();
    } while (c != '\n' && c != EOF);
}

int main() {
    char filename[31];
    printf("Podaj sciezke:");
    if (scanf("%30s", filename) != 1) {
        printf("Incorrect input\n");
        return 0;
    }
    clearBuffer();

    struct color_t colors[100];
    int colors_count = load_colors_t(filename, colors, 100);
    if (colors_count == -2) {
        printf("Couldn't open file\n");
        return 4;
    } else if (colors_count == -3) {
        printf("File corrupted\n");
        return 6;
    } else if (colors_count <= 0) {
        printf("Incorrect input\n");
        return 1;
    }

    struct color_t unknown;
    while (1) {
        printf("Podaj skladowe koloru:");
        if (scanf("%f %f %f", &(unknown.r), &(unknown.g), &(unknown.b)) != 3) {
            printf("Incorrect input\n");
            return 0;
        }

        int err_code;
        enum colors result = find_nearest_neighbour(colors, colors_count, &unknown, &err_code);
        if (err_code == 1) {
            printf("Incorrect input\n");
            return 0;
        } else if (err_code == 2) {
            printf("UNKNOWN\n");
        } else {
            switch (result) {
                case RED:
                    printf("RED\n");
                    break;
                case GREEN:
                    printf("GREEN\n");
                    break;
                case BLUE:
                    printf("BLUE\n");
                    break;
                case YELLOW:
                    printf("YELLOW\n");
                    break;
                default:
                    printf("UNKNOWN\n");
                    break;
            }
        }
    }
}


