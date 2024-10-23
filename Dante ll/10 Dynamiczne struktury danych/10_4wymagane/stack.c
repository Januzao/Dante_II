#include "stack.h"
#include "tested_declarations.h"
#include "rdebug.h"
#define ONE 1

int stack_push(struct stack_t **stack, char *value) {
    if (!stack || !value) {
        return 1;
    }
    struct stack_t *new_elem = (struct stack_t *)malloc(sizeof(struct stack_t));
    if (!new_elem) {
        return 2;
    }
    new_elem->sentence = value;
    new_elem->prev = *stack;
    *stack = new_elem;
    return 0;
}

char *stack_pop(struct stack_t **stack, int *err_code) {
    if (!stack || !*stack) {
        if (err_code) {
            *err_code = 1;
        }
        return NULL;
    }
    struct stack_t *top = *stack;
    char *value = top->sentence;
    *stack = top->prev;
    free(top);
    if (err_code) {
        *err_code = 0;
    }
    return value;
}

void stack_destroy(struct stack_t **stack) {
    if (!stack) {
        return;
    }
    struct stack_t *current = *stack;
    while (current) {
        struct stack_t *next = current->prev;
        free(current->sentence);
        free(current);
        current = next;
    }
    *stack = NULL;
}

int stack_load(struct stack_t **stack, const char *filename) {
    if (!stack || !filename || (*stack) != NULL) {
        return 1;
    }
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        return 2;
    }

    stack_destroy(stack);

    fpos_t pos;
    while (!feof(file)) {
        fgetpos(file, &pos);
        char asd = fgetc(file);
        int count = ONE;

        for (; asd != '.' && asd != '\0' && asd != EOF; asd = fgetc(file)) {
            count++;
        }
        if (asd == '\0' || asd == EOF) {
            break;
        }

        fsetpos(file, &pos);
        char *sentence = malloc((count + ONE) * sizeof(char));
        if (sentence == NULL) {
            stack_destroy(stack);
            fclose(file);
            return 3;
        }

        asd = fgetc(file);
        count = 0;
        for (count = 0; asd != '.'; asd = fgetc(file)) {
            *(sentence + count) = asd;
            count++;
        }
        *(sentence + count++) = asd;
        *(sentence + count) = '\0';

        int push_result = stack_push(stack, sentence);
        if (push_result != 0) {
            free(sentence);
            stack_destroy(stack);
            fclose(file);
            return 3;
        }
    }
    fclose(file);
    return 0;
}


int stack_save(const struct stack_t *stack, const char *filename) {
    if (!stack || !filename) {
        return 1;
    }
    FILE *file = fopen(filename, "w");
    if (!file) {
        return 2;
    }
    const struct stack_t *current = stack;
    while (current) {
        fprintf(file, "%s", current->sentence);
        current = current->prev;
    }
    fclose(file);
    return 0;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Not enough arguments\n");
        return 9;
    }

    for (int i = 1; i < argc; i++) {
        struct stack_t *stack = NULL;
        int load_result = stack_load(&stack, *(argv + i));
        if (load_result == 2) {
            printf("Couldn't open file %s\n", *(argv + i));
            continue;
        } else if (load_result == 3) {
            printf("Failed to allocate memory\n");
            stack_destroy(&stack);
            return 8;
        }

        int save_result = stack_save(stack, *(argv + i));
        if (save_result == 2) {
            printf("Couldn't create file\n");
            stack_destroy(&stack);
            return 5;
        } else if (save_result == 0) {
            printf("File %s saved\n", *(argv + i));
        }

        stack_destroy(&stack);
    }

    return 0;
}

