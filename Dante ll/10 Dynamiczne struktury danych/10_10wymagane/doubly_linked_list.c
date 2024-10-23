#include "doubly_linked_list.h"
#include "tested_declarations.h"
#include "rdebug.h"



struct doubly_linked_list_t *dll_create() {
    struct doubly_linked_list_t *dll = calloc(1, sizeof(struct doubly_linked_list_t));
    if (!dll) {
        return NULL;
    }
    dll->head = NULL;
    dll->tail = NULL;
    return dll;
}

int dll_push_back(struct doubly_linked_list_t *dll, int value) {
    if (!dll) return 1;

    struct node_t *new_data = malloc(sizeof(struct node_t));
    if (!new_data) return 2;

    new_data->data = value;
    new_data->next = NULL;
    if (dll->head) {
        new_data->prev = dll->tail;
        dll->tail->next = new_data;
    } else {
        dll->head = new_data;
        new_data->prev = NULL;
    }
    dll->tail = new_data;
    return 0;
}

int dll_push_front(struct doubly_linked_list_t *dll, int value) {
    if (dll == NULL) {
        return 1;
    }
    struct node_t *new_mode = calloc(1, sizeof(struct node_t));
    if (!new_mode) return 2;
    new_mode->data = value;
    new_mode->next = dll->head;
    new_mode->prev = NULL;
    if (dll->head != NULL) {
        dll->head->prev = new_mode;
    }
    dll->head = new_mode;
    if (dll->tail == NULL) {
        dll->tail = new_mode;
    }
    return 0;
}

int dll_pop_front(struct doubly_linked_list_t *dll, int *err_code) {
    if (err_code) *err_code = 0;
    if (!dll || !dll->head || !dll->tail) {
        if (err_code) *err_code = 1;
        return -1;
    }

    struct node_t *node_to_remove = dll->head;
    int value = node_to_remove->data;
    dll->head = dll->head->next;
    if (dll->head != NULL) {
        dll->head->prev = NULL;
    } else {
        dll->tail = NULL;
    }
    free(node_to_remove);
    if (err_code != NULL) *err_code = 0;
    return value;
}

int dll_pop_back(struct doubly_linked_list_t *dll, int *err_code) {
    if (err_code) *err_code = 0;
    if (!dll || !dll->head || !dll->tail) {
        if (err_code) *err_code = 1;
        return -1;
    }

    struct node_t *node_to_remove = dll->tail;
    int value = node_to_remove->data;
    dll->tail = dll->tail->prev;
    if (dll->tail != NULL) {
        dll->tail->next = NULL;
    } else {
        dll->head = NULL;
    }
    free(node_to_remove);
    if (err_code != NULL) *err_code = 0;
    return value;
}

int dll_back(const struct doubly_linked_list_t *dll, int *err_code) {
    if (err_code) *err_code = 0;
    if (!dll || !dll->tail || !dll->head) {
        if (err_code != NULL) *err_code = 1;
        return -1;
    }
    if (err_code != NULL) *err_code = 0;
    return dll->tail->data;
}

int dll_front(const struct doubly_linked_list_t *dll, int *err_code) {
    if (err_code) *err_code = 0;
    if (!dll || !dll->tail || !dll->head) {
        if (err_code != NULL) *err_code = 1;
        return -1;
    }

    if (err_code != NULL) *err_code = 0;
    return dll->head->data;
}

struct node_t *dll_begin(struct doubly_linked_list_t *dll) {
    if (!dll || !dll->tail || !dll->head) return NULL;
    return dll->head;
}

struct node_t *dll_end(struct doubly_linked_list_t *dll) {
    if (!dll || !dll->tail || !dll->head) return NULL;
    return dll->tail;
}

int dll_size(const struct doubly_linked_list_t *dll) {
    if (!dll) {
        return -1;
    }
    int count = 0;
    struct node_t *current = dll->tail;
    while (current != NULL) {
        current = current->prev;
        count++;
    }
    return count;
}

