#include "int_operations.h"
#include <stdio.h>
#include "tested_declarations.h"
#include "rdebug.h"


int add_int(int a, int b){
    return a + b;
}
int sub_int(int a, int b){
    return a - b;
}
int div_int(int a, int b){
    if (b == 0){
        return 0;
    }
    return a / b;
}
int mul_int(int a, int b){
    return a * b;
}

int calculate(int a, int b, int(*operation)(int, int)){
    return operation(a, b);
}

int main(void){
    int a, b;
    int (*funcs[4])(int, int) = {add_int, sub_int, div_int, mul_int};
    printf("Enter numbers:");
    if (scanf("%d %d", &a, &b) != 2){
        printf("Incorrect input");
        return 1;
    }

    int operation;
    printf("Choose an operation:");
    if (scanf("%d", &operation) != 1){
        printf("Incorrect input");
        return 1;
    }
    if (operation < 0 || operation > 3) {
        printf("Incorrect input data\n");
        return 2;
    }

    int result = calculate(a, b, *(funcs + operation));
    printf("Result: %d\n", result);

    return 0;
}

