#include "format_type.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <limits.h>
#include "tested_declarations.h"
#include "rdebug.h"

struct statistic_t {
    int min;
    int max;
    float avg;
    float standard_deviation;
    int range;
};

int binary(const char *filename, int ***ptr) {
    if (!filename || !ptr) {
        return 1;
    }
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        return 2;
    }

    if (feof(file)) {
        fclose(file);
        return 3;
    }
    int ilosc_wierz = 0, value = 0;
    while (!feof(file)) {
        int result = fread(&value, sizeof(int), 1, file);
        if (result != 1 && !feof(file)) {
            fclose(file);
            return 3;
        } else if (value == -1) {
            ilosc_wierz++;
        }
    }

    if (ilosc_wierz == 0) {
        fclose(file);
        return 3;
    }

    int **alocate = (int **) (calloc(ilosc_wierz, sizeof(int *)));
    if (alocate == NULL) {
        fclose(file);
        return 4;
    }

    *(alocate + ilosc_wierz - 1) = NULL;
    int lines = ilosc_wierz;
    lines--;
    rewind(file);

    int i;
    for (i = 0; i < lines; ++i) {
        fpos_t pos;
        fgetpos(file, &pos);
        ilosc_wierz = 0;
        do {
            fread(&value, sizeof(int), 1, file);
            ilosc_wierz++;
        } while (value != -1);
        fsetpos(file, &pos);
        *(alocate + i) = (int *) calloc(ilosc_wierz, sizeof(int));
        if (*(alocate + i) == NULL) {
            for (int j = 0; j < i; ++j) {
                free(*(alocate + j));
            }
            free(alocate);
            fclose(file);
            return 4;
        }
        int j = 0;
        while (j < ilosc_wierz) {
            fread(&value, sizeof(int), 1, file);
            *(*(alocate + i) + j) = value;
            j++;
        }
    }

    *(alocate + lines) = NULL;
    *ptr = alocate;
    fclose(file);
    return 0;
}

int load_text(const char *filename, int ***ptr) {
    if (filename == NULL || ptr == NULL) {
        return 1;
    }
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        return 2;
    }
    int liczba_linij = 0, value = 0;
    if (feof(file)) {
        fclose(file);
        return 3;
    }
    while (!feof(file)) {
        int result = fscanf(file, "%d", &value);
        if (result != 1 && !feof(file)) {
            fclose(file);
            return 3;
        }
        if (value == -1) {
            liczba_linij++;
        }
    }
    if (liczba_linij == 0) {
        fclose(file);
        return 3;
    }
    rewind(file);
    int lines = liczba_linij;
    lines--;
    int **alocate = calloc(liczba_linij, sizeof(int *));
    if (alocate == NULL) {
        fclose(file);
        return 4;
    }
    *(alocate + liczba_linij - 1) = NULL;
    int i = 0;
    while (i < lines) {
        fpos_t pos;
        fgetpos(file, &pos);
        liczba_linij = 0;
        do {
            fscanf(file, "%d", &value);
            liczba_linij++;
        } while (value != -1);
        fsetpos(file, &pos);

        *(alocate + i) = (int *) calloc(liczba_linij, sizeof(int));
        if (*(alocate + i) == NULL) {
            for (int j = 0; j < i; ++j) {
                free(*(alocate + j));
            }
            free(alocate);
            fclose(file);
            return 4;
        }

        int j = 0;
        while (j < liczba_linij) {
            fscanf(file, "%d", &value);
            *(*(alocate + i) + j) = value;
            j++;
        }
        i++;
    }
    *(alocate + lines) = NULL;
    *ptr = alocate;
    fclose(file);
    return 0;
}


int load(const char *filename, int ***ptr, enum save_format_t format) {
    if (filename == NULL || ptr == NULL) {
        return 1;
    }

    switch (format) {
        case fmt_text:
            return load_text(filename, ptr);
        case fmt_binary:
            return binary(filename, ptr);
        default:
            return 1;
    }
}

