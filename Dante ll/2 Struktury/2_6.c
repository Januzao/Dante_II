#include <stdio.h>
#include <math.h>
#include "tested_declarations.h"
#include "rdebug.h"

struct point_t {
    int x;
    int y;
};

struct segment_t {
    struct point_t start;
    struct point_t end;
};

struct segment_t* read_segment(struct segment_t* p) {
    if(p == NULL){
        return NULL;
    }
    printf("Enter coordinates of the first point:\n");
    printf("Enter X coordinate:");
    if(scanf("%d", &(p->start.x)) != 1){
        return NULL;
    }
    printf("Enter Y coordinate:");
    if(scanf("%d", &(p->start.y)) != 1){
        return NULL;
    }
    printf("Enter coordinates of the second point:\n");
    printf("Enter X coordinate:");
    if(scanf("%d", &(p->end.x)) != 1){
        return NULL;
    }
    printf("Enter Y coordinate:");
    if(scanf("%d", &(p->end.y)) != 1){
        return NULL;
    }
    return p;

}

void show_segment(const struct segment_t* p) {
    if(p == NULL) return;
    printf("Line start coords: x = %d; y = %d\n", p->start.x, p->start.y);
    printf("Line end coords: x = %d; y = %d\n", p->end.x, p->end.y);

}
float length(const struct segment_t* s, int *err_code) {
    if (s == NULL){
        if (err_code != NULL) *err_code = 1;
        return -1;
    }

    float dx = s->end.x - s->start.x;
    float dy = s->end.y - s->start.y;
    float result = sqrt(dx*dx + dy*dy);

    if (isnan(result)) {
        *err_code = 1;
        return -1;
    }

    if(err_code != NULL) *err_code = 0;
    return result;
}

int main() {
    struct segment_t segment;
    struct segment_t* p_segment = &segment;


    if (read_segment(p_segment) == NULL){
        printf("Incorrect input");
        return 1;
    }
    show_segment(p_segment);

    int err_code;
    float len = length(p_segment, &err_code);
    if (err_code == 1){
        printf("Incorrect input");
        return 1;
    }

    printf("%.2f", len);
    return 0;
}






