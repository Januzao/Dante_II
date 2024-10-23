#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
#include "tested_declarations.h"
#include "rdebug.h"

int stack_init(struct stack_t **stack, int N) {
    if (!stack || N < 1) {
        return 1;
    }

    *stack = (struct stack_t *) malloc(sizeof(struct stack_t));
    if (*stack == NULL) {
        return 2;
    }

    (*stack)->data = (int *) calloc(N, sizeof(int));
    if ((*stack)->data == NULL) {
        free(*stack);
        *stack = NULL;
        return 2;
    }

    (*stack)->head = 0;
    (*stack)->capacity = N;

    return 0;
}

int stack_push(struct stack_t *stack, int value) {
    if (!stack || !stack->data || stack->capacity <= 0 || stack->head < 0 ||
        stack->head > stack->capacity) {
        return 1;
    }

    if (stack->head == stack->capacity) {
        int *new_data = (int *) realloc(stack->data, stack->capacity * 2 * sizeof(int));
        if (new_data == NULL) {
            return 2;
        }
        stack->capacity *= 2;
        stack->data = new_data;
    }

    *(stack->data + stack->head) = value;
    stack->head++;

    return 0;
}

int stack_pop(struct stack_t *stack, int *err_code) {
    if (err_code != NULL) *err_code = 0;

    if (!stack || !stack->data || stack->capacity <= 0 || stack->head < 0 ||
        stack->head > stack->capacity) {
        if (err_code != NULL) *err_code = 1;
        return 1;
    }

    if (stack->head == 0) {
        if (err_code) *err_code = 2;
        return 2;
    }

    int value = *(stack->data + --stack->head);
    if (err_code) *err_code = 0;
    return value;
}

void stack_display(const struct stack_t *stack) {
    if (stack != NULL && stack->data != NULL && stack->capacity > 0 && stack->head > 0 && stack->head <= stack->capacity)
        for (int i = stack->head - 1; i >= 0; i--) {
            printf("%d ", *(stack->data + i));
        }
}

void stack_free(struct stack_t *stack) {
    if (stack == NULL) {
        return;
    }

    free(stack->data);
    free(stack);
}

int main(void) {
    struct stack_t *stack = NULL;
    int initial_capacity = 10;

    int init_result = stack_init(&stack, initial_capacity);
    if (init_result != 0) {
        printf("Failed to allocate memory\n");
        return 8;
    }

    int choice;
    while (1) {
        printf("Co chcesz zrobic? ");
        if (scanf("%d", &choice) != 1) {
            printf("Incorrect input\n");
            stack_free(stack);
            return 1;
        }

        if (choice == 0) {
            break;
        } else if (choice == 1) {
            int value;
            printf("Podaj liczbe ");
            if (scanf("%d", &value) != 1) {
                printf("Incorrect input\n");
                stack_free(stack);
                return 1;
            }
            int result = stack_push(stack, value);
            if (result == 1) {
                printf("Incorrect input data\n");
            } else if (result == 2) {
                printf("Failed to allocate memory\n");
                stack_free(stack);
                return 8;
            }
        } else if (choice == 2) {
            int err_code;
            int value = stack_pop(stack, &err_code);
            if (err_code == 0) {
                printf("%d\n", value);
            } else if (err_code == 1) {
                printf("Incorrect input data\n");
            } else if (err_code == 2) {
                printf("Stack is empty\n");
            }
        } else if (choice == 3) {
            if (stack->head == 0) {
                printf("Stack is empty\n");
            } else {
                stack_display(stack);
                printf("\n");
            }
        } else {
            printf("Incorrect input data\n");
        }
    }

    stack_free(stack);
    return 0;
}

