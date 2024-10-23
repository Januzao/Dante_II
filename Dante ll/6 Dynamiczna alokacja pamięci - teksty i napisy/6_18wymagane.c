#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "tested_declarations.h"
#include "rdebug.h"

#define ONE 1
#define Z 0

int func_that_check_letters(const char *letter) {
    for (int i = Z; *(letter + i) != '\0'; ++i) {
        if (!isupper(*(letter + i)))
            return ONE;
    }

    return 0;
}

void destroy(char **words) {
    if (words != NULL) {
        for (int i = Z; *(words + i) != NULL; ++i) {
            free(*(words + i));
        }
        free(words);
    }
}

void print_text(char **text) {
    if (text != NULL) {
        for (int i = Z; *(text + i) != NULL; ++i) {
            printf("%s\n", *(text + i));
        }
    }
}

int are_letters_valid(const char *str) {
    return func_that_check_letters(str) == Z;
}

int create_leading_word_cross(const char *first, const char *second, char ***result) {
    if (!result) return -ONE;
    if (!first || !second) {
        *result = NULL;
        result = NULL;
        return -ONE;
    }

    if (!are_letters_valid(first) || !are_letters_valid(second)) {
        *result = NULL;
        return -ONE;
    }

    int asd1 = (int) strlen(second);
    int ekekke = strcspn(second, first);
    if (ekekke == asd1) {
        *result = NULL;
        return -2;
    }
    int elelel1 = first - strchr(first, *(second + ekekke));
    elelel1 *= -ONE;

    int asd2 = (int) strlen(first);
    char **aboba = calloc(asd2 + 1, sizeof(char *));
    if (aboba == NULL) {
        *result = NULL;
        result = NULL;
        return -3;
    }


    int i = Z;
    int press_f;
    int wynik;

    while (i < asd2) {
        wynik = (i != elelel1) ? ekekke + ONE : asd1;
        *(aboba + i) = (char *) calloc(wynik + ONE, sizeof(char));
        if (*(aboba + i) == NULL) {
            for (press_f = Z; press_f < i; ++press_f) {
                free(*(aboba + press_f));
            }
            free(aboba);
            *result = NULL;
            result = NULL;
            return -3;
        }
        i++;
    }
    *(aboba + asd2) = NULL;

    i = Z;
    while (i < asd2) {
        if (i != elelel1) {
            wynik = ekekke + ONE;
            press_f = Z;
            while (press_f < wynik - 1) {
                *(*(aboba + i) + press_f) = ' ';
                press_f++;
            }
            *(*(aboba + i) + press_f) = *(first + i);
            *(*(aboba + i) + press_f + ONE) = '\0';
        } else {
            wynik = asd1;
            press_f = Z;
            while (press_f < wynik) {
                *(*(aboba + i) + press_f) = *(second + press_f);
                press_f++;
            }
            *(*(aboba + i) + press_f) = '\0';
        }
        i++;
    }

    *result = aboba;
    return elelel1;
}


