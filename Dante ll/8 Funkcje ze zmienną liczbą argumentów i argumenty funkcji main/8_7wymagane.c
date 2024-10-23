#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>
#include "tested_declarations.h"
#include "rdebug.h"

#define TEN 10

struct point_t {
    int x;
    int y;
};

void print_int(int num, int *w) {
    if (num == 0) {
        putchar('0');
        (*w)++;
        return;
    }

    if (num < 0) {
        putchar('-');
        num = -num;
        (*w)++;
    }

    int reversed = 0, count = 0;
    while (num > 0) {
        reversed = reversed * TEN + (num % TEN);
        num /= TEN;
        count++;
    }

    while (count > 0) {
        putchar(reversed % TEN + '0');
        reversed /= TEN;
        count--;
        (*w)++;
    }
}

void print_float(double num, int *w) {
    int int_part = (int) num;
    double frac_part = num - int_part;

    print_int(int_part, w);

    putchar('.');
    (*w)++;

    if (frac_part < 0) {
        frac_part = -frac_part;
    }

    for (int i = 0; i < 5; i++) {
        frac_part *= TEN;
        int digit = (int) frac_part;
        putchar(digit + '0');
        frac_part -= digit;
        (*w)++;
    }
}

void print_point(struct point_t point, int *w) {
    putchar('(');
    (*w)++;

    print_int(point.x, w);

    putchar(' ');
    (*w)++;

    print_int(point.y, w);

    putchar(')');
    (*w)++;
}

int my_printf(char *txt, ...) {
    int index = 0, width = 0;
    va_list args;
    va_start(args, txt);

    while (*(txt + index) != '\0') {
        if (*(txt + index) == '%') {
            ++index;
            switch (*(txt + index)) {
                case 's': {
                    char *str = va_arg(args, char*);
                    while (*str != '\0') {
                        putchar(*str++);
                        width++;
                    }
                    break;
                }
                case 'd': {
                    int num = va_arg(args, int);
                    print_int(num, &width);
                    break;
                }
                case 'f': {
                    double num = va_arg(args, double);
                    print_float(num, &width);
                    break;
                }
                case 'p': {
                    struct point_t point = va_arg(args, struct point_t);
                    print_point(point, &width);
                    break;
                }
                default: {
                    putchar(*(txt + index));
                    width++;
                    break;
                }
            }
        } else {
            putchar(*(txt + index));
            width++;
        }
        ++index;
    }

    va_end(args);
    return width;
}


int my_scanf(char *format, ...) {
    int conversion_count = 0;
    va_list args;
    va_start(args, format);
    int read_flag = 1;
    char current_char;

    for (int format_index = 0; *(format + format_index) != '\0'; ++format_index) {
        if (read_flag) {
            current_char = getchar();
        }
        if (*(format + format_index) == '%') {
            ++format_index;
            switch (*(format + format_index)) {
                case 'd': {
                    read_flag = 1;
                    int *int_ptr = va_arg(args, int*);
                    int negative_flag = 0;
                    int number = 0;
                    int digit_count = 0;

                    while (isdigit(current_char) || current_char == '-') {
                        if (current_char == '-') {
                            if (digit_count != 0)
                                return conversion_count;
                            negative_flag = 1;
                            current_char = getchar();
                            continue;
                        }
                        number += current_char - '0';
                        ++digit_count;
                        current_char = getchar();
                        if (!isdigit(current_char)) {
                            read_flag = 0;
                            break;
                        }
                        number *= 10;
                    }
                    if (digit_count == 0)
                        return conversion_count;
                    if (negative_flag)
                        number *= -1;
                    *int_ptr = number;
                    conversion_count++;
                    break;
                }
                case 'f': {
                    read_flag = 1;
                    int negative_flag = 0;
                    double number = 0;
                    int digit_count = 0;
                    double *double_ptr = va_arg(args, double*);
                    

                    while (isdigit(current_char) || current_char == '-') {
                        if (current_char == '-') {
                            if (digit_count != 0)
                                return conversion_count;
                            negative_flag = 1;
                            current_char = getchar();
                            continue;
                        }
                        number += current_char - '0';
                        ++digit_count;
                        current_char = getchar();
                        if (!isdigit(current_char))
                            break;
                        number *= 10;
                    }
                    if (digit_count == 0)
                        return conversion_count;

                    if (current_char == '.') {
                        digit_count = TEN;
                        current_char = getchar();
                        if (!isdigit(current_char))
                            return conversion_count;
                        switch (current_char) {
                            case '0': case '1': case '2': case '3': case '4':
                            case '5': case '6': case '7': case '8': case '9':
                                do {
                                    number += (double)((double)(current_char - '0') / (double)digit_count);
                                    digit_count *= 10;
                                    current_char = getchar();
                                } while (isdigit(current_char));
                                break;
                        }
                        read_flag = 0;
                    }

                    if (negative_flag)
                        number *= -1;
                    *double_ptr = number;
                    conversion_count++;
                    break;
                }
                case 'p': {
                    read_flag = 1;
                    struct point_t *point_ptr = va_arg(args, struct point_t*);
                    int negative_flag = 0;
                    int number = 0;
                    int digit_count = 0;

                    if (current_char != '(')
                        return conversion_count;
                    current_char = getchar();
                    while (isdigit(current_char) || current_char == '-') {
                        if (current_char == '-') {
                            if (digit_count != 0)
                                return conversion_count;
                            negative_flag = 1;
                            current_char = getchar();
                            continue;
                        }
                        number += current_char - '0';
                        ++digit_count;
                        current_char = getchar();
                        if (!isdigit(current_char))
                            break;
                        number *= TEN;
                    }
                    if (digit_count == 0)
                        return conversion_count;
                    if (negative_flag)
                        number *= -1;
                    point_ptr->x = number;
                    negative_flag = 0;
                    number = 0;
                    digit_count = 0;

                    if (current_char != ' ')
                        return conversion_count;
                    current_char = getchar();
                    while (isdigit(current_char) || current_char == '-') {
                        if (current_char == '-') {
                            if (digit_count != 0)
                                return conversion_count;
                            negative_flag = 1;
                            current_char = getchar();
                            continue;
                        }
                        number += current_char - '0';
                        ++digit_count;
                        current_char = getchar();
                        if (!isdigit(current_char))
                            break;
                        number *= TEN;
                    }
                    if (digit_count == 0)
                        return conversion_count;
                    if (negative_flag)
                        number *= -1;
                    point_ptr->y = number;

                    if (current_char != ')')
                        return conversion_count;
                    conversion_count += 2;
                    break;
                }
                default:
                    return conversion_count;
            }
        } else {
            read_flag = 1;
            if (current_char != *(format + format_index))
                return conversion_count;
        }
    }
    va_end(args);
    return conversion_count;
}


int main() {
    struct point_t a;
    my_printf("Wpisz punkt w postaci (x y): ");
    int res = my_scanf("%p", &a);
    my_printf("Wynik: [%d;%d;%d]", a.x, a.y, res);
    return 0;
}