int statistics_row(int **ptr, struct statistic_t **stats) {
    if (ptr == NULL || stats == NULL)
        return -1;

    int elements = 0;
    while (*(ptr + elements) != NULL)
        elements++;

    *stats = (struct statistic_t *) calloc(elements, sizeof(struct statistic_t));
    if (*stats == NULL) {
        return -2;
    }

    int i = 0;
    while (i < elements) {
        int value = 0;
        float sum = 0.0f;
        float sum_squares = 0.0f;
        int max = **(ptr + i);
        int min = **(ptr + i);

        while (*(*(ptr + i) + value) != -1) {
            int current_value = *(*(ptr + i) + value);
            sum += (float) current_value;
            sum_squares += pow(current_value, 2);
            if (min > current_value)
                min = current_value;
            if (max < current_value)
                max = current_value;
            value++;
        }

        if (value == 0) {
            (*stats + i)->min = -1;
            (*stats + i)->max = -1;
            (*stats + i)->avg = -1;
            (*stats + i)->standard_deviation = -1;
            (*stats + i)->range = -1;
        } else {
            (*stats + i)->min = min;
            (*stats + i)->max = max;
            (*stats + i)->avg = sum / (float) value;
            (*stats + i)->standard_deviation = sum_squares / (float) value - pow((*stats + i)->avg, 2);
            (*stats + i)->standard_deviation = sqrt((*stats + i)->standard_deviation);
            (*stats + i)->range = max - min;
        }
        i++;
    }
    return elements;
}


void destroy(int ***ptr) {
    if (ptr == NULL || *ptr == NULL) {
        return;
    }

    int q = 0;
    while (*(*ptr + q) != NULL) {
        free(*(*ptr + q));
        q++;
    }

    if (*ptr != NULL) {
        free(*ptr);
    }
}

void display(int **ptr) {
    if (ptr == NULL || *ptr == NULL) return;

    for (int i = 0; *(ptr + i) != NULL; i++) {
        for (int j = 0; *(*(ptr + i) + j) != -1; j++) {
            printf("%d ", *(*(ptr + i) + j));
        }
        printf("\n");
    }
}


int stringSwitch(char *txt, char *sub) {
    int len_text = strlen(txt);
    int len_sub = strlen(sub);
    if (len_sub > len_text) {
        return 0;
    }

    int count = 0;
    for (int i = 1; i <= len_sub; ++i) {
        if (*(sub + len_sub - i) == *(txt + len_text - i))
            count++;
    }
    if (count == len_sub)
        return 1;
    return 0;
}

void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}


int main() {
    struct statistic_t *stats;
    char* name = (char*)calloc(40, sizeof(char));
    if (name == NULL) {
        printf("Failed to allocate memory\n");
        return 8;
    }

    int result, result1;
    printf("Podaj nazwe pliku:");
    scanf("%39s", name);
    clear_input_buffer();
    int **temp;

    if (stringSwitch(name, ".txt")) {
        result = load(name, &temp, fmt_text);
        if (result == 1) {
            free(name);
            printf("Incorrect input\n");
            return 1;
        } else if (result == 2) {
            free(name);
            printf("Couldn't open file\n");
            return 4;
        } else if (result == 3) {
            free(name);
            printf("File corrupted\n");
            return 6;
        } else if (result == 4) {
            free(name);
            printf("Failed to allocate memory\n");
            return 8;
        }

        result1 = statistics_row(temp, &stats);
        if (result1 == -1) {
            free(name);
            printf("Incorrect input\n");
            return 1;
        } else if (result1 == -2) {
            free(name);
            printf("Failed to allocate memory\n");
            return 8;
        }

        for (int i = 0; i < result1; ++i) {
            printf("%d %d %d %f %f\n", (stats+i)->min, (stats+i)->max, (stats+i)->range, (stats+i)->avg, (stats+i)->standard_deviation);
        }
        free(name);
        destroy(&temp);
        free(stats);
        return 0;
    } else if (stringSwitch(name, ".bin")) {
        result = load(name, &temp, fmt_binary);
        if (result == 1) {
            free(name);
            printf("Incorrect input\n");
            return 1;
        } else if (result == 2) {
            free(name);
            printf("Couldn't open file\n");
            return 4;
        } else if (result == 3) {
            free(name);
            printf("File corrupted\n");
            return 6;
        } else if (result == 4) {
            free(name);
            printf("Failed to allocate memory\n");
            return 8;
        }

        result1 = statistics_row(temp, &stats);
        if (result1 == -1) {
            free(name);
            printf("Incorrect input\n");
            return 1;
        } else if (result1 == -2) {
            free(name);
            printf("Failed to allocate memory\n");
            return 8;
        }

        for (int i = 0; i < result1; ++i) {
            printf("%d %d %d %f %f\n", (stats+i)->min, (stats+i)->max, (stats+i)->range, (stats+i)->avg, (stats+i)->standard_deviation);
        }
        free(name);
        destroy(&temp);
        free(stats);
        return 0;
    } else {
        free(name);
        printf("Unsupported file format\n");
        return 7;
    }
}