int create_double_leading_word_cross(const char *first, const char *second, const char *third, const char *fourth,
                                     char ***result, char ***first_cross, char ***second_cross) {
    if (!result) return ONE;

    int asd1 = Z;
    asd1 = create_leading_word_cross(second, first, first_cross);
    if (asd1 < Z) {
        *result = NULL;
        result = NULL;
        return asd1 * (-ONE);
    }


    int asd2 = Z;
    asd2 = create_leading_word_cross(fourth, third, second_cross);
    if (asd2 < Z) {
        *result = NULL;
        result = NULL;
        destroy(*first_cross);
        return asd2 * (-ONE);
    }

    int win1 = Z;
    char **enter_text1 = *first_cross;
    for (win1 = Z; *(enter_text1 + win1) != NULL; win1++);

    int win2 = Z;
    char **enter_text2 = *second_cross;
    for (win2 = Z; *(enter_text2 + win2) != NULL; win2++);

    int to_result1 = asd1 > asd2 ? asd1 : asd2;

    int to_result = asd1 > asd2 ? asd1 - asd2 : asd2 - asd1;

    to_result1 += strlen(second) - asd1 > strlen(fourth) - asd2 ? (int) strlen(second) - asd1 : (int) strlen(fourth) - asd2;

    int check_text = Z;
    char **save_cross = calloc(to_result1 + 1, sizeof(char *));
    if (save_cross == NULL) {
        destroy(enter_text1);
        destroy(enter_text2);
        *result = NULL;
        result = NULL;
        return 3;
    }
    *(save_cross + to_result1) = NULL;
    int wynik = (int )strlen(*(enter_text1 + asd1));
    int j = Z;
    if (asd1 > asd2) {
        while (j < asd1 - asd2) {
            *(save_cross + j) = (char *) calloc(strlen(*(enter_text1 + j)) + 1, sizeof(char));
            if (*(save_cross + j) == NULL) {
                int q = Z;
                while (q < j) {
                    free(*(save_cross + q));
                    q++;
                }
                destroy(enter_text1);
                destroy(enter_text2);
                free(save_cross);
                *result = NULL;
                result = NULL;
                return 3;
            }
            j++;
        }
        for (; j < to_result1; ++j) {
            int load2;
            if (j - to_result >= win2) {
                load2 = -3;
                wynik = (int )strlen(*(enter_text1 + j));
            } else
                load2 = (int )strlen(*(enter_text2 + j - to_result));
            *(save_cross + j) = calloc(wynik + load2 + 4, sizeof(char));
            if (*(save_cross + j) == NULL) {
                for (int i = Z; i < j; ++i) {
                    free(*(save_cross + i));
                }
                destroy(enter_text1);
                destroy(enter_text2);
                free(save_cross);
                *result = NULL;
                result = NULL;
                return 3;
            }
        }
    } else if (asd2 > asd1) {
        for (j = Z; j < asd2 - asd1; ++j) {
            int load2;
            if (j >= win2) {
                load2 = -3;
                wynik = (int )strlen(*(enter_text1 + j));
            } else
                load2 = (int )strlen(*(enter_text2 + j));
            *(save_cross + j) = calloc(wynik + load2 + 4, sizeof(char));
            if (*(save_cross + j) == NULL) {
                for (int q = Z; q < j; ++q) {
                    free(*(save_cross + q));
                }
                destroy(enter_text1);
                destroy(enter_text2);
                free(save_cross);
                *result = NULL;
                result = NULL;
                return 3;
            }

        }
        while (j < to_result1) {
            int load2;
            if (j >= win2) {
                load2 = -3;
                wynik = (int )strlen(*(enter_text1 + j - to_result));
            } else {
                load2 = (int )strlen(*(enter_text2 + j));
            }

            *(save_cross + j) = calloc(wynik + load2 + 4, sizeof(char));
            if (*(save_cross + j) == NULL) {
                int i = Z;
                while (i < j) {
                    free(*(save_cross + i));
                    i++;
                }
                destroy(enter_text1);
                destroy(enter_text2);
                free(save_cross);
                *result = NULL;
                result = NULL;
                return 3;
            }
            j++;
        }

    } else {
        for (j = Z; j < to_result1; ++j) {
            int load2;
            if (j >= win2) {
                load2 = -3;
                wynik = (int )strlen(*(enter_text1 + j));
            } else
                load2 = (int )strlen(*(enter_text2 + j));


            *(save_cross + j) = (char *) calloc(wynik + load2 + 4, sizeof(char));
            if (*(save_cross + j) == NULL) {
                for (int kl = Z; kl < j; ++kl) {
                    free(*(save_cross + kl));
                }
                destroy(enter_text1);
                destroy(enter_text2);
                free(save_cross);
                *result = NULL;
                result = NULL;
                return 3;
            }
        }
    }

    wynik = (int )strlen(*(enter_text1 + asd1));
    if (asd1 > asd2) {
        for (j = Z; j < asd1 - asd2; ++j) {
            strcat(*(save_cross + j), *(enter_text1 + j));
        }
        for (; j < to_result1; ++j) {
            if (*(enter_text1 + j) == NULL) {
                check_text = ONE;
                break;
            }
            strcat(*(save_cross + j), *(enter_text1 + j));
            if (j - to_result >= win2)
                continue;
            int tag = strlen(*(enter_text1 + j));
            while (tag < wynik) {
                strcat(*(save_cross + j), " ");
                tag++;
            }

            strcat(*(save_cross + j), "   ");
            strcat(*(save_cross + j), *(enter_text2 + j - to_result));
        }
    } else if (asd2 > asd1) {
        j = Z;
        while (j < asd2 - asd1) {
            int H = Z;
            while (H < wynik) {
                strcat(*(save_cross + j), " ");
                H++;
            }
            strcat(*(save_cross + j), "   ");
            strcat(*(save_cross + j), *(enter_text2 + j));
            j++;
        }

        for (; j < to_result1; ++j) {
            if (*(enter_text1 + j - to_result) == NULL) {
                check_text = 1;
                break;
            }
            strcat(*(save_cross + j), *(enter_text1 + j - to_result));
            if (j >= win2)
                continue;
            for (int kotyk = (int )strlen(*(enter_text1 + j - to_result)); kotyk < wynik; ++kotyk) {
                strcat(*(save_cross + j), " ");
            }
            strcat(*(save_cross + j), "   ");
            strcat(*(save_cross + j), *(enter_text2 + j));
        }
    } else {
        for (j = Z; j < to_result1; ++j) {
            if (*(enter_text1 + j) == NULL) {
                check_text = 1;
                break;
            }
            strcat(*(save_cross + j), *(enter_text1 + j));

            if (j >= win2) {
                continue;
            }
            int hj = (int)strlen(*(enter_text1 + j));
            while (hj < wynik) {
                strcat(*(save_cross + j), " ");
                hj++;
            }
            strcat(*(save_cross + j), "   ");
            strcat(*(save_cross + j), *(enter_text2 + j));
        }
    }

    if (check_text == ONE) {
        while (j < to_result1) {
            int cj = Z;
            while (cj < wynik) {
                strcat(*(save_cross + j), " ");
                cj++;
            }
            strcat(*(save_cross + j), "   ");
            if (!(asd1 > asd2)) {
                to_result = Z;
            }
            strcat(*(save_cross + j), *(enter_text2 + j - to_result));
            j++;
        }
    }

    *result = save_cross;

    return Z;
}

