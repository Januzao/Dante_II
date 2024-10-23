#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "format_type.h"
#include "tested_declarations.h"
#include "rdebug.h"

struct statistic_t {
    int min;
    int max;
    float avg;
    float standard_deviation;
    int range;
};

int statistics(int **ptr, struct statistic_t **stats) {
    if (stats == NULL || ptr == NULL)
        return 1;
    *stats = (struct statistic_t *) malloc(sizeof(struct statistic_t));

    if (*stats == NULL) {
        return 2;
    }

    if (*ptr != NULL) {
        (*stats)->min = **ptr;
        (*stats)->max = **ptr;
        (*stats)->avg = 0;
        (*stats)->standard_deviation = 0;
    }

    int count = 0;
    for (int i = 0; *(ptr + i) != NULL; i++) {
        for (int j = 0; *(*(ptr + i) + j) != -1; j++) {
            (*stats)->avg += *(*(ptr + i) + j);
            (*stats)->standard_deviation += pow(*(*(ptr + i) + j), 2);
            if ((*stats)->min > *(*(ptr + i) + j)) (*stats)->min = *(*(ptr + i) + j);
            if ((*stats)->max < *(*(ptr + i) + j)) (*stats)->max = *(*(ptr + i) + j);
            count++;
        }
    }

    if (count == 0) {
        free(*stats);
        return 3;
    }

    (*stats)->avg /= count;
    (*stats)->standard_deviation = (*stats)->standard_deviation / count - pow((*stats)->avg, 2);
    (*stats)->standard_deviation = sqrt((*stats)->standard_deviation);
    (*stats)->range = (*stats)->max - (*stats)->min;

    return 0;
}

void display(int **ptr) {
    if (ptr != NULL) {
        for (int i = 0; *(ptr + i) != NULL; i++) {
            for (int j = 0; *(*(ptr + i) + j) != -1; j++) {
                printf("%d ", *(*(ptr + i) + j));
            }
            printf("\n");
        }
    }
}

int save(const char *filename, int **ptr, enum save_format_t format) {
    if ((ptr == NULL) || (filename == NULL))
        return 1;

    FILE *filef;
    int sin, out;

    switch (format) {
        case fmt_text:
            filef = fopen(filename, "w");
            if (filef == NULL) {
                return 2;
            }

            sin = 0;
            while (*(ptr + sin) != NULL) {
                out = 0;
                do {
                    fprintf(filef, "%d ", *(*(ptr + sin) + out));
                } while ((*(*(ptr + sin) + out++)) != -1);
                fprintf(filef, "\n");
                sin++;
            }
            break;

        case fmt_binary:
            filef = fopen(filename, "wb");
            if (filef == NULL)
                return 2;

            sin = 0;
            while (*(ptr + sin) != NULL) {
                out = 0;
                do {
                    fwrite(*(ptr + sin) + out, sizeof(int), 1, filef);
                } while (*(*(ptr + sin) + out++) != -1);
                sin++;
            }
            break;

        default:
            return 1;
    }

    fclose(filef);
    return 0;
}


int main() {
    int A[] = {10, 20, 30, 40, 50, 60, 70, -1};
    int B[] = {100, 200, 300, 400, 500, 600, 700, 800, -1};
    int C[] = {1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, -1};
    int *D[] = {A, B, C, NULL};

    display(D);

    char *filename = (char *) calloc(40, sizeof(char));
    if (filename == NULL) {
        printf("Failed to allocate memory\n");
        return 8;
    }

    printf("Podaj nazwe pliku:");
    scanf("%39s", filename);

    char *txtFilename = malloc(strlen(filename) + 5);
    char *binFilename = malloc(strlen(filename) + 5);
    if (txtFilename == NULL || binFilename == NULL) {
        printf("Failed to allocate memory\n");
        free(filename);
        free(txtFilename);
        free(binFilename);
        return 8;
    }

    sprintf(txtFilename, "%s.txt", filename);
    sprintf(binFilename, "%s.bin", filename);

    int result = save(txtFilename, D, fmt_text);
    printf(result == 0 ? "File saved\n" : "Couldn't create file\n");

    result = save(binFilename, D, fmt_binary);
    printf(result == 0 ? "File saved\n" : "Couldn't create file\n");

    struct statistic_t *stats;
    result = statistics(D, &stats);
    if (result != 0) {
        printf("Failed to allocate memory\n");
    } else {
        printf("%d\n", stats->min);
        printf("%d\n", stats->max);
        printf("%d\n", stats->range);
        printf("%f\n", stats->avg);
        printf("%f\n", stats->standard_deviation);
        free(stats);
    }

    free(filename);
    free(txtFilename);
    free(binFilename);

    return 0;
}

