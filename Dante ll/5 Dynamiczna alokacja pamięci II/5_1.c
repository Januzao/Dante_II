#include <stdlib.h>
#include <stdio.h>
#include "tested_declarations.h"
#include "rdebug.h"

#define DES 10

int main(){
    int **tablica = malloc(DES * sizeof(int*));
    if (tablica  == NULL){
        printf("Failed to allocate memory");
        return 8;
    }
    for (int i = 0; i < DES; ++i) {
        *(tablica + i) = malloc(DES * sizeof(int));
        if (*(tablica + i) == NULL){
            printf("Failed to allocate memory");
            for (int j = 0; j < i; ++j) {
                free(*(tablica + j));
            }
            free(tablica);
            return 8;
        }
    }

    for (int i = 0; i < DES; i++) {
        for (int j = 0; j < DES; j++) {
            *(*(tablica + i) + j) = (i + 1) * (j + 1);
        }
    }

    for (int i = 0; i < DES; ++i) {
        for (int j = 0; j < DES; ++j) {
            printf("%3d ", *(*(tablica + i) + j));
        }
        printf("\n");
    }

    for (int i = 0; i < DES; ++i) {
        free(*(tablica + i));
    }
    free(tablica);

    return 0;
}

