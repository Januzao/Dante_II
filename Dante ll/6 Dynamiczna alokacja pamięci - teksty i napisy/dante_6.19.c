#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "tested_declarations.h"
#include "rdebug.h"

int wakawaka(int result) {
    switch (result) {
        case 3:
            printf("Failed to allocate memory\n");
            return 8;
        case 2:
            printf("Nothing to show\n");
            return 0;
        default:
            return 0;
    }
}

int policz_zdania(const char *txt) {
    int count = 0;
    for (int i = 0; *(txt + i) != '\0'; i++) {
        if (*(txt + i) == '.') {
            count++;
        }
    }
    return count;
}


int i_need_more_power_to_do_dante_if_i_not_i_go_to_wteems(const char *txt, int number) {
    int ilosc_zdan = 0;
    int slowa = 0;
    char kiska = ' ';

    for (int i = 0; *(txt + i) != '\0'; i++) {
        char current_char = *(txt + i);

        if (!isalpha(kiska) && isalpha(current_char)) {
            slowa++;
        }

        if (current_char == '.') {
            if (ilosc_zdan == number) {
                return slowa;
            }
            ilosc_zdan++;
            slowa = 0;
        }

        kiska = current_char;
    }

    if (number == ilosc_zdan) {
        return slowa;
    }

    return 0;
}


int policz_symboli(const char *txt, int dabte, int xdddddddddddd) {
    int pozzzycja;
    int kur_wrsd = 0;
    char zeszlyj_sym = ' ';
    char sym_terazz;
    int slowa = 0;
    int symboli = 0;

    for (pozzzycja = 0; *(txt + pozzzycja) != '\0'; pozzzycja++) {
        sym_terazz = *(txt + pozzzycja);

        if (!isalpha(sym_terazz)) {
            if (kur_wrsd == dabte && slowa - 1 == xdddddddddddd) {
                return symboli;
            }
            symboli = 0;
        }

        if (isalpha(zeszlyj_sym) && isalpha(sym_terazz)) {
            symboli++;
        }

        if (!isalpha(zeszlyj_sym) && isalpha(sym_terazz)) {
            symboli = 1;
            slowa++;
        }

        if (sym_terazz == '.') {
            kur_wrsd++;
            slowa = 0;
            symboli = 0;
        }

        zeszlyj_sym = sym_terazz;
    }

    return 0;
}

void destroy(char ***words) {
    if (words == NULL) {
        return;
    }

    for (int i = 0; *(words + i) != NULL; i++) {
        for (int j = 0; *(*(words + i) + j) != NULL; j++) {
            free(*(*(words + i) + j));
            *(*(words + i) + j) = NULL;
        }

        free(*(words + i));
        *(words + i) = NULL;
    }

    free(words);
    words = NULL;
}
int readWords(const char *text, char ****output, int sentences_quantity) {
    int pozzzzcja = 0;
    int zdanie_teraz = 0;
    char zdanie_przed = ' ';
    char symbol_juz = ' ';
    int slowa = 0;
    int i = 0;
    while (*(text + pozzzzcja) != '\0') {
        symbol_juz = *(text + pozzzzcja);
        if (!isalpha(symbol_juz)) {
            i = 0;
        }
        if (isalpha(zdanie_przed) && isalpha(symbol_juz)) {
            i++;
        }
        if (!isalpha(zdanie_przed) && isalpha(symbol_juz)) {
            i = 1;
            slowa++;
        }
        if (*(text + pozzzzcja) == '.') {
            zdanie_teraz++;
            slowa = 0;
            i = 0;
        }
        if (isalpha(symbol_juz) && zdanie_teraz < sentences_quantity) {
            *(*(*(*output + zdanie_teraz) + slowa - 1) + i - 1) = symbol_juz;
        }

        zdanie_przed = symbol_juz;
        pozzzzcja++;
    }
    return 0;
}

