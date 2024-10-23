#include <stdio.h>
#include <stdlib.h>
#include "tested_declarations.h"
#include "rdebug.h"
int main(){

    int *temp = (int *)malloc(sizeof(int) * 100);
    if(temp == NULL){
        printf("Failed to allocate memory");
        return 8;
    }
    for (int i = 0; i < 100; ++i) {
        *(temp + i) = i;
    }

    for (int i = 0; i < 100; ++i) {
        printf("%d ", *(temp + i));
    }
    free(temp);
    return 0;
}
