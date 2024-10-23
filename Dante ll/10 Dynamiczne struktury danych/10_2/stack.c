#include <stdlib.h>
#include <stdio.h>
#include "stack.h"
#include "tested_declarations.h"
#include "rdebug.h"

int stack_init(struct stack_t **stack) {
    if (!stack) {
        return 1;
    }

    *stack = (struct stack_t *)malloc(sizeof(struct stack_t));
    if (*stack == NULL) {
        return 2;
    }

    (*stack)->head = NULL;
    return 0;
}

int stack_push(struct stack_t *stack, int value) {
    if (!stack) {
        return 1;
    }

    struct node_t *new_node = (struct node_t *)malloc(sizeof(struct node_t));
    if (new_node == NULL) {
        return 2;
    }

    new_node->data = value;
    new_node->next = stack->head;
    stack->head = new_node;
    return 0;
}

void stack_display(const struct stack_t *stack) {
    if (!stack || !stack->head) {
        return;
    }

    struct node_t *current = stack->head;
    while (current) {
        printf("%d ", current->data);
        current = current->next;
    }
}

int stack_pop(struct stack_t* stack, int *err_code){
    if (err_code != NULL) *err_code = 0;

    if (!stack || !stack->head){
        if (err_code != NULL) *err_code = 1;
            return 1;
    }
    struct node_t *top_node = stack->head;
    int value = top_node->data;
    stack->head = top_node->next;
    free(top_node);

    if (err_code != NULL) *err_code = 0;
    return value;
}
void stack_destroy(struct stack_t** stack){
    if (!stack || !*stack){
        return;
    }

    struct node_t *current = (*stack)->head;
    while (current){
        struct node_t *new = current->next;
        free(current);
        current = new;
    }
    free(*stack);
    *stack = NULL;
}
int stack_empty(const struct stack_t* stack){
    if (!stack){
        return 2;
    }

    return stack->head == NULL ? 1 : 0;
}


int main(void){
    struct stack_t *stack = NULL;

    int init_result = stack_init(&stack);
    if (init_result != 0){
        printf("Failed to allocate memory\n");
        return 8;
    }

    int choice;
    while (1){
        printf("Co chcesz zrobic? ");
        if (scanf("%d", &choice) != 1){
            printf("Incorrect input\n");
            stack_destroy(&stack);
            return 1;
        }

        if (choice == 0){
            break;
        } else if (choice == 1){
            int value;
            printf("Podaj liczbe ");
            if (scanf("%d", &value) != 1){
                printf("Incorrect input\n");
                stack_destroy(&stack);
                return 1;
            }
            int result = stack_push(stack, value);
            if (result == 1){
                printf("Incorrect input data\n");
            } else if (result == 2){
                printf("Failed to allocate memory\n");
                stack_destroy(&stack);
                return 8;
            }
        } else if (choice == 2){
            int err_code;
            int value = stack_pop(stack, &err_code);
            if (err_code == 0){
                printf("%d\n", value);
            } else if (err_code == 1){
                printf("Stack is empty\n");
            }
        } else if (choice == 3){
            int empty = stack_empty(stack);
            if (empty == 1){
                printf("1\n");
            } else if (empty == 0){
                printf("0\n");
            } else {
                printf("Incorrect input data\n");
            }
        } else if (choice == 4){
            if (stack->head == NULL){
                printf("Stack is empty\n");
            } else {
                stack_display(stack);
                printf("\n");
            }
        } else {
            printf("Incorrect input data\n");
        }
    }
    stack_destroy(&stack);
    return 0;
}
