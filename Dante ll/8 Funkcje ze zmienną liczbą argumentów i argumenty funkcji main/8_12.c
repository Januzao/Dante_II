#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Not enough arguments\n");
        return 9;
    }

    int sum = 0;
    for (int i = 1; i < argc; i++) {
        char *endptr;
        long num = strtol(*(argv + i), &endptr, 10);

        if (*endptr != '\0') {
            printf("Incorrect input\n");
            return 1;
        }

        sum += num;
    }

    printf("%d\n", sum);
    return 0;
}