int dll_is_empty(const struct doubly_linked_list_t *dll) {
    if (!dll) {
        return -1;
    }
    return (dll->head == NULL);
}

int dll_at(const struct doubly_linked_list_t *dll, unsigned int index, int *err_code) {
    if (err_code) *err_code = 0;
    if (!dll || dll_size(dll) < (int) index) {
        if (err_code) *err_code = 1;
        return -1;
    }
    struct node_t *current = dll->head;
    unsigned int i = 0;
    while (current != NULL && i < index) {
        current = current->next;
        i++;
    }
    if (current == NULL) {
        if (err_code != NULL) *err_code = 1;
        return -1;
    }
    if (err_code != NULL) *err_code = 0;
    return current->data;
}

int dll_insert(struct doubly_linked_list_t *dll, unsigned int index, int value) {
    if (!dll || dll_size(dll) < (int) index) {
        return 1;
    }
    if (index == 0) {
        return dll_push_front(dll, value);
    }
    struct node_t *current = dll->head;
    unsigned int i = 0;
    while (current != NULL && i < index - 1) {
        current = current->next;
        i++;
    }
    if (current == NULL) return 1;
    struct node_t *new_mode = malloc(sizeof(struct node_t));
    if (!new_mode) return 2;
    new_mode->data = value;
    new_mode->next = current->next;
    new_mode->prev = current;
    if (current->next != NULL) {
        current->next->prev = new_mode;
    } else {
        dll->tail = new_mode;
    }
    current->next = new_mode;
    return 0;
}

int dll_remove(struct doubly_linked_list_t *dll, unsigned int index, int *err_code) {
    if (err_code) *err_code = 0;

    if (!dll || (int)index < 0 || dll_size(dll) <= (int)index || dll_is_empty(dll) == 1) {
        if (err_code) *err_code = 1;
        return 1;
    }
    if (index == 0) return dll_pop_front(dll, err_code);

    if ((int)index == dll_size(dll) - 1) return dll_pop_back(dll, err_code);

    struct node_t *current = dll->head;
    for (unsigned int i = 0; i < index; i++) {
        current = current->next;
    }

    int value = current->data;
    current->prev->next = current->next;
    current->next->prev = current->prev;
    free(current);
    return value;
}



void dll_clear(struct doubly_linked_list_t *dll) {
    if (!dll) return;
    struct node_t *current = dll->head;
    while (current != NULL) {
        struct node_t *next = current->next;
        free(current);
        current = next;
    }
    dll->head = NULL;
    dll->tail = NULL;
}

void dll_display(const struct doubly_linked_list_t *dll) {
    if (!dll || !dll->tail || !dll->head) return;

    struct node_t *current = dll->head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
}

void dll_display_reverse(const struct doubly_linked_list_t *dll) {
    if (!dll || !dll->tail || !dll->head) return;

    struct node_t *current = dll->tail;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->prev;
    }
}

void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void incorrect_input(struct doubly_linked_list_t *dll) {
    printf("Incorrect input\n");
    dll_clear(dll);
    free(dll);
    exit(1);
}