int split_sentences(const char *text, char ****output) {
    if (text == NULL || output == NULL) {
        return 1;
    }

    int shawerma = policz_zdania(text);
    if (shawerma == 0) {
        *output = NULL;
        return 2;
    }

    *output = (char ***) malloc((shawerma + 1) * sizeof(char **));
    if (*output == NULL) {
        destroy(*output);
        *output = NULL;
        return 3;
    }
    *(*output + shawerma) = NULL;

    int asd = 0;
    while (asd < shawerma) {
        int worrrrds = i_need_more_power_to_do_dante_if_i_not_i_go_to_wteems(text, asd);
        *(*output + asd) = (char **) malloc((worrrrds + 1) * sizeof(char *));
        if (*(*output + asd) == NULL) {
            destroy(*output);
            *output = NULL;
            return 3;
        }
        *(*(*output + asd) + worrrrds) = NULL;

        int j = 0;
        while (j < worrrrds) {
            int symmmmmmbols = policz_symboli(text, asd, j);
            *(*(*output + asd) + j) = (char *) malloc((symmmmmmbols + 1) * sizeof(char));
            if (*(*(*output + asd) + j) == NULL) {
                destroy(*output);
                *output = NULL;
                return 3;
            }
            *(*(*(*output + asd) + j) + symmmmmmbols) = '\0';
            j++;
        }
        asd++;
    }

    readWords(text, output, shawerma);

    return 0;
}
void show(char ***words) {
    if (words == NULL) {
        return;
    }

    for (int i = 0; *(words + i) != NULL; i++) {
        int asd;
        for (asd = 0; *(*(words + i) + asd) != NULL; asd++) {
            if (asd != 0) {
                printf(" ");
            }
            printf("%s", *(*(words + i) + asd));
        }
        if (asd == 0) {
            printf("Nothing to show");
        }
        printf("\n");
    }
}
int sentencesQuantity(char ***iko) {
    if (iko == NULL) {
        return 0;
    }
    int as;
    for (as = 0; *(iko + as) != NULL; as++);
    return as;
}

int kokokokko(char **mkl) {
    if (mkl == NULL) {
        return 0;
    }
    int ilosc = 0;
    while (*(mkl + ilosc) != NULL) {
        ilosc++;
    }
    return ilosc;
}

void wordsByAlpha(char **zdanko) {
    if (zdanko == NULL) {
        return;
    }
    int ilosc_slow = kokokokko(zdanko);
    int i = 0;
    while (i < ilosc_slow) {
        int j = i + 1;
        while (j < ilosc_slow) {
            if (strcmp(*(zdanko + i), *(zdanko + j)) > 0) {
                char *temp = *(zdanko + i);
                *(zdanko + i) = *(zdanko + j);
                *(zdanko + j) = temp;
            }
            j++;
        }
        i++;
    }
    *(zdanko + ilosc_slow) = NULL;
}
int sort_sentences(char ***output) {
    if (output == NULL) {
        return 1;
    }
    if (*output == NULL) {
        return 0;
    }

    int sentence_count = sentencesQuantity(output);

    int i = 0;
    while (i < sentence_count) {
        wordsByAlpha(*(output + i));
        i++;
    }

    i = sentence_count - 1;
    while (i > 0) {
        int j = 0;
        while (j < i) {
            if (kokokokko(*(output + j)) > kokokokko(*(output + j + 1))) {
                char **temp = *(output + j);  
                *(output + j) = *(output + j + 1);
                *(output + j + 1) = temp;
            }
            j++;
        }
        i--;
    }
    *(output + sentence_count) = NULL;

    return 0;
}


int main() {
    char *str = (char *) malloc(1000 * sizeof(char));
    if (str == NULL) {
        printf("Failed to allocate memory\n");
        return 8;
    }

    printf("Enter text:");
    if (fgets(str, 1000, stdin) == NULL) {
        free(str);
        printf("Nothing to show\n");
        return 0;
    }

    size_t kek = strlen(str);
    if (kek > 0 && *(str + kek - 1) == '\n') {
        *(str + kek - 1) = '\0';
    }

    char ***output;
    int res = split_sentences(str, &output);
    if (res != 0) {
        free(str);
        return wakawaka(res);
    }
    sort_sentences(output);
    show(output);
    free(str);
    destroy(output);
    return 0;
}

