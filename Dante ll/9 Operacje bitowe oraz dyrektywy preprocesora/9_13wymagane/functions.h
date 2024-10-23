#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdio.h>
#include <limits.h>

#define COUNT_BITS(value, set_bits, cleared_bits)    \
    do {                                             \
        unsigned int count_set = 0;                  \
        unsigned int count_cleared = 0;              \
        for (unsigned int i = 0; i < sizeof(value) * 8; ++i) {  \
            if (value & (1UL << i)) {                \
                ++count_set;                         \
            } else {                                 \
                ++count_cleared;                     \
            }                                        \
        }                                            \
        *set_bits = count_set;                       \
        *cleared_bits = count_cleared;               \
    } while (0)

#define DISPLAY_BITS(value)                          \
    do {                                             \
        for (unsigned int i = sizeof(value) * 8; i > 0; --i) {   \
            printf("%c", (value & (1UL << (i - 1))) ? '1' : '0');\
        }                                            \
        printf("\n");                                \
    } while (0)

#define REVERSE_BITS(value_ptr)                      \
    do {                                             \
        unsigned long long reversed = 0;             \
        unsigned long long original = *(value_ptr);  \
        for (unsigned int i = 0; i < sizeof(*(value_ptr)) * 8; ++i) { \
            if (original & (1ULL << i)) {            \
                reversed |= 1ULL << ((sizeof(*(value_ptr)) * 8 - 1) - i); \
            }                                        \
        }                                            \
        *(value_ptr) = reversed;                     \
    } while (0)

#endif // FUNCTIONS_H
