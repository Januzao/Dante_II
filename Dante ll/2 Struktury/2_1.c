#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "tested_declarations.h"
#include "rdebug.h"

struct point_t {
    int x;
    int y;
};

struct point_t *set(struct point_t *p, int x, int y) {
    if (p == NULL) {
        return NULL;
    }

    p->x = x;
    p->y = y;
    return p;
}

void show(const struct point_t *p){
    if(p == NULL)
        return;

    printf("x = %d; y = %d\n", p->x, p->y);
}

struct point_t *read(struct point_t *p){
    if(p == NULL) return NULL;
    printf("Podaj wspolrzedna x:");
    if(scanf("%d", &(p->x)) != 1){
        printf("Incorrect input\n");
        return NULL;
    }
    printf("Podaj wspolrzedna y:");
    if(scanf("%d", &(p->y)) != 1){
        printf("Incorrect input\n");
        return NULL;
    }
    return p;
}


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
int main() {
    srand(time(NULL));

    struct point_t point1;
    if(read(&point1) == NULL){
        return 1;
    }
      struct point_t point2;
        point2.x = rand() % 20 - 10;
        point2.y = rand() % 20 - 10;

    show(&point1);
    show(&point2);

    int err_code;
    float dist = distance(&point1, &point2, &err_code);
    if(err_code == 0){
        printf("%.2f", dist);
    }
    else
        printf("Incorrect input");
    return 0;
}



