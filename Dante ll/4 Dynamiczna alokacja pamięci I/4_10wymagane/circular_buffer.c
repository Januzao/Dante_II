#include <stdio.h>
#include <stdlib.h>
#include "circular_buffer.h"
#include "tested_declarations.h"
#include "rdebug.h"

int circular_buffer_create(struct circular_buffer_t *buffer, int size) {
    if (buffer == NULL || size <= 0) {
        return 1;
    }
    buffer->ptr = (int *) calloc(size, sizeof(int));
    if (buffer->ptr == NULL) {
        return 2;
    }
    buffer->begin = 0;
    buffer->end = 0;
    buffer->capacity = size;
    buffer->full = 0;
    return 0;
}

int circular_buffer_create_struct(struct circular_buffer_t **buffer, int size) {
    int result;
    if (buffer == NULL || size <= 0) {
        return 1;
    }
    *buffer = (struct circular_buffer_t *) malloc(sizeof(struct circular_buffer_t));
    result = circular_buffer_create(*buffer, size);
    if (result != 0) {
        free(*buffer);
    }
    return result;
}

void circular_buffer_destroy(struct circular_buffer_t *buffer) {
    if (!(buffer == NULL || buffer->ptr == NULL)) {
        free(buffer->ptr);
    }
}

void circular_buffer_destroy_struct(struct circular_buffer_t **buffer) {
    if (buffer != NULL) {
        circular_buffer_destroy(*buffer);
        free(*buffer);
    }
}

int circular_buffer_push_back(struct circular_buffer_t *buffer, int value) {
    int newIndex;
    if (buffer == NULL || buffer->ptr == NULL || buffer->begin < 0 || buffer->end < 0 || buffer->capacity < 0 ||
        buffer->begin >= buffer->capacity || buffer->end >= buffer->capacity) {
        return 1;
    }
    *(buffer->ptr + buffer->end) = value;

    newIndex = buffer->end + 1;
    while (newIndex >= buffer->capacity) {
        newIndex -= buffer->capacity;
    }
    buffer->end = newIndex;
    if (buffer->full == 1)
        buffer->begin = buffer->end;
    if (buffer->begin == buffer->end)
        buffer->full = 1;
    return 0;
}

int circular_buffer_pop_front(struct circular_buffer_t *buffer, int *error_code) {
    int newIndex, value;
    if (buffer == NULL || buffer->ptr == NULL || buffer->begin < 0 || buffer->end < 0 || buffer->capacity < 0 ||
        buffer->begin >= buffer->capacity || buffer->end >= buffer->capacity) {
        if (error_code != NULL)
            *error_code = 1;
        return 0;
    } else if (circular_buffer_empty(buffer) != 0) {
        if (error_code != NULL)
            *error_code = 2;
        return 0;
    } else {
        value = *(buffer->ptr + buffer->begin);
        newIndex = buffer->begin + 1;
        while (newIndex >= buffer->capacity) {
            newIndex -= buffer->capacity;
        }
        buffer->begin = newIndex;
        buffer->full = 0;
        if (error_code != NULL)
            *error_code = 0;
        return value;
    }
}

int circular_buffer_pop_back(struct circular_buffer_t *buffer, int *error_code) {
    int newIndex, value;
    if (buffer == NULL || buffer->ptr == NULL || buffer->begin < 0 || buffer->end < 0 || buffer->capacity < 0 ||
        buffer->begin >= buffer->capacity || buffer->end >= buffer->capacity) {
        if (error_code != NULL)
            *error_code = 1;
        return 0;
    } else if (circular_buffer_empty(buffer) != 0) {
        if (error_code != NULL)
            *error_code = 2;
        return 0;
    } else {
        newIndex = (buffer->end + buffer->capacity - 1) % buffer->capacity;
        value = *(buffer->ptr + newIndex);
        buffer->end = newIndex;
        buffer->full = 0;
        if (error_code != NULL)
            *error_code = 0;
        return value;
    }
}

int circular_buffer_empty(const struct circular_buffer_t *buffer) {
    if (buffer == NULL || buffer->ptr == NULL || buffer->begin < 0 || buffer->end < 0 || buffer->capacity < 0 ||
        buffer->begin >= buffer->capacity || buffer->end >= buffer->capacity) {
        return -1;
    } else if (buffer->full == 0 && buffer->begin == buffer->end) {
        return 1;
    }
    return 0;
}

int circular_buffer_full(const struct circular_buffer_t *buffer) {
    if (buffer == NULL || buffer->ptr == NULL || buffer->begin < 0 || buffer->end < 0 || buffer->capacity < 0 ||
        buffer->begin >= buffer->capacity || buffer->end >= buffer->capacity) {
        return -1;
    } else if (buffer->full == 1) {
        return 1;
    }
    return 0;
}

void circular_buffer_display(const struct circular_buffer_t *buffer) {
    if (!(buffer == NULL || buffer->ptr == NULL || buffer->begin < 0 || buffer->end < 0 || buffer->capacity < 0 ||
          buffer->begin >= buffer->capacity || buffer->end >= buffer->capacity || circular_buffer_empty(buffer) != 0)) {
        int index, nextIndex;
        index = buffer->begin;
        do {
            printf("%d ", *(buffer->ptr + index));
            nextIndex = (index + 1) % buffer->capacity;
            index = nextIndex;
        } while (index != buffer->end);
    }
}

int main() {
    struct circular_buffer_t *buffer;
    int status, num, action = 1;

    printf("Podaj rozmiar bufora:");
    status = scanf("%d", &num);
    if (status != 1) {
        printf("Incorrect input\n");
        return 1;
    }
    if (num <= 0) {
        printf("Incorrect input data\n");
        return 2;
    }
    status = circular_buffer_create_struct(&buffer, num);
    if (status != 0) {
        printf("Failed to allocate memory\n");
        return 8;
    }

    while (action != 0) {
        printf("Co chcesz zrobic? ");
        status = scanf("%d", &action);
        if (status != 1) {
            printf("Incorrect input\n");
            circular_buffer_destroy_struct(&buffer);
            return 1;
        }

        switch (action) {
            case 1:
                printf("Podaj liczbe ");
                status = scanf("%d", &num);
                if (status != 1) {
                    printf("Incorrect input\n");
                    circular_buffer_destroy_struct(&buffer);
                    return 1;
                }
                circular_buffer_push_back(buffer, num);
                break;
            case 2:
                num = circular_buffer_pop_back(buffer, &status);
                if (status != 0) {
                    printf("Buffer is empty\n");
                } else {
                    printf("%d\n", num);
                }
                break;
            case 3:
                num = circular_buffer_pop_front(buffer, &status);
                if (status != 0) {
                    printf("Buffer is empty\n");
                } else {
                    printf("%d\n", num);
                }
                break;
            case 4:
                status = circular_buffer_empty(buffer);
                if (status != 0) {
                    printf("Buffer is empty");
                } else {
                    circular_buffer_display(buffer);
                }
                printf("\n");
                break;
            case 5:
                status = circular_buffer_empty(buffer);
                printf("%d\n", status == 0 ? 0 : 1);
                break;
            case 6:
                status = circular_buffer_full(buffer);
                printf("%d\n", status == 0 ? 0 : 1);
                break;
            default:
                printf("Incorrect input data\n");
                break;
        }
    }

    circular_buffer_destroy_struct(&buffer);
    return 0;
}

