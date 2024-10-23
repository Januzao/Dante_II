#include "comparators.h"
#include <stdlib.h>
#include <stdio.h>
#include "tested_declarations.h"
#include "rdebug.h"

int comp_min(const int *ptr1, const int *ptr2, int width) {
    if (!ptr1 || !ptr2 || width <= 0) {
        return 2;
    }
    int min1 = *ptr1;
    int min2 = *ptr2;
    for (int i = 1; i < width; ++i) {
        if (*(ptr1 + i) < min1) {
            min1 = *(ptr1 + i);
        }
        if (*(ptr2 + i) < min2) {
            min2 = *(ptr2 + i);
        }
    }
    return (min1 > min2) - (min1 < min2);
}

int comp_max(const int *ptr1, const int *ptr2, int width) {
    if (!ptr1 || !ptr2 || width <= 0) {
        return 2;
    }
    int max1 = *ptr1;
    int max2 = *ptr2;
    for (int i = 1; i < width; ++i) {
        if (*(ptr1 + i) > max1) {
            max1 = *(ptr1 + i);
        }
        if (*(ptr2 + i) > max2) {
            max2 = *(ptr2 + i);
        }
    }
    return (max1 > max2) - (max1 < max2);
}

int comp_sum(const int *ptr1, const int *ptr2, int width) {
    if (!ptr1 || !ptr2 || width <= 0) {
        return 2;
    }
    int sum1 = 0;
    int sum2 = 0;
    for (int i = 0; i < width; ++i) {
        sum1 += *(ptr1 + i);
        sum2 += *(ptr2 + i);
    }
    return (sum1 > sum2) - (sum1 < sum2);
}

void swap_rows(int **matrix, int row1, int row2) {
    int *temp = *(matrix + row1);
    *(matrix + row1) = *(matrix + row2);
    *(matrix + row2) = temp;
}

int sort_rows(int **matrix, int width, int height, int (*comp)(const int *, const int *, int)) {
    if (!matrix || !comp || width <= 0 || height <= 0) {
        return 1;
    }
    for (int i = 0; i < height - 1; ++i) {
        for (int j = 0; j < height - 1 - i; ++j) {
            if (comp(*(matrix + j), *(matrix + j + 1), width) > 0) {
                swap_rows(matrix, j, j + 1);
            }
        }
    }
    return 0;
}

int main(void) {
    int width, height;
    printf("Enter width and height: ");
    if (scanf("%d %d", &width, &height) != 2) {
        printf("Incorrect input\n");
        return 1;
    }
    if (width <= 0 || height <= 0) {
        printf("Incorrect input data\n");
        return 2;
    }

    int **matrix = (int **)malloc(height * sizeof(int *));
    if (!matrix) {
        printf("Failed to allocate memory\n");
        return 8;
    }
    for (int i = 0; i < height; ++i) {
        *(matrix + i) = (int *)malloc(width * sizeof(int));
        if (!*(matrix + i)) {
            printf("Failed to allocate memory\n");
            for (int j = 0; j < i; ++j) {
                free(*(matrix + j));
            }
            free(matrix);
            return 8;
        }
    }

    printf("Enter data: \n");
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            if (scanf("%d", (*(matrix + i) + j)) != 1) {
                printf("Incorrect input\n");
                for (int k = 0; k < height; ++k) {
                    free(*(matrix + k));
                }
                free(matrix);
                return 1;
            }
        }
    }

    int choice;
    printf("Selection choice: ");
    if (scanf("%d", &choice) != 1) {
        printf("Incorrect input\n");
        for (int i = 0; i < height; ++i) {
            free(*(matrix + i));
        }
        free(matrix);
        return 1;
    } else if ((choice < 0 || choice > 2)){
        printf("Incorrect input data\n");
        for (int i = 0; i < height; ++i) {
            free(*(matrix + i));
        }
        free(matrix);
        return 2;
    }

    int (*comp)(const int *, const int *, int);
    switch (choice) {
        case 0:
            comp = comp_min;
            break;
        case 1:
            comp = comp_max;
            break;
        case 2:
            comp = comp_sum;
            break;
        default:
            printf("Incorrect input data\n");
            for (int i = 0; i < height; ++i) {
                free(*(matrix + i));
            }
            free(matrix);
            return 2;
    }

    if (sort_rows(matrix, width, height, comp) != 0) {
        printf("Failed to sort rows\n");
        for (int i = 0; i < height; ++i) {
            free(*(matrix + i));
        }
        free(matrix);
        return 1;
    }

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            printf("%d ", *(*(matrix + i) + j));
        }
        printf("\n");
    }

    for (int i = 0; i < height; ++i) {
        free(*(matrix + i));
    }
    free(matrix);

    return 0;
}