void clearBuffer() {
    int c;
    while ((c = getchar()) != '\n');
}

char* allocate_string(int size) {
    char* str = calloc(size, sizeof(char));
    if (str == NULL) {
        return NULL;
    }
    return str;
}

int main() {
    char *allocate_aboba = allocate_string(11), *allocate_chinazes = allocate_string(11), *allocate_soundtre = allocate_string(11), *allocate_patsiuk = allocate_string(11);
    if (allocate_aboba == NULL || allocate_chinazes == NULL || allocate_soundtre == NULL || allocate_patsiuk == NULL) {
        free(allocate_aboba); free(allocate_chinazes); free(allocate_soundtre); free(allocate_patsiuk);
        printf("Failed to allocate memory");
        return 8;
    }

    printf("Enter words:");
    if (scanf("%10s %10s %10s %10s", allocate_aboba, allocate_chinazes, allocate_soundtre, allocate_patsiuk) != 4) {
        printf("Incorrect input");
        free(allocate_aboba); free(allocate_chinazes); free(allocate_soundtre); free(allocate_patsiuk);
        return 1;
    }
    clearBuffer();

    char **res = NULL;
    char **result1 = NULL;
    char **result2 = NULL;
    int result = create_double_leading_word_cross(allocate_aboba, allocate_chinazes, allocate_soundtre, allocate_patsiuk, &res, &result1, &result2);


    if (result == 8) {
        printf("Failed to allocate memory");
        free(allocate_aboba);
        free(allocate_chinazes);
        free(allocate_soundtre);
        free(allocate_patsiuk);
        return 8;
    }

    switch(result) {
        case 1:
            printf("Incorrect input");
            free(allocate_aboba);
            free(allocate_chinazes);
            free(allocate_soundtre);
            free(allocate_patsiuk);
            return 1;
        case 2:
            printf("Unable to make two crosses");
            free(allocate_aboba);
            free(allocate_chinazes);
            free(allocate_soundtre);
            free(allocate_patsiuk);
            return Z;
        case 3:
            printf("Failed to allocate memory");
            free(allocate_aboba);
            free(allocate_chinazes);
            free(allocate_soundtre);
            free(allocate_patsiuk);
            return 8;
        case 0:
            print_text(result1);
            printf("\n");
            print_text(result2);
            printf("\n");
            print_text(res);
            destroy(result1);
            destroy(result2);
            destroy(res);
            break;
        default:
            printf("Unexpected error");
            free(allocate_aboba);
            free(allocate_chinazes);
            free(allocate_soundtre);
            free(allocate_patsiuk);
    }

    free(allocate_aboba);
    free(allocate_chinazes);
    free(allocate_soundtre);
    free(allocate_patsiuk);
    return result;
}
