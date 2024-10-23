#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "tested_declarations.h"
#include "rdebug.h"

int stack_push(struct stack_t **stack, char value) {
    if (!stack) {
        return 1;
    }

    struct stack_t *new_node = (struct stack_t *)malloc(sizeof(struct stack_t));
    if (new_node == NULL) {
        return 2;
    }

    new_node->character = value;
    new_node->prev = *stack;
    *stack = new_node;
    return 0;
}

char stack_pop(struct stack_t **stack, int *err_code) {
    if (err_code != NULL) *err_code = 0;

    if (!stack || !*stack) {
        if (err_code != NULL) *err_code = 1;
        return '\0';
    }

    struct stack_t *top_node = *stack;
    char value = top_node->character;
    *stack = top_node->prev;
    free(top_node);

    if (err_code != NULL) *err_code = 0;
    return value;
}

void stack_display(const struct stack_t *stack) {
    const struct stack_t *current = stack;
    while (current) {
        printf("%c ", current->character);
        current = current->prev;
    }
    printf("\n");
}

void stack_destroy(struct stack_t **stack) {
    if (!stack || !*stack) {
        return;
    }
    while (*stack) {
        struct stack_t *current = *stack;
        *stack = (*stack)->prev;
        free(current);
    }
}

int stack_empty(const struct stack_t *stack) {
    return stack == NULL ? 1 : 0;
}

int precedence(char op) {
    switch (op) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        default:
            return 0;
    }
}

void process_expression(char *expression) {
    struct stack_t *operators = NULL;
    char *token = strtok(expression, " ");
    while (token != NULL) {
        if (isdigit(*token) || (*token == '-' && isdigit(*(token + 1)))) {
            printf("%s ", token);
        } else if (strchr("+-*/", *token) != NULL) {
            while (!stack_empty(operators) && precedence(operators->character) >= precedence(*token)) {
                int err_code;
                char op = stack_pop(&operators, &err_code);
                if (err_code == 0) {
                    printf("%c ", op);
                }
            }
            if (stack_push(&operators, *token) != 0) {
                printf("Failed to allocate memory\n");
                stack_destroy(&operators);
                exit(8);
            }
        } else if (*token == '(') {
            if (stack_push(&operators, *token) != 0) {
                printf("Failed to allocate memory\n");
                stack_destroy(&operators);
                exit(8);
            }
        } else if (*token == ')') {
            int err_code;
            char top;
            while (!stack_empty(operators) && (top = stack_pop(&operators, &err_code)) != '(') {
                printf("%c ", top);
            }
            if (err_code != 0) {
                printf("Incorrect input\n");
                stack_destroy(&operators);
                exit(1);
            }
        }
        token = strtok(NULL, " ");
    }

    while (!stack_empty(operators)) {
        int err_code;
        char op = stack_pop(&operators, &err_code);
        if (err_code == 0) {
            printf("%c ", op);
        }
    }

    stack_destroy(&operators);
}

int main(void) {
    char *expression = NULL;
    size_t bufsize = 0;

    printf("Enter expression: ");
    if (getline(&expression, &bufsize, stdin) != -1) {
        int len = (int)strlen(expression);
        if (len > 0 && *(expression + len - 1) == '\n') {
            *(expression + len - 1) = '\0';
        }

        if (len > 0 && strcmp(expression, "") != 0) {
            process_expression(expression);
        }
    }

    return 0;
}