int main() {
    struct doubly_linked_list_t *dll = dll_create();
    if (dll == NULL) {
        printf("Failed to allocate memory\n");
        return 8;
    }

    int choice;
    while (1) {
        printf("Co chcesz zrobic? ");
        int input_status = scanf("%d", &choice);
        if (input_status != 1) {
            clear_input_buffer();
            incorrect_input(dll);
        }

        switch (choice) {
            case 0:
                dll_clear(dll);
                free(dll);
                return 0;
            case 1:
                printf("Podaj liczbe: ");
                int value;
                input_status = scanf("%d", &value);
                if (input_status != 1) {
                    clear_input_buffer();
                    incorrect_input(dll);
                }
                input_status = dll_push_back(dll, value);
                if (input_status != 0) {
                    printf("Failed to allocate memory\n");
                    dll_clear(dll);
                    free(dll);
                    return 8;
                }
                break;
            case 2: {
                int err_code;
                value = dll_pop_back(dll, &err_code);
                if (err_code != 0) {
                    printf("List is empty\n");
                } else {
                    printf("%d\n", value);
                }
                break;
            }
            case 3:
                printf("Podaj liczbe: ");
                input_status = scanf("%d", &value);
                if (input_status != 1) {
                    clear_input_buffer();
                    incorrect_input(dll);
                }
                input_status = dll_push_front(dll, value);
                if (input_status != 0) {
                    printf("Failed to allocate memory\n");
                    dll_clear(dll);
                    free(dll);
                    return 8;
                }
                break;
            case 4: {
                int err_code;
                value = dll_pop_front(dll, &err_code);
                if (err_code != 0) {
                    printf("List is empty\n");
                } else {
                    printf("%d\n", value);
                }
                break;
            }
            case 5:
                printf("Podaj liczbe: ");
                input_status = scanf("%d", &value);
                if (input_status != 1) {
                    clear_input_buffer();
                    incorrect_input(dll);
                }
                printf("Podaj index: ");
                unsigned int index;
                input_status = scanf("%u", &index);
                if (input_status != 1) {
                    clear_input_buffer();
                    incorrect_input(dll);
                }
                input_status = dll_insert(dll, index, value);
                if (input_status == 1) {
                    printf("Index out of range\n");
                } else if (input_status == 2) {
                    printf("Failed to allocate memory\n");
                    dll_clear(dll);
                    free(dll);
                    return 8;
                }
                break;
            case 6:
                if (dll_is_empty(dll) == 1) {
                    printf("List is empty\n");
                } else {
                    printf("Podaj index: ");
                    input_status = scanf("%u", &index);
                    if (input_status != 1) {
                        clear_input_buffer();
                        incorrect_input(dll);
                    }
                    int err_code;
                    value = dll_remove(dll, index, &err_code);
                    if (err_code != 0) {
                        printf("Index out of range\n");
                    } else {
                        printf("%d\n", value);
                    }
                }
                break;
            case 7: {
                int err_code;
                value = dll_back(dll, &err_code);
                if (err_code != 0) {
                    printf("List is empty\n");
                } else {
                    printf("%d\n", value);
                }
                break;
            }
            case 8: {
                int err_code;
                value = dll_front(dll, &err_code);
                if (err_code != 0) {
                    printf("List is empty\n");
                } else {
                    printf("%d\n", value);
                }
                break;
            }
            case 9:
                printf("%d\n", dll_is_empty(dll));
                break;
            case 10:
                printf("%d\n", dll_size(dll));
                break;
            case 11:
                dll_clear(dll);
                break;
            case 12:
                if (dll_is_empty(dll) == 1) {
                    printf("List is empty\n");
                } else {
                    printf("Podaj index: ");
                    input_status = scanf("%u", &index);
                    if (input_status != 1) {
                        clear_input_buffer();
                        incorrect_input(dll);
                    }
                    int err_code;
                    value = dll_at(dll, index, &err_code);
                    if (err_code != 0) {
                        printf("Index out of range\n");
                    } else {
                        printf("%d\n", value);
                    }
                }
                break;
            case 13:
                if (dll_is_empty(dll) == 1) {
                    printf("List is empty\n");
                } else {
                    dll_display(dll);
                    printf("\n");
                }
                break;
            case 14:
                if (dll_is_empty(dll) == 1) {
                    printf("List is empty\n");
                } else {
                    dll_display_reverse(dll);
                    printf("\n");
                }
                break;
            default:
                printf("Incorrect input data\n");
                clear_input_buffer();
                break;
        }
    }

    dll_clear(dll);
    free(dll);
    return 0;
}

