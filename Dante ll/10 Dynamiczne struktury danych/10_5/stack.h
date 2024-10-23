#ifndef UNTITLED1_STACK_H
#define UNTITLED1_STACK_H

struct stack_t {
    char character;
    struct stack_t *prev;
};

int stack_push(struct stack_t **stack, char value);
char stack_pop(struct stack_t **stack, int *err_code);
void stack_display(const struct stack_t *stack);
void stack_destroy(struct stack_t **stack);
int stack_empty(const struct stack_t *stack);

#endif //UNTITLED1_STACK_H
