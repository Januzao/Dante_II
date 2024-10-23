#include <stdio.h>
#include <math.h>
#include <float.h>
#include <ctype.h>
#include "tested_declarations.h"
#include "rdebug.h"

struct point_t {
    int x;
    int y;
};

float distance(const struct point_t *p1, const struct point_t *p2, int *err_code) {
    if (p1 == NULL || p2 == NULL) {
        if (err_code != NULL) {
            *err_code = 1;
        }
        return -1;
    }

    float dx = p2->x - p1->x;
    float dy = p2->y - p1->y;
    float dist = sqrt(dx * dx + dy * dy);

    if (err_code != NULL) {
        *err_code = 0;
    }
    return dist;
}

void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }
}

int check_for_text(FILE *file) {
    char ch;
    while ((ch = fgetc(file)) != EOF) {
        if (!isdigit(ch) && ch != ' ' && ch != '\n' && ch != '\t' && ch != '-'){
            return 1;
        }
    }
    fseek(file, 0, SEEK_SET);
    return 0;
}

int main() {
    FILE *file;
    char filename[100];
    printf("Podaj sciezke:");
    scanf("%99s", filename);
    clear_input_buffer();

    file = fopen(filename, "r");
    if (file == NULL) {
        printf("Couldn't open file\n");
        return 4;
    }

    if (check_for_text(file)) {
        printf("File corrupted");
        fclose(file);
        return 6;
    }

    fclose(file);

    file = fopen(filename, "r");
    if (file == NULL) {
        printf("Couldn't open file\n");
        return 4;
    }

    struct point_t p1, p2, min_p1, min_p2;
    int err_code, count = 0;
    float min_dist = FLT_MAX, current_dist;
    long pos;

    while (fscanf(file, "%d %d", &p1.x, &p1.y) == 2) {
        count += 2;
        pos = ftell(file);

        while (fscanf(file, "%d %d", &p2.x, &p2.y) == 2) {
            current_dist = distance(&p1, &p2, &err_code);
            if (err_code == 0 && current_dist < min_dist) {
                min_dist = current_dist;
                min_p1 = p1;
                min_p2 = p2;
            }
            else if (current_dist == min_dist){
                if (p1.x < min_p1.x){
                    min_p1 = p1;
                    min_p2 = p2;
                }
            }
        }

        fseek(file, pos, SEEK_SET);
    }

    fclose(file);

    if (count <= 2){
        printf("File corrupted\n");
        return 6;
    }
    printf("%d %d %d %d", min_p2.x, min_p2.y, min_p1.x, min_p1.y);

    return 0;
}

