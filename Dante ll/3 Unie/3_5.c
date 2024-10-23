#include <stdio.h>

int main() {
    unsigned int number;
    int bitSum = 0;

    printf("Podaj wartosc:");
    if (scanf("%u", &number) != 1) {
        printf("Incorrect input\n");
        return 1;
    }

    while (number > 0) {
        bitSum += number % 2;
        number /= 2;
    }

    if (bitSum % 2 == 0) {
        printf("YES\n");
    } else {
        printf("NO\n");
    }

    return 0;
}
