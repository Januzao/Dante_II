#include <stdio.h>
#include <stdint.h>
#include "tested_declarations.h"
#include "rdebug.h"

int toggle_bit(uint32_t* pvalue, int b) {
    if (pvalue == NULL || b < 0 || b >= 32) return -1;
    uint32_t mask = 1;
    while (b--) mask *= 2;
    *pvalue = (*pvalue / mask % 2 == 1) ? *pvalue - mask : *pvalue + mask;
    return 0;
}

int set_bit(uint32_t* pvalue, int b) {
    if (pvalue == NULL || b < 0 || b >= 32) return -1;
    uint32_t mask = 1;
    while (b--) mask *= 2;
    if (*pvalue / mask % 2 == 0) *pvalue += mask;
    return 0;
}

int clear_bit(uint32_t* pvalue, int b) {
    if (pvalue == NULL || b < 0 || b >= 32) return -1;
    uint32_t mask = 1;
    while (b--) mask *= 2;
    if (*pvalue / mask % 2 == 1) *pvalue -= mask;
    return 0;
}

int isset_bit(const uint32_t* pvalue, int b) {
    if (pvalue == NULL || b < 0 || b >= 32) return -1;
    uint32_t mask = 1;
    while (b--) mask *= 2;
    return (*pvalue / mask % 2 == 1) ? 1 : 0;
}

int main() {
    uint32_t value;
    int bitIndex, operation;

    printf("Enter value:\n");
    if (scanf("%u", &value) != 1) {
        printf("Incorrect input\n");
        return 1;
    }

    printf("Enter bit index:\n");
    if (scanf("%d", &bitIndex) != 1) {
        printf("Incorrect input\n");
        return 1;
    }
    if (bitIndex < 0 || bitIndex > 31){
        printf("Invalid bit index\n");
        return 2;
    }

    printf("Select operation (0-toggle, 1-set, 2-clear, 3-read):\n");
    if (scanf("%d", &operation) != 1) {
        printf("Incorrect input\n");
        return 1;

    }
    if (operation < 0 || operation > 3){
        printf("Invalid operation\n");
        return 2;
    }

    switch (operation) {
        case 0:
            toggle_bit(&value, bitIndex);
            break;
        case 1:
            set_bit(&value, bitIndex);
            break;
        case 2:
            clear_bit(&value, bitIndex);
            break;
        case 3:
            printf("%d\n", isset_bit(&value, bitIndex));
            return 0;
    }

    printf("%08x\n", value);

    return 0;
}


