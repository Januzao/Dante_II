#include <stdio.h>
#include <stdlib.h>
#include "functions.h"
#include "tested_declarations.h"
#include "rdebug.h"

CREATE_READ_FUNCTIONS(int, "%d")
CREATE_SORT_FUNCTIONS(int)
CREATE_DISPLAY_FUNCTIONS(int, "%d")

CREATE_READ_FUNCTIONS(float, "%f")
CREATE_SORT_FUNCTIONS(float)
CREATE_DISPLAY_FUNCTIONS(float, "%f")

CREATE_READ_FUNCTIONS(double, "%lf")
CREATE_SORT_FUNCTIONS(double)
CREATE_DISPLAY_FUNCTIONS(double, "%lf")

int main() {
    int type;
    printf("Choose your type: ");
    if (scanf("%d", &type) != 1) {
        printf("Incorrect input\n");
        return 1;
    }

    if (type < 0 || type > 2) {
        printf("Incorrect input data\n");
        return 2;
    }

    int size;
    printf("Enter array size: ");
    if (scanf("%d", &size) != 1) {
        printf("Incorrect input\n");
        return 1;
    } else if (size <= 0){
        printf("Incorrect input data\n");
        return 2;
    }

    if (type == 0) {
        int *data = malloc(size * sizeof(int));
        if (!data) {
            printf("Failed to allocate memory\n");
            return 8;
        }

        printf("Enter numbers: ");
        int result = read_int(data, size);
        if (result == 1) {
            printf("Incorrect input\n");
            free(data);
            return 1;
        } else if (result == 2) {
            printf("Incorrect input\n");
            free(data);
            return 1;
        }

        sort_int(data, size);
        display_int(data, size);

        free(data);
    } else if (type == 1) {
        float *data = malloc(size * sizeof(float));
        if (!data) {
            printf("Failed to allocate memory\n");
            return 8;
        }

        printf("Enter numbers: ");
        int result = read_float(data, size);
        if (result == 1) {
            printf("Incorrect input\n");
            free(data);
            return 1;
        } else if (result == 2) {
            printf("Incorrect input\n");
            free(data);
            return 1;
        }

        sort_float(data, size);
        display_float(data, size);

        free(data);
    } else if (type == 2) {
        double *data = malloc(size * sizeof(double));
        if (!data) {
            printf("Failed to allocate memory\n");
            return 8;
        }

        printf("Enter numbers: ");
        int result = read_double(data, size);
        if (result == 1) {
            printf("Incorrect input\n");
            free(data);
            return 1;
        } else if (result == 2) {
            printf("Incorrect input\n");
            free(data);
            return 1;
        }

        sort_double(data, size);
        display_double(data, size);

        free(data);
    }

    return 0;
}

