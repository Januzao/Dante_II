#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"
#include "tested_declarations.h"
#include "rdebug.h"


DEFINE_ARRAY(int)
DEFINE_ARRAY(double)
CREATE_ARRAY(int)
CREATE_ARRAY(double)
FREE_ARRAY(int)
FREE_ARRAY(double)
SAVE_ARRAY(int)
SAVE_ARRAY(double)
LOAD_ARRAY(int)
LOAD_ARRAY(double)
SORT_ARRAY(int)
SORT_ARRAY(double)

void handle_error(const char *message, int exit_code) {
    printf("%s\n", message);
    exit(exit_code);
}

int main(void) {
    char *filename = (char *)malloc(30 * sizeof(char));
    if (!filename) {
        handle_error("Failed to allocate memory", 8);
    }

    printf("Enter filename: ");
    if (!fgets(filename, 30, stdin)) {
        free(filename);
        handle_error("Incorrect input", 1);
    }
    *(filename + strcspn(filename, "\n")) = '\0';

    printf("Choose your type: ");
    int type;
    if (scanf("%d", &type) != 1) {
        free(filename);
        handle_error("Incorrect input", 1);
    } else if (type != 0 && type != 1) {
        free(filename);
        handle_error("Incorrect input data", 2);
    }

    if (type == 0) {
        array_int_t *array = NULL;
        int load_result = load_array_int(&array, filename);
        if (load_result != 0) {
            free(filename);
            switch (load_result) {
                case 1:
                    handle_error("Incorrect input", 1);
                    break;
                case 2:
                    handle_error("Couldn't open file", 4);
                    break;
                case 3:
                    handle_error("File corrupted", 6);
                    break;
                case 4:
                    handle_error("Failed to allocate memory", 8);
                    break;
            }
        }

        if (sort_array_int(array) != 0) {
            free_array_int(array);
            free(filename);
            handle_error("File corrupted", 6);
        }

        if (save_array_int(array, filename) != 0) {
            free_array_int(array);
            free(filename);
            handle_error("Couldn't create file", 5);
        }

        free_array_int(array);
    } else if (type == 1) {
        array_double_t *array = NULL;
        int load_result = load_array_double(&array, filename);
        if (load_result != 0) {
            free(filename);
            switch (load_result) {
                case 1:
                    handle_error("Incorrect input", 1);
                    break;
                case 2:
                    handle_error("Couldn't open file", 4);
                    break;
                case 3:
                    handle_error("File corrupted", 6);
                    break;
                case 4:
                    handle_error("Failed to allocate memory", 8);
                    break;
            }
        }

        if (sort_array_double(array) != 0) {
            free_array_double(array);
            free(filename);
            handle_error("File corrupted", 6);
        }

        if (save_array_double(array, filename) != 0) {
            free_array_double(array);
            free(filename);
            handle_error("Couldn't create file", 5);
        }

        free_array_double(array);
    } else {
        free(filename);
        handle_error("Incorrect input data", 2);
    }

    free(filename);
    printf("File saved\n");
    return 0;
}

