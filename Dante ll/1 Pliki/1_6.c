#include <stdio.h>
#include "tested_declarations.h"
#include "rdebug.h"

int main() {
    FILE *file_0 = fopen("0.txt", "w");
    FILE *file_2 = fopen("2.txt", "w");
    FILE *file_3 = fopen("3.txt", "w");
    FILE *file_5 = fopen("5.txt", "w");

    if (file_2 == NULL || file_3 == NULL || file_5 == NULL || file_0 == NULL) {
        printf("Couldn't create file\n");
        if (file_2 != NULL) fclose(file_2);
        if (file_3 != NULL) fclose(file_3);
        if (file_5 != NULL) fclose(file_5);
        if (file_0 != NULL) fclose(file_0);
        return 5;
    }

    printf("Podaj liczby:\n");

    int num;
    while (1) {
        scanf("%d", &num);

        if (num == 0)
            break;

        if (num % 2 == 0)
            fprintf(file_2, "%d\n", num);
        if (num % 3 == 0)
            fprintf(file_3, "%d\n", num);
        if (num % 5 == 0)
            fprintf(file_5, "%d\n", num);
        if (num % 2 != 0 && num % 3 != 0 && num % 5 != 0) // Число не ділиться на 2, 3 або 5 без остачі
            fprintf(file_0, "%d\n", num);
    }

    printf("Files saved\n");

    fclose(file_2);
    fclose(file_3);
    fclose(file_5);
    fclose(file_0);

    return 0;
}

