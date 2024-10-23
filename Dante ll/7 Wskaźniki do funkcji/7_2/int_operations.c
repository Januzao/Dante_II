#include <stdio.h>
#include "int_operations.h"
#include "tested_declarations.h"
#include "rdebug.h"


int add_int(int a, int b) {
    return a + b;
}

int sub_int(int a, int b) {
    return a - b;
}

int div_int(int a, int b) {
    if (b == 0) {
        return 0;
    }
    return a / b;
}

int mul_int(int a, int b) {
    return a * b;
}

int calculate(int a, int b, int (*operation)(int, int)) {
    return operation(a, b);
}

int (*get_function(operations_t operation))(int, int) {
    int (*funcs[])(int, int) = {add_int, sub_int, div_int, mul_int};
    if (operation < 0 || operation > 3) {
        return NULL;
    }
    return *(funcs + operation);
}

int main() {
    int a, b, operation;
    operations_t op_type;

    printf("Enter numbers: ");
    if (scanf("%d %d", &a, &b) != 2) {
        printf("Incorrect input\n");
        return 1;
    }

    printf("Choose an operation:");
    if (scanf("%d", &operation) != 1) {
        printf("Incorrect input\n");
        return 1;
    }

    if (operation < 0 || operation > 3) {
        printf("Incorrect input data\n");
        return 2;
    }

    op_type = (operations_t)operation;
    int (*operation_func)(int, int) = get_function(op_type);

    if (operation_func == NULL) {
        printf("Incorrect input data\n");
        return 2;
    }

    int result = calculate(a, b, operation_func);
    printf("Result: %d\n", result);

    return 0;
}
